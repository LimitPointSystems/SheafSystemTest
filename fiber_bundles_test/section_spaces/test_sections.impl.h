

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation of section test function templates.

#ifndef TEST_SECTIONS_IMPL_H
#define TEST_SECTIONS_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TEST_SECTIONS_H
#include "test_sections.h"
#endif

#ifndef ARG_LIST_H
#include "arg_list.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef AT0_SPACE_H
#include "at0_space.h"
#endif

#ifndef AT1_SPACE_H
#include "at1_space.h"
#endif

#ifndef BINARY_SECTION_SPACE_SCHEMA_POSET_H
#include "binary_section_space_schema_poset.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef SEC_AT0_H
#include "sec_at0.h"
#endif

#ifndef SEC_AT0_SPACE_H
#include "sec_at0_space.h"
#endif

#ifndef SEC_AT1_H
#include "sec_at1.h"
#endif

#ifndef SEC_AT1_SPACE_H
#include "sec_at1_space.h"
#endif

#ifndef SEC_AT2_E2_H
#include "sec_at2_e2.h"
#endif

#ifndef SEC_AT2_E3_H
#include "sec_at2_e3.h"
#endif

#ifndef SEC_AT3_E3_H
#include "sec_at3_e3.h"
#endif

#ifndef SEC_E1_H
#include "sec_e1.h"
#endif

#ifndef SEC_E2_H
#include "sec_e2.h"
#endif

#ifndef SEC_E3_H
#include "sec_e3.h"
#endif

#ifndef SEC_JCB_E13_H
#include "sec_jcb_e13.h"
#endif

#ifndef SEC_JCB_E23_H
#include "sec_jcb_e23.h"
#endif

#ifndef SEC_JCB_E33_H
#include "sec_jcb_e33.h"
#endif

#ifndef SEC_JCB_E13_H
#include "sec_jcb_e13.h"
#endif

#ifndef SEC_JCB_E13_H
#include "sec_jcb_e13.h"
#endif

#ifndef SEC_MET_E1_H
#include "sec_met_e1.h"
#endif

#ifndef SEC_MET_E2_H
#include "sec_met_e2.h"
#endif

#ifndef SEC_MET_E3_H
#include "sec_met_e3.h"
#endif

#ifndef SEC_ST2_E2_H
#include "sec_st2_e2.h"
#endif

#ifndef SEC_ST2_E3_H
#include "sec_st2_e3.h"
#endif

#ifndef SEC_ST3_E3_H
#include "sec_st3_e3.h"
#endif

#ifndef SEC_STP_SPACE_H
#include "sec_stp_space.h"
#endif

#ifndef SEC_T2_E2_H
#include "sec_t2_e2.h"
#endif

#ifndef SEC_T2_E3_H
#include "sec_t2_e3.h"
#endif

#ifndef SEC_T3_E3_H
#include "sec_t3_e3.h"
#endif

#ifndef SEC_TP_SPACE_H
#include "sec_tp_space.h"
#endif

#ifndef SEC_VD_IMPL_H
#include "sec_vd.impl.h"
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

#ifndef STP_SPACE_H
#include "stp_space.h"
#endif

#ifndef TP_SPACE_H
#include "tp_space.h"
#endif

#ifndef TEST_UTILS_H
#include "test_utils.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// ASSIGNMENT TESTS
//==============================================================================

template <typename S>
void
test_assignment(fiber_bundles_namespace& xns,
                const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));

  // Body:

  typedef S sec_type;
  string section_name = S::static_class_name();

  typedef typename sec_type::fiber_type fiber_type;
  typedef  typename fiber_type::volatile_type volatile_type;

  print_header("Testing assignment for " + section_name);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  sec_type lvector[2];
  make_test_sections(xns, xbase_path, "test_assignment", "vector", lvector, 2);

  lvector[0].get_read_write_access();
  lvector[1].get_read_write_access();

  // Assign a section to a section.

  lvector[1] = lvector[0];

  // Cleanup.

  lvector[0].detach_from_state();
  lvector[1].detach_from_state();

  // Postconditions:

  // Exit:
}

//==============================================================================
// SEC_ATP FACET
//==============================================================================

