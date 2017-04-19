
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

/// @example st4_e2.t.cc
/// Test driver for class st4_e2.

#include "SheafSystem/st4_e2.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/stp_space.h"
#include "SheafSystemTest/test_fibers.impl.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  void
  test_st4_e2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<st4_e2_lite>();

    test_volatile_row_dofs<st4_e2_lite>();

    test_volatile_class_tp_facet<st4_e2_lite>();

    //==========================================================================

    typedef double value_type;
    typedef st4_e2_row_dofs_type<double> row_dofs_type;

    st4_e2_lite lfiber;
    const st4_e2_lite lfiber_const;

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);


    //==========================================================================

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);
    const tp_lite& ltp_prototype1 = lfiber.tp_prototype(1);
    const tp_lite& ltp_prototype2 = lfiber.tp_prototype(2);
    const tp_lite& ltp_prototype4 = lfiber.tp_prototype(4);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);
    const atp_lite& latp_prototype1 = lfiber.atp_prototype(1);
    const atp_lite& latp_prototype2 = lfiber.atp_prototype(2);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype2 = lfiber.stp_prototype(2);
    const stp_lite& lstp_prototype4 = lfiber.stp_prototype(4);

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

} // end unnamed namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  string lfilename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  // Run tests.

  test_persistent_tensor_type<st4_e2>(lns);

  test_volatile_type<st4_e2>();

  test_tensor_conversions<st4_e2>(lns);

  // Test vd facet:

  test_tensor_vd_facet<st4_e2>(lns);

  test_stp_facet<st4_e2>(lns);

  //@todo Implement test_st4_facet<st4_e2>(lns).
  //test_st4_facet<st4_e2>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_st4_e2_volatile();

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(lfilename + ".hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
