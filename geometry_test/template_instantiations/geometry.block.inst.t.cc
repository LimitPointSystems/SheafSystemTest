
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

#include "auto_block.h"
#include "block.h"
#include "geometry.h"
#include "test_utils.h"
#include "test_sheaves.impl.h"
#include "d_tree_point_locator_node.h"
#include "d_bounding_box.h"
#include "db0_point_locator.h"
#include "singly_linked_list.h"

using namespace std;
using namespace geometry;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // d_bounding_box<1, 0> 

  print_header("Begin testing block<d_bounding_box<1, 0> >");
  ltest &= test_block_facet<d_bounding_box<1, 0> >();
  ltest &= test_block_facet_equal<d_bounding_box<1, 0> >();
  ltest &= test_block_facet_insertion<d_bounding_box<1, 0> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<1, 0> >();
  print_footer("End testing block<d_bounding_box<1, 0> >");

  // d_bounding_box<1, 1> 

  print_header("Begin testing block<d_bounding_box<1, 1> >");
  ltest &= test_block_facet<d_bounding_box<1, 1> >();
  ltest &= test_block_facet_equal<d_bounding_box<1, 1> >();
  ltest &= test_block_facet_insertion<d_bounding_box<1, 1> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<1, 1> >();
  print_footer("End testing block<d_bounding_box<1, 1> >");

  // d_bounding_box<2, 0> 

  print_header("Begin testing block<d_bounding_box<2, 0> >");
  ltest &= test_block_facet<d_bounding_box<2, 0> >();
  ltest &= test_block_facet_equal<d_bounding_box<2, 0> >();
  ltest &= test_block_facet_insertion<d_bounding_box<2, 0> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<2, 0> >();
  print_footer("End testing block<d_bounding_box<2, 0> >");

  // d_bounding_box<2, 2> 

  print_header("Begin testing block<d_bounding_box<2, 2> >");
  ltest &= test_block_facet<d_bounding_box<2, 2> >();
  ltest &= test_block_facet_equal<d_bounding_box<2, 2> >();
  ltest &= test_block_facet_insertion<d_bounding_box<2, 2> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<2, 2> >();
  print_footer("End testing block<d_bounding_box<2, 2> >");

  // d_bounding_box<3, 0> 

  print_header("Begin testing block<d_bounding_box<3, 0> >");
  ltest &= test_block_facet<d_bounding_box<3, 0> >();
  ltest &= test_block_facet_equal<d_bounding_box<3, 0> >();
  ltest &= test_block_facet_insertion<d_bounding_box<3, 0> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<3, 0> >();
  print_footer("End testing block<d_bounding_box<3, 0> >");

  // d_bounding_box<3, 1> 

  print_header("Begin testing block<d_bounding_box<3, 1> >");
  ltest &= test_block_facet<d_bounding_box<3, 1> >();
  ltest &= test_block_facet_equal<d_bounding_box<3, 1> >();
  ltest &= test_block_facet_insertion<d_bounding_box<3, 1> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<3, 1> >();
  print_footer("End testing block<d_bounding_box<3, 1> >");

  // d_bounding_box<3, 2> 

  print_header("Begin testing block<d_bounding_box<3, 2> >");
  ltest &= test_block_facet<d_bounding_box<3, 2> >();
  ltest &= test_block_facet_equal<d_bounding_box<3, 2> >();
  ltest &= test_block_facet_insertion<d_bounding_box<3, 2> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<3, 2> >();
  print_footer("End testing block<d_bounding_box<3, 2> >");

  // d_bounding_box<3, 3> 

  print_header("Begin testing block<d_bounding_box<3, 3> >");
  ltest &= test_block_facet<d_bounding_box<3, 3> >();
  ltest &= test_block_facet_equal<d_bounding_box<3, 3> >();
  ltest &= test_block_facet_insertion<d_bounding_box<3, 3> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<3, 3> >();
  print_footer("End testing block<d_bounding_box<3, 3> >");

  // d_bounding_box<4, 4> 

  print_header("Begin testing block<d_bounding_box<4, 4> >");
  ltest &= test_block_facet<d_bounding_box<4, 4> >();
  ltest &= test_block_facet_equal<d_bounding_box<4, 4> >();
  ltest &= test_block_facet_insertion<d_bounding_box<4, 4> >();
  //ltest &= test_block_facet_deep_size<d_bounding_box<4, 4> >();
  print_footer("End testing block<d_bounding_box<4, 4> >");

  // d_bounding_box<1, 0> const*

  print_header("Begin testing block<d_bounding_box<1, 0> const*>");
  ltest &= test_block_facet<d_bounding_box<1, 0> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<1, 0> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<1, 0> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<1, 0> const*>();
  print_footer("End testing block<d_bounding_box<1, 0> const*>");

  // d_bounding_box<1, 1> const*

  print_header("Begin testing block<d_bounding_box<1, 1> const*>");
  ltest &= test_block_facet<d_bounding_box<1, 1> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<1, 1> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<1, 1> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<1, 1> const*>();
  print_footer("End testing block<d_bounding_box<1, 1> const*>");

  // d_bounding_box<2, 0> const*

  print_header("Begin testing block<d_bounding_box<2, 0> const*>");
  ltest &= test_block_facet<d_bounding_box<2, 0> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<2, 0> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<2, 0> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<2, 0> const*>();
  print_footer("End testing block<d_bounding_box<2, 0> const*>");

  // d_bounding_box<2, 2> const*

  print_header("Begin testing block<d_bounding_box<2, 2> const*>");
  ltest &= test_block_facet<d_bounding_box<2, 2> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<2, 2> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<2, 2> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<2, 2> const*>();
  print_footer("End testing block<d_bounding_box<2, 2> const*>");

  // d_bounding_box<3, 0> const*

  print_header("Begin testing block<d_bounding_box<3, 0> const*>");
  ltest &= test_block_facet<d_bounding_box<3, 0> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<3, 0> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<3, 0> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<3, 0> const*>();
  print_footer("End testing block<d_bounding_box<3, 0> const*>");

  // d_bounding_box<3, 1> const*

  print_header("Begin testing block<d_bounding_box<3, 1> const*>");
  ltest &= test_block_facet<d_bounding_box<3, 1> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<3, 1> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<3, 1> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<3, 1> const*>();
  print_footer("End testing block<d_bounding_box<3, 1> const*>");

  // d_bounding_box<3, 2> const*

  print_header("Begin testing block<d_bounding_box<3, 2> const*>");
  ltest &= test_block_facet<d_bounding_box<3, 2> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<3, 2> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<3, 2> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<3, 2> const*>();
  print_footer("End testing block<d_bounding_box<3, 2> const*>");

  // d_bounding_box<3, 3> const*

  print_header("Begin testing block<d_bounding_box<3, 3> const*>");
  ltest &= test_block_facet<d_bounding_box<3, 3> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<3, 3> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<3, 3> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<3, 3> const*>();
  print_footer("End testing block<d_bounding_box<3, 3> const*>");

  // d_bounding_box<4, 4> const*

  print_header("Begin testing block<d_bounding_box<4, 4> const*>");
  ltest &= test_block_facet<d_bounding_box<4, 4> const*>();
  ltest &= test_block_facet_equal<d_bounding_box<4, 4> const*>();
  ltest &= test_block_facet_insertion<d_bounding_box<4, 4> const*>();
  //ltest &= test_block_facet_deep_size<d_bounding_box<4, 4> const*>();
  print_footer("End testing block<d_bounding_box<4, 4> const*>");

  //============================================================================

  // singly_linked_list<d_bounding_box<1, 0> const*> 

  print_header("Begin testing block<singly_linked_list<d_bounding_box<1, 0> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<1, 0> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<1, 0> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<1, 0> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<1, 0> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<1, 0> const*> >");

  // singly_linked_list<d_bounding_box<1, 1> const*>

  print_header("Begin testing block<singly_linked_list<d_bounding_box<1, 1> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<1, 1> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<1, 1> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<1, 1> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<1, 1> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<1, 1> const*> >");

  // singly_linked_list<d_bounding_box<2, 0> const*> 

  print_header("Begin testing block<singly_linked_list<d_bounding_box<2, 0> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<2, 0> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<2, 0> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<2, 0> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<2, 0> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<2, 0> const*> >");

  // singly_linked_list<d_bounding_box<2, 2> const*> 

  print_header("Begin testing block<singly_linked_list<d_bounding_box<2, 2> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<2, 2> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<2, 2> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<2, 2> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<2, 2> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<2, 2> const*> >");

  // singly_linked_list<d_bounding_box<3, 0> const*> 

  print_header("Begin testing block<singly_linked_list<d_bounding_box<3, 0> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<3, 0> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<3, 0> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<3, 0> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<3, 0> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<3, 0> const*> >");

  // singly_linked_list<d_bounding_box<3, 1> const*> 

  print_header("Begin testing block<singly_linked_list<d_bounding_box<3, 1> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<3, 1> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<3, 1> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<3, 1> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<3, 1> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<3, 1> const*> >");

  // singly_linked_list<d_bounding_box<3, 2> const*> 

  print_header("Begin testing block<singly_linked_list<d_bounding_box<3, 2> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<3, 2> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<3, 2> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<3, 2> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<3, 2> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<3, 2> const*> >");

  // singly_linked_list<d_bounding_box<3, 3> const*> 

  print_header("Begin testing block<singly_linked_list<d_bounding_box<3, 3> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<3, 3> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<3, 3> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<3, 3> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<3, 3> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<3, 3> const*> >");

  // singly_linked_list<d_bounding_box<4, 4> const*> 

  print_header("Begin testing block<singly_linked_list<d_bounding_box<4, 4> const*> >");
  ltest &= test_block_facet<singly_linked_list<d_bounding_box<4, 4> const*> >();
  //ltest &= test_block_facet_equal<singly_linked_list<d_bounding_box<4, 4> const*> >();
  //ltest &= test_block_facet_insertion<singly_linked_list<d_bounding_box<4, 4> const*> >();
  //ltest &= test_block_facet_deep_size<singly_linked_list<d_bounding_box<4, 4> const*> >();
  print_footer("End testing block<singly_linked_list<d_bounding_box<4, 4> const*> >");

  //============================================================================

  // d_tree_point_locator_node<1, 1> 

  print_header("Begin testing block<d_tree_point_locator_node<1, 1> >");
  ltest &= test_block_facet<d_tree_point_locator_node<1, 1> >();
  ltest &= test_block_facet_equal<d_tree_point_locator_node<1, 1> >();
  ltest &= test_block_facet_insertion<d_tree_point_locator_node<1, 1> >();
  //ltest &= test_block_facet_deep_size<d_tree_point_locator_node<1, 1> >();
  print_footer("End testing block<d_tree_point_locator_node<1, 1> >");

  // d_tree_point_locator_node<2, 2> 

  print_header("Begin testing block<d_tree_point_locator_node<2, 2> >");
  ltest &= test_block_facet<d_tree_point_locator_node<2, 2> >();
  ltest &= test_block_facet_equal<d_tree_point_locator_node<2, 2> >();
  ltest &= test_block_facet_insertion<d_tree_point_locator_node<2, 2> >();
  //ltest &= test_block_facet_deep_size<d_tree_point_locator_node<2, 2> >();
  print_footer("End testing block<d_tree_point_locator_node<2, 2> >");

  // d_tree_point_locator_node<3, 3> 

  print_header("Begin testing block<d_tree_point_locator_node<3, 3> >");
  ltest &= test_block_facet<d_tree_point_locator_node<3, 3> >();
  ltest &= test_block_facet_equal<d_tree_point_locator_node<3, 3> >();
  ltest &= test_block_facet_insertion<d_tree_point_locator_node<3, 3> >();
  //ltest &= test_block_facet_deep_size<d_tree_point_locator_node<3, 3> >();
  print_footer("End testing block<d_tree_point_locator_node<3, 3> >");

