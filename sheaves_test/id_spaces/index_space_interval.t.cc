
// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @example id_spaces/index_space_interval.t.cc
/// Test driver for class id space intervals.

#include "arg_list.h"
#include "array_index_space_interval.h"
#include "hub_index_space_handle.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "ragged_array_index_space_interval.h"
#include "scoped_index.h"
#include "singleton_implicit_index_space_iterator.h"
#include "singleton_index_space_interval.h"
#include "std_strstream.h"
#include "test_index_spaces.h"

using namespace sheaf;

namespace
{

///
/// Simulate the zone-vertex id space for a polyline with xseg_ct.
///
pod_index_type
create_connectivity(index_space_family& xid_spaces,
		    pod_index_type xvertex_space_id,
		    size_type xseg_ct)
{
  // Create the connectivity array.

  size_type lconn_ct = 2*xseg_ct;
  block<pod_index_type> lconn(lconn_ct);
  lconn.set_ct(lconn_ct);
  index_space_iterator& itr = xid_spaces.get_id_space_iterator(xvertex_space_id);
  for(int i = 0; !itr.is_done(); i+=2)
  {
    pod_index_type lid = itr.hub_pod();
    if(i < lconn_ct)
      lconn[i] = lid;
    if(i > 0)
      lconn[i-1] = lid;

    itr.next();
  }
  xid_spaces.release_id_space_iterator(itr);

  // Create the id space interval.

  arg_list largs =
    array_index_space_interval::make_arg_list(lconn, 2, true);

  return xid_spaces.new_secondary_interval("array_index_space_interval",
					   largs, xseg_ct);
}

///
/// Simulate the zone adjacency id space.
///
pod_index_type
create_adjacency(index_space_family& xid_spaces,
		 pod_index_type xzone_space_id,
		 size_type xseg_ct)
{
  // Create the ids per id space array.

  size_type lvertex_ct = xseg_ct+1;

  size_type* lids_per_space = new size_type[lvertex_ct];
  lids_per_space[0] = 1;
  for(int i=1; i<xseg_ct; i++)
  {
    lids_per_space[i] = 2;
  }
  lids_per_space[xseg_ct] = 1;

  // Create the adjacency ragged array.

  ragged_array<pod_index_type> ladj(lids_per_space, lvertex_ct);

  index_space_iterator& itr = xid_spaces.get_id_space_iterator(xzone_space_id);

  for(ragged_array<pod_index_type>::index_type i = 0; !itr.is_done(); i++)
  {
    pod_index_type lid = itr.hub_pod();

    // Add the zone id to the current vertex.

    ladj[i][(i > 0) ? 1 : 0] = lid;

    // Add the zone id to the next vertex.

    ladj[i+1][0] = lid;

    // Move to the next zone.

    itr.next();
  }

  xid_spaces.release_id_space_iterator(itr);

  // Create the id space interval.

  arg_list largs = ragged_array_index_space_interval::make_arg_list(ladj, true);

  return xid_spaces.new_secondary_interval("ragged_array_index_space_interval",
					   largs, lvertex_ct);
}

///
/// Test the ragged array and array id space intervals by simulating
/// the connectivity and adjacency of a polyline with xseg_ct line segements.
///
void test_array_intervals(size_type xseg_ct)
{
  print_out_header("Test Creating Array Intervals.");

  // Create the id space family.

  index_space_family lid_spaces;

  // Add the members

  lid_spaces.new_id(); // bottom
  lid_spaces.new_id(); // top
  lid_spaces.update_standard_id_spaces(); //  Used to test the clear id spaces.
  pod_index_type lzone_space_id = lid_spaces.new_primary_state(xseg_ct); // zones/edges
  pod_index_type lvertex_space_id = lid_spaces.new_primary_state(xseg_ct+1); // vertices

  // Create the zone-vertex connectivity.

  create_connectivity(lid_spaces, lvertex_space_id, xseg_ct);
  create_adjacency(lid_spaces, lzone_space_id, xseg_ct);

  cout << lid_spaces << endl;

  // Test clearing the non-standard id spaces.

  print_out_header("Test Clearing Non-Standard ID Spaces");

  lid_spaces.clear_id_spaces();

  cout << lid_spaces << endl;

  // Test creating connectivity after clear.

  print_out_header("Test Creating Connectivity after Clear");

  lzone_space_id = lid_spaces.new_primary_state(xseg_ct); // zones/edges
  lvertex_space_id = lid_spaces.new_primary_state(xseg_ct+1); // vertices

  pod_index_type lconn_space_id =
    create_connectivity(lid_spaces, lvertex_space_id, xseg_ct);

  pod_index_type ladj_space_id =
    create_adjacency(lid_spaces, lzone_space_id, xseg_ct);

  cout << lid_spaces << endl;

  // Test deleting entire interval.

  print_out_header("Test Deleting Entire Interval");

  lid_spaces.delete_secondary_interval(lconn_space_id);
  lid_spaces.delete_secondary_interval(ladj_space_id);

  cout << lid_spaces << endl;

  /// @todo Uncomment when removing states from an implicit interval is supported.

//   // Test creating connectivity after interval delete.

//   print_out_header("Test Creating Connectivity after Interval Delete");

//   lconn_space_id =
//     create_connectivity(lid_spaces, lvertex_space_id, xseg_ct);
//   ladj_space_id =
//     create_adjacency(lid_spaces, lzone_space_id, xseg_ct);

//   cout << lid_spaces << endl;

//   // Test deleting the individual id spaces.

//   print_out_header("Test Deleting the Individual Id Spaces");

//   lid_spaces.delete_secondary_state(lconn_space_id); // First id space.
//   lid_spaces.delete_secondary_state(lconn_space_id+xseg_ct-1); // Last id space.
//   lid_spaces.delete_secondary_state(lconn_space_id+(xseg_ct/2)); // Middle id space.

//   lid_spaces.delete_secondary_state(ladj_space_id); // First id space.
//   lid_spaces.delete_secondary_state(ladj_space_id+xseg_ct-1); // Second to last id space.
//   lid_spaces.delete_secondary_state(ladj_space_id+((xseg_ct+1)/2)); // Middle id space.

//   cout << lid_spaces << endl;

  /// @todo Add test for overrides.
}

///
/// Test the singleton id space by simulating the connectivity of
/// a point block with xct number of vertices.
///
void test_singleton(size_type xct)
{
  print_out_header("Test Creating Singleton Interval.");

  // Create the id space family.

  index_space_family lid_spaces;

  // Add the members

  lid_spaces.new_id(); // top
  lid_spaces.new_id(); // bottom
  pod_index_type lspace_id = lid_spaces.new_primary_state(xct); // points

  // Create the singleton id space interval.

  pod_index_type lhub_offset = lid_spaces.hub_pod(lspace_id, 0);

  arg_list largs = singleton_index_space_interval::make_arg_list(lhub_offset);

  pod_index_type lbegin = 
    lid_spaces.new_secondary_interval("singleton_index_space_interval", largs, xct);

  cout << lid_spaces << endl;

  print_out_header("Test Singleton Iterators.");

  singleton_implicit_index_space_iterator itr;

  for(pod_index_type i=0; i<xct; ++i)
  {
    itr.attach_to(lid_spaces, i+lbegin);
    test_iterator(itr);
  }
}

} // unnamed namespace

///
/// Main routine for testing implicit_index_space_interval.  This
/// test drivers uses the various types of implicit_index_map_intervals
/// by simulating a 1D polyline with argv[1] number of segements.
///
int main(int argc, char** argv)
{
  size_t lseg_ct = argc > 1 ? atoi(argv[1]) : 5;

  assertion(lseg_ct >= 5);

  test_array_intervals(lseg_ct);

  test_singleton(lseg_ct);

  return 0;
}


