// $RCSfile: hash_index_map.t.cc,v $ $Revision: 1.11 $ $Date: 2012/07/04 16:42:19 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example id_spaces/hash_index_map.t.cc
/// Test driver for class hash_index_map.

#include "hash_index_map.h"

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
/// Test index_space created with an hash_id_map.
///
void
test_hash_index_map(index_space_family& xid_spaces, size_t xoffset)
{
  print_header("Testing hash_index_map");

  // Create a space.

  arg_list lmap_args = hash_index_map::make_arg_list(28);
  arg_list lspace_args =
    simple_index_space::make_arg_list("hash_index_map", lmap_args);

  index_space& lspace = make_id_space(xid_spaces,
				      "test_hash_id_map",
				      "simple_index_space",
				      lspace_args);

  hash_index_map& lmap = lspace.id_map<hash_index_map>();
  // Initialize the id map.

  print_header("Initialize the id map.");

  for(int i=0; i<10; i++)
  {
    insert_entry(lmap, i*2, i+xoffset);
  }

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test remove_entry for domain ids.

  print_header("Test remove_entry for domain ids.");

  remove_entry(lmap, 0, false, true);
  remove_entry(lmap, 6, false, true);
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
  insert_entry(lmap, 5, xoffset+3);
  insert_entry(lmap, 25, xoffset+4);

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

  delete_id(xid_spaces, xoffset+1);
  delete_id(xid_spaces, xoffset+7);
  delete_id(xid_spaces, xoffset+8);

  gather(lmap);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test index_space_iterator.

  print_header("Test index_space_iterator.");

  test_space_iterator(lspace, true);
  test_space_iterator(lspace, false);

  // Test empty map.

  print_header("Test empty map.");
  for(pod_index_type i = lmap.domain_begin(); i < lmap.domain_end(); i++)
  {
    remove_entry(lmap, i, false, false);
   }

  update_extrema(lmap);
  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);
}

} // unnamed namespace

///
/// Main routine for testing hash_index_map.
///
int main(int argc, char** argv)
{
  size_t loffset = argc > 1 ? atoi(argv[1]) : 10;

  assertion(loffset >= 0);

  // Construct the family.  Construct a top id range that is the
  // largest domain id (loffset + 15).  This top id range is
  // needed so the index maps can be mapped to the top id space.

  index_space_family lid_spaces;
  lid_spaces.new_primary_id_space(loffset + 14);
  
  // Test the hash_index_map.

  test_hash_index_map(lid_spaces, loffset);

  return 0;
}


