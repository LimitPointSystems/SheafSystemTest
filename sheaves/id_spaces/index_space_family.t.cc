// $RCSfile: index_space_family.t.cc,v $ $Revision: 1.12 $ $Date: 2012/07/04 16:42:20 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example id_spaces/index_space_family.t.cc
/// Test driver for class index_space_family.

#include "arg_list.h"
#include "array_index_map.h"
#include "index_space.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "gluable_sum_index_space.h"
#include "hash_index_map.h"
#include "scoped_index.h"
#include "simple_index_space.h"
#include "std_strstream.h"
#include "test_index_spaces.h"

using namespace sheaf;

namespace
{

///
/// Create id spaces inorder to test the equivalence iteration.
///
void create_eqv(index_space_family& xfamily)
{
  gluable_sum_index_space& ltop = xfamily.top_id_space();
  size_type lub = ltop.end();

  // Reverse space: the range is the reverse of the domain.

  arg_list lmap_args = array_index_map::make_arg_list(lub);
  arg_list lspace_args =
    simple_index_space::make_arg_list("array_index_map", lmap_args);

  xfamily.new_secondary_id_space("reverse_space", "simple_index_space",
				 lspace_args, true);

  mutable_index_map& lmap_reverse =
    xfamily.id_space("reverse_space").id_map<mutable_index_map>();

  // Space 200: every other top id.

  xfamily.new_secondary_id_space("space_200", "simple_index_space",
				 lspace_args, true);

  mutable_index_map& lmap_200 =
    xfamily.id_space("space_200").id_map<mutable_index_map>();

  // Space 300: every third top id.

  xfamily.new_secondary_id_space("space_300", "simple_index_space",
				 lspace_args, true);

  mutable_index_map& lmap_300 =
    xfamily.id_space("space_300").id_map<mutable_index_map>();

  // Space 400: every fourth top id.

  xfamily.new_secondary_id_space("space_400", "simple_index_space",
				 lspace_args, true);

  mutable_index_map& lmap_400 =
    xfamily.id_space("space_400").id_map<mutable_index_map>();

  // Populate the id spaces.

  index_space_iterator* litr = ltop.iterator(true);

  while(!litr->is_done())
  {
    pod_index_type lpod = litr->pod();

    // Reverse space: The range is the reverse of the domain.

    lmap_reverse.insert_entry(lub-lpod, lpod);

    if((lpod % 2) == 0)
    {
      // Space 200: Every other id.

      lmap_200.insert_entry((200 + lpod), lpod);
    }
    
    if((lpod % 3) == 0)
    {
      // Space 300: Every third id.

      lmap_300.insert_entry((300 + lpod), lpod);
    }

    if((lpod % 4) == 0)
    {
      // Space 400: Every fourth id.

      lmap_400.insert_entry((400 + lpod), lpod);
    }

    litr->next();
  }

  delete litr;
}

///
/// Simulate creating an top id space from scratch.
///
void create(size_t xinterval_mbr_ct)
{
  // Print out the header.

  print_header("Simulate creating from scratch.");

  // Create the id space family.

  index_space_family lid_spaces;
  gluable_sum_index_space& ltop_id_space = lid_spaces.top_id_space();

  // Add some members

  ltop_id_space.new_id(); // bottom
  ltop_id_space.new_id(); // top
  ltop_id_space.new_id(); // id before creating interval.

  lid_spaces.new_primary_id_space(xinterval_mbr_ct); // interval.

  ltop_id_space.new_id(); // id after creating interval.

  // Create the equivalance maps.

  create_eqv(lid_spaces);

  // Output the id spaces.

  cout << lid_spaces << endl;

  // Output the top id map.

  test_domain_id_iterator(ltop_id_space);
  test_range_id_iterator(ltop_id_space);
}

///
/// Simulate reading the entire top id space from a file.
///
void read_all(size_t xinterval_mbr_ct)
{
  // Print out the header.

  print_header("Simulate reading all.");

  // Create the id space family.

  index_space_family lid_spaces;
  gluable_sum_index_space& ltop_id_space = lid_spaces.top_id_space();

  // Add all members from the file (reconstruct create example above but in
  // random order).

  ltop_id_space.new_id(3); // id after creating interval.
  ltop_id_space.new_id(1); // top

  lid_spaces.new_primary_id_space(RESERVED_TERM_SIZE, xinterval_mbr_ct); // interval

  ltop_id_space.new_id(0); // bottom
  ltop_id_space.new_id(2); // id before creating interval.

  // Add some new members.

  ltop_id_space.new_id(); // new id
  lid_spaces.new_primary_id_space(xinterval_mbr_ct); // new interval

  // Create the equivalance maps.

  create_eqv(lid_spaces);

  // Output the index_space_family.

  cout << lid_spaces << endl;

  // Output the top id map.

  test_domain_id_iterator(ltop_id_space);
  test_range_id_iterator(ltop_id_space);
}

///
/// Simulate deleting members.
///
void delete_members(size_t xinterval_mbr_ct)
{
  // Print out the header.

  print_header("Simulate deleting members.");

  // Create the id space family.

  index_space_family lfamily;

  // Create the id space family.

  index_space_family lid_spaces;
  gluable_sum_index_space& ltop_id_space = lid_spaces.top_id_space();

  // Add some members

  ltop_id_space.new_id(); // bottom
  ltop_id_space.new_id(); // top
  ltop_id_space.new_id(); // id before creating intervals.

  pod_index_type lterm_id = lid_spaces.new_primary_id_space(xinterval_mbr_ct); // interval 0
  lid_spaces.new_primary_id_space(xinterval_mbr_ct); // interval 1.

  ltop_id_space.new_id(); // id after creating intervals.

  // Output before test.

  print_subheader("Before deletion test");

  cout << lid_spaces << endl;

  test_domain_id_iterator(ltop_id_space);
  test_range_id_iterator(ltop_id_space);

  // Test deleting.

  lid_spaces.delete_primary_id_space(lterm_id); // delete interval 0.
  ltop_id_space.delete_id(3); // delete id after creating intervals.
  ltop_id_space.new_id(); // id after first delete.
  ltop_id_space.delete_id(2); // delete id before creating intervals.

  // Output after test.

  print_subheader("After deletion test");

  cout << lid_spaces << endl;

  test_domain_id_iterator(ltop_id_space);
  test_range_id_iterator(ltop_id_space);
}

///
/// Simulate overflowing the reserved id space.
///
void reserved_ids(size_t xinterval_mbr_ct)
{
  // Print out the header.

  print_header("Simulate overflowing the reserved id space.");

  // Create the id space family.

  index_space_family lid_spaces;
  gluable_sum_index_space& ltop_id_space = lid_spaces.top_id_space();

  // Add some members

  ltop_id_space.new_id(); // bottom
  ltop_id_space.new_id(); // top

  lid_spaces.new_primary_id_space(xinterval_mbr_ct); // interval.

  for(int i = 0; i < RESERVED_TERM_SIZE; i++)
  {
    ltop_id_space.new_id();
  }

  // Output the id spaces.

  cout << lid_spaces << endl;
}

///
/// Simulate clearing the non-standard id spaces and ids.
///
void clear_ids(size_t xinterval_mbr_ct)
{
  // Print out header

  print_header("Simulate clearing non-standard id spaces and ids.");

  // Create the id space family.

  index_space_family lid_spaces;
  gluable_sum_index_space& ltop_id_space = lid_spaces.top_id_space();

  // Create standard members.

  ltop_id_space.new_id(); // bottom
  ltop_id_space.new_id(); // top
  lid_spaces.new_primary_id_space(xinterval_mbr_ct);

  // Set the standard ids.

  lid_spaces.update_standard_id_spaces();
  
  print_subheader("Standard Id Spaces and Ids.");

  cout << lid_spaces << endl;
  test_space_iterator(ltop_id_space, true);

  // Add some non-standard id spaces and ids.

  ltop_id_space.new_id(); // Non-standard top id.
  lid_spaces.new_primary_id_space(xinterval_mbr_ct); // Non-standard primary id space.
  create_eqv(lid_spaces); // Non-standard secondary id spaces.

  print_subheader("Added Non-Standard Id Spaces and Ids.");

  cout << lid_spaces << endl;
  test_space_iterator(ltop_id_space, true);

  // Clear non-standard id space and ids.

  lid_spaces.clear_id_spaces();

  print_subheader("Cleared Non-Standard Id Spaces and Ids.");

  cout << lid_spaces << endl;
  test_space_iterator(ltop_id_space, true);
}


} // unnamed namespace

///
/// Main routine for testing index_space_family.
///
int main(int argc, char** argv)
{
  size_t lrange_mbr_ct = argc > 1 ? atoi(argv[1]) : 4;

  assertion(lrange_mbr_ct >= 4);

  create(lrange_mbr_ct);
  read_all(lrange_mbr_ct);
  delete_members(lrange_mbr_ct);
  reserved_ids(lrange_mbr_ct);
  clear_ids(lrange_mbr_ct);
  
  return 0;
}


