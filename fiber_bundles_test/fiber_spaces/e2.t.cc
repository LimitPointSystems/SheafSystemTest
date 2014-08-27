
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

/// @example e2.t.cc
/// Unit test driver for class e2.

#include "e2.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "test_fibers.impl.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  void
  test_e2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<e2_lite>();

    test_volatile_row_dofs<e2_lite>();

    test_volatile_class_tp_facet<e2_lite>();

    //==========================================================================
    // vd facet
    //==========================================================================

    e2_lite lfiber;

    //operator row_dofs_type& ();

    e2_lite::row_dofs_type& lrow_dofs1 = lfiber;

    //operator const row_dofs_type& () const;

    const e2_lite lfiber_const;
    const e2_lite::row_dofs_type& lrow_dofs3 = lfiber_const;

    //==========================================================================

    //static const tp_lite& static_tp_prototype(int xp);

    const tp_lite& lstatic_tp_prototype0 = e2_lite::static_tp_prototype(0);
    const tp_lite& lstatic_tp_prototype1 = e2_lite::static_tp_prototype(1);
    const tp_lite& lstatic_tp_prototype2 = e2_lite::static_tp_prototype(2);
    const tp_lite& lstatic_tp_prototype4 = e2_lite::static_tp_prototype(4);

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);
    const tp_lite& ltp_prototype1 = lfiber.tp_prototype(1);
    const tp_lite& ltp_prototype2 = lfiber.tp_prototype(2);
    const tp_lite& ltp_prototype4 = lfiber.tp_prototype(4);

    //static const atp_lite& static_atp_prototype(int xp);

    const atp_lite& lstatic_atp_prototype0 = e2_lite::static_atp_prototype(0);
    const atp_lite& lstatic_atp_prototype1 = e2_lite::static_atp_prototype(1);
    const atp_lite& lstatic_atp_prototype2 = e2_lite::static_atp_prototype(2);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);
    const atp_lite& latp_prototype1 = lfiber.atp_prototype(1);
    const atp_lite& latp_prototype2 = lfiber.atp_prototype(2);

    //static const stp_lite& static_stp_prototype(int xp);

    const stp_lite& lstatic_stp_prototype2 = e2_lite::static_stp_prototype(2);
    const stp_lite& lstatic_stp_prototype4 = e2_lite::static_stp_prototype(4);

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

  test_persistent_vector_type<e2>(lns);

  test_volatile_type<e2>();

  test_vector_conversions<e2>(lns);

  // Test vd facet:

  test_vector_vd_facet<e2>(lns);

  // Test atp facet:

#ifndef _WIN32

  test_hook_product<e2, e2, at0>(lns);
  test_hook_product<at2_e2, e2, e2>(lns);

  test_star_operator<e2, e2>(lns);

  test_wedge_product<e2, e2, at2_e2>(lns);

#endif

  // Test ed facet:

  test_ed_facet<e2>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_e2_volatile();

  //============================================================================

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(lfilename + ".hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
