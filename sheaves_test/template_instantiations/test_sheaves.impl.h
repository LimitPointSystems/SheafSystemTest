
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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
/// Implementation of sheaves test function templates.

#ifndef TEST_SHEAVES_IMPL_H
#define TEST_SHEAVES_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#include "arg_list.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "block.h"
#include "list_pool.h"
#include "std_iostream.h"
#include "test_sheaves.h"
#include "test_utils.h"

#include "test_sheaves.h"

#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "subposet_member_iterator.h"

#include "ragged_array.h"
#include "rc_any.h"
#include "record_map.h"



namespace sheaf
{

//=============================================================================
// ANY FACET
//=============================================================================

template<typename T>
bool
test_any_facet(const T& xobject)
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"any\" facet:");

  print_subheader("Contents of the original object \"xobject\":");

  cout << xobject << endl;
  cout << endl;

  // Test the clone function.

  print_subheader("Test the \"clone\" function:");

  cout << "T* lclone = xobject.clone():" << endl; 
  T* lclone = xobject.clone(); 

  cout << "Contents of the cloned object \"lclone\":" << endl;
  cout << *lclone << endl;
  cout << endl;

  bool ltest;

  print_subheader("Test the \"is_ancestor_of\" function:");

  ltest = xobject.is_ancestor_of(lclone);
  cout << "  xobject.is_ancestor_of(lclone): " << boolalpha << ltest << endl;
  cout << endl;

  print_subheader("Test the \"is_same_type\" function:");

  ltest = xobject.is_same_type(lclone);
  cout << "  xobject.is_same_type(lclone): " << boolalpha << ltest << endl;
  cout << endl;

  print_subheader("Test the \"invariant\" function:");

  ltest = xobject.invariant();
  cout << "  xobject.invariant(): " << boolalpha << ltest << endl;
  cout << endl;

  print_subheader("Test the \"invariant_check\" function:");

  ltest = xobject.invariant_check();
  cout << "  xobject.invariant_check(): " << boolalpha << ltest << endl;
  cout << endl;

  print_subheader("Test the \"disable_invariant_check\" function:");

  xobject.disable_invariant_check();
  cout << "  xobject.invariant_check(): " << boolalpha << ltest << endl;
  cout << endl;

  print_subheader("Test the \"enable_invariant_check\" function:");

  xobject.enable_invariant_check();
  cout << "  xobject.invariant_check(): " << boolalpha << ltest << endl;
  cout << endl;

  print_subheader("Test the \"disable_invariance_check_request_depth\" function");

  int lnum = xobject.disable_invariance_check_request_depth();
  cout << "  xobject.disable_invariance_check_request_depth(): " << lnum
       << endl;
  cout << endl;

  print_footer("End testing \"any\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

template<typename T>
bool
test_any_facet()
{
  // Preconditions:

  // Body:

   T lobject;
   test_any_facet(lobject);


  // Postconditions:

  // Exit:

  return true;
}

//=============================================================================
// RC_ANY FACET
//=============================================================================

template<typename T>
bool
test_rc_any_facet(const T& xobject)
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"_rc_any\" facet:");

  print_subheader("Test rc_any(const rc_any & xother)");

  rc_any lcopy(xobject);

  print_subheader("Test operator<<");

  cout << lcopy << endl;

  print_subheader("Test rc_any& operator=(const rc_any& xother)");

  //$$ISSUE: Doesn't seem to call the right function?
  rc_any& lsame = lcopy;

  cout << lsame << endl;

  print_subheader("Test bool is_shared() const");

  // Need a pointer to do add/remove_reference.

  T* lptr = new T();

  print_subheader("Test add_reference()");

  lptr->add_reference();
  lptr->add_reference();

  print_subheader("Test ref_ct() const");

  size_type lct = lptr->ref_ct();
  cout << "  lptr->ref_ct() = " << lct << endl;

  print_subheader("Test bool is_shared() const");

  bool ltest = lptr->is_shared();
  cout << "  lptr->is_shared() = " << boolalpha << ltest << endl;

  print_subheader("Test remove_reference()");

  lptr->remove_reference();
  lptr->remove_reference();

  print_footer("End testing \"_rc_any\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

template<typename T>
bool
test_rc_any_facet()
{
  // Preconditions:

  // Body:

  T lobject;
  test_rc_any_facet(lobject);

  // Postconditions:

  // Exit:

  return true;
}

//=============================================================================
// AUTO_BLOCK FACET
//=============================================================================

//   // Similar to c++11 (c++0x) type_traits::is_pointer
//   // Invoke as bool ltest = is_pointer<T>::value

//   template<typename T> 
//   struct is_pointer 
//   {
//     static const bool value = false;
//   };

//   template<typename T> 

//   struct is_pointer<T*> 
//   {
//     static const bool value = true;
//   };

template<typename T, typename S>
bool
test_auto_block_facet()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"auto_block\" facet:");

  print_subheader("Test auto_block(index_type xub = 0)");

  typedef auto_block<T, S> T0;

  T0 lblock0(5);

  //cout << lblock0 << endl;

  print_subheader("Test new auto_block<T, S");
  T0* lblock_ptr = new T0();
  //cout << *lblock_ptr << endl;
  delete lblock_ptr;

  print_subheader("Test auto_block(index_type xub, size_type xct, const T* xitems)");

  T l0 = T(), l1 = T(), l2 = T(), l3 = T(), l4 = T();
  T litems[5] =  {l0, l1, l4, l3, l4};
  T0 lblock1(10, 5, litems);

  //cout << lblock1 << endl;

  print_subheader("Test auto_block(const block& xother)");

  T0 lblock2(lblock1);

  print_subheader("Test block& operator=(const block& xother)");

  T0 lblock3;
  lblock3 = lblock2;

//   print_subheader("Test bool operator==(const auto_block<T,S>& xblk1, const auto_block<T,S>& xblk2)");

