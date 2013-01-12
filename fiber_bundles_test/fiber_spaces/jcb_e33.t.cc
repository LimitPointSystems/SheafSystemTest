

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example jcb_e33.t.cc
/// Test driver for class jcb_e33.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e3.h"
#include "jcb_e33.h"
#include "jcb_space.h"
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

  test_persistent_jacobian_type<jcb_e33>(ns);

  test_volatile_type<jcb_e33>();

  test_jacobian_conversions<jcb_e33>(ns);

  // Test vd facet:

  test_jacobian_vd_facet<jcb_e33>(ns);

  // Test jcb facet:

  test_jcb_facet<jcb_e33>(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:


  return 0;
}
