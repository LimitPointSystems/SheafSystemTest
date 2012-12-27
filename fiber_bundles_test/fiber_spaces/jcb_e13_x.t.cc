
// $RCSfile: jcb_e13_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example jcb_e13_x.t.cc
/// Test driver for class jcb_e13.

#include "jcb_e13.h"

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
  test_jcb_e13_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<jcb_e13_lite>();

    //test_volatile_jcb_facet<jcb_e13_lite>();

    //==========================================================================

    jcb_e13_lite lfiber(0.11, 0.21, 0.31);
    lfiber.put_components(0.111, 0.121, 0.131);

    jcb_e13_lite::row_dofs_type& lrow_dofs(lfiber);

    const jcb_e13_lite lfiber_const;

    const jcb_e13_lite::row_dofs_type& lrow_dofs_const(lfiber_const);

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

  test_jcb_e13_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
