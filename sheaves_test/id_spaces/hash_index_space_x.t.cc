// $RCSfile$ $Revision$ $Date$

// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example hash_index_space_x.t.cc
/// Test driver for hash id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "mutable_index_space_handle.h"
#include "hash_index_space_iterator.h"
#include "hash_index_space_state.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(6);

  string lname("test_hash_id_space");

  pod_index_type lspace_id =
    make_id_space(lid_spaces,
		  lname,
		  "hash_index_space_state",
		  hash_index_space_state::make_arg_list(3)).index();

  mutable_index_space_handle lhandle(lid_spaces, lspace_id);
  push_back(lhandle, 0);
  push_back(lhandle, 2);
  push_back(lhandle, 4);

  // Test iterator facet.

  test_explicit_iterator_facet<hash_index_space_iterator>(lid_spaces, lspace_id);

  // Test the mutable facet.

  test_mutable_facet(lid_spaces, lspace_id);

  // Postconditions:

  // Exit:

  return 0;
}

  
