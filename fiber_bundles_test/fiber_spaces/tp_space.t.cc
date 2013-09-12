
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
/// @example tp_space.t.cc
/// Test driver for tp_space.

#include "tp_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "poset_path.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"
#include "tp.h"
#include "wsv_block.h"


using namespace fiber_bundle;

namespace
{

  poset_path make_vector_space_schema(fiber_bundles_namespace& xns)
  {
    // Make a vector space schema; copied from e2::make_standard_schema().

    string ldof_specs = "x DOUBLE false y DOUBLE false";

    schema_poset_member lvector_schema(xns,
				       "shallow_instantiation_test_vd_space_schema",
				       at1_space::standard_schema_path(),
				       ldof_specs,
				       true);

    poset_path result = lvector_schema.path();
    lvector_schema.detach_from_state();

    return result;
  }

  poset_path make_tensor_space_schema(fiber_bundles_namespace& xns)
  {

    // Make a tensor space schema; copied from t2_e2::make_standard_schema().

    string ltensor_dof_specs = "xx DOUBLE false ";
    ltensor_dof_specs       += "xy DOUBLE false ";
    ltensor_dof_specs       += "yx DOUBLE false ";
    ltensor_dof_specs       += "yy DOUBLE false";


    schema_poset_member ltensor_schema(xns,
				       "tp_space_test_schema",
				       tp_space::standard_schema_path(),
				       ltensor_dof_specs,
				       true);

    poset_path result = ltensor_schema.path();
    ltensor_schema.detach_from_state();

    return result;
  }
  
  void test_shallow_instantiation(fiber_bundles_namespace& xns, 
				  const poset_path& xtensor_schema_path,
				  const poset_path& xvector_schema_path)
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

    //    cout << *lscalar_space << endl;  

    arg_list lvector_args = at1_space::make_arg_list(lscalar_path);
  
     at1_space& lvector_space = xns.new_fiber_space<at1>("at1_space_test", 
							 lvector_args, 
							 xvector_schema_path,
							 true);

     poset_path lvector_path = lvector_space.path();

    //    cout << *lvector_space << endl;

    arg_list ltensor_args = tp_space::make_arg_list(2, lvector_path);

    tp_space& ltensor_space =
      xns.new_fiber_space<tp>("tp_space_test", 
			      ltensor_args, 
			      xtensor_schema_path, 
			      true);
  
    //    cout << *ltensor_space << endl;

    return;
  }

  tp_space& test_deep_instantiation(fiber_bundles_namespace& xns, 
			       const poset_path& xtensor_schema_path, 
			       const poset_path& xvector_schema_path)
  {

    poset_path lpath("deep_instantiation_test_tp_space", "");
    arg_list ltensor_args = tp_space::make_arg_list(2, "");


    tp_space& lspace = xns.new_tensor_space<tp>(lpath, 
						ltensor_args, 
						xtensor_schema_path,
						"",
						"",
						xvector_schema_path);
    
    
    //    cout << lspace << endl;

    return lspace;
  }

} // end unnamed namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  poset_path lvector_schema_path = make_vector_space_schema(lns);
  poset_path ltensor_schema_path = make_tensor_space_schema(lns);

  test_shallow_instantiation(lns, ltensor_schema_path, lvector_schema_path);

  tp_space& lspace =
    test_deep_instantiation(lns, ltensor_schema_path, lvector_schema_path);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<tp_space>(lns, lspace);

  //int dd(bool xauto_access) const

  int ldd = lspace.dd(true);
  cout << "ldd = " << ldd << endl;
  
  //============================================================================

  //  cout << lns << endl;
  
  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
