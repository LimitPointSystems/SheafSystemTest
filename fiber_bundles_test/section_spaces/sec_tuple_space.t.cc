
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example sec_tuple_space.t.cc
/// Unit test for sec_tuple_space.

#include "sec_tuple_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "sec_tuple.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "structured_block_1d.h"
#include "test_fibers.impl.h"
#include "tuple_space.h"
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

    // Make a tuple space schema

    string lmember_names = "x DOUBLE false y DOUBLE false";

    schema_poset_member lschema(xns,
				"tuple_space_test_schema",
				tuple_space::standard_schema_path(),
				lmember_names,
				true,
				true);

    poset_path result = lschema.path();

    lschema.detach_from_state();

    return result;
  }

  poset_path make_fiber_space(fiber_bundles_namespace& xns, 
			      const poset_path& xfiber_space_schema_path)
  {
  
    arg_list largs = tuple_space::make_arg_list(2);

    tuple_space& lfiber_space = 
      xns.new_fiber_space<tuple>("tuple_space_test", largs, xfiber_space_schema_path, true);

    poset_path result = lfiber_space.path(true);

    return result;
  }

  poset_path make_section_space_schema(fiber_bundles_namespace& xns, 
				       const poset_path& xbase_space_path,
				       const poset_path& xfiber_space_path)
  {
    // Create the schema poset.

    poset_path lrep_path = sec_tuple::standard_rep_path();
    arg_list lsssp_args = 
      binary_section_space_schema_poset::make_arg_list(lrep_path, 
						       xbase_space_path, 
						       xfiber_space_path);

    poset_path lsssp_schema_path = 
      binary_section_space_schema_poset::standard_schema_path();
    
    binary_section_space_schema_poset* lsssp = 
      new binary_section_space_schema_poset(xns,
					    "sec_tuple_schema_host",
					    lsssp_args,
					    lsssp_schema_path,
					    true);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lfiber_space_schema_path = 
      lsssp->fiber_space().schema().path();
    
    binary_section_space_schema_member 
      lschema_mbr(lsssp, xbase_space_path, lfiber_space_schema_path);
    lschema_mbr.put_name("sec_tuple_schema", true, false);
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

    arg_list largs = sec_tuple_space::make_arg_list(2);

    sec_tuple_space& lsection_space =
      xns.new_section_space<sec_tuple>("shallow_instantiation_test_sec_tuple",
				       largs, xsection_schema_path,
				       true);

    lsection_space.get_read_access();
    
    poset_path result = lsection_space.path(false);
    cout << lsection_space << endl;

    lsection_space.release_access();

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

  sec_tuple_space&
  test_deep_instantiation(fiber_bundles_namespace& xns, 
			       const poset_path& xbase_space_path,
			       const poset_path& xfiber_space_schema_path)
  {
    // Deep instantiation not supported for sec_tuple;
    // fiber is not a scalar, vector, or tensor.

    typedef binary_section_space_schema_poset host_type;

    // Make the section space schema arguments.

    arg_list largs = host_type::make_arg_list("", xbase_space_path, "");


    // Make the tuple section space schema.

    poset_path ltuple_schema_path =
      xns.new_tuple_section_space_schema<sec_tuple>("deep_instantiation_test_sec_tuple_schema", 
						  largs,
						  "", // xsection_space_schema_schema_path
						  "", // xrep_path
						  "", // xbase_space_path
						  "", // xfiber_space_path
						  "", // xfiber_space_args
						  xfiber_space_schema_path);

    // Make the section space.
    // Can either call new_Tuple_section_space or just new_section_space.

    //     sec_tuple_space& lsection_space =
    //       xns.new_tuple_section_space<sec_tuple>("deep_instantiation_test_sec_tuple_space",
    // 					     "", // xtuple_space_args
    // 					     ltuple_schema_path,
    // 					     true);

    sec_tuple_space& lsection_space =
      xns.new_section_space<sec_tuple>("deep_instantiation_test_sec_tuple_space",
				       arg_list(""), // xtuple_space_args
				       ltuple_schema_path,
				       true);

    cout << lsection_space << endl;

    return lsection_space;
  }
  
    
}


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  print_header("Begin testing sec_tuple_space");

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  // Make a base space.

  poset_path lbase_space_path = make_base_space(lns);

  // Make a schema for a concrete tuple space.

  poset_path lfiber_space_schema_path = make_fiber_space_schema(lns);

  // Test shallow instantiation

  test_shallow_instantiation(lns, lbase_space_path, lfiber_space_schema_path);

  // Test deep instantiation

  sec_tuple_space& lspace =
   test_deep_instantiation(lns, lbase_space_path, lfiber_space_schema_path);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<sec_tuple_space>(lns, lspace);
  
  //============================================================================

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  print_footer("End testing sec_tuple_space");

  // Postconditions:

  // Exit:

  return 0;
}

  

