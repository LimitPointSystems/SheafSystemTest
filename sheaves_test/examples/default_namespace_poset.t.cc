
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

/// @example examples/default_namespace_poset.t.cc
/// Test driver for class namespace_poset

#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/storage_agent.h"

using namespace std;
using namespace sheaf;

int main()
{
  int result = 0;

  // Make the default namespace

  namespace_poset ns("default_namespace_poset");

  // Output a text version to stdout

  cout << ns << endl;

  // Write it to a file;
  // need read-write access in order to write it
  // and to delete it in the destructor.

  ns.get_read_write_access();

  storage_agent sa("default_namespace_poset.t.hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(128);
  sa.put_dof_tuple_record_buffer_ub(8);
  sa.write_entire(ns);

  return result;
}


