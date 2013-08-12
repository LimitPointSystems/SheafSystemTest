
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example posets/poset.t.cc
/// test driver for poset cluster

#include "abstract_poset_member.h"
#include "arg_list.h"
#include "block.h"
#include "mutable_index_space_handle.h"
#include "index_space_iterator.h"
#include "sheaves_namespace.h"
#include "hash_index_space_state.h"
#include "namespace_poset_member.h"
#include "poset.h"
#include "poset_member.h"
#include "poset_member_iterator.h"
#include "postorder_member_iterator.h"
#include "primitives_poset.h"
#include "primitives_poset_schema.h"
#include "assert_contract.h"
#include "std_string.h"
#include "storage_agent.h"
#include "subposet.h"
#include "subposet_member_iterator.h"
#include "tern.h"
#include "total_poset_member.h"
#include "wsv_block.h"

#include "sheaf.h"

using namespace sheaf;

poset* R2_schema;

poset* cells;

total_poset_member *t, *e0, *e1,*e2, *v0, *v1, *v2;

///
/// Test creating an empty poset.
/// Also tests poset with same name as namespace.
///
void empty_poset_test(sheaves_namespace& xns)
{
  poset_path lschema_path = xns.primitives().schema(true).path(true);
  poset::new_table(xns, "poset.t", lschema_path, true);
}

///
/// Output the top level posets.
///
void new_top_level_test(sheaves_namespace& xns)
{

  // Preconditions:

  // Body:

  cout << endl << "*** ENTERING NEW_TOP_LEVEL_TEST *************************" << endl;

  // Get read-write access to the namespace.

  xns.get_read_write_access();

  // Iterate over its jims.

  cout << "iterating over jims of the namespace" << endl;

  postorder_member_iterator itr(xns.top(), "jims", DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    cout << itr.item().index() << "  ";
    itr.next();
  }
  cout << endl;

  // Print out its members.

  cout << "the namespace contains: " << endl;

  cout << dynamic_cast<poset_state_handle&>(xns) << endl;

  // Make handles for the primitive types.

  cout << "primitives poset contains: " << endl;
  cout << xns.primitives() << endl;

  // Print out primitives_poset_schema.

  cout << "primitives poset schema contains:" << endl;
  cout << xns.primitives_schema() << endl;

  // Make a schema for use later.

  R2_schema = &xns.new_schema_poset("R2_schema", true);
  
  wsv_block<schema_descriptor> ldofs_specs("x_component DOUBLE false y_component DOUBLE false");
  schema_poset_member lschema(xns, "R2_schema", "R2_schema/bottom", ldofs_specs, true);
  lschema.detach_from_state();  

  // Print out the entire namespace.

  cout << "the namespace contains: " << endl;

  cout << xns << endl;

  // Release access to all posets.

  xns.release_access();

  cout << "*** LEAVING NEW_TOP_LEVEL_TEST *************************" << endl << endl;

  // Postconditions:

  // Exit

  return;
}

///
/// Test multiple poset names.
///
void multiple_names_test(sheaves_namespace& xns)
{

  // Preconditions:

  // Body:

  cout << endl << "*** ENTERING MULTIPLE_NAMES_TEST *************************" << endl;

  // Get read-write access to the namespace

  xns.get_read_write_access();

  // Give top and bottom alternate names.

  xns.top().put_name("everything", false, false);
  xns.bottom().put_name("nothing", false, false);

  // Give the whole and jims subposets alternate names.

  xns.jims().put_name("join-irreducible-members", false, false);

  // Give the components of R2 alternate names.

  R2_schema->get_read_write_access();
  total_poset_member lx(R2_schema, "x_component");
  lx.put_name("x", false, false);
  lx.put_name("x0", false, false);
  lx.detach_from_state();
  total_poset_member ly(R2_schema, "y_component");
  ly.put_name("y", false, false);
  ly.put_name("x1", false, false);
  ly.detach_from_state();

  // Print out the entire namespace.

  cout << xns << endl;
  R2_schema->release_access();
  xns.release_access();

  cout << "*** LEAVING MULTIPLE_NAMES_TEST *************************" << endl << endl;

  // Postconditions:

  // Exit

  return;
}

