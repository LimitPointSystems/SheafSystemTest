
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

/// @example sec_met_e2.t.cc
/// Unit test for class sec_met_e2.

#include "sec_met_e2.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_string.h"
#include "storage_agent.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;

///

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  string lfilename = filename_from_cmdline(*xargv);

  print_header("Testing " + lfilename);

  // Create the namespace.

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;

  const poset_path& lbase_path = make_test_base_space(lns, i_size, j_size);

  // Run tests.

  // Test assignment:

  test_assignment<sec_met_e2>(lns, lbase_path);

  // Test vd facet:

  test_sec_vd_facet<sec_met_e2>(lns, lbase_path);

  // Test met facet:

  test_sec_met_facet<sec_met_e2>(lns, lbase_path);

  //============================================================================

  test_section_common_unattached<sec_met_e2>();
  test_section_common_attached<sec_met_e2>(lns, lbase_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(lfilename + ".t.hdf");
  write_agent.write_entire(lns);

  print_footer("Ending testing sec_met_e2");

  // Postconditions:

  // Exit:

  return 0;
}

