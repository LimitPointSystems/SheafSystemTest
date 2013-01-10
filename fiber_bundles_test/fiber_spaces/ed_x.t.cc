
// $RCSfile: ed_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example ed_x.t.cc
/// Test driver for class ed.

#include "ed.h"
#include "e1.h"
#include "at1_space.h"

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
  test_ed_volatile()
  {
    // Preconditions:

    // Body:

   //==========================================================================

    test_volatile_common<ed_lite>();

    //test_volatile_row_dofs<ed_lite>();

    test_volatile_tp_facet<ed_lite>();

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_ed_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<ed, e1>(lns);

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

  test_ed_volatile();
  test_ed_persistent();

  // Postconditions:

  // Exit:

  return 0;
}
