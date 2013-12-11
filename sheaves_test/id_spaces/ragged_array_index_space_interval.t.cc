
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @example ragged_array_index_space_interval.t.cc
/// Test driver for ragged array id space intervals.

#include "assert_contract.h"
#include "error_message.h"
#include "index_space_family.h"
#include "namespace_poset.h"
#include "ragged_array_index_space_interval.h"
#include "ragged_array_implicit_index_space_iterator.h"
#include "std_iostream.h"
#include "std_strstream.h"
#include "test_index_spaces.impl.h"

using namespace std;
using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  namespace_poset::initialize_id_space_prototypes();

  test_index_space_family lid_spaces;
  lid_spaces.new_primary_space(6);

  string lname("test_ragged_array_id_space_interval");

  ragged_array<pod_index_type> lids;
  lids.push_back(2);
  lids.push_back(3);
  lids.push_back(4);
  lids.new_back_row();
  lids.push_back(5);

  pod_index_type lspace_id =
    ragged_array_index_space_interval::new_space(lid_spaces, 2, lids, true).begin();

  // Give the id space a name.

  strstream lspace_name;
  lspace_name << "implicit_" << lspace_id;

  lid_spaces.put_name(lspace_id, lspace_name.str());

  // Test iterator facet.

  test_iterator_facet<ragged_array_implicit_index_space_iterator>(lid_spaces, lspace_id);

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 0, 2);

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  ragged_array_implicit_index_space_iterator litr(lid_spaces, lspace_id);
  const ragged_array_index_space_interval& linterval =
    reinterpret_cast<const ragged_array_index_space_interval&>(litr.host());

  cout << "hub_ids()       = " << &linterval.hub_ids() << endl;
  cout << "owns_hub_ids()  = " << linterval.owns_hub_ids() << endl;

  // Postconditions:

  // Exit:

  return 0;
}

  
