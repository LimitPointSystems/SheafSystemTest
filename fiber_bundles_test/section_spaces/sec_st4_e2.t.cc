

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example sec_st4_e2.t.cc
/// Unit test for class sec_st4_e2.

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "sec_st4_e2.h"
#include "storage_agent.h"
#include "test_sections.impl.h"

using namespace fiber_bundle;

///
int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  string filename = filename_from_cmdline(*xargv);

  print_header("Testing " + filename);

  // Create the namespace.

  fiber_bundles_namespace ns(filename);

  ns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;

  const poset_path& lbase_path = make_test_base_space(ns, i_size, j_size);

  // Run tests.

  // Test assignment:

  test_assignment<sec_st4_e2>(ns, lbase_path);

  // Test vd facet:

  test_sec_vd_facet<sec_st4_e2>(ns, lbase_path);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");

  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}