///
/// Test a product represention.
///
void product_rep_test(sheaves_namespace& xns)
{
  cout << endl << "*** ENTERING PRODUCT_REP_TEST *************************" << endl;

  total_poset_member::new_host(xns, "R2", "R2_schema/R2_schema", true);
  poset& R2 = xns.member_poset<poset>("R2", true);

  R2.get_read_write_access();

  total_poset_member mbr(&R2);
  mbr.put_name("zero", true, false);
  double dofs[2] = {0.0,0.0};
  mbr.put_dof_tuple(dofs, sizeof(dofs));

  mbr.new_jim_state(&R2);
  mbr.put_name("i-hat", true, false);
  dofs[0] = 1.0;
  dofs[1] = 0.0;
  mbr.put_dof_tuple(dofs, sizeof(dofs));

  mbr.new_jim_state(&R2);
  mbr.put_name("j-hat", true, false);
  dofs[0] = 0.0;
  dofs[1] = 1.0;
  mbr.put_dof_tuple(dofs, sizeof(dofs));

  mbr.detach_from_state();

  cout << "R2:" << endl;

  cout << R2 << endl;

  R2.release_access();

  cout << "*** LEAVING PRODUCT_REP_TEST *************************" << endl << endl;

  return;
}

///
/// Test creating jims.
///
void new_jim_test(sheaves_namespace& xns)
{

  // Preconditions:

  // Body:

  cout << "*** ENTERING NEW_JIM_TEST *************************" << endl;

  // Make a triangle.

  //       t
  //       *
  //      ***
  //     * * *
  //    *  *  *
  //   *   *   *
  // e0    e1   e2
  // *     *     *
  // **   ***   **
  // * * * * * * *
  // *  *  *  *  *
  // * * * * * * *
  // **   ***   **
  // *     *     *
  // v0    v1   v2

  // Create a poset; schema will include a single pod_index_type dof.
  
  poset_path lschema_path = xns.primitives().pod_index_type_type().path();

  poset::new_table(xns, "cells", lschema_path, true);
  cells = &xns.member_poset<poset>("cells", true);
  

  cells->get_read_write_access();

  // Create some id spaces.

  arg_list largs = hash_index_space_state::make_arg_list(0);

  // Create vertices id space.

  pod_index_type lid =
    cells->member_id_spaces(false).new_secondary_state("__vertices",
						       "hash_index_space_state",
						       largs, true);
  mutable_index_space_handle lv_id_space(cells->member_id_spaces(false), lid);

  // Create edge id space.

  lid = cells->member_id_spaces(false).new_secondary_state("__edges",
							   "hash_index_space_state",
							   largs, true);
  mutable_index_space_handle le_id_space(cells->member_id_spaces(false), lid);

  // Create triangle id space.

  lid = cells->member_id_spaces(false).new_secondary_state("__triangles",
							   "hash_index_space_state",
							   largs, true);
  mutable_index_space_handle lt_id_space(cells->member_id_spaces(false), lid);

  // Create 1 based vertices id space.

  lid = cells->member_id_spaces(false).new_secondary_state("__1_based_vertices",
							   "hash_index_space_state",
							   largs, true);
  mutable_index_space_handle lv1_id_space(cells->member_id_spaces(false), lid);

  cells->begin_jim_edit_mode(false);

  total_poset_member* v = new total_poset_member(cells, 0, false, false);
  v->put_name("standard vertex", true, false);
  int dof = 2;
  v->put_dof_tuple(&dof,sizeof(dof));

  total_poset_member* e = new total_poset_member(cells, 0, false, false);
  e->put_name("standard edge", true, false);
  dof = 3;
  e->put_dof_tuple(&dof,sizeof(dof));


  t  = new total_poset_member(cells, 0, false, false);
  t->put_name("standard triangle", true, false);
  dof = 4;
  t->put_dof_tuple(&dof,sizeof(dof));
  lt_id_space.push_back(t->index());


  e0 = new total_poset_member(cells, 0, false, false);
  e0->put_name("e0", true, false);
  dof = 3;
  e0->put_dof_tuple(&dof,sizeof(dof));
  le_id_space.push_back(e0->index());

  e1 = new total_poset_member(cells, 0, false, false);
  e1->put_name("e1", true, false);
  dof = 3;
  e1->put_dof_tuple(&dof,sizeof(dof));
  le_id_space.push_back(e1->index());

  e2 = new total_poset_member(cells, 0, false, false);
  e2->put_name("e2", true, false);
  dof = 3;
  e2->put_dof_tuple(&dof,sizeof(dof));
  le_id_space.push_back(e2->index());

  v0 = new total_poset_member(cells, 0, false, false);
  v0->put_name("v0", true, false);
  dof = 2;
  v0->put_dof_tuple(&dof,sizeof(dof));
  lv_id_space.push_back(v0->index());
  lv1_id_space.insert(1, v0->index());

  v1 = new total_poset_member(cells, 0, false, false);
  v1->put_name("v1", true, false);
  dof = 2;
  v1->put_dof_tuple(&dof,sizeof(dof));
  lv_id_space.push_back(v1->index());
  lv1_id_space.insert(2, v1->index());

  v2 = new total_poset_member(cells, 0, false, false);
  v2->put_name("v2", true, false);
  dof = 2;
  v2->put_dof_tuple(&dof,sizeof(dof));
  lv_id_space.push_back(v2->index());
  lv1_id_space.insert(3, v2->index());

  t->create_cover_link(e0);
  t->create_cover_link(e1);
  t->create_cover_link(e2);

  e0->create_cover_link(v0);
  e0->create_cover_link(v1);

  e1->create_cover_link(v0);
  e1->create_cover_link(v2);

  e2->create_cover_link(v1);
  e2->create_cover_link(v2);

  cells->end_jim_edit_mode(true, false);

  // Print out the poset

  cout << endl << "Cells poset contains:" << endl;

  cout << *cells << endl;

  // release access to namespace

  cells->release_access();

  cout << "*** LEAVING NEW_JIM_TEST *************************" << endl;


  // Postconditions:

  // Exit

  return;
}

