
// $RCSfile: atp.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example atp.t.cc
/// Unit test driver for class atp.

#include "atp.h"

#include "assert_contract.h"
#include "at2_e2.h"
#include "atp_space.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers.impl.h"
//#include "storage_agent.h"

using namespace fiber_bundle;

namespace
{

  void
  test_atp_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<atp_lite>();

    test_volatile_class_tp_facet<atp_lite>();

    //==========================================================================

    //atp_lite(const row_dofs_type& xrow_dofs);

    atp_lite::row_dofs_type lrow_dofs;
    atp_lite lfiber(lrow_dofs);


    //atp_lite& operator=(const row_dofs_type& xrow_dofs);

    atp_lite lfiber_assign = lrow_dofs;

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_atp_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<atp, at2_e2>(lns);

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

  test_atp_volatile();
  test_atp_persistent();

  // Postconditions:

  // Exit:

  return 0;
}
