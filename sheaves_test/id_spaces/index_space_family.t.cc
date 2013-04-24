

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example id_spaces/index_space_family.t.cc
/// Test driver for class index_space_family.

#include "arg_list.h"
#include "array_index_space_state.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "hash_index_space_state.h"
#include "hub_index_space_handle.h"
#include "mutable_index_space_handle.h"
#include "namespace_poset.h"
#include "std_strstream.h"
#include "test_index_spaces.h"

//#define TEST_RELEASE_FAILURE

using namespace sheaf;

namespace
{

///
/// Create id spaces inorder to test the equivalence iteration.
///
void create_eqv(index_space_family& xfamily)
{
  const hub_index_space_handle& lhub = xfamily.hub_id_space();
  size_type lub = lhub.end();

  // Reverse space: the range is the reverse of the domain.

  arg_list lspace_args = array_index_space_state::make_arg_list(lub);
  xfamily.new_secondary_state("reverse_space", "array_index_space_state",
			      lspace_args, true);

  mutable_index_space_handle& lspace_reverse =
    xfamily.get_id_space<mutable_index_space_handle>("reverse_space");

  // Space 200: every other hub id.

  lspace_args = hash_index_space_state::make_arg_list(lub);
  xfamily.new_secondary_state("space_200", "hash_index_space_state",
			      lspace_args, true);

  mutable_index_space_handle& lspace_200 =
    xfamily.get_id_space<mutable_index_space_handle>("space_200");

  // Space 300: every third hub id.

  xfamily.new_secondary_state("space_300", "hash_index_space_state",
			      lspace_args, true);

  mutable_index_space_handle& lspace_300 =
    xfamily.get_id_space<mutable_index_space_handle>("space_300");

  // Space 400: every fourth hub id.

  xfamily.new_secondary_state("space_400", "hash_index_space_state",
			      lspace_args, true);

  mutable_index_space_handle& lspace_400 =
    xfamily.get_id_space<mutable_index_space_handle>("space_400");

  // Populate the id spaces.

  index_space_iterator& litr = lhub.get_iterator();

  while(!litr.is_done())
  {
    pod_index_type lpod = litr.pod();

    // Reverse space: The range is the reverse of the domain.

    lspace_reverse.insert(lub-lpod, lpod);

    if((lpod % 2) == 0)
    {
      // Space 200: Every other id.

      lspace_200.insert((200 + lpod), lpod);
    }
    
    if((lpod % 3) == 0)
    {
      // Space 300: Every third id.

      lspace_300.insert((300 + lpod), lpod);
    }

    if((lpod % 4) == 0)
    {
      // Space 400: Every fourth id.

      lspace_400.insert((400 + lpod), lpod);
    }

    litr.next();
  }

  lhub.release_iterator(litr);
}

///
/// Simulate creating an hub id space from scratch.
///
void create(size_t xinterval_mbr_ct)
{
  // Print out the header.

  print_out_header("Simulate creating from scratch.");

  // Create the id space family.

  index_space_family lid_spaces;

  // Add some members

  lid_spaces.new_id(); // bottom
  lid_spaces.new_id(); // top
  lid_spaces.new_id(); // id before creating interval.

  lid_spaces.new_primary_state(xinterval_mbr_ct); // interval.

  lid_spaces.new_id(); // id after creating interval.

#ifdef TEST_RELEASE_FAILURE

  // Test releasing a handle allocated on the stack.
  // An assertion should be blown.

  hub_index_space_handle lhandle(lid_spaces, 0);
  lhandle.host().release_handle(lhandle);

#endif

  // Create the equivalance maps.

  create_eqv(lid_spaces);

  // Output the id spaces.

  cout << lid_spaces << endl;

  // Output the hub id space.

  test_iterator(lid_spaces.hub_id_space());
}

///
/// Simulate reading the entire hub id space from a file.
///
void read_all(size_t xinterval_mbr_ct)
{
  // Print out the header.

  print_out_header("Simulate reading all.");

  // Create the id space family.

  index_space_family lid_spaces;

  // Add all members from the file (reconstruct create example above but in
  // random order).

  lid_spaces.new_id(3); // id after creating interval.
  lid_spaces.new_id(1); // top

  lid_spaces.new_primary_state(RESERVED_TERM_SIZE, xinterval_mbr_ct); // interval

  lid_spaces.new_id(0); // bottom
  lid_spaces.new_id(2); // id before creating interval.

  // Add some new members.

  lid_spaces.new_id(); // new id
  lid_spaces.new_primary_state(xinterval_mbr_ct); // new interval

  // Create the equivalance maps.

  create_eqv(lid_spaces);

  // Output the index_space_family.

  cout << lid_spaces << endl;

  // Output the hub id map.

  test_iterator(lid_spaces.hub_id_space());
}

///
/// Simulate deleting members.
///
void delete_members(size_t xinterval_mbr_ct)
{
  // Print out the header.

  print_out_header("Simulate deleting members.");

  // Create the id space family.

  index_space_family lid_spaces;

  // Add some members

  lid_spaces.new_id(); // bottom
  lid_spaces.new_id(); // top
  lid_spaces.new_id(); // id before creating intervals.

  pod_index_type lterm_id = lid_spaces.new_primary_state(xinterval_mbr_ct); // interval 0
  lid_spaces.new_primary_state(xinterval_mbr_ct); // interval 1.

  lid_spaces.new_id(); // id after creating intervals.

  // Output before test.

  print_out_subheader("Before deletion test");

  cout << lid_spaces << endl;

  test_iterator(lid_spaces.hub_id_space());

  // Test deleting.

  lid_spaces.delete_primary_state(lterm_id); // delete interval 0.
  lid_spaces.delete_id(3); // delete id after creating intervals.
  lid_spaces.new_id(); // id after first delete.
  lid_spaces.delete_id(2); // delete id before creating intervals.

  // Output after test.

  print_out_subheader("After deletion test");

  cout << lid_spaces << endl;

  test_iterator(lid_spaces.hub_id_space());
}

///
/// Simulate overflowing the reserved id space.
///
void reserved_ids(size_t xinterval_mbr_ct)
{
  // Print out the header.

  print_out_header("Simulate overflowing the reserved id space.");

  // Create the id space family.

  index_space_family lid_spaces;

  // Add some members

  lid_spaces.new_id(); // bottom
  lid_spaces.new_id(); // top

  lid_spaces.new_primary_state(xinterval_mbr_ct); // interval.

  for(int i = 0; i < RESERVED_TERM_SIZE; i++)
  {
    lid_spaces.new_id();
  }

  // Output the id spaces.

  cout << lid_spaces << endl;

  test_iterator(lid_spaces.hub_id_space());
}

///
/// Simulate clearing the non-standard id spaces and ids.
///
void clear_ids(size_t xinterval_mbr_ct)
{
  // Print out header

  print_out_header("Simulate clearing non-standard id spaces and ids.");

  // Create the id space family.

  index_space_family lid_spaces;

  // Create standard members.

  lid_spaces.new_id(); // bottom
  lid_spaces.new_id(); // top
  lid_spaces.new_primary_state(xinterval_mbr_ct);

  // Set the standard ids.

  lid_spaces.update_standard_id_spaces();
  
  print_out_subheader("Standard Id Spaces and Ids.");

  cout << lid_spaces << endl;
  test_iterator(lid_spaces.hub_id_space());

  // Add some non-standard id spaces and ids.

  lid_spaces.new_id(); // Non-standard hub id.
  lid_spaces.new_primary_state(xinterval_mbr_ct); // Non-standard primary id space.
  create_eqv(lid_spaces); // Non-standard secondary id spaces.

  print_out_subheader("Added Non-Standard Id Spaces and Ids.");

  cout << lid_spaces << endl;
  test_iterator(lid_spaces.hub_id_space());

  // Clear non-standard id space and ids.

  lid_spaces.clear_id_spaces();

  print_out_subheader("Cleared Non-Standard Id Spaces and Ids.");

  cout << lid_spaces << endl;
  test_iterator(lid_spaces.hub_id_space());
}

///
/// Simulate constructing the gathered hub id space.
///
void gather_ids(size_t xinterval_mbr_ct)
{
  // Print out header

  print_out_header("Simulate constructing the gathered hub id space.");

  // Create the id space family.

  index_space_family lid_spaces;

  // Create standard members.

  lid_spaces.new_id(); // bottom
  lid_spaces.new_id(); // top
  lid_spaces.new_primary_state(xinterval_mbr_ct);

  // Create the gathered hub id space.

  lid_spaces.new_gathered_hub_id_space(true);

  // Output the hub id space and gathered hub id space.

  test_iterator(lid_spaces.hub_id_space());
  test_iterator(lid_spaces.gathered_hub_id_space());

  lid_spaces.new_id(4); // new member
  lid_spaces.new_primary_state(300, xinterval_mbr_ct);

  // Create a new member and a new range.

  print_out_subheader("Added Some more members.");

  // Update the gathered hub id space.

  lid_spaces.update_gathered_hub_id_space();

  // Output the hub id space and gathered hub id space.

  test_iterator(lid_spaces.hub_id_space());
  test_iterator(lid_spaces.gathered_hub_id_space());
}

} // unnamed namespace

///
/// Main routine for testing index_space_family.
///
int main(int argc, char** argv)
{
  size_t lrange_mbr_ct = argc > 1 ? atoi(argv[1]) : 4;

  assertion(lrange_mbr_ct >= 4);

  namespace_poset::initialize_id_space_prototypes();

  create(lrange_mbr_ct);
  read_all(lrange_mbr_ct);
  delete_members(lrange_mbr_ct);
  reserved_ids(lrange_mbr_ct);
//   clear_ids(lrange_mbr_ct);
  gather_ids(lrange_mbr_ct);
  
  return 0;
}


