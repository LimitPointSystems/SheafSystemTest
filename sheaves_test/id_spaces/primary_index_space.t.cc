


//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example primary_index_space.t.cc
/// Test driver for primary id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "primary_index_space_handle.h"
#include "primary_index_space_iterator.h"
#include "primary_index_space_state.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  index_space_family lid_spaces;
  pod_index_type lspace_id = lid_spaces.new_primary_state(6);

  // Test handle facet.

  test_handle_facet<primary_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  primary_index_space_handle lhandle(lid_spaces, lspace_id);

  cout << "offset()      = " << lhandle.offset() << endl;
  cout << "extend(10)" << endl;
  lhandle.extend(10);
  cout << "hub_term_id() = " << lhandle.hub_term_id() << endl;

  // Test iterator facet.

  test_iterator_facet<primary_index_space_iterator>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous iterator functions");

  primary_index_space_iterator litr(lid_spaces, lspace_id);

  cout << "offset()             = " << litr.offset() << endl;
  cout << "ct()                 = " << litr.ct() << endl;

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 1, 1);

  // Postconditions:

  // Exit:

  return 0;
}

  
