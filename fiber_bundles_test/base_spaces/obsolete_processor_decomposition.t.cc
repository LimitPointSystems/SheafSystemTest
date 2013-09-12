
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

/// @example base_spaces/processor_decomposition.t.cc
/// Test driver for processor_decomposition.cc.

#include "id_block.h"
#include "material_decomposition.h"
#include "mesh_decomposition.h"
#include "poset_path.h"
#include "preorder_iterator.h"
#include "processor_decomposition.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_at0.h"
#include "sec_e2.h"
#include "sec_rep_space.h"
#include "structured_block_1d.h"
#include "storage_agent.h"
#include "unstructured_block.h"

using namespace fiber_bundle;

// OBSOLETE: This test driver is obsolete

///
/// Create the read scopes for processor decomposition xdecomp.
///
void make_1d_read_scopes_1(processor_decomposition& xdecomp)
{

  // Preconditions:

  require(xdecomp.mesh().state_is_read_write_accessible());

  // Body:

  const index_space& lzone_id_space = *xdecomp.mesh().elements().id_space();
  id_block lread_ids(xdecomp.mesh(), lzone_id_space, 5);
  int l_id;

  // Processor 0 read scope:

  lread_ids.set_ct(0);
  lread_ids.put_id_space(lzone_id_space, false);
  lread_ids.push_back(scoped_index(0));
  lread_ids.push_back(scoped_index(1));
  lread_ids.push_back(scoped_index(2));
  lread_ids.put_id_space_internal(false);

  xdecomp.put_read_scope(0, lread_ids);

  // Processor 1:

  lread_ids.set_ct(0);
  lread_ids.put_id_space(lzone_id_space, false);
  lread_ids.push_back(scoped_index(1));
  lread_ids.push_back(scoped_index(2));
  lread_ids.push_back(scoped_index(3));
  lread_ids.push_back(scoped_index(4));
  lread_ids.push_back(scoped_index(5));
  lread_ids.put_id_space_internal(false);

  xdecomp.put_read_scope(1, lread_ids);

  // Processor 2:

  lread_ids.set_ct(0);
  lread_ids.put_id_space(lzone_id_space, false);
  lread_ids.push_back(scoped_index(4));
  lread_ids.push_back(scoped_index(5));
  lread_ids.push_back(scoped_index(6));
  lread_ids.put_id_space_internal(false);

  xdecomp.put_read_scope(2, lread_ids);

  // Postconditions:

  ensure(xdecomp.mesh().includes_subposet(xdecomp.scope_set_name("read")));
  ensure(xdecomp.mesh().contains_member(xdecomp.read_scope_name(0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.read_scope_name(1)));
  ensure(xdecomp.mesh().contains_member(xdecomp.read_scope_name(2)));

  // Exit:

  return;
}


///
/// Create the send scopes for processor decomposition xdecomp.
///
void make_1d_send_scopes_1(processor_decomposition& xdecomp)
{

  // Preconditions:

  require(xdecomp.mesh().state_is_read_write_accessible());

  // Body:

  const index_space& lzone_id_space = *xdecomp.mesh().elements().id_space();
  id_block lsend_ids(xdecomp.mesh(), lzone_id_space, 2);

  // Processor 0 send 1 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(1));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(0, 1, lsend_ids);

  // Processor 1 send 0 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(2));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(1, 0, lsend_ids);

  // Processor 1 send 2 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(4));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(1, 2, lsend_ids);

  // Processor 2 send 1:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(5));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(2, 1, lsend_ids);

  // Postconditions:

  ensure(xdecomp.mesh().includes_subposet(xdecomp.scope_set_name("send")));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(0, 1)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(1, 0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(1, 2)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(2, 1)));

  // Exit:

  return;
}

