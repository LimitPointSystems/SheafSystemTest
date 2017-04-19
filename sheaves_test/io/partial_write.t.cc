
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

/// @example io/partial_write.t.cc
/// Test driver for test.

#include "SheafSystem/abstract_poset_member.h"
#include "SheafSystem/poset.h"
#include "SheafSystem/poset_bounds_descriptor.h"
#include "SheafSystem/poset_path.h"
#include "SheafSystem/postorder_iterator.h"
#include "SheafSystem/sheaves_namespace.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/std_sstream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/subposet_member_iterator.h"
#include "SheafSystem/total_poset_member.h"


poset* mesh;
abstract_poset_member* edge;

const int BLOCK_CT = 2;
const int BLOCK_CONN_CT = 8;
const int BLOCK_BDY_CT = 2;

int block_0_conn[BLOCK_CONN_CT] =
  {
    0, 1,
    1, 2,
    2, 3,
    3, 4
  };

int block_1_conn[BLOCK_CONN_CT] =
  {
    4, 5,
    5, 6,
    6, 7,
    7, 8
  };

int* block_conn[BLOCK_CT] =
  {
    block_0_conn,
    block_1_conn
  };

int block_0_bdy[BLOCK_BDY_CT] =
  {
    0,
    4
  };

int block_1_bdy[BLOCK_BDY_CT] =
  {
    4,
    8
  };

int* block_bdy[BLOCK_CT] =
  {
    block_0_bdy,
    block_1_bdy
  };

char* block_names[BLOCK_CT] =
  {
    "block_0",
    "block_1"
  };

const int PROC_CT = 2;
const int PROC_ELEMENT_CT = 4;

int proc_0_elements[PROC_ELEMENT_CT] =
  {
    0, 1, 2, 3
  };

int proc_1_elements[PROC_ELEMENT_CT] =
  {
    4, 5, 6, 7
  };

int* proc_elements[PROC_CT] =
  {
    proc_0_elements,
    proc_1_elements
  };


void
name_mesh_cells(poset* xmesh)
{
  // Name all the edges

  subposet edges(xmesh, "__elements");
  subposet_member_iterator* edge_itr = edges.member_iterator();
  while(!edge_itr->is_done())
  {
    if(edge_itr->name().empty())
    {
      pod_index_type cid = edges.id_map()->domain_id(edge_itr->index());
      stringstream mbr_name_stream;
      string mbr_name;
      mbr_name_stream << "edge_" << cid;
      mbr_name_stream >> mbr_name;
      cout << mbr_name << endl;
      edge_itr->put_name(mbr_name);
    }
    edge_itr->next();
  }
  edges.detach_from_state();

  // Name all the vertices

  subposet vertices(xmesh, "__vertices");
  subposet_member_iterator* vertex_itr = vertices.member_iterator();
  while(!vertex_itr->is_done())
  {
    if(vertex_itr->name().empty())
    {
      pod_index_type cid = vertices.id_map()->domain_id(vertex_itr->index());
      stringstream mbr_name_stream;
      string mbr_name;
      mbr_name_stream << "vertex_" << cid;
      mbr_name_stream >> mbr_name;
      cout << mbr_name << endl;
      vertex_itr->put_name(mbr_name);
    }
    vertex_itr->next();
  }
  vertices.detach_from_state();
}


///
int
main(int xargc, char* xargv[])
{

  // Command line processing:

  int edge_ct = 1;
  bool include_names = true;

  if (xargc > 1)
    edge_ct = atoi(xargv[1]);

  int domain_ct = 0;

  if (xargc > 2)
    domain_ct = atoi(xargv[2]);

  // Preconditions:

  require(edge_ct > 0);
  require(domain_ct >= 0);
  require(domain_ct <= edge_ct);

  // Body:

  sheaves_namespace* test_namespace = new sheaves_namespace("partial_write.t");

  test_namespace->get_read_write_access();

  // Initialize the storage agent; opens the file.

  storage_agent sa("partial_write.t.hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(64);
  sa.put_dof_tuple_record_buffer_ub(15);

  // Create mesh poset

  mesh = new poset(test_namespace, "local_coordinates_schema/local_coordinates_schema", "polyline");


  // Write the name space itself.
  // In the current implementation, the namespace poset must be the first poset written
  // and no members can be added or removed from it until the file is closed.

  sa.write(*test_namespace);

  // Create and write down set of each member of the block decomposition.

  mesh->get_read_write_access();

  total_poset_member lblock;
  unordered_map<int, int> glue_map;

  for(int i=0; i<BLOCK_CT; i++)
  {
    /// @error access control in new_block_state is no longer compatible
    /// with logic for creating boundary in block_poset_builder. Boundary
    /// is required by delete_down bleow.

    lblock.new_block_state(mesh,
                           "cell definitions/edge",
                           block_conn[i],
                           BLOCK_CONN_CT,
                           &glue_map,
                           false);

    name_mesh_cells(mesh);

    // Write the block.

    cout << "writing block " << i << endl;

    poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                        BOTTOM_INDEX,
                                        lblock.index());

    cout << *mesh << endl;

    sa.write(*mesh,
             lrow_bounds,
             poset_bounds_descriptor::BOTTOM_TOP,
             storage_agent::RELEASE_ALL);

    // Delete the downset of the block, except for the boundary.

    lblock.delete_down();

    //     // Synchronize the storage agent with the deletion.

    //     sa.sync_with(*mesh);

    cout << *mesh << endl;
  }

  lblock.attach_to_state(mesh, "__block_0");
  lblock.delete_down(true);
  cout << "after deleting block 0 external boundary" << endl;
  cout << *mesh << endl;

  lblock.attach_to_state(mesh, "__block_1");
  lblock.delete_down(true);
  cout << "after deleting block 1 external boundary" << endl;
  cout << *mesh << endl;

  lblock.detach_from_state();

  // Releasing write access sets the poset is_modified flag.
  // If poset is_modfied when write_remainder is invoked,
  // the poset will be written out again, so release write access
  // now so that write_toc is the last write of the mesh.

  mesh->release_access();
  mesh->get_read_access();

  // Write table of contents of the mesh;

  sa.write_toc(*mesh, mesh->subposet_id("__blocks"));

  mesh->release_access();

  // Write the remainder of the name space.

  sa.write_remainder(*test_namespace);

  delete test_namespace;

  // Postconditions:

  // Exit:

  return 0;
}
