
// $RCSfile: jcb_e33_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example jcb_e33_x.t.cc
/// Test driver for class jcb_e33.

#include "jcb_e33.h"

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
  test_jcb_e33_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<jcb_e33_lite>();

    //test_volatile_jcb_facet<jcb_e33_lite>();

    //==========================================================================

    jcb_e33_lite lfiber(0.11, 0.12, 0.13, 0.21, 0.22, 0.23, 0.31, 0.32, 0.33);
    lfiber.put_components(0.111, 0.112, 0.113,
                          0.121, 0.122, 0.123,
                          0.131, 0.132, 0.133);

    jcb_e33_lite::row_dofs_type& lrow_dofs(lfiber);

    const jcb_e33_lite lfiber_const;

    const jcb_e33_lite::row_dofs_type& lrow_dofs_const(lfiber_const);

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

  test_jcb_e33_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
