

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example tp.t.cc
/// Unit test driver for class tp.

#include "tp.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "t2_e2.h"
#include "test_fibers.impl.h"
#include "tp_space.h"
//#include "storage_agent.h"

using namespace fiber_bundle;

namespace
{
  void
  test_tp_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<tp_lite>();

    test_volatile_class_tp_facet<tp_lite>();

    //==========================================================================

    //tp_lite(const row_dofs_type& xrow_dofs);

    tp_lite::row_dofs_type lrow_dofs;
    tp_lite lfiber(lrow_dofs);


    //tp_lite& operator=(const row_dofs_type& xrow_dofs);

    tp_lite lfiber_assign = lrow_dofs;

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_tp_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<tp, t2_e2>(lns);

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

  test_tp_volatile();
  test_tp_persistent();

  // Postconditions:

  // Exit:

  return 0;
}