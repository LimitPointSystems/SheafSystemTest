
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
/// @example field_refiner.t.cc

/// @file
/// Test driver for field_refiner.


#include "assert_contract.h"
#include "base_space_member.h"
#include "base_space_poset.h"
#include "depth_bound_refinement_policy.h"
#include "fields.h"
#include "fiber_bundles_namespace.h"
#include "field_factory.h"
#include "field_refiner_family.h"
#include "field_refiner.h"
#include "sec_ed_invertible.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "field_vd.h"
#include "wsv_block.h"

//#define DIAGNOSTIC_OUTPUT 1

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
/// Test 1d refinement.
///
void test_1d_refinement(fiber_bundles_namespace& xns)
{
  wsv_block<sec_vd_value_type> xlower("-2.0");
  wsv_block<sec_vd_value_type> xupper("2.0");

  // An 3 element fine mesh with xmin = -2.0 and xmax = 2.0,
  // with a step in it.

  field_vd* coarse =
    field_factory::new_scalar_field_1d_unstructured(xns,
        "coarse_segments",
        3,
        xlower,
        xupper,
        step_fcn);

  coarse->print_property_dofs(cout,
                              field_factory::zero,
                              "Before refining "
                              " unstructured coarse_segments:",
                              true,
                              true);

  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  field_refiner lrefiner(*coarse->base_space().host(),
                         "zone_centered_refiner_family",
                         "depth_bound_refinement_policy",
                         true);

  //  lrefiner.refine(*coarse, true);
  lrefiner.refine(coarse->coordinates(), coarse->property(), true);
  coarse->print_property_dofs(cout,
                              step_fcn,
                              "After refining "
                              " unstructured coarse_segments:",
                              true,
                              true);

  // Exit:

  return;
}

///
/// Test 2d refinement.
///
void test_2d_refinement(fiber_bundles_namespace& xns, bool xuse_quads, const string& xrefiner_type)
{

  // Preconsitions:

  require((xrefiner_type == "edge_centered") || (xrefiner_type == "barycentric"));


  // Body:

  // A 3x3 element coarse mesh with xmin = -2.0 and xmax = 2.0,
  // with a step in it..

  wsv_block<sec_vd_value_type> xlower("-2.0 -2.0");
  wsv_block<sec_vd_value_type> xupper("2.0 2.0");

  string lfield_name = "coarse_" + xrefiner_type + (xuse_quads ? "_quads" : "_triangles");

  field_vd* coarse =
    field_factory::new_scalar_field_2d_unstructured(xns,
        lfield_name,
        3,
        3,
        xuse_quads,
        xlower,
        xupper,
        step_fcn);

  coarse->print_property_dofs(cout,
                              field_factory::zero,
                              "Before refining"
                              " unstructured coarse:",
                              true,
                              true);

  // Refine the "coarse" field and
  // print the result compared to the exact value.

  field_refiner lrefiner(*coarse->base_space().host(),
                         xrefiner_type + "_refiner_family",
                         "variance_bound_refinement_policy",
                         true);

  lrefiner.refine(*coarse, true);
  coarse->print_property_dofs(cout,
                              step_fcn,
                              "After refining"
                              " unstructured coarse:",
                              true,
                              true);

  // Exit:

  return;
}

}

///
/// Main routine.
///
int
main(int argc, char* argv[])
{
  fiber_bundles_namespace ns("field_refiner.t");
  ns.get_read_write_access();

  // Test the section refiner in d = 1.

  test_1d_refinement(ns);

  // Test the section refiner in d = 2 using
  // quads and edge centered refinement.

  test_2d_refinement(ns, true, "edge_centered");

  // Test the section refiner in d = 2 using
  // triangles and edge centered refinement.

  test_2d_refinement(ns, false, "edge_centered");

  // Test the section refiner in d = 2 using
  // triangles and barycentric refinement.

  test_2d_refinement(ns, false, "barycentric");

  storage_agent sa("field_refiner.t.hdf");
  sa.write_entire(ns);

  return 0;
}


