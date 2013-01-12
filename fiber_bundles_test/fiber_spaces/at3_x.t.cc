

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example at3_x.t.cc
/// Test driver for class at3.

#include "at3.h"
#include "at3_e3.h"
#include "atp_space.h"

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
  test_at3_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<at3_lite>();

    test_volatile_class_tp_facet<at3_lite>();

    //==========================================================================

    //at3_lite(const row_dofs_type& xrow_dofs);

     at3_lite::row_dofs_type lrow_dofs;
     at3_lite lfiber(lrow_dofs);


     //at3_lite& operator=(const row_dofs_type& xrow_dofs);

     at3_lite lfiber_assign = lrow_dofs;

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_at3_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<at3, at3_e3>(lns);

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

  test_at3_volatile();
  test_at3_persistent();

  // Postconditions:

  // Exit:

  return 0;
}
