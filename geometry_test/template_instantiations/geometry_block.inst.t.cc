// $RCSfile: geometry_block.inst.t.cc,v $ $Revision: 1.1.2.4 $ $Date: 2012/10/24 02:00:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class block.

#include "auto_block.impl.h"
#include "block.impl.h"
#include "geometry.h"
#include "test_utils.h"
#include "test_sheaves.impl.h"
#include "d_tree_point_locator_node.impl.h"
#include "d_bounding_box.impl.h"
#include "db0_point_locator.impl.h"
#include "kd_plane.h"
#include "kd_bounding_box.h"
#include "std_slist.h"

using namespace geometry;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  //============================================================================

  // kd_plane:

  print_header("Begin testing block<kd_plane>");
  ltest &= test_block_facet<kd_plane>();
  ltest &= test_block_facet_equal<kd_plane>();
  ltest &= test_block_facet_insertion<kd_plane>();
  //ltest &= test_block_facet_deep_size<kd_plane>();
  print_footer("End testing block<kd_plane>");

  // kd_bounding_box:

  print_header("Begin testing block<kd_bounding_box>");
  ltest &= test_block_facet<kd_bounding_box>();
  ltest &= test_block_facet_equal<kd_bounding_box>();
  ltest &= test_block_facet_insertion<kd_bounding_box>();
  //ltest &= test_block_facet_deep_size<kd_bounding_box>();
  print_footer("End testing block<kd_bounding_box>");

  //============================================================================

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

  // slist<d_bounding_box<1, 0> const*> 

  print_header("Begin testing block<slist<d_bounding_box<1, 0> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<1, 0> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<1, 0> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<1, 0> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<1, 0> const*> >();
  print_footer("End testing block<slist<d_bounding_box<1, 0> const*> >");

  // slist<d_bounding_box<1, 1> const*>

  print_header("Begin testing block<slist<d_bounding_box<1, 1> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<1, 1> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<1, 1> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<1, 1> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<1, 1> const*> >();
  print_footer("End testing block<slist<d_bounding_box<1, 1> const*> >");

  // slist<d_bounding_box<2, 0> const*> 

  print_header("Begin testing block<slist<d_bounding_box<2, 0> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<2, 0> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<2, 0> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<2, 0> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<2, 0> const*> >();
  print_footer("End testing block<slist<d_bounding_box<2, 0> const*> >");

  // slist<d_bounding_box<2, 2> const*> 

  print_header("Begin testing block<slist<d_bounding_box<2, 2> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<2, 2> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<2, 2> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<2, 2> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<2, 2> const*> >();
  print_footer("End testing block<slist<d_bounding_box<2, 2> const*> >");

  // slist<d_bounding_box<3, 0> const*> 

  print_header("Begin testing block<slist<d_bounding_box<3, 0> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<3, 0> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<3, 0> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<3, 0> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<3, 0> const*> >();
  print_footer("End testing block<slist<d_bounding_box<3, 0> const*> >");

  // slist<d_bounding_box<3, 1> const*> 

  print_header("Begin testing block<slist<d_bounding_box<3, 1> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<3, 1> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<3, 1> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<3, 1> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<3, 1> const*> >();
  print_footer("End testing block<slist<d_bounding_box<3, 1> const*> >");

  // slist<d_bounding_box<3, 2> const*> 

  print_header("Begin testing block<slist<d_bounding_box<3, 2> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<3, 2> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<3, 2> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<3, 2> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<3, 2> const*> >();
  print_footer("End testing block<slist<d_bounding_box<3, 2> const*> >");

  // slist<d_bounding_box<3, 3> const*> 

  print_header("Begin testing block<slist<d_bounding_box<3, 3> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<3, 3> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<3, 3> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<3, 3> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<3, 3> const*> >();
  print_footer("End testing block<slist<d_bounding_box<3, 3> const*> >");

  // slist<d_bounding_box<4, 4> const*> 

  print_header("Begin testing block<slist<d_bounding_box<4, 4> const*> >");
  ltest &= test_block_facet<slist<d_bounding_box<4, 4> const*> >();
  //ltest &= test_block_facet_equal<slist<d_bounding_box<4, 4> const*> >();
  //ltest &= test_block_facet_insertion<slist<d_bounding_box<4, 4> const*> >();
  //ltest &= test_block_facet_deep_size<slist<d_bounding_box<4, 4> const*> >();
  print_footer("End testing block<slist<d_bounding_box<4, 4> const*> >");

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

  // d_tree_point_locator_node<4, 4> 

  print_header("Begin testing block<d_tree_point_locator_node<4, 4> >");
  ltest &= test_block_facet<d_tree_point_locator_node<4, 4> >();
  ltest &= test_block_facet_equal<d_tree_point_locator_node<4, 4> >();
  ltest &= test_block_facet_insertion<d_tree_point_locator_node<4, 4> >();
  //ltest &= test_block_facet_deep_size<d_tree_point_locator_node<4, 4> >();
  print_footer("End testing block<d_tree_point_locator_node<4, 4> >");

  //============================================================================

  //$$SCRIBBLE: db0_point_locator<DC>::vertex_type is protected.

  // slist<geometry::db0_point_locator<1>::vertex_type>

//   print_header("Begin testing block<slist<db0_point_locator<1>::vertex_type> >");
//   //ltest &= test_block_facet<slist<db0_point_locator<1>::vertex_type> >();
//   //ltest &= test_block_facet_equal<slist<db0_point_locator<1>::vertex_type> >();
//   //ltest &= test_block_facet_insertion<slist<db0_point_locator<1>::vertex_type> >();
//   //ltest &= test_block_facet_deep_size<slist<db0_point_locator<1>::vertex_type >();
//   print_footer("End testing block<slist<db0_point_locator<1>::vertex_type> >");

//   // slist<geometry::db0_point_locator<2>::vertex_type>

//   print_header("Begin testing block<slist<db0_point_locator<2>::vertex_type> >");
//   //ltest &= test_block_facet<slist<db0_point_locator<2>::vertex_type> >();
//   //ltest &= test_block_facet_equal<slist<db0_point_locator<2>::vertex_type> >();
//   //ltest &= test_block_facet_insertion<slist<db0_point_locator<2>::vertex_type> >();
//   //ltest &= test_block_facet_deep_size<slist<db0_point_locator<2>::vertex_type >();
//   print_footer("End testing block<slist<db0_point_locator<2>::vertex_type> >");

//   // slist<geometry::db0_point_locator<3>::vertex_type>

//   print_header("Begin testing block<slist<db0_point_locator<3>::vertex_type> >");
//   //ltest &= test_block_facet<slist<db0_point_locator<3>::vertex_type> >();
//   //ltest &= test_block_facet_equal<slist<db0_point_locator<3>::vertex_type> >();
//   //ltest &= test_block_facet_insertion<slist<db0_point_locator<3>::vertex_type> >();
//   //ltest &= test_block_facet_deep_size<slist<db0_point_locator<3>::vertex_type >();
//   print_footer("End testing block<slist<db0_point_locator<3>::vertex_type> >");

  //============================================================================

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

/*
block<geometry::d_bounding_box<1, 0> >
block<geometry::d_bounding_box<1, 1> >
block<geometry::d_bounding_box<2, 0> >
block<geometry::d_bounding_box<2, 2> >
block<geometry::d_bounding_box<3, 0> >
block<geometry::d_bounding_box<3, 1> >
block<geometry::d_bounding_box<3, 2> >
block<geometry::d_bounding_box<3, 3> >
block<geometry::d_bounding_box<4, 4> >
block<geometry::kd_bounding_box>
block<geometry::d_tree_point_locator_node<1, 1> >
block<geometry::d_tree_point_locator_node<2, 2> >
block<geometry::d_tree_point_locator_node<3, 3> >
block<geometry::d_tree_point_locator_node<4, 4> >
block<geometry::kd_plane>

block<__gnu_cxx::slist<geometry::d_bounding_box<1, 0> const*, std::allocator<geometry::d_bounding_box<1, 0> const*> > >
block<__gnu_cxx::slist<geometry::d_bounding_box<1, 1> const*, std::allocator<geometry::d_bounding_box<1, 1> const*> > >
block<__gnu_cxx::slist<geometry::d_bounding_box<2, 0> const*, std::allocator<geometry::d_bounding_box<2, 0> const*> > >
block<__gnu_cxx::slist<geometry::d_bounding_box<2, 2> const*, std::allocator<geometry::d_bounding_box<2, 2> const*> > >
block<__gnu_cxx::slist<geometry::d_bounding_box<3, 0> const*, std::allocator<geometry::d_bounding_box<3, 0> const*> > >
block<__gnu_cxx::slist<geometry::d_bounding_box<3, 1> const*, std::allocator<geometry::d_bounding_box<3, 1> const*> > >
block<__gnu_cxx::slist<geometry::d_bounding_box<3, 2> const*, std::allocator<geometry::d_bounding_box<3, 2> const*> > >
block<__gnu_cxx::slist<geometry::d_bounding_box<3, 3> const*, std::allocator<geometry::d_bounding_box<3, 3> const*> > >
block<__gnu_cxx::slist<geometry::d_bounding_box<4, 4> const*, std::allocator<geometry::d_bounding_box<4, 4> const*> > >

block<__gnu_cxx::slist<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> > >
block<__gnu_cxx::slist<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> > >
block<__gnu_cxx::slist<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> > >



*/
