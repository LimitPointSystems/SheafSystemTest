
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
/// Test driver for class standard_subposet_index.

#include "standard_subposet_index.h"

#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_utils.h"

using namespace sheaf;

int
main()
{
  // Preconditions:

  // Body:

  print_header("Begin testing class standard_subposet_index.");

  //============================================================================

  standard_subposet_index lindex = STANDARD_SUBPOSET_INDEX_BEGIN;

  cout << "lindex = " << lindex << endl;

  // standard_subposet_index& operator++(standard_subposet_index& x);

  ++lindex;

  cout << "lindex = " << lindex << endl;

  // const string& standard_subposet_index_to_name(standard_subposet_index xpt);

  const string& lname = standard_subposet_index_to_name(lindex);

  cout << "lname = " << lname << endl;

  const string& lname1 = standard_subposet_index_to_name(++lindex);

  cout << "lname1 = " << lname1 << endl;

  // standard_subposet_index standard_subposet_index_from_name(const string& xname);

  standard_subposet_index lindex1 =
    standard_subposet_index_from_name("WHOLE_INDEX");

  cout << "lindex1 = " << lindex1 << endl;

  // standard_subposet_index standard_subposet_index_from_index(pod_index_type xindex);

  standard_subposet_index lindex2 = standard_subposet_index_from_index(2);

  cout << "lindex2 = " << lindex2 << endl;

  // bool is_standard_subposet_index(pod_index_type xindex);

  bool lis_standard_subposet_index = is_standard_subposet_index(2);

  cout << "lis_standard_subposet_index = " << boolalpha
       << lis_standard_subposet_index << endl;
   

  //============================================================================

  print_footer("End testing class standard_subposet_index.");

  // Postconditions:

  // Exit:

  return 0;
}

