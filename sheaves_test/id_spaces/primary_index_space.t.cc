
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

/// @example primary_index_space.t.cc
/// Test driver for primary id spaces.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/primary_index_space_handle.h"
#include "SheafSystem/primary_index_space_iterator.h"
#include "SheafSystem/primary_index_space_state.h"
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
  pod_index_type lspace_id = lid_spaces.new_primary_space(6);

  // Test handle facet.

  test_handle_facet<primary_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  primary_index_space_handle lhandle(lid_spaces, lspace_id);

  cout << "offset()      = " << lhandle.offset() << endl;
  cout << "extend(10)" << endl;
  lhandle.extend(10);
  cout << "hub_term_id() = " << lhandle.hub_term_id() << endl;

  // Test iterator facet.

  test_iterator_facet<primary_index_space_iterator>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous iterator functions");

  primary_index_space_iterator litr(lid_spaces, lspace_id);

  cout << "offset()             = " << litr.offset() << endl;
  cout << "ct()                 = " << litr.ct() << endl;

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 1, 1);

  // Postconditions:

  // Exit:

  return 0;
}

  
