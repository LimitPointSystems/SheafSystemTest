
// $RCSfile: e3_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example e3_x.t.cc
/// Test driver for class e3.

#include "e3.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers_x.impl.h"
//#include "storage_agent.h"


using namespace fiber_bundle;

namespace
{
  void
  test_e3_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<e3_lite>();

    test_volatile_row_dofs<e3_lite>();

    test_volatile_tp_facet<e3_lite>();

    //==========================================================================
    // vd facet
    //==========================================================================

     e3_lite lfiber;

    //operator row_dofs_type& ();

    e3_lite::row_dofs_type& lrow_dofs1 = lfiber;

    //operator const row_dofs_type& () const;

    const e3_lite lfiber_const;
    const e3_lite::row_dofs_type& lrow_dofs3 = lfiber_const;

    //==========================================================================

    //static const tp_lite& static_tp_prototype(int xp);

    const tp_lite& lstatic_tp_prototype0 = e3_lite::static_tp_prototype(0);
    const tp_lite& lstatic_tp_prototype1 = e3_lite::static_tp_prototype(1);
    const tp_lite& lstatic_tp_prototype2 = e3_lite::static_tp_prototype(2);
    const tp_lite& lstatic_tp_prototype3 = e3_lite::static_tp_prototype(3);
    const tp_lite& lstatic_tp_prototype4 = e3_lite::static_tp_prototype(4);

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);
    const tp_lite& ltp_prototype1 = lfiber.tp_prototype(1);
    const tp_lite& ltp_prototype2 = lfiber.tp_prototype(2);
    const tp_lite& ltp_prototype3 = lfiber.tp_prototype(3);
    const tp_lite& ltp_prototype4 = lfiber.tp_prototype(4);

    //static const atp_lite& static_atp_prototype(int xp);

    const atp_lite& lstatic_atp_prototype0 = e3_lite::static_atp_prototype(0);
    const atp_lite& lstatic_atp_prototype1 = e3_lite::static_atp_prototype(1);
    const atp_lite& lstatic_atp_prototype2 = e3_lite::static_atp_prototype(2);
    const atp_lite& lstatic_atp_prototype3 = e3_lite::static_atp_prototype(3);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);
    const atp_lite& latp_prototype1 = lfiber.atp_prototype(1);
    const atp_lite& latp_prototype2 = lfiber.atp_prototype(2);
    const atp_lite& latp_prototype3 = lfiber.atp_prototype(3);

    //static const stp_lite& static_stp_prototype(int xp);

    const stp_lite& lstatic_stp_prototype2 = e3_lite::static_stp_prototype(2);
    const stp_lite& lstatic_stp_prototype3 = e3_lite::static_stp_prototype(3);
    const stp_lite& lstatic_stp_prototype4 = e3_lite::static_stp_prototype(4);

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

  //string filename = filename_from_cmdline(*xargv);

  // Create the namespace.

  //fiber_bundles_namespace lns(filename);
  //lns.get_read_write_access();

  // Run tests.

  test_e3_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
