

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example t4_e3.t.cc
/// Test driver for class t4_e3.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e3.h"
#include "storage_agent.h"
#include "t4_e3.h"
#include "test_fibers.impl.h"

using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  string filename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace ns(filename);
  ns.get_read_write_access();

  // Run tests.

  test_persistent_tensor_type<t4_e3>(ns);

  test_volatile_type<t4_e3>();

  test_tensor_conversions<t4_e3>(ns);

  // Test vd facet:

  test_tensor_vd_facet<t4_e3>(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
