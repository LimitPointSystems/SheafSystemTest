
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

/// @example
/// Unit test driver for template class auto_block.

#include "auto_block.h"

#include "block.h"
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

/*  print_header("Begin testing auto_block<arg_list::arg_type>");
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
  ltest &= test_auto_block_facet_un<scoped_index>();
  ltest &= test_auto_block_facet_equal_un<scoped_index>();
  ltest &= test_auto_block_facet_insertion_un<scoped_index>();
  ltest &= test_auto_block_facet_deep_size_un<scoped_index>();
  print_footer("End testing auto_block<scoped_index>");

  // scoped_index*

  print_header("Begin testing auto_block<scoped_index*>");
  ltest &= test_auto_block_facet_all<scoped_index*>();
  ltest &= test_auto_block_facet_equal_all<scoped_index*>();
  ltest &= test_auto_block_facet_insertion_all<scoped_index*>();
  ltest &= test_auto_block_facet_deep_size_all<scoped_index*>();
  print_footer("End testing auto_block<scoped_index*>");*/

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
//   ltest &= test_auto_block_facet_all<e3_lite>();
//   ltest &= test_auto_block_facet_equal_all<e3_lite>();
//   ltest &= test_auto_block_facet_insertion_all<e3_lite>();
//   ltest &= test_auto_block_facet_deep_size_all<e3_lite>();
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

  // block<scoped_index>*

/*  print_header("Begin testing auto_block<block<scoped_index>*>");
  ltest &= test_auto_block_facet_all<block<scoped_index>*>();
  ltest &= test_auto_block_facet_equal_all<block<scoped_index>*>();
  ltest &= test_auto_block_facet_insertion_all<block<scoped_index>*>();
  ltest &= test_auto_block_facet_deep_size_all<block<scoped_index>*>();
  print_footer("End testing auto_block<block<scoped_index>*>");*/

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

  //pair<scoped_index, chart_point_3d>

  print_header("Begin testing auto_block<pair<scoped_index, chart_point_3d> >");
  cout << "Need to specialize this one." << endl;
  //ltest &= test_auto_block_facet_all<pair<scoped_index, chart_point_3d> >();
  //ltest &= test_auto_block_facet_equal_all<pair<scoped_index, chart_point_3d> >();
  //ltest &= test_auto_block_facet_insertion_all<pair<scoped_index, chart_point_3d> >();
  //ltest &= test_auto_block_facet_deep_size_all<pair<scoped_index, chart_point_3d> >();
  print_footer("End testing auto_block<pair<scoped_index, chart_point_3d> >");

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

