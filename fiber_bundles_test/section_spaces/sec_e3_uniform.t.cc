
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

/// @example section_spaces/sec_e3_uniform.t.cc
/// Unit test for class sec_e3_uniform.

#include "SheafSystem/sec_e3_uniform.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystemTest/test_sections.impl.h"
#include "SheafSystemTest/test_utils.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fiber_bundle;

int
main(int argc, char* argv[])
{
  // Preconditions:

  // Body:

  typedef sec_e3_uniform S;

  const string& lsection_name = S::static_class_name();

  print_header("Begin testing " + lsection_name);

  size_t i_size = (argc > 1) ? atoi(argv[1]) : 2;
  size_t j_size = (argc > 2) ? atoi(argv[2]) : 3;
  size_t k_size = (argc > 3) ? atoi(argv[3]) : 4;

  // Create the namespace.

  fiber_bundles_namespace lns(lsection_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  const poset_path& lbase_path =
    make_test_base_space(lns, i_size, j_size, k_size);

  // Make the section space.

  S::host_type& lhost =
    S::standard_host(lns, lbase_path, "", "", "", false);
  
  // Make the section.

  wsv_block<sec_vd_dof_type> llower("-2.0 -3.0 -4.0");
  wsv_block<sec_vd_dof_type> lupper("2.0 3.0 4.0");

  S lcoords(&lhost, llower, lupper, true);
  lcoords.put_name("uniform_coordinates", true, true);

  // Print the result.

  //cout << lns << endl;

  // Clean-up

  lcoords.detach_from_state();

  //============================================================================

  test_section_common_unattached<S>();
  test_section_common_attached<S>(lns, lbase_path);

  //============================================================================

  print_footer("End testing " + lsection_name);

  // Postconditions:

  // Exit:

  return 0;
}

