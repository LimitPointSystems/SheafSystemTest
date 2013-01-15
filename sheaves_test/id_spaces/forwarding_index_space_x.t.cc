// $RCSfile$ $Revision$ $Date$

// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example forwarding_index_space_x.t.cc
/// Test driver for forwarding id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "forwarding_index_space_handle.h"
#include "constant_index_space_interval.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(6);

  string lname("test_forwarding_id_space");

  pod_index_type lspace_id =
    make_id_space_interval(lid_spaces,
			   "constant_index_space_interval",
			   constant_index_space_interval::make_arg_list(2),
			   2);

  // Test handle facet.

  test_implicit_handle_facet<forwarding_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  // Postconditions:

  // Exit:

  return 0;
}

  
