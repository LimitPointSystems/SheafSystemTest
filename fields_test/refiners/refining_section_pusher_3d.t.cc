
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

/// @example refining_section_pusher_3d.t.cc

/// @file
/// Test driver for refining_section_pusher.


#include "ComLimitPoint/sheaf/assert_contract.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "field_factory.h"
#include "fields.h"
#include "sec_ed_invertible.h"
#include "section_dof_iterator.h"
#include "section_pusher.h"
#include "std_iostream.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "field_vd.h"
#include "wsv_block.h"
#include "refining_section_pusher.h"

//#define DIAGNOSTIC_OUTPUT 1

using namespace std;
using namespace fields;
using namespace std;
using namespace fields;

namespace
{

///
/// Step function.
///
void
step_fcn(block<sec_vd_value_type>& xglobal_coords,
         block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  require(xglobal_coords.ct() >= 1);
  require(xproperty_dofs.ct() == 1);

  // Body:

  // Not exactly a step, really a ramp.
  // Test case centers coarse mesh zone on
  // origin of coordinates, so make sure
  // test function not symmetric (or antisymmetric).
  // Otherwise, the error at the center may
  // be unexpectedly small.

  sec_vd_value_type x = xglobal_coords[0];

  if(x < -0.5)
  {
    xproperty_dofs[0] = -1.0;
  }
  else if(x > 0.0)
  {
    xproperty_dofs[0] = 1.0;
  }
  else
  {
    xproperty_dofs[0] = 4.0*x + 1.0;
  }


  // Postconditions:

  // Exit:

  return;
}

///
/// Test fine to coarse push with refinement.
///
void test_fine_to_coarse_with_refinement()
{
  fiber_bundles_namespace lns("refining_section_pusher_3d.t");
  lns.get_read_write_access();

  // An 8x8x8 element hex mesh.
  
  wsv_block<sec_vd_value_type> xlower("-2.0 -2.0 -2.0");
  wsv_block<sec_vd_value_type> xupper("2.0 2.0 2.0");

  field_vd* fine =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "fine",
        8,
        8,
        8,
        true,
        xlower,
        xupper,
        step_fcn);

  // A 2x2x2 element tet mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "coarse",
        2,
        2,
        2,
        false,
        xlower,
        xupper,
        field_factory::zero);

  coarse->print_property_dofs(cout,
                              field_factory::zero,
                              "test_fine_to_coarse_with_refinement: before pushing unstructured fine >>"
                              " unstructured coarse:",
                              true,
                              true);

  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  refining_section_pusher lpusher(*coarse->base_space().host(),
                                  "zone_centered_refiner_family",
                                  "zone_centered_error_bound_refinement_policy",
                                  true);

  lpusher.push(*fine, *coarse, true);

  coarse->print_property_dofs(cout,
                              step_fcn,
                              "test_fine_to_coarse_with_refinement: after pushing unstructured fine hexs >>"
                              " unstructured coarse hexs:",
                              true,
                              true);

  storage_agent sa("refining_section_pusher_3d.t.hdf");
  sa.write_entire(coarse->name_space());
}

} //namespace

///
/// Main routine.
///
int
main(int argc, char* argv[])
{

  // Test refinement.

  test_fine_to_coarse_with_refinement();

  return 0;
}