///
void
make_1d_example_1(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make a simple 1D mesh.

  base_space_poset& lmesh = xns.new_base_space<structured_block_1d>("1d_mesh_example_1");

  structured_block_1d lblock(&lmesh, 7, true);
  lblock.put_name("mesh", true, true);
  lblock.detach_from_state();

  lmesh.get_read_write_access();
  //  cout << lmesh << endl;

  // Create a processor decomposition.

  processor_decomposition ldecomp(lmesh, "__pd_1");

  make_1d_read_scopes_1(ldecomp);
  make_1d_send_scopes_1(ldecomp);

  ldecomp.compute_comm_scopes();
  ldecomp.compute_zone_ceiling();

  // cout << lmesh << endl;

  // Postconditions:


  // Exit:

  return;
}

///
/// Create the material scopes for material decomposition xdecomp.
///
void make_1d_mat_scopes_1(mesh_decomposition& xdecomp)
{

  // Preconditions:

  require(xdecomp.mesh().state_is_read_write_accessible());

  // Body:

  const index_space& lzone_id_space = *xdecomp.mesh().elements().id_space();
  id_block lmat_ids(xdecomp.mesh(), lzone_id_space, 5);
  int l_id;

  // Material 0 scope:

  lmat_ids.set_ct(0);
  lmat_ids.put_id_space(lzone_id_space, false);
  lmat_ids.push_back(scoped_index(0));
  lmat_ids.push_back(scoped_index(1));
  lmat_ids.push_back(scoped_index(2));
  lmat_ids.push_back(scoped_index(3));
  lmat_ids.put_id_space_internal(false);

  xdecomp.put_scope(0, lmat_ids);

  // Material 1:

  lmat_ids.set_ct(0);
  lmat_ids.put_id_space(lzone_id_space, false);
  lmat_ids.push_back(scoped_index(4));
  lmat_ids.push_back(scoped_index(5));
  lmat_ids.push_back(scoped_index(6));
  lmat_ids.put_id_space_internal(false);

  xdecomp.put_scope(1, lmat_ids);

  // Postconditions:

  ensure(xdecomp.mesh().contains_member(xdecomp.scope_name(0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.scope_name(1)));

  // Exit:

  return;
}


///
/// Create the material scopes for material decomposition xdecomp.
///
void make_1d_mat_scopes_2(material_decomposition& xdecomp)
{

  // Preconditions:

  require(xdecomp.mesh().state_is_read_write_accessible());

  // Body:

  const index_space& lzone_id_space = *xdecomp.mesh().elements().id_space();
  id_block lmat_ids(xdecomp.mesh(), lzone_id_space, 5);
  int l_id;

  // Material 0 scope:

  lmat_ids.set_ct(0);
  lmat_ids.put_id_space(lzone_id_space, false);
  lmat_ids.push_back(scoped_index(0));
  lmat_ids.push_back(scoped_index(1));
  lmat_ids.push_back(scoped_index(2));
  lmat_ids.put_id_space_internal(false);

  xdecomp.put_material(0, lmat_ids);

  // Material 1:

  lmat_ids.set_ct(0);
  lmat_ids.put_id_space(lzone_id_space, false);
  lmat_ids.push_back(scoped_index(2));
  lmat_ids.push_back(scoped_index(3));
  lmat_ids.push_back(scoped_index(4));
  lmat_ids.push_back(scoped_index(5));
  lmat_ids.put_id_space_internal(false);

  xdecomp.put_material(1, lmat_ids);

  // Material 2:

  lmat_ids.set_ct(0);
  lmat_ids.put_id_space(lzone_id_space, false);
  lmat_ids.push_back(scoped_index(4));
  lmat_ids.push_back(scoped_index(5));
  lmat_ids.push_back(scoped_index(6));
  lmat_ids.put_id_space_internal(false);

  xdecomp.put_material(2, lmat_ids);

  // Postconditions:

  ensure(xdecomp.mesh().contains_member(xdecomp.material_name(0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.material_name(1)));
  ensure(xdecomp.mesh().contains_member(xdecomp.material_name(2)));

  // Exit:

  return;
}


///
void
make_1d_example_2(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make a simple 1D mesh.

  base_space_poset& lmesh = xns.new_base_space<structured_block_1d>("1d_mesh_example_2");

  structured_block_1d lblock(&lmesh, 7, true);
  lblock.put_name("mesh", true, true);
  lblock.detach_from_state();

  lmesh.get_read_write_access();
  //  cout << lmesh << endl;

  // Create a processor decomposition.

  processor_decomposition ldecomp(lmesh, "__pd_1");

  make_1d_read_scopes_1(ldecomp);
  make_1d_send_scopes_1(ldecomp);

  ldecomp.compute_comm_scopes();

  // Create a material decomposition

  mesh_decomposition lmat_decomp(lmesh, "__md_1");
  make_1d_mat_scopes_1(lmat_decomp);


  ldecomp.compute_zone_ceiling();

  // cout << lmesh << endl;

  // Postconditions:


  // Exit:

  return;
}

///
void
make_1d_example_3(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make a simple 1D mesh.

  base_space_poset& lmesh = xns.new_base_space<structured_block_1d>("1d_mesh_example_3");

  structured_block_1d lblock(&lmesh, 7, true);
  lblock.put_name("mesh", true, true);
  lblock.detach_from_state();

  lmesh.get_read_write_access();
  //  cout << lmesh << endl;

  // Create a material decomposition

  material_decomposition lmat_decomp(lmesh, "__md_1");
  make_1d_mat_scopes_2(lmat_decomp);
  lmat_decomp.compute_mixed_materials();

  // cout << lmesh << endl;

  // Postconditions:


  // Exit:

  return;
}

///
/// Create the read scopes for processor decomposition xdecomp.
///
void make_2d_read_scopes_1(processor_decomposition& xdecomp)
{

  // Preconditions:

  require(xdecomp.mesh().state_is_read_write_accessible());

  // Body:

  const index_space& lzone_id_space = *xdecomp.mesh().elements().id_space();
  id_block lread_ids(xdecomp.mesh(), lzone_id_space, 9);
  int l_id;

  // Processor 0 read scope:

  lread_ids.set_ct(0);
  lread_ids.put_id_space(lzone_id_space, false);
  lread_ids.push_back(scoped_index(0));
  lread_ids.push_back(scoped_index(1));
  lread_ids.push_back(scoped_index(2));
  lread_ids.push_back(scoped_index(4));
  lread_ids.push_back(scoped_index(5));
  lread_ids.push_back(scoped_index(6));
  lread_ids.push_back(scoped_index(8));
  lread_ids.push_back(scoped_index(9));
  lread_ids.push_back(scoped_index(10));
  lread_ids.put_id_space_internal(false);

  xdecomp.put_read_scope(0, lread_ids);

  // Processor 1:

  lread_ids.set_ct(0);
  lread_ids.put_id_space(lzone_id_space, false);
  lread_ids.push_back(scoped_index(1));
  lread_ids.push_back(scoped_index(2));
  lread_ids.push_back(scoped_index(3));
  lread_ids.push_back(scoped_index(5));
  lread_ids.push_back(scoped_index(6));
  lread_ids.push_back(scoped_index(7));
  lread_ids.push_back(scoped_index(9));
  lread_ids.push_back(scoped_index(10));
  lread_ids.push_back(scoped_index(11));
  lread_ids.put_id_space_internal(false);

  xdecomp.put_read_scope(1, lread_ids);

  // Processor 2:

  lread_ids.set_ct(0);
  lread_ids.put_id_space(lzone_id_space, false);
  lread_ids.push_back(scoped_index(4));
  lread_ids.push_back(scoped_index(5));
  lread_ids.push_back(scoped_index(6));
  lread_ids.push_back(scoped_index(8));
  lread_ids.push_back(scoped_index(9));
  lread_ids.push_back(scoped_index(10));
  lread_ids.push_back(scoped_index(12));
  lread_ids.push_back(scoped_index(13));
  lread_ids.push_back(scoped_index(14));
  lread_ids.put_id_space_internal(false);

  xdecomp.put_read_scope(2, lread_ids);

  // Processor 3:

  lread_ids.set_ct(0);
  lread_ids.put_id_space(lzone_id_space, false);
  lread_ids.push_back(scoped_index(5));
  lread_ids.push_back(scoped_index(6));
  lread_ids.push_back(scoped_index(7));
  lread_ids.push_back(scoped_index(9));
  lread_ids.push_back(scoped_index(10));
  lread_ids.push_back(scoped_index(11));
  lread_ids.push_back(scoped_index(13));
  lread_ids.push_back(scoped_index(14));
  lread_ids.push_back(scoped_index(15));
  lread_ids.put_id_space_internal(false);

  xdecomp.put_read_scope(3, lread_ids);

  // Postconditions:

  ensure(xdecomp.mesh().includes_subposet(xdecomp.scope_set_name("read")));
  ensure(xdecomp.mesh().contains_member(xdecomp.read_scope_name(0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.read_scope_name(1)));
  ensure(xdecomp.mesh().contains_member(xdecomp.read_scope_name(2)));
  ensure(xdecomp.mesh().contains_member(xdecomp.read_scope_name(3)));

  // Exit:

  return;
}

///
/// Create the send scopes for processor decomposition xdecomp.
///
void make_2d_send_scopes_1(processor_decomposition& xdecomp)
{

  // Preconditions:

  require(xdecomp.mesh().state_is_read_write_accessible());

  // Body:

  const index_space& lzone_id_space = *xdecomp.mesh().elements().id_space();
  id_block lsend_ids(xdecomp.mesh(), lzone_id_space, 2);

  // Processor 0 send 1 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(1));
  lsend_ids.push_back(scoped_index(5));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(0, 1, lsend_ids);

  // Processor 0 send 2 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(4));
  lsend_ids.push_back(scoped_index(5));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(0, 2, lsend_ids);

  // Processor 0 send 3 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(5));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(0, 3, lsend_ids);

  // Processor 1 send 0 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(2));
  lsend_ids.push_back(scoped_index(6));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(1, 0, lsend_ids);

  // Processor 1 send 2 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(6));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(1, 2, lsend_ids);

  // Processor 1 send 3 scope:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(6));
  lsend_ids.push_back(scoped_index(7));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(1, 3, lsend_ids);

  // Processor 2 send 0:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(8));
  lsend_ids.push_back(scoped_index(9));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(2, 0, lsend_ids);

  // Processor 2 send 1:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(9));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(2, 1, lsend_ids);

  // Processor 2 send 3:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(9));
  lsend_ids.push_back(scoped_index(13));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(2, 3, lsend_ids);

  // Processor 3 send 0:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(10));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(3, 0, lsend_ids);

  // Processor 3 send 1:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(10));
  lsend_ids.push_back(scoped_index(11));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(3, 1, lsend_ids);

  // Processor 3 send 2:

  lsend_ids.set_ct(0);
  lsend_ids.put_id_space(lzone_id_space, false);
  lsend_ids.push_back(scoped_index(10));
  lsend_ids.push_back(scoped_index(14));
  lsend_ids.put_id_space_internal(false);

  xdecomp.put_send_scope(3, 2, lsend_ids);

  // Postconditions:

  ensure(xdecomp.mesh().includes_subposet(xdecomp.scope_set_name("send")));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(0, 1)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(0, 2)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(0, 3)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(1, 0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(1, 2)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(1, 3)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(2, 0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(2, 1)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(2, 3)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(3, 0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(3, 1)));
  ensure(xdecomp.mesh().contains_member(xdecomp.send_scope_name(3, 2)));

  // Exit:

  return;
}

///
/// Create the material scopes for material decomposition xdecomp.
///
void make_2d_mat_scopes_1(material_decomposition& xdecomp)
{

  // Preconditions:

  require(xdecomp.mesh().state_is_read_write_accessible());

  // Body:

  const index_space& lzone_id_space = *xdecomp.mesh().elements().id_space();
  id_block lmat_ids(xdecomp.mesh(), lzone_id_space, 5);
  int l_id;

  // Material 0 scope:

  lmat_ids.set_ct(0);
  lmat_ids.put_id_space(lzone_id_space, false);
  for(int i=0; i<12; ++i)
  {
    lmat_ids.push_back(scoped_index(i));
  }
  lmat_ids.put_id_space_internal(false);

  xdecomp.put_material(0, lmat_ids);

  // Material 1:

  lmat_ids.set_ct(0);
  lmat_ids.put_id_space(lzone_id_space, false);
  for(int i=8; i<16; ++i)
  {
    lmat_ids.push_back(scoped_index(i));
  }

  lmat_ids.put_id_space_internal(false);

  xdecomp.put_material(1, lmat_ids);

  xdecomp.compute_mixed_materials();

  // Postconditions:

  ensure(xdecomp.mesh().contains_member(xdecomp.material_name(0)));
  ensure(xdecomp.mesh().contains_member(xdecomp.material_name(1)));

  // Exit:

  return;
}

///
void make_2d_coordinate_section(base_space_member& xbase, int xedge_ct)
{
  // Preconditions:


  // Body:

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(*xbase.name_space());

  poset_path lbase_path(xbase.path());
  poset_path lrep_path("sec_rep_descriptors", "vertex_element_dlinear");

  sec_rep_space* lspace =
    &lns.new_section_space<sec_e2>("e2_on_mesh", lbase_path, lrep_path, true);

  sec_e2 lcoords(lspace);
  lcoords.get_read_write_access();
  lcoords.put_name("coordinates", true, false);

  // Set the dofs of the coordinates.

  sec_vd_dof_type ldisc_dofs[2];
  int k = 0;
  for(int i=0; i<=xedge_ct; ++i)
  {
    for(int j=0; j<=xedge_ct; ++j)
    {
      ldisc_dofs[0] = i;
      ldisc_dofs[1] = j;
      lcoords.put_fiber(k++, ldisc_dofs, 2*sizeof(sec_vd_dof_type));
    }
  }

  lcoords.detach_from_state();

  sec_e2 lcoords2(lspace);
  lcoords2.get_read_write_access();
  lcoords2.put_name("other coordinates", true, false);

  // Set the dofs of the coordinates.

  k = 0;
  for(int i=0; i<=xedge_ct; ++i)
  {
    for(int j=0; j<=xedge_ct; ++j)
    {
      ldisc_dofs[0] = i*1.1;
      ldisc_dofs[1] = j*1.1;
      lcoords2.put_fiber(k++, ldisc_dofs, 2*sizeof(sec_vd_dof_type));
    }
  }

  lcoords2.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

///
void make_2d_scalar_section(base_space_member& xbase, int xedge_ct)
{
  // Preconditions:


  // Body:

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(*xbase.name_space());

  poset_path lbase_path(xbase.path());
  poset_path lrep_path("sec_rep_descriptors", "element_element_constant");

  sec_rep_space* lspace =
    &lns.new_section_space<sec_at0>("at0_on_mesh", lbase_path, lrep_path, true);

  sec_at0 lscalar(lspace);
  lscalar.get_read_write_access();
  lscalar.put_name("some scalar field", true, false);

  // Set the dofs of the coordinates.

  sec_vd_dof_type ldisc_dofs[1];
  int k = 0;
  for(int i=0; i<xedge_ct; ++i)
  {
    for(int j=0; j<xedge_ct; ++j)
    {
      ldisc_dofs[0] = i+j;
      lscalar.put_fiber(k++, ldisc_dofs, sizeof(sec_vd_dof_type));
    }
  }

  lscalar.detach_from_state();

  sec_at0 lscalar2(lspace);
  lscalar2.get_read_write_access();
  lscalar2.put_name("other scalar field", true, false);

  // Set the dofs of the coordinates.

  k = 0;
  for(int i=0; i<xedge_ct; ++i)
  {
    for(int j=0; j<xedge_ct; ++j)
    {
      ldisc_dofs[0] = i-j;
      lscalar2.put_fiber(k++, ldisc_dofs, sizeof(sec_vd_dof_type));
    }
  }

  lscalar2.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}


///
void make_boundary_condition(base_space_member& xbase)
{
  // Preconditions:


  // Body:

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(*xbase.name_space());

  poset_path lbase_path(xbase.path());
  poset_path lrep_path("sec_rep_descriptors", "face_face_const_2D");

  sec_rep_space* lspace =
    &lns.new_section_space<sec_at0>("at0_on_boundary", lbase_path, lrep_path, true);

  sec_at0 lscalar(lspace);
  lscalar.get_read_write_access();
  lscalar.put_name("boundary_condition", true, false);

  // Set the dofs of the coordinates.

  sec_vd_dof_type ldisc_dofs[1];
  int lbc = 0;
  preorder_iterator litr(xbase, "__1_cells");
  while(!litr.is_done())
  {
    ldisc_dofs[0] = lbc++;
    lscalar.put_fiber(litr.index(), ldisc_dofs, sizeof(sec_vd_dof_type), false);
    litr.truncate();
  }
  lscalar.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}


///
void
make_2d_example_1(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make 4 x 4 quad mesh.

  base_space_poset& lmesh =
    xns.new_base_space<unstructured_block>("mesh_representation_example", "", "", 2, true);

  poset_path lcell_path(base_space_member::prototypes_poset_name(), "quad_complex");
  unstructured_block lblock(&lmesh, lcell_path, 2, 2, true);

  lmesh.get_read_write_access();

  lblock.delete_all_names();
  lblock.put_name("quad_mesh", true, false);

  // Delete the boundary member.

  base_space_member lbdy(&lmesh, "__bdy_of___block_0");
  lbdy.delete_state();


  // Create a coordinate field

  make_2d_coordinate_section(lblock, 2);
  make_2d_scalar_section(lblock, 2);

  //  cout << xns << endl;

  lblock.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

///
void
make_2d_example_2(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make 4 x 4 quad mesh.

  base_space_poset& lmesh =
    xns.new_base_space<unstructured_block>("materials_example", "", "", 2, true);

  poset_path lcell_path(base_space_member::prototypes_poset_name(), "quad_complex");
  unstructured_block lblock(&lmesh, lcell_path, 4, 4, true);
  lmesh.get_read_write_access();

  lblock.delete_all_names();
  lblock.put_name("quad_mesh", true, false);

  lblock.detach_from_state();


  // Create a material decomposition

  material_decomposition lmat_decomp(lmesh, "__md_1");
  make_2d_mat_scopes_1(lmat_decomp);

  // Delete the boundary member.

  base_space_member lbdy(&lmesh, "__bdy_of___block_0");
  lbdy.delete_state();


  // cout << lmesh << endl;

  // Postconditions:


  // Exit:

  return;
}


///
void
make_2d_example_3(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make 4 x 4 quad mesh.

  base_space_poset& lmesh =
    xns.new_base_space<unstructured_block>("boundary_condition_example", "", "", 2, true);

  poset_path lcell_path(base_space_member::prototypes_poset_name(), "quad_complex");
  unstructured_block lblock(&lmesh, lcell_path, 4, 4, true);
  lmesh.get_read_write_access();
  lblock.delete_all_names();
  lblock.put_name("mesh", true, true);
  lblock.detach_from_state();


  // Create a material decomposition

  material_decomposition lmat_decomp(lmesh, "__md_1");
  make_2d_mat_scopes_1(lmat_decomp);

  // Create a piece of boundary for a boundary condition.

  base_space_member lmat0(&lmesh, lmat_decomp.material_name(0));
  base_space_member lbndry(&lmesh, "__bdy_of___block_0");
  lbndry.delete_all_names();
  lbndry.put_name("mesh_boundary", true, false);


  base_space_member* lbndry_mat0 = lmat0.l_meet(&lbndry);
  lbndry_mat0->put_name("material_0_boundary", true, false);

  make_boundary_condition(*lbndry_mat0);


  lbndry_mat0->detach_from_state();
  lbndry.detach_from_state();
  lmat0.detach_from_state();

  // cout << lmesh << endl;

  // Postconditions:


  // Exit:

  return;
}

///
void
make_2d_example_4(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make 4 x 4 quad mesh.

  base_space_poset& lmesh =
    xns.new_base_space<unstructured_block>("processor_decomposition_example", "", "", 2, true);

  poset_path lcell_path(base_space_member::prototypes_poset_name(), "quad_complex");
  unstructured_block lblock(&lmesh, lcell_path, 4, 4, true);

  lmesh.get_read_write_access();
  lblock.delete_all_names();
  lblock.put_name("mesh", true, true);
  lblock.detach_from_state();


  // Create a processor decomposition.

  processor_decomposition ldecomp(lmesh, "__pd_1");

  make_2d_read_scopes_1(ldecomp);
  make_2d_send_scopes_1(ldecomp);

  ldecomp.compute_comm_scopes();
  // ldecomp.compute_zone_ceiling();

  // Delete the boundary member.

  base_space_member lbdy(&lmesh, "__bdy_of___block_0");
  lbdy.delete_state();

  //  cout << lmesh << endl;

  // Postconditions:


  // Exit:

  return;
}

///
void
make_2d_example_5(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make 4 x 4 quad mesh.

  base_space_poset& lmesh =
    xns.new_base_space<unstructured_block>("multiple concurrent decompositions", "", "", 2, true);

  poset_path lcell_path(base_space_member::prototypes_poset_name(), "quad_complex");
  unstructured_block lblock(&lmesh, lcell_path, 4, 4, true);
  lmesh.get_read_write_access();

  lblock.delete_all_names();
  lblock.put_name("mesh", true, true);
  lblock.detach_from_state();


  // Create a processor decomposition.

  processor_decomposition ldecomp(lmesh, "__pd_1");

  make_2d_read_scopes_1(ldecomp);
  make_2d_send_scopes_1(ldecomp);

  ldecomp.compute_comm_scopes();

  material_decomposition lmat_decomp(lmesh, "__md_1");
  make_2d_mat_scopes_1(lmat_decomp);

  base_space_member lbndry(&lmesh, "__bdy_of___block_0");
  lbndry.delete_all_names();
  lbndry.put_name("mesh_boundary", true, false);
  lbndry.detach_from_state();

  ldecomp.compute_zone_ceiling();

  //  cout << lmesh << endl;

  // Postconditions:


  // Exit:

  return;
}

int
main(int argc, char* argv[])
{

  string size_arg;
  size_type size;
  if (argc > 1)
  {
    size = atoi(argv[1]);
    size_arg = argv[1];
  }
  else
  {
    size = 1;
    size_arg = "1";
  }

  fiber_bundles_namespace lns("processor_decomposition.t");
  lns.get_read_write_access();

  //   make_1d_example_1(lns);
  //   make_1d_example_2(lns);
  //   make_1d_example_3(lns);
  make_2d_example_1(lns);
  make_2d_example_2(lns);
  make_2d_example_3(lns);
  make_2d_example_4(lns);
  make_2d_example_5(lns);

  // cout << lns << endl;

  storage_agent sa("processor_decomposition.t.hdf");
  sa.write_entire(lns);

  return 0;
}
