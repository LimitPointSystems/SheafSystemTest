

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example tuple_space.t.cc
/// Test driver for tuple_space.

#include "tuple_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "sec_tuple.h"
#include "sec_tuple_space.h"
#include "std_iostream.h"
#include "test_fibers.impl.h"
#include "e3.h"
#include "at1_space.h"
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
  lns.get_read_write_access();

  fiber_bundle::tuple::host_type& lspace = e2::standard_host(lns, "", false);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<tuple_space>(lns, lspace);
 
  //int lfactor_ct(bool) const

  int lfactor_ct = lspace.factor_ct(true);
  cout << "lfactor_ct = " << lfactor_ct << endl;

  //============================================================================
  
  cout << lspace << endl;

  // Done.

  return 0;
}

  
