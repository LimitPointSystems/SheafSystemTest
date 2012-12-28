
// $RCSfile: test_fields.impl.h,v $ $Revision: 1.10.36.1 $ $Date: 2012/11/27 20:16:30 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Implementation of field test function templates.

#ifndef TEST_FIELDS_IMPL_H
#define TEST_FIELDS_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TEST_FIELDS_H
#include "test_fields.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef FIELD_AT0_H
#include "field_at0.h"
#endif

#ifndef FIELD_E3_H
#include "field_e3.h"
#endif

#ifndef INDEX_SPACE_ITERATOR_H
#include "index_space_iterator.h"
#endif

#ifndef SEC_AT0_H
#include "sec_at0.h"
#endif

#ifndef SEC_AT0_SPACE_H
#include "sec_at0_space.h"
#endif

#ifndef SEC_ED_INVERTIBLE_H
#include "sec_ed_invertible.h"
#endif

#ifndef STD_IOMANIP_H
#include "std_iomanip.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_SSTREAM_H
#include "std_sstream.h"
#endif

#ifndef TEST_UTILS_H
#include "test_utils.h"
#endif

//$$SCRIBBLE:
//  This code is meant for testing purposes only.
//  It is not meant to be a set of examples of how to use the library.

namespace fields
{

//=============================================================================
// TEST ASSIGNMENT
//=============================================================================

///
/// Test assignment operators.
///
template <typename F>
void
test_field_assignment(fiber_bundles_namespace& xns,
                      const poset_path& xbase_path,
                      const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));

  // Body:

  typedef F field_type;
  typedef typename field_type::property_section_type sec_type;
  typedef typename sec_type::fiber_type fiber_type;
  typedef typename fiber_type::volatile_type volatile_type;

  string field_name = F::static_class_name();
  print_header("Testing assignment for " + field_name);

  //============================================================================

  // Create fields for use in testing.

  static const int num_fields = 3;

  field_type lfield[3];
  make_test_fields(xns, xbase_path, xcoords_path, "property",
                   lfield, num_fields);

  //============================================================================

  // Create a volatile fiber.

  volatile_type lvolatile;
  for(int i=0; i<lvolatile.d(); ++i)
  {
    lvolatile[i] = 100*(1+i);
  }

  //============================================================================

  // Create a persistent fiber.

  typename fiber_type::host_type& lhost = xns.new_fiber_space<fiber_type>();
  lhost.get_read_write_access();

  fiber_type lpersistent(lhost, lvolatile, true);
  lpersistent.put_name("lpersistent", true, false);

  //============================================================================

  lfield[0].get_read_write_access(true, false);
  lfield[1].get_read_write_access(true, false);
  lfield[2].get_read_write_access(true, false);

  // Assign a field to a field.

  print_field(lfield[0]);

  lfield[1] = lfield[0];
  print_result("lfield[1] = lfield[0]:", lfield[1]);

  // Assign a field to a volatile type.

  cout << "  lvolatile: \n    " << lvolatile << endl << endl;

  lfield[0] = lvolatile;
  print_result("lfield[0] = lvolatile:", lfield[0]);

 // Assign a field to a persistent fiber type.

  cout << "  lpersistent: \n    " << lpersistent << endl << endl;

  lfield[1] = lpersistent;
  print_result("lfield[1] = lpersistent:", lfield[1]);

 // Assign a field to a section.

  lfield[2] = lfield[1].property();
  print_result("lfield[2] = lfield[1].property():", lfield[2]);

  //Cleanup.

  lpersistent.detach_from_state();
  lhost.release_access();
  lfield[0].release_access();
  lfield[1].release_access();
  lfield[2].release_access();

  // Postconditions:

  // Exit:
}

//==============================================================================
// ATP FACET
//==============================================================================

