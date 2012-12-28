// $RCSfile: error_message.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:41:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Unit test driver for class error_message.

#include "error_message.h"
#include "assert_contract.h"
#include "std_iostream.h"
#include "std_stdexcept.h"

using namespace sheaf;

int
main()
{

  // Test information message:

  error_message info(error_message::INFORMATION,
                     "error_message.t::main",
                     "testing information message.");
  info.post();

  // Test information  macro.

  post_information_message("testing information macro");

  // Test warning message.

  error_message warn(error_message::WARNING,
                     "error_message.t::main",
                     "testing warning message.");

  warn.post();

  // Test warning macro.

  post_warning_message("testing warning macro.");

  // Test severe error message.

  error_message severe(error_message::SEVERE_ERROR,
                       "error_message.t::main",
                       "testing severe error message.");

  severe.post();

  // Test severe error macro.

  post_severe_error_message("testing severe error macro.");

  // Test fatal error message; exit suppressed.

  error_message fatal(error_message::FATAL_ERROR,
                      __FILE__,
                      __LINE__,
                      "testing fatal error message. Exit suppressed.");

  fatal.post();

  // Test severe error macro; should throw a logic_error exception.

  // Catch the exception thrown so that CMake CTest doesn't complain about an error 

  try
  {
    post_fatal_error_message("testing fatal error macro. Should throw a logic_error.");
  }
  catch (std::logic_error& le)
  {
    cerr << endl;
    cerr << "Caught a logic_error: " << le.what () << endl;
    cerr << endl;
  }

  return 0;
}


