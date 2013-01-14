

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation of fiber test function templates.

#ifndef TEST_FIBERS_IMPL_H
#define TEST_FIBERS_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TEST_FIBERS_H
#include "test_fibers.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef STD_CSTDLIB_H
#include "std_cstdlib.h"
#endif

#ifndef STD_SSTREAM_H
#include "std_sstream.h"
#endif

#ifndef TEST_UTILS_H
#include "test_utils.h"
#endif

namespace fiber_bundle
{

template <typename T>
void print_fiber(const T& xfiber)
{
  // Preconditions:

  // Body:

  cout << xfiber << endl;

  // Postconditions:

  // Exit:

}

template <typename T>
void print_result(const string& xtext, const T& xfiber)
{
  // Preconditions:

  require(precondition_of(print_fiber(xfiber)));

  // Body:

  cout << xtext;
  print_fiber(xfiber);

  // Postconditions:

  ensure(postcondition_of(print_fiber(xfiber)));

  // Exit:
}

template <typename T>
void print_fiber(const T& xfiber, const string& xindent, bool xauto_access)
{
  // Preconditions:

  require(xfiber.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    xfiber.get_read_access();
  }

  cout << xindent << xfiber << endl;

  if(xauto_access)
  {
    xfiber.release_access();
  }

  // Postconditions:

  // Exit:

}

template <typename T>
void print_result(const string& xtext,
                  const T& xfiber,
                  const string& xindent,
                  bool xauto_access)
{
  // Preconditions:

  require(precondition_of(print_fiber(xfiber, xindent, xauto_access)));

  // Body:

  cout << xtext;
  print_fiber(xfiber, xindent, xauto_access);

  // Postconditions:

  ensure(postcondition_of(print_fiber(xfiber, xindent, xauto_access)));

  // Exit:
}

template <typename P>
void
test_persistent_scalar_type(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:
  
  typename P::host_type& lhost = xns.new_fiber_space<P>();
  
  lhost.get_read_write_access(true);
  
  test_persistent_type<P>(lhost);

  lhost.release_access();

  // Exit:
}

///
template <typename P>
void
test_persistent_vector_type(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_fiber_space<P>();
  lhost.get_read_write_access(true);
  
  test_persistent_type<P>(lhost);

  lhost.release_access();

  // Exit:
}

///
template <typename P>
void
test_persistent_tensor_type(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_fiber_space<P>();
  lhost.get_read_write_access(true);
  
  test_persistent_type<P>(lhost);

  lhost.release_access();

  // Exit:
}

///
template <typename P>
void
test_persistent_jacobian_type(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_jacobian_space<P>();
  lhost.get_read_write_access(true);
  
  test_persistent_type<P>(lhost);

  lhost.release_access();

  // Exit:
}

///
template <typename P>
void
test_persistent_group_type(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_group_space<P>();
  lhost.get_read_write_access(true);
  
  test_persistent_type<P>(lhost);

  lhost.release_access();

  // Exit:
}

///
template <typename P>
void
test_persistent_type(typename P::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  const string& lfiber_name = P::static_class_name();

  print_header("Testing persistent type " + lfiber_name);

  //============================================================================

  persistent_type* lfiber = new persistent_type(&xhost);

  const string lmember_name("test_fiber");
  lfiber->put_name(lmember_name, true, false);

  const string& lclass_name = lfiber->class_name();
  cout << "lclass_name = " << lclass_name << endl;

  //$$SCRIBBLE: gl classes have no factor_ct().
  //int lfactor_ct = lfiber->factor_ct();
  //cout << "lfactor_ct = " << lfactor_ct << endl;

  //$$SCRIBBLE: Inconsistency amoung classes here???
  //persistent_type* lfiber2 = new persistent_type(lfiber);
  //persistent_type* lfiber2 = new persistent_type(*lfiber);

  //persistent_type lfiber3 = *lfiber;

  const scoped_index lindex = lfiber->index();

  const poset* lposet = dynamic_cast<poset*>(&xhost);
  persistent_type* lfiber4 = new persistent_type(lposet, lmember_name);
  persistent_type* lfiber5 = new persistent_type(lposet, lindex);
  persistent_type* lfiber6 = new persistent_type(lposet, lindex.hub_pod());

  persistent_type* lfiber7 = lfiber5->clone();

  //============================================================================

  persistent_type lfiber3a;
  persistent_type& lfiber3b = lfiber3a.operator=(lfiber3a);

  //lfiber3a.detach_from_state();
  lfiber3b.detach_from_state();

  //============================================================================

  lfiber->detach_from_state();
  //lfiber2->detach_from_state();
  //lfiber3.detach_from_state();
  lfiber4->detach_from_state();
  lfiber5->detach_from_state();
  lfiber6->detach_from_state();
  lfiber7->detach_from_state();

  delete lfiber;
  //delete lfiber2;
  delete lfiber4;
  delete lfiber5;
  delete lfiber6;
  delete lfiber7;

  //============================================================================

  persistent_type* test1 = new persistent_type(&xhost);
  test1->put_name("test1", true, false);

  for(int i=0; i<test1->d(); ++i)
  {
    test1->put_component(i, i+1);
  }

  persistent_type* test2 = new persistent_type(&xhost);
  test2->put_name("test2", true, false);

  for(int i=0; i<test2->d(); ++i)
  {
    test2->put_component(i, i+1+test2->d());
  }

  cout << lfiber_name << " test1:";
  for(int i=0; i<test1->d(); i++)
  {
    cout << " " << test1->component(i);
  }
  cout << endl;

  cout << lfiber_name << " test2:";
  for(int i=0; i<test2->d(); i++)
  {
    cout << " " << test2->component(i);
  }
  cout << endl;
  
  test1->detach_from_state();
  test2->detach_from_state();

  delete test1;
  delete test2;

  //============================================================================

  //$$SCRIBBLE: Really tuple facet functions.
  //$$SCRIBBLE: These don't work! Must have never been tested.

//   persistent_type lfiber6(lposet, lmember_name);
//   int lp = lfiber6.p();

//   //virtual tp* new_tp(int xp, bool xauto_access) const;

//   tp* ltp = lfiber6.new_tp(lp, true);

//   //virtual atp* new_atp(int xp, bool xauto_access) const;

//   atp* latp = lfiber6.new_atp(lp, true);

//   //virtual stp* new_stp(int xp, bool xauto_access) const;

//   stp* lstp = lfiber6.new_stp(lp, true);

//   lfiber6.release_access();
//   lfiber6.detach_from_state();

//   delete ltp;
//   delete latp;
//   delete lstp;

  //============================================================================

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_volatile_type()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  typedef typename P::row_dofs_type row_dofs_type;
  typedef typename P::table_dofs_type table_dofs_type;
  const string& lfiber_name = volatile_type::static_class_name();

  print_header("Testing volatile type " + lfiber_name);

  volatile_type test01;
  for(int i=0; i<test01.d(); ++i)
  {
    test01.put_component(i, i+1);
  }
  cout << lfiber_name << " test01: " << test01 << endl;

  volatile_type test02;
  for(int i=0; i<test01.d(); ++i)
  {
    test02[i] = i+1+test01.d();
  }
  cout << lfiber_name << " test02: " << test02 << endl;
  cout << endl;

  // Test copy constructor.

  volatile_type test03(test02);
  cout << lfiber_name << " test03(test02): " << test03 << endl;
  cout << endl;

  // Test assignment.

  volatile_type test04 = test03;
  cout << lfiber_name << " test04 = test03: " << test04 << endl;
  cout << endl;

  // Test constructor taking a row_dof_type argument.

  row_dofs_type lrow_dofs;
  for(int i=0; i<lrow_dofs.d(); ++i)
  {
    lrow_dofs[i] = i+1+2*lrow_dofs.d();
  }

  volatile_type test05(lrow_dofs);
  cout << lfiber_name << " test05(lrow_dofs): " << test05 << endl;
  cout << endl;

  // Test table dofs.

  table_dofs_type tdt = test01.table_dofs();
  cout << endl;
  cout << "table dofs:" << tdt << endl;  

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_scalar_conversions(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_scalar_space<P>();
  lhost.get_read_write_access(true);
  
  test_conversions<P>(lhost);

  // Exit:
}

///
template <typename P>
void
test_vector_conversions(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_vector_space<P>();
  lhost.get_read_write_access(true);
  
  test_conversions<P>(lhost);

  // Exit:
}

///
template <typename P>
void
test_tensor_conversions(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_tensor_space<P>();
  lhost.get_read_write_access(true);
  
  test_conversions<P>(lhost);

  // Exit:
}

///
template <typename P>
void
test_jacobian_conversions(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_jacobian_space<P>();
  lhost.get_read_write_access(true);
  
  test_conversions<P>(lhost);

  // Exit:
}

///
template <typename P>
void
test_group_conversions(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typename P::host_type& lhost = xns.new_group_space<P>();
  lhost.get_read_write_access(true);
  
  test_conversions<P>(lhost);

  // Exit:
}

///
template <typename P>
void
test_conversions(typename P::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::volatile_type volatile_type;
  typedef typename P::row_dofs_type row_dofs_type;

  typedef typename fiber_traits<P>::matrix_type matrix_type;
  bool has_matrix_type = fiber_traits<P>::has_matrix_type();

  const string& lfiber_name = P::static_class_name();
  const string& lname_vt = volatile_type::static_class_name();
  const string& lname_rdt = row_dofs_type::static_class_name();

  print_header("Testing conversions for " + lfiber_name);

  // ROW_DOFS_TYPE->ROW_DOFS_TYPE:

  cout << endl;
  cout << "Convert row_dofs_type to row_dofs_type:" << endl;
  cout << endl;

  row_dofs_type lrdt1;
  for(int i=0; i<lrdt1.d(); ++i) { lrdt1[i] = i+1; }
  cout << lname_rdt << " lrdt1 = " << lrdt1 << endl;
  cout << endl;

  row_dofs_type lrdt2 = lrdt1;
  cout << lname_rdt << " lrdt2 = lrdt1:" << lrdt2 << endl;
  cout << endl;

  row_dofs_type lrdt3(lrdt1);
  cout << lname_rdt << " lrdt3(lrdt1): " << lrdt3 << endl;
  cout << endl;

  // ROW_DOFS_TYPE->VOLATILE_TYPE:

  cout << endl;
  cout << "Convert row_dofs_type to volatile_type:" << endl;
  cout << endl;

  volatile_type lite1 = lrdt1;
  cout << lname_vt << "  lite1 = lrdt1: " << lite1 << endl;
  cout << endl;

  volatile_type lite2(lrdt1);
  cout << lname_vt << "  lite2(lrdt1):  " << lite2 << endl;
  cout << endl;

  volatile_type lite3;
  lite3 = lrdt1;
  cout << lname_vt << "  lite3; lite3 = lrdt1: " << lite3 << endl;
  cout << endl;

  // VOLATILE_TYPE->ROW_DOFS_TYPE:

  cout << endl;
  cout << "Convert volatile_type to row_dofs_type:" << endl;
  cout << endl;

  row_dofs_type lrdt7 = lite1;
  cout << lname_rdt << " lrdt7 = lite1: " << lrdt7 << endl;
  cout << endl;

  row_dofs_type lrdt8(lite1);
  cout << lname_rdt << " lrdt8(lite1): " << lrdt8 << endl;
  cout << endl;

  row_dofs_type lrdt9;
  lrdt9 = lite1;
  cout << lname_rdt << " lrdt9; lrdt9 = lite1: " << lrdt9 << endl;
  cout << endl;

  // VOLATILE_TYPE->VOLATILE_TYPE:

  cout << endl;
  cout << "Convert volatile_type to volatile_type:" << endl;
  cout << endl;

  volatile_type lite7 = lite1;
  cout << lname_vt << " lite7: " << lite7 << endl;
  cout << endl;

  volatile_type lite8(lite1);
  cout << lname_vt << " lite8: " << lite8 << endl;
  cout << endl;

  volatile_type lite9;
  lite9 = lite1;
  cout << lname_vt << " lite9; lrdt9 = lite1: " << lite9 << endl;
  cout << endl;

  // ROW_DOFS_TYPE->PERSISTENT_TYPE:

  cout << endl;
  cout << "Convert row_dofs_type to persistent_type:" << endl;
  cout << endl;
  persistent_type p6(xhost, lrdt1, true);
  p6.put_name("p6", true, false);

  cout << lfiber_name << " p6(*host, lrdt1, true): p6 = " << p6 << endl;
  cout << endl;

  persistent_type p3(&xhost, true);
  p3.put_name("p3", true, false);
  p3 = lrdt1;

  cout << lfiber_name << " p3(host, true); p3 = lrdt1: p3 = " << p3 << endl;
  cout << endl;

  // PERSISTENT_TYPE->ROW_DOFS_TYPE:

  cout << endl;
  cout << "Convert persistent_type to row_dofs_type:" << endl;
  cout << endl;

  row_dofs_type lrdt10 = p3;
  cout << lname_rdt << " lrdt10 = = p3: lrdt10 = " << lrdt10 << endl;
  cout << endl;

  row_dofs_type lrdt11(p3);
  cout << lname_rdt << " lrdt11(p3): lrdt11 = " << lrdt11 << endl;
  cout << endl;

  row_dofs_type lrdt12;
  lrdt12 = p3;
  cout << lname_rdt << " lrdt12; lrdt12 = p3: lrdt12 =  " << lrdt12 << endl;
  cout << endl;

  // PERSISTENT_TYPE->VOLATILE_TYPE:
  //   Virtual conversion to the associated volatile type.

  test_virtual_conversions<P>(xhost);

  // Test matrix conversions if we have a matrix type and
  // it's not a gl2 or gl3 (have matrix types but the number
  // of components is twice the size of the matrix.

  if((has_matrix_type) && (lfiber_name.find("gl" != 0)))
  {
    test_matrix_type_conversions<P>();
  }

  // Cleanup.

  p3.detach_from_state();
  p6.detach_from_state();

  xhost.release_access();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_virtual_conversions(typename P::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::volatile_type volatile_type;
  typedef typename P::row_dofs_type row_dofs_type;

  const string& lfiber_name = P::static_class_name();
  const string& lname_vt = volatile_type::static_class_name();
  const string& lname_rdt = row_dofs_type::static_class_name();

  // VOLATILE_TYPE -> PERSISTENT_TYPE:

  cout << endl;
  cout << "Convert volatile type to persistent type:" << endl;
  cout << endl;

  volatile_type lite1;
  for(int i=0; i<lite1.d(); ++i) { lite1[i] = i+1; }
  cout << lname_vt << " lite1 = " << lite1 << endl;
  cout << endl;

  persistent_type p1(xhost, lite1, true);
  p1.put_name("p1", true, false);
  cout << lfiber_name << " p1(*host, lite11, true): p1 = " << p1 << endl;
  cout << endl;

  persistent_type p2(&xhost, true);
  p2.put_name("p2", true, false);
  p2 = lite1;
  cout << lfiber_name << " p2(*host, true); p2 = lite1: p2 = " << p2 << endl;
  cout << endl;

  // PERSISTENT_TYPE->VOLATILE_TYPE:
  //   Virtual conversion to the associated volatile type.

  cout << endl;
  cout << "Convert persistent type to volatile type:" << endl;
  cout << endl;

  volatile_type* lite_ptr = static_cast<volatile_type*>(p2.lite_type());
  cout << lname_vt << "* lite_ptr = p2.lite_type(): *lite_ptr ="
       << *lite_ptr << endl;
  cout << endl;
  delete lite_ptr;

  // Cleanup.

  p1.detach_from_state();
  p2.detach_from_state();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_matrix_type_conversions()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::volatile_type volatile_type;
  typedef typename P::row_dofs_type row_dofs_type;
  const string& lfiber_name = P::static_class_name();

  typedef typename fiber_traits<P>::matrix_type matrix_type;

  print_subheader("Testing matrix_type conversions for " + lfiber_name);

  // MATRIX_TYPE->MATRIX_TYPE:

  cout << endl;
  cout << "Convert matrix_type to matrix_type:" << endl;
  cout << endl;

  matrix_type lmt1;

  int ld = lmt1.d();  
  for(int i=0; i<ld; ++i) { lmt1.components[i] = ld-i; }
  cout << "  lmt1 = " << endl << lmt1 << endl;

  matrix_type lmt2 = lmt1;
  cout << "  matrix_type lmt2 = lmt1: " << endl << lmt2 << endl;

  matrix_type lmt3(lmt1);
  cout << "  matrix_type lmt3(lmt1): " << endl << lmt3 << endl;

  // MATRIX_TYPE->ROW_DOFS_TYPE:

  cout << "Convert matrix_type to row_dofs_type:" << endl;
  cout << endl;
 
  row_dofs_type lrdt4 = reinterpret_cast<row_dofs_type&>(lmt1);
  cout << "  row_dofs_type lrdt4 = lmt1: " << lrdt4 << endl;
  cout << endl;

  row_dofs_type lrdt5(reinterpret_cast<row_dofs_type&>(lmt1));
  cout << "  row_dofs_type lrdt5(lmt1) " << lrdt5 << endl;
  cout << endl;

  row_dofs_type lrdt6;
  lrdt6 = reinterpret_cast<row_dofs_type&>(lmt1);
  cout << "  row_dofs_type lrdt6; lrdt6 = lmt1: " << lrdt6 << endl;
  cout << endl;

  // ROW_DOFS_TYPE->MATRIX_TYPE:

  cout << endl;
  cout << "Convert row_dofs_type to matrix_type:" << endl;
  cout << endl;

  matrix_type lmt4 = reinterpret_cast<matrix_type&>(lrdt6);
  cout << "  matrix_type lmt4 = lrdt6:" << endl << lmt4 << endl;

  matrix_type lmt5(reinterpret_cast<matrix_type&>(lrdt6));
  cout << "  matrix_type lmt5(lrdt6):" << endl << lmt5 << endl;

  matrix_type lmt6;
  lmt6 = reinterpret_cast<matrix_type&>(lrdt6);
  cout << "  matrix_type lmt6; lmt6 = lrdt6:" << endl << lmt6 << endl;

  // MATRIX_TYPE->VOLATILE_TYPE:

  volatile_type lite4 = reinterpret_cast<row_dofs_type&>(lmt1);
  cout << "  volatile_type lite4 = " << lite4 << endl;
  cout << endl;

  volatile_type lite5(reinterpret_cast<row_dofs_type&>(lmt1));
  cout << "  volatile_type lite5 = " << lite5 << endl;
  cout << endl;

  volatile_type lite6;
  lite6 = reinterpret_cast<row_dofs_type&>(lmt1);
  cout << "  volatile_type lite6 = " << lite6 << endl;
  cout << endl;

  // VOLATILE_TYPE->MATRIX_TYPE:

  row_dofs_type lrdt7 = lite4; 
  matrix_type lmt7 = reinterpret_cast<matrix_type&>(lrdt7);
  cout << "  matrix_type lmt7 = " << endl << lmt7 << endl;

  matrix_type lmt8(reinterpret_cast<matrix_type&>(lrdt7)); 
  cout << "  matrix_type lmt8 = " << endl << lmt8 << endl;

  matrix_type lmt9;
  lmt9 = reinterpret_cast<matrix_type&>(lrdt7);
  cout << "  matrix_type lmt9 = " << endl << lmt9 << endl;

  // Postconditions:

  // Exit:
}

//=============================================================================
// ATP FACET
//=============================================================================

template <typename P0, typename P1, typename PR>
void
test_hook_product(fiber_bundles_namespace& xns)
{
  // Precontitions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("Testing hook (interior) product of atp facet");

  test_volatile_hook_product<P0, P1, PR>();
  test_persistent_hook_product<P0, P1, PR>(xns);

  // Postconditions:

  // Exit:
}

template <typename P0, typename P1, typename PR>
void
test_volatile_hook_product()
{

#ifndef _WIN32

  // Precontitions:

  // Body:

  typedef typename P0::volatile_type V0;
  typedef typename P1::volatile_type V1;
  typedef typename PR::volatile_type VR;

  const string& lname_0 = V0::static_class_name();
  const string& lname_1 = V1::static_class_name();
  const string& lname_r = VR::static_class_name();
  const string lop_string = lname_0 + " _| " + lname_1 + " = " + lname_r;
  print_header("Testing hook product for: " + lop_string);

  //============================================================================

  // Create volatile fibers for testing.

  V0 x0;
  for(int i=0; i<x0.d(); ++i)
  {
    x0.put_component(i, i+1);
  }

  V1 x1;
  for(int i=0; i<x1.d(); ++i)
  {
    x1.put_component(i, i+101);
  }

  cout << lname_0 << " x0:" <<  x0 << endl;
  cout << lname_1 << " x1:" <<  x1 << endl;
  cout << endl;

  // Compute the result.

  VR result;
  hook(x0, x1, result);
  print_result("hook(x0, x1, result):\n result (" + lname_r + ") = ", result);
  cout << endl;

  VR* result2 = hook(x0, x1);
  print_result(lname_r + "* result2 = hook(x0, x1):\n *result2 = ", *result2);
  cout << endl;
  delete result2;

  //============================================================================

  // Postconditions:

  // Exit:
#endif
}

template <typename P0, typename P1, typename PR>
void
test_persistent_hook_product(fiber_bundles_namespace& xns)
{
  // Precontitions:

  require(xns.state_is_read_write_accessible());

  // Body:

  ///@issue: Has to be the same as P1 & PR.  How do we want to require this?

  typename P0::host_type& lhost_0 = new_host_space<P0>(xns);
  lhost_0.get_read_write_access(true);
  typename P1::host_type& lhost_1 = new_host_space<P1>(xns);
  lhost_1.get_read_write_access(true);
  typename PR::host_type& lhost_r = new_host_space<PR>(xns);
  lhost_r.get_read_write_access(true);  

  const string lop_string = lhost_0.name() + " _| " + lhost_1.name() + " = " + lhost_r.name();
  print_header("Testing hook product for: " + lop_string);

  P0 x0(&lhost_0);
  P1 x1(&lhost_1);
  PR result(&lhost_r);

  for(int i=0; i<x0.d(); ++i)
  {
    x0.put_component(i, i+1);
  }

  for(int i=0; i<x1.d(); ++i)
  {
    x1.put_component(i, i+101);
  }

  cout << x0.name() << " x0:" <<  x0 << endl;
  cout << x1.name() << " x1:" <<  x1 << endl;
  cout << endl;

  hook(x0, x1, result, false);
  print_result("hook(x0, x1, result):\n result (" + result.name() + ") = ", result);
  cout << endl;

  x0.detach_from_state();
  x1.detach_from_state();
  result.detach_from_state();

  lhost_0.release_access();
  lhost_1.release_access();
  lhost_r.release_access();

  // Postconditions:

  // Exit:
}

template <typename P0, typename PR>
void
test_star_operator(fiber_bundles_namespace& xns)
{
  // Precontitions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("Testing Hodge star operator of atp facet");

  test_volatile_star_operator<P0, PR>();
  test_persistent_star_operator<P0, PR>(xns);

  // Postconditions:

  // Exit:
}

template <typename P0, typename PR>
void
test_volatile_star_operator()
{
  // Precontitions:

  // Body:

  typedef typename P0::volatile_type V0;
  typedef typename PR::volatile_type VR;

  const string& lname_0 = V0::static_class_name();
  const string& lname_r = VR::static_class_name();
  const string lop_string = "*" + lname_0 + " = " + lname_r;
  print_header("Testing Hodge star operator for: " + lop_string);

  //============================================================================

  // Create volatile fibers for testing.

  V0 x0;
  for(int i=0; i<x0.d(); ++i)
  {
    x0.put_component(i, i+1);
  }

  cout << lname_0 << " x0:" <<  x0 << endl;
  cout << endl;
 
  // Compute the results.

  VR result;
  star(x0,  result);
  print_result(lname_r + " result; star(x0, result): result = ", result);
  cout << endl;

  //============================================================================

  // Postconditions:

  // Exit:
}

template <typename P0, typename PR>
void
test_persistent_star_operator(fiber_bundles_namespace& xns)
{
  // Precontitions:

  require(xns.state_is_read_write_accessible());

  // Body:

//   ///@issue: Has to be the same as P1 & PR.  How do we want to require this?

//   typedef typename P0::vector_space_type vector_space_type;

  const string& lname_0 = P0::static_class_name();
  const string& lname_r = PR::static_class_name();
  const string lop_string = "*" + lname_0 + " = " + lname_r;
  print_header("Testing Hodge star operator for: " + lop_string);

  typename P0::host_type& lhost_0 = new_host_space<P0>(xns);
  lhost_0.get_read_write_access(true);
  typename PR::host_type& lhost_r = new_host_space<PR>(xns);
  lhost_r.get_read_write_access(true);  

  P0 x0(&lhost_0);
  PR result(&lhost_r);

  for(int i=0; i<x0.d(); ++i)
  {
    x0.put_component(i, i+1);
  }

  cout << lname_0 << " x0:" <<  x0 << endl;
  cout << endl;

  star(x0, result, false);
  print_result("star(x0, result): result (" + lname_r + ") = ", result);
  cout << endl;

  x0.detach_from_state();
  result.detach_from_state();
  lhost_0.release_access();
  lhost_r.release_access();

  // Postconditions:

  // Exit:
}

template <typename P0, typename P1, typename PR>
void
test_wedge_product(fiber_bundles_namespace& xns)
{
  // Precontitions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("Testing wedge (exterior) product of atp facet");

  test_volatile_wedge_product<P0, P1, PR>();
  test_persistent_wedge_product<P0, P1, PR>(xns);

  // Postconditions:

  // Exit:
}

template <typename P0, typename P1, typename PR>
void
test_volatile_wedge_product()
{

#ifndef _WIN32

  // Preconditions:

  // Body:

  typedef typename P0::volatile_type V0;
  typedef typename P1::volatile_type V1;
  typedef typename PR::volatile_type VR;

  const string& lname_0 = V0::static_class_name();
  const string& lname_1 = V1::static_class_name();
  const string& lname_r = VR::static_class_name();
  const string lop_string = lname_0 + " ^ " + lname_1 + " = " + lname_r;
  print_header("Testing wedge product for: " + lop_string);

  //============================================================================

  // Create volatile fibers for testing.

  V0 x0;
  for(int i=0; i<x0.d(); ++i)
  {
    x0.put_component(i, i+1);
  }

  V1 x1;
  for(int i=0; i<x1.d(); ++i)
  {
    x1.put_component(i, i+101);
  }

  cout << lname_0 << "x0:" <<  x0 << endl;
  cout << lname_1 << "x1:" <<  x1 << endl;
  cout << endl;

  // Compute the results.

  VR result;
  wedge(x0, x1, result);
  print_result(lname_r + " result; wedge(x0, x1, result): result = ", result);
  cout << endl;

  VR* result2 = wedge(x0, x1);
  print_result(lname_r + "* result2 = wedge(x0, x1): *result2 = ", *result2);
  cout << endl;
  delete result2;

  //============================================================================

  // Postconditions:

  // Exit:

#endif

}

template <typename P0, typename P1, typename PR>
void
test_persistent_wedge_product(fiber_bundles_namespace& xns)
{
  // Precontitions:

  require(xns.state_is_read_write_accessible());

  // Body:

  ///@issue: Has to be the same as P1 & PR.  How do we want to require this?

//   typedef typename P0::vector_space_type vector_space_type;

  const string& lname_0 = P0::static_class_name();
  const string& lname_1 = P1::static_class_name();
  const string& lname_r = PR::static_class_name();
  const string lop_string = lname_0 + " ^ " + lname_1 + " = " + lname_r;
  print_header("Testing wedge product for: " + lop_string);

  typename P0::host_type& lhost_0 = new_host_space<P0>(xns);
  lhost_0.get_read_write_access(true);
  typename P1::host_type& lhost_1 = new_host_space<P1>(xns);
  lhost_1.get_read_write_access(true);
  typename PR::host_type& lhost_r = new_host_space<PR>(xns);
  lhost_r.get_read_write_access(true);

  P0 x0(&lhost_0);
  P1 x1(&lhost_1);
  PR result(&lhost_r);

  for(int i=0; i<x0.d(); ++i)
  {
    x0.put_component(i, i+1);
  }

  for(int i=0; i<x1.d(); ++i)
  {
    x1.put_component(i, i+101);
  }

  cout << lname_0 << "x0:" <<  x0 << endl;
  cout << lname_1 << "x1:" <<  x1 << endl;
  cout << endl;

  wedge(x0, x1, result, false);
  print_result("wedge(x0, x1, result): result (" + lname_r + ") = ", result);
  cout << endl;

  //============================================================================

  x0.detach_from_state();
  x1.detach_from_state();
  result.detach_from_state();
  lhost_0.release_access();
  lhost_1.release_access();
  lhost_r.release_access();

  // Postconditions:

  // Exit:
}

//=============================================================================
// VD FACET
//=============================================================================

template <typename P>
void
test_volatile_vd_facet()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  typedef typename volatile_type::value_type value_type;
  const string& lname = volatile_type::static_class_name();

  print_subheader("Testing volatile type \"" + lname + "\"");

  volatile_type test01;
  volatile_type test02;
  for(int i=0; i<test01.d(); ++i)
  {
    test01.put_component(i, i+1);
    test02.put_component(i, i+1+test01.d());
  }
  cout << lname << " test01:" << test01 << endl;
  cout << lname << " test02:" << test02 << endl;
  cout << endl;

  volatile_type* test10 = add(test01, test02);
  print_result(lname + "* test10 = add(test01, test02):\n *test10 = ", *test10);
  cout << endl;
  delete test10;

  volatile_type* test11 = test01 + test02;
  print_result(lname + "* test11 = test01 + test02:\n *test11 = ", *test11);
  cout << endl;
  delete test11;

  volatile_type test12;
  add(test01, test02, test12);
  print_result("add(test01, test02, test12):\n test12 = ", test12);
  cout << endl;

  add_equal(test12, test01);
  print_result("add_equal(test12, test01):\n test12 = ", test12);
  cout << endl;

  test12 += test01;
  print_result("test12 += test01:\n test12 = ", test12);
  cout << endl;

  volatile_type* test13 = subtract(test01, test02);
  print_result(lname + "* test13 = subtract(test01, test02):\n *test13 = ",
               *test13);
  cout << endl;
  delete test13;

  volatile_type* test14 = test01 - test02;
  print_result(lname + "* test14 = test01 - test02:\n *test14 = ", *test14);
  cout << endl;
  delete test14;

  volatile_type test15;
  subtract(test01, test02, test15);
  print_result("subtract(test01, test02, test15):\n test15 = ", test15);
  cout << endl;

  subtract_equal(test15, test01);
  print_result("subtract_equal(test15, test01):\n test15 = ", test15);
  cout << endl;

  test15 -= test01;
  print_result("test15 -= test01:\n test15 = ", test15);
  cout << endl;

  volatile_type* test17 = multiply(test02, 2.0);
  print_result(lname + "* test17 = multiply(test02, 2):\n *test17 = ", *test17);
  cout << endl;

  /// @hack tests for opr*, multiply_equal, and opr*= disabled
  /// until explicit instantiations added to all fiber types.
  //   volatile_type* test18 = (*test17)*2.0;
  //   print_result(lname + "* test18 = test17*2.0:\n *test18 = ", *test18);
  //   cout << endl;

  //   multiply_equal(*test18, 2.0);
  //   print_result("multiply_equal(test18, 2.0):\n test18 = ", *test18);
  //   cout << endl;

  //   (*test18) *= 2.0;
  //   print_result("test18 *= 2.0:\n test18 = ", *test18);
  //   cout << endl;

  //   delete test18;
  delete test17;

  volatile_type* test19 = divide(test02, 2);
  print_result(lname + "/ test19 = divide(test02, 2):\n *test19 = ", *test19);
  cout << endl;

  /// @hack tests for opr/, divide_equal, and opr/= disabled
  /// until explicit instantiations added to all fiber types.
  //   volatile_type* test20 = (*test19)/2.0;
  //   print_result(lname + "/ test20 = test19/2.0:\n *test20 = ", *test20);
  //   cout << endl;

  //   divide_equal(*test20, 2.0);
  //   print_result("divide_equal(test20, 2.0):\n test20 = ", *test20);
  //   cout << endl;

  //   (*test20) /= 2.0;
  //   print_result("test20 /= 2.0:\n test20 = ", *test20);
  //   cout << endl;

  //   delete test20;
  delete test19;

  //============================================================================

  // Test max and min:

  value_type lmax1;
  max(test01, lmax1);
  print_result("max(test01, lmax1):\n lmax1 = ", lmax1);
  cout << endl;
  
  value_type lmax2 = max(test01);
  print_result("lmax2 = max(test01):\n lmax2 = ", lmax1);
  cout << endl;

  value_type lmin1;
  min(test01, lmin1);
  print_result("min(test01, lmin1):\n lmin1 = ", lmin1);
  cout << endl;
  
  value_type lmin2 = min(test01);
  print_result("lmin2 = max(test01):\n lmin2 = ", lmin1);
  cout << endl;

  //============================================================================

  // Test contract:

  value_type lvalue = contract(test01, test02);
  print_result("lvalue = contract(test01, test02) = ", lvalue);
  cout << endl;

  //============================================================================

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_persistent_vd_facet(typename P::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::value_type value_type;
  typedef typename P::volatile_type volatile_type;
  const string& lfiber_name = P::static_class_name();
  //  const poset_path& lvector_space_path = P::vector_space_type::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name + "\"");

  string host_name = lfiber_name + "_vd_facet_host";

  persistent_type test03(&xhost);
  test03.put_name("test03", true, false);

  persistent_type test04(&xhost);
  test04.put_name("test04", true, false);

  for(int i=0; i<test03.d(); ++i)
  {
    test03.put_component(i, i+1);
    test04.put_component(i, i+1+test03.d());
  }
  cout << lfiber_name << " test03:" << test03 << endl;
  cout << lfiber_name << " test04:" << test04 << endl;
  cout << endl;

  persistent_type test05(&xhost);
  add(test03, test04, test05, false);
  print_result("add(test03, test04, test05):\n test05 = ", test05);
  cout << endl;

  add_equal(test05, test03, false);
  print_result("add_equal(test05, test03):\n test05 = ", test05);
  cout << endl;

  persistent_type test06(&xhost);
  subtract(test03, test04, test06, false);
  print_result("subtract(test03, test04, test06):\n test06 = ", test06);
  cout << endl;

  subtract_equal(test06, test03, false);
  print_result("subtract_equal(test06, test03):\n test06 = ", test06);
  cout << endl;

  //============================================================================

  // Test contract:

  // test03 must be a vector and test04 must be a covector.

  test03.put_is_vector(false);
  test04.put_is_covector(false);

  value_type lvalue = contract(test03, test04, false);
  print_result("lvalue = contract(test03, test04): lvalue = ", lvalue);
  cout << endl;

  //============================================================================

  test03.detach_from_state();
  test04.detach_from_state();
  test05.detach_from_state();
  test06.detach_from_state();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_st2_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  
  // Body:

  print_header("Testing st2 facet for " + P::static_class_name());

  typename P::host_type& lhost = xns.new_tensor_space<P>();
  lhost.get_read_write_access(true);
  
  test_volatile_st2_facet<P>();
  test_persistent_st2_facet<P>(lhost);

  lhost.release_access();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_volatile_st2_facet()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::value_type value_type;
  typedef typename P::volatile_type volatile_type;
  const string& lfiber_name = volatile_type::static_class_name();

  print_subheader("Testing volatile type \"" + lfiber_name + "\"");

  volatile_type test1;

  for(int i=0; i<test1.d(); ++i)
  {
    test1.put_component(i, i+1);
  }
  cout << lfiber_name << " test1:" << test1 << endl;
  cout << endl;

  // Test trace:

  value_type ltrace1 = trace(test1);
  print_result("ltrace1 = trace(test1):\n ltrace1 = ", ltrace1);
  cout << endl;

  value_type ltrace2;
  trace(test1, ltrace2);
  print_result("trace(test1, ltrace2):\n ltrace2 = ", ltrace2);
  cout << endl;

  // Test determinant:

  // Skip this test for met_e# classes because determinant is not
  // implemented in those cases.

  if(lfiber_name.find("met_") != 0)
  {
    value_type ldet1 = determinant(test1);
    print_result("ldet1 = determinant(test1):\n ldet1 = ", ldet1);
    cout << endl;

    value_type ldet2;
    determinant(test1, ldet2);
    print_result("determinant(test1, ldet2):\n ldet2 = ", ldet2);
    cout << endl;
  }

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_persistent_st2_facet(typename P::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::value_type value_type;

  const string& lfiber_name = P::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name + "\"");

  persistent_type test3(&xhost);
  test3.put_name("test3", true, false);

  for(int i=0; i<test3.d(); ++i)
  {
    test3.put_component(i, i+1);
  }
  cout << lfiber_name << " test3:" << test3 << endl;
  cout << endl;

  // Test trace:

  value_type ltrace1 = trace(test3, false);
  print_result("ltrace1 = trace(test3, false):\n ltrace1 = ", ltrace1);
  cout << endl;

  value_type ltrace2;
  trace(test3, ltrace2, false);
  print_result("trace(test3, ltrace2, false):\n ltrace2 = ", ltrace2);
  cout << endl;

  // Test determinant:

  // Skip this test for met_e# classes because determinant is not
  // implemented in those cases.

  if(lfiber_name.find("met_") != 0)
  {
    value_type ldet1 = determinant(test3, false);
    print_result("ldet1 = determinant(test3, false):\n ldet1 = ", ldet1);
    cout << endl;

    value_type ldet2;
    determinant(test3, ldet2, false);
    print_result("determinant(test3, ldet2, false):\n ldet2 = ", ldet2);
    cout << endl;
  }

  test3.detach_from_state();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_volatile_ed_facet()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  typedef typename volatile_type::value_type value_type;
  const string& lfiber_name = volatile_type::static_class_name();

  print_subheader("Testing volatile type \"" + lfiber_name + "\"");

  volatile_type test1;
  volatile_type test2;
  for(int i=0; i<test1.d(); ++i)
  {
    test1.put_component(i, i+1);
    test2.put_component(i, i+1+test1.d());
  }
  cout << lfiber_name << " test1:" << test1 << endl;
  cout << lfiber_name << " test2:" << test2 << endl;
  cout << endl;

  value_type dot1 = dot(test1, test2);
  cout << " dot1 = dot(test1, test2): dot1 = " << dot1 << endl;
  cout << endl;

  value_type len1 = length(test1);
  cout << "len1 = length(test1): len1 = " << len1 << endl;
  cout << endl;

  put_length(test1, 100.0);
  cout << "put_length(test1, 100.0): test1 = " << test1 << endl;
  cout << endl;

  normalize(test1);
  cout << "normalize(test1): " << test1 << endl;
  cout << "length(test1) = " << length(test1)  << endl;
  cout << endl;

  volatile_type test3;
  normalize(test1, test3);
  cout << lfiber_name << " test3; normalize(test1, test3): test3 = "
       << test3 << endl;
  cout << "length(test3) = " << length(test3)  << endl;

  cout << endl;

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_persistent_ed_facet(typename P::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename persistent_type::value_type value_type;
  const string& lfiber_name = P::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name +"\"");

  persistent_type test4(&xhost);
  test4.put_name("test4", true, false);

  persistent_type test5(&xhost);
  test5.put_name("test5", true, false);

  for(int i=0; i<test4.d(); ++i)
  {
    test4.put_component(i, i+1);
    test5.put_component(i, i+1+test4.d());
  }
  cout << lfiber_name << " test4:" << test4 << endl;
  cout << lfiber_name << " test5:" << test5 << endl;
  cout << endl;

  value_type dot1 = dot(test4, test5, false);
  cout << "dot1 = dot(test4, test5): dot1 = " << dot1 << endl;
  cout << endl;

  value_type len1 = length(test4, false);
  cout << "len1 = length(test4): len1 = " << len1 << endl;
  cout << endl;

  put_length(test4, 100.0, false);
  cout << "put_length(test4, 100.0): test4 = " << test4 << endl;
  cout << endl;

  normalize(test4, false);
  cout << "normalize(test4): " << test4 << endl;
  cout << "length(test4) = " << length(test4, false)  << endl;
  cout << endl;

  persistent_type test6(&xhost);
  test6.put_name("test6", true, false);
  normalize(test4, test6, false);
  cout << "normalize(test4, test6): test6 = " << test6 << endl;
  cout << "length(test6) = " << length(test6, false)  << endl;
  cout << endl;

  cout << endl;

  test4.detach_from_state();
  test5.detach_from_state();
  test6.detach_from_state();

  // Postconditions:

  // Exit:
}

///
template <typename P>
void
test_scalar_vd_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("Testing scalar vd facet for " + P::static_class_name());

  typename P::host_type& lhost = xns.new_scalar_space<P>();
  lhost.get_read_write_access(true);

  test_volatile_vd_facet<P>();
  test_persistent_vd_facet<P>(lhost);

  lhost.release_access();

  // Postconditions:

  // Exit:
}

///
template <typename P>
void
test_vector_vd_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("Testing vector vd facet for " + P::static_class_name());

  typename P::host_type& lhost = xns.new_vector_space<P>();
  lhost.get_read_write_access(true);

  test_volatile_vd_facet<P>();
  test_persistent_vd_facet<P>(lhost);

  lhost.release_access();

  // Postconditions:

  // Exit:
}

///
template <typename P>
void
test_tensor_vd_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("Testing tensor vd facet for " + P::static_class_name());