///
template <typename F0, typename F1, typename FR>
void
test_field_hook_product(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path,
                        const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));
  require(unexecutable("F0, F1, FR are compatible"));

  // Body:

  const string& lname_0 = F0::static_class_name();
  const string& lname_1 = F1::static_class_name();
  const string& lname_r = FR::static_class_name();
  const string lop_string = lname_0 + " ^ " + lname_1 + " = " + lname_r;
  print_header("Testing hook product for: " + lop_string);

  //============================================================================

  // Create fields for use in testing.

  static const int lnum_sections = 2;

  F0 ltensor_0[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_0_property",
                   ltensor_0, lnum_sections);

  F1 ltensor_1[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_1_property",
                   ltensor_1, lnum_sections);

  FR ltensor_r[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_r_property",
                   ltensor_r, lnum_sections);

  //============================================================================

  // Execute the test(s).

  print_field(ltensor_0[0]);
  print_field(ltensor_1[0]);

  hook(ltensor_0[0], ltensor_1[0], ltensor_r[0], true);
  print_result("hook(ltensor_0[0], ltensor_1[0], ltensor_r[0]):",
                ltensor_r[0]);

  //============================================================================

  // Postconditions:

  // Exit:
}

///
template <typename F0, typename FR>
void
test_field_star_operator(fiber_bundles_namespace& xns,
                         const poset_path& xbase_path,
                         const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));
  require(unexecutable("F0, F1, FR are compatible"));

  // Body:

  const string& lname_0 = F0::static_class_name();
  const string& lname_r = FR::static_class_name();
  const string lop_string = "*" + lname_0 + " = " + lname_r;
  print_header("Testing star operator for: " + lop_string);

  //============================================================================

  // Create fields for use in testing.

  static const int lnum_sections = 2;

  F0 ltensor_0[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_0_property",
                   ltensor_0, lnum_sections);

  FR ltensor_r[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_r_property",
                   ltensor_r, lnum_sections);

  //============================================================================

  // Execute the tests.

  print_field(ltensor_0[0]);

  star(ltensor_0[0], ltensor_r[0], true);
  print_result("star(ltensor_0[0], ltensor_r[0]):",
                ltensor_r[0]);

  //============================================================================

  // Postconditions:

  // Exit:
}

///
template <typename F0, typename F1, typename FR>
void
test_field_wedge_product(fiber_bundles_namespace& xns,
                         const poset_path& xbase_path,
                         const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));
  require(unexecutable("F0, F1, FR are compatible"));

  // Body:

  const string& lname_0 = F0::static_class_name();
  const string& lname_1 = F1::static_class_name();
  const string& lname_r = FR::static_class_name();
  const string lop_string = lname_0 + " (X) " + lname_1 + " = " + lname_r;
  print_header("Testing wedge product for: " + lop_string);

  //============================================================================

  // Create fields for use in testing.

  static const int lnum_sections = 2;

  F0 ltensor_0[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_0_property",
                   ltensor_0, lnum_sections);

  F1 ltensor_1[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_1_property",
                   ltensor_1, lnum_sections);

  FR ltensor_r[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_r_property",
                   ltensor_r, lnum_sections);

  //============================================================================

  // Execute the tests.

  print_field(ltensor_0[0]);
  print_field(ltensor_1[0]);

  wedge(ltensor_0[0], ltensor_1[0], ltensor_r[0], true);
  print_result("wedge(ltensor_0[0], ltensor_1[0], ltensor_r[0]):",
                ltensor_r[0]);

  //@todo Additional tests.

  //============================================================================

  // Postconditions:

  // Exit:
}

//==============================================================================
// ED FACET
//==============================================================================

