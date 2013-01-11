
// $RCSfile: t2.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example t2.t.cc
/// Unit test driver for class t2.

#include "t2.h"

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
  test_t2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<t2_lite>();

    test_volatile_class_tp_facet<t2_lite>();

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_t2_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common_2<t2, t2_e2>(lns);

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

  test_t2_volatile();
  test_t2_persistent();

  // Postconditions:

  // Exit:

  return 0;
}
