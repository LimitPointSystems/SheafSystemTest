
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

/// @example field_e3.t.cc
/// Test driver for class field_e3.

#include "assert_contract.h"
#include "at1_space.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "field_at2_e3.h"
#include "field_at3_e3.h"
#include "field_e3.h"
#include "sec_at1_space.h"
#include "sec_at2_e3.h"
#include "sec_at3_e3.h"
#include "sec_e3.h"
#include "storage_agent.h"
#include "test_fields.impl.h"

using namespace fields;

int
main()
{
  // Preconditions:

  // Body:

  const string& field_name = field_e3::static_class_name();
  print_header("Testing " + field_name);

  // Create the namespace.

  fiber_bundle::fiber_bundles_namespace lns(field_name + ".t");
  lns.get_read_write_access();

  size_type i_size = 2;
  size_type j_size = 2;
  size_type k_size = 2;

  // Make a base space.

  const poset_path& lbase_path =
    make_test_base_space(lns, i_size, j_size, k_size);

  // Create the coordinates section.

  const poset_path& lcoords_path = make_test_coordinates_3d(lns, lbase_path);

  // Run tests.

  // Test assignment:

  test_field_assignment<field_e3>(lns, lbase_path, lcoords_path);

  // Test vd facet:

  test_field_vd_facet<field_e3>(lns, lbase_path, lcoords_path);

  // Test atp facet:

  test_field_hook_product<field_e3, field_e3, field_at0>
    (lns, lbase_path, lcoords_path);

  test_field_hook_product<field_at2_e3, field_e3, field_e3>
    (lns, lbase_path, lcoords_path);

  test_field_wedge_product<field_e3, field_e3, field_at2_e3>
    (lns, lbase_path, lcoords_path);

  test_field_wedge_product<field_at2_e3, field_e3, field_at3_e3>
    (lns, lbase_path, lcoords_path);

  // Test ed facet:

  test_field_ed_facet<field_e3>(lns, lbase_path, lcoords_path);

  // Test e3 facet:

  test_field_e3_facet(lns, lbase_path, lcoords_path);

  //============================================================================

  test_field_common<field_e3>(lns, lbase_path, lcoords_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(field_name + ".t.hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
