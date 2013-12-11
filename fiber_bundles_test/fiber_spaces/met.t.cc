
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

/// @example met.t.cc
/// Unit test driver for class met.

#include "met.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "met_e2.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "stp_space.h"
#include "test_fibers.impl.h"
//#include "storage_agent.h"


using namespace std;
using namespace fiber_bundle;

namespace
{
  void
  test_met_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<met_lite>();

    test_volatile_class_tp_facet<met_lite>();

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }


  void
  test_met_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<met, met_e2>(lns);

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

  test_met_volatile();
  test_met_persistent();

  // Postconditions:

  // Exit:

  return 0;
}
