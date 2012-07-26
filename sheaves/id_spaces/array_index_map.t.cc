// $RCSfile: array_index_map.t.cc,v $ $Revision: 1.9 $ $Date: 2012/07/04 16:42:19 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example id_spaces/array_index_map.t.cc
/// Test driver for class array_index_map.

#include "array_index_map.h"

#include "arg_list.h"
#include "index_space_family.h"
#include "scoped_index.h"
#include "simple_index_space.h"
#include "std_strstream.h"
#include "test_index_spaces.h"

using namespace sheaf;

namespace
{

///
/// Test index_space created with an array_id_map.
///
void
test_array_index_map(index_space_family& xid_spaces, size_t xoffset)
{
  print_header("Testing array_index_map");

  // Create a space.

  arg_list lmap_args = array_index_map::make_arg_list(14);
  arg_list lspace_args =
    simple_index_space::make_arg_list("array_index_map", lmap_args);

  index_space& lspace = make_id_space(xid_spaces,
				      "test_array_id_map",
				      "simple_index_space",
				      lspace_args);

  array_index_map& lmap = lspace.id_map<array_index_map>();

  // Initialize the id map.

  print_header("Initialize the id map.");

  for(int i=0; i<10; i++)
  {
    push_back(lmap, i+xoffset);
  }

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test remove_entry for domain ids.

  print_header("Test remove_entry for domain ids.");

  remove_entry(lmap, 0, false, true);
  remove_entry(lmap, 3, false, true);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test remove_entry for range ids.

  print_header("Test remove_entry for range ids.");

  remove_entry(lmap, xoffset+4, true, false);
  remove_entry(lmap, xoffset+9, true, false);
  update_extrema(lmap);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test insert_entry.

  print_header("Test insert_entry.");

  insert_entry(lmap, 0, xoffset+10);
  insert_entry(lmap, 4, xoffset+3);
  insert_entry(lmap, 11, xoffset+4);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test push_back.

  print_header("Test push_back.");

  push_back(lmap, xoffset+13);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Gather the map.

  print_header("Gather the map.");

  gather(lmap);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Gather the map after removing top ids.

  print_header("Gather the map after removing top ids.");

  delete_id(xid_spaces, xoffset+7);
  delete_id(xid_spaces, xoffset+8);
  delete_id(xid_spaces, xoffset+13);

  gather(lmap);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test index_space_iterator.

  print_header("Test index_space_iterator.");

  test_space_iterator(lspace, true);
  test_space_iterator(lspace, false);

  // Test empty map.

  print_header("Test empty map.");

  clear(lmap);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);
}

} // unnamed namespace

///
/// Main routine for testing array_index_map.
///
int main(int argc, char** argv)
{
  size_t loffset = (argc > 1) ? atoi(argv[1]) : 10;

  assertion(loffset >= 0);

  // Construct the family.  Construct a top id range that is the
  // largest range id (loffset + 14).  This top id range is
  // needed so the index maps can be mapped to the top id space.

  index_space_family lid_spaces;
  lid_spaces.new_primary_id_space(loffset + 14);
  
  // Test the array_index_map.

  test_array_index_map(lid_spaces, loffset);

  return 0;
}


