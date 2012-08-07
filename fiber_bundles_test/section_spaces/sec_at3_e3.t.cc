
// $RCSfile: sec_at3_e3.t.cc,v $ $Revision: 1.9 $ $Date: 2012/03/01 00:40:54 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example sec_at3_e3.t.cc
/// Test driver for class sec_at3_e3.

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "sec_at3_e3.h"
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

  print_sec_header("Testing " + filename);

  // Create the namespace.

  fiber_bundles_namespace ns(filename);

  ns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;
  size_type k_size = 2;

  const poset_path& lbase_path =
    make_test_base_space(ns, i_size, j_size, k_size);

  // Run tests.

  // Test assignment:

  test_assignment<sec_at3_e3>(ns, lbase_path);

  // Test vd facet:

  test_sec_vd_facet<sec_at3_e3>(ns, lbase_path);

  // Test atp facet:

  test_sec_hook_product<sec_at3_e3, sec_e3, sec_at2_e3>(ns, lbase_path);

  test_sec_star_operator<sec_at3_e3, sec_at0>(ns, lbase_path);
  test_sec_star_operator<sec_at0, sec_at3_e3>(ns, lbase_path);

  test_sec_wedge_product<sec_at2_e3, sec_e3, sec_at3_e3>(ns, lbase_path);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}

