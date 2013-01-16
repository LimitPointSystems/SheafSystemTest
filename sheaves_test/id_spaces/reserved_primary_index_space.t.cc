// $RCSfile$ $Revision$ $Date$

// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example reserved_primary_index_space.t.cc
/// Test driver for reserved_primary id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "reserved_primary_index_space_handle.h"
#include "reserved_primary_index_space_iterator.h"
#include "reserved_primary_index_space_state.h"
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

  pod_index_type lspace_id = 1;

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 1, 1);

  // Test handle facet.

  test_handle_facet<reserved_primary_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  reserved_primary_index_space_handle lhandle(lid_spaces, lspace_id);

  cout << "new_id()      = " << lhandle.new_id() << endl;
  cout << "new_id(10)    = " << lhandle.new_hub_id(10) << endl;
  cout << "next_hub_id() = " << lhandle.next_hub_id() << endl;

  // Test iterator facet.

  test_iterator_facet<reserved_primary_index_space_iterator>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous iterator functions");

  reserved_primary_index_space_iterator litr(lid_spaces, lspace_id);
  litr.put_is_active_only(false);
  cout << "put_is_active_only(false)" << endl;

  cout << "offset()             = " << litr.offset() << endl;
  cout << "put_is_active_only() = " << litr.is_active_only() << endl;

  // Postconditions:

  // Exit:

  return 0;
}

  
