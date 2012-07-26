// $RCSfile: namespace_poset.t.cc,v $ $Revision: 1.11 $ $Date: 2012/03/01 00:41:29 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example posets/namespace_poset.t.cc
/// Test driver for class namespace_poset

#include "namespace_poset.h"
#include "assert_contract.h"
#include "std_string.h"
#include "storage_agent.h"
#include "subposet_member_iterator.h"


using namespace sheaf;

///
/// Test construction and deletion on the heap.
///
void test_heap_construction()
{
  // Preconditions:


  // Body:

  // Construct a a namespace on the heap.

  namespace_poset* lns = new namespace_poset("test_heap_construction");

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

  namespace_poset lns("test_stack_construction");

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
void test_file_output(const string& xfilename)
{
  // Preconditions:

  // Body:

  // Construct a namespace.

  namespace_poset lns("test_file_output");

  // Write it to a file;
  // need read-write access in order to write it
  // and to delete it.

  lns.get_read_write_access();
  storage_agent sa(xfilename + ".hdf", sheaf_file::READ_WRITE);
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
int main(int xargc, char *xargv[])
{
  int result = 0;

  test_heap_construction();
  test_stack_construction();
  test_file_output(filename_from_cmdline(*xargv));

  return result;
}


