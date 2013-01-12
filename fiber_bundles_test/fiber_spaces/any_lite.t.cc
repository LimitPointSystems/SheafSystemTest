

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test driver for class any_lite.

#include "any_lite.h"

#include "assert_contract.h"
#include "std_iostream.h"


using namespace fiber_bundle;

namespace
{
  void
  test_any_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    //$$SCRIBBLE: There is not much we can test of class any_lite
    //            because it is abstract. 

    //static const string& static_class_name();

    const string& lstatic_class_name = any_lite::static_class_name();

    cout << "lstatic_class_name = " << lstatic_class_name << endl;

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

  test_any_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
