

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example atp_space.t.cc
/// Test driver for atp_space.

#include "atp_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "at2_e2.h"
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

  atp_space& ltensor_space = at2_e2::standard_host(lns, "", true);

  // Test member functions common to all "*_space" classes.

  test_spaces_common<atp_space>(lns, ltensor_space);
  
  //============================================================================

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
