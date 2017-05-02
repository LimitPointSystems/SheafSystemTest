
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

/// @example ed.t.cc
/// Unit test driver for class ed.

#include "SheafSystem/ed.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/e1.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystemTest/test_fibers.impl.h"
//#include "SheafSystem/storage_agent.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  void
  test_ed_volatile()
  {
    // Preconditions:

    // Body:

   //==========================================================================

    test_volatile_common<ed_lite>();

    //test_volatile_row_dofs<ed_lite>();

    test_volatile_class_tp_facet<ed_lite>();

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_ed_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<ed, e1>(lns);

    // Write the namespace to standard out.

    //cout << lns << endl;

    // Write the namespace to a file.

    //storage_agent write_agent("test_namespace.hdf");
    //write_agent.write_entire(lns);

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }


} // end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  // Run tests.

  test_ed_volatile();
  test_ed_persistent();

  // Postconditions:

  // Exit:

  return 0;
}
