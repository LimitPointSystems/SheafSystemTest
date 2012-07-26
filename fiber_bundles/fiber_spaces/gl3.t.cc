
// $RCSfile: gl3.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:43 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example gl3.t.cc
/// Test driver for class gl3.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "gl3.h"
#include "gln_space.h"
#include "fiber_bundles_namespace.h"
#include "storage_agent.h"
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

  test_persistent_group_type<gl3>(ns);

  test_volatile_type<gl3>();

  test_group_conversions<gl3>(ns);

  // Test group facet:

  test_group_facet<gl3>(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