///
template <typename F>
void
test_field_ed_facet(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));

  // Body:

  typedef F vector_type;
  typedef field_at0 scalar_type;

  const string& field_name = F::static_class_name();
  print_header("Testing field_ed facet for " + field_name);

  //============================================================================

  // Create fields for use in testing.

  static const int num_sections = 4;

  vector_type lvector[4];
  make_test_fields(xns, xbase_path, xcoords_path, "vector_property",
                    lvector, num_sections);

  scalar_type lscalar[4];
  make_test_fields(xns, xbase_path, xcoords_path, "scalar_property",
                   lscalar, num_sections);

  //============================================================================

  // Execute the tests.

  print_field(lvector[0]);
  print_field(lvector[1]);

  // Test dot_product:

  dot(lvector[0], lvector[1], lscalar[0], true);
  print_result("dot(lvector[0], lvector[1], lscalar[0]):", lscalar[0]);

  // Test length:

  length(lvector[0], lscalar[1], true);
  print_result("length(lvector[0], lscalar[1]):", lscalar[1]);

  // Test normalize:

  normalize(lvector[0], lvector[2], true);
  print_result("normalize(lvector[0], lvector[2]):", lvector[2]);

  // After normalization lengths should all be 1.0:

  length(lvector[2], lscalar[2], true);
  print_result("length(lvector[2], lscalar[2]):", lscalar[2]);

  // Test put_length:

  put_length(lvector[3], 123.45, true);
  print_result("put_length(lvector[3], 123.45):", lvector[3]);

  // After put_length lengths should all be 123.45:

  length(lvector[3], lscalar[3], true);
  print_result("length(lvector[6], lscalar[3]):", lscalar[3]);

  // Postconditions:

  // Exit:

  return;
}


//==============================================================================
// JCB FACET
//==============================================================================

///
template <typename FJCB, typename FVECTOR,  typename FCOVECTOR>
void
test_field_jcb_facet(fiber_bundles_namespace& xns,
                     const poset_path& xbase_path,
                     const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));

  // Body:

  typedef FJCB jacobian_type;
  typedef FVECTOR vector_type;
  typedef FCOVECTOR covector_type;

  string field_name = FJCB::static_class_name();
  print_header("Testing field_jcb facet for " + field_name);

  //============================================================================

  // Create fields for use in testing.

  static const int num_fields = 3;

  jacobian_type ljacobian[3];
  make_test_fields(xns, xbase_path, xcoords_path, "jacobian_property",
                   ljacobian, num_fields);

  vector_type lvector[3];
  make_test_fields(xns, xbase_path, xcoords_path, "vector_property",
                   lvector, num_fields);

  covector_type lcovector[3];
  make_test_fields(xns, xbase_path, xcoords_path, "covector_property",
                   lcovector, num_fields);

  //============================================================================

  // Execute the tests.

  print_field(ljacobian[0]);
  print_field(lvector[0]);

  // Test push:

  lvector[0].property().put_is_p_vector(true);
  lcovector[1].property().put_is_p_vector(true);

  push(ljacobian[0], lvector[0], lcovector[1], true);
  print_result("push(ljacobian[0], lvector[0], lcovector[0]):", lcovector[0]);

  // Test pull:

  lcovector[0].property().put_is_p_form(true);
  lvector[1].property().put_is_p_form(true);

  pull(ljacobian[0], lcovector[0], lvector[1], true);
  print_result("pull(ljacobian[0], lcovector[0], lvector[1]):", lvector[1]);

  //============================================================================

  // Postconditions:

  // Exit:
}


//==============================================================================
// MET FACET
//==============================================================================

///
template <typename F, typename FVECTOR>
void
test_field_met_facet(fiber_bundles_namespace& xns,
                     const poset_path& xbase_path,
                     const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));

  // Body:

  typedef F metric_type;
  typedef FVECTOR vector_type;

  string field_name = F::static_class_name();
  print_header("Testing field_met facet for " + field_name);

  //============================================================================

  // Create fields for use in testing.

  static const int num_fields = 3;

  metric_type lmetric[3];
  make_test_fields(xns, xbase_path, xcoords_path, "metric_property",
                   lmetric, num_fields);

  vector_type lvector[3];
  make_test_fields(xns, xbase_path, xcoords_path, "vector_property",
                   lvector, num_fields);

  //============================================================================

  // Execute the tests.

  print_field(lmetric[0]);
  print_field(lvector[0]);

  // Test lower:

  lmetric[0].property().put_is_covariant(true);
  lvector[0].property().put_is_contravariant(true);
  lvector[1].property().put_is_covariant(true);

  lower(lmetric[0], lvector[0], lvector[1], true);
  print_result("lower(lmetric[0], lvector[0], lvector[1]):", lvector[1]);

  // Test raise:

  lmetric[0].property().put_is_contravariant(true);
  lvector[0].property().put_is_covariant(true);
  lvector[2].property().put_is_contravariant(true);

  raise(lmetric[0], lvector[0], lvector[2], true);
  print_result("raise(lmetric[0], lvector[0], lvector[2]):", lvector[2]);

  //============================================================================

  // Postconditions:

  // Exit:
}

