
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example sec_e1.t.cc
/// Unit test for class e1.

#include "sec_e1.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "storage_agent.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;

int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  string lfilename = filename_from_cmdline(*xargv);

  //print_header("Testing " + lfilename);
  print_header("Begin testing sec_e1");

  // Create the namespace.

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();


  // Make a base space.

  size_type i_size = 2;

  const poset_path& lbase_path = make_test_base_space(lns, i_size);

  // Run tests.

  // Test assignment:

  test_assignment<sec_e1>(lns, lbase_path);

  // Test vd facet:

  test_sec_vd_facet<sec_e1>(lns, lbase_path);

  // Test ed facet:

  test_sec_ed_facet<sec_e1>(lns, lbase_path);

  //============================================================================

  test_section_common_unattached<sec_e1>();
  test_section_common_attached<sec_e1>(lns, lbase_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(lfilename + ".hdf");
  write_agent.write_entire(lns);

  print_footer("Ending testing sec_e1");

  // Postconditions:

  // Exit:

  return 0;
}

