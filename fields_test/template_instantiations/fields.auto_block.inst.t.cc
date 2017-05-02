
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

#include "SheafSystem/auto_block.h"

#include "SheafSystem/fields.h"

#include "SheafSystem/barycentric_refiner_family.h"
#include "SheafSystem/edge_centered_polygon_refiner.h"
#include "SheafSystem/edge_centered_refiner_family.h"
#include "SheafSystem/local_field_refiner.h"
#include "SheafSystem/zone_centered_refiner_family.h"
#include "SheafSystem/zone_centered_segment_refiner.h"
#include "SheafSystem/zone_centered_tet_refiner.h"
#include "SheafSystem/zone_centered_triangle_refiner.h"
#include "SheafSystem/pullback_map.h"

#include "SheafSystemTest/test_utils.h"
#include "SheafSystemTest/test_sheaves.impl.h"

using namespace std;
using namespace fields;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // local_field_refiner*

  print_header("Begin testing auto_block<local_field_refiner*>");
  ltest &= test_auto_block_facet_un<local_field_refiner*>();
  ltest &= test_auto_block_facet_equal_un<local_field_refiner*>();
  ltest &= test_auto_block_facet_insertion_un<local_field_refiner*>();
  //ltest &= test_auto_block_facet_deep_size_un<local_field_refiner*>();
  print_footer("End testing auto_block<local_field_refiner*>");

  // barycentric_refiner_family*

  print_header("Begin testing auto_block<barycentric_refiner_family*>");
  ltest &= test_auto_block_facet_un<barycentric_refiner_family*>();
  ltest &= test_auto_block_facet_equal_un<barycentric_refiner_family*>();
  ltest &= test_auto_block_facet_insertion_un<barycentric_refiner_family*>();
  //ltest &= test_auto_block_facet_deep_size_un<barycentric_refiner_family*>();
  print_footer("End testing auto_block<barycentric_refiner_family*>");

  // edge_centered_polygon_refiner*

  print_header("Begin testing auto_block<edge_centered_polygon_refiner*>");
  ltest &= test_auto_block_facet_un<edge_centered_polygon_refiner*>();
  ltest &= test_auto_block_facet_equal_un<edge_centered_polygon_refiner*>();
  ltest &= test_auto_block_facet_insertion_un<edge_centered_polygon_refiner*>();
  //ltest &= test_auto_block_facet_deep_size_un<edge_centered_polygon_refiner*>();
  print_footer("End testing auto_block<edge_centered_polygon_refiner*>");

  // edge_centered_refiner_family*

  print_header("Begin testing auto_block<edge_centered_refiner_family*>");
  ltest &= test_auto_block_facet_un<edge_centered_refiner_family*>();
  ltest &= test_auto_block_facet_equal_un<edge_centered_refiner_family*>();
  ltest &= test_auto_block_facet_insertion_un<edge_centered_refiner_family*>();
  //ltest &= test_auto_block_facet_deep_size_un<edge_centered_refiner_family*>();
  print_footer("End testing auto_block<edge_centered_refiner_family*>");

  // zone_centered_refiner_family*

  print_header("Begin testing auto_block<zone_centered_refiner_family*>");
  ltest &= test_auto_block_facet_un<zone_centered_refiner_family*>();
  ltest &= test_auto_block_facet_equal_un<zone_centered_refiner_family*>();
  ltest &= test_auto_block_facet_insertion_un<zone_centered_refiner_family*>();
  //ltest &= test_auto_block_facet_deep_size_un<zone_centered_refiner_family*>();
  print_footer("End testing auto_block<zone_centered_refiner_family*>");

  // zone_centered_segment_refiner*

  print_header("Begin testing auto_block<zone_centered_segment_refiner*>");
  ltest &= test_auto_block_facet_un<zone_centered_segment_refiner*>();
  ltest &= test_auto_block_facet_equal_un<zone_centered_segment_refiner*>();
  ltest &= test_auto_block_facet_insertion_un<zone_centered_segment_refiner*>();
  //ltest &= test_auto_block_facet_deep_size_un<zone_centered_segment_refiner*>();
  print_footer("End testing auto_block<zone_centered_segment_refiner*>");

  // zone_centered_tet_refiner*

  print_header("Begin testing auto_block<zone_centered_tet_refiner*>");
  ltest &= test_auto_block_facet_un<zone_centered_tet_refiner*>();
  ltest &= test_auto_block_facet_equal_un<zone_centered_tet_refiner*>();
  ltest &= test_auto_block_facet_insertion_un<zone_centered_tet_refiner*>();
  //ltest &= test_auto_block_facet_deep_size_un<zone_centered_tet_refiner*>();
  print_footer("End testing auto_block<zone_centered_tet_refiner*>");

  // zone_centered_triangle_refiner*

  print_header("Begin testing auto_block<zone_centered_triangle_refiner*>");
  ltest &= test_auto_block_facet_un<zone_centered_triangle_refiner*>();
  ltest &= test_auto_block_facet_equal_un<zone_centered_triangle_refiner*>();
  ltest &= test_auto_block_facet_insertion_un<zone_centered_triangle_refiner*>();
  //ltest &= test_auto_block_facet_deep_size_un<zone_centered_triangle_refiner*>();
  print_footer("End testing auto_block<zone_centered_triangle_refiner*>");

  // pullback_map*

  print_header("Begin testing auto_block<pullback_map*>");
  ltest &= test_auto_block_facet_un<pullback_map*>();
  ltest &= test_auto_block_facet_equal_un<pullback_map*>();
  ltest &= test_auto_block_facet_insertion_un<pullback_map*>();
  //ltest &= test_auto_block_facet_deep_size_un<pullback_map*>();
  print_footer("End testing auto_block<pullback_map*>");


  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}


////////////////////////////////////////////////////////////////////////////////