//   bool ltest0 = (lblock3 == lblock2);
//   cout << "  Test for equality: " << boolalpha << ltest0 << endl;

  print_subheader("Test size_type ct()");

  typename T0::size_type lct = lblock3.ct();
  cout << "  lct = " << lct << endl;

  print_subheader("Test void reserve(index_type xub)");
    
  lblock3.reserve(12);

  print_subheader("Test size_type ub()");

  typename T0::index_type lub = lblock3.ub();
  cout << "  lub = " << lub << endl;

  print_subheader(
                  "Test void force_item(index_type xindex, const_reference_type xitem)");
  //...

  print_subheader("Test pointer_type base()");

  typename T0::pointer_type lbase = lblock3.base();
  cout << "  lbase = " << lbase << endl;

  print_subheader("Test reference_type item(index_type xindex) const");

  typename T0::index_type lindex0 = 2;
  typename T0::reference_type lref0 =  lblock3.item(lindex0);

  print_subheader("Test reference_type operator[](index_type xindex) const");

  typename T0::index_type lindex1 = 4;
  typename T0::reference_type lref1 = lblock3[lindex1];

  print_subheader("Test reference_type.back()");

  typename T0::reference_type lref2 = lblock3.back();

  print_subheader("Test void assign(const_reference_type xitem)");

  lblock3.assign(lref1);

  print_subheader(
                  "Test void assign(index_type xbegin, index_type xend, const_reference_type xitem)");

  lblock3.assign(lindex0, lindex1, lref2);

  print_subheader(
                  "Test void set_item(index_type xindex, const_reference_type xitem)");

  lblock3.set_item(lindex1, lref1);

  print_subheader("Test void push_back(const_reference_type item)");

  lblock3.push_back(lref2);

  print_subheader("Test void push_back(const auto_block& xother)");

  lblock3.push_back(lblock2);

  print_subheader("Test void pop_back()");

  lblock3.pop_back();

  print_subheader("Test void clear()");

  lblock3.clear();

  print_subheader("Test void initialize(index_type xindex)");

  lblock3.initialize(lindex0);

  print_subheader("Test void initialize(index_type xbegin, index_type xend)");

  lblock3.initialize(lindex0, lindex1);

  print_subheader("Test bool invariant()");

  bool ltest1 = lblock3.invariant();
  cout << "  ltest1 = " << boolalpha << ltest1 << endl;

  //==========================================================================

  print_footer("End testing \"auto_block\" facet:");

  // Postconditions:

  // Exit:

  return true;

}

// Test blocks of type auto_block<T == T2*> 

template<typename T, typename T2, typename S>
bool
test_auto_block_facet()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"auto_block\" facet:");

  print_subheader("Test auto_block(index_type xub)");

  typedef auto_block<T, S> T0;

  T0 lblock0(5);

  print_subheader("Test new auto_block<T, S");
  T0* lblock_ptr = new T0();
  delete lblock_ptr;

  print_subheader("Test auto_block(index_type xub, size_type xct, const T* xitems)");

  T2 l0, l1, l2, l3, l4;
  T litems[5] = {&l0, &l1, &l4, &l3, &l4};
  T0 lblock1(10, 5, litems);

  print_subheader("Test auto_block(const block& xother)");

  T0 lblock2(lblock1);

  print_subheader("Test block& operator=(const block& xother)");

  T0 lblock3;
  lblock3 = lblock2;

  print_subheader("Test size_type ct()");

  typename T0::size_type lct = lblock3.ct();
  cout << "  lct = " << lct << endl;

  print_subheader("Test void reserve(index_type xub)");
    
  lblock3.reserve(12);

  print_subheader("Test size_type ub()");

  typename T0::index_type lub = lblock3.ub();
  cout << "  lub = " << lub << endl;

  print_subheader(
                  "Test void force_item(index_type xindex, const_reference_type xitem)");
  //...

  print_subheader("Test pointer_type base()");

  typename T0::pointer_type lbase = lblock3.base();
  cout << "  lbase = " << lbase << endl;

  print_subheader("Test reference_type item(index_type xindex) const");

  typename T0::index_type lindex0 = 2;
  typename T0::reference_type lref0 =  lblock3.item(lindex0);

  print_subheader("Test reference_type operator[](index_type xindex) const");

  typename T0::index_type lindex1 = 4;
  typename T0::reference_type lref1 = lblock3[lindex1];

  print_subheader("Test reference_type.back()");

  typename T0::reference_type lref2 = lblock3.back();

  print_subheader("Test void assign(const_reference_type xitem)");

  lblock3.assign(lref1);

  print_subheader(
                  "Test void assign(index_type xbegin, index_type xend, const_reference_type xitem)");

  lblock3.assign(lindex0, lindex1, lref2);

  print_subheader(
                  "Test void set_item(index_type xindex, const_reference_type xitem)");

  lblock3.set_item(lindex1, lref1);

  print_subheader("Test void push_back(const_reference_type item)");

  lblock3.push_back(lref2);

  print_subheader("Test void push_back(const auto_block& xother)");

  lblock3.push_back(lblock2);

  print_subheader("Test void pop_back()");

  lblock3.pop_back();

  print_subheader("Test void clear()");

  lblock3.clear();

  print_subheader("Test void initialize(index_type xindex)");

  lblock3.initialize(lindex0);

  print_subheader("Test void initialize(index_type xbegin, index_type xend)");

  lblock3.initialize(lindex0, lindex1);

  print_subheader("Test bool invariant()");

  bool ltest1 = lblock3.invariant();
  cout << "  ltest1 = " << boolalpha << ltest1 << endl;

  //==========================================================================

//   print_subheader("Test bool operator==");
 
//   bool ltest2 = (lblock3 == lblock2);;
//   cout << "  ltest2 = " << boolalpha << ltest2 << endl;

  //==========================================================================

  print_footer("End testing \"auto_block\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//============================================================================

template<typename T, typename S>
bool
test_auto_block_facet_equal()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing auto_block facet equal:");

  auto_block<T, S> lblock(5);
  auto_block<T, S> lblock_test = lblock;

  bool ltest = (lblock_test == lblock);
  cout << "  Test for equality: " << boolalpha << ltest << endl;

  cout << lblock << endl;

  print_footer("End testing auto_block facet equal:");

  // Postconditions:

  // Exit:

  return true;
}

