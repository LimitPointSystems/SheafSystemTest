
// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example sec_vd_space.t.cc
/// Unit test for sec_vd_space.

#include "sec_vd_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0_space.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_vd.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "structured_block_1d.h"
#include "vd_space.h"
#include "wsv_block.h"

using namespace fiber_bundle;

namespace
{

  poset_path make_base_space(fiber_bundles_namespace& xns)
  {
    xns.get_read_write_access();

    base_space_poset* lhost = &xns.new_base_space<structured_block_1d>("base_space_host");
    structured_block_1d lmesh(lhost, 2, true);
    lmesh.put_name("base_space", true, true);

    poset_path result = lmesh.path(true);
    
    lmesh.detach_from_state();
    xns.release_access();
    
    return result;
  }

  poset_path make_fiber_space_schema(fiber_bundles_namespace& xns)
  {

    // Make a vd space schema

    string lmember_names = "x DOUBLE false y DOUBLE false";

    schema_poset_member lschema(xns,
				"shallow_instantiation_test_vd_space_schema",
				vd_space::standard_schema_path(),
				lmember_names,
				true,
				true);

    poset_path result = lschema.path();

    lschema.detach_from_state();

    return result;
  }

  poset_path make_scalar_fiber_space(fiber_bundles_namespace& xns)
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

    cout << *lscalar_space << endl;

