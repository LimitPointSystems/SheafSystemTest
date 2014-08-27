
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @example body_builder.t.cc

/// @file
/// Test driver for class body_builder.

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "body_factory.h"
#include "fiber_bundles_namespace.h"
#include "section_space_schema_poset.h"
#include "std_iostream.h"

using namespace std;
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
