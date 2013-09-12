
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

/// @example e4.t.cc
/// Unit test driver for class e4.

#include "e4.h"

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"

using namespace fiber_bundle;

namespace
{
  void
  test_e4_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<e4_lite>();

    test_volatile_row_dofs<e4_lite>();

    test_volatile_class_tp_facet<e4_lite>();

    //==========================================================================
    // vd facet
    //==========================================================================

     e4_lite lfiber;

    //operator row_dofs_type& ();

    e4_lite::row_dofs_type& lrow_dofs1 = lfiber;

    //operator const row_dofs_type& () const;

    const e4_lite lfiber_const;
    const e4_lite::row_dofs_type& lrow_dofs3 = lfiber_const;

    //==========================================================================

    //static const tp_lite& static_tp_prototype(int xp);

    const tp_lite& lstatic_tp_prototype0 = e4_lite::static_tp_prototype(0);
    const tp_lite& lstatic_tp_prototype1 = e4_lite::static_tp_prototype(1);

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);
    const tp_lite& ltp_prototype1 = lfiber.tp_prototype(1);

    //static const atp_lite& static_atp_prototype(int xp);

    const atp_lite& lstatic_atp_prototype0 = e4_lite::static_atp_prototype(0);
    const atp_lite& lstatic_atp_prototype1 = e4_lite::static_atp_prototype(1);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);
    const atp_lite& latp_prototype1 = lfiber.atp_prototype(1);

    //static const stp_lite& static_stp_prototype(int xp);

    const stp_lite& lstatic_stp_prototype2 = e4_lite::static_stp_prototype(2);
    const stp_lite& lstatic_stp_prototype3 = e4_lite::static_stp_prototype(3);
    const stp_lite& lstatic_stp_prototype4 = e4_lite::static_stp_prototype(4);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype2 = lfiber.stp_prototype(2);
    const stp_lite& lstp_prototype3 = lfiber.stp_prototype(3);
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

  test_persistent_vector_type<e4>(lns);

  test_volatile_type<e4>();

  test_vector_conversions<e4>(lns);

  // Test vd facet:

  test_vector_vd_facet<e4>(lns);

  // Test ed facet:

  test_ed_facet<e4>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_e4_volatile();

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
