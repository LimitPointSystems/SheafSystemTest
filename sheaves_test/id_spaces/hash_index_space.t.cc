
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

/// @example hash_index_space.t.cc
/// Test driver for hash id spaces.

#include "assert_contract.h"
#include "error_message.h"
#include "index_space_family.h"
#include "hash_index_space_handle.h"
#include "hash_index_space_iterator.h"
#include "hash_index_space_state.h"
#include "namespace_poset.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  namespace_poset::initialize_id_space_prototypes();

  test_index_space_family lid_spaces;
  lid_spaces.new_primary_space(6);

  string lname("test_hash_id_space");

  mutable_index_space_handle lhandle =
    hash_index_space_handle::new_space(lid_spaces, lname, false, 3);

  pod_index_type lspace_id = lhandle.index();

  push_back(lhandle, 0);
  push_back(lhandle, 2);
  push_back(lhandle, 4);

  // Test iterator facet.

  test_iterator_facet<hash_index_space_iterator>(lid_spaces, lspace_id);

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 1, 2);

  // Test the mutable facet.

  test_mutable_facet(lid_spaces, lspace_id);

  // Postconditions:

  // Exit:

  return 0;
}

  
