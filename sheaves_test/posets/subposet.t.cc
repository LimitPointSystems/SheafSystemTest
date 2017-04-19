
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

/// @example posets/subposet.t.cc
/// Test driver for class subposet


#include "SheafSystem/poset_member.h"
#include "SheafSystem/postorder_iterator.h"
#include "SheafSystem/preorder_iterator.h"
#include "SheafSystem/sheaves_namespace.h"
#include "SheafSystem/subposet.h"
#include "SheafSystem/subposet_member_iterator.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/storage_agent.h"


using namespace std;
using namespace sheaf;

void max_min_test()
{
  sheaves_namespace* test_namespace;

  test_namespace = new sheaves_namespace("test_namespace");

  test_namespace->make_triangle(test_namespace);

  test_namespace->get_read_access();

  // Use standard triangle in sheaves_namespace as the test case.
  // Member indexing and Correct order of iterations can be
  // deduced by inspection of output from sheaves_namespace.t.cc

  poset_member triangle(test_namespace, "cells/standard triangle");

  // Create some subposets to use as tests.

  triangle.get_read_write_access();

  // Just the 0-cells

  subposet lsp0(triangle.host());

  lsp0.put_name("0-cells", true, false);
  lsp0.insert_member(6);
  lsp0.insert_member(7);
  lsp0.insert_member(8);

  // Just the 1-cells

  subposet lsp1(triangle.host());
  lsp1.put_name("1-cells", true, false);
  lsp1.insert_member(3);
  lsp1.insert_member(4);
  lsp1.insert_member(5);

  // Both the 0-cells and 1-cells

  
  subposet lsp01(triangle.host());
  lsp01.put_name("0- and 1-cells", true, false);
  lsp0.p_union_pa(&lsp1, &lsp01);


  lsp0.detach_from_state();
  lsp1.detach_from_state();


  cout << endl << "##### begin SUBPOSET::minimals test #####" << endl;

  subposet* lmins = lsp01.minimals();

  subposet_member_iterator* lmins_itr = lmins->member_iterator();

  while(!lmins_itr->is_done())
  {
    cout << " " << lmins_itr->index();
    lmins_itr->next();
  }
  cout << endl;

  cout << "should be:" << endl;
  cout << " 6 7 8" << endl;

  cout << "##### end   SUBPOSET::minimals test #####" << endl << endl;

  cout << endl << "##### begin SUBPOSET::maximals test #####" << endl;

  subposet* lmaxs = lsp01.maximals();

  subposet_member_iterator* lmaxs_itr = lmaxs->member_iterator();

  while(!lmaxs_itr->is_done())
  {
    cout << " " << lmaxs_itr->index();
    lmaxs_itr->next();
  }
  cout << endl;

  cout << "should be:" << endl;
  cout << " 3 4 5" << endl;

  cout << "##### end   SUBPOSET::maximals test #####" << endl << endl;

  // Detach so destructor won't complain about needing write access.

  lsp01.detach_from_state();
  triangle.detach_from_state();

  test_namespace->get_read_write_access(true);
  delete test_namespace;

}

