
// $RCSfile: at3_e3.t.cc,v $ $Revision: 1.9 $ $Date: 2012/03/01 00:40:42 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example at3_e3.t.cc
/// Test driver for class at3_e3.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "at3.h"
#include "at3_e3.h"
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

  test_persistent_tensor_type<at3_e3>(ns);

  test_volatile_type<at3_e3>();

  test_tensor_conversions<at3_e3>(ns);

  // Test vd facet:

  test_tensor_vd_facet<at3_e3>(ns);

  // Test atp facet:

  test_hook_product<at3_e3, e3, at2_e3>(ns);

  test_star_operator<at3_e3, at0>(ns);

  //@issue: What is the vector_space_type for at0?
  test_star_operator<at0, at3_e3>(ns);

  test_wedge_product<at2_e3, e3, at3_e3>(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
