// $RCSfile: field_refiner.t.cc,v $ $Revision: 1.5 $ $Date: 2012/03/01 00:41:12 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
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

using namespace fields;
using namespace fields;

namespace
{

fiber_bundles_namespace ns("field_refiner.t");


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
void test_1d_refinement()
{
  wsv_block<sec_vd_value_type> xlower("-2.0");
  wsv_block<sec_vd_value_type> xupper("2.0");

  // An 3 element fine mesh with xmin = -2.0 and xmax = 2.0,
  // with a step in it.

  field_vd* coarse =
    field_factory::new_scalar_field_1d_unstructured(ns,
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
void test_2d_refinement(bool xuse_quads, const string& xrefiner_type)
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
    field_factory::new_scalar_field_2d_unstructured(ns,
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
  ns.get_read_write_access();

  // Test the section refiner in d = 1.

  test_1d_refinement();

  // Test the section refiner in d = 2 using
  // quads and edge centered refinement.

  test_2d_refinement(true, "edge_centered");

  // Test the section refiner in d = 2 using
  // triangles and edge centered refinement.

  test_2d_refinement(false, "edge_centered");

  // Test the section refiner in d = 2 using
  // triangles and barycentric refinement.

  test_2d_refinement(false, "barycentric");

  storage_agent sa("field_refiner.t.hdf");
  sa.write_entire(ns);

  return 0;
}


