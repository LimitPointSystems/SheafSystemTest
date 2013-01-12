
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/sheaves_namespace.t.cc
/// Test driver for class sheaves_namespace

#include "sheaves_namespace.h"
#include "assert_contract.h"
#include "storage_agent.h"

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
