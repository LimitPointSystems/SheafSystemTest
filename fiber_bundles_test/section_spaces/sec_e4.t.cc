
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

/// @example sec_e4.t.cc
/// Unit test for class e4.

#include "sec_e4.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace std;
using namespace fiber_bundle;

int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  // string lfilename = filename_from_cmdline(*xargv);

  //print_header("Testing " + lfilename);
  print_header("Begin testing sec_e4");

  // In order to implement this test case we have to wait for
  // support to be added to the library for 4D base spaces, etc.
       
//   // Create the namespace.

//   fiber_bundles_namespace lns(lfilename);
//   lns.get_read_write_access();

//   size_type i_size = 2;
//   size_type j_size = 2;
//   size_type k_size = 2;
//   size_type l_size = 2;

//   // Make a base space.

//   const poset_path& lbase_path =
//     make_test_base_space(lns, i_size, j_size, k_size, l_size);

//   // Run tests.

//   // Test assignment:

//   test_assignment<sec_e4>(lns, lbase_path);

//   // Test vd facet:

//   test_sec_vd_facet<sec_e4>(lns, lbase_path);

//   // Test ed facet:

//   test_sec_ed_facet<sec_e4>(lns, lbase_path);

  //============================================================================

  test_section_common_unattached<sec_e4>();
  //test_section_common_attached<sec_e4>(lns, lbase_path); // No 4d base space.

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(section_name + ".t.hdf");
  //write_agent.write_entire(lns);

  print_footer("Ending testing sec_e4");

  // Postconditions:

  // Exit:

  return 0;
}

