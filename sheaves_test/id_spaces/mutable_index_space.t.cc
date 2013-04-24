


//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example mutable_index_space.t.cc
/// Test driver for mutable id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "mutable_index_space_handle.h"
#include "hash_index_space_iterator.h"
#include "hash_index_space_state.h"
#include "namespace_poset.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  namespace_poset::initialize_id_space_prototypes();

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(6);

  string lname("test_mutable_id_space");

  pod_index_type lspace_id =
    make_id_space(lid_spaces,
		  lname,
		  "hash_index_space_state",
		  hash_index_space_state::make_arg_list(3)).index();

  mutable_index_space_handle lhandle(lid_spaces, lspace_id);
  push_back(lhandle, 0);
  push_back(lhandle, 2);
  push_back(lhandle, 4);

  // Test handle facet.

  test_handle_facet<mutable_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  // Postconditions:

  // Exit:

  return 0;
}

  
