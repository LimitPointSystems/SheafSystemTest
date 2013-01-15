// $RCSfile: class.h,v $ $Revision: 1.4 $ $Date: 2011/04/19 18:00:23 $

// $Name:  $
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation of id space test function templates

#ifndef TEST_INDEX_SPACES_IMPL_H
#define TEST_INDEX_SPACES_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TEST_INDEX_SPACES_H
#include "test_index_spaces.h"
#endif

namespace sheaf
{

// ===========================================================
// HANDLE FACET
// ===========================================================

template <typename H>
void
test_explicit_handle_facet(index_space_family& xid_spaces,  pod_index_type xspace_id)
{
  // Preconditions:

  require(xid_spaces.contains(xspace_id));
  require(xid_spaces.handle_conforms_to_state<H>(xspace_id));

  // Body:

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

  // Test index_space_family::get_handle<H> for index.

  print_out_subheader("Testing index_space_family::get_handle()");

  H& lhandle2 = xid_spaces.get_handle<H>(xspace_id);
  cout << lhandle2 << endl;
  xid_spaces.release_handle(lhandle2);

  // Name constructor.

  print_out_subheader("Testing name constructor");

  H lhandle3(xid_spaces, lname);
  cout << lhandle3 << endl;

  // Test index_space_family::get_handle<H> for name.

  print_out_subheader("Testing index_space_family::get_handle()");

  H& lhandle4 = xid_spaces.get_handle<H>(lname);
  cout << lhandle4 << endl;
  xid_spaces.release_handle(lhandle4);

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
  
template <typename H>
void
test_implicit_handle_facet(index_space_family& xid_spaces,  pod_index_type xspace_id)
{
  // Preconditions:

  require(xid_spaces.contains(xspace_id));
  require(xid_spaces.handle_conforms_to_state<H>(xspace_id));

  // Body:

  print_out_header("Testing handle facet");

  // Default Constructor.

  print_out_subheader("Testing default constructor");

  H lhandle0;
  cout << lhandle0 << endl;

  // Index constructor.

  print_out_subheader("Testing index constructor");

  H lhandle1(xid_spaces, xspace_id);
  cout << lhandle1 << endl;

  // Test index_space_family::get_handle<H> for index.

  print_out_subheader("Testing index_space_family::get_handle()");

  H& lhandle2 = xid_spaces.get_handle<H>(xspace_id);
  cout << lhandle2 << endl;
  xid_spaces.release_handle(lhandle2);

  // Test clone.

  print_out_subheader("Testing clone");

  H* lhandle3 = lhandle1.clone();
  cout << lhandle3 << endl;
  delete lhandle3;

  // Test assignment operator.

  print_out_subheader("Testing assignment operator");

  H lhandle4;
  lhandle4 = lhandle1;
  cout << lhandle4 << endl;

  // Test copy constructor.

  print_out_subheader("Testing copy constructor");

  H lhandle5(lhandle1);
  cout << lhandle5 << endl;

  // Postconditions:

  // Exit:

  return;
}
  
// ===========================================================
// HANDLE FACET
// ===========================================================

template <typename H>
void
test_explicit_iterator_facet(index_space_family& xid_spaces,  pod_index_type xspace_id)
{
  // Preconditions:

  require(xid_spaces.contains(xspace_id));

  // Body:

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

template <typename H>
void
test_implicit_iterator_facet(index_space_family& xid_spaces,  pod_index_type xspace_id)
{
  // Preconditions:

  require(xid_spaces.contains(xspace_id));

  // Body:

  print_out_header("Testing iterator facet");

  // Default Constructor.

  H litr0;

  // Index constructor.

  print_out_subheader("Testing index constructor");

  H litr1(xid_spaces, xspace_id);
  test_iterator(litr1);

  // Test clone.

//   H& litr2 = *litr1.clone();

  // Test assignment operator.

//   print_out_subheader("Testing assignment operator");

//   litr1.reset();
//   litr2 = litr1;
//   test_iterator(litr2);

  // Test copy constructor.

//   print_out_subheader("Testing copy constructor");

//   litr1.reset();
//   H litr3(litr1);
//   test_iterator(litr3);

  // Postconditions:

  // Exit:

  return;
}

} // end namespace sheaf

#endif // ifndef TEST_INDEX_SPACES_IMPL_H
