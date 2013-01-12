
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test for class sec_ed.

#include "sec_ed.h"
#include "sec_e1.h"

#include "fiber_bundles_namespace.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;

int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_ed");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_ed>();
  test_section_common_attached<sec_ed, sec_e1>(lns, 1);

  //============================================================================

  print_footer("Ending testing sec_ed");

  // Postconditions:

  // Exit:

  return 0;
}

