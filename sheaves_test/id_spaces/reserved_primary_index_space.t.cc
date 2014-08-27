
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

/// @example reserved_primary_index_space.t.cc
/// Test driver for reserved_primary id spaces.

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "arg_list.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "reserved_primary_index_space_handle.h"
#include "reserved_primary_index_space_iterator.h"
#include "reserved_primary_index_space_state.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace std;
using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  namespace_poset::initialize_id_space_prototypes();

  index_space_family lid_spaces;
  lid_spaces.new_id();
  lid_spaces.new_id();

  pod_index_type lspace_id = 1;

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 1, 1);

  // Test handle facet.

  test_handle_facet<reserved_primary_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  reserved_primary_index_space_handle lhandle(lid_spaces, lspace_id);

  cout << "new_id()      = " << lhandle.new_id() << endl;
  cout << "new_id(10)    = " << lhandle.new_hub_id(10) << endl;
  cout << "next_hub_id() = " << lhandle.next_hub_id() << endl;

  // Test iterator facet.

  test_iterator_facet<reserved_primary_index_space_iterator>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous iterator functions");

  reserved_primary_index_space_iterator litr(lid_spaces, lspace_id);
  litr.put_is_active_only(false);
  cout << "put_is_active_only(false)" << endl;

  cout << "offset()             = " << litr.offset() << endl;
  cout << "put_is_active_only() = " << litr.is_active_only() << endl;

  // Postconditions:

  // Exit:

  return 0;
}

  
