// $RCSfile$ $Revision$ $Date$

// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example interval_index_space.t.cc
/// Test driver for interval id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "interval_index_space_handle.h"
#include "interval_index_space_iterator.h"
#include "interval_index_space_state.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(6);

  string lname("test_interval_id_space");

  pod_index_type lspace_id =
    make_id_space(lid_spaces,
		  lname,
		  "interval_index_space_state",
		  interval_index_space_state::make_arg_list(3)).index();

  interval_index_space_handle lhandle(lid_spaces, lspace_id);
  push_back(lhandle, 0);
  push_back(lhandle, 2);
  push_back(lhandle, 4);

  // Test handle facet.

  test_handle_facet<interval_index_space_handle>(lid_spaces, lspace_id);

  // Test iterator facet.

  test_iterator_facet<interval_index_space_iterator>(lid_spaces, lspace_id);

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 1, 2);

  // Test the mutable facet.

  test_mutable_facet(lid_spaces, lspace_id);

  // Test interval facet.

  print_out_header("Testing Interval Facet");

  scoped_index lbegin(lid_spaces.hub_id_space(), 0);
  scoped_index lend(lid_spaces.hub_id_space(), 3);

  cout << "insert_interval(2, 5, 0, 3)" << endl;
  lhandle.insert_interval(2, 5, lbegin, lend);

  cout << "push_interval(4, 5)" << endl;
  lbegin = 4;
  lend = 5;
  lhandle.push_interval(lbegin, lend);

  cout << "remove_hub_interval(1, 2)" << endl;
  lbegin = 1;
  lend = 2;
  lhandle.remove_interval(lbegin, lend);

  cout << "remove_interval(4, 4)" << endl;
  lhandle.remove_interval(4, 4);

  lbegin = 0;
  cout << "interval_begin(0) = " << lhandle.interval_begin(lbegin) << endl;
  cout << "interval_end(0)   = " << lhandle.interval_end(lbegin) << endl;

  cout << "merge_mode()      = " << lhandle.merge_mode() << endl;
  cout << "put_merge_mode(false)" << endl;
  lhandle.put_merge_mode(false);

  cout << "print_map_rep(cout)" << endl;
  lhandle.print_map_rep(cout);

  interval_index_space_iterator litr(lid_spaces, lspace_id);
  cout << "next_interval()" << endl;
  litr.next_interval();
  cout << "interval_begin() = " << litr.interval_begin() << endl;
  cout << "interval_end()   = " << litr.interval_end() << endl;
  

  // Postconditions:

  // Exit:

  return 0;
}

  