  typename P::host_type& lhost = xns.new_tensor_space<P>();
  lhost.get_read_write_access(true);

  test_volatile_vd_facet<P>();
  test_persistent_vd_facet<P>(lhost);

  lhost.release_access();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_jacobian_vd_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("Testing jacobian vd facet for " + P::static_class_name());

  typename P::host_type& lhost = xns.new_jacobian_space<P>();
  lhost.get_read_write_access(true);

  test_volatile_vd_facet<P>();
  test_persistent_vd_facet<P>(lhost);

  lhost.release_access();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_ed_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  
  // Body:

  print_header("Testing ed facet for " + P::static_class_name());

  typename P::host_type& lhost = xns.new_vector_space<P>();
  lhost.get_read_write_access(true);

  test_volatile_ed_facet<P>();
  test_persistent_ed_facet<P>(lhost);

  lhost.release_access();

  // Postconditions:

  // Exit:
}

//==============================================================================
// TP FACET
//==============================================================================


template <typename PT>
void
test_tp_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  
  // Body:

  print_header("Testing tp facet for " + PT::static_class_name());

  test_volatile_tp_facet<PT>();
  test_persistent_tp_facet<PT>(xns);

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_volatile_tp_facet()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  typedef typename P::value_type value_type;
  typedef typename volatile_type::vector_space_type vector_space_type;
  typedef typename tensor_traits<volatile_type::P, vector_space_type>::stp_type
     sym_volatile_type;
  typedef typename tensor_traits<volatile_type::P, vector_space_type>::atp_type
     alt_volatile_type;

  const string& lfiber_name = volatile_type::static_class_name();
  const string& stp_name = sym_volatile_type::static_class_name();
  const string& atp_name = alt_volatile_type::static_class_name();

  print_subheader("Testing volatile type \"" + lfiber_name +"\"");

  cout << endl;

  // Test alt and sym functions.

  volatile_type vtensor;

  // Use some random component values so we assured that
  // the antisymmertic part is nonzero.

  srand(1);
  int ld = vtensor.d();
  for(int i=0; i<ld; ++i)
  {
    vtensor.put_component(i, 1 + (rand() % ld));
  }
  cout << lfiber_name << "vtensor:" <<  vtensor << endl;
  cout << endl;

  alt_volatile_type aresult;

  alt(vtensor, aresult);
  cout << "alt(vtensor, aresult):" << endl;
  cout << atp_name << " aresult: " <<  aresult << endl;
  cout << endl;

  sym_volatile_type sresult;

  sym(vtensor, sresult);
  cout << "sym(vtensor, sresult):" << endl;
  cout << stp_name << " sresult: " <<  sresult << endl;
  cout << endl;

  // Postconditions:

  // Exit:
}

