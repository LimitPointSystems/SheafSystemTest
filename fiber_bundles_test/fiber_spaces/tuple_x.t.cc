
// $RCSfile: tuple_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example tuple_x.t.cc
/// Test driver for class tuple.

#include "tuple.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "test_fibers.impl.h"
//#include "storage_agent.h"
//#include "tuple_space.h"

using namespace fiber_bundle;

namespace
{
  void
  test_tuple_volatile()
  {
    //==========================================================================
    // tuple facet
    //==========================================================================

    //tuple_lite();

    tuple_lite ltuple;

    //tuple_lite(const tuple_lite& xother);

    tuple_lite ltuple_copy(ltuple);

    //tuple_lite& operator=(const tuple_lite& xother);

    tuple_lite ltuple_assign = ltuple;

    //virtual ~tuple_lite();

    //virtual int factor_ct() const = 0;

    //==========================================================================
    // abstract_poset_member facet
    //==========================================================================

    //==========================================================================
    // any facet
    //==========================================================================


  }

} // end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  //string filename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace ns(filename);
  ns.get_read_write_access();

  // Run tests.

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf" + ".hdf");
  //write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
