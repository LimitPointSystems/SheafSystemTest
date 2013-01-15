// $RCSfile$ $Revision$ $Date$

// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example primary_sum_index_space_x.t.cc
/// Test driver for primary_sum id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "primary_sum_index_space_handle.h"
#include "primary_sum_index_space_iterator.h"
#include "primary_sum_index_space_state.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  index_space_family lid_spaces;
  lid_spaces.new_id();
  lid_spaces.new_id();

  pod_index_type lspace_id = 0;

  // Test handle facet.

  test_explicit_handle_facet<primary_sum_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  // Test iterator facet.

  test_explicit_iterator_facet<primary_sum_index_space_iterator>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous iterator functions");

  // Postconditions:

  // Exit:

  return 0;
}

  
