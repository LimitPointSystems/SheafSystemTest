// $RCSfile: implicit_index_space_interval.t.cc,v $ $Revision: 1.6 $ $Date: 2012/07/04 16:42:19 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example id_spaces/implicit_index_space_interval.t.cc
/// Test driver for class implicit_index_space_interval.

#include "arg_list.h"
#include "array_implicit_index_map_interval.h"
#include "gluable_sum_index_space.h"
#include "implicit_index_space_interval.h"
#include "index_space.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "mutable_index_map.h"
#include "scoped_index.h"
#include "std_strstream.h"
#include "sum_index_space.h"
#include "test_index_spaces.h"

using namespace sheaf;

namespace
{

///
/// Simulate the zone-vertex id space for a polyline with xseg_ct.
///
pod_index_type
create_connectivity(index_space_family& xid_spaces,
		    block<pod_index_type>& xconn,
		    pod_index_type xvertex_space_id,
		    int xseg_ct)
{
  // Create the connectivity array.

  int lconn_ct = 2*xseg_ct;
  xconn.reserve(lconn_ct);
  index_space& lvertex_space = xid_spaces.id_space(xvertex_space_id);
  index_space_iterator* lvertex_itr = lvertex_space.iterator(true);
  for(int i = 0; !lvertex_itr->is_done(); i+=2)
  {
    pod_index_type lid = lvertex_itr->top_pod();
    if(i < lconn_ct)
      xconn[i] = lid;
    if(i > 0)
      xconn[i-1] = lid;

    lvertex_itr->next();
  }
  delete lvertex_itr;

  // Create the zone-vertex id space.

  arg_list lmaps_args =
    array_implicit_index_map_interval::make_arg_list(xconn, 2, xseg_ct);
  arg_list lspaces_args = implicit_index_space_interval::
    make_arg_list("array_implicit_index_map_interval", lmaps_args);

  return
    xid_spaces.new_secondary_id_space_interval("implicit_index_space_interval",
					       lspaces_args);
}

///
/// Test the array_implicit_interval_map by simulating the vertex connectivity
/// of a polyline with xseg_ct line segements.
///
void test_array_interval(int xseg_ct)
{
  print_header("Test Creating interval.");

  // Create the id space family.

  index_space_family lid_spaces;
  gluable_sum_index_space& ltop_id_space = lid_spaces.top_id_space();

  // Add the members

  ltop_id_space.new_id(); // bottom
  ltop_id_space.new_id(); // top
  lid_spaces.update_standard_id_spaces(); //  Used to test the clear id spaces.
  lid_spaces.new_primary_id_space(xseg_ct); // zones/edges
  pod_index_type lvertex_space_id = lid_spaces.new_primary_id_space(xseg_ct+1); // vertices

  // Construct connectivity block here so it stays in scope.

  block<pod_index_type> lconn;

  // Create the zone-vertex connectivity.

  create_connectivity(lid_spaces, lconn, lvertex_space_id, xseg_ct);

  cout << lid_spaces << endl;

  // Test clearing the non-standard id spaces.

  print_header("Test Clearing Non-Standard ID Spaces");

  lid_spaces.clear_id_spaces();

  cout << lid_spaces << endl;

  // Test creating connectivity after clear.

  print_header("Test Creating Connectivity after Clear");

  lid_spaces.new_primary_id_space(xseg_ct); // zones/edges
  lvertex_space_id = lid_spaces.new_primary_id_space(xseg_ct+1); // vertices
  lconn.clear();

  pod_index_type lconn_space_id =
    create_connectivity(lid_spaces, lconn, lvertex_space_id, xseg_ct);

  cout << lid_spaces << endl;

  // Test deleting entire interval.

  print_header("Test Deleting Entire Interval");

  lid_spaces.delete_secondary_id_space_interval(lconn_space_id);

  cout << lid_spaces << endl;

  // Test creating connectivity after interval delete.

  print_header("Test Creating Connectivity after Interval Delete");

  lconn_space_id =
    create_connectivity(lid_spaces, lconn, lvertex_space_id, xseg_ct);

  cout << lid_spaces << endl;

  // Test deleting the individual id spaces.

  print_header("Test Deleting the Individual Id Spaces");

  lid_spaces.delete_secondary_id_space(lconn_space_id); // First id space.
  lid_spaces.delete_secondary_id_space(lconn_space_id+xseg_ct-1); // Last id space.
  lid_spaces.delete_secondary_id_space(lconn_space_id+(xseg_ct/2)); // Middle id space.

  cout << lid_spaces << endl;
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

  test_array_interval(lseg_ct);
  
  return 0;
}


