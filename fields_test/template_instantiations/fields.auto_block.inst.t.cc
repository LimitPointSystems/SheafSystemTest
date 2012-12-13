// $RCSfile: fields_auto_block.inst.t.cc,v $ $Revision: 1.1.2.3 $ $Date: 2012/10/24 02:01:06 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class auto_block.

#include "auto_block.impl.h"

//#include "block.impl.h"
#include "fields.h"

#include "barycentric_refiner_family.h"
#include "edge_centered_polygon_refiner.h"
#include "edge_centered_refiner_family.h"
#include "local_field_refiner.h"
#include "zone_centered_refiner_family.h"
#include "zone_centered_segment_refiner.h"
#include "zone_centered_tet_refiner.h"
#include "zone_centered_triangle_refiner.h"
#include "pullback_map.h"

#include "test_utils.h"
#include "test_sheaves.impl.h"

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

