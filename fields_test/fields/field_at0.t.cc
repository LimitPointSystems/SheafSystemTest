
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

/// @example field_at0.t.cc

/// @file
/// Test driver for class field.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/base_space_member.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/field_at0.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_fields.impl.h"

using namespace std;
using namespace fields;

int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  string filename = filename_from_cmdline(*xargv);

  print_header("Testing " + filename);

  // Create the namespace.

  fiber_bundles_namespace lns(filename);

  lns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;

  const poset_path& lbase_path = make_test_base_space(lns, i_size, j_size);

  // Create the coordinates section.

  const poset_path& lcoords_path = make_test_coordinates_2d(lns, lbase_path);

  // Run tests.

  // Test at0 facet:

  test_field_at0_facet(lns, lbase_path, lcoords_path);

  // Test vd facet:

  test_field_vd_facet<field_at0>(lns, lbase_path, lcoords_path);

  //============================================================================

  test_field_common<field_at0>(lns, lbase_path, lcoords_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(lns);

  //lcoords->detach_from_state();
  //delete lcoords;

 // Postconditions:

  // Exit:

  return 0;
}

