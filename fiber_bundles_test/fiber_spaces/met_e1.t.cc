
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

/// @example met_e1.t.cc
/// Unit test driver for class met_e1.

#include "met_e1.h"

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e1.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "stp_space.h"
#include "test_fibers.impl.h"

using namespace std;
using namespace fiber_bundle;
using namespace fiber_bundle::met_algebra;

namespace
{
  void
  test_met_e1_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<met_e1_lite>();

    test_volatile_class_tp_facet<met_e1_lite>();

    //==========================================================================

    met_e1_lite lfiber(123.0);
    lfiber.put_component(456.0);

    met_e1_lite::value_type lvalue = lfiber.component();

    met_e1_lite::row_dofs_type& lrow_dofs(lfiber);

    const met_e1_lite lfiber_const;

    const met_e1_lite::row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    //met_e1_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const

    met_e1_row_dofs_type<double>* lclone_row_dofs = lrow_dofs.clone(true, true);

    //virtual met_e1_lite* clone(bool xnew_state, bool xauto_access) const

    met_e1_lite* lclone = lfiber.clone(true, true);

    delete lclone_row_dofs; 
    delete lclone; 

    //==========================================================================

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_lite = lfiber.tp_prototype(1);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_lite = lfiber.atp_prototype(1);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_lite = lfiber.stp_prototype(1);

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

  test_persistent_tensor_type<met_e1>(lns);

  test_volatile_type<met_e1>();

  test_tensor_conversions<met_e1>(lns);

  // Test vd facet:

  test_tensor_vd_facet<met_e1>(lns);

  // Test stp facet:

  test_stp_facet<met_e1>(lns);

  // Test met facet:

  test_met_facet<met_e1>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_met_e1_volatile();

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
