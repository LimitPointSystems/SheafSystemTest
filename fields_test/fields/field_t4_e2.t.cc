
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

/// @example field_t4_e2.t.cc
/// Test driver for class field_t4_e2.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/base_space_member.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/field_t4_e2.h"
#include "SheafSystem/field_st4_e2.h"
#include "SheafSystem/sec_at1_space.h"
#include "SheafSystem/sec_t4_e2.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/sec_stp_space.h"
#include "SheafSystemTest/test_fields.impl.h"

using namespace std;
using namespace fields;


int
main()
{
  // Preconditions:

  // Body:

  const string& field_name = field_t4_e2::static_class_name();
  print_header("Testing " + field_name);

  // Create the namespace.

  fiber_bundles_namespace lns(field_name + ".t");
  lns.get_read_write_access();

  size_type i_size = 2;
  size_type j_size = 2;

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(lns, i_size, j_size);

  // Create the coordinates section.

  const poset_path& lcoords_path = make_test_coordinates_2d(lns, lbase_path);

  // Run tests.

  // Test assignment:

  test_field_assignment<field_t4_e2>(lns, lbase_path, lcoords_path);

  // Test vd facet:

  test_field_vd_facet<field_t4_e2>(lns, lbase_path, lcoords_path);

  // Test alt and sym functions of the tp facet:

//   test_field_tp_facet<field_t4_e2, field_at4_e2, field_st4_e2>
//     (lns, lbase_path, lcoords_path);

//   test_field_tensor_product<field_t3_e2, field_e2, field_t4_e2>
//     (lns, lbase_path, lcoords_path);

//   test_field_tensor_product<field_at3_e2, field_e2, field_t4_e2>
//     (lns, lbase_path, lcoords_path);

//   test_field_tensor_product<field_st3_e2, field_e2, field_t4_e2>
//     (lns, lbase_path, lcoords_path);

  //============================================================================

  test_field_common<field_t4_e2>(lns, lbase_path, lcoords_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(field_name + ".t.hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
