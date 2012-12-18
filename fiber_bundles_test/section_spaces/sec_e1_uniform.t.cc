
// $RCSfile: sec_e1_uniform.t.cc,v $ $Revision: 1.11 $ $Date: 2012/03/01 00:40:54 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example section_spaces/sec_e1_uniform.t.cc
/// Unit test for class sec_e1_uniform.

#include "assert_contract.h"
#include "sec_e1_uniform.h"
#include "std_iostream.h"
#include "test_sections.impl.h"

using namespace fiber_bundle;

int main(int argc, char* argv[])
{
  // Preconditions:

  // Body:

  size_t i_size = 2;
  if (argc > 1)
    i_size = atoi(argv[1]);

  const string& section_name = sec_e1_uniform::static_class_name();

  print_header("Testing " + section_name);

  // Create the namespace.

  fiber_bundles_namespace lns(section_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(lns, i_size);

  // Make the section space.

  sec_e1_uniform::host_type& lhost =
    new_host_space<sec_e1_uniform>(lns, "uniform_coordinates_host", lbase_path);

  // Make the section.

  sec_e1_uniform lcoords(&lhost, -1.0, 1.0, true);
  lcoords.put_name("uniform_coordinates", true, true);

  // Print the result.

  lns.get_read_access();
  cout << lns << endl;

  // Clean-up

  lns.get_read_write_access(true);
  lcoords.detach_from_state();

  // Postconditions:

  // Exit:

  return 0;
}

