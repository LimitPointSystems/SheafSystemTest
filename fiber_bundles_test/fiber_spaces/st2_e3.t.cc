
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

/// @example st2_e3.t.cc
/// Unit test driver for class st2_e3.

#include "st2_e3.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "st2_e3.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "stp_space.h"
#include "test_fibers.impl.h"

using namespace std;
using namespace fiber_bundle;
using namespace fiber_bundle::st2_algebra;

namespace
{
  void
  test_st2_e3_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<st2_e3_lite>();

    test_volatile_row_dofs<st2_e3_lite>();

    test_volatile_class_tp_facet<st2_e3_lite>();

    //==========================================================================

    typedef double value_type;
    typedef st2_e3_row_dofs_type<double> row_dofs_type;
    typedef symmetric_matrix_3x3<double> matrix_type;

    //st2_e3_lite(const matrix_type& xmatrix);

    matrix_type lmat;
    lmat[0][0] = 1;  lmat[0][1] = 2;  lmat[0][2] = 3;
                     lmat[1][1] = 4;  lmat[1][2] = 5;
                                      lmat[2][2] = 6;

    cout << "lmat = " << endl;
    cout << lmat << endl;

    st2_e3_lite lfiber(lmat);
    const st2_e3_lite lfiber_const(lmat);

    //st2_e3_lite& operator=(const matrix_type& xmatrix);

    st2_e3_lite lfiber_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const);

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //st2_e3_lite(
    //  const value_type& xx, const value_type& xy, const value_type& xz,
    //  const value_type& yy, const value_type& yz, const value_type& zz);

    const value_type lxx_comp = 11.0;
    const value_type lxy_comp = 12.0;
    const value_type lxz_comp = 13.0;
    const value_type lyy_comp = 22.0;
    const value_type lyz_comp = 23.0;
    const value_type lzz_comp = 33.0;

    st2_e3_lite lfiber2(lxx_comp, lxy_comp, lxz_comp,
                       lyy_comp, lyz_comp, lzz_comp);

    //virtual void put_components(const value_type& xx_comp,
    //                            const value_type& xy_comp,
    //                            const value_type& xz_comp,
    //                            const value_type& yy_comp,
    //                            const value_type& yz_comp,
    //                            const value_type& zz_comp);

    lfiber.put_components(lxx_comp, lxy_comp, lxz_comp,
                          lyy_comp, lyz_comp, lzz_comp);

    //==========================================================================

    //operator st2_e3_row_dofs_type<T>& () const

    st2_e3_row_dofs_type<double>& lrow_dofs2(lmat);

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

    //template <> void to_principal_axes(
    //  const st2_e3_lite& xlite, gl3_lite& xtransform, st2_e3_lite& xresult);

    gl3_lite ltransform;
    st2_e3_lite lresult;

    st2_e3_lite llite(11.0, 12.0, 13.0, 22.0, 23.0, 33.0);

    to_principal_axes(llite, ltransform, lresult);

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

  test_persistent_tensor_type<st2_e3>(lns);

  test_volatile_type<st2_e3>();

  test_tensor_conversions<st2_e3>(lns);

  // Test vd facet:

  test_tensor_vd_facet<st2_e3>(lns);

  // Test tp facet:

  test_tensor<st2_e3, e3, t3_e3>(lns);

  // Test stp facet:

  test_stp_facet<st2_e3>(lns);

  // Test st2 facet:

  test_st2_facet<st2_e3>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_st2_e3_volatile();

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
