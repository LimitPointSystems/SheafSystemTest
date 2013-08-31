

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example tp_space.t.cc
/// Test driver for tp_space.

#include "tp_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "poset_path.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"
#include "tp.h"
#include "wsv_block.h"


using namespace fiber_bundle;

namespace
{

} // end unnamed namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  tp_space& lspace = t2_e2::standard_host(lns, "", true);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<tp_space>(lns, lspace);

  //int dd(bool xauto_access) const

  int ldd = lspace.dd(true);
  cout << "ldd = " << ldd << endl;
  
  //============================================================================

  //  cout << lns << endl;
  
  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
