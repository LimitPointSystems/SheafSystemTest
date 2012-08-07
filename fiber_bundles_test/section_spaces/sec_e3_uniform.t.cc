
// $RCSfile: sec_e3_uniform.t.cc,v $ $Revision: 1.11 $ $Date: 2012/03/01 00:40:55 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example section_spaces/sec_e3_uniform.t.cc
/// Unit test for class sec_e3_uniform.

#include "assert_contract.h"
#include "sec_e3_uniform.h"
#include "std_iostream.h"
#include "test_sections.impl.h"
#include "wsv_block.h"

using namespace fiber_bundle;

int main(int argc, char* argv[])
{
  // Preconditions:

  // Body:

  size_t i_size = 2;
  if (argc > 1)
    i_size = atoi(argv[1]);

  size_t j_size = 3;
  if (argc > 2)
    j_size = atoi(argv[2]);

  size_t k_size = 4;
  if (argc > 3)
    k_size = atoi(argv[3]);

  const string& section_name = sec_e3_uniform::static_class_name();

  print_sec_header("Testing " + section_name);

  // Create the namespace.

  fiber_bundles_namespace lns(section_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(lns, i_size, j_size, k_size);

  // Make the section space.

  sec_e3_uniform::host_type& lhost =
    new_host_space<sec_e3_uniform>(lns, "uniform_coordinates_host", lbase_path);
  
  // Make the section.

  wsv_block<sec_vd_dof_type> llower("-2.0 -3.0 -4.0");
  wsv_block<sec_vd_dof_type> lupper("2.0 3.0 4.0");

  sec_e3_uniform lcoords(&lhost, llower, lupper, true);
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

