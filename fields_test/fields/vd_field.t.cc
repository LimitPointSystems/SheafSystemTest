
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
/// @example vd_field.t.cc

/// @file
/// Test driver for class vd_field.

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "base_space_member.h"
#include "client_index.h"
#include "e1.h"
#include "e2.h"
#include "fiber_bundles_namespace.h"
#include "field_factory.h"
#include "name_map.h"
#include "schema_descriptor.h"
#include "sec_at0.h"
#include "sec_ed_invertible.h"
#include "sec_e2_uniform.h"
#include "storage_agent.h"
#include "vd_field.h"
#include "wsv_block.h"

using namespace fields;

namespace
{

///
/// Creates a scalar field on a 2d unstructured mesh.
///
void test_new_scalar_field_2d_unstructured()
{
  fiber_bundles_namespace lns("vd_field.t");
  lns.get_read_write_access();

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("2 2");

  vd_field* lfield =
    field_factory::new_scalar_field_2d_unstructured(lns,
        "test",
        2,
        2,
        true,
        llower,
        lupper);

  // cout << lns << endl;

  return;
}

///
/// Creates a scalar field on a 1d mesh.
///
vd_field* test_new_scalar_field_1d(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Make a schema for the coordinates

  wsv_block<schema_descriptor> lcoord_dof_specs("units C_STRING true");

  poset_path lcoord_schema_path =
    e1::make_schema(xns, "coord_schema", lcoord_dof_specs, true);

  // Make a schema for the property

  wsv_block<schema_descriptor> lprop_dof_specs("units C_STRING true");

  poset_path lprop_schema_path =
    at0::make_schema(xns, "prop_schema", lprop_dof_specs, true);

  // Make the coordinate and property table dofs

  arg_list lcoord_table_dofs;
  lcoord_table_dofs << "units" << "secs";

  arg_list lprop_table_dofs;
  lprop_table_dofs << "units" << "meters";

  // Create the field

  size_type lzone_ct = 6;

  vd_field* result =
    field_factory::new_scalar_field_1d(xns,
                                       "1d_base_space",
                                       lzone_ct,
                                       lcoord_schema_path,
                                       "time",
                                       "time_on_1d_base_space",
                                       lcoord_table_dofs,
                                       "coordinates",
                                       lprop_schema_path,
                                       "category",
                                       "category_on_1d_base_space",
                                       lprop_table_dofs,
                                       "property",
                                       "sec_rep_descriptors/element_element_constant");


  result->get_read_write_access(false, true);

  // Set the coordinates dofs.

  client_index lcoord_index(&result->coordinates().schema().disc_seq_id_map());

  for(size_type i=0; i<=lzone_ct; ++i)
  {
    sec_vd_dof_type ldof = i;

    lcoord_index = i;
    result->coordinates().put_discretization_dofs(lcoord_index, false, &ldof, 1);
  }

  // Set the property dofs.

  client_index lprop_index(&result->property().schema().disc_seq_id_map());

  for(size_type i=0; i<lzone_ct; ++i)
  {
    sec_vd_dof_type ldof = i/2;

    lprop_index = i;
    result->property().put_discretization_dofs(lprop_index, false, &ldof, 1);
  }

  result->release_access();

  // cout << xns << endl;

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_attached());
  ensure(!result->state_is_read_accessible());

  return result;
}

///
/// Tests the embed_property member function using
/// a scalar field on a 1d mesh.
///
void test_embed_property(vd_field* xfield, const string& xpartition_name)
{
  // Create a simple name map.

  block<string> lnames(6);
  lnames[0] = "category_0";
  lnames[1] = "category_1";
  lnames[2] = "category_2";

  //name_map<client_index> lname_map(lnames.base(), lnames.ub());
  name_map<int> lname_map(lnames.base(), lnames.ub());

  xfield->embed_property(xpartition_name, lname_map, true);

  xfield->base_space().get_read_access();

  // cout << *(xfield->base_space().host()) << endl;

  xfield->base_space().release_access();
}