    return lscalar_path;
  }
  
  poset_path make_vector_fiber_space(fiber_bundles_namespace& xns, 
				     const poset_path& xvector_space_schema_path,
				     const poset_path& xscalar_space_schema_path)
  {
    // Make the vector space.

    arg_list lvector_args = vd_space::make_arg_list(xscalar_space_schema_path);
  
    vd_space* lvector_space = new vd_space(xns, 
					   "shallow_instantiation_test_vd_space", 
					   lvector_args, 
					   xvector_space_schema_path, 
					   true);
  
    cout << *lvector_space << endl;

    poset_path result = lvector_space->path(true);

    return result;
  }

  poset_path make_scalar_section_space_schema(fiber_bundles_namespace& xns, 
					      const poset_path& xbase_space_path,
					      const poset_path& xfiber_space_path)
  {
    // Create the schema poset.

    poset_path lrep_path = sec_at0::standard_rep_path();
    arg_list lsssp_args = 
      binary_section_space_schema_poset::make_arg_list(lrep_path, 
						       xbase_space_path, 
						       xfiber_space_path);

    poset_path lsssp_schema_path = 
      binary_section_space_schema_poset::standard_schema_path();
    
    binary_section_space_schema_poset* lsssp = 
      new binary_section_space_schema_poset(xns,
					    "shallow_instantiation_test_sec_at0_schema_host",
					    lsssp_args,
					    lsssp_schema_path,
					    true);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lfiber_space_schema_path = 
      lsssp->fiber_space().schema().path();
    
    binary_section_space_schema_member 
      lschema_mbr(lsssp, xbase_space_path, lfiber_space_schema_path);
    lschema_mbr.put_name("sec_at0_schema", true, false);
    poset_path result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp->release_access();

    cout << *lsssp << endl;

    return result;
  }

  poset_path make_vector_section_space_schema(fiber_bundles_namespace& xns, 
					      const poset_path& xbase_space_path,
					      const poset_path& xfiber_space_path)
  {
    // Create the schema poset.

    poset_path lrep_path = sec_vd::standard_rep_path();
    arg_list lsssp_args = 
      binary_section_space_schema_poset::make_arg_list(lrep_path, 
						       xbase_space_path, 
						       xfiber_space_path);

    poset_path lsssp_schema_path = 
      binary_section_space_schema_poset::standard_schema_path();
    
    binary_section_space_schema_poset* lsssp = 
      new binary_section_space_schema_poset(xns,
					    "shallow_instantiation_test_sec_vd_schema_host",
					    lsssp_args,
					    lsssp_schema_path,
					    true);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lfiber_space_schema_path = 
      lsssp->fiber_space().schema().path();
    
    binary_section_space_schema_member 
      lschema_mbr(lsssp, xbase_space_path, lfiber_space_schema_path);
    lschema_mbr.put_name("shallow_instantiation_test_sec_vd_schema", true, false);
    poset_path result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp->release_access();

    cout << *lsssp << endl;

    return result;
  }

  poset_path make_scalar_section_space(fiber_bundles_namespace& xns, 
				       const poset_path& xsection_schema_path)
  {
    // Create the section space.

    arg_list largs = sec_at0_space::make_arg_list();

    sec_at0_space* lsection_space =
      new sec_at0_space(xns,
			"shallow_instantiation_test_sec_at0",
			largs, xsection_schema_path,
			true);

    lsection_space->get_read_access();
    
    poset_path result = lsection_space->path(false);
    cout << *lsection_space << endl;

    lsection_space->release_access();

    return result;
  }  

  poset_path make_vector_section_space(fiber_bundles_namespace& xns, 
				       const poset_path& xvector_schema_path,
				       const poset_path& xscalar_space_path)
  {
    // Make the arguments.

    arg_list lsection_space_args =
      sec_vd_space::make_arg_list(xscalar_space_path);

    // Make the vector section space.

    sec_vd_space* lsection_space =
      new sec_vd_space(xns,
		       "shallow_instantiation_test_sec_vd",
		       lsection_space_args,
		       xvector_schema_path,
		       true);

    lsection_space->get_read_access();
    
    poset_path result = lsection_space->path(false);
    cout << *lsection_space << endl;

    lsection_space->release_access();

    return result;
  }  

  void test_shallow_instantiation(fiber_bundles_namespace& xns, 
				  const poset_path& xbase_space_path,
				  const poset_path& xfiber_space_schema_path)
  {

    // Make the scalar fiber space.

    poset_path lscalar_fiber_space_path = make_scalar_fiber_space(xns);

    // Make the vector fiber space.

    poset_path lvector_fiber_space_path =
      make_vector_fiber_space(xns, xfiber_space_schema_path, lscalar_fiber_space_path);

    // Make the scalar section space schema.

    poset_path lscalar_section_space_schema_path =
      make_scalar_section_space_schema(xns, xbase_space_path, lscalar_fiber_space_path);

    // Make the vector section space schema
  
    poset_path lvector_section_space_schema_path =
      make_vector_section_space_schema(xns, xbase_space_path, lvector_fiber_space_path);

    // Make the scalar section space.

    poset_path lscalar_section_space_path =
      make_scalar_section_space(xns, lscalar_section_space_schema_path);

    // Make the section space.

    poset_path lvector_section_space_path =
      make_vector_section_space(xns, lvector_section_space_schema_path, lscalar_section_space_path);
  }

  void test_deep_instantiation(fiber_bundles_namespace& xns, 
			       const poset_path& xbase_space_path,
			       const poset_path& xfiber_space_schema_path)
  {
    typedef binary_section_space_schema_poset host_type;

    // Make the section space schema arguments.

    arg_list largs = host_type::make_arg_list("", xbase_space_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<sec_at0>("deep_instantiation_test_sec_at0_schema",
						   largs);

    // Make the vector section space schema.

    poset_path lvector_schema_path =
      xns.new_vector_section_space_schema<sec_vd>("deep_instantiation_test_sec_vd_schema", 
						  largs,
						  "", // xsection_space_schema__schema_path
						  "", // xrep_path
						  "", // xbase_space_path
						  "", // xfiber_space_path
						  "", // xfiber_space_args
						  xfiber_space_schema_path);

    // Make the section space.
    // Can either call new_vector_section_space or just new_section_space.


    //     sec_vd_space& lsection_space =
    //       xns.new_vector_section_space<sec_vd>("deep_instantiation_test_sec_vd_space",
    // 					   "", // xvector_space_args
    // 					   lvector_schema_path,
    // 					   "deep_instantiation_test_sec_at0_space",
    // 					   "", // xscalar_space_args
    // 					   lscalar_schema_path);

    sec_vd_space& lsection_space =
      xns.new_section_space<sec_vd>("deep_instantiation_test_sec_vd_space",
				    arg_list(""), // xvector_space_args
				    lvector_schema_path);

    cout << lsection_space << endl;
  }
  
    
}


int main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  // Make a base space.

  poset_path lbase_space_path = make_base_space(lns);

  // Make a schema for a concrete vd space.

  poset_path lfiber_space_schema_path = make_fiber_space_schema(lns);

  // Test shallow instantiation

  test_shallow_instantiation(lns, lbase_space_path, lfiber_space_schema_path);

  // Test deep instantiation

  test_deep_instantiation(lns, lbase_space_path, lfiber_space_schema_path);

  // Display the namespace.

  cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  

