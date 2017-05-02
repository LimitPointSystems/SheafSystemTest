
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

/// @example jcb_space.t.cc
/// Test driver for jcb_space.

#include "SheafSystem/jcb_space.h"

#include "SheafSystem/arg_list.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/e1.h"
#include "SheafSystem/e3.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/jcb_e13.h"
#include "SheafSystem/schema_descriptor.h"
#include "SheafSystem/schema_poset_member.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_fibers.impl.h"
#include "SheafSystem/vd_space.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
} // end unnamed namespace.

int main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  jcb_space& lspace = jcb_e13::standard_host(lns, "", false);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<jcb_space>(lns, lspace);

  //============================================================================
  
  //  cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
