// $RCSfile: sec_at0_space.t.cc,v $ $Revision: 1.10 $ $Date: 2012/07/04 16:42:10 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example sec_at0_space.t.cc
/// Test driver for sec_at0_space.

#define DIAGNOSTIC_OUTPUT

#include "sec_at0_space.h"

#include "arg_list.h"
#include "at0_space.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
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

  poset_path make_fiber_space_schema(fiber_bundles_namespace& xns)
  {
    // Make a at0 space schema

    poset_path result = at0::standard_schema_path();

    return result;
  }

  poset_path make_fiber_space(fiber_bundles_namespace& xns, 
			      const poset_path& xfiber_space_schema_path)
  {
  
    arg_list largs = at0_space::make_arg_list();
  
    at0_space* lfiber_space = 
      new at0_space(xns, "at0_space_test", largs, xfiber_space_schema_path, true);

    poset_path result = lfiber_space->path(true);

    return result;
  }

  poset_path make_section_space_schema(fiber_bundles_namespace& xns, 
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
					    "sec_at0_schema_host",
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

  poset_path make_section_space(fiber_bundles_namespace& xns, 
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

  void test_shallow_instantiation(fiber_bundles_namespace& xns, 
				  const poset_path& xbase_space_path,
				  const poset_path& xfiber_space_schema_path)
  {

    // Make the fiber space.

    poset_path lfiber_space_path = make_fiber_space(xns, xfiber_space_schema_path);

    // Make the section space schema
  
    poset_path lsection_space_schema_path =
      make_section_space_schema(xns, xbase_space_path, lfiber_space_path);

    // Make the section space.

    poset_path lsection_space_path = make_section_space(xns, lsection_space_schema_path);
    
  }

  void test_deep_instantiation(fiber_bundles_namespace& xns, 
			       const poset_path& xbase_space_path,
			       const poset_path& xfiber_space_schema_path)
  {
    typedef binary_section_space_schema_poset schema_poset_type;
    
    // The standard fiber space was already created by the shallow test.

    // Make the section space schema arguments.

    arg_list largs = 
      schema_poset_type::make_arg_list("", xbase_space_path, "");

    // Make the section space schema.
    
    poset_path lschema_path = xns.new_scalar_section_space_schema<sec_at0>("", largs);
    
    section_space_schema_poset* lsssp =
      reinterpret_cast<section_space_schema_poset*>(xns.member_poset(lschema_path, true));

    cout << *lsssp << endl;

    // Make the section space arguments.

    largs = sec_at0_space::make_arg_list();

    // Make the section space.

    sec_at0_space& lsection_space =
      xns.new_scalar_section_space<sec_at0>("deep_instantiation_test_sec_at0",
					    largs, lschema_path);

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

  // Make a schema for a concrete at0 space.

  poset_path lfiber_space_schema_path = make_fiber_space_schema(lns);

  // Test shallow instantiation

  test_shallow_instantiation(lns, lbase_space_path, lfiber_space_schema_path);

  // Test deep instantiation

  test_deep_instantiation(lns, lbase_space_path, lfiber_space_schema_path);

  cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  