///
/// Test creating jrms.
///
void new_jrm_test(sheaves_namespace& xns)
{

  // Preconditions:

  // Body:

  cout << "*** ENTERING NEW_JRM_TEST *********************" << endl << endl;


  // Get read-write access to the namespace.

  xns.get_read_write_access();
  cells->get_read_write_access();

  // Now make some jrms in the cells lattice.

  // Jrm containing 2 vertices;
  // test joiner using internal scope.

  scoped_index vertex2_ids[2] = {v0->index(), v1->index()};

  total_poset_member vertexs2;
  vertexs2.new_jrm_state(cells, vertex2_ids, 2, tern::TRUE, false);
  vertexs2.put_name("2 vertices", true, false);

  cout << "Cells lattice with 2 vertexs jrm:" << endl;
  cout << *cells << endl;

  // Jrm containing other 2 vertices; 
  // test joiner using __vertices scope

  scoped_index lv1_id(v1->index(), *cells, "__vertices");
  scoped_index lv2_id(v2->index(), *cells, "__vertices");
  
  //  scoped_index vertexo2_ids[2] = {v2->index(), v1->index()};
  scoped_index vertexo2_ids[2] = {lv2_id, lv1_id};

  total_poset_member vertexso2;
  vertexso2.new_jrm_state(cells, vertexo2_ids, 2, tern::TRUE, false);
  vertexso2.put_name("other 2 vertices", true, false);


  cout << "Cells lattice with other 2 vertexs jrm:" << endl;
  cout << *cells << endl;

  // Join of vertexs2 and vertexso2.

  total_poset_member* vertexs2o2 = vertexs2.l_join(&vertexso2);
  vertexs2o2->put_name("2 join other 2", true, false);

  cout << "Cells lattice with vertex pairs joined jrm:" << endl;
  cout << *cells << endl;

  // Jrm containing all vertices;
  // test joiner using 1-based vertex ids.

  scoped_index lv0_1_id(v0->index(), *cells, "__1_based_vertices");
  scoped_index lv1_1_id(v1->index(), *cells, "__1_based_vertices");
  scoped_index lv2_1_id(v2->index(), *cells, "__1_based_vertices");

  scoped_index vertex_ids[3] = {lv0_1_id, lv1_1_id, lv2_1_id};

  total_poset_member vertexs(cells, vertex_ids, 3, tern::TRUE, false);
  vertexs.put_name("all vertices", true, false);


  cout << "Cells lattice with vertexs jrm:" << endl;
  cout << *cells << endl;

  // Jrm containing all edges.
  // Use the direct jrm constructor and direct linking.

  cells->begin_jim_edit_mode();

  // Create the jrm

  total_poset_member edges;
  edges.new_jrm_state(cells, false);
  edges.put_name("edges", true, false);

  // Jrm goes between the triangle and its current lower cover.
  // Unlink the triangle from its lower cover.

  t->delete_cover_link(&vertexs);
  t->delete_cover_link(e0);
  t->delete_cover_link(e1);
  t->delete_cover_link(e2);

  // Link the jrm.

  t->create_cover_link(&edges);
  edges.create_cover_link(&vertexs);
  edges.create_cover_link(e0);
  edges.create_cover_link(e1);
  edges.create_cover_link(e2);

  cells->end_jim_edit_mode();

  cout << "Cells lattice with edges jrm:" << endl;
  cout << *cells << endl;

  // Clean up.

  edges.detach_from_state();
  vertexs.detach_from_state();
  vertexso2.detach_from_state();
  vertexs2.detach_from_state();

  cells->release_access();
  xns.release_access();

  cout << "*** LEAVING NEW_JRM_TEST ***********************" << endl << endl;

  // Postconditions:

  // Exit

  return;
}

