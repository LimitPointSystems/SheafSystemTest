
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

/// @example test_posets/sheaves_namespace.t.cc
/// Test driver for class sheaves_namespace

#include "SheafSystem/sheaves_namespace.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/subposet_member_iterator.h"

using namespace std;
using namespace sheaf;

///
/// Test the constructor that takes a name.
///
void test_named_ctor(const string& xfilename)
{
  // Preconditions:


  // Body:

  // Construct an unattached namespace handle with the default constructor.

  sheaves_namespace* lns = new sheaves_namespace("test_named_ctor");

  // Output a text version to stdout

  cout << *lns << endl;

  // Write it to a file;
  // need read-write access in order to write it
  // and to delete it.

  lns->get_read_write_access();
  storage_agent sa(xfilename + ".hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(*lns);

  // Delete it.

  delete lns;

  // Postconditions:


  // Exit:

  return;
}

///
/// The main routine for this test driver.
///
int main(int xargc, char *xargv[])
{
  int result = 0;

   string filename = filename_from_cmdline(*xargv);

  test_named_ctor(filename);

  return result;
}


