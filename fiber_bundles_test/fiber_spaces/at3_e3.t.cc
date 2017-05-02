
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

/// @example at3_e3.t.cc
/// Test driver for class at3_e3.

#include "SheafSystem/at3_e3.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/at3.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_fibers.impl.h"

using namespace std;
using namespace fiber_bundle;
using namespace fiber_bundle::atp_algebra;

namespace
{
  void
  test_at3_e3_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<at3_e3_lite>();

    test_volatile_row_dofs<at3_e3_lite>();

    test_volatile_class_tp_facet<at3_e3_lite>();

    //==========================================================================

    typedef double value_type;
    typedef at3_e3_row_dofs_type<double> row_dofs_type;

    at3_e3_lite lfiber;
    const at3_e3_lite lfiber_const;

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //at3_e3_lite(const value_type& xy);

    value_type lvalue = 123.456;
    at3_e3_lite lfiber2(lvalue);

    //virtual void put_component(value_type xy);

    lfiber.put_components(lvalue);


    //==========================================================================

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);
    const tp_lite& ltp_prototype1 = lfiber.tp_prototype(1);
    const tp_lite& ltp_prototype2 = lfiber.tp_prototype(2);
    const tp_lite& ltp_prototype3 = lfiber.tp_prototype(3);
    const tp_lite& ltp_prototype4 = lfiber.tp_prototype(4);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);
    const atp_lite& latp_prototype1 = lfiber.atp_prototype(1);
    const atp_lite& latp_prototype2 = lfiber.atp_prototype(2);
    const atp_lite& latp_prototype3 = lfiber.atp_prototype(3);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype2 = lfiber.stp_prototype(2);
    const stp_lite& lstp_prototype3 = lfiber.stp_prototype(3);
    const stp_lite& lstp_prototype4 = lfiber.stp_prototype(4);

    //==========================================================================

    // Hodge star operator functions not exercized elsewhere.

    at3_e3_lite lat3_e3_lite(123.0);

    //at0_lite* star(const at3_e3_lite& x0);

    at0_lite* lstar_at0 = star(lat3_e3_lite);

    delete lstar_at0;

    //==========================================================================

    //virtual int index_for_ijk(int xi, int xj, int xk) const;

    int lindex = lfiber.index_for_ijk(0, 0, 0);

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

  string filename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace lns(filename);
  lns.get_read_write_access();

  // Run tests.

  test_persistent_tensor_type<at3_e3>(lns);

  test_volatile_type<at3_e3>();

  test_tensor_conversions<at3_e3>(lns);

  // Test vd facet:

  test_tensor_vd_facet<at3_e3>(lns);

  // Test atp facet:

  test_hook_product<at3_e3, e3, at2_e3>(lns);

  test_star_operator<at3_e3, at0>(lns);

  //@issue: What is the vector_space_type for at0?
  test_star_operator<at0, at3_e3>(lns);

  test_wedge_product<at2_e3, e3, at3_e3>(lns);

  //============================================================================

  // Test class member functions and other not test above.

  test_at3_e3_volatile();

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
