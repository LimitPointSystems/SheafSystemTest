
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
/// Implementation of id space test function templates

#ifndef TEST_INDEX_SPACES_IMPL_H
#define TEST_INDEX_SPACES_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef TEST_INDEX_SPACES_H
#include "SheafSystemTest/test_index_spaces.h"
#endif

namespace sheaf
{

// ===========================================================
// HANDLE FACET
// ===========================================================

template <typename H>
void
test_handle_facet(index_space_family& xid_spaces,  pod_index_type xspace_id)
{
  // Preconditions:

  require(xid_spaces.contains(xspace_id));
  require(xid_spaces.handle_conforms_to_state<H>(xspace_id));

  // Body:

  using namespace std;

  print_out_header("Testing handle facet");

  const string& lname = xid_spaces.name(xspace_id);

  // Default Constructor.

  print_out_subheader("Testing default constructor");

  H lhandle0;
  cout << lhandle0 << endl;

  // Index constructor.

  print_out_subheader("Testing index constructor");

  H lhandle1(xid_spaces, xspace_id);
  cout << lhandle1 << endl;

  // Test index_space_family::get_id_space<H> for index.

  print_out_subheader("Testing index_space_family::get_id_space()");

  H& lhandle2 = xid_spaces.get_id_space<H>(xspace_id);
  cout << lhandle2 << endl;
  xid_spaces.release_id_space(lhandle2);

  // Name constructor.

  print_out_subheader("Testing name constructor");

  H lhandle3(xid_spaces, lname);
  cout << lhandle3 << endl;

  // Test index_space_family::get_id_space<H> for name.

  print_out_subheader("Testing index_space_family::get_id_space()");

  H& lhandle4 = xid_spaces.get_id_space<H>(lname);
  cout << lhandle4 << endl;
  xid_spaces.release_id_space(lhandle4);

  // Test clone.

  print_out_subheader("Testing clone");

  H* lhandle5 = lhandle1.clone();
  cout << lhandle5 << endl;
  delete lhandle5;

  // Test assignment operator.

  print_out_subheader("Testing assignment operator");

  H lhandle6;
  lhandle6 = lhandle1;
  cout << lhandle6 << endl;

  // Test copy constructor.

  print_out_subheader("Testing copy constructor");

  H lhandle7(lhandle1);
  cout << lhandle7 << endl;

  // Postconditions:

  // Exit:

  return;
}
  
// ===========================================================
// HANDLE FACET
// ===========================================================

template <typename H>
void
test_iterator_facet(index_space_family& xid_spaces,  pod_index_type xspace_id)
{
  // Preconditions:

  require(xid_spaces.contains(xspace_id));

  // Body:

  using namespace std;

  print_out_header("Testing iterator facet");

  const string& lname = xid_spaces.name(xspace_id);

  // Default Constructor.

  H litr0;

  // Index constructor.

  print_out_subheader("Testing index constructor");

  H litr1(xid_spaces, xspace_id);
  test_iterator(litr1);

  // Name constructor.

  print_out_subheader("Testing name constructor");

  H litr2(xid_spaces, lname);
  test_iterator(litr2);

  // Test clone.

  H& litr3 = *litr2.clone();

  // Test assignment operator.

  print_out_subheader("Testing assignment operator");

  litr2.reset();
  litr3 = litr2;
  test_iterator(litr3);

  // Test copy constructor.

  print_out_subheader("Testing copy constructor");

  litr2.reset();
  H litr4(litr2);
  test_iterator(litr4);

  // Postconditions:

  // Exit:

  return;
}

} // end namespace sheaf

#endif // ifndef TEST_INDEX_SPACES_IMPL_H
