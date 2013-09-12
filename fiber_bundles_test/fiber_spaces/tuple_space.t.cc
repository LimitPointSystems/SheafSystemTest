
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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
#include "tuple.h"
#include "tuple_space.h"
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

  // Make a tuple space schema.

  string lmember_names = "x DOUBLE false y DOUBLE false";

  schema_poset_member lschema(lns,
                              "tuple_space_test_schema",
                              tuple_space::standard_schema_path(),
                              lmember_names,
                              true);

  poset_path lschema_path = lschema.path();

  lschema.detach_from_state();

  arg_list largs = tuple_space::make_arg_list(2);
  
  poset_path lfiber_space_path("tuple_space_test");
  
  fiber_bundle::tuple::host_type& lspace =
    lns.new_fiber_space< fiber_bundle::tuple>(lfiber_space_path, largs, lschema_path, true);

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

  