//==============================================================================
// ST2  FACET
//==============================================================================

///
template <typename F>
void
test_field_st2_facet(fiber_bundles_namespace& xns,
                     const poset_path& xbase_path,
                     const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));

  // Body:

  typedef F tensor_type;
  typedef field_at0 scalar_type;

  const string& field_name = F::static_class_name();
  print_header("Testing field_st2 facet for " + field_name);

  //============================================================================

  // Create fields for use in testing.

  tensor_type ltensor[1];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_property",
                    ltensor, 1);

  scalar_type lscalar[2];
  make_test_fields(xns, xbase_path, xcoords_path, "scalar_property",
                   lscalar, 2);

  //============================================================================

  // Execute the tests.

  print_field(ltensor[0]);

  // Test dot_product:

  trace(ltensor[0], lscalar[0], true);
  print_result("trace(ltensor[0], lscalar[0]):", lscalar[0]);

  // Test determinant:

  // Skip this test for "field_met_*" classes because determinant is not
  // implemented in those cases.

  if(field_name.find("field_met_") != 0)
  {
    determinant(ltensor[0], lscalar[1], true);
    print_result("determinant(ltensor[0], lscalar[1]):", lscalar[1]);
  }

  // Postconditions:

  // Exit:

  return;
}

//==============================================================================
// TP FACET
//==============================================================================

///
template <typename TP, typename ATP, typename STP>
void
test_field_tp_facet(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));
  require(unexecutable("TP, ATP, STP are compatible"));

  // Body:

  const string& field_name = TP::static_class_name();
  print_header("Testing field_tp facet for " + field_name);

  //============================================================================

  // Create fields for use in testing.

  static const int num_fields = 2;

  TP lgen_tensor[2];
  make_test_fields(xns, xbase_path, xcoords_path, "general_tensor_property",
                   lgen_tensor, num_fields);

  ATP lalt_tensor[2];
  make_test_fields(xns, xbase_path, xcoords_path, "alt_tensor_property",
                   lalt_tensor, num_fields);

  STP lsym_tensor[2];
  make_test_fields(xns, xbase_path, xcoords_path, "sym_tensor_property",
                   lsym_tensor, num_fields);

  //============================================================================

  // Execute the tests.

  print_field(lgen_tensor[0]);

  // Test alt (antisymmetric part) function.

  alt(lgen_tensor[0], lalt_tensor[0], true);
  print_result("alt(lgen_tensor[0], lalt_tensor[0]):", lalt_tensor[0]);

  // Test sym (symmetric part) function.

  sym(lgen_tensor[0], lsym_tensor[0], true);
  print_result("sym(lgen_tensor[0], lsym_tensor[0]):", lsym_tensor[0]);

  //@todo Additional tests.

  //============================================================================

  // Postconditions:

  // Exit:
}

///
template <typename F0, typename F1, typename FR>
void
test_field_tensor_product(fiber_bundles_namespace& xns,
                          const poset_path& xbase_path,
                          const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));
  require(unexecutable("F0, F1, FR are compatible"));

  // Body:

  const string& lname_0 = F0::static_class_name();
  const string& lname_1 = F1::static_class_name();
  const string& lname_r = FR::static_class_name();
  const string lop_string = lname_0 + " (x) " + lname_1 + " = " + lname_r;
  print_header("Testing tensor product for: " + lop_string);

  //============================================================================

  // Create fields for use in testing.

  static const int lnum_fields = 2;

  F0 ltensor_0[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_0_property",
                   ltensor_0, lnum_fields);

  F1 ltensor_1[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_1_property",
                   ltensor_1, lnum_fields);

  FR ltensor_r[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_r_property",
                   ltensor_r, lnum_fields);

  //============================================================================

  // Execute the tests.

  print_field(ltensor_0[0]);
  print_field(ltensor_1[0]);

  tensor(ltensor_0[0], ltensor_1[0], ltensor_r[0], true);
  print_result("tensor(ltensor_0[0], ltensor_1[0], ltensor_r[0]):",
                ltensor_r[0]);

  //============================================================================

  // Postconditions:

  // Exit:
}

