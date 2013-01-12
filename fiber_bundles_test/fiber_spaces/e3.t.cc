

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example e3.t.cc
/// Test driver for class e3.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e3.h"
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

  test_persistent_vector_type<e3>(ns);

  test_volatile_type<e3>();

  test_vector_conversions<e3>(ns);

  // Test vd facet:

  test_vector_vd_facet<e3>(ns);

  // Test atp facet:

#ifndef _WIN32
  test_hook_product<e3, e3, at0>(ns);
  test_hook_product<at2_e3, e3, e3>(ns);

  test_wedge_product<e3, e3, at2_e3>(ns);
  test_wedge_product<at2_e3, e3, at3_e3>(ns);
#endif

  // Test ed facet:

  test_ed_facet<e3>(ns);

  // Test e3 facet:

  test_e3_facet(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
