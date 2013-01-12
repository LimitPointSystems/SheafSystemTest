

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example at2_e3.t.cc
/// Test driver for class at2_e3.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "at2.h"
#include "at2_e3.h"
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

  test_persistent_tensor_type<at2_e3>(ns);

  test_volatile_type<at2_e3>();

  test_tensor_conversions<at2_e3>(ns);

  // Test vd facet:

  test_tensor_vd_facet<at2_e3>(ns);

  // Test tp facet:

  test_tensor<at2_e3, e3, t3_e3>(ns);

  // Test atp facet:

  test_tensor_atp_facet<at2_e3>(ns);

#ifndef _WIN32

  test_hook_product<at2_e3, e3, e3>(ns);

  test_star_operator<at2_e3, e3>(ns);
  test_star_operator<e3, at2_e3>(ns);

  test_wedge_product<e3, e3, at2_e3>(ns);

#endif

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf" + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
