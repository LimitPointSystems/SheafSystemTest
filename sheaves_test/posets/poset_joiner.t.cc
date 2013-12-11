
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
/// @example posets/poset_joiner.t.cc
/// Test dirver for poset_joiner.  Only the subposet interface.

#include "sheaves_namespace.h"
#include "subposet.h"
#include "poset_joiner.h"
#include "subposet_member_iterator.h"
#include "std_iostream.h"
#include "tern.h"
#include "total_poset_member.h"

using namespace std;
using namespace sheaf;

///
/// The main routine of this test driver.
///
int main()
{
  sheaves_namespace* test_namespace = new sheaves_namespace("poset_joiner.t");

  // Make the standard triangle poset.

  test_namespace->make_triangle(test_namespace);

  test_namespace->get_read_access();

  // Use standard triangle in sheaves_namespace as the test case.
  // Member indexing and Correct order of iterations can be
  // deduced by inspection of output from sheaves_namespace.t.cc

  total_poset_member triangle(test_namespace, "cells/standard triangle");

  // Create some subposets to use as filters.

  triangle.get_read_write_access();

  // Just the 0-cells

  subposet lsp0(triangle.host());
  lsp0.put_name("0-cells", true, false);
  lsp0.insert_member(6);
  lsp0.insert_member(7);
  lsp0.insert_member(8);

  //  cout << lsp0 << endl;


  // Just the 1-cells

  subposet lsp1(triangle.host());
  lsp1.put_name("1-cells", true, false);
  lsp1.insert_member(3);
  lsp1.insert_member(4);
  lsp1.insert_member(5);

  //  cout << lsp1 << endl;

  // A single cell

  subposet lsp_single(triangle.host());
  lsp_single.put_name("single-cell", true, false);
  lsp_single.insert_member(8);

  //  cout << lsp_single << endl;

  // Both the 0-cells and 1-cells

  subposet lsp01(triangle.host());
  lsp01.put_name("0- and 1-cells", true, false);
  lsp0.p_union_pa(&lsp1, &lsp01);

  //  cout << lsp01 << endl;


  cout << "##### Begin 0-cells POSET_JOINER test ##########" << endl;

  poset_joiner sp_joiner(triangle.host());
  total_poset_member all_0cells;
  sp_joiner.join(&lsp0, tern::TRUE, all_0cells);
  all_0cells.put_name("all_0_cells", true, false);  
  cout << *triangle.host() << endl;

  cout << "##### End   0-cells POSET_JOINER test ##########" << endl << endl;

  cout << "##### Begin 1-cells POSET_JOINER test ##########" << endl;

  //  poset_joiner sp_joiner1(triangle.host());
  total_poset_member all_1cells;
  sp_joiner.join(&lsp1, tern::TRUE, all_1cells);
  all_1cells.put_name("all_1_cells", true, false);
  cout << *triangle.host() << endl;

  cout << "##### End   1-cells POSET_JOINER test ##########" << endl << endl;

  cout << "##### Begin single member POSET_JOINER test ##########" << endl;

  //  poset_joiner sp_joiner2(triangle.host());
  total_poset_member single_member;
  sp_joiner.join(&lsp_single, tern::TRUE, single_member);
  single_member.put_name("single_member", true, false);
  cout << *triangle.host() << endl;

  cout << "##### End   single member POSET_JOINER test ##########" << endl << endl;


  // Detach so destructor won't complain about needing write access.

  all_0cells.detach_from_state();
  lsp0.detach_from_state();
  lsp1.detach_from_state();
  lsp01.detach_from_state();
  triangle.detach_from_state();

  return 0;
}