template<typename T, typename S>
bool
test_auto_block_facet_equal_equal()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing auto_block facet equal_equal:");

  auto_block<T, S> lblock(5);
  auto_block<T, S> lblock_test = lblock;

  bool ltest = (lblock_test == lblock);
  cout << "  Test for equality: " << boolalpha << ltest << endl;

  cout << lblock << endl;

  print_footer("End testing auto_block facet equal_equal:");

  // Postconditions:

  // Exit:

  return true;
}

template<typename T, typename S>
bool
test_auto_block_facet_insertion()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing auto_block facet deep_size:");

  auto_block<T, S> lblock(5);

  cout << lblock << endl;

  print_footer("End testing auto_block facet deep_size:");

  // Postconditions:

  // Exit:

  return true;
}

template<typename T, typename S>
bool
test_auto_block_facet_deep_size()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"deep_size\" facet:");

  auto_block<T, S> lblock(5);

  size_t lsize = deep_size(lblock, true);
  cout << "Test deep_size (including shallow) = " << lsize << endl;

  lsize = deep_size(lblock, false);
  cout << "Test deep_size (excluding shallow) = " << lsize << endl;

  print_footer("End testing \"deep_size\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//============================================================================

template<typename T, typename T2, typename S>
bool
test_auto_block_facet_equal()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing auto_block facet equal:");

  auto_block<T, S> lblock(5);
  auto_block<T, S> lblock_test = lblock;

  bool ltest = (lblock_test == lblock);
  cout << "  Test for equality: " << boolalpha << ltest << endl;

  cout << lblock << endl;

  print_footer("End testing auto_block facet equal:");

  // Postconditions:

  // Exit:

  return true;
}

template<typename T, typename T2, typename S>
bool
test_auto_block_facet_insertion()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing auto_block facet deep_size:");

  auto_block<T, S> lblock(5);

  cout << lblock << endl;

  print_footer("End testing auto_block facet deep_size:");

  // Postconditions:

  // Exit:

  return true;
}


template<typename T, typename T2, typename S>
bool
test_auto_block_facet_deep_size()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"deep_size\" facet:");

  auto_block<T, S> lblock(5);

  size_t lsize = deep_size(lblock, true);
  cout << "Test deep_size (including shallow) = " << lsize << endl;

  lsize = deep_size(lblock, false);
  cout << "Test deep_size (excluding shallow) = " << lsize << endl;

  print_footer("End testing \"deep_size\" facet:");

  // Postconditions:

  // Exit:

  return true;
}


//============================================================================

template<typename T>
bool
test_auto_block_facet_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet<T, S>();
  return true;
}

//============================================================================

template<typename T>
bool
test_auto_block_facet_equal_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_equal_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_equal_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal<T, S>();
  return true;
}

//============================================================================

template<typename T>
bool
test_auto_block_facet_equal_equal_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal_equal<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_equal_equal_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal_equal<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_equal_equal_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal_equal<T, S>();
  return true;
}

//============================================================================

template<typename T>
bool
test_auto_block_facet_insertion_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_insertion<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_insertion_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_insertion<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_insertion_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_insertion<T, S>();
  return true;
}

//============================================================================

template<typename T>
bool
test_auto_block_facet_deep_size_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_deep_size<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_deep_size_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_deep_size<T, S>();
  return true;
}

template<typename T>
bool
test_auto_block_facet_deep_size_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_deep_size<T, S>();
  return true;
}

//============================================================================
 
template<typename T>
bool
test_auto_block_facet_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_un<T>();
  lresult &= test_auto_block_facet_invalid<T>();
  lresult &= test_auto_block_facet_zero<T>();

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T>
bool
test_auto_block_facet_equal_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_equal_un<T>();
  lresult &= test_auto_block_facet_equal_invalid<T>();
  lresult &= test_auto_block_facet_equal_zero<T>();

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T>
bool
test_auto_block_facet_equal_equal_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_equal_equal_un<T>();
  lresult &= test_auto_block_facet_equal_equal_invalid<T>();
  lresult &= test_auto_block_facet_equal_equal_zero<T>();

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T>
bool
test_auto_block_facet_insertion_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_insertion_un<T>();
  lresult &= test_auto_block_facet_insertion_invalid<T>();
  lresult &= test_auto_block_facet_insertion_zero<T>();

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T>
bool
test_auto_block_facet_deep_size_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_deep_size_un<T>();
  lresult &= test_auto_block_facet_deep_size_invalid<T>();
  lresult &= test_auto_block_facet_deep_size_zero<T>();

  // Postconditions:

  // Exit:

  return lresult;
}

//============================================================================

template<typename T, typename T2>
bool
test_auto_block_facet_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet<T, T2, S>();
  return true;
}

template<typename T, typename T2>
bool
test_auto_block_facet_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet<T, T2, S>();
  return true;
}

template<typename T, typename T2>
bool
test_auto_block_facet_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet<T, T2, S>();
  return true;
}

//============================================================================

template<typename T, typename T2>
bool
test_auto_block_facet_equal_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal<T, T2, S>();
  return true;
}

template<typename T, typename T2>
bool
test_auto_block_facet_equal_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal<T, T2, S>();
  return true;
}

template<typename T, typename T2>
bool
test_auto_block_facet_equal_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_equal<T, T2, S>();
  return true;
}

//============================================================================

template<typename T, typename T2>
bool
test_auto_block_facet_insertion_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_insertion<T, T2, S>();
  return true;
}

template<typename T, typename T2>
bool
test_auto_block_facet_insertion_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_insertion<T, T2, S>();
  return true;
}

template<typename T, typename T2>
bool
test_auto_block_facet_insertion_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_insertion<T, T2, S>();
  return true;
}