template <typename PT>
void
test_persistent_tp_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef PT persistent_type;
  typedef typename PT::volatile_type volatile_type;
  typedef typename PT::vector_space_type vector_space_type;

  typedef typename tensor_traits<PT::P, vector_space_type>::stp_type
    sym_persistent_type;
  typedef typename tensor_traits<PT::P, vector_space_type>::atp_type
    alt_persistent_type;

  const string& lfiber_name = PT::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name +"\"");

  //============================================================================
  // Test variance:
  //============================================================================

  typename PT::host_type& lhost = xns.new_tensor_space<PT>();
  lhost.get_read_write_access(true);
  typename sym_persistent_type::host_type& lsym_host = new_host_space<sym_persistent_type>(xns);
  lsym_host.get_read_write_access(true);
  typename alt_persistent_type::host_type& lalt_host = new_host_space<alt_persistent_type>(xns);
  lalt_host.get_read_write_access(true);

  persistent_type test01(&lhost);
  test01.put_name("test01", true, false);

  persistent_type test02(&lhost);
  test02.put_name("test02", true, false);

  for(int i=0; i<test01.d(); ++i)
  {
    test01.put_component(i, i+1);
    test02.put_component(i, i+1+test01.d());
  }
  cout << lfiber_name << " test01:" << test01 << endl;
  cout << lfiber_name << " test02:" << test02 << endl;
  cout << endl;

  cout << boolalpha;
  for(int i=0; i<test01.p(false); ++i)
  {
    cout << "test01.is_covariant(" << i << ", false): "
         << test01.is_covariant(i, false) << endl;
    cout << "test01.is_contravariant(" << i << ", false): "
         << test01.is_contravariant(i, false) << endl;

    cout << endl;

    cout << "test02.is_covariant(" << i << ", false): "
         << test02.is_covariant(i, false) << endl;
    cout << "test02.is_contravariant(" << i << ", false): "
         << test02.is_contravariant(i, false) << endl;

    cout << endl;
  }

  cout << endl;

  // Change to contravariant type.

  for(int i=0; i<test01.p(false); ++i)
  {
    test01.put_is_covariant(i, false);
    test02.put_is_covariant(i, false);
  }

  for(int i=0; i<test01.p(false); ++i)
  {
    cout << "test01.is_covariant(" << i << ", false): "
         << test01.is_covariant(i, false) << endl;
    cout << "test01.is_contravariant(" << i << ", false): "
         << test01.is_contravariant(i, false) << endl;

    cout << endl;

    cout << "test02.is_covariant(" << i << ", false): "
         << test02.is_covariant(i, false) << endl;
    cout << "test02.is_contravariant(" << i << ", false): "
         << test02.is_contravariant(i, false) << endl;

    cout << endl;
  }

  cout << endl;

  test01.detach_from_state();
  test02.detach_from_state();

  //============================================================================
  // Test alt and sym functions.
  //============================================================================

  persistent_type ptensor(&lhost);
  cout<<"ptensor is a "<<persistent_type::static_class_name()<<endl;
  
  ptensor.put_name("ptensor", true, false);

  // Use some random component values so we are assured(?) that
  // the antisymmertic part is nonzero.

  srand(1);
  int ld = ptensor.d();
  for(int i=0; i<ld; ++i)
  {
    ptensor.put_component(i, 1 + (rand() % ld));
  }
  cout << "ptensor components:" <<  ptensor << endl;

  alt_persistent_type aresult(&lalt_host);
  cout<<"aresult is a "<<alt_persistent_type::static_class_name()<<endl;

  alt(ptensor, aresult, false);
  cout << "alt(ptensor, aresult):" << endl;
  cout << "  aresult components:" <<  aresult << endl;

  sym_persistent_type sresult(&lsym_host);

  sym(ptensor, sresult, false);
  cout << "sym(ptensor, sresult):" << endl;
  cout << "  sresult components:" <<  sresult << endl;

  cout << endl;
  cout << endl;

  //============================================================================

  aresult.detach_from_state();
  sresult.detach_from_state();
  ptensor.detach_from_state();
  lhost.release_access();
  lsym_host.release_access();
  lalt_host.release_access();

  // Postconditions:

  // Exit:
}

