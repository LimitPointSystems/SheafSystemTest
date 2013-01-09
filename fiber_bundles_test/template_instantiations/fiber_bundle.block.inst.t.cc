// $RCSfile: fiber_bundles_block.inst.t.cc,v $ $Revision: 1.1.2.9 $ $Date: 2012/11/08 17:22:07 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class block.

#include "block.h"

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

/*  print_header("Begin testing block<arg_list::arg_type>");
  ltest &= test_block_facet<arg_list::arg_type>();
  ltest &= test_block_facet_equal<arg_list::arg_type>();
  ltest &= test_block_facet_insertion<arg_list::arg_type>();
  ltest &= test_block_facet_deep_size<arg_list::arg_type>();
  print_footer("End testing block<arg_list::arg_type>");

  // double

  print_header("Begin testing block<double>");
  ltest &= test_block_facet<double>();
  ltest &= test_block_facet_equal<double>();
  ltest &= test_block_facet_insertion<double>();
  ltest &= test_block_facet_deep_size<double>();
  print_footer("End testing block<double>");

  // scoped_index

  print_header("Begin testing block<scoped_index>");
  ltest &= test_block_facet<scoped_index>();
  ltest &= test_block_facet_equal<scoped_index>();
  ltest &= test_block_facet_insertion<scoped_index>();
  ltest &= test_block_facet_deep_size<scoped_index>();
  print_footer("End testing block<scoped_index>");

  // scoped_index*

  print_header("Begin testing block<scoped_index*>");
  ltest &= test_block_facet<scoped_index*>();
  ltest &= test_block_facet_equal<scoped_index*>();
  ltest &= test_block_facet_insertion<scoped_index*>();
  ltest &= test_block_facet_deep_size<scoped_index*>();
  print_footer("End testing block<scoped_index*>");*/

  // chart_point_1d

  print_header("Begin testing block<chart_point_1d>");
  ltest &= test_block_facet<chart_point_1d>();
  ltest &= test_block_facet_equal<chart_point_1d>();
  ltest &= test_block_facet_insertion<chart_point_1d>();
  ltest &= test_block_facet_deep_size<chart_point_1d>();
  print_footer("End testing block<chart_point_1d>");

  // chart_point_1d*

  print_header("Begin testing block<chart_point_1d*>");
  ltest &= test_block_facet<chart_point_1d*>();
  ltest &= test_block_facet_equal<chart_point_1d*>();
  ltest &= test_block_facet_insertion<chart_point_1d*>();
  ltest &= test_block_facet_deep_size<chart_point_1d*>();
  print_footer("End testing block<chart_point_1d*>");

  // chart_point_2d

  print_header("Begin testing block<chart_point_2d>");
  ltest &= test_block_facet<chart_point_2d>();
  ltest &= test_block_facet_equal<chart_point_2d>();
  ltest &= test_block_facet_insertion<chart_point_2d>();
  ltest &= test_block_facet_deep_size<chart_point_2d>();
  print_footer("End testing block<chart_point_2d>");

  // chart_point_2d*

  print_header("Begin testing block<chart_point_2d*>");
  ltest &= test_block_facet<chart_point_2d*>();
  ltest &= test_block_facet_equal<chart_point_2d*>();
  ltest &= test_block_facet_insertion<chart_point_2d*>();
  ltest &= test_block_facet_deep_size<chart_point_2d*>();
  print_footer("End testing block<chart_point_2d*>");

  // chart_point_3d

  print_header("Begin testing block<chart_point_3d>");
  ltest &= test_block_facet<chart_point_3d>();
  ltest &= test_block_facet_equal<chart_point_3d>();
  ltest &= test_block_facet_insertion<chart_point_3d>();
  ltest &= test_block_facet_deep_size<chart_point_3d>();
  print_footer("End testing block<chart_point_3d>");

  // chart_point_3d*

  print_header("Begin testing block<chart_point_3d*>");
  ltest &= test_block_facet<chart_point_3d*>();
  ltest &= test_block_facet_equal<chart_point_3d*>();
  ltest &= test_block_facet_insertion<chart_point_3d*>();
  ltest &= test_block_facet_deep_size<chart_point_3d*>();
  print_footer("End testing block<chart_point_3d*>");

  // e3_lite

  print_header("Begin testing block<e3_lite>");
  ltest &= test_block_facet<e3_lite>();
  ltest &= test_block_facet_equal<e3_lite>();
  ltest &= test_block_facet_insertion<e3_lite>();
  ltest &= test_block_facet_deep_size<e3_lite>();
  print_footer("End testing block<e3_lite>");

  // section_evaluator*

  print_header("Begin testing block<section_evaluator*>");
  ltest &= test_block_facet<section_evaluator*>();
  ltest &= test_block_facet_equal<section_evaluator*>();
  ltest &= test_block_facet_insertion<section_evaluator*>();
  ltest &= test_block_facet_deep_size<section_evaluator*>();
  print_footer("End testing block<section_evaluator*>");

  // differentiable_section_evaluator*

  print_header("Begin testing block<differentiable_section_evaluator*>");
  ltest &= test_block_facet<differentiable_section_evaluator*>();
  ltest &= test_block_facet_equal<differentiable_section_evaluator*>();
  ltest &= test_block_facet_insertion<differentiable_section_evaluator*>();
  ltest &= test_block_facet_deep_size<differentiable_section_evaluator*>();
  print_footer("End testing block<differentiable_section_evaluator*>");

  // integrable_section_evaluator*

  print_header("Begin testing block<integrable_section_evaluator*>");
  ltest &= test_block_facet<integrable_section_evaluator*>();
  ltest &= test_block_facet_equal<integrable_section_evaluator*>();
  ltest &= test_block_facet_insertion<integrable_section_evaluator*>();
  ltest &= test_block_facet_deep_size<integrable_section_evaluator*>();
  print_footer("End testing block<integrable_section_evaluator*>");

  // block<scoped_index>*

