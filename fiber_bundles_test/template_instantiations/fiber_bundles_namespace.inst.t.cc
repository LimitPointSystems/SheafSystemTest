// $RCSfile: fiber_bundles_namespace.inst.t.cc,v $ $Revision: 1.1.2.5 $ $Date: 2012/11/05 23:28:35 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example template_instantiations/fiber_bundles_namespace.inst.t.cc
/// Unit test driver for class fiber_bundles_namespace template functions.

#include "std_stdexcept.h"

#include "fiber_bundles_namespace.h"

#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "at2_e2.h"
#include "at2_e3.h"
#include "at2.h"
#include "at3_e3.h"
#include "at3.h"
#include "atp.h"
#include "atp_space.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "e4.h"
#include "ed.h"
#include "gl2.h"
#include "gl3.h"
#include "gln.h"
#include "gln_space.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"
#include "jcb_ed.h"
#include "jcb.h"
#include "jcb_space.h"
#include "met_e1.h"
#include "met_e2.h"
#include "met_e3.h"
#include "met_ed.h"
#include "met.h"
#include "st2_e2.h"
#include "st2_e3.h"
#include "st2.h"
#include "st3_e3.h"
#include "st3.h"
#include "st4_e2.h"
#include "st4_e3.h"
#include "st4.h"
#include "stp.h"
#include "stp_space.h"
#include "t2_e2.h"
#include "t2_e3.h"
#include "t2.h"
#include "t3_e3.h"
#include "t3.h"
#include "t4_e2.h"
#include "t4_e3.h"
#include "t4.h"
#include "tp.h"
#include "tp_space.h"
#include "tuple.h"
#include "tuple_space.h"
#include "vd.h"
#include "vd_space.h"

#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_at2_e2.h"
#include "sec_at2_e3.h"
#include "sec_at2.h"
#include "sec_at3_e3.h"
#include "sec_at3.h"
#include "sec_atp.h"
#include "sec_atp_space.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_e4.h"
#include "sec_ed.h"

#include "sec_jcb_e13.h"
#include "sec_jcb_e23.h"
#include "sec_jcb_e33.h"
#include "sec_jcb_ed.h"
#include "sec_jcb.h"
#include "sec_jcb_space.h"
#include "sec_met_e1.h"
#include "sec_met_e2.h"
#include "sec_met_e3.h"
#include "sec_met_ed.h"
#include "sec_met.h"
#include "sec_st2_e2.h"
#include "sec_st2_e3.h"
#include "sec_st2.h"
#include "sec_st3_e3.h"
#include "sec_st3.h"
#include "sec_st4_e2.h"
#include "sec_st4_e3.h"
#include "sec_st4.h"
#include "sec_stp.h"
#include "sec_stp_space.h"
#include "sec_t2_e2.h"
#include "sec_t2_e3.h"
#include "sec_t2.h"
#include "sec_t3_e3.h"
#include "sec_t3.h"
#include "sec_t4_e2.h"
#include "sec_t4_e3.h"
#include "sec_t4.h"
#include "sec_tp.h"
#include "sec_tp_space.h"
#include "sec_tuple.h"
#include "sec_tuple_space.h"
#include "sec_vd.h"
#include "sec_vd_space.h"


// #include "at0.h"
// #include "at0_space.h"
// #include "at1_space.h"
// #include "at2_e2.h"
// #include "atp_space.h"
// #include "e2.h"
// #include "gl2.h"
// #include "gl3.h"
// #include "gln_space.h"
// #include "jcb_e13.h"
// #include "jcb_space.h"
// #include "st2_e2.h"
// #include "stp_space.h"
// #include "t2_e2.h"
// #include "tp_space.h"
// #include "tuple_space.h"
// #include "vd_space.h"
// #include "vd.h"

// #include "sec_at0.h"
// #include "sec_at2_e2.h"
// #include "sec_e2.h"
// #include "sec_jcb_e13.h"
// #include "sec_st2_e2.h"
// #include "sec_t2_e2.h"
// #include "sec_tp.h"
// #include "sec_tuple.h"
// #include "sec_vd.h"

// #include "sec_at0_space.h"
// #include "sec_at1_space.h"
// #include "sec_atp_space.h"
// #include "sec_jcb_space.h"
// #include "sec_rep_space.h"
// #include "sec_stp_space.h"
// #include "sec_tp_space.h"
// #include "sec_tuple_space.h"
// #include "sec_vd_space.h"

#include "base_space_poset.h"
#include "structured_block_1d.h"

#include "binary_section_space_schema_poset.h"
#include "section_space_schema_poset.h"
#include "sec_rep_descriptor_poset.h"

#include "scoped_index.h"

#include "test_utils.h"

#include "test_sections.impl.h"

#include "arg_list.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "wsv_block.h"

#include "structured_block_1d.h"
#include "structured_block_2d.h"

