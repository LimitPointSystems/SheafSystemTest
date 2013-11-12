
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

/// @example constant_index_space_interval.t.cc
/// Test driver for constant id space intervals.

#include "assert_contract.h"
#include "error_message.h"
#include "index_space_family.h"
#include "constant_index_space_interval.h"
#include "constant_implicit_index_space_iterator.h"
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

  test_index_space_family lid_spaces;
  lid_spaces.new_primary_space(6);

  string lname("test_constant_id_space_interval");

  pod_index_type lspace_id =
    constant_index_space_interval::new_space(lid_spaces, 2, 2).begin();

  // Give the id space a name.

  strstream lspace_name;
  lspace_name << "implicit_" << lspace_id;

  lid_spaces.put_name(lspace_id, lspace_name.str());

  // Test iterator facet.

  test_iterator_facet<constant_implicit_index_space_iterator>(lid_spaces, lspace_id);

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 0, 2);

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  constant_implicit_index_space_iterator litr(lid_spaces, lspace_id);
  const constant_index_space_interval& linterval =
    reinterpret_cast<const constant_index_space_interval&>(litr.host());

  cout << "hub_id() = " << linterval.hub_id() << endl;

  // Postconditions:

  // Exit:

  return 0;
}

  