///
/// Creates a scalar field on a 2d mesh with uniform coordinates.
///
vd_field* test_new_scalar_field_2d_uniform(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member("fiber_space_schema/prop_schema"));

  // Set the mesh index bounds.

  wsv_block<int> lindex_ubs("3 2");
  int lzone_ct_i = lindex_ubs[0];
  int lzone_ct_j = lindex_ubs[1];

  // Set the coordinate bounds.

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("3 2");

  // Create the prop section handle.

  sec_at0 lprop;

  // Create the field.

  vd_field* result =
    field_factory::new_uniform_field(xns,
                                     "2d_uniform_base_space",
                                     lindex_ubs,
                                     llower,
                                     lupper,
                                     "lat_lon",
                                     "coordinates",
                                     "prop",
                                     "property",
                                     "sec_rep_descriptors/vertex_element_dlinear",
                                     lprop);


  lprop.detach_from_state();

  result->get_read_write_access(false, true);

  // Don't need to set the coordinates dofs.

  // Set the property dofs.

  client_index lcid(&result->property().schema().disc_seq_id_map());

  for(int i=0; i<lzone_ct_i; ++i)
  {
    for(int j=0; j<lzone_ct_j; ++j)
    {
      sec_vd_dof_type ldof = i;

      lcid = i*lzone_ct_j + j;

      result->property().put_discretization_dofs(lcid, false, &ldof, 1);
    }
  }

  result->release_access();

  // cout << xns << endl;

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_attached());
  ensure(!result->state_is_read_accessible());

  return result;
}

///
/// Creates a scalar field on a 2d mesh with uniform coordinates.
///
vd_field* test_new_scalar_field_2d_structured(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset_member("fiber_space_schema/prop_schema"));

  // Create the coordinates schema.

  wsv_block<schema_descriptor> ldof_specs("units CHAR_PTR true");
  poset_path lcoord_schema_path =
    e2::make_schema(xns, "lat_lon_schema", ldof_specs, true);

  // Use an existing property schema.

  poset_path lprop_schema_path("fiber_space_schema/prop_schema");

  // Make the coordinate and property table dofs

  arg_list lcoord_table_dofs;
  lcoord_table_dofs << "units" << "Km";

  arg_list lprop_table_dofs;
  lprop_table_dofs << "units" << "meters";

  // Set the mesh index bounds.

  size_type lzone_ct_i = 3;
  size_type lzone_ct_j = 2;

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("3 2");

  vd_field* result =
    field_factory::new_scalar_field_2d_structured(xns,
        "2d_base_space",
        lzone_ct_i,
        lzone_ct_j,
        llower,
        lupper,
        lcoord_schema_path,
        "lat_lon",
        "lat_lon_on_2d_base_space",
        lcoord_table_dofs,
        "coordinates",
        lprop_schema_path,
        "category2",
        "category2_on_2d_base_space",
        lprop_table_dofs,
        "property",
        "sec_rep_descriptors/element_element_constant");

  result->get_read_write_access(false, true);

  // Set the property dofs.

  client_index lcid(&result->property().schema().disc_seq_id_map());

  for(size_type i=0; i<lzone_ct_i; ++i)
  {
    for(size_type j=0; j<lzone_ct_j; ++j)
    {
      sec_vd_dof_type ldof = i;

      lcid = i*lzone_ct_j + j;

      result->property().put_discretization_dofs(lcid, false, &ldof, 1);
    }
  }

  result->release_access();

  // cout << xns << endl;

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_attached());
  ensure(!result->state_is_read_accessible());

  return result;
}

///
/// Tests pushed field constructor.
///
vd_field* test_new_scalar_field_2d_pushed(fiber_bundles_namespace& xns,
    vd_field* xsrc)
{
  vd_field* result;

  // Preconditions:

  require(xsrc != 0);
  require(xsrc->is_attached());

  // Body:

  xsrc->get_read_access();

  // Create a uniform coordinate field for the destination;
  // first create the sec rep space.

  // Use an existing coordinates schema.

  poset_path lcoord_schema_path =
    xsrc->coordinates().schema().fiber_schema().path();

  arg_list largs; // fiber space already exists, so won't be referenced.

  sec_rep_space* lhost =
    sec_e2_uniform::new_host(xns,
                             "dst_2d_base_space",
                             5,
                             3,
                             lcoord_schema_path,
                             largs,
                             true);

  // Then create the coord section.

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("5 3");

  sec_e2_uniform* ldst_coords = new sec_e2_uniform(lhost, llower, lupper, true);
  ldst_coords->put_name("dst_coords", true, true);

  // Create the pushed field.

  result = 0;


  xsrc->release_access();

  // Postconditions:


  // Exit:

  return result;
}

}

///
/// Main routine.
///
int main(int argc, char* argv[])
{
  fiber_bundles_namespace lns("vd_field.t");
  lns.get_read_write_access();

  vd_field* lfield_1d = test_new_scalar_field_1d(lns);

  test_embed_property(lfield_1d, "categories");

  vd_field* lfield_2d = test_new_scalar_field_2d_structured(lns);

  test_embed_property(lfield_2d, "categories");

  vd_field* lfield_2d_u = test_new_scalar_field_2d_uniform(lns);

  vd_field* lfield_2d_pushed = test_new_scalar_field_2d_pushed(lns, lfield_2d_u);

  cout << lns << endl;

  storage_agent sa("vd_fields.t.hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  return 0;
}