#include "sec_e1_uniform.h"
#include "sec_e2_uniform.h"
#include "sec_e3_uniform.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_e4.h"
#include "sec_ed.h"
#include "sec_t2.h"
#include "sec_t3.h"
#include "sec_t4.h"
#include "sec_tp.h"
#include "sec_vd.h"
#include "sec_at0.h"
#include "sec_at1.h"
#include "sec_at2.h"
#include "sec_at3.h"
#include "sec_atp.h"
#include "sec_met.h"
#include "sec_st2.h"
#include "sec_st3.h"
#include "sec_st4.h"
#include "sec_stp.h"
#include "sec_st2_e2.h"
#include "sec_st2_e3.h"
#include "sec_st3_e3.h"
#include "sec_st4_e2.h"
#include "sec_st4_e3.h"
#include "sec_t2_e2.h"
#include "sec_t2_e3.h"
#include "sec_t3_e3.h"
#include "sec_t4_e2.h"
#include "sec_t4_e3.h"
#include "sec_tuple.h"

#include "sec_met.h"
#include "sec_met_e1.h"
#include "sec_met_e2.h"
#include "sec_met_e3.h"
#include "sec_met_ed.h"

using namespace fiber_bundle;

namespace
{

//============================================================================
// NAMESPACE_POSET FACET
//============================================================================

template<typename S>
bool
test_fiber_bundles_namespace_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  bool lresult = true;

  bool ltest;

  print_subheader("Testing completed_schema_path(const poset_path&)");

  poset_path lpath("dummy");
  cout << "lpath  = " << lpath << endl;   

  const poset_path& lpath0 = xns.completed_schema_path<S>(lpath);
  cout << "lpath0 = " << lpath0 << endl; 