template <typename P0, typename P1, typename PR>
void
test_tensor(fiber_bundles_namespace& xns)
{
  // Preconditions:

  // Body:

  print_header("Testing tp facet tensor product:");

  test_volatile_tensor<P0, P1, PR>();
  test_persistent_tensor<P0, P1, PR>(xns);

  // Postconditions:

  // Exit:

}

template <typename P0, typename P1, typename PR>
void
test_volatile_tensor()
{
  // Preconditions:

  // Body:

  typedef typename P0::volatile_type V0;
  typedef typename P1::volatile_type V1;
  typedef typename PR::volatile_type VR;

  string lname_0 = V0::static_class_name();
  string lname_1 = V1::static_class_name();
  string lname_r = VR::static_class_name();

  print_subheader("Testing tp facet tensor product for volatile types");

  // Form tensor product: V0(X)V1 = VR.

  V0 x0;
  V1 x1;
  VR result;

  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    x0.put_component(i, i+1);
  }
  cout << lname_0 << " x0:" <<  x0 << endl;

  ld = x1.d();
  for(int i=0; i<ld; ++i)
  {
    x1.put_component(i, i+1+ld);
  }
  cout << lname_1 << " x1:" <<  x1 << endl;

  cout << endl;

  tensor(x0, x1, result);
  print_result("tensor(x0, x1, result):\n result (" + lname_r + ") = ", result);
  cout << endl;

  tensor(x1, x0, result);
  print_result("tensor(x1, x1, result):\n result (" + lname_r + ") = ", result);
  cout << endl;

  // Postconditions:

  // Exit:

}

