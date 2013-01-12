

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test for class sec_st4_e3.

#include "sec_st4_e3.h"

#include "fiber_bundles_namespace.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;


int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_st4_e3");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_st4_e3>();
  test_section_common_attached_2<sec_st4_e3>(lns, 3);

  //============================================================================

  print_footer("Ending testing sec_st4_e3");

  // Postconditions:

  // Exit:

  return 0;
}

