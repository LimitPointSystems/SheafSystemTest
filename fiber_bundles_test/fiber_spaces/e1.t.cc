

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example e1.t.cc
/// Test driver for class e1.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e1.h"
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

  test_persistent_vector_type<e1>(ns);

  test_volatile_type<e1>();

  test_vector_conversions<e1>(ns);

  // Test vd facet:

  test_vector_vd_facet<e1>(ns);

  // Test atp facet:

  test_vector_atp_facet<e1>(ns);

  // Test ed facet:

  test_ed_facet<e1>(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:


  return 0;
}
