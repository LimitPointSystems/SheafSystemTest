
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

/// @example gln_space.t.cc
/// Test driver for gln_space.

#include "SheafSystem/gln_space.h"

#include "SheafSystem/arg_list.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/gl2.h"
#include "SheafSystem/schema_descriptor.h"
#include "SheafSystem/schema_poset_member.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_fibers.impl.h"
#include "SheafSystem/vd_space.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  string filename = filename_from_cmdline(*xargv);
 
  fiber_bundles_namespace lns(filename);

  gln_space& lspace = gl2::standard_host(lns, "", false);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<gln_space>(lns, lspace);

  //============================================================================

  //int n() const;

  int ln0 = lspace.n();
  cout << "ln0 = " << ln0 << endl;

  //int n(bool xauto_access) const;

  int ln = lspace.n(true);
  cout << "ln = " << ln << endl;

  //poset_path scalar_space_path() const;

  poset_path lscalar_path0 = lspace.scalar_space_path();
  cout << "lscalar_path0 = " << lscalar_path0 << endl;

  //poset_path scalar_space_path(bool xauto_access) const;

  poset_path lscalar_path = lspace.scalar_space_path(true);
  cout << "lscalar_path = " << lscalar_path << endl;

  //poset_path vector_space_path() const;

  poset_path lvector_path0 = lspace.vector_space_path();
  cout << "lvector_path0 = " << lvector_path0 << endl;

  //poset_path vector_space_path(bool xauto_access) const;

  poset_path lvector_path = lspace.vector_space_path(true);
  cout << "lvector_path = " << lvector_path << endl;

  //virtual int d() const;

  int ld0 = lspace.d();
  cout << "ld0 = " << ld0 << endl;

  //int d(bool xauto_access) const;

  int ld = lspace.d(true);
  cout << "ld = " << ld << endl;

  //============================================================================

  //cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Postconditions:

  // Exit.

  return 0;
}

  
