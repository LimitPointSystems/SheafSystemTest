
// $RCSfile: st2_e3.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:44 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example st2_e3.t.cc
/// Test driver for class st2_e3.

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e3.h"
#include "st2_e3.h"
#include "storage_agent.h"
#include "stp_space.h"
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

  test_persistent_tensor_type<st2_e3>(ns);

  test_volatile_type<st2_e3>();

  test_tensor_conversions<st2_e3>(ns);

  // Test vd facet:

  test_tensor_vd_facet<st2_e3>(ns);

  // Test tp facet:

  test_tensor<st2_e3, e3, t3_e3>(ns);

  // Test stp facet:

  test_stp_facet<st2_e3>(ns);

  // Test st2 facet:

  test_st2_facet<st2_e3>(ns);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:


  return 0;
}