  ltest = xns.completed_schema_path_conforms_to<S>(lpath0, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  ltest = xns.args_conform_to_completed_schema_path<S>(arg_list(""), lpath0, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  const poset_path& lpath1 = xns.completed_space_path<S>(lpath);
  cout << "lpath1 = " << lpath1 << endl;

  ltest = xns.completed_space_path_is_available<S>(lpath1, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  //$$SCRIBBLE: at2 and above.
  //int lint0 = xns.completed_p<S>(lpath1, arg_list(""), true);
  //cout << "lint0 = " << lint0 << endl;      


  // Postconditions:

  // Exit:

  return lresult;
}

template<typename S>
bool
test_fiber_bundles_namespace_facet2(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  bool lresult = true;

  bool ltest;

  //print_subheader("Testing completed_schema_path(const poset_path&)");
  print_subheader("=================================================");

  poset_path lpath("dummy");
  cout << "lpath  = " << lpath << endl;   

  //const poset_path& lpath0 = xns.completed_schema_path<S>(lpath);
  //cout << "lpath0 = " << lpath0 << endl; 

  //ltest = xns.completed_schema_path_conforms_to<S>(lpath0, true);
  //cout << "ltest = " << boolalpha << ltest << endl;

  //ltest = xns.args_conform_to_completed_schema_path<S>(arg_list(""), lpath0, true);
  //cout << "ltest = " << boolalpha << ltest << endl;

  const poset_path& lpath1 = xns.completed_space_path<S>(lpath);
  cout << "lpath1 = " << lpath1 << endl;

  ltest = xns.completed_space_path_is_available<S>(lpath1, true);
  cout << "ltest = " << boolalpha << ltest << endl;

  //$$SCRIBBLE: at2 and above.
  //int lint0 = xns.completed_p<S>(lpath1, arg_list(""), true);
  //cout << "lint0 = " << lint0 << endl;      


  // Postconditions:

  // Exit:

  return lresult;
}


//============================================================================
//============================================================================

template<typename T>
void test(fiber_bundles_namespace& xns, const poset_path& lbase_path)
{

  const poset_path lpath = "test_space_" + T::static_class_name();
//   const poset_path
//      lrep_path(fiber_bundles_namespace::standard_sec_rep_descriptor_poset_name(),
//                "element_element_constant");


  sec_rep_space* lhost = &xns.new_section_space<T>(lpath.poset_name(),
                                                   lbase_path);
    //lrep_path,
    //true);

  const poset_path lpath2 = "test_space_2_" + T::static_class_name();
  sec_rep_space* lhost2 = &xns.new_section_space<T>(lpath2.poset_name(), arg_list(""), "", true);
  //sec_rep_space* lhost2 = &xns.new_section_space<T>(lpath.poset_name(), arg_list(""), "", true);
  //sec_rep_space* lhost2 = &xns.new_section_space<T>("", arg_list(""));

  return;
}

  //////////////////////////////////////////////////////////////////////////////

  poset_path make_base_space(fiber_bundles_namespace& xns)
  {
    xns.get_read_write_access();
    
    base_space_poset* lhost = &xns.new_base_space<structured_block_1d>("base_space_host");
    structured_block_1d lmesh(lhost, 2, true);
    lmesh.put_name("base_space", true, true);

    poset_path result = lmesh.path(true);
    
    lmesh.detach_from_state();
    // xns.release_access();
    
    return result;
  }

  poset_path make_vector_fiber_space_schema(fiber_bundles_namespace& xns)
  {

    // Make a at1 space schema

    string lmember_names = "x DOUBLE false y DOUBLE false";

    schema_poset_member lschema(xns,
				"shallow_instantiation_test_at1_space_schema",
				at1_space::standard_schema_path(),
				lmember_names,
				true,
				true);

    poset_path result = lschema.path();

    lschema.detach_from_state();

    return result;
  }

  poset_path make_tensor_fiber_space_schema(fiber_bundles_namespace& xns)
  {

    // Make a tensor space schema; copied from at2_e2::make_standard_schema().

    string ltensor_dof_specs = "xy DOUBLE false";


    schema_poset_member ltensor_schema(xns,
				       "atp_space_test_schema",
				       atp_space::standard_schema_path(),
				       ltensor_dof_specs,
				       true,
				       true);

    poset_path result = ltensor_schema.path();
    ltensor_schema.detach_from_state();

    return result;
  }
  

  void test_deep_instantiation(fiber_bundles_namespace& xns, 
			       const poset_path& xbase_space_path,
			       const poset_path& xvector_fiber_space_schema_path,
			       const poset_path& xtensor_fiber_space_schema_path)
  {
    typedef binary_section_space_schema_poset host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = host_type::make_arg_list("", xbase_space_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<sec_at0>("deep_instantiation_test_sec_at0_schema",
						   lsss_args);

    // Make the vector section space schema.

    poset_path lvector_schema_path =
      xns.new_vector_section_space_schema<sec_at1>("deep_instantiation_test_sec_at1_schema", 
						   lsss_args,
						   "", // xsection_space_schema__schema_path
						   "", // xrep_path
						   "", // xbase_space_path
						   "", // xfiber_space_path
						   "", // xfiber_space_args
						   xvector_fiber_space_schema_path);

    // Make the tensor section space schema.

    arg_list lfiber_args = atp_space::make_arg_list(2, "");
    
    poset_path ltensor_schema_path =
      xns.new_tensor_section_space_schema<sec_atp>("deep_instantiation_test_sec_atp_schema", 
						   lsss_args,
						   "", // xsection_space_schema_schema_path
						   "", // xrep_path
						   "", // xbase_space_path
						   "", // xfiber_space_path
						   lfiber_args, // xfiber_space_args
						   xtensor_fiber_space_schema_path, // xfiber_space_schema_path
						   "", // xvector_space_path
						   "", // xvector_space_args
						   xvector_fiber_space_schema_path
						   );

    // Make the section space.

    arg_list ltensor_args = sec_atp_space::make_arg_list(2, "");

    sec_atp_space& lsection_space =
      xns.new_tensor_section_space<sec_at2>("deep_instantiation_test_sec_atp_space",
					    ltensor_args,
					    ltensor_schema_path,
					    "deep_instantiation_test_sec_at1_space",
					    "", // xvector_space_args
					    lvector_schema_path,
					    "deep_instantiation_test_sec_at0_space",
					    "", // xscalar_space_args
					    lscalar_schema_path);

    cout << lsection_space << endl;
  }
  

  //////////////////////////////////////////////////////////////////////////////
  /*
  poset_path make_vector_space_schema(fiber_bundles_namespace& xns)
  {
    // Make a vector space schema; copied from e2::make_standard_schema().

    string ldof_specs = "x DOUBLE false y DOUBLE false";

    schema_poset_member lvector_schema(xns,
				       "shallow_instantiation_test_vd_space_schema",
				       at1_space::standard_schema_path(),
				       ldof_specs,
				       true,
				       true);

    poset_path result = lvector_schema.path();
    lvector_schema.detach_from_state();

    return result;
  }

  poset_path make_tensor_space_schema(fiber_bundles_namespace& xns)
  {

    // Make a tensor space schema; copied from at2_e2::make_standard_schema().

    string lmember_names = "xy DOUBLE false";

    schema_poset_member ltensor_schema(xns,
				       "atp_space_test_schema",
				       atp_space::standard_schema_path(),
				       lmember_names,
				       true,
				       true);

    poset_path result = ltensor_schema.path();
    ltensor_schema.detach_from_state();

    return result;
  }


template<typename T>
bool
test_fiber_bundles_namespace_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string lname = T::static_class_name() + "_space";

  print_header("Begin testing " + lname);

  bool lresult = true;

  typedef typename T::host_type S;

  S& lspace = xns.new_fiber_space<T>(lname);

  //lresult &= test_common(xns, lspace);

  //============================================================================

  ///
  /// True if and only if xargs are empty or if xargs conforms to
  /// completed_schema_path<S>(xpath).
  ///
//   template <typename S>
//   bool args_conform_to_completed_schema_path(const arg_list& xargs, 
// 					     const poset_path& xpath, 
// 					     bool xauto_access) const;

  bool ltest =
    xns.args_conform_to_completed_schema_path<T>(arg_list(""), poset_path(), true);

  cout << "ltest = " << boolalpha << ltest << endl;

  //============================================================================

  print_footer("End testing " + lname);

  // Postconditions:

  // Exit:

  return lresult;
}
  */


} // namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  print_header("Begin testing fiber_bundles_namespace instantiations.");

  try {

//   ltest &= test_fiber_bundles_namespace_facet<at0>(lns);
//   ltest &= test_fiber_bundles_namespace_facet<at2_e2>(lns);
//   ltest &= test_fiber_bundles_namespace_facet<e2>(lns);
//   ltest &= test_fiber_bundles_namespace_facet<gl2>(lns);
//   ltest &= test_fiber_bundles_namespace_facet<jcb_e13>(lns);
//   ltest &= test_fiber_bundles_namespace_facet<st2_e2>(lns);
//   ltest &= test_fiber_bundles_namespace_facet<t2_e2>(lns);
//   ltest &= test_fiber_bundles_namespace_facet<tuple>(lns);
//   ltest &= test_fiber_bundles_namespace_facet<vd>(lns);

  //============================================================================

  //fiber_bundle::at2::host_type& fiber_bundle::fiber_bundles_namespace::new_fiber_space<fiber_bundle::at2>
  //     (sheaf::poset_path const&, sheaf::arg_list const&, sheaf::poset_path const&, bool)

  //typename at2::host_type& lhost = lns.new_fiber_space<at2>();
//   atp_space& lhost = lns.new_fiber_space<at2>();
// //                      const poset_path& xfiber_space_path = "",
// // 					 const arg_list& xfiber_space_args = "",
// // 					 const poset_path& xfiber_space_schema_path = "",
// // 					 bool xauto_access = true

//   cout << &lhost << endl;


  //typename at2::host_type& lhost = lns.new_tensor_space<at2>();

  //fiber_bundle::at2::host_type& fiber_bundle::fiber_bundles_namespace::new_tensor_space<fiber_bundle::at2>
  //    (sheaf::poset_path const&,
  //     sheaf::arg_list const&, sheaf::poset_path const&, sheaf::poset_path const&,
  //     sheaf::arg_list const&, sheaf::poset_path const&, sheaf::poset_path const&, sheaf::arg_list const&,
  //     sheaf::poset_path const&, bool)


 //    poset_path lvector_schema_path = make_vector_space_schema(lns);
//     poset_path ltensor_schema_path = make_tensor_space_schema(lns);

//     poset_path lpath("deep_instantiation_test_tp_space", "");
//     arg_list ltensor_args = atp_space::make_arg_list(2, "");


//     atp_space& lspace = lns.new_tensor_space<atp>(lpath, 
// 						ltensor_args, 
// 						ltensor_schema_path,
// 						"",
// 						"",
// 						lvector_schema_path);
    
    
//     cout << lspace << endl;

  //============================================================================
  /*
  // Make a base space.

  poset_path lbase_space_path = make_base_space(lns);

  // Make a schema for a concrete at1 space.

  poset_path lvector_space_schema_path = make_vector_fiber_space_schema(lns);

  // Make a schema for a concrete atp space.

  poset_path ltensor_space_schema_path = make_tensor_fiber_space_schema(lns);

  // Test shallow instantiation

  //test_shallow_instantiation(lns, lbase_space_path, lvector_space_schema_path, ltensor_space_schema_path);

  // Test deep instantiation

  test_deep_instantiation(lns, lbase_space_path, lvector_space_schema_path, ltensor_space_schema_path);
  */

  //============================================================================

  /*
 
  // Make a scalar space, use standard schema.

  arg_list lscalar_args = at0_space::make_arg_list();
  poset_path lscalar_schema_path = at0_space::standard_schema_path();
  at0_space* lscalar_space = new at0_space(lns, 
					   "at0_space_test", 
					   lscalar_args,
					   lscalar_schema_path,
					   true);

  poset_path lscalar_path = lscalar_space->path();

  //cout << *lscalar_space << endl;  

  // Make a vector space schema; copied from e2::make_standard_schema().

  string lvector_dof_specs = "x DOUBLE false y DOUBLE false";

  schema_poset_member lvector_schema(lns,
                              "vd_space_test_schema",
                              vd_space::standard_schema_path(),
                              lvector_dof_specs,
                              true,
                              true);

  poset_path lvector_schema_path = lvector_schema.path();
  lvector_schema.detach_from_state();

  arg_list lvector_args = vd_space::make_arg_list(lscalar_path);
  
  vd_space* lvector_space = new vd_space(lns, 
					 "vd_space_test", 
					 lvector_args, 
					 lvector_schema_path, 
					 true);
  
  poset_path lvector_path = lvector_space->path();

  // Make a tensor space schema; copied from t2_e2::make_standard_schema().

  string ltensor_dof_specs = "xx DOUBLE false ";
  ltensor_dof_specs       += "xy DOUBLE false ";
  ltensor_dof_specs       += "yx DOUBLE false ";
  ltensor_dof_specs       += "yy DOUBLE false";


  schema_poset_member ltensor_schema(lns,
                              "atp_space_test_schema",
                              atp_space::standard_schema_path(),
                              ltensor_dof_specs,
                              true,
                              true);

  poset_path ltensor_schema_path = ltensor_schema.path();
  ltensor_schema.detach_from_state();

  arg_list ltensor_args = atp_space::make_arg_list(2, lvector_path);
  
  vd_space* ltensor_space = new tp_space(lns, 
					 "atp_space_test", 
					 ltensor_args, 
					 ltensor_schema_path, 
					 true);

  cout << *ltensor_space << endl;

  poset_path lfiber_space_path("atp_space_test2");
  
  atp::host_type& lspace = lns.new_fiber_space<atp>(lfiber_space_path, ltensor_args, ltensor_schema_path, true);
  
  cout << lspace << endl;

  */
  //============================================================================
  /*
  const poset_path& lbase_path = make_base_space(lns); 

  cout << "sec_at0" << endl;
  test<sec_at0>(lns, lbase_path);

  //cout << "sec_at1" << endl;
  //test<sec_at1>(lns, lbase_path);

  //cout << "sec_at2" << endl;
  //test<sec_at2>(lns, lbase_path);

  cout << "sec_at2_e2" << endl;
  test<sec_at2_e2>(lns, lbase_path);

  cout << "sec_at2_e3" << endl;
  test<sec_at2_e3>(lns, lbase_path);

  //cout << "sec_at3" << endl;
  //test<sec_at3>(lns, lbase_path);

  cout << "sec_at3_e3" << endl;
  test<sec_at3_e3>(lns, lbase_path);

  cout << "sec_e1" << endl;
  test<sec_e1>(lns, lbase_path);

  cout << "sec_e2" << endl;
  test<sec_e2>(lns, lbase_path);

  cout << "sec_e3" << endl;
  test<sec_e3>(lns, lbase_path);

  cout << "sec_e4" << endl;
  test<sec_e4>(lns, lbase_path);

  //cout << "sec_ed" << endl;
  //test<sec_ed>(lns, lbase_path);

  //cout << "sec_st2" << endl;
  //test<sec_st2>(lns, lbase_path);

  cout << "sec_st2_e2" << endl;
  test<sec_st2_e2>(lns, lbase_path);

  cout << "sec_st2_e3" << endl;
  test<sec_st2_e3>(lns, lbase_path);

  //cout << "sec_st3" << endl;
  //test<sec_st3>(lns, lbase_path);

  cout << "sec_st3_e3" << endl;
  test<sec_st3_e3>(lns, lbase_path);

  //cout << "sec_st4" << endl;
  //test<sec_st4>(lns, lbase_path);

  cout << "sec_st4_e2" << endl;
  test<sec_st4_e2>(lns, lbase_path);

  cout << "sec_st4_e3" << endl;
  test<sec_st4_e3>(lns, lbase_path);

  //cout << "sec_stp" << endl;
  //test<sec_stp>(lns, lbase_path);

  //cout << "sec_t2" << endl;
  //test<sec_t2>(lns, lbase_path);

  cout << "sec_t2_e2" << endl;
  test<sec_t2_e2>(lns, lbase_path);

  cout << "sec_t2_e3" << endl;
  test<sec_t2_e3>(lns, lbase_path);

  //cout << "sec_t3" << endl;
  //test<sec_t3>(lns, lbase_path);

  cout << "sec_t3_e3" << endl;
  test<sec_t3_e3>(lns, lbase_path);

  //cout << "sec_t4" << endl;
  //test<sec_t4>(lns, lbase_path);

  cout << "sec_t4_e2" << endl;
  test<sec_t4_e2>(lns, lbase_path);

  cout << "sec_t4_e3" << endl;
  test<sec_t4_e3>(lns, lbase_path);

  //cout << "sec_tp" << endl;
  //test<sec_tp>(lns, lbase_path);

  //cout << "sec_met" << endl;
  //test<sec_met>(lns, lbase_path);


  cout << "sec_met_e1" << endl;
  test<sec_met_e1>(lns, lbase_path);

  cout << "sec_met_e2" << endl;
  test<sec_met_e1>(lns, lbase_path);

  cout << "sec_met_e3" << endl;
  test<sec_met_e1>(lns, lbase_path);

  //cout << "sec_met_ed" << endl;
  //test<sec_met_e1>(lns, lbase_path);
  */

  //============================================================================
  /*
  ltest &= test_fiber_bundles_namespace_facet<at0>(lns);
  ltest &= test_fiber_bundles_namespace_facet<at1>(lns);
  ltest &= test_fiber_bundles_namespace_facet<at2_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<at2_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<at2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<at3_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<at3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<atp>(lns);
  ltest &= test_fiber_bundles_namespace_facet<e1>(lns);
  ltest &= test_fiber_bundles_namespace_facet<e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<e4>(lns);
  ltest &= test_fiber_bundles_namespace_facet<ed>(lns);
  ltest &= test_fiber_bundles_namespace_facet<gl2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<gl3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<gln>(lns);
  ////ltest &= test_fiber_bundles_namespace_facet<group>(lns);
  ltest &= test_fiber_bundles_namespace_facet<jcb_e13>(lns);
  ltest &= test_fiber_bundles_namespace_facet<jcb_e23>(lns);
  ltest &= test_fiber_bundles_namespace_facet<jcb_e33>(lns);
  ltest &= test_fiber_bundles_namespace_facet<jcb_ed>(lns);
  ltest &= test_fiber_bundles_namespace_facet<jcb>(lns);
  ltest &= test_fiber_bundles_namespace_facet<met_e1>(lns);
  ltest &= test_fiber_bundles_namespace_facet<met_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<met_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<met_ed>(lns);
  ltest &= test_fiber_bundles_namespace_facet<met>(lns);
  ltest &= test_fiber_bundles_namespace_facet<st2_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<st2_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<st2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<st3_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<st3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<st4_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<st4_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<st4>(lns);
  ltest &= test_fiber_bundles_namespace_facet<stp>(lns);
  ltest &= test_fiber_bundles_namespace_facet<t2_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<t2_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<t2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<t3_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<t3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<t4_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet<t4_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet<t4>(lns);
  ltest &= test_fiber_bundles_namespace_facet<tp>(lns);
  ltest &= test_fiber_bundles_namespace_facet<tuple>(lns);
  ltest &= test_fiber_bundles_namespace_facet<vd>(lns);


  //============================================================================

  ltest &= test_fiber_bundles_namespace_facet2<sec_at2_e2>(lns);

  ltest &= test_fiber_bundles_namespace_facet2<sec_at0>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_at1>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_at2_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_at2_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_at2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_at3_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_at3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_atp>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_e1>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_e4>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_ed>(lns);
  //  ltest &= test_fiber_bundles_namespace_facet2<sec_gl2>(lns);
  //  ltest &= test_fiber_bundles_namespace_facet2<sec_gl3>(lns);
  //  ltest &= test_fiber_bundles_namespace_facet2<sec_gln>(lns);
  //  ltest &= test_fiber_bundles_namespace_facet2<sec_jcb_e13>(lns);
  //  ltest &= test_fiber_bundles_namespace_facet2<sec_jcb_e23>(lns);
  //  ltest &= test_fiber_bundles_namespace_facet2<sec_jcb_e33>(lns);
  //  ltest &= test_fiber_bundles_namespace_facet2<sec_jcb_ed>(lns);
  //  ltest &= test_fiber_bundles_namespace_facet2<sec_jcb>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_met_e1>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_met_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_met_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_met_ed>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_met>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_st2_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_st2_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_st2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_st3_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_st3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_st4_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_st4_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_st4>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_stp>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_t2_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_t2_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_t2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_t3_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_t3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_t4_e2>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_t4_e3>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_t4>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_tp>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_tuple>(lns);
  ltest &= test_fiber_bundles_namespace_facet2<sec_vd>(lns);

  */
  //============================================================================

  lns.new_fiber_space<at0>();
  lns.new_fiber_space<at1>();
  ////lns.new_fiber_space<at2>(); //xi >= xj
  lns.new_fiber_space<at2_e2>();
  lns.new_fiber_space<at2_e3>();
  ////lns.new_fiber_space<at3>(); //xi >= xj
  lns.new_fiber_space<at3_e3>();
  ////lns.new_fiber_space<atp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0
  lns.new_fiber_space<e1>();
  lns.new_fiber_space<e2>();
  lns.new_fiber_space<e3>();
  lns.new_fiber_space<e4>();
  lns.new_fiber_space<ed>();
  lns.new_fiber_space<gl2>();
  lns.new_fiber_space<gl3>();
  lns.new_fiber_space<gln>();
  lns.new_fiber_space<jcb_e13>();
  lns.new_fiber_space<jcb_e23>();
  lns.new_fiber_space<jcb_e33>();
  lns.new_fiber_space<jcb_ed>();
  lns.new_fiber_space<jcb>();
  lns.new_fiber_space<met_e1>();
  lns.new_fiber_space<met_e2>();
  lns.new_fiber_space<met_e3>();
  ////lns.new_fiber_space<met_ed>(); //xi >= xj'
  ////lns.new_fiber_space<met>(); //xi >= xj'
  lns.new_fiber_space<st2_e2>();
  lns.new_fiber_space<st2_e3>();
  ////lns.new_fiber_space<st2>(); //xi >= xj'
  lns.new_fiber_space<st3_e3>();
  ////lns.new_fiber_space<st3>(); //xi >= xj'
  lns.new_fiber_space<st4_e2>();
  lns.new_fiber_space<st4_e3>();
  ////lns.new_fiber_space<st4>(); //xi >= xj'
  ////lns.new_fiber_space<stp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0
  lns.new_fiber_space<t2_e2>();
  lns.new_fiber_space<t2_e3>();
  lns.new_fiber_space<t2>();
  lns.new_fiber_space<t3_e3>();
  lns.new_fiber_space<t3>();
  lns.new_fiber_space<t4_e2>();
  lns.new_fiber_space<t4_e3>();
  lns.new_fiber_space<t4>();
  ////lns.new_fiber_space<tp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0
  lns.new_fiber_space<tuple>();
  lns.new_fiber_space<vd>();

  //============================================================================

  lns.new_scalar_space<at0>();
//   lns.new_scalar_space<at1>();
//   lns.new_scalar_space<at2>();
//   lns.new_scalar_space<at2_e2>();
//   lns.new_scalar_space<at2_e3>();
//   lns.new_scalar_space<at3>();
//   lns.new_scalar_space<at3_e3>();
//   lns.new_scalar_space<atp>();
//   lns.new_scalar_space<e1>();
//   lns.new_scalar_space<e2>();
//   lns.new_scalar_space<e3>();
//   lns.new_scalar_space<e4>();
//   lns.new_scalar_space<ed>();
//   lns.new_scalar_space<gl2>();
//   lns.new_scalar_space<gl3>();
//   lns.new_scalar_space<gln>();
//   lns.new_scalar_space<jcb_e13>();
//   lns.new_scalar_space<jcb_e23>();
//   lns.new_scalar_space<jcb_e33>();
//   lns.new_scalar_space<jcb_ed>();
//   lns.new_scalar_space<jcb>();
//   lns.new_scalar_space<met_e1>();
//   lns.new_scalar_space<met_e2>();
//   lns.new_scalar_space<met_e3>();
//   lns.new_scalar_space<met_ed>();
//   lns.new_scalar_space<met>();
//   lns.new_scalar_space<st2_e2>();
//   lns.new_scalar_space<st2_e3>();
//   lns.new_scalar_space<st2>();
//   lns.new_scalar_space<st3_e3>();
//   lns.new_scalar_space<st3>();
//   lns.new_scalar_space<st4_e2>();
//   lns.new_scalar_space<st4_e3>();
//   lns.new_scalar_space<st4>();
//   lns.new_scalar_space<stp>();
//   lns.new_scalar_space<t2_e2>();
//   lns.new_scalar_space<t2_e3>();
//   lns.new_scalar_space<t2>();
//   lns.new_scalar_space<t3_e3>();
//   lns.new_scalar_space<t3>();
//   lns.new_scalar_space<t4_e2>();
//   lns.new_scalar_space<t4_e3>();
//   lns.new_scalar_space<t4>();
//   lns.new_scalar_space<tp>();
//   lns.new_scalar_space<tuple>();
//   lns.new_scalar_space<vd>();

  //============================================================================

  //lns.new_vector_space<at0>();
  lns.new_vector_space<at1>();
//   lns.new_vector_space<at2>();
//   lns.new_vector_space<at2_e2>();
//   lns.new_vector_space<at2_e3>();
//   lns.new_vector_space<at3>();
//   lns.new_vector_space<at3_e3>();
//   lns.new_vector_space<atp>();

  lns.new_vector_space<e1>();
  lns.new_vector_space<e2>();
  lns.new_vector_space<e3>();
  lns.new_vector_space<e4>();
  lns.new_vector_space<ed>();

//   lns.new_vector_space<gl2>();
//   lns.new_vector_space<gl3>();
//   lns.new_vector_space<gln>();
//   lns.new_vector_space<jcb_e13>();
//   lns.new_vector_space<jcb_e23>();
//   lns.new_vector_space<jcb_e33>();
//   lns.new_vector_space<jcb_ed>();
//   lns.new_vector_space<jcb>();
//   lns.new_vector_space<met_e1>();
//   lns.new_vector_space<met_e2>();
//   lns.new_vector_space<met_e3>();
//   lns.new_vector_space<met_ed>();
//   lns.new_vector_space<met>();
//   lns.new_vector_space<st2_e2>();
//   lns.new_vector_space<st2_e3>();
//   lns.new_vector_space<st2>();
//   lns.new_vector_space<st3_e3>();
//   lns.new_vector_space<st3>();
//   lns.new_vector_space<st4_e2>();
//   lns.new_vector_space<st4_e3>();
//   lns.new_vector_space<st4>();
//   lns.new_vector_space<stp>();
//   lns.new_vector_space<t2_e2>();
//   lns.new_vector_space<t2_e3>();
//   lns.new_vector_space<t2>();
//   lns.new_vector_space<t3_e3>();
//   lns.new_vector_space<t3>();
//   lns.new_vector_space<t4_e2>();
//   lns.new_vector_space<t4_e3>();
//   lns.new_vector_space<t4>();
//   lns.new_vector_space<tp>();
//   lns.new_vector_space<tuple>();
//   lns.new_vector_space<vd>();

  //============================================================================

//   lns.new_tensor_space<at0>();
//   lns.new_tensor_space<at1>();

  ////lns.new_tensor_space<at2>(); //xi >= xj
  lns.new_tensor_space<at2_e2>();
  lns.new_tensor_space<at2_e3>();
  ////lns.new_tensor_space<at3>(); //xi >= xj
  lns.new_tensor_space<at3_e3>();
  ////lns.new_tensor_space<atp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0
//   lns.new_tensor_space<e1>();
//   lns.new_tensor_space<e2>();
//   lns.new_tensor_space<e3>();
//   lns.new_tensor_space<e4>();
//   lns.new_tensor_space<ed>();
//   lns.new_tensor_space<gl2>();
//   lns.new_tensor_space<gl3>();
//   lns.new_tensor_space<gln>();
//   lns.new_tensor_space<jcb_e13>();
//   lns.new_tensor_space<jcb_e23>();
//   lns.new_tensor_space<jcb_e33>();
//   lns.new_tensor_space<jcb_ed>();
//   lns.new_tensor_space<jcb>();
  lns.new_tensor_space<met_e1>();
  lns.new_tensor_space<met_e2>();
  lns.new_tensor_space<met_e3>();
  ////lns.new_tensor_space<met_ed>(); //xi >= xj
  ////lns.new_tensor_space<met>(); //xi >= xj
  lns.new_tensor_space<st2_e2>();
  lns.new_tensor_space<st2_e3>();
  ////lns.new_tensor_space<st2>(); //xi >= xj
  lns.new_tensor_space<st3_e3>();
  ////lns.new_tensor_space<st3>(); //xi >= xj
  lns.new_tensor_space<st4_e2>();
  lns.new_tensor_space<st4_e3>();
  ////lns.new_tensor_space<st4>();; //xi >= xj
  ////lns.new_tensor_space<stp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0
  lns.new_tensor_space<t2_e2>();
  lns.new_tensor_space<t2_e3>();
  lns.new_tensor_space<t2>();
  lns.new_tensor_space<t3_e3>();
  lns.new_tensor_space<t3>();
  lns.new_tensor_space<t4_e2>();
  lns.new_tensor_space<t4_e3>();
  lns.new_tensor_space<t4>();
  ////lns.new_tensor_space<tp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0
//   lns.new_tensor_space<tuple>();
//   lns.new_tensor_space<vd>();

  //============================================================================

  lns.new_group_space<gl2>();
  lns.new_group_space<gl3>();
  lns.new_group_space<gln>();

  lns.new_jacobian_space<jcb_e13>();
  lns.new_jacobian_space<jcb_e23>();
  lns.new_jacobian_space<jcb_e33>();
  lns.new_jacobian_space<jcb_ed>();
  lns.new_jacobian_space<jcb>();

  //============================================================================

  base_space_poset& lbase =
    lns.new_base_space<structured_block_2d>("2d_base_space");

  //cout << lns << endl;

  //============================================================================



  //lns.new_scalar_section_space<sec_at0>("scalar_section_space_0");

  //============================================================================

  // These return poset_path:

  // ??? = xpath.full() || xbase_space_path.full() ||
  //       (xargs.contains_arg("base_space_path") &&
  //       poset_path(xargs.value("base_space_path")).full())
  // file fiber_bundles_namespace.impl.h at line 3824

  ////lns.new_section_space_schema<sec_at0>();  //???
  ////lns.new_section_space_schema<sec_at1>();  //???
  ////lns.new_section_space_schema<sec_at2>();  //???
  ////lns.new_section_space_schema<sec_at2_e2>(); //???
  ////lns.new_section_space_schema<sec_at2_e3>(); //???
  ////lns.new_section_space_schema<sec_at3>(); //???
  ////lns.new_section_space_schema<sec_at3_e3>(); //???
  ////lns.new_section_space_schema<sec_atp>(); //???
  ////lns.new_section_space_schema<sec_e1>(); //???
  ////lns.new_section_space_schema<sec_e1_uniform>(); //???
  ////lns.new_section_space_schema<sec_e2>(); //???
  ////lns.new_section_space_schema<sec_e2_uniform>(); //???
  ////lns.new_section_space_schema<sec_e3>(); //???
  ////lns.new_section_space_schema<sec_e3_uniform>(); //???
  ////lns.new_section_space_schema<sec_e4>(); //???
  ////lns.new_section_space_schema<sec_ed>(); //???

  //lns.new_section_space_schema<sec_jcb_e13>();
  //lns.new_section_space_schema<sec_jcb_e23>();
  //lns.new_section_space_schema<sec_jcb_e33>();

  ////lns.new_section_space_schema<sec_met>(); //???
  ////lns.new_section_space_schema<sec_met_e1>(); //???
  ////lns.new_section_space_schema<sec_met_e2>(); //???
  ////lns.new_section_space_schema<sec_met_e3>(); //???
  ////lns.new_section_space_schema<sec_met_ed>(); //???
  ////lns.new_section_space_schema<sec_st2>(); //???

  ////lns.new_section_space_schema<sec_st2_e2>(); //???
  ////lns.new_section_space_schema<sec_st2_e3>(); //???
  ////lns.new_section_space_schema<sec_st3>(); //???
  ////lns.new_section_space_schema<sec_st3_e3>(); //???
  ////lns.new_section_space_schema<sec_st4>(); //???
  ////lns.new_section_space_schema<sec_st4_e2>(); //???
  ////lns.new_section_space_schema<sec_st4_e3>(); //???
  ////lns.new_section_space_schema<sec_stp>(); //???
  ////lns.new_section_space_schema<sec_t2>(); //???
  ////lns.new_section_space_schema<sec_t2_e2>(); //???
  ////lns.new_section_space_schema<sec_t2_e3>(); //???
  ////lns.new_section_space_schema<sec_t3>(); //???
  ////lns.new_section_space_schema<sec_t3_e3>(); //???
  ////lns.new_section_space_schema<sec_t4>(); //???
  ////lns.new_section_space_schema<sec_t4_e2>(); //???
  ////lns.new_section_space_schema<sec_t4_e3>(); //???
  ////lns.new_section_space_schema<sec_tp>(); //???


  //============================================================================

  lns.new_scalar_section_space_schema<sec_at0>("dummy_schema"); //???

  //============================================================================

  ////lns.new_vector_section_space_schema<sec_at1>(); //???
  ////lns.new_vector_section_space_schema<sec_e1>(); //???
  ////lns.new_vector_section_space_schema<sec_e1_uniform>(); //???
  ////lns.new_vector_section_space_schema<sec_e2>(); //???
  ////lns.new_vector_section_space_schema<sec_e2_uniform>(); //???
  ////lns.new_vector_section_space_schema<sec_e3>(); //???
  ////lns.new_vector_section_space_schema<sec_e3_uniform>(); //???
  ////lns.new_vector_section_space_schema<sec_e4>(); //???
  ////lns.new_vector_section_space_schema<sec_ed>(); //???
  ////lns.new_vector_section_space_schema<sec_vd>(); //???

  //============================================================================

  }
  catch(std::logic_error le)
  {
    cerr << "EXCEPTION EXCEPTION EXCEPTION EXCEPTION " << endl;
    cerr << "Caught: " << le.what() << endl;
    cerr << "Type: " << typeid(le).name( ) << endl;
  }

  int lresult = ltest ? 0 : 1;


  // Postconditions:

  // Exit:

  return lresult;
}

