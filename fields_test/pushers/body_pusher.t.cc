
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

/// @example body_pusher.t.cc

/// @file
/// Test driver for class body_pusher.

#include "assert_contract.h"
#include "base_space_member.h"
#include "body_factory.h"
#include "body_pusher.h"
#include "fiber_bundles_namespace.h"
#include "field_factory.h"
#include "field_factory_2.h"
#include "point_block_2d.h"
#include "sec_ed_invertible.h"
#include "section_space_schema_poset.h"
#include "std_iostream.h"
#include "field_vd.h"
#include "wsv_block.h"

using namespace fields;

namespace
{

///
/// Push bodies form xsrc_coords to xdst_coords.
///
void push_bodies(sec_ed_invertible& xsrc_coords, sec_ed& xdst_coords)
{
  // Preconditions:

  // Body:

  // Get access to the coordinates.

  xsrc_coords.get_read_access();
  xdst_coords.get_read_access();

  // Get a handle to the source bodies.

  subposet lsrc_bodies(&xsrc_coords.schema().host()->base_space(), "bodies");

  // Output the src base space.

  cout << xsrc_coords.schema().host()->base_space() << endl;

  // Output the destination base space.

  cout << xdst_coords.schema().host()->base_space() << endl;

  // Create the body pusher.

  body_pusher lbody_pusher(xsrc_coords, xdst_coords, true);

  // Push all bodies to their lower bounds in the destination.

  lbody_pusher.name_suffix() = "_lb";
  subposet* ldst_bodies_lb = lbody_pusher.push(lsrc_bodies, false, true);

  // Push all bodies to their upper bounds in the destination.

  lbody_pusher.name_suffix() = "_ub";
  subposet* ldst_bodies_ub = lbody_pusher.push(lsrc_bodies, true, true);

  // Output the destination base space again.

  cout << xdst_coords.schema().host()->base_space() << endl;

  // Clean up.

  lsrc_bodies.detach_from_state();
  ldst_bodies_lb->detach_from_state();
  delete ldst_bodies_lb;
  ldst_bodies_ub->detach_from_state();
  delete ldst_bodies_ub;
  xdst_coords.release_access();
  xsrc_coords.release_access();

  // Exit:

  return;
};

///
/// Push 1d uniform block to unstructured block.
///
void push_1d_uniform_to_unstructured(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Create source bodies

  field_vd* lsrc_field = body_factory::new_1d_uniform_bodies(xns, "src");

  // Create the destination mesh with coordinates that overlap source mesh;
  // it's convenient to it with a field object and ignore the property section.

  wsv_block<sec_vd_value_type> ldst_lower("0");
  wsv_block<sec_vd_value_type> ldst_upper("2");

  field_vd* ldst_field =
    field_factory::new_scalar_field_1d_unstructured(xns,
        "dst_1d",
        15,
        ldst_lower,
        ldst_upper);

  // Push the bodies.

  push_bodies(lsrc_field->coordinates(), ldst_field->coordinates());

  // Exit:

  return;
};

///
/// Push 2d unstructured block to an unstructured block.
///
void push_2d_unstructured_to_unstructured_1(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Create source bodies

  field_vd* lsrc_field = body_factory::new_2d_unstructured_bodies(xns, "src_1");

  // Create the destination mesh with coordinates that are identical to the source mesh;
  // it's convenient to it with a field object and ignore the property section.

  wsv_block<sec_vd_value_type> ldst_lower("-1 -1");
  wsv_block<sec_vd_value_type> ldst_upper("1 1");

  field_vd* ldst_field =
    field_factory::new_scalar_field_2d_unstructured(xns,
        "dst_2d_identical",
        10,
        10,
        true,
        ldst_lower,
        ldst_upper);

  // Push the bodies.

  push_bodies(lsrc_field->coordinates(), ldst_field->coordinates());

  // Exit:

  return;
};

///
/// Push 2d unstructured block to an unstructured block.
///
void push_2d_unstructured_to_unstructured_2(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Create source bodies

  field_vd* lsrc_field = body_factory::new_2d_unstructured_bodies(xns, "src_2");

  // Create the destination mesh with coordinates that are identical to the source mesh;
  // it's convenient to it with a field object and ignore the property section.

  wsv_block<sec_vd_value_type> ldst_lower("0 0");
  wsv_block<sec_vd_value_type> ldst_upper("2 2");

  field_vd* ldst_field =
    field_factory::new_scalar_field_2d_unstructured(xns,
        "dst_2d_coarser",
        7,
        7,
        false,
        ldst_lower,
        ldst_upper);

  // Push the bodies.

  push_bodies(lsrc_field->coordinates(), ldst_field->coordinates());

  // Exit:

  return;
};

///
/// Push 2d unstructured block to an unstructured block.
///
void push_2d_unstructured_to_unstructured_3(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Create source bodies

  field_vd* lsrc_field = body_factory::new_2d_unstructured_bodies(xns, "src_3");

  // Create the destination mesh with coordinates that are identical to the source mesh;
  // it's convenient to it with a field object and ignore the property section.

  wsv_block<sec_vd_value_type> ldst_lower("0 0");
  wsv_block<sec_vd_value_type> ldst_upper("2 2");

  field_vd* ldst_field =
    field_factory::new_scalar_field_2d_unstructured(xns,
        "dst_2d_finer",
        15,
        15,
        false,
        ldst_lower,
        ldst_upper);

  // Push the bodies.

  push_bodies(lsrc_field->coordinates(), ldst_field->coordinates());

  // Exit:

  return;
};

///
/// Push 2d uniform block to an unstructured block.
///
void push_2d_uniform_to_unstructured(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Create source bodies

  field_vd* lsrc_field = body_factory::new_2d_uniform_bodies(xns, "src");

  // Create the destination mesh with coordinates that overlap source mesh;
  // it's convenient to it with a field object and ignore the property section.

  wsv_block<sec_vd_value_type> ldst_lower("0 0");
  wsv_block<sec_vd_value_type> ldst_upper("2 2");

  field_vd* ldst_field =
    field_factory::new_scalar_field_2d_unstructured(xns,
        "dst_2d",
        15,
        15,
        true,
        ldst_lower,
        ldst_upper);

  // Push the bodies.

  push_bodies(lsrc_field->coordinates(), ldst_field->coordinates());

  // Exit:

  return;
};

///
/// Push 2d uniform block to points.
///
void push_2d_uniform_to_points(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Create source bodies

  field_vd* lsrc_field = body_factory::new_2d_uniform_bodies(xns, "src_2d_points");

  // Create the destination mesh with coordinates that overlap source mesh;
  // it's convenient to it with a field object and ignore the property section.

  field_factory_2<sec_e2, sec_at0, point_block_2d> lfactory;
  
  wsv_block<int> lbase_index_ubs("15 15");
  lfactory.base_index_ubs() = lbase_index_ubs;

  wsv_block<sec_vd_value_type> ldst_lower("0 0");
  lfactory.coord_lb() = ldst_lower;

  wsv_block<sec_vd_value_type> ldst_upper("2 2");
  lfactory.coord_ub() = ldst_upper;

  lfactory.coord_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory.prop_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  
  // Specify explicit,unique paths rather than just name, so factory
  // creates new section schema and spaces rather than trying to find
  // and existing schema or space.

  poset_path lbase_path("dst_2d_points_base_space", "dst_2d_points_point_block_2d");

  field_vd* ldst_field =
    lfactory.standard_field(xns, lbase_path, "dst_2d_points_coords", "dst_2d_points_prop", false);

  // Push the bodies.

  push_bodies(lsrc_field->coordinates(), ldst_field->coordinates());

  // Exit:

  return;
};

///
/// Push uniform block to unstructured block.
///
void push_3d_uniform_to_unstructured(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Create source bodies

  field_vd* lsrc_field = body_factory::new_3d_uniform_bodies(xns, "src");

  // Create the destination mesh with coordinates that overlap source mesh;
  // it's convenient to it with a field object and ignore the property section.

  wsv_block<sec_vd_value_type> ldst_lower("0 0 0");
  wsv_block<sec_vd_value_type> ldst_upper("2 2 2");

  field_vd* ldst_field =
    field_factory::new_scalar_field_3d_unstructured(xns,
        "dst_3d",
        15,
        10,
        10,
        true,
        ldst_lower,
        ldst_upper);

  // Push the bodies.

  push_bodies(lsrc_field->coordinates(), ldst_field->coordinates());

  // Exit:

  return;
};



}
; // End namespace.


///
/// Main routine.
///
int main(int argc, char* argv[])
{
  // Create the namespace

  fiber_bundles_namespace lns("body_builder.t");
  lns.get_read_write_access();

  // Dst identical to src.

  push_2d_unstructured_to_unstructured_1(lns);

  // Dst coarser than src; no lower bound result.

  push_2d_unstructured_to_unstructured_2(lns);

  // Dst finer than src.

  push_2d_unstructured_to_unstructured_3(lns);

  push_1d_uniform_to_unstructured(lns);

  push_2d_uniform_to_unstructured(lns);

  push_2d_uniform_to_points(lns);

  push_3d_uniform_to_unstructured(lns);

  return 0;
}