template <typename P0, typename P1, typename PR>
void
test_persistent_tensor(fiber_bundles_namespace& xns)
{
  // Preconditions:
  
  require(xns.state_is_read_write_accessible());

  // Body:

  // Form tensor product: P0(X)P1 = PR.

  ///@issue: Has to be the same as P1 & PR.  How do we want to require this?

  print_subheader("Testing tp facet tensor product for persistent types");

  typename P0::host_type& lhost_0 = new_host_space<P0>(xns);
  lhost_0.get_read_write_access(true);
  typename P1::host_type& lhost_1 = new_host_space<P1>(xns);
  lhost_1.get_read_write_access(true);
  typename PR::host_type& lhost_r = new_host_space<PR>(xns);
  lhost_r.get_read_write_access(true);

  P0 x0(&lhost_0);
  P1 x1(&lhost_1);
  PR result(&lhost_r);

  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    x0.put_component(i, i+1+ld);
  }
  cout << lhost_0.name() << " x0:" <<  x0 << endl;

  ld = x1.d();
  for(int i=0; i<ld; ++i)
  {
    x1.put_component(i, i+1);
  }
  cout << lhost_1.name() << " x1:" <<  x1 << endl;

  cout << endl;

  tensor(x0, x1, result, false);
  print_result("tensor(x0, x1, result):\n result (" + lhost_r.name() + ") = ", result);
  cout << endl;

  tensor(x1, x0, result, false);
  print_result("tensor(x1, x0, result):\n result (" + lhost_r.name() + ") = ", result);
  cout << endl;

  x0.detach_from_state();
  x1.detach_from_state();
  result.detach_from_state();
  lhost_0.release_access();
  lhost_1.release_access();
  lhost_r.release_access();
  
  // Postconditions:

  // Exit:

}

template <typename P0, typename PR>
void
test_contract(fiber_bundles_namespace& xns)
{
  // Preconditions:

  // Body:

  print_header("Testing tp facet contract:");

  test_volatile_contract<P0, PR>();
  test_persistent_contract<P0, PR>(xns);

  // Postconditions:

  // Exit:

}

template <typename P0, typename PR>
void
test_volatile_contract()
{
  // Preconditions:

  // Body:

  typedef typename P0::volatile_type V0;
  typedef typename PR::volatile_type VR;

  string ltensor_name = V0::static_class_name();
  string lresult_name = VR::static_class_name();

  print_subheader("Testing tp facet contract for volatile types");

  // Form tensor product: V0(X)V1 = VR.

  V0 ltensor;
  VR lresult;

  cout << endl;
 
  for(int i=0; i<ltensor.d(); ++i)
  {
    ltensor.put_component(i, i+1);
  }
  cout << ltensor_name << " ltensor:" <<  ltensor << endl;
  cout << endl;

  contract(ltensor, 0, 1, lresult);
  cout << "contract(ltensor, 0, 1, lresult):" << endl;
  cout << lresult_name << " lresult = " << lresult << endl;
  cout << endl;

  if(ltensor.p() >= 3)
  {
    contract(ltensor, 1, 2, lresult);
    cout << "contract(ltensor, 1, 2, lresult):" << endl;
    cout << lresult_name << " lresult = " << lresult << endl;
    cout << endl;
  }

  // Postconditions:

  // Exit:

}

template <typename P0, typename PR>
void
test_persistent_contract(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  ///@issue: Has to be the same as P1 & PR.  How do we want to require this?

  print_subheader("Testing tp facet contract for persistent types");

  typename P0::host_type& lhost_0 = new_host_space<P0>(xns);
  lhost_0.get_read_write_access(true);
  typename PR::host_type& lhost_r = new_host_space<PR>(xns);
  lhost_r.get_read_write_access(true);

  P0 ltensor(&lhost_0);
  PR lresult(&lhost_r);

  int ld = ltensor.d();
  for(int i=0; i<ld; ++i)
  {
    ltensor.put_component(i, i+1);
  }
  cout << lhost_0.name() << " ltensor:" <<  ltensor << endl;

  cout << endl;

  ltensor.put_is_covariant(1, false);
  cout << "ltensor.put_covariant(1, false):" << endl;
  cout << endl;

  contract(ltensor, 0, 1, lresult, false);
  cout << "contract(ltensor, 0, 1, lresult, false):" << endl;
  cout << lhost_r.name() << " lresult:" << lresult << endl;

  cout << boolalpha;
  cout << "  lresult.is_p_form():   " << lresult.is_p_form(false) << endl;
  cout << "  lresult.is_p_vector(): " << lresult.is_p_vector(false) << endl;

  cout << endl;

  if(ltensor.p() >= 3)
  {
    ltensor.put_is_covariant(0, false);
    cout << "ltensor.put_covariant(0, false):" << endl;
    cout << endl;

    contract(ltensor, 1, 2, lresult, false);
    cout << "contract(ltensor, 1, 2, lresult, false):" << endl;
    cout << lhost_r.name() << " lresult:" << lresult << endl;

    cout << boolalpha;
    cout << "  lresult.is_p_form():   " << lresult.is_p_form(false) << endl;
    cout << "  lresult.is_p_vector(): " << lresult.is_p_vector(false) << endl;

    cout << endl;
  }

  ltensor.detach_from_state();
  lresult.detach_from_state();
  lhost_0.release_access();
  lhost_r.release_access();

  // Postconditions:

  // Exit:

}


//==============================================================================
// ATP FACET
//==============================================================================

///
template <typename P>
void
test_vector_atp_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  
  // Body:

  typename P::host_type& lhost = xns.new_vector_space<P>();
  lhost.get_read_write_access(true);
  
  test_atp_facet<P>(lhost);
  
  lhost.release_access();
  
  // Exit:
}

///
template <typename P>
void
test_tensor_atp_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  
  // Body:

  typename P::host_type& lhost = xns.new_tensor_space<P>();
  lhost.get_read_write_access(true);
  
  test_atp_facet<P>(lhost);
  
  lhost.release_access();
  
  // Exit:
}

