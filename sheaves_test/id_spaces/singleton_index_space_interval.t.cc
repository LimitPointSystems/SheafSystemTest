


//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example singleton_index_space_interval.t.cc
/// Test driver for singleton id space intervals.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "singleton_index_space_interval.h"
#include "singleton_implicit_index_space_iterator.h"
#include "std_iostream.h"
#include "std_strstream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(6);

  string lname("test_singleton_id_space_interval");

  pod_index_type lspace_id =
    make_id_space_interval(lid_spaces,
			   "singleton_index_space_interval",
			   singleton_index_space_interval::make_arg_list(2),
			   2);

  // Give the id space a name.

  strstream lspace_name;
  lspace_name << "implicit_" << lspace_id;

  lid_spaces.put_name(lspace_id, lspace_name.str());

  // Test iterator facet.

  test_iterator_facet<singleton_implicit_index_space_iterator>(lid_spaces, lspace_id);

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 0, 2);

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  singleton_implicit_index_space_iterator litr(lid_spaces, lspace_id);
  const singleton_index_space_interval& linterval =
    reinterpret_cast<const singleton_index_space_interval&>(litr.host());

  cout << "hub_offset() = " << linterval.hub_offset() << endl;

  // Postconditions:

  // Exit:

  return 0;
}

  
