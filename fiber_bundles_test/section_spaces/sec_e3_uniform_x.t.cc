
// $RCSfile: sec_e3_uniform_x.t.cc,v $ $Revision: 1.11 $ $Date: 2012/03/01 00:40:54 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test for class sec_e3_uniform.

#include "sec_e3_uniform.h"

#include "fiber_bundles_namespace.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;

int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_e3_uniform");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_e3_uniform>();
  test_section_common_attached<sec_e3_uniform>(lns, 3);

  //============================================================================

  print_footer("Ending testing sec_e3_uniform");

  // Postconditions:

  // Exit:

  return 0;
}

