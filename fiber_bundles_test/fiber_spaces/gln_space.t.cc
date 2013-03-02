
// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example gln_space.t.cc
/// Test driver for gln_space.

#include "gln_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e2.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "gl2.h"
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

    //cout << *lscalar_space << endl;  

    // Make a vector space schema; copied from e2::make_standard_schema().

    string lvector_dof_specs = "x DOUBLE false y DOUBLE false";

    schema_poset_member lvector_schema(xns,
				       "at1_space_test_schema",
				       at1_space::standard_schema_path(),
				       lvector_dof_specs,
				       true,
				       true);

    poset_path lvector_schema_path = lvector_schema.path();
    lvector_schema.detach_from_state();

    arg_list lvector_args = at1_space::make_arg_list(lscalar_path);
  
    at1_space& lvector_space = xns.new_fiber_space<at1>("at1_space_test", 
							lvector_args, 
							lvector_schema_path);

    poset_path lvector_path = lvector_space.path();

    //cout << *lvector_space << endl;

    // Make a gln space schema; copied from gl2::make_standard_schema().

    string lgln_dof_specs = "bxx DOUBLE false ";
    lgln_dof_specs       += "bxy DOUBLE false ";
    lgln_dof_specs       += "byx DOUBLE false ";
    lgln_dof_specs       += "byy DOUBLE false";
    lgln_dof_specs       += "cxx DOUBLE false ";
    lgln_dof_specs       += "cxy DOUBLE false ";
    lgln_dof_specs       += "cyx DOUBLE false ";
    lgln_dof_specs       += "cyy DOUBLE false";


    schema_poset_member lgln_schema(xns,
				    "gln_space_test_schema",
				    gln_space::standard_schema_path(),
				    lgln_dof_specs,
				    true,
				    true);

    poset_path lgln_schema_path = lgln_schema.path();
    lgln_schema.detach_from_state();

    arg_list lgln_args =
      gln_space::make_arg_list(2, lscalar_path, lvector_path);

    gln_space& lgln_space =
      xns.new_fiber_space<gln>("gln_space_test", 
			       lgln_args, 
			       lgln_schema_path);
  }
  

  gln_space& test_deep_instantiation(fiber_bundles_namespace& xns)
  {
    gln_space& lspace =
      xns.new_group_space<gl2>("deep_instantiation_test_gl2_space");

    return lspace;
  }

} // End unnamed namespace.


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);
 
  fiber_bundles_namespace lns(filename);

  test_shallow_instantiation(lns);
  gln_space& lspace = test_deep_instantiation(lns);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<gln_space>(lns, lspace);

  //============================================================================

  //int n() const;

  int ln0 = lspace.n();
  cout << "ln0 = " << ln0 << endl;

  //int n(bool xauto_access) const;

  int ln = lspace.n(true);
  cout << "ln = " << ln << endl;

  //poset_path scalar_space_path() const;

  poset_path lscalar_path0 = lspace.scalar_space_path();
  cout << "lscalar_path0 = " << lscalar_path0 << endl;

  //poset_path scalar_space_path(bool xauto_access) const;

  poset_path lscalar_path = lspace.scalar_space_path(true);
  cout << "lscalar_path = " << lscalar_path << endl;

  //poset_path vector_space_path() const;

  poset_path lvector_path0 = lspace.vector_space_path();
  cout << "lvector_path0 = " << lvector_path0 << endl;

  //poset_path vector_space_path(bool xauto_access) const;

  poset_path lvector_path = lspace.vector_space_path(true);
  cout << "lvector_path = " << lvector_path << endl;

  //virtual int d() const;

  int ld0 = lspace.d();
  cout << "ld0 = " << ld0 << endl;

  //int d(bool xauto_access) const;

  int ld = lspace.d(true);
  cout << "ld = " << ld << endl;

  //============================================================================

  //cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Postconditions:

  // Exit.

  return 0;
}

  
