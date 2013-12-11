
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

/// @example
/// Unit test driver for class primitive_value.

#include "primitive_value.h"

#include "namespace_poset.h"
#include "poset_path.h"
#include "std_iomanip.h"
#include "test_utils.h"

using namespace std;
using namespace sheaf;

namespace
{

template<typename T>
bool
test_primitive_value_facet(T xprimitive)
{
  // Preconditions:

  // Body:

  //============================================================================

  cout << boolalpha;
  bool lfrom_string;
  bool lequal_equal;

  cout << "xprimitive = " << xprimitive << endl; 


  print_subheader("Testing primitive_value()");

  primitive_value lprim_value0;
  

  print_subheader("Testing primitive_value(const T& x)");

  primitive_value lprim_value(xprimitive);


  print_subheader("Testing primitive_type& id()");

  primitive_type lprim_type = lprim_value.id();
  cout << "lprim_value.id() = " << lprim_type << endl;

  pod_index_type lid = lprim_value.id();
  cout << "lprim_value.id() = " << lid << endl;


  print_subheader("Testing primitive_value(pod_index_type xid, void* xvalue_ptr)");

  primitive_value lprim_value5(lid, &xprimitive);


  print_subheader("Testing primitive_value(primitive_type xid)");

  primitive_value lprim_value6(lprim_type);


  print_subheader("Testing primitive_value(const primitive_value& xother)");

  primitive_value lprim_value2(lprim_value);


  print_subheader("Testing primitive_value& operator=(const primitive_value& x)");

  primitive_value& lprim_value3 = lprim_value;


  print_subheader("Testing primitive_value& operator=(const T& xval)");

  primitive_value lprim_value7;
  lprim_value7 = xprimitive;

  print_subheader("Testing string to_string() const");

  string lstring = lprim_value.to_string();
  cout << "lprim_value.to_string() = " << lstring << endl;

  print_subheader("Testing  bool from_string(const std::string& x)");

  lfrom_string = lprim_value.from_string(lstring);
  cout << "lprim_value.from_string(lprim_value.to_string()) = "
       << lfrom_string << endl;

  print_subheader("Testing operator==(const primitive_value& xpv1,",
                  "                   const primitive_value& xpv2)");

  lequal_equal = (lprim_value == lprim_value2);
  cout << "(lprim_value == lprim_value2) = "
       << lequal_equal << endl;

  print_subheader("Testing operator==(const primitive_value& xpv,",
                  "                   const T& xval)");

  lequal_equal = (xprimitive == lprim_value);
  cout << "(xprimitive == lprim_value) = "
       << lequal_equal << endl;

  print_subheader("Testing operator==(const T& xval,",
                  "                   const primitive_value& xpv)");

  lequal_equal = (lprim_value == xprimitive);
  cout << "(lprim_value == xprimitive) = "
       << lequal_equal << endl;

  print_subheader("Testing deep_size(primitive_value const&, bool)");

  size_t ldeep_size = deep_size(lprim_value, false);
  cout << "ldeep_size = " << ldeep_size << endl;

  //============================================================================

  // Postconditions:

  // Exit:

  return true;
}


template<typename T>
bool
test_primitive_value_facet(T* xprimitive)
{
  // Preconditions:

  // Body:

  //============================================================================

  cout << boolalpha;
  bool lfrom_string;
  bool lequal_equal;

  cout << "xprimitive = " << xprimitive << endl; 


  print_subheader("Testing primitive_value()");

  primitive_value lprim_value0;
  

  print_subheader("Testing primitive_value(const T& x)");

  primitive_value lprim_value(xprimitive);


  print_subheader("Testing primitive_type& id()");

  primitive_type lprim_type = lprim_value.id();
  cout << "lprim_value.id() = " << lprim_type << endl;

  pod_index_type lid = lprim_value.id();
  cout << "lprim_value.id() = " << lid << endl;


  print_subheader("Testing primitive_value(pod_index_type xid, void* xvalue_ptr)");

  primitive_value lprim_value5(lid, &xprimitive);


  print_subheader("Testing primitive_value(primitive_type xid)");

  primitive_value lprim_value6(lprim_type);


  print_subheader("Testing primitive_value(const primitive_value& xother)");

  primitive_value lprim_value2(lprim_value);


  print_subheader("Testing primitive_value& operator=(const primitive_value& x)");

  primitive_value& lprim_value3 = lprim_value;


  print_subheader("Testing primitive_value& operator=(const T& xval)");

  primitive_value lprim_value7;
  lprim_value7 = xprimitive;

  print_subheader("Testing string to_string() const");

  string lstring = lprim_value.to_string();
  cout << "lprim_value.to_string() = " << lstring << endl;

  print_subheader("Testing  bool from_string(const std::string& x)");

  lfrom_string = lprim_value.from_string(lstring);
  cout << "lprim_value.from_string(lprim_value.to_string()) = "
       << lfrom_string << endl;

  print_subheader("Testing operator==(const primitive_value& xpv1,",
                  "                   const primitive_value& xpv2)");

  lequal_equal = (lprim_value == lprim_value2);
  cout << "(lprim_value == lprim_value2) = "
       << lequal_equal << endl;

  print_subheader("Testing operator==(const primitive_value& xpv,",
                  "                   const T& xval)");

  lequal_equal = (xprimitive == (void*)lprim_value);
  cout << "(xprimitive == lprim_value) = "
       << lequal_equal << endl;

  print_subheader("Testing operator==(const T& xval,",
                  "                   const primitive_value& xpv)");

  lequal_equal = ((void*)lprim_value == xprimitive);
  cout << "(lprim_value == xprimitive) = "
       << lequal_equal << endl;


  print_subheader("Testing deep_size(primitive_value const&, bool)");

  size_t ldeep_size = deep_size(lprim_value, false);
  cout << "ldeep_size = " << ldeep_size << endl;

  //============================================================================

  // Postconditions:

  // Exit:

  return true;
}


} //end namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing primitive_value facet");

  bool ltest = true;

  // Make an id space family and a primary term so that scoped ids can be
  // constructed.

  namespace_poset::initialize_id_space_prototypes();

  index_space_family lid_spaces;
  lid_spaces.new_id(123);

  const index_space_handle& lhub_id_space = lid_spaces.hub_id_space();

  //============================================================================


  print_header("Testing primitive_value facet for type \"bool\"");
  ltest &= test_primitive_value_facet<bool>(true);


  print_header("Testing primitive_value facet for type \"char\"");
  ltest &= test_primitive_value_facet<char>('C');


  print_header("Testing primitive_value facet for type \"char*\"");
  ltest &= test_primitive_value_facet<char>("ABC");


  print_header("Testing primitive_value facet for type \"double\"");
  ltest &= test_primitive_value_facet<double>(123.456);


  print_header("Testing primitive_value facet for type \"float\"");
  ltest &= test_primitive_value_facet<float>(123.456);


  print_header("Testing primitive_value facet for type \"int\"");
  ltest &= test_primitive_value_facet<int>(123);


  print_header("Testing primitive_value facet for type \"long double\"");
  ltest &= test_primitive_value_facet<long double>(123.456);


  print_header("Testing primitive_value facet for type \"long int\"");
  ltest &= test_primitive_value_facet<long int>(123);


  print_header("Testing primitive_value facet for type \"long long int\"");
  ltest &= test_primitive_value_facet<long long int>(123);


  print_header("Testing primitive_value facet for type",
               " \"namespace_relative_member_index\"");
  namespace_relative_member_index lindex0;
  ltest &= test_primitive_value_facet<namespace_relative_member_index>(lindex0);


  print_header("Testing primitive_value facet for type",
               " \"namespace_relative_member_index_pod_type\"");
  namespace_relative_member_index_pod_type lpod0;
  lpod0.poset_id = 0;
  lpod0.member_id = 0;
  ltest &= test_primitive_value_facet<namespace_relative_member_index_pod_type>(lpod0);


  print_header("Testing primitive_value facet for type",
               " \"namespace_relative_subposet_index\"");
  namespace_relative_subposet_index lindex1;
  ltest &= test_primitive_value_facet<namespace_relative_subposet_index>(lindex1);


  print_header("Testing primitive_value facet for type",
               " \"namespace_relative_subposet_index_pod_type\"");
  namespace_relative_subposet_index_pod_type lpod1;
  lpod1.poset_id = 0;
  lpod1.subposet_id = 0;
  ltest &= test_primitive_value_facet<namespace_relative_subposet_index_pod_type>(lpod1);


  print_header("Testing primitive_value facet for type \"scoped_index\"");
  scoped_index lscoped_index(lhub_id_space, 123);
  ltest &= test_primitive_value_facet<scoped_index>(lscoped_index);


  print_header("Testing primitive_value facet for type \"short int\"");
  ltest &= test_primitive_value_facet<short int>(123);


  print_header("Testing primitive_value facet for type \"signed char\"");
  ltest &= test_primitive_value_facet<signed char>('C');


  print_header("Testing primitive_value facet for type \"string\"");
  ltest &= test_primitive_value_facet<string>("ABC");


  print_header("Testing primitive_value facet for type \"unsigned char\"");
  ltest &= test_primitive_value_facet<unsigned char>('C');


  print_header("Testing primitive_value facet for type \"unsigned int\"");
  ltest &= test_primitive_value_facet<unsigned int>(123);


  print_header("Testing primitive_value facet for type \"unsigned long int\"");
  ltest &= test_primitive_value_facet<unsigned long int>(123);


  print_header("Testing primitive_value facet for type \"unsigned long long int\"");
  ltest &= test_primitive_value_facet<unsigned long long int>(123);


  print_header("Testing primitive_value facet for type \"unsigned short int\"");
  ltest &= test_primitive_value_facet<unsigned short int>(123);


  print_header("Testing primitive_value facet for type \"void*\"");
  int lint = 123; void* lvoid_star = &lint;
  ltest &= test_primitive_value_facet<void>(lvoid_star);


  print_header("Testing primitive_value facet for type \"poset_path\"");
  poset_path lposet_path("Hello","World");
  ltest &= test_primitive_value_facet<poset_path>(lposet_path);

  //============================================================================

  // Test the static protype function.

  print_header("Testing static const primitive_value& prototype(pod_index_type xid)");

  const primitive_value& lproto0 = primitive_value::prototype(0);
  cout << "lproto0 = " << lproto0 << endl; 

  const primitive_value& lproto1 = primitive_value::prototype(1);
  cout << "lproto1 = " << lproto1 << endl; 

  const primitive_value& lproto2 = primitive_value::prototype(2);
  cout << "lproto2 = " << lproto2 << endl; 

  const primitive_value& lproto3 = primitive_value::prototype(3);
  cout << "lproto3 = " << lproto3 << endl; 

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing primitive_value facet");

  // Postconditions:

  // Exit:

  return lresult;
}