///
template <typename F0, typename FR>
void
test_field_contract(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));
  require(unexecutable("F0, FR are compatible"));

  // Body:

  const string& lname_0 = F0::static_class_name();
  print_header("Testing contract for: " + lname_0);

  //============================================================================

  // Create fields for use in testing.

  static const int lnum_fields = 2;

  F0 ltensor_0[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_0_property",
                     ltensor_0, lnum_fields);

  FR ltensor_r[2];
  make_test_fields(xns, xbase_path, xcoords_path, "tensor_r_property",
                     ltensor_r, lnum_fields);

  //============================================================================

  // Execute the tests.

  print_field(ltensor_0[0]);

  ltensor_0[0].property().put_is_contravariant(0, true);
  ltensor_0[0].property().put_is_covariant(1, true);
  contract(ltensor_0[0], 0, 1, ltensor_r[0], true);
  print_result("contract(ltensor_0[0], 0, 1, ltensor_r[0]):", ltensor_r[0]);

  if(ltensor_0[0].property().p(true) >= 3)
  {
    ltensor_0[0].property().put_is_covariant(1, true);
    ltensor_0[0].property().put_is_contravariant(2, true);
    contract(ltensor_0[0], 1, 2, ltensor_r[1], true);
    print_result("contract(ltensor_0[0], 1, 2, ltensor_r[1]):", ltensor_r[1]);
  }

  //============================================================================

  // Postconditions:

  // Exit:
}

//==============================================================================
// VD FACET
//==============================================================================

///
template <typename F>
void
test_field_vd_facet(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));

  // Body:

  typedef F field_vd_type;
  string field_name = F::static_class_name();
  print_header("Testing field_vd facet for " + field_name);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int num_fields = 5;

  field_vd_type lvector[5];
  make_test_fields(xns, xbase_path, xcoords_path, "vector_property",
                   lvector, num_fields);

  field_at0 lscalar[5];
  make_test_fields(xns, xbase_path, xcoords_path, "scalar_property",
                   lscalar, num_fields);

  //============================================================================

  // Execute the tests.

  print_field(lvector[0]);
  print_field(lvector[1]);

  // Add: lvector[3] = lvector[0] + lvector[1];

  add(lvector[0], lvector[1], lvector[2], true);
  print_result("add(lvector[0], lvector[1], lvector[2]):", lvector[2]);

  // Test add_equal:

  add_equal(lvector[2], lvector[1], true);
  print_result("add_equal(lvector[2], lvector[1]):", lvector[2]);

  cout << boolalpha;
  cout << "lvector[0].property().is_covector(true) = "
       << lvector[0].property().is_covector(true) << endl;
  cout << "lvector[1].property().is_covector(true) = "
       << lvector[1].property().is_covector(true) << endl;
  cout << "lvector[2].property().is_covector(true) = "
       << lvector[2].property().is_covector(true) << endl;
  cout << endl;
  cout << boolalpha;
  cout << "lvector[0].property().is_vector(true) = "
       << lvector[0].property().is_vector(true) << endl;
  cout << "lvector[1].property().is_vector(true) = "
       << lvector[1].property().is_vector(true) << endl;
  cout << "lvector[2].property().is_vector(true) = "
       << lvector[2].property().is_vector(true) << endl;
  cout << endl;

  // Test subtract:

  subtract(lvector[2], lvector[1], lvector[3], true);
  print_result("subtract(lvector[0], lvector[1], lvector[3]):", lvector[3]);

  // Test subtract_equal:

  subtract_equal(lvector[3], lvector[1], true);
  print_result("subtract_equal(lvector[3], lvector[1]):", lvector[3]);

  // Test multiply:

  multiply(lvector[2], 5.0, lvector[4], true);
  print_result("multiply(lvector[2], 5, lvector[4]):", lvector[4]);

  // Test multiply_equal:

  multiply_equal(lvector[4], 5.0, true);
  print_result("multiply_equal(lvector[4], 5):", lvector[4]);

  // Test multiply:

