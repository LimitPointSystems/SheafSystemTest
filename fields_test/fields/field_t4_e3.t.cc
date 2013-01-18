
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example field_t4_e3.t.cc
/// Test driver for class field_t4_e3.

#include "assert_contract.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "field_t4_e3.h"
#include "field_st4_e3.h"
#include "sec_at1_space.h"
#include "sec_t4_e3.h"
#include "storage_agent.h"
#include "sec_stp_space.h"
#include "test_fields.impl.h"

using namespace fields;


int
main()
{
  // Preconditions:

  // Body:

  const string& field_name = field_t4_e3::static_class_name();
  print_header("Testing " + field_name);

  // Create the namespace.

  fiber_bundles_namespace lns(field_name + ".t");
  lns.get_read_write_access();

  size_type i_size = 2;
  size_type j_size = 2;
  size_type k_size = 2;

  // Make a base space.

  const poset_path& lbase_path =
    make_test_base_space(lns, i_size, j_size, k_size);

  // Create the coordinates section.

  const poset_path& lcoords_path = make_test_coordinates_3d(lns, lbase_path);

  // Run tests.

  // Test assignment:

  test_field_assignment<field_t4_e3>(lns, lbase_path, lcoords_path);

  // Test vd facet:

  test_field_vd_facet<field_t4_e3>(lns, lbase_path, lcoords_path);

  //============================================================================

  test_field_common<field_t4_e3>(lns, lbase_path, lcoords_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(field_name + ".t.hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