///
/// Output the subposets xns.
///
void
subposet_iterator_test(sheaves_namespace& xns)
{
  // Preconditions:

  // Body:

  cout << "**** ENTERING SUBPOSET ITERATOR TEST **********************" << endl;

  // test index iterator via poset member iterator

  xns.get_read_access();

  // Create an unattached subposet handle

  subposet lsp;

  // Iterate over the subposets in xns.

  index_space_iterator& lsp_itr = xns.get_subposet_id_space_iterator();
  scoped_index lsp_id = xns.subposet_id(false);
  while(!lsp_itr.is_done())
  {
    lsp_id = lsp_itr.pod();
    
    // Attach the subposet handle to the current subposet state

    lsp.attach_to_state(&xns, lsp_id);

    // Print out the subposet index and name

    cout << "subposet " << lsp.index() << " " << lsp.name();

    // Iterate over the members of the current subposet

    cout << ":\tmembers ";
    subposet_member_iterator* itr = lsp.member_iterator();
    while(!itr->is_done())
    {
      cout << " " << itr->index();
      itr->next();
    }
    cout << endl;
    delete itr;

    // Move to the next subposet

    lsp_itr.next();
  }

  xns.release_subposet_id_space_iterator(lsp_itr);

  // Detach so state won't be deleted when handle
  // goes out of scope.

  lsp.detach_from_state();

  xns.release_access();

  cout << "**** LEAVING SUBPOSET ITERATOR TEST **********************" << endl << endl;

  // Postconditions:

  // Exit

  return;
}

///
/// Output the members of xns.
///
void
output_namespace_members(sheaves_namespace& xns)
{

  cout << endl << "ENTERING OUTPUT_NAMESPACE_MEMBERS" << endl << endl;

  poset_state_handle* ns_mbr;

  xns.get_read_access();

  subposet_member_iterator itr(xns.whole());

  while(!itr.is_done())
  {
    if(itr.is_jim())
    {
      ns_mbr = &xns.member_poset(itr.index(), true);
      cout << *ns_mbr << endl;
    }

    itr.next();
  }

  xns.release_access();

  cout << endl << "LEAVING OUTPUT_NAMESPACE_MEMBERS" << endl << endl;

  return;
}

///
/// The main routine for this test driver.
///
int main(int xargc, char *xargv[])
{

  string filename = filename_from_cmdline(*xargv);
  
  // Create top level poset with primitive type defintions
  
  sheaves_namespace lns(filename);

  empty_poset_test(lns);

  new_top_level_test(lns);

  multiple_names_test(lns);

  product_rep_test(lns);

  new_jim_test(lns);
  
  new_jrm_test(lns);

  subposet_iterator_test(lns);

  // Write it to a file;
  // need read-write access in order to write it.

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(64);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(lns);

  cout << static_cast<poset_state_handle&>(lns) << endl;

  return 0;
}

