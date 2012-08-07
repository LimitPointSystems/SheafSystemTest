
// $RCSfile: at0.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example at0.t.cc
/// Test driver for class at0.

#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
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

  //@issue: What is the vector_space_type for at0?

  test_persistent_scalar_type<at0>(ns);

  test_volatile_type<at0>();

  test_scalar_conversions<at0>(ns);

  // Test vd facet:

  test_scalar_vd_facet<at0>(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf" + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
