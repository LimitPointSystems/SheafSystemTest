
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example sec_st4_e3.t.cc
/// Unit test for class sec_st4_e3.

#include "sec_st4_e3.h"

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

  print_header("Begin testing sec_st4_e3");

  string lfilename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;
  size_type k_size = 2;

  const poset_path& lbase_path =
    make_test_base_space(lns, i_size, j_size, k_size);

  // Run tests.

  // Test assignment:

  test_assignment<sec_st4_e3>(lns, lbase_path);

  // Test vd facet:

  test_sec_vd_facet<sec_st4_e3>(lns, lbase_path);

  //test_sec_stp<sec_st4_e3,...>(lns, lbase_path);

  //============================================================================

  test_section_common_unattached<sec_st4_e3>();
  test_section_common_attached_2<sec_st4_e3>(lns, lbase_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(lfilename + ".t.hdf");
  write_agent.write_entire(lns);

  print_footer("Ending testing sec_st4_e3");

  // Postconditions:

  // Exit:

  return 0;
}

