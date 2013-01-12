

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test for class sec_tuple.

#include "sec_tuple.h"
#include "sec_e2.h"

#include "fiber_bundles_namespace.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;


int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_tuple");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_tuple>();
  test_section_common_attached<sec_tuple, sec_e2>(lns, 2);

  //============================================================================

  print_footer("Ending testing sec_tuple");

  // Postconditions:

  // Exit:

  return 0;
}

