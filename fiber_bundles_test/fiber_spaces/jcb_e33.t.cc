
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

/// @example jcb_e33.t.cc
/// Unit test driver for class jcb_e33.

#include "SheafSystem/jcb_e33.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/e3.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/jcb_space.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_fibers.impl.h"

using namespace std;
using namespace fiber_bundle;
using namespace fiber_bundle::jcb_algebra;

namespace
{
  void
  test_jcb_e33_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<jcb_e33_lite>();

    //test_volatile_jcb_facet<jcb_e33_lite>();

    //==========================================================================

    typedef double value_type;
    typedef jcb_e33_row_dofs_type<double> row_dofs_type;
    typedef general_matrix_3x3<double> matrix_type;

    jcb_e33_lite lfiber(0.11, 0.12, 0.13, 0.21, 0.22, 0.23, 0.31, 0.32, 0.33);
    lfiber.put_components(0.111, 0.112, 0.113,
                          0.121, 0.122, 0.123,
                          0.131, 0.132, 0.133);

    row_dofs_type& lrow_dofs(lfiber);

    const jcb_e33_lite lfiber_const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    matrix_type lmat;
    lmat[0][0] =  10; lmat[0][1] = -10; lmat[0][2] =   0;
    lmat[1][0] = -10; lmat[1][1] =  20; lmat[1][2] = -10;
    lmat[2][0] =   0; lmat[2][1] =   0; lmat[2][2] =  10;

    cout << "lmat = " << endl;
    cout << lmat << endl;

    //jcb_e33_lite(const matrix_type& xmatrix);

    jcb_e33_lite lfiber2(lmat);
    const jcb_e33_lite lfiber2_const(lmat);

    //jcb_e33_lite& operator=(const matrix_type& xmatrix);

    jcb_e33_lite lfiber2_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber2);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const);

    //==========================================================================

    //jcb_e33_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const

    row_dofs_type* lclone_row_dofs = lrow_dofs.clone(true, true);

    //virtual jcb_e33_lite* clone(bool xnew_state, bool xauto_access) const

    jcb_e33_lite* lclone = lfiber.clone(true, true);

    delete lclone_row_dofs; 
    delete lclone;

   //==========================================================================

    //operator jcb_e33_row_dofs_type<T>& () const

    jcb_e33_row_dofs_type<double>& lrow_dofs3(lmat);

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

  test_persistent_jacobian_type<jcb_e33>(lns);

  test_volatile_type<jcb_e33>();

  test_jacobian_conversions<jcb_e33>(lns);

  // Test vd facet:

  test_jacobian_vd_facet<jcb_e33>(lns);

  // Test jcb facet:

  test_jcb_facet<jcb_e33>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_jcb_e33_volatile();

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
