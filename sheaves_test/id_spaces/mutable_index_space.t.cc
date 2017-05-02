
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

/// @example mutable_index_space.t.cc
/// Test driver for mutable id spaces.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/hash_index_space_handle.h"
#include "SheafSystem/hash_index_space_iterator.h"
#include "SheafSystem/hash_index_space_state.h"
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

  string lname("test_mutable_id_space");

  scattered_insertion_index_space_handle lhandle =
    hash_index_space_handle::new_space(lid_spaces, lname, false, 3);

  pod_index_type lspace_id = lhandle.index();

  push_back(lhandle, 0);
  push_back(lhandle, 2);
  push_back(lhandle, 4);

  // Test handle facet.

  test_handle_facet<scattered_insertion_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  // Postconditions:

  // Exit:

  return 0;
}

  
