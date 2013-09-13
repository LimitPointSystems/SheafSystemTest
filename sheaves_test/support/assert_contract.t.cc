
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// Unit test driver for class assert_contract.

#include "assert_contract.h"
#include "std_iostream.h"
#include "std_stdexcept.h"

using namespace sheaf;

int
main()
{
   // Catch the exception thrown so that CMake CTest doesn't complain about an error 

  try
  {
    cerr << endl;
    cerr << "Test not_implemented()" << endl;
    not_implemented();
  }
  catch (std::logic_error& le)
  {
    cerr << "Caught a logic_error: " << le.what () << endl;
    cerr << endl;
  }

  try
  {
    cerr << endl;
    cerr << "Test is_abstract()" << endl;
    is_abstract();
  }
  catch (std::logic_error& le)
  {
    cerr << "Caught a logic_error: " << le.what () << endl;
    cerr << endl;
  }

  try
  {
    cerr << endl;
    cerr << "Test required(false)" << endl;
    require(false);
  }
  catch (std::logic_error& le)
  {
    cerr << "Caught a logic_error: " << le.what () << endl;
    cerr << endl;
  }

  try
  {
    cerr << endl;
    cerr << "Test ensure(false)" << endl;
    ensure(false);
  }
  catch (std::logic_error& le)
  {
    cerr << "Caught a logic_error: " << le.what () << endl;
    cerr << endl;
  }

  // @todo Implement remaining conditions.

  return 0;
}


