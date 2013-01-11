// $RCSfile: at0_space.t.cc,v $ $Revision: 1.7 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example at0_space.t.cc
/// Test driver for at0_space.

#include "at0_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "wsv_block.h"
#include "test_fibers.impl.h"

using namespace fiber_bundle;

int
main( int xargc, char* xargv[])
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

  at0_space& lscalar_space2 =
    lns.new_scalar_space<at0>("deep_instantiation_test_at0");

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<at0_space>(lns, lscalar_space2);
  
  //============================================================================

  //cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
