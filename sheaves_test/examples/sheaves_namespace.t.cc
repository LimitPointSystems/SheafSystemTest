
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

/// @example examples/sheaves_namespace.t.cc
/// Test driver for class sheaves_namespace

#include "SheafSystem/sheaves_namespace.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/storage_agent.h"

using namespace std;
using namespace sheaf;

int main()
{
  int result = 0;

  // Make the sheaves namespace

  sheaves_namespace the_namespace("sheaves_namespace");

  // Output a text version to stdout

  cout << the_namespace << endl;

  // Need read-write access to write namespace to a file
  // and to delete it in the destructor.

  the_namespace.get_read_write_access();

  // Write it to a file

  storage_agent sa("sheaves_namespace.t.hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(the_namespace);

  // Output a text version to stdout again.

  cout << the_namespace << endl;

  return result;
}
