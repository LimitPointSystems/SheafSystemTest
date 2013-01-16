// $RCSfile$ $Revision$ $Date$

// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example offset_index_space.t.cc
/// Test driver for offset id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "offset_index_space_handle.h"
#include "offset_index_space_iterator.h"
#include "offset_index_space_state.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(6);

  string lname("test_offset_id_space");

  pod_index_type lspace_id =
    make_id_space(lid_spaces,
		  lname,
		  "offset_index_space_state",
		  offset_index_space_state::make_arg_list(2, 4)).index();

  // Test handle facet.

  test_handle_facet<offset_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  offset_index_space_handle lhandle(lid_spaces, lspace_id);
  cout << "offset() = " << lhandle.offset() << endl;

  // Test iterator facet.

  test_iterator_facet<offset_index_space_iterator>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous iterator functions");

  offset_index_space_iterator litr(lid_spaces, lspace_id);
  cout << "offset() = " << litr.offset() << endl;
  cout << "ct()     = " << litr.ct() << endl;

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 0, 2);

  // Postconditions:

  // Exit:

  return 0;
}

  
