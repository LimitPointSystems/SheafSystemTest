
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

/// @example at2.t.cc
/// Unit test driver for class at2.

#include "at2.h"
#include "at2_e2.h"
#include "atp_space.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers.impl.h"
//#include "ComLimitPoint/sheaf/storage_agent.h"


using namespace std;
using namespace fiber_bundle;

namespace
{
  void
  test_at2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<at2_lite>();

    test_volatile_class_tp_facet<at2_lite>();

    //==========================================================================

    //at2_lite(const row_dofs_type& xrow_dofs);

     at2_lite::row_dofs_type lrow_dofs;
     at2_lite lfiber(lrow_dofs);


     //at2_lite& operator=(const row_dofs_type& xrow_dofs);

     at2_lite lfiber_assign = lrow_dofs;

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_at2_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<at2, at2_e2>(lns);

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

  test_at2_volatile();
  test_at2_persistent();

  // Postconditions:

  // Exit:

  return 0;
}

