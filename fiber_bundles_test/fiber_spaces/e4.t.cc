

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example e4.t.cc
/// Test driver for class e4.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e4.h"
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

  test_persistent_vector_type<e4>(ns);

  test_volatile_type<e4>();

  test_vector_conversions<e4>(ns);

  // Test vd facet:

  test_vector_vd_facet<e4>(ns);

  // Test ed facet:

  test_ed_facet<e4>(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