template <typename P>
void
test_atp_facet(typename P::host_type& xhost)
{
  // Preconditions:

  // Body:

  print_header("Testing atp facet for " + P::static_class_name());

  test_persistent_atp_facet<P>(xhost);

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_volatile_atp_facet()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  typedef typename P::value_type value_type;
  const string& lfiber_name = volatile_type::static_class_name();

  print_subheader("Testing volatile type \"" + lfiber_name + "\"");

  cout << endl;
  cout << "Not implemented." << endl;

  cout << endl;

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_persistent_atp_facet(typename P::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::vector_space_type vector_space_type;

  const string& lfiber_name = P::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name +"\"");

  // Test variance:

  //$$SCRIBBLE: The following is identical for stp.
  //            So we should probably put it in a separate function.

  persistent_type test01(&xhost);
  test01.put_name("test01", true, false);

  persistent_type test02(&xhost);
  test02.put_name("test02", true, false);

  for(int i=0; i<test01.d(); ++i)
  {
    test01.put_component(i, i+1);
    test02.put_component(i, i+1+test01.d());
  }
  cout << lfiber_name << " test01:" << test01 << endl;
  cout << lfiber_name << " test02:" << test01 << endl;
  cout << endl;

  cout << boolalpha;

  cout << "test01.is_p_form(false): " << test01.is_p_form(false) << endl;
  cout << "test02.is_p_form(false): " << test02.is_p_form(false) << endl;

  cout << "test01.is_p_vector(false): " << test01.is_p_vector(false) << endl;
  cout << "test02.is_p_vector(false): " << test02.is_p_vector(false) << endl;

  cout << "test01.is_covector(false): " << test01.is_covector(false) << endl;
  cout << "test02.is_covector(false): " << test02.is_covector(false) << endl;

  cout << "test01.is_vector(false): " << test01.is_vector(false) << endl;
  cout << "test02.is_vector(false): " << test02.is_vector(false) << endl;

  cout << endl;

  for(int i=0; i<test01.p(false); ++i)
  {
    cout << "test01.is_covariant(" << i << ", false): "
         << test01.is_covariant(i, false) << endl;
    cout << "test01.is_contravariant(" << i << ", false): "
         << test01.is_contravariant(i, false) << endl;

    cout << endl;

    cout << "test02.is_covariant(" << i << ", false): "
         << test02.is_covariant(i, false) << endl;
    cout << "test02.is_contravariant(" << i << ", false): "
         << test02.is_contravariant(i, false) << endl;

    cout << endl;
  }

  cout << endl;

  test01.put_is_p_form(false);
  test02.put_is_p_form(false);

  cout << "test01.is_p_form(false): " << test01.is_p_form(false) << endl;
  cout << "test02.is_p_form(false): " << test02.is_p_form(false) << endl;

  cout << "test01.is_p_vector(false): " << test01.is_p_vector(false) << endl;
  cout << "test02.is_p_vector(false): " << test02.is_p_vector(false) << endl;

  cout << "test01.is_covector(false): " << test01.is_covector(false) << endl;
  cout << "test02.is_covector(false): " << test02.is_covector(false) << endl;

  cout << "test01.is_vector(false): " << test01.is_vector(false) << endl;
  cout << "test02.is_vector(false): " << test02.is_vector(false) << endl;

  cout << endl;

  for(int i=0; i<test01.p(false); ++i)
  {
    cout << "test01.is_covariant(" << i << ", false): "
         << test01.is_covariant(i, false) << endl;
    cout << "test01.is_contravariant(" << i << ", false): "
         << test01.is_contravariant(i, false) << endl;

    cout << endl;

    cout << "test02.is_covariant(" << i << ", false): "
         << test02.is_covariant(i, false) << endl;
    cout << "test02.is_contravariant(" << i << ", false): "
         << test02.is_contravariant(i, false) << endl;

    cout << endl;
  }

  //=======================================================================

  // Test contract. This really should be in test_vd_persistent but
  // jcb does not have a put_is_p_form function so we put this test here.

  cout << endl;

  test01.put_is_p_vector(false);
  test02.put_is_p_form(false);
  cout << "contract(test01, test02) = "
       << contract(test01, test02, false)<< endl;
  cout << endl;

  //=======================================================================

  test01.detach_from_state();
  test02.detach_from_state();

  // Postconditions:

  // Exit:
}


//==============================================================================
// STP FACET
//==============================================================================


template <typename P>
void
test_stp_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  
  // Body:

  print_header("Testing stp facet for " + P::static_class_name());

  typename P::host_type& lhost = xns.new_tensor_space<P>();
  lhost.get_read_write_access(true);
  
  test_volatile_stp_facet<P>();
  test_persistent_stp_facet<P>(lhost);

  lhost.release_access();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_volatile_stp_facet()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  const string& lfiber_name = volatile_type::static_class_name();

  print_subheader("Testing volatile type \"" + lfiber_name +"\"");
  cout << endl;

  cout << "Not implemented." << endl;

  //=======================================================================

  // Test symmetric product:

  //$$SCRIBBLE: Testing the symmetric product awaits adding a rank 4
  //            symmetric tensor to the library.

  //=======================================================================

  cout << endl;

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_persistent_stp_facet(typename P::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::vector_space_type vector_space_type;

  const string& lfiber_name = P::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name +"\"");

  //$$SCRIBBLE: The following is identical for atp.
  //            So we should probably put it in a separate function.

  persistent_type test01(&xhost);
  test01.put_name("test01", true, false);

  persistent_type test02(&xhost);
  test02.put_name("test02", true, false);

  for(int i=0; i<test01.d(); ++i)
  {
    test01.put_component(i, i+1);
    test02.put_component(i, i+1+test01.d());
  }
  cout << lfiber_name << " test01 components:" << test01 << endl;
  cout << lfiber_name << " test02 components:" << test02 << endl;
  cout << endl;

  cout << boolalpha;

  cout << "test01.is_covariant(false): " << test01.is_covariant(false) << endl;
  cout << "test02.is_covariant(false): " << test02.is_covariant(false) << endl;

  cout << "test01.is_contravariant(false): " << test01.is_contravariant(false) << endl;
  cout << "test02.is_contravariant(false): " << test02.is_contravariant(false) << endl;

  cout << "test01.is_covector(false): " << test01.is_covector(false) << endl;
  cout << "test02.is_covector(false): " << test02.is_covector(false) << endl;

  cout << "test01.is_vector(false): " << test01.is_vector(false) << endl;
  cout << "test02.is_vector(false): " << test02.is_vector(false) << endl;

  cout << endl;

  for(int i=0; i<test01.p(false); ++i)
  {
    cout << "test01.is_covariant(" << i << ", false): "
         << test01.is_covariant(i, false) << endl;
    cout << "test01.is_contravariant(" << i << ", false): "
         << test01.is_contravariant(i, false) << endl;

    cout << endl;

    cout << "test02.is_covariant(" << i << ", false): "
         << test02.is_covariant(i, false) << endl;
    cout << "test02.is_contravariant(" << i << ", false): "
         << test02.is_contravariant(i, false) << endl;

    cout << endl;
  }

  cout << endl;

  test01.put_is_covariant(false);
  test02.put_is_covariant(false);

  cout << "test01.is_covariant(false): " << test01.is_covariant(false) << endl;
  cout << "test02.is_covariant(false): " << test02.is_covariant(false) << endl;

  cout << "test01.is_contravariant(false): " << test01.is_contravariant(false) << endl;
  cout << "test02.is_contravariant(false): " << test02.is_contravariant(false) << endl;

  cout << "test01.is_covector(false): " << test01.is_covector(false) << endl;
  cout << "test02.is_covector(false): " << test02.is_covector(false) << endl;

  cout << "test01.is_vector(false): " << test01.is_vector(false) << endl;
  cout << "test02.is_vector(false): " << test02.is_vector(false) << endl;

  cout << endl;

  for(int i=0; i<test01.p(false); ++i)
  {
    cout << "test01.is_covariant(" << i << ", false): "
         << test01.is_covariant(i, false) << endl;
    cout << "test01.is_contravariant(" << i << ", false): "
         << test01.is_contravariant(i, false) << endl;

    cout << endl;

    cout << "test02.is_covariant(" << i << ", false): "
         << test02.is_covariant(i, false) << endl;
    cout << "test02.is_contravariant(" << i << ", false): "
         << test02.is_contravariant(i, false) << endl;

    cout << endl;
  }

  //=======================================================================

  test01.put_is_vector(false);
  // $$SCRIBBLE dmb contract now requires args x0.is_vector(), x1.is_covector().
  test02.put_is_covector(false);
  cout << "contract(test01, test02) = "
       << contract(test01, test02, false)<< endl;
  cout << endl;

  //=======================================================================

  test01.detach_from_state();
  test02.detach_from_state();

  // Postconditions:

  // Exit:
}

//==============================================================================
// JCB FACET
//==============================================================================

template <typename P>
void
test_jcb_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  // Body:

  print_header("Testing jcb facet for " + P::static_class_name());

  test_volatile_jcb_facet<P>();
  test_persistent_jcb_facet<P>(xns);

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_volatile_jcb_facet()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  typedef typename P::value_type value_type;

  typedef typename fiber_traits<P>::volatile_vector_type vector_type;
  typedef typename fiber_traits<P>::volatile_covector_type covector_type;

  const string& lfiber_name = volatile_type::static_class_name();
  const string& v_name = vector_type::static_class_name();
  const string& c_name = covector_type::static_class_name();

  print_subheader("Testing volatile type \"" + lfiber_name +"\"");

  cout << "vector type   = " << v_name << endl;
  cout << "covector type = " << c_name << endl;
  cout << endl;

  //============================================================================

  // Create volatile fibers for testing.

  volatile_type jacobian;
  for(int i=0; i<jacobian.d(); ++i)
  {
    jacobian.put_component(i, i+1);
  }

  cout << "jacobian (" << lfiber_name << "): " << jacobian << endl;

  vector_type vector;
  for(int i=0; i<vector.d(); ++i)
  {
    vector.put_component(i, i+1);
  }

  cout << "vector (" << v_name << "): " << vector << endl;
  cout << endl;

  // Test push:

  covector_type result1;
  push(jacobian, vector, result1);
  print_result(
    "push(jacobian, vector, result1): result1 (" + c_name + ") = ", result1);
  cout << endl;

  covector_type* result2 = push(jacobian, vector);
  print_result(
    "result2 = push(jacobian, vector): *result2 (" + c_name + ") = ", *result2);
  cout << endl;
  delete result2;

  // Test pull:

  vector_type result3;
  pull(jacobian, result1, result3);
  print_result(
    "pull(jacobian, result1, result3): result3 (" + v_name + ") = ", result3);
  cout << endl;

  vector_type* result4 = pull(jacobian, result1);
  print_result(
     "pull(jacobian, result1, result4): *result4 (" + v_name + ") = ",*result4);
  cout << endl;
  delete result4;

  //============================================================================

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_persistent_jcb_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef P persistent_type;

  typedef typename fiber_traits<P>::persistent_vector_type vector_type;
  typedef typename fiber_traits<P>::persistent_covector_type covector_type;

  const string& lfiber_name = P::static_class_name();
  const string& vector_name = vector_type::static_class_name();
  const string& covector_name = covector_type::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name +"\"");

  typename persistent_type::host_type& host = new_host_space<persistent_type>(xns);
  host.get_read_write_access(true);
  typename vector_type::host_type& vector_host = new_host_space<vector_type>(xns);
  vector_host.get_read_write_access(true);
  typename covector_type::host_type& covector_host = new_host_space<covector_type>(xns);
  covector_host.get_read_write_access(true);

  persistent_type jacobian(&host);
  jacobian.put_name("jacobian", true, false);
  for(int i=0; i<jacobian.d(); ++i)
  {
    jacobian.put_component(i, i+1);
  }

  cout << lfiber_name << " jacobian: " << jacobian << endl;

  vector_type vector1(&vector_host);
  vector1.put_name("vector1", true, false);
  for(int i=0; i<vector1.d(); ++i)
  {
    vector1.put_component(i, i+1);
  }

  cout << vector_name << " vector1: " << vector1 << endl;

  covector_type covector1(&covector_host);
  covector1.put_name("covector1", true, false);

  push(jacobian, vector1, covector1, false);
  cout << "push(jacobian, vector1, covector1): covector1 = "
       << covector1 << endl;
  cout << endl;

  vector_type vector2(&vector_host);
  vector2.put_name("vector2", true, false);

  covector1.put_is_p_form(false);
  vector2.put_is_p_form(false);

  pull(jacobian, covector1, vector2, false);
  cout << "pull(jacobian, covector1, vector2): vector2 = "
       << vector2 << endl;
  cout << endl;

  jacobian.detach_from_state();
  covector1.detach_from_state();
  vector1.detach_from_state();
  vector2.detach_from_state();

  host.release_access();
  vector_host.release_access();
  covector_host.release_access();

  // Postconditions:

  // Exit:
}


//==============================================================================
// MET FACET
//==============================================================================

