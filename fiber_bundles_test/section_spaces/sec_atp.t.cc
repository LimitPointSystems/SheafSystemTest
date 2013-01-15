
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test for class sec_atp.

#include "sec_atp.h"
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

  print_header("Begin testing sec_atp");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_atp>();
  test_section_common_attached<sec_atp, sec_e1>(lns, 1);

  //============================================================================

  print_footer("Ending testing sec_atp");

  // Postconditions:

  // Exit:

  return 0;
}

