
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

/// @example met_e3.t.cc
/// Unit test driver for class met_e3.

#include "SheafSystem/met_e3.h"

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
using namespace fiber_bundle::met_algebra;

namespace
{
  void
  test_met_e3_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<met_e3_lite>();

    test_volatile_class_tp_facet<met_e3_lite>();

    //==========================================================================

    met_e3_lite lfiber(11.0, 12.0, 13.0, 22.0, 23.0, 33.0);
    lfiber.put_components(111.0, 112.0, 113.0, 122.0, 123.0, 133.0);

    //met_e3_lite::value_type lvalue = lfiber.component();

    met_e3_lite::row_dofs_type& lrow_dofs(lfiber);

    const met_e3_lite lfiber_const;

    const met_e3_lite::row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    typedef double value_type;
    typedef met_e3_row_dofs_type<double> row_dofs_type;
    typedef symmetric_matrix_3x3<double> matrix_type;

    //met_e3_lite(const matrix_type& xmatrix);

    matrix_type lmat;
    lmat[0][0] = 1;  lmat[0][1] = 2;  lmat[0][2] = 3;
                     lmat[1][1] = 4;  lmat[1][2] = 5;
                                      lmat[2][2] = 6;

    cout << "lmat = " << endl;
    cout << lmat << endl;

    met_e3_lite lfiber2(lmat);
    const met_e3_lite lfiber_const2(lmat);

    //met_e3_lite& operator=(const matrix_type& xmatrix);

    met_e3_lite lfiber_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber2);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const2);

    //==========================================================================

    //met_e3_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const

    row_dofs_type* lclone_row_dofs = lrow_dofs.clone(true, true);

    //virtual met_e3_lite* clone(bool xnew_state, bool xauto_access) const

    met_e3_lite* lclone = lfiber.clone(true, true);

    delete lclone_row_dofs; 
    delete lclone; 

    //==========================================================================
 
    //operator met_e3_row_dofs_type<T>& () const

    met_e3_row_dofs_type<double>& lrow_dofs2(lmat);

    //==========================================================================

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_lite = lfiber.tp_prototype(2);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_lite = lfiber.atp_prototype(2);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_lite = lfiber.stp_prototype(2);

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

  test_persistent_tensor_type<met_e3>(lns);

  test_volatile_type<met_e3>();

  test_tensor_conversions<met_e3>(lns);

  // Test vd facet:

  test_tensor_vd_facet<met_e3>(lns);

  // Test tp facet:

  test_tensor<met_e3, e3, t3_e3>(lns);

  // Test stp facet:

  test_stp_facet<met_e3>(lns);

  // Test st2 facet:

  test_st2_facet<met_e3>(lns);

  // Test met facet:

  test_met_facet<met_e3>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_met_e3_volatile();

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
