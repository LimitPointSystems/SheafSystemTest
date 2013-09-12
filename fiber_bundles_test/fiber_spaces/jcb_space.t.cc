
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

/// @example jcb_space.t.cc
/// Test driver for jcb_space.

#include "jcb_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e1.h"
#include "e3.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "jcb_e13.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"
#include "vd_space.h"
#include "wsv_block.h"

using namespace fiber_bundle;

namespace
{
  void test_shallow_instantiation(fiber_bundles_namespace& xns)
  {

    // Make a scalar space, use standard schema.
 
    arg_list lscalar_args = at0_space::make_arg_list();
    poset_path lscalar_schema_path = at0_space::standard_schema_path();

    at0_space& lscalar_space =
      xns.new_fiber_space<at0>("at0_space_test", 
			       lscalar_args,
			       lscalar_schema_path,
			       true);
    poset_path lscalar_path = lscalar_space.path();

    // Make a domain vector space.
 
    poset_path ldomain_schema_path = e1::standard_schema_path();
    arg_list ldomain_args = at1_space::make_arg_list(lscalar_path);

    at1_space& ldomain_space =
      xns.new_fiber_space<at1>("jcb_space_test_domain_space", 
			       ldomain_args,
			       ldomain_schema_path,
			       true);

    poset_path ldomain_path = ldomain_space.path();

    // Make a range vector space.
 
    poset_path lrange_schema_path = e3::standard_schema_path();
    arg_list lrange_args = at1_space::make_arg_list(lscalar_path);

    at1_space& lrange_space =
      xns.new_fiber_space<at1>("jcb_space_test_range_space", 
			       lrange_args,
			       lrange_schema_path,
			       true);

    poset_path lrange_path = lrange_space.path();

    // Make a jcb space; use jcb_e13 schema.

    arg_list ljcb_args = jcb_space::make_arg_list(ldomain_path, lrange_path);

    jcb_space& ljcb_space =
      xns.new_fiber_space<jcb>("jcb_space_test", 
			       ljcb_args, 
			       jcb_e13::standard_schema_path(), 
			       true);
  }

  jcb_space& test_deep_instantiation(fiber_bundles_namespace& xns)
  {
    jcb_space& lspace =
      xns.new_jacobian_space<jcb_e13>("deep_instantiation_test_jcb_e13");

    return lspace;
  }

 
} // end unnamed namespace.

  

int main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  test_shallow_instantiation(lns);
  jcb_space& lspace = test_deep_instantiation(lns);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<jcb_space>(lns, lspace);

  //============================================================================
  
  //  cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
