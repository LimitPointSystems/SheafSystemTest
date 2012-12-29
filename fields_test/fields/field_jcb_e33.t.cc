
// $RCSfile: field_jcb_e33.t.cc,v $ $Revision: 1.5 $ $Date: 2012/03/01 00:41:04 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example field_jcb_e33.t.cc
/// Test driver for class field_jcb_e33.


#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "field_jcb_e33.h"
#include "storage_agent.h"
#include "test_fields.impl.h"

#include "jcb_e33.h"
#include "sec_jcb_e33.h"
#include "sec_jcb_space.h"

using namespace fields;

///
int
main()
{
  // Preconditions:

  // Body:

  const string& field_name = field_jcb_e33::static_class_name();
  print_header("Testing " + field_name);

  // Create the namespace.

  fiber_bundles_namespace lns(field_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;
  size_type k_size = 2;

  const poset_path& lbase_path =
    make_test_base_space(lns, i_size, j_size, k_size);

  // Create the coordinates section.

  const poset_path& lcoords_path = make_test_coordinates_3d(lns, lbase_path);

  // Run tests.

  // Test assignment:

  typedef field_jcb_e33 field_type;
  typedef typename field_type::property_section_type sec_type;
  typedef typename sec_type::fiber_type fiber_type;
  typedef typename fiber_type::volatile_type volatile_type;

  cout << "field_type    = " << field_type::static_class_name() << endl;
  cout << "sec_type      = " << sec_type::static_class_name() << endl;
  cout << "fiber_type    = " << fiber_type::static_class_name() << endl;
  cout << "volatile_type = " << volatile_type::static_class_name() << endl;

  cout << "sec_type::host_type = "
       << sec_type::host_type::static_class_name() << endl;


//   test_field_assignment<field_jcb_e33>(lns, lbase_path, lcoords_path);

  // Test vd facet:

  //@issue What does it mean to test the vd facet for jacobians?
  //       They do derive from field_vd and therefore should pass
  //       the vd facet tests.

//   test_field_vd_facet<field_jcb_e33>(lns, lbase_path, lcoords_path);

//   // Test jcb facet:

//   test_field_jcb_facet<field_jcb_e33, field_e3, field_e3>
//     (lns, lbase_path, lcoords_path);

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(field_name + ".t.hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
