
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class section_space_factory.

#include "section_space_factory.h"

#include "fiber_bundles_namespace.h"
#include "test_utils.h"

#include "sec_at0.h"
#include "sec_at2_e2.h"
#include "sec_at2_e3.h"
#include "sec_at3_e3.h"
#include "sec_e1.h"
#include "sec_e1_uniform.h"
#include "sec_e2.h"
#include "sec_e2_uniform.h"
#include "sec_e3.h"
#include "sec_e3_uniform.h"
#include "sec_met_e1.h"
#include "sec_met_e2.h"
#include "sec_met_e3.h"
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

#include "assert_contract.h"
#include "base_space_member.h"
#include "base_space_poset.h"
// #include "error_message.h"
// #include "fiber_bundles_namespace.h"
// #include "field_factory.h"
// #include "fields.h"
// #include "namespace_poset.h"
#include "sec_at1_space.h"
// #include "sec_e1_uniform.h"
// #include "sec_ed_invertible.h"
// #include "sec_rep_descriptor.h"
// #include "section_dof_iterator.h"
// #include "section_pusher.h"
// #include "std_iostream.h"
// #include "storage_agent.h"
// #include "structured_block_1d.h"
// #include "field_vd.h"
// #include "wsv_block.h"


// #include "arg_list.h"
// #include "chart_point_1d.h"
// #include "chart_point_2d.h"
// #include "chart_point_3d.h"
// #include "discretization_context.h"
// #include "e3.h"
// #include "sec_tuple.h"
// #include "sec_vd.h"
// #include "section_evaluator.h"
// #include "differentiable_section_evaluator.h"
// #include "integrable_section_evaluator.h"
// #include "structured_block.h"
#include "structured_block_1d.h"
// #include "structured_block_1d_crg_range.h"
// #include "structured_block_2d_crg_range.h"
// #include "structured_block_3d_crg_range.h"
// #include "base_space_crg_range.h"
// #include "point_block_crg_range.h"
// #include "zone_nodes_block_crg_range.h"
// #include "homogeneous_block_crg_range.h"
// #include "test_utils.h"
// #include "test_sheaves.impl.h"

using namespace fiber_bundle;

namespace
{
  template<typename S>
  bool
  test_section_space_factory(fiber_bundles_namespace& xns)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());

    // Body:

    section_space_factory<S> lfac;

    bool lfound = lfac.found_section();

    lfac.clear_paths();

    //section_space_factory<S> lfac_copy(lfac); //not_implemented.

    ////////////////////////////////////////////////////////////////////////////

//   poset_path lpath("coarse_mesh_coordinate_section_space/coordinates_0");
  
//   string lbase_name("coarse_mesh");

//   base_space_poset* lbase_host = &xns.new_base_space<structured_block_1d>(lbase_name);
//   structured_block_1d lbase(lbase_host, 3, true);
//   lbase.put_name(lbase_name, true, true);

//   sec_rep_space& lhost = xns.new_section_space<sec_e1_uniform>(lpath,
// 							       lbase.path(),
// 							       "",
// 							       true);
//   lhost.get_read_write_access();  
  
//   sec_e1_uniform lcoarse_coords(&lhost, -2.0, 2.0, true);
//   lcoarse_coords.put_name("coarse_coords", true, true);

//   lcoarse_coords.detach_from_state();
//   lbase.detach_from_state();

//   subposet lbase_parts(lbase_host);
//   lbase_parts.insert_member(scoped_index(0));

   ////////////////////////////////////////////////////////////////////////////

//     base_space_poset* lbase_host =
//       &xns.new_base_space<structured_block_1d>("1d_structured_mesh");

//     structured_block_1d lbase0(lbase_host, 4, true);
//     lbase0.put_name("1d_structured_block", true, true);

//     const string lname = "my_section_space";
//     sec_rep_space& lspace = 
//        xns.new_section_space<S>(lname, lbase0.path(), "", true);

//     lspace.get_read_write_access();

//     subposet lbase_parts(lbase0.host());

//     lbase_parts.put_name("base_parts", true, false);
//     lbase_parts.insert_member(lbase0.index());

    ////////////////////////////////////////////////////////////////////////////

    // subposet lbase_parts;
    //string lname2 = "section_name";
    //S* lsec = lfac.new_multi_section(xns, lpath, lbase_parts);
    //S* lsec = lfac.new_multi_section(xns, lname, lbase_parts);
    //S* lsec2 = lfac.new_multi_section(xns, lpath, lbase_parts);

    //S lsec;
    //lfac.put_bounds(&lsec);

    ////////////////////////////////////////////////////////////////////////////

    // Postconditions:

    // Exit:

    //return lresult;
    return true;
  }

} //end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing section_space_factory");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  bool ltest = true;

  ltest &= test_section_space_factory<sec_at0>(lns);
  ltest &= test_section_space_factory<sec_at2_e2>(lns);
  ltest &= test_section_space_factory<sec_at2_e3>(lns);
  ltest &= test_section_space_factory<sec_at3_e3>(lns);
  ltest &= test_section_space_factory<sec_e1>(lns);
   ltest &= test_section_space_factory<sec_e1_uniform>(lns);
  ltest &= test_section_space_factory<sec_e2>(lns);
  ltest &= test_section_space_factory<sec_e2_uniform>(lns);
  ltest &= test_section_space_factory<sec_e3>(lns);
  ltest &= test_section_space_factory<sec_e3_uniform>(lns);
  ltest &= test_section_space_factory<sec_met_e1>(lns);
  ltest &= test_section_space_factory<sec_met_e2>(lns);
  ltest &= test_section_space_factory<sec_met_e3>(lns);
  ltest &= test_section_space_factory<sec_st2_e2>(lns);
  ltest &= test_section_space_factory<sec_st2_e3>(lns);
  ltest &= test_section_space_factory<sec_st3_e3>(lns);
  ltest &= test_section_space_factory<sec_st4_e2>(lns);
  ltest &= test_section_space_factory<sec_st4_e3>(lns);
  ltest &= test_section_space_factory<sec_t2_e2>(lns);
  ltest &= test_section_space_factory<sec_t2_e3>(lns);
  ltest &= test_section_space_factory<sec_t3_e3>(lns);
  ltest &= test_section_space_factory<sec_t4_e2>(lns);
  ltest &= test_section_space_factory<sec_t4_e3>(lns);

//template class fiber_bundle::section_space_factory<fiber_bundle::sec_jcb_e13>;
//template class fiber_bundle::section_space_factory<fiber_bundle::sec_jcb_e23>;
//template class fiber_bundle::section_space_factory<fiber_bundle::sec_jcb_e33>;

  //============================================================================

  print_footer("End testing section_space_factory");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
