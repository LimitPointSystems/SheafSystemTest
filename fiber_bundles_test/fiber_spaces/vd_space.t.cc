
// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example vd_space.t.cc
/// Test driver for vd_space.

#include "vd_space.h"

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
#include "vd.h"
#include "wsv_block.h"

using namespace fiber_bundle;

namespace
{

  poset_path
  make_vector_space_schema(fiber_bundles_namespace& xns)
  {
    // Make a vector space schema; copied from e2::make_standard_schema().

    string ldof_specs = "x DOUBLE false y DOUBLE false";

    schema_poset_member lvector_schema(xns,
				       "shallow_instantiation_test_vd_space_schema",
				       vd_space::standard_schema_path(),
				       ldof_specs,
				       true,
				       true);

    poset_path result = lvector_schema.path();
    lvector_schema.detach_from_state();

    return result;
  }

  void
  test_shallow_instantiation(fiber_bundles_namespace& xns,
                             const poset_path& xvector_schema_path)
  {
    // Make a scalar space, use standard schema.

    arg_list lscalar_args = at0_space::make_arg_list();
    poset_path lscalar_schema_path = at0_space::standard_schema_path();
    at0_space* lscalar_space = new at0_space(xns, 
					     "shallow_instantiation_test_at0_space", 
					     lscalar_args,
					     lscalar_schema_path,
					     true);

    poset_path lscalar_path = lscalar_space->path();

    //    cout << *lscalar_space << endl;

    arg_list lvector_args = vd_space::make_arg_list(lscalar_path);
  
    vd_space* lvector_space = new vd_space(xns, 
					   "shallow_instantiation_test_vd_space", 
					   lvector_args, 
					   xvector_schema_path, 
					   true);
  
    //    cout << *lvector_space << endl;

    return;
  }

  vd_space&
  test_deep_instantiation(fiber_bundles_namespace& xns,
                          const poset_path& xvector_schema_path)
  {
    poset_path lpath("deep_instantiation_test_vd_space", "");
    arg_list lvector_args = vd_space::make_arg_list("");

    vd_space& lspace =
      xns.new_vector_space<vd>(lpath, lvector_args, xvector_schema_path);
    
    //cout << lspace << endl;

    return lspace;
  }
 
} // end unnamed namespace.


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  poset_path lvector_schema_path = make_vector_space_schema(lns);

  test_shallow_instantiation(lns, lvector_schema_path);
  
  vd_space& lspace = test_deep_instantiation(lns, lvector_schema_path);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<vd_space>(lns, lspace);
 
  //int factor_ct(int xd) const

  int lfactor_ct = lspace.factor_ct(2);
  cout << "lfactor_ct = " << lfactor_ct << endl;

  //void print_prereq_paths(ostream &xos, 
  //			  const vd_space& xspace, 
  //			  const string& xheading,
  //			  const string& xindent,
  //			  bool xauto_access = true);

  print_prereq_paths(cout, lspace, "vd space prereq paths:", "  ");
 
  //============================================================================

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
