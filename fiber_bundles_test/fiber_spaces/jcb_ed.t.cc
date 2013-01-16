

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example jcb_ed.t.cc
/// Unit test driver for class jcb_ed.

#include "jcb_ed.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "jcb_e13.h"
#include "jcb_space.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers.impl.h"
//#include "storage_agent.h"


using namespace fiber_bundle;

namespace
{
  void
  test_jcb_ed_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<jcb_ed_lite>();

    //test_volatile_jcb_facet<jcb_ed_lite>();

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_jcb_ed_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common<jcb_ed, jcb_e13>(lns);

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

  test_jcb_ed_volatile();
  test_jcb_ed_persistent();

  // Postconditions:

  // Exit:

  return 0;
}