
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

/// @example posets/member_multiple_names.t.cc
/// Test driver for multiple names for posets.

#include "arg_list.h"
#include "poset_member.h"
#include "postorder_iterator.h"
#include "preorder_iterator.h"
#include "sheaves_namespace.h"
#include "std_iostream.h"
#include "std_string.h"
#include "storage_agent.h"
#include "subposet.h"
#include "subposet_member_iterator.h"



using namespace sheaf;

///
/// The main routine for this test driver.
///
int main(int xargc, char *xargv[])
{

  string filename = filename_from_cmdline(*xargv);

  block<string> mbr_names;

  sheaves_namespace test_namespace("test_namespace");
  test_namespace.get_read_write_access();

  poset& test_poset =
    poset::new_table(test_namespace,
		     "member_multiple_names_test",
		     test_namespace.primitives().schema(true).path(true),
		     false);

  test_poset.get_read_write_access();

  // Make a poset_member with multiple names.

  poset_member mbr0(&test_poset);
  mbr0.put_name("alpha", false, false);
  mbr0.put_name("beta", false, false);
  mbr0.put_name("gamma", false, false);


  cout << endl;
  cout << "mbr0 names are: " << endl;
  cout << "--------------- " << endl;

  mbr0.all_names(mbr_names);

  for(int i = 0; i < mbr_names.ct(); i++)
  {
    cout << " " <<  mbr_names[i] << endl;
  }
  cout << endl;

  cout << "Deleting mbr0 name gamma: " << endl;

  mbr0.delete_name("gamma");

  cout << endl;
  cout << "mbr0 names are: " << endl;
  cout << "--------------- " << endl;

  mbr0.all_names(mbr_names);

  for(int i = 0; i < mbr_names.ct(); i++)
  {
    cout << " " <<  mbr_names[i] << endl;
  }

  cout << endl;
  cout << "Deleting all mbr0 names : " << endl;

  mbr0.delete_all_names();

  cout << endl;
  cout << "mbr0 names are: " << endl;
  cout << "--------------- " << endl;

  mbr0.all_names(mbr_names);

  for(int i = 0; i < mbr_names.ct(); i++)
  {
    cout << " " <<  mbr_names[i] << endl;
  }

  cout << endl;
  cout << "Restoring mbr0 names before write: " << endl;

  mbr0.put_name("alpha", false, false);
  mbr0.put_name("beta", false, false);
  mbr0.put_name("gamma", false, false);

  cout << endl;
  cout << "mbr0 names are: " << endl;
  cout << "--------------- " << endl;

  mbr0.all_names(mbr_names);

  for(int i = 0; i < mbr_names.ct(); i++)
  {
    cout << " " <<  mbr_names[i] << endl;
  }

  // Make a poset_member with exactly one name.

  poset_member mbr1(&test_poset);
  mbr1.put_name("delta", true, false);

  // Make a poset_member with no name.

  poset_member mbr2(&test_poset);

  // Detach so destructor won't complain about needing write access.

  mbr0.detach_from_state();
  mbr1.detach_from_state();
  mbr2.detach_from_state();

  test_poset.release_access();

  cout << endl << "Writing " << filename + ".hdf" << endl << endl;

  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(64);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(test_namespace);

  // Read the file back in and get the multiple member names from it.

  // Make the default namespace

  namespace_poset ns("test");

  cout << endl << "Reading " << filename + ".hdf" << endl << endl;

  // We need write access in order to read the file.

  ns.get_read_write_access();
  storage_agent rsa(filename + ".hdf", sheaf_file::READ_ONLY, false);
  rsa.put_member_record_buffer_ub(15);
  rsa.read_entire(ns);

  ///@hack Obtained the indices 3, 4, and 5 by dumping *psh to stdout.

  poset_state_handle& psh = ns.member_poset("member_multiple_names_test");

  psh.get_read_write_access();

  // Print the poset name to stdout

  cout << "poset name is: " << psh.name() << endl;
  cout << endl;

  // Print the names for mbr0 to stdout

  psh.all_member_names(2, mbr_names);

  cout << "For index 2, member name(s) are: " << " ";

  for(int i = 0; i < mbr_names.ct(); i++)
  {
    cout << " " <<  mbr_names[i];
  }

  cout << endl;
  cout << "Should be: alpha beta gamma" << endl;
  cout << endl;

  // Print the names for mbr1 to stdout.

  psh.all_member_names(3, mbr_names);

  cout << "For index 3, member name(s) are:" << " ";

  for(int i = 0; i < mbr_names.ct(); i++)
  {
    cout << " " <<  mbr_names[i];
  }

  cout << endl;
  cout << "Should be: delta" << endl;
  cout << endl;

  // Print the names for mbr2 to stdout

  psh.all_member_names(4, mbr_names);

  cout << "For index 4, member name(s) are:" << " ";

  for(int i = 0; i < mbr_names.ct(); i++)
  {
    cout << " " <<  mbr_names[i];
  }

  cout << endl;
  cout << "Should be empty (null)." << endl;
  cout << endl;

  //  cout << *psh << endl;

  return 0;

}

