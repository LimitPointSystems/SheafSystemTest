


//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example array_index_space_interval.t.cc
/// Test driver for array id space intervals.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "array_index_space_interval.h"
#include "array_implicit_index_space_iterator.h"
#include "namespace_poset.h"
#include "std_iostream.h"
#include "std_strstream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  namespace_poset::initialize_id_space_prototypes();

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(6);

  string lname("test_array_id_space_interval");

  block<pod_index_type> lids;
  lids.push_back(2);
  lids.push_back(3);
  lids.push_back(4);
  lids.push_back(5);

  pod_index_type lspace_id =
    make_id_space_interval(lid_spaces,
			   "array_index_space_interval",
			   array_index_space_interval::make_arg_list(lids, 2, true),
			   2);

  // Give the id space a name.

  strstream lspace_name;
  lspace_name << "implicit_" << lspace_id;

  lid_spaces.put_name(lspace_id, lspace_name.str());

  // Test iterator facet.

  test_iterator_facet<array_implicit_index_space_iterator>(lid_spaces, lspace_id);

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 0, 2);

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  array_implicit_index_space_iterator litr(lid_spaces, lspace_id);
  const array_index_space_interval& linterval =
    reinterpret_cast<const array_index_space_interval&>(litr.host());

  cout << "hub_ids()       = " << &linterval.hub_ids() << endl;
  cout << "ids_per_space() = " << linterval.ids_per_space() << endl;
  cout << "owns_hub_ids()  = " << linterval.owns_hub_ids() << endl;

  // Postconditions:

  // Exit:

  return 0;
}

  
