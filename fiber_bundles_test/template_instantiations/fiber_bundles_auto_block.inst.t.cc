// $RCSfile: fiber_bundles_auto_block.inst.t.cc,v $ $Revision: 1.1.2.2 $ $Date: 2012/10/19 02:24:25 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class auto_block.

#include "auto_block.impl.h"

#include "block.impl.h"
#include "fiber_bundle.h"
#include "arg_list.h"
#include "chart_point_1d.h"
#include "chart_point_2d.h"
#include "chart_point_3d.h"
#include "discretization_context.h"
#include "e3.h"
#include "sec_tuple.h"
#include "sec_vd.h"
#include "section_evaluator.h"
#include "differentiable_section_evaluator.h"
#include "integrable_section_evaluator.h"
#include "structured_block.h"
#include "structured_block_1d.h"
#include "structured_block_1d_crg_range.h"
#include "structured_block_2d_crg_range.h"
#include "structured_block_3d_crg_range.h"
#include "base_space_crg_range.h"
#include "point_block_crg_range.h"
#include "zone_nodes_block_crg_range.h"
#include "homogeneous_block_crg_range.h"
#include "test_utils.h"
#include "test_sheaves.impl.h"

using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // arg_list::arg_type

  print_header("Begin testing auto_block<arg_list::arg_type>");
  ltest &= test_auto_block_facet_un<arg_list::arg_type>();
  ltest &= test_auto_block_facet_equal_un<arg_list::arg_type>();
  ltest &= test_auto_block_facet_insertion_un<arg_list::arg_type>();
  ltest &= test_auto_block_facet_deep_size_un<arg_list::arg_type>();
  print_footer("End testing auto_block<arg_list::arg_type>");

  // double

  print_header("Begin testing auto_block<double>");
  ltest &= test_auto_block_facet_all<double>();
  ltest &= test_auto_block_facet_equal_all<double>();
  ltest &= test_auto_block_facet_insertion_all<double>();
  ltest &= test_auto_block_facet_deep_size_all<double>();
  print_footer("End testing auto_block<double>");

  // scoped_index

  print_header("Begin testing auto_block<scoped_index>");
  ltest &= test_auto_block_facet_all<scoped_index>();
  ltest &= test_auto_block_facet_equal_all<scoped_index>();
  ltest &= test_auto_block_facet_insertion_all<scoped_index>();
  ltest &= test_auto_block_facet_deep_size_all<scoped_index>();
  print_footer("End testing auto_block<scoped_index>");

  // scoped_index*

  print_header("Begin testing auto_block<scoped_index*>");
  ltest &= test_auto_block_facet_all<scoped_index*>();
  ltest &= test_auto_block_facet_equal_all<scoped_index*>();
  ltest &= test_auto_block_facet_insertion_all<scoped_index*>();
  ltest &= test_auto_block_facet_deep_size_all<scoped_index*>();
  print_footer("End testing auto_block<scoped_index*>");

  // chart_point_1d

  print_header("Begin testing auto_block<chart_point_1d>");
  ltest &= test_auto_block_facet_un<chart_point_1d>();
  ltest &= test_auto_block_facet_equal_un<chart_point_1d>();
  ltest &= test_auto_block_facet_insertion_un<chart_point_1d>();
  ltest &= test_auto_block_facet_deep_size_un<chart_point_1d>();
  print_footer("End testing auto_block<chart_point_1d>");

  // chart_point_1d*

  print_header("Begin testing auto_block<chart_point_1d*>");
  ltest &= test_auto_block_facet_all<chart_point_1d*>();
  ltest &= test_auto_block_facet_equal_all<chart_point_1d*>();
  ltest &= test_auto_block_facet_insertion_all<chart_point_1d*>();
  ltest &= test_auto_block_facet_deep_size_all<chart_point_1d*>();
  print_footer("End testing auto_block<chart_point_1d*>");

  // chart_point_2d

  print_header("Begin testing auto_block<chart_point_2d>");
  ltest &= test_auto_block_facet_un<chart_point_2d>();
  ltest &= test_auto_block_facet_equal_un<chart_point_2d>();
  ltest &= test_auto_block_facet_insertion_un<chart_point_2d>();
  ltest &= test_auto_block_facet_deep_size_un<chart_point_2d>();
  print_footer("End testing auto_block<chart_point_2d>");

  // chart_point_2d*

  print_header("Begin testing auto_block<chart_point_2d*>");
  ltest &= test_auto_block_facet_all<chart_point_2d*>();
  ltest &= test_auto_block_facet_equal_all<chart_point_2d*>();
  ltest &= test_auto_block_facet_insertion_all<chart_point_2d*>();
  ltest &= test_auto_block_facet_deep_size_all<chart_point_2d*>();
  print_footer("End testing auto_block<chart_point_2d*>");

  // chart_point_3d

  print_header("Begin testing auto_block<chart_point_3d>");
  ltest &= test_auto_block_facet_un<chart_point_3d>();
  ltest &= test_auto_block_facet_equal_un<chart_point_3d>();
  ltest &= test_auto_block_facet_insertion_un<chart_point_3d>();
  ltest &= test_auto_block_facet_deep_size_un<chart_point_3d>();
  print_footer("End testing auto_block<chart_point_3d>");

  // chart_point_3d*

  print_header("Begin testing auto_block<chart_point_3d*>");
  ltest &= test_auto_block_facet_all<chart_point_3d*>();
  ltest &= test_auto_block_facet_equal_all<chart_point_3d*>();
  ltest &= test_auto_block_facet_insertion_all<chart_point_3d*>();
  ltest &= test_auto_block_facet_deep_size_all<chart_point_3d*>();
  print_footer("End testing auto_block<chart_point_3d*>");

  // e3_lite

  print_header("Begin testing auto_block<e3_lite>");
  ltest &= test_auto_block_facet_all<e3_lite>();
  ltest &= test_auto_block_facet_equal_all<e3_lite>();
  ltest &= test_auto_block_facet_insertion_all<e3_lite>();
  ltest &= test_auto_block_facet_deep_size_all<e3_lite>();
  print_footer("End testing auto_block<e3_lite>");

  // section_evaluator*

  print_header("Begin testing auto_block<section_evaluator*>");
  ltest &= test_auto_block_facet_all<section_evaluator*>();
  ltest &= test_auto_block_facet_equal_all<section_evaluator*>();
  ltest &= test_auto_block_facet_insertion_all<section_evaluator*>();
  ltest &= test_auto_block_facet_deep_size_all<section_evaluator*>();
  print_footer("End testing auto_block<section_evaluator*>");

  // differentiable_section_evaluator*

  print_header("Begin testing auto_block<differentiable_section_evaluator*>");
  ltest &= test_auto_block_facet_all<differentiable_section_evaluator*>();
  ltest &= test_auto_block_facet_equal_all<differentiable_section_evaluator*>();
  ltest &= test_auto_block_facet_insertion_all<differentiable_section_evaluator*>();
  ltest &= test_auto_block_facet_deep_size_all<differentiable_section_evaluator*>();
  print_footer("End testing auto_block<differentiable_section_evaluator*>");

  // integrable_section_evaluator*

  print_header("Begin testing auto_block<integrable_section_evaluator*>");
  ltest &= test_auto_block_facet_all<integrable_section_evaluator*>();
  ltest &= test_auto_block_facet_equal_all<integrable_section_evaluator*>();
  ltest &= test_auto_block_facet_insertion_all<integrable_section_evaluator*>();
  ltest &= test_auto_block_facet_deep_size_all<integrable_section_evaluator*>();
  print_footer("End testing auto_block<integrable_section_evaluator*>");

  // structured_auto_block_1d_crg_range*

  print_header("Begin testing auto_block<structured_block_1d_crg_range*>");
  ltest &= test_auto_block_facet_all<structured_block_1d_crg_range*>();
  ltest &= test_auto_block_facet_equal_all<structured_block_1d_crg_range*>();
  ltest &= test_auto_block_facet_insertion_all<structured_block_1d_crg_range*>();
  ltest &= test_auto_block_facet_deep_size_all<structured_block_1d_crg_range*>();
  print_footer("End testing auto_block<structured_block_1d_crg_range*>");

  // structured_auto_block_2d_crg_range*

  print_header("Begin testing auto_block<structured_block_2d_crg_range*>");
  ltest &= test_auto_block_facet_all<structured_block_2d_crg_range*>();
  ltest &= test_auto_block_facet_equal_all<structured_block_2d_crg_range*>();
  ltest &= test_auto_block_facet_insertion_all<structured_block_2d_crg_range*>();
  ltest &= test_auto_block_facet_deep_size_all<structured_block_2d_crg_range*>();
  print_footer("End testing auto_block<structured_block_2d_crg_range*>");

  // structured_auto_block_3d_crg_range*

  print_header("Begin testing auto_block<structured_block_3d_crg_range*>");
  ltest &= test_auto_block_facet_all<structured_block_3d_crg_range*>();
  ltest &= test_auto_block_facet_equal_all<structured_block_3d_crg_range*>();
  ltest &= test_auto_block_facet_insertion_all<structured_block_3d_crg_range*>();
  ltest &= test_auto_block_facet_deep_size_all<structured_block_3d_crg_range*>();
  print_footer("End testing auto_block<structured_block_3d_crg_range*>");

  // base_space_crg_range*

  print_header("Begin testing auto_block<base_space_crg_range*>");
  ltest &= test_auto_block_facet_all<base_space_crg_range*>();
  ltest &= test_auto_block_facet_equal_all<base_space_crg_range*>();
  ltest &= test_auto_block_facet_insertion_all<base_space_crg_range*>();
  ltest &= test_auto_block_facet_deep_size_all<base_space_crg_range*>();
  print_footer("End testing auto_block<base_space_crg_range*>");

  // point_block_crg_range*

  print_header("Begin testing auto_block<point_block_crg_range*>");
  ltest &= test_auto_block_facet_all<point_block_crg_range*>();
  ltest &= test_auto_block_facet_equal_all<point_block_crg_range*>();
  ltest &= test_auto_block_facet_insertion_all<point_block_crg_range*>();
  ltest &= test_auto_block_facet_deep_size_all<point_block_crg_range*>();
  print_footer("End testing auto_block<point_block_crg_range*>");

  // zone_nodes_block_crg_range*

  print_header("Begin testing auto_block<zone_nodes_block_crg_range*>");
  ltest &= test_auto_block_facet_all<zone_nodes_block_crg_range*>();
  ltest &= test_auto_block_facet_equal_all<zone_nodes_block_crg_range*>();
  ltest &= test_auto_block_facet_insertion_all<zone_nodes_block_crg_range*>();
  ltest &= test_auto_block_facet_deep_size_all<zone_nodes_block_crg_range*>();
  print_footer("End testing auto_block<zone_nodes_block_crg_range*>");

  // homogeneous_block_crg_range*

  print_header("Begin testing auto_block<homogeneous_block_crg_range*>");
  ltest &= test_auto_block_facet_all<homogeneous_block_crg_range*>();
  ltest &= test_auto_block_facet_equal_all<homogeneous_block_crg_range*>();
  ltest &= test_auto_block_facet_insertion_all<homogeneous_block_crg_range*>();
  ltest &= test_auto_block_facet_deep_size_all<homogeneous_block_crg_range*>();
  print_footer("End testing auto_block<homogeneous_block_crg_range*>");

  // block<scoped_index>*

  print_header("Begin testing auto_block<block<scoped_index>*>");
  ltest &= test_auto_block_facet_all<block<scoped_index>*>();
  ltest &= test_auto_block_facet_equal_all<block<scoped_index>*>();
  ltest &= test_auto_block_facet_insertion_all<block<scoped_index>*>();
  ltest &= test_auto_block_facet_deep_size_all<block<scoped_index>*>();
  print_footer("End testing auto_block<block<scoped_index>*>");

  // discretization_context

  print_header("Begin testing auto_block<discretization_context>");
  ltest &= test_auto_block_facet_un<discretization_context>();
  //ltest &= test_auto_block_facet_equal_un<discretization_context>();  //No operator==
  ltest &= test_auto_block_facet_insertion_un<discretization_context>();
  ltest &= test_auto_block_facet_deep_size_un<discretization_context>();
  print_footer("End testing auto_block<discretization_context>");

  // discretization_context*

  print_header("Begin testing auto_block<discretization_context*>");
  ltest &= test_auto_block_facet_all<discretization_context*>();
  ltest &= test_auto_block_facet_equal_all<discretization_context*>();
  ltest &= test_auto_block_facet_insertion_all<discretization_context*>();
  ltest &= test_auto_block_facet_deep_size_all<discretization_context*>();
  print_footer("End testing auto_block<discretization_context*>");

  //============================================================================
  // Two parameter cases:
  //============================================================================

  // sec_vd*

  print_header("Begin testing auto_block<sec_vd*>");
  ltest &= test_auto_block_facet_un<sec_vd*, sec_vd>();
  ltest &= test_auto_block_facet_equal_un<sec_vd*, sec_vd>();
  ltest &= test_auto_block_facet_insertion_un<sec_vd*, sec_vd>();
  ltest &= test_auto_block_facet_deep_size_un<sec_vd*, sec_vd>();
  print_footer("End testing auto_block<sec_vd*>");

  // sec_tuple*

  print_header("Begin testing auto_block<sec_tuple*>");
  ltest &= test_auto_block_facet_un<sec_tuple*, sec_tuple>();
  ltest &= test_auto_block_facet_equal_un<sec_tuple*, sec_tuple>();
  ltest &= test_auto_block_facet_insertion_un<sec_tuple*, sec_tuple>();
  ltest &= test_auto_block_facet_deep_size_un<sec_tuple*, sec_tuple>();
  print_footer("End testing auto_block<sec_tuple*>");

  // structured_auto_block*

  print_header("Begin testing auto_block<structured_block*>");
  ltest &= test_auto_block_facet_un<structured_block*, structured_block_1d>();
  ltest &= test_auto_block_facet_equal_un<structured_block*, structured_block_1d>();
  ltest &= test_auto_block_facet_insertion_un<structured_block*, structured_block_1d>();
  ltest &= test_auto_block_facet_deep_size_un<structured_block*, structured_block_1d>();
  print_footer("End testing auto_block<structured_block*>");


  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}


////////////////////////////////////////////////////////////////////////////////

