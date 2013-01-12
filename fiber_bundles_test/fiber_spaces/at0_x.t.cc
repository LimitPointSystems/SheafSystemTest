

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example at0_x.t.cc
/// Test driver for class at0.

#include "at0.h"

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
  test_at0_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<at0_lite>();

    test_volatile_row_dofs<at0_lite>();

    test_volatile_class_tp_facet<at0_lite>();

    //==========================================================================

    at0_lite lfiber;

    //operator row_dofs_type& ();

    at0_lite::row_dofs_type& lrow_dofs1 = lfiber;

    //operator const row_dofs_type& () const;

    const at0_lite lfiber_const;
    const at0_lite::row_dofs_type& lrow_dofs3 = lfiber_const;

    //==========================================================================

    //static const tp_lite& static_tp_prototype(int xp);

    const tp_lite& lstatic_tp_prototype0 = at0_lite::static_tp_prototype(0);

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);

    //static const atp_lite& static_atp_prototype(int xp);

    const atp_lite& lstatic_atp_prototype0 = at0_lite::static_atp_prototype(0);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);

    //static const stp_lite& static_stp_prototype(int xp);

    const stp_lite& lstatic_stp_prototype0 = at0_lite::static_stp_prototype(0);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype0 = lfiber.stp_prototype(0);

    //==========================================================================

    // Postconditions:

    // Exit:

    return;
  }

  void
  //test_at0_persistent(fiber_bundles_namespace& xns)
  test_at0_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    typedef at0_lite volatile_type;
    typedef at0_row_dofs_type<double> row_dofs_type;

    // at0();

    at0 lfiber;

    // ~at0();

    at0* lfiber_ptr = new at0;
    delete lfiber_ptr;

    // virtual const volatile_type& lite_prototype() const;

    const volatile_type& llite_prototype = lfiber.lite_prototype();

    // virtual volatile_type* lite_type() const;

    ////volatile_type* llite_type = lfiber.lite_type();

    //operator row_dofs_type& ();

    ////row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const at0 lfiber_const;
    ////const row_dofs_type& lrow_dofs_const(lfiber_const);
    
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

  test_at0_volatile();

  test_at0_persistent();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