//   multiply(lvector[2], lscalar[0], lvector[4], true);
//   print_result("multiply(lvector[2], lscalar[0], lvector[4]):", lvector[4]);
//   print_field(lvector[2]);
//   print_field(lscalar[0]);

  // Test divide:

  divide(lvector[2], 5.0, lvector[4], true);
  print_result("divide(lvector[2], 5, lvector[4]):", lvector[4]);

  // Test divide_equal:

  divide_equal(lvector[4], 5.0, true);
  print_result("divide_equal(lvector[4], 5):", lvector[4]);

  // Test divide:

//   divide(lvector[4], lscalar[0], lvector[2], true);
//   print_result("divide(lvector[4], lscalar[0], lvector[2]):", lvector[2]);
//   print_field(lvector[4]);
//   print_field(lscalar[0]);

  //============================================================================

//   // Test max:

//   typedef typename F::fiber_type::volatile_type volatile_type;
//   const string& lname_v = volatile_type::static_class_name(); 

//   volatile_type lfiber;
//   max(lvector[0], lfiber, true);
//   cout << "max(lvector[0], lfiber): lfiber = " <<  lfiber << endl;

//   volatile_type* lfiber1 = max(lvector[0], true);
//   cout << lname_v <<  "* lfiber1 = max(lvector[0]): *lfiber1 = "
//        <<  *lfiber1 << endl;
//   delete lfiber1;

//   cout << endl;

//   // Test min:

//   min(lvector[0], lfiber, true);
//   cout << "min(lvector[0], lfiber): lfiber = " <<  lfiber << endl;

//   volatile_type* lfiber2 = min(lvector[0], true);
//   cout << lname_v <<  "* lfiber2 = min(lvector[0]): *lfiber2 = "
//        <<  *lfiber2 << endl;
//   delete lfiber2;
  
//   cout << endl;

  //============================================================================

  // Test contract:

  // Skip this test for field_jcb classes because the put_is_dual function
  // is a noop in those cases.

  if(field_name.find("field_jcb_") != 0)
  {
    // The covector must be dual.

    lvector[1].property().put_is_covector(true);
    contract(lvector[0], lvector[1], lscalar[0], true);
    print_result("contract(lvector[0], lvector[1], lscalar[0]):", lscalar[0]);
  }

  //============================================================================

  // Postconditions:

  // Exit:
}

//==============================================================================
//==============================================================================

template <typename T>
void print_field(const T& xfield, const string& xindent, bool xauto_access)
{
  // Preconditions:

  require(xfield.property().state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    xfield.property().get_read_access();
  }

  typedef sec_vd::dof_type dof_type;
  typedef typename T::property_section_type section_type;
  typedef typename section_type::fiber_type::volatile_type volatile_type;

  volatile_type lfiber;

  int ld = lfiber.d();

  section_type& lsection = const_cast<section_type&>(xfield.property());
  index_space_iterator& litr =
    lsection.schema().discretization_id_space().get_iterator();
  while(!litr.is_done())
  {
    lsection.get_fiber(litr.pod(), lfiber);
    cout << xindent << setw(5) << litr.pod() << " : ";

    for(int i=0; i<ld; ++i)
    {
      cout << " " << setw(10) << lfiber.component(i);
    }
    cout << endl;

    litr.next();
  }
  lsection.schema().discretization_id_space().release_iterator(litr);

  if(xauto_access)
  {
    xfield.property().release_access();
  }

  // Postconditions:

  // Exit:
}

///
template <typename T>
void print_result(const string& xtext,
                  const T& xfield,
                  const string& xindent,
                  bool xauto_access)
{
  // Preconditions:

  require(precondition_of(print_field(xsection, xindent, xauto_access)));

  // Body:

  cout << xtext << endl;
  print_field(xfield, xindent, xauto_access);

  // Postconditions:

  require(postcondition_of(print_field(xfield, xindent, xauto_access)));

  // Exit:
}

//==============================================================================


