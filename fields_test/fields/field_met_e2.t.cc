
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

/// @example field_met_e2.t.cc
/// Test driver for class field_met_e2.

#include "assert_contract.h"
#include "at1_space.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "field_e2.h"
#include "field_met_e2.h"
#include "sec_at1_space.h"
#include "sec_e2.h"
#include "sec_met_e2.h"
#include "sec_stp_space.h"
#include "storage_agent.h"
#include "stp_space.h"
#include "test_fields.impl.h"

using namespace fields;

int
main()
{
  // Preconditions:

  // Body:

  const string& field_name = field_met_e2::static_class_name();
  print_header("Testing " + field_name);

  // Create the namespace.

  fiber_bundles_namespace lns(field_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;

  const poset_path& lbase_path = make_test_base_space(lns, i_size, j_size);

  // Create the coordinates section.

  const poset_path& lcoords_path = make_test_coordinates_2d(lns, lbase_path);

  // Run tests.

  // Test assignment:

  test_field_assignment<field_met_e2>(lns, lbase_path, lcoords_path);

  // Test vd facet:

  test_field_vd_facet<field_met_e2>(lns, lbase_path, lcoords_path);

  // Test st2 facet:

  test_field_st2_facet<field_met_e2>(lns, lbase_path, lcoords_path);

  // Test met facet:

  test_field_met_facet<field_met_e2, field_e2>(lns, lbase_path, lcoords_path);

  //============================================================================

  test_field_common<field_met_e2>(lns, lbase_path, lcoords_path);

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
