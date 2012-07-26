// $RCSfile: default_namespace_poset.t.cc,v $ $Revision: 1.17 $ $Date: 2012/03/01 00:41:18 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example examples/default_namespace_poset.t.cc
/// Test driver for class namespace_poset

#include "namespace_poset.h"
#include "assert_contract.h"
#include "storage_agent.h"

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


