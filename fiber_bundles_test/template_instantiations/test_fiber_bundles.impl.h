
// $RCSfile: test_fiber_bundles.impl.h,v $ $Revision: 1.1.2.2 $ $Date: 2012/11/08 17:24:44 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @file
/// Implementation of fiber_bundles test function templates.

#ifndef TEST_FIBER_BUNDLES_IMPL_H
#define TEST_FIBER_BUNDLES_IMPL_H

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_iostream.h"
#include "test_utils.h"
#include "test_fiber_bundles.h"

namespace fiber_bundle
{

//=============================================================================
// ABSTRACT_POSET_MEMBER FACET
//=============================================================================

template<typename VB, typename VD>
bool
test_volatile_abstract_poset_member_facet()
{
  // Preconditions:

  //require(is_base_of<VB, VD>() == true);
  bool lis_base_of = is_base_of<VB, VD>();
  require(lis_base_of == true);

  // Body:

  bool lresult = true;

  const string& lname = VB::static_class_name();

  print_header("Testing volatile type " + lname);

  // Create const and nonconst objects.

  VD ltest;
  const VD& ltestc = ltest;

  print_subheader("Testing sheaf::row_dofs(" + lname + ")");

  typedef typename VB::row_dofs_type R_TYPE;
  R_TYPE& lrow_dofs0 = sheaf::row_dofs<VB>(ltest);
  const R_TYPE& lrow_dofs1 = sheaf::row_dofs<VB>(ltestc);

  cout << "&lrow_dofs0 = " << &lrow_dofs0 << endl;
  cout << "&lrow_dofs1 = " << &lrow_dofs1 << endl;

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename V>
bool
test_volatile_abstract_poset_member_facet()
{
  // Preconditions:

  // Body:

  bool lresult = test_volatile_abstract_poset_member_facet<V, V>();

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename PB, typename PD>
bool
test_persistent_abstract_poset_member_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  //require(is_base_of<PB, PD>() == true);
  bool lis_base_of = is_base_of<PB, PD>();
  require(lis_base_of == true);

  // Body:

  bool lresult = true;

  const string& lname = PB::static_class_name();

  print_header("Testing persistent type " + lname);

  // Create a persistent object.

  typename PD::host_type& lhost = xns.new_fiber_space<PD>();
  lhost.get_read_write_access(true);
  
  PB* ltest = new PB(&lhost);
  ltest->put_name(lname, true, false);

  // Need a const version also.

  const PB* ltestc = ltest;

  print_subheader("Testing sheaf::row_dofs(" + lname + ")");

  typedef typename PB::row_dofs_type R_TYPE;

  R_TYPE& lrow_dofs0 = sheaf::row_dofs<PB>(*ltest);
  R_TYPE& lrow_dofs1 = sheaf::row_dofs<PB>(*ltest, true);

  const R_TYPE& lrow_dofs2 = sheaf::row_dofs<PB>(*ltestc);
  const R_TYPE& lrow_dofs3 = sheaf::row_dofs<PB>(*ltestc, true);

  cout << "&lrow_dofs0 = " << &lrow_dofs0 << endl;
  cout << "&lrow_dofs1 = " << &lrow_dofs1 << endl;
  cout << "&lrow_dofs2 = " << &lrow_dofs2 << endl;
  cout << "&lrow_dofs3 = " << &lrow_dofs3 << endl;


  print_subheader("Testing sheaf::table_dofs(" + lname + ")");

  typedef typename PB::table_dofs_type T_TYPE;

  T_TYPE& ltable_dofs0 = sheaf::table_dofs<PB>(*ltest);
  T_TYPE& ltable_dofs1 = sheaf::table_dofs<PB>(*ltest, true);

  const T_TYPE& ltable_dofs2 = sheaf::table_dofs<PB>(*ltestc);
  const T_TYPE& ltable_dofs3 = sheaf::table_dofs<PB>(*ltestc, true);

  cout << "&ltable_dofs0 = " << &ltable_dofs0 << endl;
  cout << "&ltable_dofs1 = " << &ltable_dofs1 << endl;
  cout << "&ltable_dofs2 = " << &ltable_dofs2 << endl;
  cout << "&ltable_dofs3 = " << &ltable_dofs3 << endl;

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename P>
bool
test_persistent_abstract_poset_member_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  // Body:

  bool lresult = test_persistent_abstract_poset_member_facet<P, P>(xns);

  // Postconditions:

  // Exit:

  return lresult;
}


template<typename B, typename D>
bool
is_base_of()
{
  D derived;
  bool result = dynamic_cast<B*>(&derived) != 0;

  return result;
}

//============================================================================
// NAMESPACE_POSET FACET
//============================================================================

template<typename S>
bool
test_fiber_bundles_namespace_poset_facet(fiber_bundles_namespace& xns,
                                         S& lspace)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  bool lresult = true;

  print_subheader("Testing bool contains_path(const poset_path&, bool) const");
  const poset_path& lpath = lspace.path();
  bool ltest = xns.contains_path<S>(lpath, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  print_subheader("Testing bool contains_path(const scoped_index&, bool) const");
  const scoped_index& lindex = lspace.index();
  ltest = xns.contains_poset<S>(lindex, true);

  cout << "ltest = " << boolalpha << ltest << endl;
  cout << endl;

  print_subheader("Testing bool contains_path(const string&, bool) const");
  const string& lname = lspace.path().poset_name();
  ltest = xns.contains_poset<S>(lname, true);

  cout << "ltest = " << boolalpha << ltest << endl;
  cout << endl;


  print_subheader("Testing path_is_auto_read_accessible(const poset_path&, bool) const");
  ltest = xns.path_is_auto_read_accessible<S>(lpath, true);
  cout << "ltest = " << boolalpha << ltest << endl;


  print_subheader("Testing path_is_auto_read_write_accessible(const poset_path&, bool) const");
  ltest = xns.path_is_auto_read_write_accessible<S>(lpath, true);
  cout << "ltest = " << boolalpha << ltest << endl;


  print_subheader("Testing path_is_auto_read_available(const poset_path&, bool) const");
  ltest = xns.path_is_auto_read_available<S>(lpath, true);
  cout << "ltest = " << boolalpha << ltest << endl;


  print_subheader("Testing path_is_auto_read_write_available(const poset_path&, bool) const");
  ltest = xns.path_is_auto_read_write_available<S>(lpath, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  //============================================================================

  //$$SCRIBBLE: Purposely make these return false (temporarily).

  const string lname2 = "dummy_space_path";
  const arg_list largs;

  print_subheader("Testing arg_is_auto_read_accessible(const string&, const arg_list&, bool) const");
  ltest = xns.arg_is_auto_read_accessible<S>(lname2, largs, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  print_subheader("Testing arg_is_auto_read_write_accessible(const string&, const arg_list&, bool) const");
  ltest = xns.arg_is_auto_read_write_accessible<S>(lname2, largs, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  print_subheader("Testing arg_is_auto_read_available(const string&, const arg_list&, bool) const");
  ltest = xns.arg_is_auto_read_available<S>(lname2, largs, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  print_subheader("Testing arg_is_auto_read_write_available(const string&, const arg_list&, bool) const");
  ltest = xns.arg_is_auto_read_write_available<S>(lname2, largs, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  //============================================================================

  print_subheader("Testing S* member_poset(const scoped_index&, bool)");
  S* lspace0 = xns.member_poset<S>(lindex, true);
  cout << "lspace0 = " << lspace0 << endl;

  print_subheader("Testing S* member_poset(const string&, bool)");
  S* lspace1 = xns.member_poset<S>(lname, true);
  cout << "lspace1 = " << lspace1 << endl;

  print_subheader("Testing S* member_poset(const poset_path& xpath, bool)");
  S* lspace2 = xns.member_poset<S>(lpath, true);
  cout << "lspace2 = " << lspace2 << endl;

 //============================================================================

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T>
bool
test_fiber_bundles_namespace_poset_facet(fiber_bundles_namespace& xns,
                                         const poset_path& lbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string lname = "test_section_space_" + T::static_class_name();

  print_footer("End testing " + lname);

  bool lresult = true;

  typedef typename T::host_type S;

  S& lspace = xns.new_section_space<T>(lname, lbase_path);

  lresult &= test_fiber_bundles_namespace_poset_facet(xns, lspace);

  print_footer("End testing " + lname);

  // Postconditions:

  // Exit:

  return lresult;
}


template<typename T>
bool
test_fiber_bundles_namespace_poset_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string lname = T::static_class_name() + "_space";

  print_header("Begin testing " + lname);

  bool lresult = true;

  typedef typename T::host_type S;

  S& lspace = xns.new_fiber_space<T>(lname);

  lresult &= test_fiber_bundles_namespace_poset_facet(xns, lspace);

  print_footer("End testing " + lname);

  // Postconditions:

  // Exit:

  return lresult;
}

template<typename T, typename S>
bool
test_fiber_bundles_namespace_poset_facet(fiber_bundles_namespace& xns,
                                         const poset_path& lbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string lname = "test_section_space_" + T::static_class_name();

  print_footer("End testing " + lname);

  bool lresult = true;

  S& lspace = xns.new_section_space<T>(lname, lbase_path);

  lresult &= test_fiber_bundles_namespace_poset_facet(xns, lspace);

  print_footer("End testing " + lname);

  // Postconditions:

  // Exit:

  return lresult;
}

//============================================================================
//============================================================================


} // namespace fiber_bundle

#endif // ifndef TEST_FIBER_BUNDLES_IMPL_H
