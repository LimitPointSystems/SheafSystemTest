
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

/// @example t2_e2.t.cc
/// Unit test driver for class t2_e2.

#include "SheafSystem/t2_e2.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/at2_e2.h"
#include "SheafSystem/atp_space.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/st2_e2.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/stp_space.h"
#include "SheafSystemTest/test_fibers.impl.h"
#include "SheafSystem/tp_space.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  void
  test_t2_e2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<t2_e2_lite>();

    test_volatile_row_dofs<t2_e2_lite>();

    test_volatile_class_tp_facet<t2_e2_lite>();

    //==========================================================================

    typedef double value_type;
    typedef t2_e2_row_dofs_type<double> row_dofs_type;
    typedef general_matrix_2x2<double> matrix_type;

    //t2_e2_lite(const matrix_type& xmatrix);

    matrix_type lmat;
    lmat[0][0] =  4;  lmat[0][1] = -2; 
    lmat[1][0] = -2;  lmat[1][1] =  3; 
 
    cout << "lmat = " << endl;
    cout << lmat << endl;

    t2_e2_lite lfiber(lmat);
    const t2_e2_lite lfiber_const(lmat);

    //t2_e2_lite& operator=(const matrix_type& xmatrix);

    t2_e2_lite lfiber_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const);

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    //t2_e2_lite(const value_type& xx_comp,
    //           const value_type& xy_comp,
    //           const value_type& yx_comp,
    //           const value_type& yy_comp);

    value_type lxx_comp = 11.0;
    value_type lxy_comp = 12.0;
    value_type lyx_comp = 21.0;
    value_type lyy_comp = 22.0;

    t2_e2_lite lfiber2(lxx_comp, lxy_comp, lyx_comp, lyy_comp);

    //virtual void put_components(const value_type& xx_comp,
    //                            const value_type& xy_comp,
    //                            const value_type& yx_comp,
    //                            const value_type& yy_comp);

    lfiber.put_components(lxx_comp, lxy_comp, lyx_comp, lyy_comp);

    //==========================================================================

    // Other constructors and assignment operators:

    //t2_e2_lite(const at2_e2_lite& xother);

    at2_e2_lite lfiber_at2_e2;
    t2_e2_lite lfiber3(lfiber_at2_e2);

    //t2_e2_lite& operator=(const at2_e2_lite& xother);

    t2_e2_lite lfiber3_assign = lfiber_at2_e2;

    //t2_e2_lite(const st2_e2_lite& xother);

    st2_e2_lite lfiber_st2_e2;
     t2_e2_lite lfiber4(lfiber_st2_e2);

    //t2_e2_lite& operator=(const st2_e2_lite& xother);

    t2_e2_lite lfiber4_assign = lfiber_st2_e2;

    //==========================================================================

    //operator t02_e2_row_dofs_type<T>& () const

    t02_e2_row_dofs_type<double>& lrow_dofs3(lmat);

   //operator t11_e2_row_dofs_type<T>& () const

    t11_e2_row_dofs_type<double>& lrow_dofs4(lmat);

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

  test_persistent_tensor_type<t2_e2>(lns);

  test_volatile_type<t2_e2>();

  test_tensor_conversions<t2_e2>(lns);

  // Test vd facet:

  test_tensor_vd_facet<t2_e2>(lns);

  // Test tp facet:
 
  test_tp_facet<t2_e2>(lns);

  test_tensor<e2, e2, t2_e2>(lns);

  test_contract<t2_e2, at0>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_t2_e2_volatile();

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
