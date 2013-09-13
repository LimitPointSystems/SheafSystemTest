
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

/// @file
/// Implementation for test_fibers non template functions.

#include "test_fibers.impl.h"

#include "at0_space.h"
#include "at1_space.h"
#include "std_iostream.h"
#include "test_utils.h"

#include "gln_space.h"

using namespace fiber_bundle::e3_algebra;

///
string
fiber_bundle::
create_vector_space_name(const string& xvector_class_name)
{
  // Preconditions:

  // Body:

  // We have to make up different names (in general) for the vector spaces
  // each time this function is called. So we'll just add "_space#" to
  // the end of the names with "#" incremented on very call.

  static int lname_suffix = -1;
  lname_suffix++;
  static ostringstream lname;

  lname.str("");
  lname << xvector_class_name << "_space_" << lname_suffix;

  string result = lname.str();

  // Postconditions:

  // Exit:

  return result;
}

using namespace fiber_bundle; // Workaround for MS C++ bug.

///
void
fiber_bundle::
create_host_name(const string& xbase_name, string& xresult)
{
  // Preconditions:

  // Body:

  // We have to make up different names (in general) for the hosts
  // each time this function is called. So we'll just add "_#" to
  // the end of the names with "#" incremented on very call.

  static int lname_suffix = -1;
  lname_suffix++;
  static ostringstream lname;

  lname.str("");
  lname << xbase_name << "_" << lname_suffix;

  xresult = lname.str();

  // Postconditions:

  // Exit:  
}


//==============================================================================
// E3 FACET
//==============================================================================

///
void
fiber_bundle::
test_e3_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  // Body:

  print_header("Testing e3 facet:");

  test_volatile_e3_facet();
  test_persistent_e3_facet(xns);

  // Postconditions:

  // Exit:
}

///
void
fiber_bundle::
test_volatile_e3_facet()
{
  // Preconditions:

  // Body:

  print_subheader("Testing volatile type \"e3_lite\"");

  e3_lite test1(1, 2, 3);
  cout << "e3_lite test1:" << test1 << endl;

  e3_lite test2(4, 5, 6);
  cout << "e3_lite test2:" << test2 << endl;
  cout << endl;

  // Cross product: (1, 2, 3) x (4, 5, 6) = (-3, 6, -3).

  e3_lite* test3 = cross(test1, test2);
  cout << "cross(test1, test2): " << *test3 << endl;
  cout << endl;
  delete test3;

  e3_lite* test4 = test1^test2;
  cout << "test1 ^ test2: " << *test4 << endl;
  cout << endl;
  delete test4;

  e3_lite test5;
  cross(test1, test2, test5);
  cout << "cross(test1, test2, test5): " << test5 << endl;
  cout << endl;

  test5 = test1;
  cross_equal(test5, test2);
  cout << "cross_equal(test5, test2):" << test5 << endl;
  cout << endl;

  test5 = test1;
  test5 ^= test2;
  cout << "test5 ^= test2:" << test5 << endl;
  cout << endl;

  // Postconditions:

  // Exit:
}

///
void
fiber_bundle::
test_persistent_e3_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_subheader("Testing persistent type \"e3\"");

  e3::host_type& host = e3::standard_host(xns, "test_persistent_e3_facet", false);
  host.get_read_write_access();
  
  e3 test7(&host);
  test7.put_name("test7", true, false);

  e3 test8(&host);
  test8.put_name("test8", true, false);

  for(int i=0; i<test7.d(); ++i)
  {
    test7.put_component(i, i+1);
    test8.put_component(i, i+1+test7.d());
  }
  cout << "e3 test7:" << test7 << endl;
  cout << "e3 test8:" << test8 << endl;

  // Cross product: (1, 2, 3) x (4, 5, 6) = (-3, 6, -3).

  e3 test9(&host);
  test9.put_name("test9", true, false);
  cross(test7, test8, test9, false);
  cout << "cross(test7, test8, test9): " << test9 << endl;
  cout << endl;

  cross_equal(test7, test8, false);
  cout << "cross_equal(test7, test8):" << test7 << endl;
  cout << endl;

  test7.detach_from_state();
  test8.detach_from_state();
  test9.detach_from_state();
  host.release_access();

  // Postconditions:

  // Exit:
}

