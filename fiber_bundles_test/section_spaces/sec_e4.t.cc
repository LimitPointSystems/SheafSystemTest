

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example sec_e4.t.cc
/// Test driver for class e4.

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "sec_e4.h"
#include "storage_agent.h"
#include "test_sections.impl.h"

using namespace fiber_bundle;

///
int
main()
{
  // Preconditions:

  // Body:

  const string& section_name = sec_e4::static_class_name();

  print_header("Testing " + section_name);

  cout << " Not implemented." << endl;
  cout << endl;

  // In order to implement this test case we have to wait for
  // support to be added to the library for 4D base spaces, etc.
       
//   // Create the namespace.

//   fiber_bundles_namespace ns(section_name + ".t");
//   ns.get_read_write_access();

//   size_type i_size = 2;
//   size_type j_size = 2;
//   size_type k_size = 2;
//   size_type l_size = 2;

//   // Make a base space.

//   const poset_path& lbase_path =
//     make_test_base_space(ns, i_size, j_size, k_size, l_size);

//   // Run tests.

//   // Test assignment:

//   test_assignment<sec_e4>(ns, lbase_path);

//   // Test vd facet:

//   test_sec_vd_facet<sec_e4>(ns, lbase_path);

//   // Test ed facet:

//   test_sec_ed_facet<sec_e4>(ns, lbase_path);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(section_name + ".t.hdf");
  //write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}

