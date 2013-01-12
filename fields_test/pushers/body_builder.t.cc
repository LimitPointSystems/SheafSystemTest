
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example body_builder.t.cc

/// @file
/// Test driver for class body_builder.

#include "assert_contract.h"
#include "body_factory.h"
#include "fiber_bundles_namespace.h"
#include "section_space_schema_poset.h"
#include "std_iostream.h"

using namespace fields;

///
/// Main routine.
///
int main(int argc, char* argv[])
{
  fiber_bundles_namespace lns("body_builder.t");
  lns.get_read_write_access();

  body_factory::new_1d_unstructured_bodies(lns, "test");
  body_factory::new_1d_uniform_bodies(lns, "test");

  body_factory::new_2d_unstructured_bodies(lns, "test");
  body_factory::new_2d_uniform_bodies(lns, "test");

  body_factory::new_3d_unstructured_bodies(lns, "test");
  body_factory::new_3d_uniform_bodies(lns, "test");

  cout << lns << endl;

  return 0;
}
