
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

/// @example interval_index_space.t.cc
/// Test driver for interval id spaces.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/interval_index_space_handle.h"
#include "SheafSystem/interval_index_space_iterator.h"
#include "SheafSystem/interval_index_space_state.h"
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

  string lname("test_interval_id_space");

  interval_index_space_handle lhandle =
    interval_index_space_handle::new_space(lid_spaces, lname, false, true);

  pod_index_type lspace_id = lhandle.index();

  push_back(lhandle, 0);
  push_back(lhandle, 2);
  push_back(lhandle, 4);

  // Test handle facet.

  test_handle_facet<interval_index_space_handle>(lid_spaces, lspace_id);

  // Test iterator facet.

  test_iterator_facet<interval_index_space_iterator>(lid_spaces, lspace_id);

  // Test state facet.

  test_state_facet(lid_spaces, lspace_id, 1, 2);

  // Test the gathered_insertion facet.

  test_gathered_insertion_facet(lid_spaces, lspace_id);

  // Test the mutable facet.

  test_scattered_insertion_facet(lid_spaces, lspace_id);

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

  
