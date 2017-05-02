
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @example field_e4.t.cc
/// Test driver for class e4.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/field_e4.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_fields.impl.h"

using namespace std;
using namespace fields;


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