//   // d_tree_point_locator_node<4, 4> not instantiated

//   print_header("Begin testing block<d_tree_point_locator_node<4, 4> >");
//   ltest &= test_block_facet<d_tree_point_locator_node<4, 4> >();
//   ltest &= test_block_facet_equal<d_tree_point_locator_node<4, 4> >();
//   ltest &= test_block_facet_insertion<d_tree_point_locator_node<4, 4> >();
//   //ltest &= test_block_facet_deep_size<d_tree_point_locator_node<4, 4> >();
//   print_footer("End testing block<d_tree_point_locator_node<4, 4> >");

  //============================================================================

  //$$SCRIBBLE: db0_point_locator<DC>::vertex_type is protected.

  // singly_linked_list<geometry::db0_point_locator<1>::vertex_type>

//   print_header("Begin testing block<singly_linked_list<db0_point_locator<1>::vertex_type> >");
//   //ltest &= test_block_facet<singly_linked_list<db0_point_locator<1>::vertex_type> >();
//   //ltest &= test_block_facet_equal<singly_linked_list<db0_point_locator<1>::vertex_type> >();
//   //ltest &= test_block_facet_insertion<singly_linked_list<db0_point_locator<1>::vertex_type> >();
//   //ltest &= test_block_facet_deep_size<singly_linked_list<db0_point_locator<1>::vertex_type >();
//   print_footer("End testing block<singly_linked_list<db0_point_locator<1>::vertex_type> >");

