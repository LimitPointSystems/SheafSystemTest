

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test for class sec_met.

#include "sec_met.h"
#include "sec_met_e2.h"

#include "fiber_bundles_namespace.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;


int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_met");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_met>();
  test_section_common_attached<sec_met, sec_met_e2>(lns, 2);

  //============================================================================

  print_footer("Ending testing sec_met");

  // Postconditions:

  // Exit:

  return 0;
}