void multiple_names_test(string xfilename)
{

  cout << "filename is: " << xfilename << endl;
  sheaves_namespace* multiple_name_ns = new sheaves_namespace("multiple_name_ns");

  // Make the standard triangle poset.

  multiple_name_ns->make_triangle(multiple_name_ns);

  multiple_name_ns->get_read_access();

  // Use standard triangle in sheaves_namespace as the test case.
  // Member indexing and Correct order of iterations can be
  // deduced by inspection of output from sheaves_namespace.t.cc.

  poset_member triangle(multiple_name_ns, "cells/standard triangle");

  // Create some subposets to use as tests.

  triangle.get_read_write_access();

  // A subposet with multiple names.

  subposet lsp0(triangle.host());

  // Give it a few names

  lsp0.put_name("alpha", false, false);
  lsp0.put_name("beta", false, false);
  lsp0.put_name("gamma", false, false);


  // Ask the resident subposet for it's names.

  block<string> names;

  cout << endl;
  cout << "lsp0 names are: " << endl;
  cout << "--------------- " << endl;

  lsp0.all_names(names);

  for(int i = 0; i < names.ct(); i++)
  {
    cout << " " <<  names[i] << endl;
  }
  cout << endl;

  cout << "Deleting lsp0 name gamma: " << endl;

  lsp0.delete_name("gamma");

  cout << endl;
  cout << "lsp0 names are: " << endl;
  cout << "--------------- " << endl;

  lsp0.all_names(names);

  for(int i = 0; i < names.ct(); i++)
  {
    cout << " " <<  names[i] << endl;
  }

  cout << endl;
  cout << "Deleting all lsp0 names : " << endl;

  lsp0.delete_all_names();

  cout << endl;
  cout << "lsp0 names are: " << endl;
  cout << "--------------- " << endl;

  lsp0.all_names(names);

  for(int i = 0; i < names.ct(); i++)
  {
    cout << " " <<  names[i] << endl;
  }

  cout << endl;
  cout << "Restoring lsp0 names before write: " << endl;

  lsp0.put_name("alpha", false, false);
  lsp0.put_name("beta", false, false);
  lsp0.put_name("gamma", false, false);

  cout << endl;
  cout << "lsp0 names are: " << endl;
  cout << "--------------- " << endl;

  lsp0.all_names(names);

  for(int i = 0; i < names.ct(); i++)
  {
    cout << " " <<  names[i] << endl;
  }

  // A subposet with exactly one name.

  subposet lsp1(triangle.host());

  // Name it.

  lsp1.put_name("delta", true, false);

  // A subposet with no name

  subposet lsp2(triangle.host());

  // Detach so destructor won't complain about needing write access.

  lsp0.detach_from_state();
  lsp1.detach_from_state();
  lsp2.detach_from_state();
  triangle.detach_from_state();

  multiple_name_ns->release_access();

  // Write the namespace out to disk.

  cout << endl << "Writing " << xfilename + ".hdf" << endl << endl;

  cout << *multiple_name_ns << endl;

  multiple_name_ns->get_read_write_access();
  storage_agent sa(xfilename + ".hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(64);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(*multiple_name_ns);

  // Read the file back in and get the multiple subposet names from it.

  // Make the default namespace

  namespace_poset ns("test");

  // Read the namespace from the file;
  // need write access in order to read it.

  cout << endl << "Reading " << xfilename + ".hdf" << endl << endl;

  ns.get_read_write_access();
  storage_agent rsa(xfilename + ".hdf", sheaf_file::READ_ONLY, false);
  rsa.put_member_record_buffer_ub(15);
  rsa.read_entire(ns);


  // cout << "After reading:" << endl << ns << endl;
  
  poset_state_handle& psh = ns.member_poset(6);

  psh.get_read_write_access();

  // Print the poset name to stdout.

  cout << "poset name is: " << psh.name() << endl;
  cout << endl;

  // Print the names for member 3 to stdout

  subposet sp0(&psh, 3);
  sp0.all_names(names);

  cout << "For index 3, subposet name(s) are: " << " ";

  for(int i = 0; i < names.ct(); i++)
  {
    cout << " " <<  names[i];
  }

  cout << endl;
  cout << "Should be: alpha beta gamma" << endl;
  cout << endl;

  // Print the names for member 4 to stdout

  subposet sp1(&psh, 4);

  sp1.all_names(names);

  cout << "For index 4, subposet name(s) are:" << " ";

  for(int i = 0; i < names.ct(); i++)
  {
    cout << " " <<  names[i];
  }

  cout << endl;
  cout << "Should be: delta" << endl;
  cout << endl;

  // Print the names for member 5 to stdout.

  subposet sp2(&psh, 5);

  sp2.all_names(names);

  cout << "For index 5, subposet name(s) are:" << " ";

  for(int i = 0; i < names.ct(); i++)
  {
    cout << " " <<  names[i];
  }

  cout << endl;
  cout << "Should be empty (null)." << endl;
  cout << endl;

  sp0.detach_from_state();
  sp1.detach_from_state();
  sp2.detach_from_state();

  multiple_name_ns->get_read_write_access();
  delete multiple_name_ns;

  return;
}

int main(int xargc, char *xargv[])
{

  max_min_test();
  multiple_names_test(filename_from_cmdline(*xargv));

  return 0;
}
