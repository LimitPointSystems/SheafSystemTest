// $RCSfile: stp_space.t.cc,v $ $Revision: 1.7 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example stp_space.t.cc
/// Test driver for stp_space.

#include "stp_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0_space.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"
#include "vd_space.h"
#include "wsv_block.h"

using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  // Make a scalar space, use standard schema.

  arg_list lscalar_args = at0_space::make_arg_list();
  poset_path lscalar_schema_path = at0_space::standard_schema_path();
  at0_space* lscalar_space = new at0_space(lns, 
					   "at0_space_test", 
					   lscalar_args,
					   lscalar_schema_path,
					   true);

  poset_path lscalar_path = lscalar_space->path();

  //  cout << *lscalar_space << endl;  

  // Make a vector space schema; copied from e2::make_standard_schema().

  string lvector_dof_specs = "x DOUBLE false y DOUBLE false";

  schema_poset_member lvector_schema(lns,
                              "vd_space_test_schema",
                              vd_space::standard_schema_path(),
                              lvector_dof_specs,
                              true,
                              true);

  poset_path lvector_schema_path = lvector_schema.path();
  lvector_schema.detach_from_state();

  arg_list lvector_args = vd_space::make_arg_list(lscalar_path);
  
  vd_space* lvector_space = new vd_space(lns, 
					 "vd_space_test", 
					 lvector_args, 
					 lvector_schema_path, 
					 true);
  
  poset_path lvector_path = lvector_space->path();

  //  cout << *lvector_space << endl;

  // Make a tensor space schema; copied from t2_e2::make_standard_schema().

  string ltensor_dof_specs = "xx DOUBLE false ";
  ltensor_dof_specs       += "xy DOUBLE false ";
  ltensor_dof_specs       += "yx DOUBLE false ";
  ltensor_dof_specs       += "yy DOUBLE false";


  schema_poset_member ltensor_schema(lns,
                              "stp_space_test_schema",
                              stp_space::standard_schema_path(),
                              ltensor_dof_specs,
                              true,
                              true);

  poset_path ltensor_schema_path = ltensor_schema.path();
  ltensor_schema.detach_from_state();

  arg_list ltensor_args = stp_space::make_arg_list(2, lvector_path);
  
  vd_space* ltensor_space = new tp_space(lns, 
					 "stp_space_test", 
					 ltensor_args, 
					 ltensor_schema_path, 
					 true);
  
  //  cout << *ltensor_space << endl;

  //============================================================================

  stp_space& ltensor_space2 =
    lns.new_tensor_space<st2_e2>("deep_instantiation_test_st2_e2");

  // Test member functions common to all "*_space" classes.

  test_spaces_common<stp_space>(lns, ltensor_space2);
  
  //============================================================================


  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
