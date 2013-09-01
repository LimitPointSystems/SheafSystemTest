

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example vd_space.t.cc
/// Test driver for vd_space.

#include "vd_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"
#include "e2.h"
#include "at1_space.h"
#include "wsv_block.h"

using namespace fiber_bundle;

namespace
{

} // end unnamed namespace.


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  vd_space& lspace = e2::standard_host(lns, "", false);

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

  
