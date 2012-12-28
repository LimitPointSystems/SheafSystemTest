
// $RCSfile: met_e1_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example met_e1_x.t.cc
/// Test driver for class met_e1.

#include "met_e1.h"

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
  test_met_e1_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<met_e1_lite>();

    test_volatile_tp_facet<met_e1_lite>();

    //==========================================================================

    met_e1_lite lfiber(123.0);
    lfiber.put_component(456.0);

    met_e1_lite::value_type lvalue = lfiber.component();

    met_e1_lite::row_dofs_type& lrow_dofs(lfiber);

    const met_e1_lite lfiber_const;

    const met_e1_lite::row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    //met_e1_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const

    met_e1_row_dofs_type<double>* lclone_row_dofs = lrow_dofs.clone(true, true);

    //virtual met_e1_lite* clone(bool xnew_state, bool xauto_access) const

    met_e1_lite* lclone = lfiber.clone(true, true);

    delete lclone_row_dofs; 
    delete lclone; 

    //==========================================================================

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_lite = lfiber.tp_prototype(1);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_lite = lfiber.atp_prototype(1);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_lite = lfiber.stp_prototype(1);

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

  test_met_e1_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
