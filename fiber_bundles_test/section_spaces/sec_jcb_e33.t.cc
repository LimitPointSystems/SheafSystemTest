

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example sec_jcb_e33.t.cc
/// Test driver for class sec_jcb_e33.


#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "sec_jcb_e33.h"
#include "storage_agent.h"
#include "test_sections.impl.h"

using namespace fiber_bundle;

///
int
main()
{
  // Preconditions:

  // Body:

  const string& section_name = sec_jcb_e33::static_class_name();

  print_header("Testing " + section_name);

  // Create the namespace.

  fiber_bundles_namespace ns(section_name + ".t");
  ns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;
  size_type k_size = 2;

  const poset_path& lbase_path =
    make_test_base_space(ns, i_size, j_size, k_size);

  // Run tests.

  // Test assignment:

  test_assignment<sec_jcb_e33>(ns, lbase_path);

  // Test vd facet:

  //@issue What does it mean to test the vd facet for jacobians?
  //       They do derive from sec_vd and therefore should pass
  //       the vd facet tests.

  test_sec_vd_facet<sec_jcb_e33>(ns, lbase_path);

  // Test jcb facet:

  test_sec_jcb_facet<sec_jcb_e33, sec_e3, sec_e3>(ns, lbase_path);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(section_name + ".t.hdf");
  //write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}

