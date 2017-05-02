
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

/// @example st3_e3.t.cc
/// Unit test driver for class st3_e3.

#include "SheafSystem/st3_e3.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/e3.h"
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
  test_st3_e3_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<st3_e3_lite>();

    test_volatile_row_dofs<st3_e3_lite>();

    test_volatile_class_tp_facet<st3_e3_lite>();

    //==========================================================================

    typedef double value_type;
    typedef st3_e3_row_dofs_type<double> row_dofs_type;
//     typedef symmetric_matrix_3x3<double> matrix_type;

//     //st3_e3_lite(const matrix_type& xmatrix);

//     matrix_type lmat;
//     lmat[0][0] = 1;  lmat[0][1] = 2;  lmat[0][2] = 3;
//                      lmat[1][1] = 4;  lmat[1][2] = 5;
//                                       lmat[2][2] = 6;

//     cout << "lmat = " << endl;
//     cout << lmat << endl;

//     st3_e3_lite lfiber(lmat);
//     const st3_e3_lite lfiber_const(lmat);

//     //st3_e3_lite& operator=(const matrix_type& xmatrix);

//     st3_e3_lite lfiber_assign = lmat;

//     //operator matrix_type& ();

//     matrix_type& lmatrix_type(lfiber);

//     //operator const matrix_type& () const;

//     const matrix_type& lmatrix_type_const(lfiber_const);

    //operator row_dofs_type& ();

    st3_e3_lite lfiber;
    const st3_e3_lite lfiber_const;

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

//     //st3_e3_lite(
//     //  const value_type& xx, const value_type& xy, const value_type& xz,
//     //  const value_type& yy, const value_type& yz, const value_type& zz);

//     const value_type lxx_comp = 11.0;
//     const value_type lxy_comp = 12.0;
//     const value_type lxz_comp = 13.0;
//     const value_type lyy_comp = 22.0;
//     const value_type lyz_comp = 23.0;
//     const value_type lzz_comp = 33.0;

//     st3_e3_lite lfiber2(lxx_comp, lxy_comp, lxz_comp,
//                        lyy_comp, lyz_comp, lzz_comp);

//     //virtual void put_components(const value_type& xx_comp,
//     //                            const value_type& xy_comp,
//     //                            const value_type& xz_comp,
//     //                            const value_type& yy_comp,
//     //                            const value_type& yz_comp,
//     //                            const value_type& zz_comp);

//     lfiber.put_components(lxx_comp, lxy_comp, lxz_comp,
//                           lyy_comp, lyz_comp, lzz_comp);

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

  string lfilename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  // Run tests.

  test_persistent_tensor_type<st3_e3>(lns);

  test_volatile_type<st3_e3>();

  test_tensor_conversions<st3_e3>(lns);

  // Test vd facet:

  test_tensor_vd_facet<st3_e3>(lns);

  // Test atp facet:

  test_stp_facet<st3_e3>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_st3_e3_volatile();

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
