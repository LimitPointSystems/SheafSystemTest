// $RCSfile: at1_space.t.cc,v $ $Revision: 1.7 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example at1_space.t.cc
/// Test driver for at1_space.

#include "at1_space.h"

#include "arg_list.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "assert_contract.h"
#include "error_message.h"
#include "e2.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "wsv_block.h"

using namespace fiber_bundle;

int main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
 
  //Body

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

  //cout << *lscalar_space << endl;

  // Make a vector space schema; copied from e2::make_standard_schema().

  string ldof_specs = "x DOUBLE false y DOUBLE false";

  schema_poset_member lvector_schema(lns,
                              "at1_space_test_schema",
                              at1_space::standard_schema_path(),
                              ldof_specs,
                              true,
                              true);

  poset_path lvector_schema_path = lvector_schema.path();
  lvector_schema.detach_from_state();

  arg_list lvector_args = at1_space::make_arg_list(lscalar_path);
  
  vd_space* lvector_space = new vd_space(lns, 
					 "at1_space_test", 
					 lvector_args, 
					 lvector_schema_path, 
					 true);

  //cout << *lvector_space << endl;

  // Test deep instantiation.

  at1_space& lvector_space2 = lns.new_vector_space<e2>("deep_instantiation_test_e2");
  
  //cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
