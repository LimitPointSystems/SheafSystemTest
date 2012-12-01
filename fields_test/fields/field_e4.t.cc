
// $RCSfile: field_e4.t.cc,v $ $Revision: 1.5 $ $Date: 2012/03/01 00:41:03 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example field_e4.t.cc
/// Test driver for class e4.

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "field_e4.h"
#include "storage_agent.h"
#include "test_fields.impl.h"

using namespace fields;

///
int
main()
{
  // Preconditions:

  // Body:

  const string& field_name = field_e4::static_class_name();
  print_header("Testing " + field_name);

  cout << " Not implemented." << endl;
  cout << endl;

  // In order to implement this test case we have to wait for
  // support to be added to the library for 4D base spaces, etc.
       
//   // Create the namespace.

//   fiber_bundles_namespace lns(field_name + ".t");
//   ns.get_read_write_access();

//   size_type i_size = 2;
//   size_type j_size = 2;
//   size_type k_size = 2;
//   size_type l_size = 2;

//   // Make a base space.

//   const poset_path& lbase_path =
//     make_test_base_space(lns, i_size, j_size, k_size, l_size);

 // Create the coordinates section.

//   const poset_path& lcoords_path = make_test_coordinates_3d(lns, lbase_path);

//   // Run tests.

//   // Test vd facet:

  //test_field_vd_facet<field_e4>(lns, lbase_path, lcoords_path);

//   // Test ed facet:

//   test_field_ed_facet<field_e4>(lns, lbase_path);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(field_name + ".t.hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