//============================================================================

template<typename T, typename T2>
bool
test_auto_block_facet_deep_size_un()
{
  typedef sheaf::un_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_deep_size<T, T2, S>();
  return true;
}

template<typename T, typename T2>
bool
test_auto_block_facet_deep_size_invalid()
{
  typedef sheaf::invalid_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_deep_size<T, T2, S>();
  return true;
}

template<typename T, typename T2>
bool
test_auto_block_facet_deep_size_zero()
{
  typedef sheaf::zero_block_initialization_policy<T> S;
  bool ltest = test_auto_block_facet_deep_size<T, T2, S>();
  return true;
}

//============================================================================

template<typename T, typename T2>
bool
test_auto_block_facet_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_un<T>();
  lresult &= test_auto_block_facet_invalid<T>();
  lresult &= test_auto_block_facet_zero<T>();

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T, typename T2>
bool
test_auto_block_facet_equal_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_equal_un<T, T2>();
  lresult &= test_auto_block_facet_equal_invalid<T, T2>();
  lresult &= test_auto_block_facet_equal_zero<T, T2>();

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T, typename T2>
bool
test_auto_block_facet_insertion_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_insertion_un<T, T2>();
  lresult &= test_auto_block_facet_insertion_invalid<T, T2>();
  lresult &= test_auto_block_facet_insertion_zero<T, T2>();

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T, typename T2>
bool
test_auto_block_facet_deep_size_all()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  lresult &= test_auto_block_facet_deep_size_un<T, T2>();
  lresult &= test_auto_block_facet_deep_size_invalid<T, T2>();
  lresult &= test_auto_block_facet_deep_size_zero<T, T2>();

  // Postconditions:

  // Exit:

  return lresult;
}

//=============================================================================
// BLOCK FACET
//=============================================================================

// Test blocks of type block<T>.

template<typename T>
bool
test_block_facet()
{
  // Preconditions:

  // Body:

  print_header("Begin testing \"block\" facet:");

  print_subheader("Test block(index_type xub = 0)");

  block<T> lblock0(5);

  print_subheader("Test new block<T>");
  block<T>* lblock_ptr = new block<T>();
  delete lblock_ptr;

  print_subheader("Test block(index_type xub, size_type xct, const T* xitems)");

  T litems[5];
  block<T> lblock1(10, 5, litems);

  print_subheader("Test block(const block& xother)");

  block<T> lblock2(lblock1);

  print_subheader("Test block& operator=(const block& xother)");

  block<T> lblock3;
  lblock3 = lblock2;

  print_footer("End testing \"block\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

// Test blocks of type block<T == T2*> 

template<typename T, typename T2>
bool
test_block_facet()
{
  // Preconditions:

  // Body:

  print_header("Begin testing \"block\" facet:");

  print_subheader("Test block(index_type xub)");

  block<T> lblock0(5);

  //cout << lblock0 << endl;

  print_subheader("Test new block<T>");
  block<T>* lblock_ptr = new block<T>();
  delete lblock_ptr;


  print_subheader("Test block(index_type xub, size_type xct, const T* xitems)");

  T2 lv[5];
  T litems[5] = {&lv[0], &lv[1], &lv[2], &lv[3], &lv[4]};
  block<T> lblock1(10, 5, litems);

  print_subheader("Test block(const block& xother)");

  block<T> lblock2(lblock1);


  print_subheader("Test block& operator=(const block& xother)");

  block<T> lblock3;
  lblock3 = lblock2;


  print_footer("End testing \"block\" facet:");

  // Postconditions:

  // Exit:

  return true;
}


template<typename T>
bool
test_block_facet_equal()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing block facet equal:");

  T litems[5];
  block<T> lblock(10, 5, litems);

  block<T> lblock_test = lblock;

   bool ltest = (lblock_test == lblock);
   cout << "  Test for equality: " << boolalpha << ltest << endl;

   //cout << lblock << endl;

  print_footer("End testing block facet equal:");

  // Postconditions:

  // Exit:

  return true;
}

template<typename T>
bool
test_block_facet_insertion()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing block facet insertion:");

  T litems[5];
  block<T> lblock(10, 5, litems);

  cout << lblock << endl;

  print_footer("End testing block facet insertion:");

  // Postconditions:

  // Exit:

  return true;
}

template<typename T>
bool
test_block_facet_deep_size()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"deep_size\" facet:");

  T litems[5];
  block<T> lblock(10, 5, litems);

  size_t lsize = deep_size(lblock, true);
  cout << "Test deep_size (including shallow) = " << lsize << endl;

  lsize = deep_size(lblock, false);
  cout << "Test deep_size (excluding shallow) = " << lsize << endl;

  print_footer("End testing \"deep_size\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//=============================================================================
// WSV_BLOCK FACET
//=============================================================================

template<typename T>
bool
test_wsv_block_facet()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"wsv_block\" facet:");

  print_subheader("Test wsv_block() - default constructor");

  wsv_block<T> lblock0;

  cout << lblock0 << endl;

  print_subheader("Test wsv_block(const wsv_block& xother)");

  wsv_block<T> lblock1(lblock0);

  cout << lblock1 << endl;

  print_subheader("Test wsv_block(const char* xlist)");

  char lcharlist[64] = "99 88 77";
  wsv_block<T> lblock2(lcharlist);

  cout << lblock2 << endl;

  print_subheader("Test wsv_block(const string& xlist)");

  const string llist = "11 22 33";
  wsv_block<T> lblock3(llist);

  cout << lblock3 << endl;

  print_subheader("Test  wsv_block& operator=(const wsv_block& xother)");

  wsv_block<T> lblock4;
  lblock4 = lblock3;

  cout << lblock4 << endl;

  print_subheader("Test  wsv_block& operator=(const string& xlist)");

  const string llist4 = "111 222 333";
  lblock4 = llist4;

  cout << lblock4 << endl;

  print_subheader("Test wsv_block& operator=(const char* xlist)");

  const char* lcharlist4 = "999 888 777";
  lblock4 = lcharlist4;

  cout << lblock4 << endl;

  print_subheader("Test bool invariant() const");

  bool ltest = lblock4.invariant();
  cout << "lblock4.invariant() = " << boolalpha << ltest << endl;

  print_subheader("Test void push_back(const wsv_block& xother)");

  lblock4.push_back(lblock2);

  cout << lblock4 << endl;

  print_footer("End testing \"wsv_block\" facet:");

  // Postconditions:

  // Exit:

  return true;
}


