
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
/// @example field_factory_2.t.cc

/// @file
/// Test driver for class field_factory_2.

#include "field_factory_2.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "storage_agent.h"
#include "field_vd.h"
#include "wsv_block.h"

namespace fiber_bundle
{
class unstructured_block;
class sec_e1;
class sec_at0;
}

using namespace fields;

namespace
{
///
/// Property dof function for constructing tests.
///
void
linear_scalar_fcn(block<sec_vd_value_type>& xglobal_coords,
                  block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  require(xglobal_coords.ct() > 0);
  require(xproperty_dofs.ct() == 1);

  // Body:

  sec_vd_dof_type lprop_dof = 20.0;

  int ldc = xglobal_coords.ct();
  for(int i=0; i<ldc; ++i)
  {
    lprop_dof += (i+1)*xglobal_coords[i];
  }

  xproperty_dofs[0] = lprop_dof;


  // Postconditions:

  // Exit:

  return;
};

///
/// Prperty dof function that sets all dofs to 0.0
///
void zero(block<sec_vd_value_type>& xglobal_coords,
          block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  // Body:

  xproperty_dofs.assign(0.0);

  // Postconditions:

  ensure_for_all(i, 0, xproperty_dofs.ct(), xproperty_dofs[i] == 0.0);

  // Exit:

  return;
}


///
/// Tests new_scalar_field_1d_unstructured.
///
void test_new_scalar_field_1d_unstructured(fiber_bundles_namespace& xns)
{

  field_factory_2<sec_e1, sec_at0, unstructured_block> lfactory;

  lfactory.base_index_ubs() = "3";

  lfactory.coord_section_space_path() = "test_1d_unstructured_coord_section_space";
  lfactory.coord_lb() = "0";
  lfactory.coord_ub() = "3";

  lfactory.prop_section_space_path() = "test_1d_unstructured_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_1d_unstructured_base_space/unstructured_block",
                       "1d_unstructured_coordinates",
                       "1d_unstructured_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_1d_unstructured"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_1d_structured.
///
void test_new_scalar_field_1d_structured(fiber_bundles_namespace& xns)
{

  field_factory_2<sec_e1, sec_at0, structured_block_1d> lfactory;

  lfactory.base_index_ubs() = "3";

  lfactory.coord_section_space_path() = "test_1d_structured_coord_section_space";
  lfactory.coord_lb() = "0";
  lfactory.coord_ub() = "3";

  lfactory.prop_section_space_path() = "test_1d_structured_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_1d_structured_base_space/structured_block",
                       "1d_structured_coordinates",
                       "1d_structured_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_1d_structured"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_1d_point.
///
void test_new_scalar_field_1d_points(fiber_bundles_namespace& xns)
{

  field_factory_2<sec_e1, sec_at0, point_block_1d> lfactory;

  lfactory.base_index_ubs() = "4";

  lfactory.coord_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory.coord_section_space_path() = "test_1d_point_coord_section_space";
  lfactory.coord_lb() = "0";
  lfactory.coord_ub() = "3";

  lfactory.prop_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory.prop_section_space_path() = "test_1d_point_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_1d_point_base_space/point_block",
                       "1d_point_coordinates",
                       "1d_point_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_1d_points"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_1d_uniform.
///
void test_new_scalar_field_1d_uniform(fiber_bundles_namespace& xns)
{
  field_factory_2<sec_e1_uniform, sec_at0, structured_block_1d> lfactory;

  lfactory.base_index_ubs() = "3";

  lfactory.coord_section_space_path() = "test_1d_uniform_coord_section_space";
  lfactory.coord_lb() = "0";
  lfactory.coord_ub() = "3";

  lfactory.prop_section_space_path() = "test_1d_uniform_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_1d_uniform_base_space/structured_block_1d",
                       "1d_uniform_coordinates",
                       "1d_uniform_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_1d_uniform"
                              ":",
                              true,
                              true);
  return;
}

///
/// Tests new_scalar_field_1d_uniform.
///
void test_new_scalar_field_1d_uniform_same_coords(fiber_bundles_namespace& xns)
{
  field_factory_2<sec_e1_uniform, sec_at0, structured_block_1d> lfactory;

  poset_path lcoord_path("test_1d_uniform_coord_section_space", "coordinates");
  poset_path lprop_path("test_1d_uniform_prop_section_space", "property2");

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_1d_uniform_base_space/structured_block_1d",
                       lcoord_path,
                       lprop_path);

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_1d_uniform_same_coords"
                              ":",
                              true,
                              true);
  return;
}

///
/// Tests new_scalar_field_2d_unstructured.
///
void test_new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns)
{

  field_factory_2<sec_e2, sec_at0, unstructured_block> lfactory;

  lfactory.base_index_ubs() = "3 2";

  lfactory.coord_fiber_path() = "e2_test";
  lfactory.coord_section_space_path() = "test_2d_unstructured_coord_section_space";
  lfactory.coord_lb() = "0 0";
  lfactory.coord_ub() = "3 2";

  lfactory.prop_section_space_path() = "test_2d_unstructured_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_2d_unstructured_base_space/unstructured_block",
                       "2d_unstructured_coordinates",
                       "2d_unstructured_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_2d_unstructured"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_2d_structured.
///
void test_new_scalar_field_2d_structured(fiber_bundles_namespace& xns)
{

  field_factory_2<sec_e2, sec_at0, structured_block_2d> lfactory;

  lfactory.base_index_ubs() = "3 2";

  lfactory.coord_fiber_path() = "e2_test";
  lfactory.coord_section_space_path() = "test_2d_structured_coord_section_space";
  lfactory.coord_lb() = "0 0";
  lfactory.coord_ub() = "3 2";

  lfactory.prop_section_space_path() = "test_2d_structured_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_2d_structured_base_space/structured_block",
                       "2d_structured_coordinates",
                       "2d_structured_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_2d_structured"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_2d_points.
///
void test_new_scalar_field_2d_points(fiber_bundles_namespace& xns)
{

  field_factory_2<sec_e2, sec_at0, point_block_2d> lfactory;

  lfactory.base_index_ubs() = "4 3";

  lfactory.coord_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory.coord_fiber_path() = "e2_test";
  lfactory.coord_section_space_path() = "test_2d_point_coord_section_space";
  lfactory.coord_lb() = "0 0";
  lfactory.coord_ub() = "3 2";

  lfactory.prop_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory.prop_section_space_path() = "test_2d_point_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_2d_point_base_space/point_block",
                       "2d_point_coordinates",
                       "2d_point_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_2d_points"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_2d_uniform.
///
void test_new_scalar_field_2d_uniform(fiber_bundles_namespace& xns)
{
  field_factory_2<sec_e2_uniform, sec_at0, structured_block_2d> lfactory;

  lfactory.base_index_ubs() = "3 2";

  lfactory.coord_fiber_path() = "e2_test";
  lfactory.coord_section_space_path() = "test_2d_uniform_coord_section_space";
  lfactory.coord_lb() = "0 0";
  lfactory.coord_ub() = "3 2";

  lfactory.prop_section_space_path() = "test_2d_uniform_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_2d_uniform_base_space/structured_block_2d",
                       "2d_uniform_coordinates",
                       "2d_uniform_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_2d_uniform"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_3d_unstructured.
///
void test_new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns)
{
  field_factory_2<sec_e3, sec_at0, unstructured_block> lfactory;

  lfactory.base_index_ubs() = "3 2 1";

  lfactory.coord_fiber_path() = "e3_test";
  lfactory.coord_section_space_path() = "test_3d_unstructured_coord_section_space";
  lfactory.coord_lb() = "0 0 0";
  lfactory.coord_ub() = "3 2 1";

  lfactory.prop_section_space_path() = "test_3d_unstructured_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_3d_unstructured_base_space/unstructured_block",
                       "3d_unstructured_coordinates",
                       "3d_unstructured_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_3d_unstructured"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_3d_structured.
///
void test_new_scalar_field_3d_structured(fiber_bundles_namespace& xns)
{
  field_factory_2<sec_e3, sec_at0, structured_block_3d> lfactory;

  lfactory.base_index_ubs() = "3 2 1";

  lfactory.coord_section_space_path() = "test_3d_structured_coord_section_space";
  lfactory.coord_lb() = "0 0 0";
  lfactory.coord_ub() = "3 2 1";

  lfactory.prop_section_space_path() = "test_3d_structured_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_3d_structured_base_space/structured_block_3d",
                       "3d_structured_coordinates",
                       "3d_structured_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_3d_structured"
                              ":",
                              true,
                              true);


  return;
}

///
/// Tests new_scalar_field_3d_unstructured.
///
void test_new_scalar_field_3d_points(fiber_bundles_namespace& xns)
{
  field_factory_2<sec_e3, sec_at0, point_block_3d> lfactory;

  lfactory.base_index_ubs() = "4 3 2";

  lfactory.coord_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory.coord_section_space_path() = "test_3d_point_coord_section_space";
  lfactory.coord_lb() = "0 0 0";
  lfactory.coord_ub() = "3 2 1";

  lfactory.prop_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory.prop_section_space_path() = "test_3d_point_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_3d_point_base_space/point_block",
                       "3d_point_coordinates",
                       "3d_point_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_3d_points"
                              ":",
                              true,
                              true);

  return;
}

///
/// Tests new_scalar_field_3d_uniform.
///
void test_new_scalar_field_3d_uniform(fiber_bundles_namespace& xns)
{
  field_factory_2<sec_e3_uniform, sec_at0, structured_block_3d> lfactory;

  lfactory.base_index_ubs() = "3 2 1";

  lfactory.coord_fiber_path() = "e3_uniform";
  lfactory.prop_section_space_path() = "test_3d_uniform_prop_section_space";
  lfactory.coord_lb() = "0 0 0";
  lfactory.coord_ub() = "3 2 1";

  lfactory.prop_section_space_path() = "test_3d_uniform_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_3d_uniform_base_space/structured_block_3d",
                       "3d_uniform_coordinates",
                       "3d_uniform_property");

  lfield->put_property_dofs(zero, true);

  lfield->print_property_dofs(cout,
                              0,
                              "new_scalar_field_3d_uniform"
                              ":",
                              true,
                              true);


  return;
}

}
// End unnamed namespace.

///
/// Main routine.
///
int main(int argc, char* argv[])
{

  fiber_bundles_namespace lns("field_factory_2.t");
  lns.get_read_write_access();

  //  test_delete_field_spaces(lns);

  test_new_scalar_field_1d_unstructured(lns);
  test_new_scalar_field_1d_structured(lns);
  test_new_scalar_field_1d_points(lns);
  test_new_scalar_field_1d_uniform(lns);
  test_new_scalar_field_1d_uniform_same_coords(lns);

  test_new_scalar_field_2d_unstructured(lns);
  test_new_scalar_field_2d_structured(lns);
  test_new_scalar_field_2d_points(lns);
  test_new_scalar_field_2d_uniform(lns);

  test_new_scalar_field_3d_unstructured(lns);
  test_new_scalar_field_3d_structured(lns);
  test_new_scalar_field_3d_points(lns);
  test_new_scalar_field_3d_uniform(lns);

  storage_agent sa("field_factory_2.t.hdf");
  sa.write_entire(lns);

  return 0;
}