/*  print_header("Begin testing block<block<scoped_index>*>");
  ltest &= test_block_facet<block<scoped_index>*>();
  ltest &= test_block_facet_equal<block<scoped_index>*>();
  ltest &= test_block_facet_insertion<block<scoped_index>*>();
  //ltest &= test_block_facet_deep_size<block<scoped_index>*>();
  print_footer("End testing block<block<scoped_index>*>");*/

  // discretization_context

  print_header("Begin testing block<discretization_context>");
  ltest &= test_block_facet<discretization_context>();
  //ltest &= test_block_facet_equal<discretization_context>();  //No operator==
  ltest &= test_block_facet_insertion<discretization_context>();
  ltest &= test_block_facet_deep_size<discretization_context>();
  print_footer("End testing block<discretization_context>");

  // discretization_context*

  print_header("Begin testing block<discretization_context*>");
  ltest &= test_block_facet<discretization_context*>();
  ltest &= test_block_facet_equal<discretization_context*>();
  ltest &= test_block_facet_insertion<discretization_context*>();
  ltest &= test_block_facet_deep_size<discretization_context*>();
  print_footer("End testing block<discretization_context*>");

  // pair<scoped_index, chart_point_3d>

  //$$SCRIBBLE: This test is really needed in geometry but our current
  //            convention says it should be here (fiber_bundle::chart_point_3d).
  //
  //            Need specialization to make deep_size, etc work.

  print_header("Begin testing block<pair<scoped_index, chart_point_3d> >");
  ltest &= test_block_facet<pair<scoped_index, chart_point_3d> >();
  //ltest &= test_block_facet_equal<pair<scoped_index, chart_point_3d> >();
  //ltest &= test_block_facet_insertion<pair<scoped_index, chart_point_3d> >();
  //ltest &= test_block_facet_deep_size<pair<scoped_index, chart_point_3d> >();
  print_footer("End testing block<pair<scoped_index, chart_point_3d> >");


  //============================================================================
  // Two parameter cases:
  //============================================================================

  // sec_vd*

  print_header("Begin testing block<sec_vd*>");
  ltest &= test_block_facet<sec_vd*, sec_vd>();
  ltest &= test_block_facet_equal<sec_vd*>();
  //ltest &= test_block_facet_insertion<sec_vd*>();
  ltest &= test_block_facet_deep_size<sec_vd*>();
  print_footer("End testing block<sec_vd*>");

  // sec_tuple*

  print_header("Begin testing block<sec_tuple*>");
  ltest &= test_block_facet<sec_tuple*, sec_tuple>();
  ltest &= test_block_facet_equal<sec_tuple*>();
  //ltest &= test_block_facet_insertion<sec_tuple*>();
  ltest &= test_block_facet_deep_size<sec_tuple*>();
  print_footer("End testing block<sec_tuple*>");

  // structured_block*

  print_header("Begin testing block<structured_block*>");
  ltest &= test_block_facet<structured_block*, structured_block_1d>();
  ltest &= test_block_facet_equal<structured_block*>();
  //ltest &= test_block_facet_insertion<structured_block*>();
  ltest &= test_block_facet_deep_size<structured_block*>();
  print_footer("End testing block<structured_block*>");


  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
