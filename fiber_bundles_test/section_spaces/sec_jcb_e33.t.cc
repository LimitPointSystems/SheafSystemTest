
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

/// @example sec_jcb_e33.t.cc
/// Unit test for class sec_jcb_e33.

#include "sec_jcb_e33.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "sec_jcb_space.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;

int
main()
{
  // Preconditions:

  // Body:

  typedef sec_jcb_e33 S;

  const string& lsection_name = S::static_class_name();

  print_header("Begin testing " + lsection_name);

  // Create the namespace.

  fiber_bundles_namespace lns(lsection_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;
  size_type k_size = 2;

  const poset_path& lbase_path =
    make_test_base_space(lns, i_size, j_size, k_size);

  // Run tests.

  //$$SCRIBBLE: Jacobian not complete in fiber_bundles_namespace.

//   // Test assignment:

//   test_assignment<S>(lns, lbase_path);

//   // Test vd facet:

//   //@issue What does it mean to test the vd facet for jacobians?
//   //       They do derive from sec_vd and therefore should pass
//   //       the vd facet tests.

//   test_sec_vd_facet<S>(lns, lbase_path);

//   // Test jcb facet:

//   test_sec_jcb_facet<sec_jcb_e33, sec_e3, sec_e3>(lns, lbase_path);

  //============================================================================

  test_section_common_unattached<S>();

  //$$SCRIBBLE: Jacobian not complete in fiber_bundles_namespace.
  //test_section_common_attached<S>(lns, lbase_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(lsection_name + ".t.hdf");
  //write_agent.write_entire(lns);

  print_footer("End testing " + lsection_name);

  // Postconditions:

  // Exit:

  return 0;
}