//=============================================================================
// RECORD_MAP FACET
//=============================================================================

template<typename T1, typename T2>
bool
test_record_map_facet()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"record_map\" facet:");

  // Make a new record_map (test default constructor).

  print_subheader("Testing default constructor:");

  record_map<T1, T2> lmap;

  // Test "put_ids(internal_index_type xinternal_id, external_index_type xexternal_id);

  print_subheader("Testing put_ids(internal_index_type xinternal_id, external_index_type xexternal_id)");

  for(int i=0; i<10; ++i)
  {
    T1 linternal_id(i);
    T2 lexternal_id(i+100);
    cout << "   put_ids(): " << linternal_id << ", " << lexternal_id << endl;;
    lmap.put_ids(linternal_id, lexternal_id);
  }

  // Test "operator<<" and "print" functions:

  print_subheader("Testing operator<<");

  cout << lmap << endl;
  cout << endl;

  print_subheader("Testing print()");

  lmap.print();
  cout << endl;

  // Test "ct()":

  print_subheader("Testing ct()");

  size_t lct = lmap.ct();
  cout << "lct = " << lct << endl;
  cout << endl;

  // Test "is_empty()":

  print_subheader("Testing is_empty()");

  bool lis_empty = lmap.is_empty();
  cout << "lis_empty = " << boolalpha << lis_empty << endl;
  cout << endl;

  // Test "ub_is_max()":

  print_subheader("Testing ub_is_max()");

  bool lub_is_max = lmap.ub_is_max();
  cout << "lub_is_max = " << boolalpha << lub_is_max << endl;
  cout << endl;

  // Test "internal_index_type internal_id_ub()";

  print_subheader("Testing internal_id_ub()");

  T1 lin_id_ub = lmap.internal_id_ub();
  cout << "lin_id_ub = " << lin_id_ub << endl;
  cout << endl;

  // Test "external_index_type external_id_ub()";

  print_subheader("Testing external_id_ub()");

  T2 lex_id_ub = lmap.external_id_ub();
  cout << "lex_id_ub = " << lex_id_ub << endl;
  cout << endl;

  // Test "internal_ids_sequential()":

  print_subheader("Testing internal_ids_sequential()");

  bool linternal_ids_sequential = lmap.internal_ids_sequential();
  cout << "linternal_ids_sequential = " << boolalpha << linternal_ids_sequential << endl;
  cout << endl;

  // Test "external_ids_sequential()":

  print_subheader("Testing external_ids_sequential()");

  bool lexternal_ids_sequential = lmap.external_ids_sequential();
  cout << "lexternal_ids_sequential = " << boolalpha << lexternal_ids_sequential << endl;
  cout << endl;

  // Test "external_id(T1 xinternal_id)":

  print_subheader("Testing external_id(internal_index_type)");

  T2 lex_id = lmap.external_id(T1(5));
  cout << "lex_id = " << lex_id << endl;
  cout << endl;

  // Test "internal_id(T2 xexternal_id)":

  print_subheader("Testing internal_id(external_index_type)");

  T1 lin_id = lmap.internal_id(T2(105));
  cout << "lin_id = " << lin_id << endl;
  cout << endl;

  // Test "clear()":

  print_subheader("Testing clear()");

  lmap.clear();
  cout << lmap << endl;
  cout << endl;

  // Test "external_index_type put_internal_id(internal_index_type xinternal_id)"

  print_subheader("Testing external_index_type put_internal_id(internal_index_type xinternal_id)");

  T2 lex_id2 = lmap.put_internal_id(T1(20));
  cout << "lex_id2 = " << lex_id2 << endl;
  T2 lex_id3 = lmap.put_internal_id(T1(21));
  cout << "lex_id3 = " << lex_id3 << endl;
  cout << lmap << endl;
  cout << endl;

  // Test "contains_internal_id(internal_index_type xint_id)":

  print_subheader("Testing contains_internal_id(internal_index_type xint_id)");

  bool ltest = lmap.contains_internal_id(T1(20));
  cout << "ltest = " << boolalpha << ltest << endl;
  ltest = lmap.contains_internal_id(T1(22));
  cout << "ltest = " << boolalpha << ltest << endl;
  cout << endl;


  // Test "remove_internal_id(internal_index_type xinternal_id)":

  print_subheader("Testing remove_internal_id(internal_index_type xinternal_id)");
  lmap.remove_internal_id(T1(20));

  //Test "put_scratch_internal_id(internal_index_type xid)":

  print_subheader("Testing put_scratch_internal_id(internal_index_type xid)");
  lmap.put_scratch_internal_id(T1(66));

  lmap.clear();

  // Test internal_index_type put_external_id(external_index_type xexternal_id)"

  print_subheader("Testing internal_index_type put_external_id(external_index_type xexternal_id)");
  T1 lin_id2 = lmap.put_external_id(T2(20));
  cout << "lin_id2 = " << lin_id2 << endl;
  T1 lin_id3 = lmap.put_external_id(T2(21));
  cout << "lin_id3 = " << lin_id3 << endl;
  cout << lmap << endl;
  cout << endl;

  //Test "contains_external_id(external_index_type xext_id)":

  print_subheader("Testing contains_external_id(external_index_type xext_id)");
  ltest = lmap.contains_external_id(T2(20));
  cout << "ltest = " << boolalpha << ltest << endl;
  ltest = lmap.contains_external_id(T2(22));
  cout << "ltest = " << boolalpha << ltest << endl;

  //Test "put_scratch_external_id(external_index_type xid)":

  print_subheader("Testing put_scratch_external_id(external_index_type xid)");
  lmap.put_scratch_external_id(T2(99));

  // Test "remove_external_id(external_index_type xinternal_id)":

  print_subheader("Testing remove_external_id(external_index_type xinternal_id)");
  lmap.remove_external_id(T2(20));

  // Test copy constructor:

  print_subheader("Testing copy constructor");
  record_map<T1, T2> lmap_copy (lmap);

  // Test equality:

  print_subheader("Testing ");
  ltest = (lmap == lmap_copy);
  cout << "lmap == lmap_copy: " << boolalpha << ltest << endl; 

  // Test  "begin()" and "end()":

  print_subheader("Testing begin() and end()");

  typename sheaf::record_map<T1, T2>::const_iterator litr_begin = lmap.begin();
  typename sheaf::record_map<T1, T2>::const_iterator litr_end = lmap.end();
  typename sheaf::record_map<T1, T2>::const_iterator litr = litr_begin;
  for(litr = litr_begin; litr != litr_end; litr++)
  {
    cout << "itr = " << litr->first << "\t: " << litr->second << endl;
  }
  cout << endl;

  print_header("End testing \"record_map\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//=============================================================================
// RAGGED_ARRAY FACET
//=============================================================================

template<typename T>
bool
test_ragged_array_facet()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"ragged_array\" facet:");

  print_subheader("Test ragged_array<T>(size_t xct)");

  ragged_array<T> larray1(10);

  print_subheader("Test operator<<");

  cout << larray1 << endl;

  print_subheader("Test ragged_array(const index_type xrow_ct, const index_type xvalue_ct)");

  ragged_array<T> larray2(10, 20);

  cout << larray2 << endl;

  print_subheader("Test ragged_array(const index_type* xcol_cts, index_type xcol_cts_ub)");

  const typename sheaf::ragged_array<T>::index_type lcol_cts[3] = {3, 5, 7};

  ragged_array<T> larray3(lcol_cts, 3);

  cout << larray3 << endl;

  print_subheader("Test T* row(const index_type xrow_index) const");

  T* lrow = larray3.row(1);
  const typename sheaf::ragged_array<T>::index_type lct = larray3.col_ct(1);
  for(int i=0; i<lct; ++i)
  {
    cout << "  " << i << " : " << lrow[i] << endl; 
  }

  print_subheader("Test T* values() const");

  const T* lvalues = larray3.values();

  typename sheaf::ragged_array<T>::index_type lct2 = larray3.value_ct();
  for(int i=0; i<lct2; ++i)
  {
    cout << "  " << i << " : " << lvalues[i] << endl; 
  }

  print_subheader("Test void new_back_row()");

  larray3.new_back_row();

  cout << larray3 << endl;

  print_subheader("Test index_type back_row() const");

  const typename sheaf::ragged_array<T>::index_type lback_row = larray3.back_row();

  cout << "Back row index: " << lback_row << endl;

  print_subheader("Test void push_back(const T& xvalue)");

  larray3.push_back(T(32)); // char 32 is space.

  cout << larray3 << endl;

  print_subheader("Test reset_rows()");

  larray3.reset_rows();

  cout << larray3 << endl;

  print_subheader("Test reset_rows(const index_type* xcol_cts, index_type xcol_cts_ub)");

  larray2.reset_rows(lcol_cts, 3);

  cout << larray2 << endl;

  print_subheader("Test void initialize_push_back(index_type xrow_ct, index_type xvalue_ct)");

  larray2.initialize_push_back(2, 3);

  cout << larray2 << endl;


  print_footer("End testing \"ragged_array\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//=============================================================================
// DEEP_SIZE FACET
//=============================================================================

template<typename T>
bool
test_deep_size(const T& xobject)
{
  // Preconditions:

  // Body:

  using namespace std;

  print_subheader("Test deep_size");

  cout << endl;
  size_t lsize = deep_size(xobject, true);
  cout << "Test deep_size (including shallow) = " << lsize << endl;

  lsize = deep_size(xobject, false);
  cout << "Test deep_size (excluding shallow) = " << lsize << endl;
  cout << endl;

  // Postconditions:

  // Exit:

  return true;
}

//============================================================================
// NAMESPACE_POSET FACET
//============================================================================

template<typename T>
bool
test_namespace_poset_facet(namespace_poset& xns,
                           poset_state_handle& xposet)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  using namespace std;

  print_header("Begin testing \"namespace_poset\" facet:");

  bool ltest = true;

  print_subheader("Test contains_poset<T>(lpath, true);");

  const poset_path& lpath = xposet.path();
  cout << "xposet.path() = " << xposet.path() << endl;
  ltest = xns.contains_poset<T>(lpath, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  //$$SCRIBBLE: No instantiations for scoped_index version.
  //const scoped_index& lindex = xposet.index();
  //cout << "xposet.index() = " << xposet.index() << endl;
  //ltest = xns.contains_poset<T>(lindex, true);
  //cout << "ltest = " << boolalpha << ltest << endl;

  //$$SCRIBBLE: No instantiations for string version (except refinable_poset).
  //const string& lname = xposet.name();
  //cout << "xposet.name() = " << xposet.name() << endl;
  //ltest = xns.contains_poset<T>(lname, true);
  //cout << "ltest = " << boolalpha << ltest << endl;

  print_subheader("Test contains_poset<T>(lpath, true);");

  T* lptr = &xns.member_poset<T>(lpath, true);
  cout << "xns.member_poset<T>(lpath, true) = " << lptr << endl;
 

  print_footer("End testing \"namespace_poset\" facet:");

  // Postconditions:

  // Exit:

  return ltest;
}

//==============================================================================
// DEPTH_FIRST_ITERATOR FACET
//==============================================================================

template <template <typename> class ITR, typename T>
bool
test_depth_first_itr_facet(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  using namespace std;

  //============================================================================

  print_header("Begin testing \"depth_first_itr\" facet");

  bool ltest = true;

  const string lposet_name = "refinable_triangle";
  if(!(xns.contains_member(lposet_name)))
  {
     make_triangle_poset(xns, lposet_name);
  }
  refinable_poset& lposet = xns.member_poset<refinable_poset>(lposet_name);
  lposet.get_read_write_access();
  const abstract_poset_member& lanchor = lposet.top();

  //////////////////////////////////////////////////////////////////////////////

  subposet* lvertices;
  if(!(lposet.includes_subposet("__vertices")))
  {
    lvertices = new subposet(&lposet);
    lvertices->put_name("__vertices", true, false);
  }
  else
  {
    lvertices = new subposet(&lposet, "__vertices");
  }

  //ITR<T> litr(lanchor, const string& xfilter_name);
  ITR<T> litr_xx(lanchor, "__vertices", sheaf::DOWN, sheaf::NOT_STRICT);

  const subposet& lfilter = litr_xx.filter();

  cout << "lfilter.name() = " << lfilter.name() << endl;
  cout << "lfilter.index() = " << lfilter.index() << endl;

  //ITR<T> litr(lanchor, scoped_index xfilter_index);
  ITR<T> litr_yy(lanchor, lfilter.index(), sheaf::DOWN, sheaf::NOT_STRICT);

  //ITR<T> litr(lanchor); == litr(lanchor, 0, sheaf::DOWN, sheaf::NOT_STRICT)
  ITR<T> litr_zz(lanchor, *lvertices, sheaf::DOWN, sheaf::NOT_STRICT);
  ITR<T> litr_zz2(lanchor, *lvertices, sheaf::UP, sheaf::NOT_STRICT);
  ITR<T> litr_zz3(lanchor, *lvertices, sheaf::UP, sheaf::STRICT);
  ITR<T> litr_zz4(lanchor, *lvertices, sheaf::DOWN, sheaf::STRICT);

  //////////////////////////////////////////////////////////////////////////////

  print_subheader("Testing filtered_depth_first_itr(",
                  "        const abstract_poset_member&, const subposet*,)");

  ITR<T> litr(lanchor, sheaf::DOWN, sheaf::NOT_STRICT);

  print_subheader("Testing depth_first_itr<T>::reserve_has_visited(pod_index_type xub)");

  litr.reserve_has_visited(16);


  print_subheader("Testing bool depth_first_itr<T>::visit_once()");

  bool lvisit_once = litr.visit_once();
  cout << "lvisit_once = " << boolalpha << lvisit_once << endl;

  print_subheader("Testing depth_first_itr<T>::put_visit_once(bool)");

  litr.put_visit_once(!lvisit_once);
  litr.put_visit_once(lvisit_once);

  print_subheader("Testing depth_first_itr<T>::depth()");

  size_t ldepth = litr.depth();
  cout << "ldepth = " << ldepth << endl;

  print_subheader("Testing depth_first_itr<T>::ct(bool)");

  int lct = litr.ct(false);
  cout << "lct = " << lct << endl;

  // After ct() call is_done() == true; so reset.

  litr.reset();

  print_subheader("Testing scoped_index depth_first_itr<T>::greater_index()");

  scoped_index lgreater_index = litr.greater_index();
  cout << "lgreater_index = " << lgreater_index << endl;

  print_subheader("Testing bool depth_first_itr<T>::is_maximal()");

  bool lis_maximal = litr.is_maximal();
  cout << "lis_maximal = " << boolalpha << lis_maximal << endl;


  //============================================================================

  print_subheader("Testing depth_first_itr<T>::operator=(",
                  "        sheaf::depth_first_itr<T> const&)");

  ITR<T> litr_eql = litr;
  cout << "litr_eql (address) = " << &litr_eql << endl;

  print_subheader("Testing depth_first_itr<T>::depth_first_itr(",
                  "        depth_first_itr<T> const&)");

  ITR<T> litr_copy(litr);
  cout << "litr_copy (address) = " << &litr_copy << endl;


  print_subheader("Testing depth_first_itr<T>::clone() const");

  ITR<T>* litr_clone = litr.clone();
  cout << "litr_clone (address) = " << litr_clone << endl;

  //$$SCRIBBLE: Trying to call depth_first_itr<T>.clone()
  depth_first_itr<T>* litr0 = dynamic_cast<depth_first_itr<T>*>(&litr);
  //depth_first_itr<T>* litr0 = reinterpret_cast<depth_first_itr<T>*>(&litr);

  //depth_first_itr<T>* litr0_clone = litr0->clone();
  depth_first_itr<T>* litr0_clone = litr0->depth_first_itr<T>::clone();

  print_subheader("Testing depth_first_itr<T>::is_ancestor_of(const any* other) const");

  bool lis_ancestor_of = litr.is_ancestor_of(litr0);
  cout << "lis_ancestor_of = " << boolalpha << lis_ancestor_of << endl;
  bool lis_ancestor_of2 = litr0_clone->is_ancestor_of(&litr);
  cout << "lis_ancestor_of2 = " << boolalpha << lis_ancestor_of2 << endl;

  //============================================================================

  print_subheader("Testing depth_first_itr<T>::has_visited(",
                  "        const abstract_poset_member* xmbr) const");

  total_poset_member lmbr(&lposet, litr.index());
  cout << "lmbr.index() " << lmbr.index() << endl;
  cout << "lmbr.name() " << lmbr.name() << endl;

  bool lhas_visited = litr.has_visited(&lmbr);
  cout << "litr.has_visited(&lmbr) = " << boolalpha << lhas_visited << endl;

  lmbr.detach_from_state();

  //============================================================================

  print_subheader("Test depth_first_itr<T>::erase_cover()");

  // Need a LINK_ACTION to invoke erase_cover().

  litr.reset();
  while(!litr.is_done())
  {
    if(litr.action() == ITR<T>::LINK_ACTION)
    {
      cout << "lptr.erase_cover():   index = " << litr.index() << endl;
      litr.erase_cover();
      break;
    }
    litr.next();
  }

  //============================================================================

  // Cleanup:

  lposet.release_access();


  //============================================================================

  print_footer("End testing \"depth_first_itr\" facet");

  // Postconditions:

  // Exit:

  return ltest;

}

//==============================================================================
// FILTERED_DEPTH_FIRST_ITERATOR FACET
//==============================================================================

template <template <typename> class ITR, typename T>
bool
test_filtered_depth_first_itr_facet(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  using namespace std;

  //============================================================================

  print_header("Begin testing \"filtered_depth_first_itr\" facet");

  bool ltest = true;

  const string lposet_name = "refinable_triangle";
  if(!(xns.contains_member(lposet_name)))
  {
     make_triangle_poset(xns, lposet_name);
  }
  refinable_poset& lposet = xns.member_poset<refinable_poset>(lposet_name);
  lposet.get_read_access();
  const abstract_poset_member& lanchor = lposet.top();

  //============================================================================

  // Test constructors and assignment operator.

  print_subheader("Testing filtered_depth_first_itr()");

  ITR<T> litr0;

  print_subheader("Testing filtered_depth_first_itr(",
                  "        const abstract_poset_member&, const subposet*,...)");

  ITR<T> litr(lanchor, sheaf::DOWN, sheaf::NOT_STRICT);


  print_subheader("Testing filtered_depth_first_itr<T>(",
                  "        const abstract_poset_member&, const string& xfilter_name,)");

  ITR<T> litr2(lanchor, lposet.whole().name(), sheaf::DOWN, sheaf::NOT_STRICT);


  print_subheader("Testing filtered_depth_first_itr<T>(",
                  "        const abstract_poset_member&, scoped_index xfilter_index,)");

  ITR<T> litr3(lanchor, lposet.whole().index(), sheaf::DOWN, sheaf::NOT_STRICT);

  print_subheader("Testing filtered_depth_first_itr<T>(",
                  "        const filtered_depth_first_itr& xother)");

  ITR<T> litr_copy(litr);

  print_subheader("Testing filtered_depth_first_itr<T>&",
                  "          operator=(const filtered_depth_first_itr& xother)");

  // Use expliicit call.
  //ITR<T> litr_eql = litr;
  ITR<T> litr_eql = litr.operator=(litr);

  print_subheader("Testing filtered_depth_first_itr<T>* = ",
                  "        filtered_depth_first_itr<T>.clone()");

  ITR<T>* litr_clone = litr.clone();


  print_subheader("Testing filtered_depth_first_itr<T>::is_ancestor_of(",
                   "       const any* xother) const");

  bool lis_ancestor_of = litr.is_ancestor_of(&litr2);
  cout << "lis_ancestor_of = " << boolalpha << lis_ancestor_of << endl;

  //============================================================================

//   while(!litr.is_done())
//   {
//     switch(litr.action())
//     {
//       case ITR<T>::PREVISIT_ACTION:
//         cout << "PREVISIT_ACTION" << endl;
//         cout << " " << litr.index() << endl;
//         break;
//       case ITR<T>::LINK_ACTION:
//         cout << "LINK_ACTION" << endl;
//         cout << " " << litr.index() << endl;
//         break;
//       case ITR<T>::POSTVISIT_ACTION:
//         cout << "POSTVISIT_ACTION" << endl;
//         cout << " " << litr.index() << endl;
//         break;
//       default:
//         break;
//     }
//     litr.next();
//   }

//   litr.reset();

  //============================================================================

  print_subheader("Testing depth_first_itr<T>::put_descending(bool)");

  litr.put_descending(true);


  print_subheader("Testing depth_first_itr<T>::put_strict(bool)");

  litr.put_strict(true);


  print_subheader("Testing filtered_depth_first_itr<T>::put_anchor(",
                  "        const abstract_poset_member*)");

  //litr.put_anchor(???);


  print_subheader("Testing filtered_depth_first_itr<T>::put_anchor(",
                  "        const scoped_index& xfilter_index)");

  litr.put_anchor(lanchor.index());


  print_subheader("Testing filtered_depth_first_itr<T>::put_filter(",
                  "        const subposet* xfilter)");

  //litr.put_filter(???);


  print_subheader("Testing filtered_depth_first_itr<T>::put_filter(",
                  "        const string& xfilter_name)");

  litr.put_filter(lposet.whole().name());


  print_subheader("Testing filtered_depth_first_itr<T>::put_filter(",
                  "        const scoped_index& xfilter_index)");

  litr.put_filter(lposet.whole().index());

  //============================================================================

  // Cleanup:

  lposet.release_access();

  //============================================================================

  print_footer("End testing \"filtered_depth_first_itr\" facet");

  // Postconditions:

  // Exit:

  return ltest;

}

//==============================================================================
// LIST_POOL
//==============================================================================

template<typename T>
bool
test_list_pool_facet()
{
  // Preconditions:

  // Body:

  using namespace std;

  print_header("Begin testing \"list_pool\" facet:");

  bool ltest = true;

  // Test default constructor.

  print_subheader("Testing default constuctor.");

  list_pool<T> lpool;

  // Test get with no items.

  print_subheader("Test get() with no free items.");

  T& litem0 = lpool.get();

  // Test pool count.

  print_subheader("Test ct() with one item.");

  cout << "ct() = " << lpool.ct() << endl;

  // Test release.

  print_subheader("Test release(litem0)");

  lpool.release(litem0);

  // Test get with a free item.

  print_subheader("Test get() with a free item.");

  T& litem1 = lpool.get();

  // Test deep_size on the pool.

  print_subheader("Test deep_size.");

  cout << "deep_size(lpool, true)  = " << deep_size(lpool, true) << endl;
  cout << "deep_size(lpool. false) = " << deep_size(lpool, false) << endl;

  // Postconditions:

  // Exit:

  return ltest;
}

//==============================================================================
//==============================================================================


} // namespace sheaf

#endif // ifndef TEST_SHEAVES_IMPL_H
