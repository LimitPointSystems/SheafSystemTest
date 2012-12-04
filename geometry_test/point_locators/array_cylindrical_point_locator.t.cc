// $RCSfile: array_cylindrical_point_locator.t.cc,v $ $Revision: 1.1.2.4 $ $Date: 2012/10/24 02:00:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for class array_cylindrical_point_locator.

#include "array_cylindrical_point_locator.h"

#include "test_utils.h"

using namespace geometry;

namespace
{

bool
test_array_cylindrical_point_locator_facet()
{
  // Preconditions:

  // Body:

  // Need sec_ed xcoords.

  // array_cylindrical_point_locator(sec_ed& xcoords);

  // array_cylindrical_point_locator(sec_ed& xcoords, const block<size_type>& xbin_ub);

  // Postconditions:

  // Exit:

  return true;
}

} //end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing array_cylindrical_point_locator facet:");

  bool ltest = true;

  //============================================================================

  ltest &= test_array_cylindrical_point_locator_facet();

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_header("Begin testing array_cylindrical_point_locator facet:");

  // Postconditions:

  // Exit:

  return lresult;
}