//   // singly_linked_list<geometry::db0_point_locator<2>::vertex_type>

//   print_header("Begin testing block<singly_linked_list<db0_point_locator<2>::vertex_type> >");
//   //ltest &= test_block_facet<singly_linked_list<db0_point_locator<2>::vertex_type> >();
//   //ltest &= test_block_facet_equal<singly_linked_list<db0_point_locator<2>::vertex_type> >();
//   //ltest &= test_block_facet_insertion<singly_linked_list<db0_point_locator<2>::vertex_type> >();
//   //ltest &= test_block_facet_deep_size<singly_linked_list<db0_point_locator<2>::vertex_type >();
//   print_footer("End testing block<singly_linked_list<db0_point_locator<2>::vertex_type> >");

//   // singly_linked_list<geometry::db0_point_locator<3>::vertex_type>

//   print_header("Begin testing block<singly_linked_list<db0_point_locator<3>::vertex_type> >");
//   //ltest &= test_block_facet<singly_linked_list<db0_point_locator<3>::vertex_type> >();
//   //ltest &= test_block_facet_equal<singly_linked_list<db0_point_locator<3>::vertex_type> >();
//   //ltest &= test_block_facet_insertion<singly_linked_list<db0_point_locator<3>::vertex_type> >();
//   //ltest &= test_block_facet_deep_size<singly_linked_list<db0_point_locator<3>::vertex_type >();
//   print_footer("End testing block<singly_linked_list<db0_point_locator<3>::vertex_type> >");

  //============================================================================

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
