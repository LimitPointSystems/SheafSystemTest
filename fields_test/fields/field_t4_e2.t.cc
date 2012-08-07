
// $RCSfile: field_t4_e2.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:05 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example field_t4_e2.t.cc
/// Test driver for class field_t4_e2.

#include "assert_contract.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "field_t4_e2.h"
#include "field_st4_e2.h"
#include "sec_at1_space.h"
#include "sec_t4_e2.h"
#include "storage_agent.h"
#include "sec_stp_space.h"
#include "test_fields.impl.h"

using namespace fields;

///
int
main()
{
  // Preconditions:

  // Body:

  const string& field_name = field_t4_e2::static_class_name();
  print_field_header("Testing " + field_name);

  // Create the namespace.

  fiber_bundles_namespace lns(field_name + ".t");
  lns.get_read_write_access();

  size_type i_size = 2;
  size_type j_size = 2;

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(lns, i_size, j_size);

  // Create the coordinates section.

  const poset_path& lcoords_path = make_test_coordinates_2d(lns, lbase_path);

  // Run tests.

  // Test assignment:

  test_field_assignment<field_t4_e2>(lns, lbase_path, lcoords_path);

  // Test vd facet:

  test_field_vd_facet<field_t4_e2>(lns, lbase_path, lcoords_path);

  // Test alt and sym functions of the tp facet:

//   test_field_tp_facet<field_t4_e2, field_at4_e2, field_st4_e2>
//     (lns, lbase_path, lcoords_path);

//   test_field_tensor_product<field_t3_e2, field_e2, field_t4_e2>
//     (lns, lbase_path, lcoords_path);

//   test_field_tensor_product<field_at3_e2, field_e2, field_t4_e2>
//     (lns, lbase_path, lcoords_path);

//   test_field_tensor_product<field_st3_e2, field_e2, field_t4_e2>
//     (lns, lbase_path, lcoords_path);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(field_name + ".t.hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
