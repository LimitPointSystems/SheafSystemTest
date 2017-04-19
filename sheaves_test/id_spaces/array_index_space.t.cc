
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

/// @example array_index_space.t.cc
/// Test driver for array id spaces.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/array_index_space_handle.h"
#include "SheafSystem/array_index_space_iterator.h"
#include "SheafSystem/array_index_space_state.h"
#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystemTest/test_index_spaces.impl.h"

using namespace std;
using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  namespace_poset::initialize_id_space_prototypes();

  test_index_space_family lid_spaces;
  lid_spaces.new_primary_space(6);

  string lname("test_array_id_space");

  array_index_space_handle lid_space =
    array_index_space_handle::new_space(lid_spaces, lname, false, 3);

  push_back(lid_space, 0);
  push_back(lid_space, 2);
  push_back(lid_space, 4);

  // Test iterator facet.

  test_iterator_facet<array_index_space_iterator>(lid_spaces, lid_space.index());

  // Test state facet.

  test_state_facet(lid_spaces, lid_space.index(), 1, 2);

  // Test the gathered_insertion facet.

  test_gathered_insertion_facet(lid_spaces, lid_space.index());

  // Test the mutable facet.

  test_scattered_insertion_facet(lid_space);

  // Postconditions:

  // Exit:

  return 0;
}

  