template <typename S0, typename S1, typename SR>
void
test_sec_hook_product(fiber_bundles_namespace& xns,
		      const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(unexecutable("S0, S1, SR are compatible"));

  // Body:

  using namespace fiber_bundle::sec_atp_algebra;

  const string& lname_0 = S0::static_class_name();
  const string& lname_1 = S1::static_class_name();
  const string& lname_r = SR::static_class_name();
  const string lop_string = lname_0 + " ^ " + lname_1 + " = " + lname_r;
  print_header("Testing hook product for: " + lop_string);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int lnum_sections = 2;

  S0 ltensor_0[2];
  make_test_sections(xns, xbase_path, "test_hook", "tensor_0", ltensor_0, lnum_sections);

  S1 ltensor_1[2];
  make_test_sections(xns, xbase_path, "test_hook", "tensor_1", ltensor_1, lnum_sections);

  SR ltensor_r[2];
  make_test_sections(xns, xbase_path, "test_hook", "tensor_r", ltensor_r, lnum_sections);

  //============================================================================

  // Execute the test(s).

  print_section(ltensor_0[0]);
  print_section(ltensor_1[0]);

  hook(ltensor_0[0], ltensor_1[0], ltensor_r[0], true);
  print_result("hook(ltensor_0[0], ltensor_1[0], ltensor_r[0]):", ltensor_r[0]);

  //============================================================================

  // Detach the sections.

  for(int i=0; i<lnum_sections; ++i)
  {
    ltensor_0[i].detach_from_state();
    ltensor_1[i].detach_from_state();
    ltensor_r[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

template <typename S0, typename SR>
void
test_sec_star_operator(fiber_bundles_namespace& xns,
                       const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(unexecutable("S0, S1, SR are compatible"));

  // Body:

  using namespace fiber_bundle::sec_atp_algebra;

  const string& lname_0 = S0::static_class_name();
  const string& lname_r = SR::static_class_name();
  const string lop_string = "*" + lname_0 + " = " + lname_r;
  print_header("Testing star operator for: " + lop_string);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int lnum_sections = 2;

  S0 ltensor_0[2];
  make_test_sections(xns, xbase_path, "test_star", "tensor_0", ltensor_0, lnum_sections); 

  SR ltensor_r[2];
  make_test_sections(xns, xbase_path, "test_star", "tensor_r", ltensor_r, lnum_sections);

  //============================================================================

  // Execute the tests.

  print_section(ltensor_0[0]);

  star(ltensor_0[0], ltensor_r[0], true);
  print_result("star(ltensor_0[0], ltensor_r[0]):", ltensor_r[0]);

  //============================================================================

  // Detach the sections.

  for(int i=0; i<lnum_sections; ++i)
  {
    ltensor_0[i].detach_from_state();
    ltensor_r[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

template <typename S0, typename S1, typename SR>
void
test_sec_wedge_product(fiber_bundles_namespace& xns,
                       const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(unexecutable("S0, S1, SR are compatible"));

  // Body:

  using namespace fiber_bundle::sec_atp_algebra;

  const string& lname_0 = S0::static_class_name();
  const string& lname_1 = S1::static_class_name();
  const string& lname_r = SR::static_class_name();
  const string lop_string = lname_0 + " (X) " + lname_1 + " = " + lname_r;
  print_header("Testing wedge product for: " + lop_string);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int lnum_sections = 2;

  S0 ltensor_0[2];
  make_test_sections(xns, xbase_path, "test_wedge", "tensor_0", ltensor_0, lnum_sections);

  S1 ltensor_1[2];
  make_test_sections(xns, xbase_path, "test_wedge", "tensor_1", ltensor_1, lnum_sections);

  SR ltensor_r[2];
  make_test_sections(xns, xbase_path, "test_wedge", "tensor_r", ltensor_r, lnum_sections);

  //============================================================================

  // Execute the tests.

  print_section(ltensor_0[0]);
  print_section(ltensor_1[0]);

  wedge(ltensor_0[0], ltensor_1[0], ltensor_r[0], true);
  print_result("wedge(ltensor_0[0], ltensor_1[0], ltensor_r[0]):", ltensor_r[0]);

  //@todo Additional tests.

  //============================================================================

  // Detach the sections.

  for(int i=0; i<lnum_sections; ++i)
  {
    ltensor_0[i].detach_from_state();
    ltensor_1[i].detach_from_state();
    ltensor_r[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

//==============================================================================
// SEC_ED FACET
//==============================================================================

template <typename S>
void
test_sec_ed_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));

  // Body:

  using namespace fiber_bundle::sec_ed_algebra;

  typedef S vector_type;
  typedef sec_at0 scalar_type;

  string section_name = S::static_class_name();

  print_header("Testing sec_ed facet for " + section_name);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int num_sections = 4;

  vector_type lvector[4];
  make_test_sections(xns, xbase_path, "test_ed", "vector", lvector, num_sections);

  scalar_type lscalar[4];
  make_test_sections(xns, xbase_path, "test_ed", "scalar", lscalar, num_sections);

  //============================================================================

  // Execute the tests.

  print_section(lvector[0]);
  print_section(lvector[1]);

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

  //============================================================================

  // Detach the sections.

  for(int i=0; i<num_sections; ++i)
  {
    lvector[i].detach_from_state();
    lscalar[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}


//==============================================================================
// SEC_JCB FACET
//==============================================================================

template <typename SJAC, typename SVECTOR,  typename SCOVECTOR>
void
test_sec_jcb_facet(fiber_bundles_namespace& xns,
                   const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));

  // Body:

  using namespace fiber_bundle::sec_jcb_algebra;

  typedef SJAC jacobian_type;
  typedef SVECTOR vector_type;
  typedef SCOVECTOR covector_type;

  string section_name = SJAC::static_class_name();

  print_header("Testing sec_jcb facet for " + section_name);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int num_sections = 3;

  jacobian_type ljacobian[3];
  make_test_sections(xns, xbase_path, "test_jcb", "jacobian", ljacobian, num_sections);

  vector_type lvector[3];
  make_test_sections(xns, xbase_path, "test_jcb", "vector", lvector, num_sections);

  covector_type lcovector[3];
  make_test_sections(xns, xbase_path, "test_jcb", "covector", lcovector, num_sections);

  //============================================================================

  // Execute the tests.

  print_section(ljacobian[0]);
  print_section(lvector[0]);

  // Test push:

  lvector[0].put_is_covariant(true);
  lcovector[1].put_is_covariant(true);

  push(ljacobian[0], lvector[0], lcovector[1], true);
  print_result("push(ljacobian[0], lvector[0], lcovector[0]):", lcovector[0]);

  // Test pull:

  lcovector[0].put_is_contravariant(true);
  lvector[1].put_is_contravariant(true);

  pull(ljacobian[0], lcovector[0], lvector[1], true);
  print_result("pull(ljacobian[0], lcovector[0], lvector[1]):", lvector[1]);

  //============================================================================

  // Detach the sections.

  for(int i=0; i<num_sections; ++i)
  {
    ljacobian[i].detach_from_state();
    lvector[i].detach_from_state();
    lcovector[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}


//==============================================================================
// SEC_MET FACET
//==============================================================================

template <typename S>
void
test_sec_met_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));

  // Body:

  using namespace fiber_bundle::sec_met_algebra;

  typedef S metric_type;
  typedef typename S::vector_space_type vector_type;

  string section_name = S::static_class_name();

  print_header("Testing sec_met facet for " + section_name);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int num_sections = 3;

  metric_type lmetric[3];
  make_test_sections(xns, xbase_path, "test_met", "metric", lmetric, num_sections);

  vector_type lvector[3];
  make_test_sections(xns, xbase_path, "test_met", "vector", lvector, num_sections);

  //============================================================================

  // Execute the tests.

  print_section(lmetric[0]);
  print_section(lvector[0]);

  // Test lower:

  lmetric[0].put_is_contravariant(true);
  lvector[0].put_is_covariant(true);
  lvector[1].put_is_contravariant(true);

  lower(lmetric[0], lvector[0], lvector[1], true);
  print_result("lower(lmetric[0], lvector[0], lvector[1]):", lvector[1]);

  // Test raise:

  lmetric[0].put_is_covariant(true);
  lvector[0].put_is_contravariant(true);
  lvector[2].put_is_covariant(true);

  raise(lmetric[0], lvector[0], lvector[2], true);
  print_result("raise(lmetric[0], lvector[0], lvector[2]):", lvector[2]);

  //============================================================================

  // Detach the sections.

  for(int i=0; i<num_sections; ++i)
  {
    lmetric[i].detach_from_state();
    lvector[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

//==============================================================================
// SEC_TP FACET
//==============================================================================

template <typename S>
void
test_sec_tp_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));

  // Body:

  using namespace fiber_bundle::sec_tp_algebra;

  typedef S sec_tp_type;
  typedef typename S::vector_space_type sec_vd_type;

  const int lp = S::fiber_type::volatile_type::P;
  typedef typename tensor_section_traits<lp, sec_vd_type>::atp_type sec_atp_type;
  typedef typename tensor_section_traits<lp, sec_vd_type>::stp_type sec_stp_type;

  string section_name = S::static_class_name();

  print_header("Testing sec_tp facet for " + section_name);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int num_sections = 2;

  sec_tp_type lgen_tensor[2];
  make_test_sections(xns, xbase_path, "test_tp", "gen_tensor", lgen_tensor, num_sections);

  sec_atp_type lalt_tensor[2];
  make_test_sections(xns, xbase_path, "test_tp", "alt_tensor", lalt_tensor, num_sections);

  sec_stp_type lsym_tensor[2];
  make_test_sections(xns, xbase_path, "test_tp", "sym_tensor", lsym_tensor, num_sections);

  //============================================================================

  // Execute the tests.

  print_section(lgen_tensor[0]);

  // Test alt (antisymmetric part) function.

  alt(lgen_tensor[0], lalt_tensor[0], true);
  print_result("alt(lgen_tensor[0], lalt_tensor[0]):", lalt_tensor[0]);

  // Test sym (symmetric part) function.

  sym(lgen_tensor[0], lsym_tensor[0], true);
  print_result("sym(lgen_tensor[0], lsym_tensor[0]):", lsym_tensor[0]);

  //@todo Additional tests.

  //============================================================================

  // Detach the sections.

  for(int i=0; i<num_sections; ++i)
  {
    lgen_tensor[i].detach_from_state();
    lalt_tensor[i].detach_from_state();
    lsym_tensor[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

template <typename S0, typename S1, typename SR>
void
test_sec_tensor_product(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(unexecutable("S0, S1, SR are compatible"));

  // Body:

  using namespace fiber_bundle::sec_tp_algebra;

  const string& lname_0 = S0::static_class_name();
  const string& lname_1 = S1::static_class_name();
  const string& lname_r = SR::static_class_name();
  const string lop_string = lname_0 + " (x) " + lname_1 + " = " + lname_r;
  print_header("Testing tensor product for: " + lop_string);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int lnum_sections = 2;

  S0 ltensor_0[2];
  make_test_sections(xns, xbase_path, "test_tensor", "tensor_0", ltensor_0, lnum_sections);

  S1 ltensor_1[2];
  make_test_sections(xns, xbase_path, "test_tensor", "tensor_1", ltensor_1, lnum_sections);

  SR ltensor_r[2];
  make_test_sections(xns, xbase_path, "test_tensor", "tensor_r", ltensor_r, lnum_sections);

  //============================================================================

  // Execute the tests.

  print_section(ltensor_0[0]);
  print_section(ltensor_1[0]);

  tensor(ltensor_0[0], ltensor_1[0], ltensor_r[0], true);
  print_result("tensor(ltensor_0[0], ltensor_1[0], ltensor_r[0]):", ltensor_r[0]);

  //============================================================================

  // Detach the sections.

  for(int i=0; i<lnum_sections; ++i)
  {
    ltensor_0[i].detach_from_state();
    ltensor_1[i].detach_from_state();
    ltensor_r[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

template <typename S0, typename SR>
void
test_sec_contract(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(unexecutable("S0, SR are compatible"));

  // Body:

  using namespace fiber_bundle::sec_tp_algebra;

  const string& lname_0 = S0::static_class_name();
  print_header("Testing contract for: " + lname_0);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int lnum_sections = 2;

  S0 ltensor_0[2];
  make_test_sections(xns, xbase_path, "test_contract", "tensor_0", ltensor_0, lnum_sections);

  SR ltensor_r[2];
  make_test_sections(xns, xbase_path, "test_contract", "tensor_r", ltensor_r, lnum_sections);

  //============================================================================

  // Execute the tests.

  print_section(ltensor_0[0]);

  ltensor_0[0].put_is_contravariant(0, true);
  ltensor_0[0].put_is_covariant(1, true);
  contract(ltensor_0[0], 0, 1, ltensor_r[0], true);
  print_result("contract(ltensor_0[0], 0, 1, ltensor_r[0]):", ltensor_r[0]);

  if(ltensor_0[0].p(true) >= 3)
  {
    ltensor_0[0].put_is_covariant(1, true);
    ltensor_0[0].put_is_contravariant(2, true);
    contract(ltensor_0[0], 1, 2, ltensor_r[1], true);
    print_result("contract(ltensor_0[0], 1, 2, ltensor_r[1]):", ltensor_r[1]);
  }

  //============================================================================

  // Detach the sections.

  for(int i=0; i<lnum_sections; ++i)
  {
    ltensor_0[i].detach_from_state();
    ltensor_r[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

//==============================================================================
// SEC_VD FACET
//==============================================================================

template <typename S>
void
test_sec_vd_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));

  // Body:

  using namespace fiber_bundle::sec_vd_algebra;

  typedef S sec_vd_type;
  string section_name = S::static_class_name();

  print_header("Testing sec_vd facet for " + section_name);

  //============================================================================

  // Create attached sections for testing
  // (also creates the base space, section space, and schema if necessary).

  static const int num_sections = 5;

  sec_vd_type lvector[5];
  make_test_sections(xns, xbase_path, "test_vd", "vector", lvector, num_sections);

  sec_at0 lscalar[5];
  make_test_sections(xns, xbase_path, "test_vd", "scalar", lscalar, num_sections);

  //============================================================================

  // Execute the tests.

  print_section(lvector[0]);
  print_section(lvector[1]);

  // Add: lvector[3] = lvector[0] + lvector[1];

  add(lvector[0], lvector[1], lvector[2], true);
  print_result("add(lvector[0], lvector[1], lvector[2]):", lvector[2]);

  // Test add_equal:

  add_equal(lvector[2], lvector[1], true);
  print_result("add_equal(lvector[2], lvector[1]):", lvector[2]);

  cout << boolalpha;

  cout << "lvector[0].is_covector(true) = " << lvector[0].is_covector(true) << endl;
  cout << "lvector[1].is_covector(true) = " << lvector[0].is_covector(true) << endl;
  cout << "lvector[2].is_covector(true) = " << lvector[0].is_covector(true) << endl;

  cout << "lvector[0].is_vector(true) = " << lvector[0].is_vector(true) << endl;
  cout << "lvector[1].is_vector(true) = " << lvector[0].is_vector(true) << endl;
  cout << "lvector[2].is_vector(true) = " << lvector[0].is_vector(true) << endl;

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

  multiply(lvector[2], lscalar[0], lvector[4], true);
  print_result("multiply(lvector[2], lscalar[0], lvector[4]):", lvector[4]);
  print_section(lvector[2]);
  print_section(lscalar[0]);

  // Test divide:

  divide(lvector[2], 5.0, lvector[4], true);
  print_result("divide(lvector[2], 5, lvector[4]):", lvector[4]);

  // Test divide_equal:

  divide_equal(lvector[4], 5.0, true);
  print_result("divide_equal(lvector[4], 5):", lvector[4]);

  // Test divide:

  divide(lvector[4], lscalar[0], lvector[2], true);
  print_result("divide(lvector[4], lscalar[0], lvector[2]):", lvector[2]);
  print_section(lvector[4]);
  print_section(lscalar[0]);

  //============================================================================

  // Detach the sections.

  for(int i=0; i<num_sections; ++i)
  {
    lvector[i].detach_from_state();
    lscalar[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

//==============================================================================
// OUTPUT FACET
//==============================================================================

template <typename T>
void print_section(const T& xsection, const string& xindent, bool xauto_access)
{
  // Preconditions:

  require(xsection.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    xsection.get_read_access();
  }

  typedef sec_vd::dof_type dof_type;
  typedef typename T::fiber_type::volatile_type volatile_type;

  volatile_type lfiber;

  int ld = lfiber.d();

  T& lsection = const_cast<T&>(xsection);
  size_type ldisc_ct = lsection.schema().discretization_ct();

  cout << xindent << xsection.name() << ":" << endl;;
  for(size_type i=0; i<ldisc_ct; ++i)
  {
    lsection.get_fiber(i, lfiber);
    cout << xindent << setw(5) << i << " : ";

    for(int i=0; i<ld; ++i)
    {
      cout << " " << setw(10) << lfiber.component(i);
    }
    cout << endl;
  }
  cout << endl;

  if(xauto_access)
  {
    xsection.release_access();
  }

  // Postconditions:

  // Exit:
}

template <typename T>
void print_result(const string& xtext,
                  const T& xsection,
                  const string& xindent,
                  bool xauto_access)
{
  // Preconditions:

  require(precondition_of(print_section(xsection, xindent, xauto_access)));

  // Body:

  cout << xtext << endl;
  print_section(xsection, xindent, xauto_access);

  // Postconditions:

  require(postcondition_of(print_section(xsection, xindent, xauto_access)));

  // Exit:
}

//==============================================================================
// SECTION FACET
//==============================================================================

template <typename T>
void make_test_sections(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path,
                        const string& xspace_name,
                        const string& xbase_section_name,
                        T xsections[],
                        int xnum_sections)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member(xbase_path));
  require(unexecutable("xsections dimension is >= num_sections"));

  // Body:

  typedef typename T::host_type host_type;

  // Create a unique name for the section space.

  string lspace_name;
  create_section_space_name(xspace_name, lspace_name);

  // Create the section space

  host_type& lsection_space = T::standard_host(xns, xbase_path, "", lspace_name, "", true);

  // Also, assign values to the section degrees of freedom.
  // Currently these values are not realistic and are the same
  // for each section.  

  ostringstream lname;
  for(int i=0; i<xnum_sections; ++i)
  {
    lname.str("");
    lname << xbase_section_name << "_" << i;

    xsections[i].new_jim_state(&lsection_space);
    xsections[i].get_read_write_access();
    xsections[i].put_name(lname.str(), true, false);
    set_dofs(xsections[i]);
    xsections[i].release_access();
  }

  // Preconditions:

  ensure(unexecutable("for i=0; i<xnum_sections; namespace contains xsections[i]."));
  ensure(unexecutable("!xsections[i].state_read_write_accessible"));

  // Exit:
}

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

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    // Just make up some values for testing.

    for(int n=0; n<ld; ++n)
    {
      lfiber.put_component(n, (1.1)*(i+1+n*ldisc_ct));
    }

    xresult.put_fiber(i, lfiber);
  }
}

//==============================================================================
//==============================================================================

//$$TODO: Clean these functions up.
//$$TODO: Reduce the repeated code by refactoring, etc.

//$$SCRIBBLE: Some classes implement operator<< (eg: sec_e3) which requires
//            "state_is_read_accessible() == true"; so we don't attempt to
//            prine class objects here.

template <typename S>
void
test_section_common_unattached()
{
  // Preconditions:

  // Body:

  //==========================================================================

  cout << boolalpha;

  typedef typename S::fiber_type F;

  //static const string& static_class_name();

  print_subheader("Test static const string& static_class_name()");

  const string& lname = S::static_class_name();
  cout << "  lname = " << lname << endl;

  //==========================================================================

  //S();
  print_subheader("Test default constructor: " + lname + "()");

  S lsection;
  //cout << "  lsection = " << lsection << endl;

  //S(const S& xother);
  print_subheader("Test copy constructor: " + lname
                  + "(const " + lname +"& xother)");

  S lsection_copy(lsection);
  //cout << "  lsection_copy = " << lsection_copy << endl;

  //S& operator=(const S& xother);
  print_subheader("Test assignment operator: " + lname 
                  + "& operator=(const " + lname + "& xother)");
 
  S lsection_assign = lsection;
  // cout << "  lsection_assign = " << lsection_assign << endl;

  //S& operator=(const ed_lite& xother);

  ////ed_lite led_lite;
  ////S& lsection_lite_assign = led_lite;

  //virtual const fiber_type& fiber_prototype() const;
  print_subheader("Test virtual const fiber_type& fiber_prototype() const"); 

  const F& lfiber_type = lsection.fiber_prototype();

  // Can't print because it's not attached.
  //cout << "  lfiber_type = " << lfiber_type << endl;

  //virtual S* clone() const;
  print_subheader("Test virtual " + lname +"* clone() const"); 

  S* lsection_clone = lsection.clone();
  //cout << "  *lsection_clone = " << *lsection_clone << endl;

  // Not attached; so won't work;
  //S* lsection_clone2 = lsection.clone(false, false);

  //virtual const string& class_name() const;
  print_subheader("Test virtual const string& class_name() const"); 

  const string& lclass_name = lsection.class_name();
  cout << "  lclass_name = " << lclass_name << endl;

  //bool fiber_is_ancestor_of(const any* xother) const;
  print_subheader("Test bool fiber_is_ancestor_of(const any* xother) const"); 

  bool lfiber_is_ancestor_of = lsection.fiber_is_ancestor_of(lsection_clone);
  cout << "  lfiber_is_ancestor_of = " << lfiber_is_ancestor_of << endl;

  //bool is_ancestor_of(const any* xother) const;
  print_subheader("Test bool is_ancestor_of(const any* xother) const"); 

  bool lis_ancestor_of = lsection.is_ancestor_of(lsection_clone);
  cout << "  lis_ancestor_of = " << lis_ancestor_of << endl;

  //bool invariant() const;
  print_subheader("Test bool invariant() const"); 

  bool linvariant = lsection.invariant();
  cout << "  linvariant = " << linvariant  << endl;

  // Postconditions:

  // Exit:

  return;

}

template<typename S>
void
test_section_common_attached(fiber_bundles_namespace& xns, int xdim)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(1<=xdim && xdim<=3);

  // Body:

  typedef typename S::fiber_type F;
  typedef typename F::volatile_type V;

  //==========================================================================

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(xdim, xns);

  S lvector[2];
  make_test_sections(xns, lbase_path, "test_common_attached", "vector", lvector, 2);

  lvector[0].get_read_write_access();
  lvector[1].get_read_write_access();

  poset_path lpath0 = lvector[0].path();
  poset_path lpath1 = lvector[1].path();

  scoped_index lindex0 = lvector[0].index();
  scoped_index lindex1 = lvector[1].index();

  print_subheader("Test operator<<");
  cout << lvector[0] << endl;

  //============================================================================

  sec_rep_space* lhost = lvector[0].host();

  //S(const sec_rep_space* xhost, const scoped_index& xindex);

  S lsec2(lhost, lindex0);

  lsec2.detach_from_state();

  //S(const sec_rep_space* xhost, pod_index_type xindex);

  S lsec2a(lhost, lindex0.hub_pod());

  lsec2a.detach_from_state();

  //S(const sec_rep_space* xhost, const string& xname);

  S lsec3(lhost, lpath0.member_name());

  lsec3.detach_from_state();

  //S(const namespace_poset* xnamespace,
  //  const poset_path& xpath,
  //  bool xauto_access = true);

  S lsec0(&xns, lpath0, true);

  lsec0.detach_from_state();

  //explicit S(const sec_rep_space_member* xother);

  S lsec1(&lvector[0]);

  // Don't detach here so we can use it below.
  //lsec1.detach_from_state();

  //S(sec_rep_space* xhost,
  //  section_dof_map* xdof_map = 0,
  //  bool xauto_access = true);

  S lsec4(lhost);

  lsec4.detach_from_state();

  //virtual S& operator=(const abstract_poset_member& xother);

  abstract_poset_member* lapm = &lsec1;
  lsec1 = *lapm;

  //==========================================================================

  //S& operator=(V& xfiber);

  V lfiber_lite;
  lsec1 = lfiber_lite;

  //S& operator=(const F& xfiber);

  typename F::host_type& lfiber_host = F::standard_host(xns, "test_section_common_attached", false);
  lfiber_host.get_read_write_access(true);

  F lfiber(&lfiber_host);
  lsec1 = lfiber;

  lsec1.detach_from_state();
  lfiber.detach_from_state();

  //==========================================================================

  // Cleanup.

  lvector[0].detach_from_state();
  lvector[1].detach_from_state();

  //==========================================================================

  // Postconditions:

  // Exit:

  return;

}

template<typename S>
void
test_section_common_attached_2(fiber_bundles_namespace& xns, int xdim)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(1<=xdim && xdim<=3);

  // Body:

  typedef typename S::fiber_type F;
  typedef typename F::volatile_type V;

  //==========================================================================

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(xdim, xns);

  S lvector[2];
  make_test_sections(xns, lbase_path, "test_common_attached_2", "vector", lvector, 2);

  lvector[0].get_read_write_access();
  lvector[1].get_read_write_access();

  poset_path lpath0 = lvector[0].path();
  poset_path lpath1 = lvector[1].path();

  scoped_index lindex0 = lvector[0].index();
  scoped_index lindex1 = lvector[1].index();

  print_subheader("Test operator<<");
  cout << lvector[0] << endl;

  //============================================================================

  sec_rep_space* lhost = lvector[0].host();

  //S(const sec_rep_space* xhost, const scoped_index& xindex);

  S lsec2(lhost, lindex0);

  lsec2.detach_from_state();

  //S(const sec_rep_space* xhost, pod_index_type xindex);

  S lsec2a(lhost, lindex0.hub_pod());

  lsec2a.detach_from_state();

  //S(const sec_rep_space* xhost, const string& xname);

  S lsec3(lhost, lpath0.member_name());

  lsec3.detach_from_state();

  //S(const namespace_poset* xnamespace,
  //  const poset_path& xpath,
  //  bool xauto_access = true);

  S lsec0(&xns, lpath0, true);

  lsec0.detach_from_state();

//   //explicit S(const sec_rep_space_member* xother);

//   S lsec1(&lvector[0]);

  //S(const sec_rep_space_member& xother);

  S lsec1(lvector[0]);

  // Don't detach here so we can use it below.
  //lsec1.detach_from_state();

  //S(sec_rep_space* xhost,
  //  section_dof_map* xdof_map = 0,
  //  bool xauto_access = true);

  S lsec4(lhost);

  lsec4.detach_from_state();

  //virtual S& operator=(const abstract_poset_member& xother);

  abstract_poset_member* lapm = &lsec1;
  lsec1 = *lapm;

  //==========================================================================

  //S& operator=(V& xfiber);

  V lfiber_lite;
  lsec1 = lfiber_lite;

  //S& operator=(const F& xfiber);

  typename F::host_type& lfiber_host = F::standard_host(xns, "test_section_common_attached_2", false);
  lfiber_host.get_read_write_access(true);

  F lfiber(&lfiber_host);
  lsec1 = lfiber;

  lsec1.detach_from_state();
  lfiber.detach_from_state();

  //==========================================================================

  // Cleanup.

  lvector[0].detach_from_state();
  lvector[1].detach_from_state();

  //==========================================================================

  // Postconditions:

  // Exit:

  return;

}

//$$SCRIBBLE: Cleanup and comment.

template<typename SB, typename SD>
void
test_section_common_attached(fiber_bundles_namespace& xns, int xdim)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(1<=xdim && xdim<=3);

  // Body:

  typedef typename SD::fiber_type F;
  typedef typename F::volatile_type V;

  //==========================================================================

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(xdim, xns);

  SD lvector[2];
  make_test_sections(xns, lbase_path, "test_common_attached", "vector", lvector, 2);

  lvector[0].get_read_write_access();
  lvector[1].get_read_write_access();

  poset_path lpath0 = lvector[0].path();
  poset_path lpath1 = lvector[1].path();

  scoped_index lindex0 = lvector[0].index();
  scoped_index lindex1 = lvector[1].index();

  sec_rep_space* lhost = lvector[0].host();

  //SB(const sec_rep_space* xhost, const scoped_index& xindex);

  SB lsec2(lhost, lindex0);

  lsec2.detach_from_state();

  //S(const sec_rep_space* xhost, pod_index_type xindex);

  SB lsec2a(lhost, lindex0.hub_pod());

  lsec2a.detach_from_state();

  //SB(const sec_rep_space* xhost, const string& xname);

  SB lsec3(lhost, lpath0.member_name());

  lsec3.detach_from_state();

  //SB(const namespace_poset* xnamespace,
  //     const poset_path& xpath,
  //     bool xauto_access = true);

  SB lsec0(&xns, lpath0, true);

  lsec0.detach_from_state();

  //explicit SB(const sec_rep_space_member* xother);

  SB lsec1(&lvector[0]);

  // Don't detach here so we can use it below.
  //lsec1.detach_from_state();

  //SB(sec_rep_space* xhost,
  //   section_dof_map* xdof_map = 0,
  //   bool xauto_access = true);

  SB lsec4(lhost);

  lsec4.detach_from_state();

  //virtual SB& operator=(const abstract_poset_member& xother);

  abstract_poset_member* lapm = &lsec1;
  lsec1 = *lapm;

  //==========================================================================

  //SB& operator=(V& xfiber);

  V lfiber_lite;
  lsec1 = lfiber_lite;

  //SB& operator=(const F& xfiber);

  typename F::host_type& lfiber_host = F::standard_host(xns, "test_section_common_attached", false);
  lfiber_host.get_read_write_access(true);

  F lfiber(&lfiber_host);
  lsec1 = lfiber;

  lsec1.detach_from_state();
  lfiber.detach_from_state();

  //==========================================================================

  //SB& operator=(const SB& xother)

  SB lbase = lvector[0];
  lbase = lvector[1];

  lbase.detach_from_state();

  //==========================================================================

  //inline SB* clone(bool xnew_state, bool xauto_access = true) const

  SB* lclone = lvector[0].clone(false, true);

  //==========================================================================

  // Cleanup.

  lvector[0].detach_from_state();
  lvector[1].detach_from_state();

  //==========================================================================

  // Postconditions:

  // Exit:

  return;

}

////////////////////////////////////////////////////////////////////////////////

template<typename S>
void
test_section_common_attached_2(fiber_bundles_namespace& xns,
                               poset_path xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!(xbase_path.empty()));
  require(xns.contains_member(xbase_path.poset_name()));

  // Body:

  typedef typename S::fiber_type F;
  typedef typename F::volatile_type V;

  //==========================================================================

  // Make a base space.

  //const poset_path& lbase_path = make_test_base_space(xdim, xns);

  S lvector[2];
  make_test_sections(xns, xbase_path, "test_common_attached_2", "vector", lvector, 2);

  lvector[0].get_read_write_access();
  lvector[1].get_read_write_access();

  poset_path lpath0 = lvector[0].path();
  poset_path lpath1 = lvector[1].path();

  scoped_index lindex0 = lvector[0].index();
  scoped_index lindex1 = lvector[1].index();

  print_subheader("Test operator<<");
  cout << lvector[0] << endl;

  //============================================================================

  sec_rep_space* lhost = lvector[0].host();

  //S(const sec_rep_space* xhost, const scoped_index& xindex);

  S lsec2(lhost, lindex0);

  lsec2.detach_from_state();

  //S(const sec_rep_space* xhost, pod_index_type xindex);

  S lsec2a(lhost, lindex0.hub_pod());

  lsec2a.detach_from_state();

  //S(const sec_rep_space* xhost, const string& xname);

  S lsec3(lhost, lpath0.member_name());

  lsec3.detach_from_state();

  //S(const namespace_poset* xnamespace,
  //  const poset_path& xpath,
  //  bool xauto_access = true);

  S lsec0(&xns, lpath0, true);

  lsec0.detach_from_state();

//   //explicit S(const sec_rep_space_member* xother);

//   S lsec1(&lvector[0]);

  //S(const sec_rep_space_member& xother);

  S lsec1(lvector[0]);

  // Don't detach here so we can use it below.
  //lsec1.detach_from_state();

  //S(sec_rep_space* xhost,
  //  section_dof_map* xdof_map = 0,
  //  bool xauto_access = true);

  S lsec4(lhost);

  lsec4.detach_from_state();

  //virtual S& operator=(const abstract_poset_member& xother);

  abstract_poset_member* lapm = &lsec1;
  lsec1 = *lapm;

  //==========================================================================

  //S& operator=(V& xfiber);

  V lfiber_lite;
  lsec1 = lfiber_lite;

  //S& operator=(const F& xfiber);

  typename F::host_type& lfiber_host = F::standard_host(xns, "test_section_common_attached_2", false);
  lfiber_host.get_read_write_access(true);

  F lfiber(&lfiber_host);
  lsec1 = lfiber;

  lsec1.detach_from_state();
  lfiber.detach_from_state();

  //==========================================================================

  // Cleanup.

  lvector[0].detach_from_state();
  lvector[1].detach_from_state();

  //==========================================================================

  // Postconditions:

  // Exit:

  return;

}

template<typename S>
void
test_section_common_attached(fiber_bundles_namespace& xns,
                             poset_path xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!(xbase_path.empty()));
  require(xns.contains_member(xbase_path.poset_name()));

  // Body:

  typedef typename S::fiber_type F;
  typedef typename F::volatile_type V;

  //==========================================================================

  S lvector[2];
  make_test_sections(xns, xbase_path, "test_common_attached", "vector", lvector, 2);

  lvector[0].get_read_write_access();
  lvector[1].get_read_write_access();

  poset_path lpath0 = lvector[0].path();
  poset_path lpath1 = lvector[1].path();

  scoped_index lindex0 = lvector[0].index();
  scoped_index lindex1 = lvector[1].index();

  print_subheader("Test operator<<");
  cout << lvector[0] << endl;

  //============================================================================

  sec_rep_space* lhost = lvector[0].host();

  //S(const sec_rep_space* xhost, const scoped_index& xindex);

  S lsec2(lhost, lindex0);

  lsec2.detach_from_state();

  //S(const sec_rep_space* xhost, pod_index_type xindex);

  S lsec2a(lhost, lindex0.hub_pod());

  lsec2a.detach_from_state();

  //S(const sec_rep_space* xhost, const string& xname);

  S lsec3(lhost, lpath0.member_name());

  lsec3.detach_from_state();

  //S(const namespace_poset* xnamespace,
  //  const poset_path& xpath,
  //  bool xauto_access = true);

  S lsec0(&xns, lpath0, true);

  lsec0.detach_from_state();

  //explicit S(const sec_rep_space_member* xother);

  S lsec1(&lvector[0]);

  // Don't detach here so we can use it below.
  //lsec1.detach_from_state();

  //S(sec_rep_space* xhost,
  //  section_dof_map* xdof_map = 0,
  //  bool xauto_access = true);

  S lsec4(lhost);

  lsec4.detach_from_state();

  //virtual S& operator=(const abstract_poset_member& xother);

  abstract_poset_member* lapm = &lsec1;
  lsec1 = *lapm;

  //==========================================================================

  //S& operator=(V& xfiber);

  V lfiber_lite;
  lsec1 = lfiber_lite;

  //S& operator=(const F& xfiber);

  typename F::host_type& lfiber_host = F::standard_host(xns, "test_section_common_attached", false);
  lfiber_host.get_read_write_access(true);

  F lfiber(&lfiber_host);
  lsec1 = lfiber;

  lsec1.detach_from_state();
  lfiber.detach_from_state();

  //==========================================================================

  // Cleanup.

  lvector[0].detach_from_state();
  lvector[1].detach_from_state();

  //==========================================================================

  // Postconditions:

  // Exit:

  return;

}

} // namespace fiber_bundle

#endif // ifndef TEST_SECTIONS_IMPL_H
