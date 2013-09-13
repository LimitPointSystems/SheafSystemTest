
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

/// @example io/write_col_decomposition.t.cc
/// Test driver for test.

//#include "abstract_poset_member.h"
//#include "poset_bounds_descriptor.h"
#include "fiber_bundles_namespace.h"
#include "poset_path.h"
#include "poset.h"
#include "sec_rep_descriptor.h"
#include "sec_rep_space.h"
#include "sec_rep_space_member.h"
#include "section_dof_iterator.h"
#include "sheaves_namespace.h"
#include "assert_contract.h"
#include "std_string.h"
#include "std_strstream.h"
#include "storage_agent.h"
#include "subposet_member_iterator.h"
#include "total_poset_member.h"

using namespace sheaf;

namespace
{

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

string block_names[BLOCK_CT] =
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
      edge_itr->put_name(mbr_name, true, true);
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
      vertex_itr->put_name(mbr_name, true, true);
    }
    vertex_itr->next();
  }
  vertices.detach_from_state();
}

poset*
make_base_space(namespace_poset* xns)
{
  poset* result;

  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());

  // Create mesh poset

//   result = new poset(xns,
//                      "local_coordinates_schema/local_coordinates_schema",
//                      "polyline");
  fiber_bundles_namespace* lns = dynamic_cast<fiber_bundles_namespace*>(xns);
  result = &lns->new_base_space<structured_block>("polyline",
				       "",
				       "local_coordinates_schema/local_coordinates_schema",
				       "",
				       true);

  // Create each member of the block decomposition.

  result->get_read_write_access();
  result->begin_jim_edit_mode();

  subposet lblocks_sp(result);
  lblocks_sp.put_name("blocks", true, false);

  total_poset_member lblock;
  hash_map<int, int> glue_map;

  for(int i=0; i<BLOCK_CT; i++)
  {
    cout << "creating block " << i << endl;

    lblock.new_block_state(result,
                           "cell definitions/edge",
                           block_conn[i],
                           BLOCK_CONN_CT,
                           &glue_map);

    lblock.put_name(block_names[i]);
    lblocks_sp.insert_member(&lblock);
  }

  result->end_jim_edit_mode();

  lblock.detach_from_state();
  lblocks_sp.detach_from_state();

  name_mesh_cells(result);

  result->release_access();
  result->get_read_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_read_accessible());

  return result;
}

poset*
make_fiber_schema(namespace_poset* xns)
{
  poset* result;

  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());

  // Body:

  primitives_poset& primitives = xns->primitives();

  // Make a new poset

  result = new poset( xns, &(primitives.schema()), "R2_schema");

  result->get_read_write_access();

  subposet ltable_dofs(result);
  subposet lrow_dofs(result);

  result->begin_jim_edit_mode();

  // Make the jims

  total_poset_member lmbr;
  lmbr.new_jim_state(result, &(primitives.int_type().dof_map(false)));
  lmbr.put_name("dim", true, false);
  ltable_dofs.insert_member(&lmbr);

  lmbr.new_jim_state(result, &(primitives.double_type().dof_map(false)));
  lmbr.put_name("x_comp", true, false);
  lrow_dofs.insert_member(&lmbr);

  lmbr.new_jim_state(result, &(primitives.double_type().dof_map(false)));
  lmbr.put_name("y_comp", true, false);
  lrow_dofs.insert_member(&lmbr);

  result->end_jim_edit_mode();

  result->schematize(&ltable_dofs, &lrow_dofs, true);

  lmbr.detach_from_state();
  ltable_dofs.detach_from_state();
  lrow_dofs.detach_from_state();

  result->release_access();
  result->get_read_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_read_accessible());

  // Exit

  return result;
}

sec_rep_descriptor*
make_sec_rep_descriptor(namespace_poset* xns)
{
  sec_rep_descriptor* result;

  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());

  // Body:

  primitives_poset& primitives = xns->primitives();

  // Make a sec rep descriptor

  poset* sec_rep_desc = sec_rep_descriptor::new_host(xns, "sec_rep_descriptors");

  sec_rep_desc->get_read_write_access();

  sec_rep_desc->begin_jim_edit_mode();

  result = new sec_rep_descriptor(sec_rep_desc,
                                  "__vertices",
                                  "",
                                  "__elements",
                                  "dlinear",
                                  "www.lpsweb.com/libSheaf/std_namespace.html",
                                  1);

  result->put_name("vertex_element_dlinear", true, false);

  sec_rep_desc->end_jim_edit_mode();
  result->release_access();
  result->get_read_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_read_accessible());

  // Exit

  return result;
}

sec_rep_space_member*
make_test_field(namespace_poset* xns, const poset* xmesh)
{
  sec_rep_space_member* result;

  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());
  require(xmesh != 0);
  require(xmesh->state_is_read_accessible());

  // Body:

  (void) make_fiber_schema(xns);

  sec_rep_descriptor* ldesc = make_sec_rep_descriptor(xns);

  int ldim = 2;

  sec_rep_space* lsrs = new sec_rep_space(&(xmesh->top()),
                                          "R2_schema/top",
                                          ldesc,
                                          "scalar_on_polyline",
                                          &ldim,
                                          sizeof(ldim),
                                          true);

  lsrs->get_read_write_access();
  lsrs->begin_jim_edit_mode();

  result = new sec_rep_space_member(lsrs);
  result->put_name("test_field", true, false);

  lsrs->end_jim_edit_mode();

  double ldof;
  int i = 0;
  section_dof_iterator* itr = result->schema().row_dof_iterator();
  while(!itr->is_done())
  {
    ldof = i++;
    result->dof_map().put_dof(itr->item(), &ldof, sizeof(ldof));
    itr->next();
  }

  lsrs->release_access();
  lsrs->get_read_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_read_only_accessible());

  // Exit:

  return result;
}
  
} // unnamed namespace

///
int
main(int xargc, char* xargv[])
{

  // Body:

  sheaves_namespace* ns =
    new sheaves_namespace("write_col_decomposition.t");
  ns->get_read_write_access();

  // Make the base space.

  poset* mesh = make_base_space(ns);
  subposet ldecomp(mesh, "blocks");

  // Make the test field.

  sec_rep_space_member* lfield = make_test_field(ns, mesh);

  // Output a text version

  // cout << *ns << endl;

  // Initialize the storage agent; opens the file.

  storage_agent sa("write_col_decomposition.t.hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(64);
  sa.put_dof_tuple_record_buffer_ub(15);

  //   sa.write_entire(*ns);

  // Write the name space itself.
  // In the current implementation, the namespace poset must be the first poset
  // written and no members can be added or removed from it until the file is closed.

  sa.write(*ns);

  // Write the mesh decomposition

  sa.write_row_decomposition(*mesh, ldecomp.index());

  // Write table of contents of the mesh;

  sa.write_toc(*mesh, ldecomp.index());

  // Write the sec_rep_space.

  sa.write_col_decomposition(*(lfield->host()), lfield->index(), ldecomp.index());

  sa.write(*(lfield->host()));

  ldecomp.detach_from_state();

  mesh->release_access();

  // Write the remainder of the name space.

  sa.write_remainder(*ns);

  delete ns;

  // Postconditions:

  // Exit:

  return 0;
}
