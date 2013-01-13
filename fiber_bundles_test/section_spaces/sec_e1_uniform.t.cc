
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example section_spaces/sec_e1_uniform.t.cc
/// Unit test for class sec_e1_uniform.

#include "sec_e1_uniform.h"

#include "assert_contract.h"
#include "std_iostream.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;

int
main(int argc, char* argv[])
{
  // Preconditions:

  // Body:

  typedef sec_e1_uniform S;

  const string& lsection_name = S::static_class_name();

  print_header("Begin testing " + lsection_name);

  size_t i_size = (argc > 1) ? atoi(argv[1]) : 2;

  // Create the namespace.

  fiber_bundles_namespace lns(lsection_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(lns, i_size);

  // Make the section space.

  S::host_type& lhost =
    new_host_space<S>(lns, "uniform_coordinates_host", lbase_path);

  // Make the section.

  S lcoords(&lhost, -1.0, 1.0, true);
  lcoords.put_name("uniform_coordinates", true, true);

  // Print the result.

  //cout << lns << endl;

  // Clean-up

  lcoords.detach_from_state();

  //============================================================================

  test_section_common_unattached<S>();
  test_section_common_attached<S>(lns, lbase_path);

  //============================================================================

  print_footer("End testing " + lsection_name);

  // Postconditions:

  // Exit:

  return 0;
}

