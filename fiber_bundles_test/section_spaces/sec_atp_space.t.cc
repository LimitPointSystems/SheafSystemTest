
// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example sec_atp_space.t.cc
/// Unit test for sec_atp_space.

#include "sec_atp_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "atp_space.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_atp.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "structured_block_1d.h"
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

  poset_path make_vector_fiber_space_schema(fiber_bundles_namespace& xns)
  {

    // Make a at1 space schema

    string lmember_names = "x DOUBLE false y DOUBLE false";

    schema_poset_member lschema(xns,
				"shallow_instantiation_test_at1_space_schema",
				at1_space::standard_schema_path(),
				lmember_names,
				true,
				true);

    poset_path result = lschema.path();

    lschema.detach_from_state();

    return result;
  }

  poset_path make_tensor_fiber_space_schema(fiber_bundles_namespace& xns)
  {

    // Make a tensor space schema; copied from at2_e2::make_standard_schema().

    string ltensor_dof_specs = "xy DOUBLE false";


    schema_poset_member ltensor_schema(xns,
				       "atp_space_test_schema",
				       atp_space::standard_schema_path(),
				       ltensor_dof_specs,
				       true,
				       true);

    poset_path result = ltensor_schema.path();
    ltensor_schema.detach_from_state();

    return result;
  }
  

  poset_path make_scalar_fiber_space(fiber_bundles_namespace& xns)
  {
    // Make the scalar fiber space, use standard schema.

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
				     const poset_path& xscalar_space_path)
  {
    // Make the vector fiber space.

    arg_list lvector_args = at1_space::make_arg_list(xscalar_space_path);
  
    at1_space* lvector_space = new at1_space(xns, 
					     "shallow_instantiation_test_at1_space", 
					     lvector_args, 
					     xvector_space_schema_path, 
					     true);
  
    cout << *lvector_space << endl;

    poset_path result = lvector_space->path(true);

    return result;
  }

  poset_path make_tensor_fiber_space(fiber_bundles_namespace& xns,
				     const poset_path& xtensor_space_schema_path,
				     const poset_path& xvector_space_path)
  {
    // Make the tensor fiber space.

    arg_list ltensor_args = atp_space::make_arg_list(2, xvector_space_path);
  
    atp_space* ltensor_space = new atp_space(xns, 
					     "shallow_instantiation_test_atp_space", 
					     ltensor_args, 
					     xtensor_space_schema_path, 
					     true);
  
    poset_path result = ltensor_space->path(true);

    cout << *ltensor_space << endl;

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

    poset_path lrep_path = sec_at1::standard_rep_path();
    arg_list lsssp_args = 
      binary_section_space_schema_poset::make_arg_list(lrep_path, 
						       xbase_space_path, 
						       xfiber_space_path);

    poset_path lsssp_schema_path = 
      binary_section_space_schema_poset::standard_schema_path();
    
    binary_section_space_schema_poset* lsssp = 
      new binary_section_space_schema_poset(xns,
					    "shallow_instantiation_test_sec_at1_schema_host",
					    lsssp_args,
					    lsssp_schema_path,
					    true);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lfiber_space_schema_path = 
      lsssp->fiber_space().schema().path();
    
    binary_section_space_schema_member 
      lschema_mbr(lsssp, xbase_space_path, lfiber_space_schema_path);
    lschema_mbr.put_name("shallow_instantiation_test_sec_at1_schema", true, false);
    poset_path result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp->release_access();

    cout << *lsssp << endl;

    return result;
  }

  poset_path make_tensor_section_space_schema(fiber_bundles_namespace& xns, 
					      const poset_path& xbase_space_path,
					      const poset_path& xfiber_space_path)
  {
    // Create the schema poset.

    poset_path lrep_path = sec_atp::standard_rep_path();
    arg_list lsssp_args = 
      binary_section_space_schema_poset::make_arg_list(lrep_path, 
						       xbase_space_path, 
						       xfiber_space_path);

    poset_path lsssp_schema_path = 
      binary_section_space_schema_poset::standard_schema_path();
    
    binary_section_space_schema_poset* lsssp = 
      new binary_section_space_schema_poset(xns,
					    "shallow_instantiation_test_sec_atp_schema_host",
					    lsssp_args,
					    lsssp_schema_path,
					    true);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lfiber_space_schema_path = 
      lsssp->fiber_space().schema().path();
    
    binary_section_space_schema_member 
      lschema_mbr(lsssp, xbase_space_path, lfiber_space_schema_path);
    lschema_mbr.put_name("shallow_instantiation_test_sec_atp_schema", true, false);
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
			"shallow_instantiation_test_sec_at0_space",
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
      sec_at1_space::make_arg_list(xscalar_space_path);

    // Make the vector section space.

    sec_at1_space* lsection_space =
      new sec_at1_space(xns,
		       "shallow_instantiation_test_sec_at1_space",
		       lsection_space_args,
		       xvector_schema_path,
		       true);

    lsection_space->get_read_access();
    
    poset_path result = lsection_space->path(false);
    cout << *lsection_space << endl;

    lsection_space->release_access();

    return result;
  }

  poset_path make_tensor_section_space(fiber_bundles_namespace& xns,
				       const poset_path& xtensor_schema_path,
				       const poset_path& xvector_space_path)
  {
    // Make the arguments.

    arg_list lsection_space_args =
      sec_atp_space::make_arg_list(2, xvector_space_path);

    // Make the tensor section space.

    sec_atp_space* lsection_space =
      new sec_atp_space(xns,
			"shallow_instantiation_test_sec_atp_space",
			lsection_space_args,
			xtensor_schema_path,
			true);

    lsection_space->get_read_access();
    
    poset_path result = lsection_space->path(false);
    cout << *lsection_space << endl;

    lsection_space->release_access();

    return result;
  }

  void test_shallow_instantiation(fiber_bundles_namespace& xns, 
				  const poset_path& xbase_space_path,
				  const poset_path& xvector_space_schema_path,
				  const poset_path& xtensor_space_schema_path)
  {
    // Make the scalar fiber space.

    poset_path lscalar_fiber_space_path = make_scalar_fiber_space(xns);

    // Make the vector fiber space.

    poset_path lvector_fiber_space_path =
      make_vector_fiber_space(xns, xvector_space_schema_path, lscalar_fiber_space_path);

    // Make the tensor fiber space.

    poset_path ltensor_fiber_space_path =
      make_tensor_fiber_space(xns, xtensor_space_schema_path, lvector_fiber_space_path);

    // Make the scalar section space schema.

    poset_path lscalar_section_space_schema_path =
      make_scalar_section_space_schema(xns, xbase_space_path, lscalar_fiber_space_path);

    // Make the vector section space schema.
  
    poset_path lvector_section_space_schema_path =
      make_vector_section_space_schema(xns, xbase_space_path, lvector_fiber_space_path);

    // Make the tensor section space schema.

    poset_path ltensor_section_space_schema_path =
      make_tensor_section_space_schema(xns, xbase_space_path, ltensor_fiber_space_path);

    // Make the scalar section space.

    poset_path lscalar_section_space_path =
      make_scalar_section_space(xns, lscalar_section_space_schema_path);

    // Make the vector section space.

    poset_path lvector_section_space_path =
      make_vector_section_space(xns, lvector_section_space_schema_path, lscalar_section_space_path);

    // Make the tensor section space.

    poset_path ltensor_section_space_path =
      make_tensor_section_space(xns, ltensor_section_space_schema_path, lvector_section_space_path);
  }

  void test_deep_instantiation(fiber_bundles_namespace& xns, 
			       const poset_path& xbase_space_path,
			       const poset_path& xvector_fiber_space_schema_path,
			       const poset_path& xtensor_fiber_space_schema_path)
  {
    typedef binary_section_space_schema_poset host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = host_type::make_arg_list("", xbase_space_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<sec_at0>("deep_instantiation_test_sec_at0_schema",
						   lsss_args);

    // Make the vector section space schema.

    poset_path lvector_schema_path =
      xns.new_vector_section_space_schema<sec_at1>("deep_instantiation_test_sec_at1_schema", 
						   lsss_args,
						   "", // xsection_space_schema__schema_path
						   "", // xrep_path
						   "", // xbase_space_path
						   "", // xfiber_space_path
						   "", // xfiber_space_args
						   xvector_fiber_space_schema_path);

    // Make the tensor section space schema.

    arg_list lfiber_args = atp_space::make_arg_list(2, "");
    
    poset_path ltensor_schema_path =
      xns.new_tensor_section_space_schema<sec_atp>("deep_instantiation_test_sec_atp_schema", 
						   lsss_args,
						   "", // xsection_space_schema_schema_path
						   "", // xrep_path
						   "", // xbase_space_path
						   "", // xfiber_space_path
						   lfiber_args, // xfiber_space_args
						   xtensor_fiber_space_schema_path, // xfiber_space_schema_path
						   "", // xvector_space_path
						   "", // xvector_space_args
						   xvector_fiber_space_schema_path
						   );

    // Make the section space.

    arg_list ltensor_args = sec_atp_space::make_arg_list(2, "");

    sec_atp_space& lsection_space =
      xns.new_tensor_section_space<sec_atp>("deep_instantiation_test_sec_atp_space",
					    ltensor_args,
					    ltensor_schema_path,
					    "deep_instantiation_test_sec_at1_space",
					    "", // xvector_space_args
					    lvector_schema_path,
					    "deep_instantiation_test_sec_at0_space",
					    "", // xscalar_space_args
					    lscalar_schema_path);

    cout << lsection_space << endl;
  }
  
    
}


int main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  // Make a base space.

  poset_path lbase_space_path = make_base_space(lns);

  // Make a schema for a concrete at1 space.

  poset_path lvector_space_schema_path = make_vector_fiber_space_schema(lns);

  // Make a schema for a concrete atp space.

  poset_path ltensor_space_schema_path = make_tensor_fiber_space_schema(lns);

  // Test shallow instantiation

  test_shallow_instantiation(lns, lbase_space_path, lvector_space_schema_path, ltensor_space_schema_path);

  // Test deep instantiation

  test_deep_instantiation(lns, lbase_space_path, lvector_space_schema_path, ltensor_space_schema_path);

  // Display the namespace.

  cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  

