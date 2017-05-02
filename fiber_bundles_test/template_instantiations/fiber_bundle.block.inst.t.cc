
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
/// Unit test driver for template class block.

#include "SheafSystem/block.h"

#include "SheafSystem/arg_list.h"
#include "SheafSystem/chart_point_1d.h"
#include "SheafSystem/chart_point_2d.h"
#include "SheafSystem/chart_point_3d.h"
#include "SheafSystem/discretization_context.h"
#include "SheafSystem/e3.h"
#include "SheafSystem/sec_tuple.h"
#include "SheafSystem/sec_vd.h"
#include "SheafSystem/section_evaluator.h"
#include "SheafSystem/differentiable_section_evaluator.h"
#include "SheafSystem/integrable_section_evaluator.h"
#include "SheafSystem/structured_block.h"
#include "SheafSystem/structured_block_1d.h"
#include "SheafSystemTest/test_utils.h"
#include "SheafSystemTest/test_sheaves.impl.h"

using namespace std;
using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;


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
