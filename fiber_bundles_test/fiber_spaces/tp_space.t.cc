// $RCSfile: tp_space.t.cc,v $ $Revision: 1.8 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example tp_space.t.cc
/// Test driver for tp_space.

#include "tp_space.h"

#include "arg_list.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "assert_contract.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "poset_path.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
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
				       true,
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
				       true,
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
    at0_space* lscalar_space = new at0_space(xns, 
					     "at0_space_test", 
					     lscalar_args,
					     lscalar_schema_path,
					     true);

    poset_path lscalar_path = lscalar_space->path();

    //    cout << *lscalar_space << endl;  

    arg_list lvector_args = at1_space::make_arg_list(lscalar_path);
  
    at1_space* lvector_space = new at1_space(xns, 
					   "at1_space_test", 
					   lvector_args, 
					   xvector_schema_path, 
					   true);
  
    poset_path lvector_path = lvector_space->path();

    //    cout << *lvector_space << endl;

    arg_list ltensor_args = tp_space::make_arg_list(2, lvector_path);
  
    vd_space* ltensor_space = new tp_space(xns, 
					   "tp_space_test", 
					   ltensor_args, 
					   xtensor_schema_path, 
					   true);
  
    //    cout << *ltensor_space << endl;

    return;
  }

  void test_deep_instantiation(fiber_bundles_namespace& xns, 
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

    return;
  }
  

}


int main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  poset_path lvector_schema_path = make_vector_space_schema(lns);
  poset_path ltensor_schema_path = make_tensor_space_schema(lns);

  test_shallow_instantiation(lns, ltensor_schema_path, lvector_schema_path);

  test_deep_instantiation(lns, ltensor_schema_path, lvector_schema_path);

  //  cout << lns << endl;
  
  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  