template <typename P>
void
test_met_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("Testing met facet for " + P::static_class_name());

  typename P::host_type& lhost = xns.new_tensor_space<P>();
  lhost.get_read_write_access(true);

  typedef typename P::vector_space_type vector_space_type;

  typename vector_space_type::host_type& lvector_space_host = xns.new_vector_space<vector_space_type>();
  lvector_space_host.get_read_write_access(true);

  test_volatile_met_facet<P>();
  test_persistent_met_facet<P>(lhost, lvector_space_host);

  lhost.release_access();

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_volatile_met_facet()
{
  // Preconditions:

  // Body:

  //$$SCRIBBLE: Note that we are presently ONLY testing whether
  //            the correct calculations are being done for
  //            the raise and lower operations.  We are NOT
  //            starting with a real metric tensor.

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  typedef typename volatile_type::vector_space_type vector_type;

  const string& lfiber_name = volatile_type::static_class_name();
  const string& v_name = vector_type::static_class_name();

  print_subheader("Testing volatile type \"" + lfiber_name +"\"");

  cout << "metric type = " << lfiber_name << endl;
  cout << "vector type = " << v_name << endl;
  cout << endl;

  volatile_type metric;
  for(int i=0; i<metric.d(); ++i)
  {
    metric.put_component(i, i+1);
  }

  vector_type vector0;
  for(int i=0; i<vector0.d(); ++i)
  {
    vector0.put_component(i, 100*(i+1));
  }

  vector_type vector1;
  lower(metric, vector0, vector1);

  cout <<"lower(metric, vector0, vector1):" << endl;
  cout << "  " << lfiber_name << " metric: " << metric << endl;
  cout << "  " << v_name << " vector0: " << vector0 << endl;
  cout << "  " << v_name << " vector1: " << vector1 << endl;
  cout << endl;

  vector_type* pvector1 = lower(metric, vector0);

  cout <<"pvector1 = lower(metric, vector0):" << endl;
  cout << "  " << lfiber_name << " metric: " << metric << endl;
  cout << "  " << v_name << " vector0:   " << vector0 << endl;
  cout << "  " << v_name << " *pvector1: " << *pvector1 << endl;
  cout << endl;

  delete pvector1;

  vector_type vector2;
  raise(metric, vector0, vector2);

  cout <<"raise(metric, vector0, vector2):" << endl;
  cout << "  " << lfiber_name << " metric: " << metric << endl;
  cout << "  " << v_name << " vector0: " << vector0 << endl;
  cout << "  " << v_name << " vector2: " << vector2 << endl;
  cout << endl;

  vector_type* pvector2 = raise(metric, vector0);

  cout <<"raise(metric, vector0, vector2):" << endl;
  cout << "  " << lfiber_name << " metric: " << metric << endl;
  cout << "  " << v_name << " vector0:   " << vector0 << endl;
  cout << "  " << v_name << " *pvector2: " << *pvector2 << endl;
  cout << endl;

  delete pvector2;

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_persistent_met_facet(typename P::host_type& xhost,
			  typename P::vector_space_type::host_type& xvector_space_host)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  //$$SCRIBBLE: Note that we are presently ONLY testing whether
  //            the correct calculations are being done for
  //            the raise and lower operations.  We are NOT
  //            starting with a real metric tensor.

  // Get the various class types, etc.

  typedef P persistent_type;
  typedef typename P::vector_space_type vector_space_type;

  const string& lfiber_name = P::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name + "\"");

  persistent_type metric(&xhost);
  metric.put_name("metric", true, false);

  for(int i=0; i<metric.d(); ++i)
  {
    metric.put_component(i, i+1);
  }

  vector_space_type vector0(&xvector_space_host);
  vector0.put_name("vector0", true, false);

  for(int i=0; i<vector0.d(); ++i)
  {
    vector0.put_component(i, 100*(i+1));
  }

  vector_space_type vector1(&xvector_space_host);
  vector1.put_name("vector1", true, false);
  const string lvector_space_name = xvector_space_host.name();

  // For the lower operation the metric is covariant,
  // vector0 is contravariant and vector1 is covariant (dual).

  metric.put_is_covariant(false);
  vector0.put_is_contravariant(false);
  vector1.put_is_covariant(false);

  lower(metric, vector0, vector1, false);

  cout <<"lower(metric, vector0, vector1):" << endl;
  cout << "  " << lfiber_name << " metric: " << metric << endl;
  cout << "  " << lvector_space_name << " vector0: " << vector0 << endl;
  cout << "  " << lvector_space_name << " vector1: " << vector1 << endl;
  cout << endl;

  vector_space_type vector2(&xvector_space_host);
  vector2.put_name("vector2", true, false);

  // For the raise operation the metric is contravariant,
  // vector0 is covariant (dual) and vector2 is contravariant.

  metric.put_is_contravariant(false);
  vector0.put_is_covariant(false);
  vector2.put_is_contravariant(false);

  raise(metric, vector0, vector2, false);

  cout <<"raise(metric, vector0, vector2):" << endl;
  cout << "  " << lfiber_name << " metric: " << metric << endl;
  cout << "  " << lvector_space_name << " vector0: " << vector0 << endl;
  cout << "  " << lvector_space_name << " vector2: " << vector2 << endl;

  cout << endl;

  metric.detach_from_state();
  vector0.detach_from_state();
  vector1.detach_from_state();
  vector2.detach_from_state();

  // Postconditions:

  // Exit:
}

//==============================================================================
// GROUP FACET
//==============================================================================

template <typename P>
void
test_group_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  // Body:

  print_header("Testing group facet for " + P::static_class_name());

  test_volatile_group_facet<P>();
  test_persistent_group_facet<P>(xns);

  // Postconditions:

  // Exit:
}


template <typename P>
void
test_volatile_group_facet()
{
  // Preconditions:

  // Body:

  // Get the various class types, etc.

  typedef typename P::volatile_type volatile_type;
  typedef typename P::row_dofs_type row_dofs_type;
  typedef typename P::value_type value_type;
  const string& lfiber_name = volatile_type::static_class_name();

  print_subheader("Testing volatile type \"" + lfiber_name +"\"");

  volatile_type test1;

  // Initialize the components to -1, 2, 3, ....

  row_dofs_type rdt1;
  int ld = rdt1.d();

  rdt1[0] = -1.0;  // Negative, so basis matrix is not singular.
  for(int i=1; i<ld; ++i)
  {
    rdt1[i] = i+1;
  }

  cout << "rdt1 basis matrix: " << endl << rdt1.basis_matrix() << endl;
  cout << endl;

  // Member function put_matrix make the component matrix equal to
  // the inverse of the basis matrix and stores the result in test1.

  test1.put_matrix(rdt1);

  cout << "test1.put_matrix(rdt1:" << endl;
  cout << lfiber_name << " test1:" << endl;
  cout << test1 << endl;
  cout << endl;

  volatile_type test2;

  // Function inverse calculates the inverse of both the basis
  // and component parts of test1 and stores them in test2.

  inverse(test1, test2);

  cout << "inverse(test1, test2):" << endl;
  cout << lfiber_name << " test2 = " << endl;
  cout << test2 << endl;
  cout << endl;

  // Postconditions:

  // Exit:
}

template <typename P>
void
test_persistent_group_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef typename P::row_dofs_type row_dofs_type;
  typedef typename P::value_type value_type;
  const string& lfiber_name = P::static_class_name();

  print_subheader("Testing persistent type \"" + lfiber_name +"\"");

  typename P::host_type& host = xns.new_group_space<P>();
  host.get_read_write_access();

  P test3(&host);
  test3.put_name("test3", true, false);

  // Initialize the components to -1, 2, 3, ....

  row_dofs_type rdt1;
  int ld = rdt1.d();

  rdt1[0] = -1.0;  // Negative, so basis matrix is not singular.
  for(int i=1; i<ld; ++i)
  {
    rdt1[i] = i+1;
  }

  cout << "rdt1 basis matrix: " << endl << rdt1.basis_matrix() << endl;
  cout << endl;

  // Member function put_matrix make the component matrix equal to
  // the inverse of the basis matrix and stores the result in test3.

  test3.put_matrix(rdt1);

  cout << "test3.put_matrix(rdt1):" << endl;
  cout << lfiber_name << " test3:" << endl;
  cout << test3 << endl;
  cout << endl;

  P test4(&host);
  test4.put_name("test4", true, false);

  // Function inverse calculates the inverse of both the basis
  // and component parts of test4 and stores them in test4.

  inverse(test3, test4);

  cout << "inverse(test3, test4):" << endl;
  cout << lfiber_name << " test4:" << endl;
  cout << test4 << endl;
  cout << endl;

  test3.detach_from_state();
  test4.detach_from_state();

  host.release_access();

  // Postconditions:

  // Exit:
}

template <typename host_type>
struct new_host_space_impl
{
  template <typename fiber_type>
  static host_type& new_space(fiber_bundles_namespace& xns)
  {
    return xns.new_tensor_space<fiber_type>();
  };
};

template<>
struct new_host_space_impl<at1_space>
{
  template <typename fiber_type>
  static at1_space& new_space(fiber_bundles_namespace& xns)
  {
    return xns.new_vector_space<fiber_type>();
  };
};

template<>
struct new_host_space_impl<at0_space>
{
  template <typename fiber_type>
  static at0_space& new_space(fiber_bundles_namespace& xns)
  {
    return xns.new_scalar_space<fiber_type>();
  };
};

template<>
struct new_host_space_impl<gln_space>
{
  template <typename fiber_type>
  static gln_space& new_space(fiber_bundles_namespace& xns)
  {
    return xns.new_group_space<fiber_type>();
  };
};

template<>
struct new_host_space_impl<jcb_space>
{
  template <typename fiber_type>
  static jcb_space& new_space(fiber_bundles_namespace& xns)
  {
    return xns.new_jacobian_space<fiber_type>();
  };
};
  

template <typename P>
typename P::host_type&
new_host_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  typedef P fiber_type;
  typedef typename P::host_type host_type;
  typedef new_host_space_impl<host_type> impl_type;
  
  // Call to function template member of template
  // requires telling compiler that dependent name is a template.

  host_type& result = impl_type::template new_space<fiber_type>(xns);

  // Postconditions:

  // Exit:

  return result;
}

//==============================================================================
// Tests for member functions of fiber and fiber space classes.
//==============================================================================

template<typename V>
void
test_volatile_common()
{
  // Preconditions:

  // Body:

  const string& lfiber_name = V::static_class_name();

  print_header("Begin testing " + lfiber_name + " common");


  // Default constructor.

  print_subheader("Testing " + lfiber_name + "()");

  V lfiber;

  int ld0 = lfiber.d();
  if(ld0 > 0)
  {
    for(int i=0; i<ld0; ++i)
    {
      lfiber.put_component(i, double(100+i));
    }
  }
    
  // Copy constructor.

  print_subheader("Testing " + lfiber_name
                  + "(const "+lfiber_name+"& xother)");

  V lcopy(lfiber);


  // Assignment operator.

  print_subheader("Testing " + lfiber_name
                  + "& = (const "+lfiber_name+"& xother");

  V lassign = lfiber;
   

  print_header("End testing " +lfiber_name+ " common");


  // Destructor.

  print_subheader("Testing ~" +lfiber_name+ "()");

  V* lptr = new V;
  delete lptr;

  //==========================================================================
  // vd facet
  //==========================================================================

  print_subheader("Testing virtual int d() const");

  int ld = lfiber.d();
  cout << "ld = " << ld << endl;

  //==========================================================================
  // tuple facet
  //==========================================================================

  print_subheader("Testing virtual int factor_ct() const");

  int lfactor_ct = lfiber.factor_ct();
  cout << "lfactor_ct = " << lfactor_ct << endl;


  //==========================================================================
  // abstract_poset_member facet
  //==========================================================================

  print_subheader("Testing virtual const string& class_name() const");

  const string& lclass_name = lfiber.class_name();
  cout << "lclass_name = " << lclass_name << endl;

 
  print_subheader("Testing static const string& static_class_name()");

  const string& lstatic_class_name = V::static_class_name();
  cout << "lstatic_class_name = " << lstatic_class_name << endl;


  print_subheader("Testing virtual " +lfiber_name+ "* clone() const");

  V* lclone = lfiber.clone();
  cout << "lclone = " << lclone << endl;
  delete lclone;

  print_subheader("Testing table_dofs_type table_dofs() const");

  typename V::table_dofs_type ltable_dofs = lfiber.table_dofs();

  //==========================================================================
  // any facet
  //==========================================================================

  print_subheader("Testing virtual bool is_ancestor_of",
                  "                          (const any_lite& xother) const");

  bool lis_ancestor_of = lfiber.is_ancestor_of(lcopy);
  cout << "lis_ancestor_of  = " << boolalpha << lis_ancestor_of  << endl;

 
  print_subheader("Testing bool invariant() const");

  bool linvariant = lfiber.invariant();
  cout << "linvariant = " << boolalpha << linvariant << endl;


  // Postconditions:

  // Exit:

  return;
}

