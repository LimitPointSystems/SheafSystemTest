// $RCSfile: d_tree_point_locator_path.inst.t.cc,v $ $Revision: 1.1.2.4 $ $Date: 2012/10/24 02:00:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for class d_tree_point_locator_path.

#include "d_tree_point_locator_path.h"

#include "geometry.h"
#include "test_utils.h"

using namespace geometry;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing d_tree_point_locator_path_facet<???>:");

  bool ltest = true;

  //============================================================================

  //$$SCRIBBLE: We test d_tree_point_locator_path in d_tree_point_locator.inst.t
  //            because we need a d_tree_point_locator to instantiate a
  //            d_tree_point_locator_path and we already create them there.

  cout << "d_tree_point_locator_path is tested in d_tree_point_locator.inst.t"
       << endl;

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing d_tree_point_locator_path_facet<???>:");

  // Postconditions:

  // Exit:

  return lresult;
}
