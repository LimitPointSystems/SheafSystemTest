
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test for class sec_tp.

#include "sec_tp.h"
#include "sec_t2_e2.h"

#include "fiber_bundles_namespace.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;


int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_tp");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_tp>();
  test_section_common_attached<sec_tp, sec_t2_e2>(lns, 2);

  //============================================================================

  print_footer("Ending testing sec_tp");

  // Postconditions:

  // Exit:

  return 0;
}

