
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

/// @example vd.t.cc
/// Unit test driver for class vd.

#include "vd.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "at1_space.h"
#include "e1.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers.impl.h"
#include "vd_space.h"
//#include "ComLimitPoint/sheaf/storage_agent.h"


using namespace std;
using namespace fiber_bundle;
using namespace fiber_bundle::vd_algebra;

namespace
{
  void
  test_volatile_tolerance_comparison()
  {
    // Preconditions:

    // Body:

    //==========================================================================
    // vector algebra: tolerance comparison
    //==========================================================================

    print_header("Begin testing vector algebra: tolerance comparison");

    vd_lite lvd0;
    vd_lite lvd1;
    vd_lite lvd_tolerance;
    double ltolerance = 0.00001;

    cout << boolalpha;

    //bool a_eql(const vd_lite& x0, const vd_lite& x1);

    bool la_eql = a_eql(lvd0, lvd1);
    cout << "la_eql = " << la_eql << endl;
  
    //bool a_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);

    bool la_eql_tol0 = a_eql(lvd0, lvd1, ltolerance);
    cout << "la_eql_tol0 = " << la_eql_tol0 << endl;

    //bool a_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);

    bool la_eql_tol1 = a_eql(lvd0, lvd1, lvd_tolerance);
    cout << "la_eql_tol1 = " << la_eql_tol1 << endl;

    //bool r_eql(const vd_lite& x0, const vd_lite& x1);

    bool lr_eql = r_eql(lvd0, lvd1);
    cout << "lr_eql = " << lr_eql << endl;
  
    //bool r_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);

    bool lr_eql_tol0 = r_eql(lvd0, lvd1, ltolerance);
    cout << "lr_eql_tol0 = " << lr_eql_tol0 << endl;

    //bool r_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);

    bool lr_eql_tol1 = r_eql(lvd0, lvd1, lvd_tolerance);
    cout << "lr_eql_tol1 = " << lr_eql_tol1 << endl;


    //bool c_eql(const vd_lite& x0, const vd_lite& x1);

    bool lc_eql = c_eql(lvd0, lvd1);
    cout << "lc_eql = " << lc_eql << endl;
  
    //bool c_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);

    bool lc_eql_tol0 = c_eql(lvd0, lvd1, ltolerance);
    cout << "lc_eql_tol0 = " << lc_eql_tol0 << endl;

    //bool c_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);

    bool lc_eql_tol1 = c_eql(lvd0, lvd1, lvd_tolerance);
    cout << "lc_eql_tol1 = " << lc_eql_tol1 << endl;

    print_footer("End testing vector algebra: tolerance comparison");

    // Postconditions:

    // Exit:

    return;
  }

  void
  test_vd_volatile()
  {
    // Preconditions:

    // Body:

    test_volatile_common<vd_lite>();

    test_volatile_tolerance_comparison();

    //==========================================================================
    // vd facet
    //==========================================================================

    vd_lite lvd;

    //vd_lite& operator=(const value_type& xvalue);

    vd_lite::value_type lvalue = 123.0;
    lvd = lvalue;

    //bool operator==(const value_type& xvalue) const;

    bool leqeq = (lvd == lvalue);

    //virtual value_type& operator[] (int xindex);

    //virtual const value_type& operator[] (int xindex) const;

    //==========================================================================

    //static const tp_lite& static_tp_prototype(int xp);

    const tp_lite& lstatic_tp_prototype = vd_lite::static_tp_prototype(2);

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype = lvd.tp_prototype(2);

    //static const atp_lite& static_atp_prototype(int xp);

    const atp_lite& lstatic_atp_prototype = vd_lite::static_atp_prototype(2);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype = lvd.atp_prototype(2);

    //static const stp_lite& static_stp_prototype(int xp);

    const stp_lite& lstatic_stp_prototype = vd_lite::static_stp_prototype(2);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype = lvd.stp_prototype(2);

    //==========================================================================

    //$$SCRIBBLE: There are other vector operations which are not tested for
    //            vd_lite.  They should probably be tested in the templated
    //            tests in test_fibers.

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_vd_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<vd, e1>(lns);

    // Write the namespace to standard out.

    //cout << lns << endl;

    // Write the namespace to a file.

    //storage_agent write_agent("test_namespace.hdf");
    //write_agent.write_entire(lns);

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

  // Run tests.

  test_vd_volatile();
  test_vd_persistent();

  // Postconditions:

  // Exit:

  return 0;
}
