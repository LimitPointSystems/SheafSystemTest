
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

/// @example io/write_row_decomposition.t.cc
/// Test driver for test.

#include "abstract_poset_member.h"
#include "poset.h"
#include "poset_bounds_descriptor.h"
#include "poset_path.h"
#include "sheaves_namespace.h"
#include "assert_contract.h"
#include "std_string.h"
#include "std_strstream.h"
#include "storage_agent.h"
#include "subposet_member_iterator.h"
#include "total_poset_member.h"


poset* mesh;
abstract_poset_member* edge;

const int BLOCK_CT = 2;
const int BLOCK_CONN_CT = 8;

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
      strstream mbr_name_stream;
      string mbr_name;
      mbr_name_stream << "edge_" << cid;
      mbr_name_stream >> mbr_name;
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
      strstream mbr_name_stream;
      string mbr_name;
      mbr_name_stream << "vertex_" << cid;
      mbr_name_stream >> mbr_name;
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

  sheaves_namespace* test_namespace =
    new sheaves_namespace("write_row_decomposition.t");
  test_namespace->get_read_write_access();

  // Create mesh poset

  mesh =
    new poset(test_namespace,
              "local_coordinates_schema/local_coordinates_schema",
              "polyline");


  // Create each member of the block decomposition.

  mesh->get_read_write_access();
  mesh->begin_jim_edit_mode();

  subposet lblocks_sp(mesh);
  lblocks_sp.put_name("blocks", true, false);

  total_poset_member lblock;
  unordered_map<int, int> glue_map;

  for(int i=0; i<BLOCK_CT; i++)
  {
    cout << "creating block " << i << endl;

    lblock.new_block_state(mesh,
                           "cell definitions/edge",
                           block_conn[i],
                           BLOCK_CONN_CT,
                           &glue_map);

    lblock.put_name(block_names[i]);
    lblocks_sp.insert_member(&lblock);
  }

  lblock.detach_from_state();
  mesh->end_jim_edit_mode();

  name_mesh_cells(mesh);

  mesh->release_access();
  mesh->get_read_access();


  // Initialize the storage agent; opens the file.

  storage_agent sa("write_row_decomposition.t.hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(64);
  sa.put_dof_tuple_record_buffer_ub(15);

  // Write the name space itself.
  // In the current implementation, the namespace poset must be the first poset
  // written and no members can be added or removed from it until the file is closed.

  sa.write(*test_namespace);

  // Write the decomposition

  sa.write_row_decomposition(*mesh, lblocks_sp.index());

  // Write table of contents of the mesh;

  sa.write_toc(*mesh, lblocks_sp.index());

  lblocks_sp.detach_from_state();

  mesh->release_access();

  // Write the remainder of the name space.

  sa.write_remainder(*test_namespace);

  delete test_namespace;

  // Postconditions:

  // Exit:

  return 0;
}
