// $RCSfile: depth_first_itr.inst.t.cc,v $ $Revision: 1.1.2.3 $ $Date: 2012/11/16 00:14:31 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example template_instantiations/depth_first_itr.inst.t.cc
/// Unit test driver for template class depth_first_itr.

#include "depth_first_itr.h"

#include "namespace_poset.h"
#include "test_sheaves.impl.h"
#include "test_utils.h"

using namespace sheaf;


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing depth_first_itr ...");

  bool ltest = true;

  //============================================================================

  //$$SCRIBBLE: Nothing here yet. depth_first_itr cannot be instantiated because
  //            all of it's constructors are protected. We can, however,
  //            create filtered_depth_first_itr instances which can be used
  //            to test the depth_first_itr facet
  //            (see filtered_depth_first_itr.inst.t.cc).

  //============================================================================

  print_footer("End testing depth_first_itr ...");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

