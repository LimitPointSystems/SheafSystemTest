
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

/// @example t4_e2.t.cc
/// Unit test driver for class t4_e2.

#include "t4_e2.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e2.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "test_fibers.impl.h"

using namespace std;
using namespace fiber_bundle;
using namespace fiber_bundle::tp_algebra;

namespace
{
  void
  test_t4_e2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<t4_e2_lite>();

    test_volatile_row_dofs<t4_e2_lite>();

    test_volatile_class_tp_facet<t4_e2_lite>();

    //==========================================================================

    typedef double value_type;
    typedef t4_e2_row_dofs_type<double> row_dofs_type;

    t4_e2_lite lfiber;
    const t4_e2_lite lfiber_const;

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    // Other constructors and assignment operators:

    //t4_e2_lite(const st4_e2_lite& xother);

    st4_e2_lite lfiber_st4_e2;
    t4_e2_lite lfiber4(lfiber_st4_e2);

    //t4_e2_lite& operator=(const st4_e2_lite& xother);

    t4_e2_lite lfiber4_assign = lfiber_st4_e2;

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

    // Sym operator functions not exercized elsewhere.

    t4_e2_lite lt4_e2_lite;
    int ld = lt4_e2_lite.d();
    for(int i=0; i<ld; ++i)
    {
      lt4_e2_lite.put_component(i, 100+i); 
    }

    st4_e2_lite lresult;

    //void sym(const t4_e2_lite& x0, st4_e2_lite& xresult);

    sym(lt4_e2_lite, lresult);

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

  test_persistent_tensor_type<t4_e2>(lns);

  test_volatile_type<t4_e2>();

  test_tensor_conversions<t4_e2>(lns);

  // Test vd facet:

  test_tensor_vd_facet<t4_e2>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_t4_e2_volatile();

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