template<typename V>
void
test_volatile_row_dofs()
{
  // Preconditions:

  // Body:

  const string& lfiber_name = V::static_class_name();

  V lfiber;

  int ld0 = lfiber.d();
  if(ld0 > 0)
  {
    for(int i=0; i<ld0; ++i)
    {
      lfiber.put_component(i, double(100+i));
    }
  }

  V lcopy(lfiber);

 
  print_subheader("Testing bool operator==(",
                  "                 const " +lfiber_name+"& xother) const");

  bool lequalequal = (lcopy == lfiber);

  cout << "lequalequal =" << boolalpha << lequalequal << endl;

  print_subheader("Testing ostream& operator<<(",
                  "          ostream& xos, const "+lfiber_name+"& x0");

  cout << "lfiber = \n" << lfiber << endl;
 
  //========================================================================

  //V(const row_dofs_type& xrow_dofs);

  typename V::row_dofs_type lrow_dofs;
  V lfiber_2(lrow_dofs);

  //V& operator=(const row_dofs_type& xrow_dofs);

  V lfiber_2_assign = lrow_dofs;

  //     //operator row_dofs_type& ();

  //     typename V::row_dofs_type& lrow_dofs1 = lfiber;

  //     //operator const row_dofs_type& () const;

  //     const V lfiber_const;
  //     const typename V::row_dofs_type& lrow_dofs3 = lfiber_const;

  // Use an array larger than any class d() value here.

  typename V::dof_type lresult[128];
  lfiber.components(lresult, 128);

  //virtual void put_components(const dof_type xcomps[], int xcomps_dimension);

  lfiber.put_components(lresult, 128);

  //==========================================================================

  V* lclone = lfiber.clone(true, true);
  delete lclone;

  //V::row_dofs_type lrow_dofs;
  typename V::row_dofs_type* lclone_row_dofs = lrow_dofs.clone(true, true);
  delete lclone_row_dofs;

  //==========================================================================

  // Postconditions:

  // Exit:

  return;
}

template<typename V>
void
test_volatile_class_tp_facet()
{
  // Preconditions:

  // Body:

  const string& lfiber_name = V::static_class_name();

  print_header("Begin testing " + lfiber_name + " tp facet");

  V lfiber;

  //virtual int p() const;

  int lp = lfiber.p();
  cout << "lp = " << lp << endl;

  //virtual int dd() const;

  int ldd = lfiber.dd();
  cout << "ldd = " << ldd << endl;

  //virtual pod_index_type vector_space_index() const;

  pod_index_type lvector_space_index = lfiber.vector_space_index();
  cout << "lvector_space_index = " << lvector_space_index << endl;

  print_footer("End testing " +lfiber_name+ " tp facet");

  // Postconditions:

  // Exit:

  return;
}

template<typename PB, typename PD>
void
test_persistent_common(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string& lfiber_name = PB::static_class_name();

  print_header("Begin testing " + lfiber_name);

  //==========================================================================

  typename PD::host_type& lhost = xns.new_fiber_space<PD>();
  lhost.get_read_write_access(true);
  
  //test_persistent_type<PB>(lhost);

  PB* lfiber = new PB(&lhost);

  typename PB::host_type* lhost2 = lfiber->host();
  cout << "lhost2 = " << lhost2 << endl;

  const string lmember_name("test_fiber");
  lfiber->put_name(lmember_name, true, false);

  const string& lclass_name = lfiber->class_name();
  cout << "lclass_name = " << lclass_name << endl;


  int lfactor_ct = lfiber->factor_ct();
  cout << "lfactor_ct = " << lfactor_ct << endl;

  //$$SCRIBBLE: Inconsistency amoung classes here???
  //PB* lfiber2 = new PB(*lfiber);
  PB* lfiber2 = new PB(lfiber);

  PB lfiber3 = *lfiber;

  const scoped_index lindex = lfiber->index();

  const poset* lposet = dynamic_cast<poset*>(&lhost);
  PB* lfiber4 = new PB(lposet, lmember_name);
  PB* lfiber5 = new PB(lposet, lindex);

  PB* lfiber6 = lfiber5->clone();

  //==========================================================================

  PB lfiber7;
  lfiber7 = *lfiber6;

  //e1 lother;
  //lfiber7 = lother;

  //==========================================================================

  // virtual const volatile_type& lite_prototype() const

  typename PB::volatile_type lvolatile = lfiber->lite_prototype();

  //virtual volatile_type* lite_type() const;

  typename PB::volatile_type* lvolatile_ptr = lfiber->lite_type();

  //==========================================================================

  lfiber->detach_from_state();
  lfiber2->detach_from_state();
  lfiber3.detach_from_state();
  lfiber4->detach_from_state();
  lfiber5->detach_from_state();
  lfiber6->detach_from_state();

  lfiber7.detach_from_state();

  delete lfiber;
  delete lfiber2;
  delete lfiber4;
  delete lfiber5;
  delete lfiber6;

  lhost.release_access();

  //==========================================================================

  print_footer("End testing " + lfiber_name);

  // Postconditions:

  // Exit:

  return;

}

template<typename PB, typename PD>
void
test_persistent_common_2(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string& lfiber_name = PB::static_class_name();

  print_header("Begin testing " + lfiber_name);

  //==========================================================================

  typename PD::host_type& lhost = xns.new_fiber_space<PD>();
  lhost.get_read_write_access(true);
  
  //test_persistent_type<PB>(lhost);

  PB* lfiber = new PB(&lhost);

  typename PB::host_type* lhost2 = lfiber->host();
  cout << "lhost2 = " << lhost2 << endl;

  const string lmember_name("test_fiber");
  lfiber->put_name(lmember_name, true, false);

  const string& lclass_name = lfiber->class_name();
  cout << "lclass_name = " << lclass_name << endl;


  int lfactor_ct = lfiber->factor_ct();
  cout << "lfactor_ct = " << lfactor_ct << endl;

  //$$SCRIBBLE: Inconsistency amoung classes here???
  PB* lfiber2 = new PB(*lfiber);
  //PB* lfiber2 = new PB(lfiber);

  PB lfiber3 = *lfiber;

  const scoped_index lindex = lfiber->index();

  const poset* lposet = dynamic_cast<poset*>(&lhost);
  PB* lfiber4 = new PB(lposet, lmember_name);
  PB* lfiber5 = new PB(lposet, lindex);

  PB* lfiber6 = lfiber5->clone();

  //==========================================================================

  PB lfiber7;
  lfiber7 = *lfiber6;

  //==========================================================================

  // virtual const volatile_type& lite_prototype() const

  typename PB::volatile_type lvolatile = lfiber->lite_prototype();

  //virtual volatile_type* lite_type() const;

  typename PB::volatile_type* lvolatile_ptr = lfiber->lite_type();

  //==========================================================================

  // Cleanup.

  lfiber->detach_from_state();
  lfiber2->detach_from_state();
  lfiber3.detach_from_state();
  lfiber4->detach_from_state();
  lfiber5->detach_from_state();
  lfiber6->detach_from_state();

  lfiber7.detach_from_state();

  delete lfiber;
  delete lfiber2;
  delete lfiber4;
  delete lfiber5;
  delete lfiber6;

  lhost.release_access();

  //==========================================================================

  print_footer("End testing " + lfiber_name);

  // Postconditions:

  // Exit:

  return;

}

template <typename T>
void test_spaces_common(fiber_bundles_namespace& xns, T& xspace)
{
  // Preconditions:

  // Body:

  typedef typename T::member_type M;
  typedef derived_space<T> TD;

  //$$SCRIBBLE: xxx_space classes have no static_class_name().
  //$$TODO: Implement xxx_space classes static_class_name().
  //string lspace_name = T::static_class_name();

  //$$HACK: To get class name.
  string lspace_name = M::static_class_name() + "_space";

  print_header("Begin testing common functions of class " + lspace_name);

  //==========================================================================

  // Get read access to xspace.

  xspace.get_read_access();

  // Get the path for xspace.

  print_subheader("Testing poset_path path() const");
  poset_path lpath = xspace.path();
  cout << "  lpath = " << lpath << endl;

  //virtual at1_space* clone() const;
  print_subheader("Testing virtual "+lspace_name+"* clone()");
  T* lspace_clone = xspace.clone();
  cout << "  lspace_clone = " << lspace_clone << endl;

  print_subheader(
                  "Testing virtual bool is_ancestor_of(const any* xother) const");
  bool lis_ancestor_of = xspace.is_ancestor_of(lspace_clone);
  cout << "  lis_ancestor_of = " << boolalpha << lis_ancestor_of << endl;

  //T lspace3(xspace);
  print_subheader("Testing copy constructor");
  TD* lspace3 = new TD(xspace);

  //T lspace4(xns, xspace.index(), true);
  print_subheader("Testing " + lspace_name +
                  "(const namespace_poset& xhost, scoped_index xindex,",
                  "            bool xauto_access)");
  TD* lspace4 = new TD(xns, xspace.index(), true);

  //T lspace4(xns, xspace.index().hub_pod(), true);
  print_subheader("Testing " + lspace_name +
                  "(const namespace_poset& xhost, pod_index_type xindex,",
                  "            bool xauto_access)");
  TD* lspace4a = new TD(xns, xspace.index().hub_pod(), true);

  //T lspace5(xns, xspace.path().poset_name(), true);
  print_subheader("Testing "+lspace_name+"(const namespace_poset& xhost,",
                  "                  const string& xname, bool xauto_access)");
  TD* lspace5 = new TD(xns, xspace.path().poset_name(), true);

  print_subheader("Testing "+lspace_name+"(const namespace_poset_member& xmbr,",
                  "             bool xauto_access)");
  xns.get_read_access();
  namespace_poset_member lmbr(&xns, xspace.index());
  xns.release_access();
  TD* lspace6 = new TD(lmbr, true);
  lmbr.detach_from_state();

  //T(M* xtop, M* xbottom);
  print_subheader("Testing "+lspace_name+"(xtop, xbottom)");
  TD* lspace7 = new TD(new M, new M);

  //T& operator=(const poset_state_handle& xother);
  print_subheader("Testing operator=(const poset_state_handle& xother)");
  TD* lspace8 = new TD;
  lspace5->get_read_access();
  poset_state_handle* lpsh = lspace5;
  lspace8->operator=(*lpsh);

  //==========================================================================

  print_footer("End testing common functions of class " + lspace_name);

  // Postconditions:

  // Exit:
  
}


} // namespace fiber_bundle

#endif // ifndef TEST_FIBERS_IMPL_H
