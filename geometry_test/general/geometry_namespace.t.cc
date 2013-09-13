
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

/// @example general/geometry_namespace.t.cc
/// Test driver for class geometry_namespace

#include "geometry_namespace.h"

#include "assert_contract.h"
#include "poset_path.h"
#include "storage_agent.h"

using namespace raw;


namespace
{
  
// Set the filenames in accordance with the OS type.

#ifdef _WIN32
  const string hdf_filename = "geometry_namespace.t.exe.hdf";
#else
  const string hdf_filename = "geometry_namespace.t.hdf";
#endif

}
  

///
/// Test construction and deletion on the heap.
///
void test_heap_construction()
{
  // Preconditions:


  // Body:

  // Construct a a namespace on the heap.

  geometry_namespace* lns = new geometry_namespace("test_heap_construction");

  // Output a text version to stdout

  cout << *lns << endl;

  // Delete it; requires write access.

  lns->get_read_write_access();
  delete lns;

  // Postconditions:

  // Exit:

  return;
}

///
/// Test construction and deletion on the stack.
///
void test_stack_construction()
{
  // Preconditions:


  // Body:

  // Construct a namespace on the stack.

  geometry_namespace lns("test_stack_construction");

  // Output a text version to stdout

  cout << lns << endl;

  // Namespace will be deleted when it goes out of scope;
  // requires write access.

  lns.get_read_write_access();

  // Postconditions:


  // Exit:

  return;
}

///
/// Test output to file.
///
void test_file_output(const string& xhdf_filename)
{
  // Preconditions:

  // Body:

  // Construct a namespace.

  geometry_namespace lns("test_file_output");

  // Write it to a file;
  // need read-write access in order to write it
  // and to delete it.

  lns.get_read_write_access();
  storage_agent sa(xhdf_filename, sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(lns);

  // Namespace will be deleted when it goes out of scope;
  // requires write access but already have it.

  // Postconditions:


  // Exit:

  return;
}

///
/// The main routine for this test driver.
///
int main()
{
  int result = 0;

  test_heap_construction();
  test_stack_construction();
  test_file_output(hdf_filename);

  return result;
}