///
template <typename T>
void make_test_sections(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path,
                        const string& xbase_property_name,
                        T xsections[],
                        int xnum_sections)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(unexecutable("xsections dimension is >= num_sections"));

  // Body:

  // Create a section space factory with
  // base_space path = xbase_path and
  // section space name = xspace_name.

  // Create a unique name for the section space.

  string lspace_name;
  create_section_space_name(xbase_property_name, lspace_name);

  // We have to make sure that the representation is the same for all
  // sections created here.  Otherwise we will end up trying to combine
  // "apples and oranges" is the vector/tensor operations (and will
  // violate pre- or postconditions).

  // For testing make all reps "vertex_element_dlinear".
  // We could eliminate this hard coding of the rep by adding
  // an additional argument to this function. 

  static const poset_path
     lrep_path(fiber_bundles_namespace::standard_sec_rep_descriptor_poset_name(),
               //"element_element_constant");
               "vertex_element_dlinear");

  // Create xnum_sections sections with names
  // xbase_field_name_# where "#" goes from 0 to xnum_sections-1.

  // Also, assign values to the section degrees of freedom.
  // Currently these values are not realistic and are the same
  // for each section.  

  ostringstream lname;
  for(int i=0; i<xnum_sections; ++i)
  {
    lname.str("");
    lname << xbase_property_name << "_" << i;
    typename T::host_type& lhost = xns.new_section_space<T>(lspace_name, xbase_path, lrep_path, true);
    lhost.get_read_write_access();
    xsections[i] = *(new T(&lhost));
    xsections[i].put_name(lname.str(), true, true);
    set_dofs(xsections[i]);
    xsections[i].release_access();
  }

  // Postconditions:

  // Exit:

  return;
}



///
template <typename F>
void make_test_fields(fiber_bundles_namespace& xns,
                      const poset_path& xbase_path,
                      const poset_path& xcoords_path,
                      const string& xbase_property_name,
                      F xfields[],
                      int xnum_fields)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(xns.contains_poset_member(xcoords_path));
  require(unexecutable("xfields dimension is >= num_fields"));

  // Body:

  typedef typename F::property_section_type T;
  T* lsections = new T[xnum_fields];

  make_test_sections(xns,
                     xbase_path,
                     xbase_property_name,
                     lsections,
                     xnum_fields);

  sec_ed lcoords(&xns, xcoords_path, true);
  lcoords.get_read_access();

  for(int i=0; i<xnum_fields; ++i)
  {
    lsections[i].get_read_access();
    xfields[i].coordinates().attach_to_state(&lcoords);
    xfields[i].property().attach_to_state(&lsections[i]);
    xfields[i].base_space().attach_to_state(
      &(lsections[i].schema().base_space()));
    lsections[i].release_access();
  }

  for(int i=0; i<xnum_fields; ++i)
  {
    lsections[i].detach_from_state();
  }

  delete [] lsections;
  lcoords.release_access();
  lcoords.detach_from_state();

  // Postconditions:

  ensure(unexecutable("for i=0; i<xnum_fields; namespace contains lsections[i]."));

  // Exit:

  return;
}

///
template <typename T>
void
set_dofs(T& xresult)
{
  // Changes to the get/put dofs interface are planned and the
  // following will have to be modified when the changes are in place.

  typedef sec_vd::dof_type dof_type;
  typedef typename T::fiber_type::volatile_type volatile_type;

  volatile_type lfiber;

  int ld = lfiber.d();
  size_type ldisc_ct = xresult.schema().discretization_ct();

  index_space_iterator& litr =
    xresult.schema().discretization_id_space().get_iterator();
  while(!litr.is_done())
  {
    pod_index_type i = litr.pod();

    // Just make up some values for testing.

    for(int n=0; n<ld; ++n)
    {
      lfiber.put_component(n, (1.1)*(i+1+n*ldisc_ct));
    }

    xresult.put_fiber(i, lfiber);

    litr.next();
  }
  xresult.schema().discretization_id_space().release_iterator(litr);
}

} // namespace fields


#endif // ifndef TEST_FIELDS_IMPL_H
