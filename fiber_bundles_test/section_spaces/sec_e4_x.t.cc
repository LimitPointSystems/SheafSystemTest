

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test for class sec_e4.

#include "sec_e4.h"

#include "fiber_bundles_namespace.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;

int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_e4");

  //fiber_bundles_namespace lns("test_namespace");
  //lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_e4>();
  //test_section_common_attached<sec_e4>(lns, 4);  // No 4d base space.

  //============================================================================

  print_footer("Ending testing sec_e4");

  // Postconditions:

  // Exit:

  return 0;
}

