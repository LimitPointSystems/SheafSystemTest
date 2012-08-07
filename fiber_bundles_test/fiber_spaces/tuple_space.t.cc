// $RCSfile: tuple_space.t.cc,v $ $Revision: 1.8 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
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
#include "std_iostream.h"
#include "tuple.h"
#include "tuple_space.h"
#include "sec_tuple.h"
#include "sec_tuple_space.h"
#include "wsv_block.h"

using namespace fiber_bundle;

int main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);

  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);
  lns.get_read_write_access();

  // Make a tuple space schema

  string lmember_names = "x DOUBLE false y DOUBLE false";

  schema_poset_member lschema(lns,
                              "tuple_space_test_schema",
                              tuple_space::standard_schema_path(),
                              lmember_names,
                              true,
                              true);

  poset_path lschema_path = lschema.path();

  lschema.detach_from_state();

  arg_list largs = tuple_space::make_arg_list(2);
  
  poset_path lfiber_space_path("tuple_space_test");
  
  tuple::host_type& lspace = lns.new_fiber_space<tuple>(lfiber_space_path, largs, lschema_path, true);
  
  cout << lspace << endl;

  // Done.

  return 0;
}

  
