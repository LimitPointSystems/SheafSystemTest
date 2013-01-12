

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example e1_x.t.cc
/// Test driver for class e1.

#include "e1.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers.impl.h"
//#include "storage_agent.h"


using namespace fiber_bundle;

namespace
{

  void
  test_e1_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<e1_lite>();

    test_volatile_row_dofs<e1_lite>();

    test_volatile_class_tp_facet<e1_lite>();

    //==========================================================================
    // vd facet
    //==========================================================================

    e1_lite lfiber;

    //operator row_dofs_type& ();

    e1_lite::row_dofs_type& lrow_dofs1 = lfiber;

    //operator const row_dofs_type& () const;

    const e1_lite lfiber_const;
    const e1_lite::row_dofs_type& lrow_dofs3 = lfiber_const;

    //==========================================================================

    //static const tp_lite& static_tp_prototype(int xp);

    const tp_lite& lstatic_tp_prototype0 = e1_lite::static_tp_prototype(0);
    const tp_lite& lstatic_tp_prototype1 = e1_lite::static_tp_prototype(1);

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);
    const tp_lite& ltp_prototype1 = lfiber.tp_prototype(1);

    //static const atp_lite& static_atp_prototype(int xp);

    const atp_lite& lstatic_atp_prototype0 = e1_lite::static_atp_prototype(0);
    const atp_lite& lstatic_atp_prototype1 = e1_lite::static_atp_prototype(1);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);
    const atp_lite& latp_prototype1 = lfiber.atp_prototype(1);

    //static const stp_lite& static_stp_prototype(int xp);

    const stp_lite& lstatic_stp_prototype0 = e1_lite::static_stp_prototype(0);
    const stp_lite& lstatic_stp_prototype1 = e1_lite::static_stp_prototype(1);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype0 = lfiber.stp_prototype(0);
    const stp_lite& lstp_prototype1 = lfiber.stp_prototype(1);

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

  test_e1_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
