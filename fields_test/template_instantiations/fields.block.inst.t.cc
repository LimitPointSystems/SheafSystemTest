
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

#include "block.h"

#include "barycentric_refiner_family.h"
#include "edge_centered_polygon_refiner.h"
#include "edge_centered_refiner_family.h"
#include "zone_centered_refiner_family.h"
#include "zone_centered_segment_refiner.h"
#include "zone_centered_tet_refiner.h"
#include "zone_centered_triangle_refiner.h"
#include "local_field_refiner.h"
#include "pullback_map.h"
#include "test_utils.h"
#include "test_sheaves.impl.h"

using namespace std;
using namespace fields;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // local_field_refiner*

  print_header("Begin testing block<local_field_refiner*>");
  ltest &= test_block_facet<local_field_refiner*>();
  ltest &= test_block_facet_equal<local_field_refiner*>();
  ltest &= test_block_facet_insertion<local_field_refiner*>();
  //ltest &= test_block_facet_deep_size<local_field_refiner*>();
  print_footer("End testing block<local_field_refiner*>");

  // barycentric_refiner_family*

  print_header("Begin testing block<barycentric_refiner_family*>");
  ltest &= test_block_facet<barycentric_refiner_family*>();
  ltest &= test_block_facet_equal<barycentric_refiner_family*>();
  ltest &= test_block_facet_insertion<barycentric_refiner_family*>();
  //ltest &= test_block_facet_deep_size<barycentric_refiner_family*>();
  print_footer("End testing block<barycentric_refiner_family*>");

  // edge_centered_polygon_refiner*

  print_header("Begin testing block<edge_centered_polygon_refiner*>");
  ltest &= test_block_facet<edge_centered_polygon_refiner*>();
  ltest &= test_block_facet_equal<edge_centered_polygon_refiner*>();
  ltest &= test_block_facet_insertion<edge_centered_polygon_refiner*>();
  //ltest &= test_block_facet_deep_size<edge_centered_polygon_refiner*>();
  print_footer("End testing block<edge_centered_polygon_refiner*>");

  // edge_centered_refiner_family*

  print_header("Begin testing block<edge_centered_refiner_family*>");
  ltest &= test_block_facet<edge_centered_refiner_family*>();
  ltest &= test_block_facet_equal<edge_centered_refiner_family*>();
  ltest &= test_block_facet_insertion<edge_centered_refiner_family*>();
  //ltest &= test_block_facet_deep_size<edge_centered_refiner_family*>();
  print_footer("End testing block<edge_centered_refiner_family*>");

  // zone_centered_refiner_family*

  print_header("Begin testing block<zone_centered_refiner_family*>");
  ltest &= test_block_facet<zone_centered_refiner_family*>();
  ltest &= test_block_facet_equal<zone_centered_refiner_family*>();
  ltest &= test_block_facet_insertion<zone_centered_refiner_family*>();
  //ltest &= test_block_facet_deep_size<zone_centered_refiner_family*>();
  print_footer("End testing block<zone_centered_refiner_family*>");

  // zone_centered_segment_refiner*

  print_header("Begin testing block<zone_centered_segment_refiner*>");
  ltest &= test_block_facet<zone_centered_segment_refiner*>();
  ltest &= test_block_facet_equal<zone_centered_segment_refiner*>();
  ltest &= test_block_facet_insertion<zone_centered_segment_refiner*>();
  //ltest &= test_block_facet_deep_size<zone_centered_segment_refiner*>();
  print_footer("End testing block<zone_centered_segment_refiner*>");

  // zone_centered_tet_refiner*

  print_header("Begin testing block<zone_centered_tet_refiner*>");
  ltest &= test_block_facet<zone_centered_tet_refiner*>();
  ltest &= test_block_facet_equal<zone_centered_tet_refiner*>();
  ltest &= test_block_facet_insertion<zone_centered_tet_refiner*>();
  //ltest &= test_block_facet_deep_size<zone_centered_tet_refiner*>();
  print_footer("End testing block<zone_centered_tet_refiner*>");

  // zone_centered_triangle_refiner*

  print_header("Begin testing block<zone_centered_triangle_refiner*>");
  ltest &= test_block_facet<zone_centered_triangle_refiner*>();
  ltest &= test_block_facet_equal<zone_centered_triangle_refiner*>();
  ltest &= test_block_facet_insertion<zone_centered_triangle_refiner*>();
  //ltest &= test_block_facet_deep_size<zone_centered_triangle_refiner*>();
  print_footer("End testing block<zone_centered_triangle_refiner*>");

  // pullback_map*

  print_header("Begin testing block<pullback_map*>");
  ltest &= test_block_facet<pullback_map*>();
  ltest &= test_block_facet_equal<pullback_map*>();
  ltest &= test_block_facet_insertion<pullback_map*>();
  //ltest &= test_block_facet_deep_size<pullback_map*>();
  print_footer("End testing block<pullback_map*>");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
