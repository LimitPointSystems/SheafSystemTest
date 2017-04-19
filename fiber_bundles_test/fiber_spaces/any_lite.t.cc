
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

/// Unit test driver for class any_lite.

#include "SheafSystem/any_lite.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystemTest/test_utils.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  // Simple class derived from any_lite to enable access to
  // the member functions of any_lite for testing.

  class any_lite_derived : public any_lite
  {
  public:
    any_lite_derived() : any_lite() {}

    ~any_lite_derived() {}

    const string& class_name() const { return any_lite::class_name(); }

    //$$SCRIBBLE: any_lite::clone() cannot be called (is_abstract())
    //            without terminating.
    //any_lite_derived* clone() const {return new any_lite_derived; }

    bool is_ancestor_of(const any_lite_derived& xother) const
    {
      return any_lite::is_ancestor_of(xother);
    }

    bool is_same_type(const any_lite_derived& xother) const
    {
      return any_lite::is_same_type(xother);
    }
  };

} // end unnamed namespace


namespace
{
  void
  test_any_volatile()
  {
    // Preconditions:

    // Body:

    print_header("Begin testing any_lite");

    //==========================================================================

    //static const string& static_class_name();

    const string& lstatic_class_name = any_lite::static_class_name();

    cout << "lstatic_class_name = " << lstatic_class_name << endl;

    any_lite_derived*lany_lite_derived = new any_lite_derived;

    const string& lclass_name = lany_lite_derived->class_name();

    cout << "lclass_name = " << lclass_name << endl;

    cout << boolalpha;

    bool lis_ancestor_of =
      lany_lite_derived->is_ancestor_of(*lany_lite_derived);

    cout << "lis_ancestor_of = " << lis_ancestor_of << endl;

    bool lis_same_type = lany_lite_derived->is_same_type(*lany_lite_derived);

    cout << "lis_same_type = " << lis_same_type << endl;

    delete lany_lite_derived;

    //==========================================================================

    print_footer("End testing any_lite");

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
