
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
/// @example at1_space.t.cc
/// Test driver for at1_space.

#include "at1_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "e2.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"
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

  at1_space& lvector_space = e2::standard_host(lns, "", true);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<at1_space>(lns, lvector_space);
  
  //============================================================================
  
  //cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}

  
