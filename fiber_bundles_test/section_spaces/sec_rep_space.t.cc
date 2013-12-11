
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

/// @example section_spaces/sec_rep_space.t.cc
/// test driver for class sec_rep_space


#include "arg_list.h"
#include "assert_contract.h"
#include "base_space_member.h"
#include "binary_section_space_schema_poset.h"
#include "block.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "index_iterator.h"
#include "namespace_poset_member.h"
#include "poset.h"
#include "poset_member_iterator.h"
#include "postorder_member_iterator.h"
#include "primitives_poset.h"
#include "primitives_poset_schema.h"
#include "product_index_space.h"
#include "sec_at1_space.h"
#include "sec_e2.h"
#include "sec_rep_descriptor_poset.h"
#include "sec_rep_space.h"
#include "sec_rep_space_member.h"
#include "section_space_schema_poset.h"
#include "std_string.h"
#include "storage_agent.h"
#include "subposet.h"
#include "subposet_member_iterator.h"

using namespace std;
using namespace fiber_bundle;

// Set this filename in accordance with the OS type.

#ifdef _WIN32
  const string filename = "sec_rep_space.t.exe";
  const string hdf_filename = "sec_rep_space.t.exe.hdf";
#else
  const string filename = "sec_rep_space.t";
  const string hdf_filename = "sec_rep_space.t.hdf";
#endif

//
// OBSOLETE: This test driver is obsolete and is only in the repository
// until it can be determined if it needs reimplemented.
//

///
/// @todo Reimplement this test driver or remove it from the repository.
///

fiber_bundles_namespace* test_namespace;

poset* R2_schema;
total_poset_member *dim, *x_comp, *y_comp;

poset* R2;


base_space_poset* cells;

///
void make_triangle(fiber_bundles_namespace* xns)
{
  // Preconditions:

  require(xns != 0);

  // Body:

  // make a triangle


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

  // Get read-write access to the namespace

  xns->get_read_write_access(true);

  cells = &base_space_member::standard_host(*xns, "cells", 3, false);

  poset_state_handle* lprototypes_poset =
    xns->member_poset(base_space_member::prototypes_poset_name(), false);

  lprototypes_poset->get_read_access();
  cells->begin_jim_edit_mode();

  base_space_member* t  = new base_space_member(cells, "triangle_complex", false, false);
  t->put_name("standard_triangle", true, false);

  base_space_member* e0 = new base_space_member(cells, "segment_complex", false, false);
  e0->put_name("e0", true, false);

  base_space_member* e1 = new base_space_member(cells, "segment_complex", false, false);
  e1->put_name("e1", true, false);

  base_space_member* e2 = new base_space_member(cells, "segment_complex", false, false);
  e2->put_name("e2", true, false);

  base_space_member* v0 = new base_space_member(cells, "point", false, false);
  v0->put_name("v0", true, false);

  base_space_member* v1 = new base_space_member(cells, "point", false, false);
  v1->put_name("v1", true, false);

  base_space_member* v2 = new base_space_member(cells, "point", false, false);
  v2->put_name("v2", true, false);

  t->create_cover_link(e0);
  t->create_cover_link(e1);
  t->create_cover_link(e2);

  e0->create_cover_link(v0);
  e0->create_cover_link(v1);

  e1->create_cover_link(v0);
  e1->create_cover_link(v2);

  e2->create_cover_link(v1);
  e2->create_cover_link(v2);

  cells->end_jim_edit_mode();
  lprototypes_poset->release_access();

  cells->get_read_write_access();

  cout << *cells << endl;

  // release access to namespace

  xns->release_access();


  // Postconditions:

  // Exit

  return;
}

void make_fiber_schema()
{

  // Preconditions:

  // Body:

  // Get read-write access to the namespace

  test_namespace->get_read_write_access();

  primitives_poset& primitives = test_namespace->primitives();

  // make a new poset

  arg_list largs = poset::make_args();

  R2_schema = &test_namespace->new_member_poset<poset>("R2_schema", primitives.schema().path(), largs, true);

  // Enter edit mode

  R2_schema->begin_jim_edit_mode();

  subposet ltable_dofs(R2_schema);
  subposet lrow_dofs(R2_schema);

  // make the jims

  dim = new total_poset_member(R2_schema, &(primitives.int_type().dof_map(false)), false, false);
  dim->put_name("dim", true, false);
  ltable_dofs.insert_member(dim);

  x_comp = new total_poset_member(R2_schema, &(primitives.double_type().dof_map(false)), false, false);
  x_comp->put_name("x_comp", true, false);
  lrow_dofs.insert_member(x_comp);

  y_comp = new total_poset_member(R2_schema, &(primitives.double_type().dof_map(false)), false, false);
  y_comp->put_name("y_comp", true, false);
  lrow_dofs.insert_member(y_comp);

  // Exit edit mode

  R2_schema->end_jim_edit_mode();

  // get read-write access to it

  R2_schema->get_read_write_access();

  R2_schema->schematize(&ltable_dofs, &lrow_dofs, true);

  ltable_dofs.detach_from_state();
  lrow_dofs.detach_from_state();

  // release access to all posets

  R2_schema->release_access();
  test_namespace->release_access();

  // Postconditions:

  // Exit

  return;
}


void make_section_space_definitions()
{

  // Preconditions:

  // Body:

  // Get read-write access to the namespace

  test_namespace->get_read_write_access();

  primitives_poset& primitives = test_namespace->primitives();

  // Make the section space schema schema.

  sec_rep_descriptor_poset::make_standard_schema(*test_namespace);
  section_space_schema_poset::make_standard_schema(*test_namespace);
  binary_section_space_schema_poset::make_standard_schema(*test_namespace);

  // Make some standard sec rep descriptors

  poset_path lschema_path("sec_rep_descriptor_schema", "sec_rep_descriptor_schema");
  arg_list largs = sec_rep_descriptor_poset::make_args();
  
  poset* sec_rep_desc =
    &test_namespace->new_member_poset<sec_rep_descriptor_poset>("sec_rep_descriptors", lschema_path, largs, true);

  sec_rep_desc->get_read_write_access();

  sec_rep_descriptor lsrd;

  lsrd.new_jim_state(sec_rep_desc);
  lsrd.put_name("vertex_element_dlinear", true, false);
  lsrd.put_discretization_subposet_name("vertices");
  lsrd.put_evaluation_subposet_name("elements");
  lsrd.put_evaluator_family_name("dlinear");
  lsrd.put_url("www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html");
  lsrd.put_multiplicity(1);

  lsrd.new_jim_state(sec_rep_desc);
  lsrd.put_name("element_element_constant", true, false);
  lsrd.put_discretization_subposet_name("elements");
  lsrd.put_evaluation_subposet_name("elements");
  lsrd.put_evaluator_family_name("const");
  lsrd.put_url("www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html");
  lsrd.put_multiplicity(1);

  // Make sec rep space definitions group (jrm)

  namespace_poset_member lm1(test_namespace, "sec_rep_descriptor_schema");
  namespace_poset_member lm2(test_namespace, sec_rep_desc->index());

  total_poset_member* sec_defns = lm1.l_join(&lm2);
  sec_defns->put_name("section space definitions", true, false);
  sec_defns->detach_from_state();
  delete sec_defns;

  // Detach all the handles allocated on the stack

  lsrd.detach_from_state();
  lm1.detach_from_state();
  lm2.detach_from_state();

  // Release access

  cout << *test_namespace << endl;

  sec_rep_desc->release_access();
  test_namespace->release_access();


  // Postconditions:

  // Exit

  return;
}



void make_sec_rep_space()
{

  // Preconditions:

  // Body:

  // Get read-write access to the namespace

  test_namespace->get_read_write_access();

  // Make the discretization subposet

  cells->get_read_write_access();
  subposet ldisc(cells, "__vertices");
  mutable_index_map* lmap = ldisc.id_map();

  ldisc.insert_member(scoped_index(6));
  lmap->push_back(scoped_index(6));
  ldisc.insert_member(scoped_index(7));
  lmap->push_back(scoped_index(7));
  ldisc.insert_member(scoped_index(8));
  lmap->push_back(scoped_index(8));

  // Make the evaluation subposet

  subposet leval(cells, "__elements");
  lmap = leval.id_map();
  base_space_member t(cells, "standard_triangle");
  leval.insert_member(&t);
  lmap->push_back(t.index());

  // Finished with the subposet handles

  ldisc.detach_from_state();
  leval.detach_from_state();

  // Get a handle to the rep descriptor

  sec_rep_descriptor lrep_mbr(test_namespace,
			      "sec_rep_descriptors/vertex_element_dlinear");
  lrep_mbr.get_read_access();

  // Make the fiber space.

  int ldim = 2; // Only one table dof, the dimension.

  R2_schema->get_read_access();
  
  //  R2 = new poset(test_namespace, &(R2_schema->top()), "R2", &ldim, sizeof(ldim));

  poset_path lR2_schema_path = R2_schema->top().path();

  arg_list lR2_args;
  lR2_args << "dim" << ldim;
  
  R2 = &test_namespace->new_member_poset<poset>("R2", lR2_schema_path, lR2_args, true);

  R2->get_read_access();

  // Make the sec_rep_space_schema:

  poset_path lsrs_schema =
    test_namespace->new_section_space_schema<sec_rep_space_member>("R2 on triangle",
								   arg_list(),
								   "",
								   lrep_mbr.path(),
								   t.path(),
								   R2->path(),
								   "",
								   "",
								   true);

  // Make the sec rep space

  // $$SCRIBBLE kabuch: Not sure sec_e2 is correct here
  sec_rep_space* lsec_rep_space =
    &test_namespace->new_section_space<sec_e2>("R2 on triangle",
						      arg_list(),
						      lsrs_schema,
						      true);
  
  // Get access

  lsec_rep_space->get_read_write_access();

  cout << "dimension = " << lsec_rep_space->df() << endl;

  // Make a section

  sec_rep_space_member lcoords(lsec_rep_space);
  lcoords.put_name("coordinates", true, false);
  double lcoords_dofs[6] = {0.0, 0.0, 2.0, 0.0, 0.0, 3.0};
  lcoords.put_dof_tuple(lcoords_dofs, sizeof(lcoords_dofs));


  sec_rep_space_member ldisps(lsec_rep_space);
  ldisps.put_name("displacements", true, false);
  double ldisps_dofs[6] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06};

  index_space_iterator* ldof_itr =
    ldisps.schema().row_dof_id_space().iterator(true);
  double *ldof_ptr = ldisps_dofs;
  while(!ldof_itr->is_done())
  {
    ldisps.put_dof(ldof_itr->item().pod(), ldof_ptr, sizeof(double));
    ldof_itr->next();
    ldof_ptr++;
  }

  delete ldof_itr;

  cout << "restriction test:";

  total_poset_member e1(cells, "e1");
  ldisps.restrict_to(&e1, x_comp);

  index_space_iterator* ldof_itr2 =
    ldisps.schema().row_dof_id_space().iterator(true);
  double ldof2;
  while(!ldof_itr2->is_done())
  {
    cout << "  " << ldisps.dof(ldof_itr2->item(), false).to_string();
    ldof_itr2->next();
  }
  cout << endl;

  delete ldof_itr2;

  t.detach_from_state();
  e1.detach_from_state();
  lcoords.detach_from_state();
  ldisps.detach_from_state();

  // release access to all posets

  lsec_rep_space->release_access();
  R2->release_access();
  R2_schema->release_access();
  lrep_mbr.release_access();
  lrep_mbr.detach_from_state();
  cells->release_access();
  test_namespace->release_access();

  // Postconditions:

  // Exit

  return;
}


void
make_member_poset_test()
{

  cout << endl << "####### begin member poset test ####################" << endl << endl;

  test_namespace->get_read_access();

  postorder_member_iterator itr(test_namespace->top(), "jims");
  while(!itr.is_done())
  {
    poset_state_handle* ptr = test_namespace->member_poset(itr.item().index());
    if(dynamic_cast<sec_rep_space*>(ptr) != 0)
    {
      cout << itr.item().name() << " is a sec_rep_space" << endl;
    }
    else if(dynamic_cast<poset*>(ptr) != 0)
    {
      cout << itr.item().name() << " is a poset" << endl;
    }
    else if(dynamic_cast<primitives_poset*>(ptr) != 0)
    {
      cout << itr.item().name() << " is a primitives_poset" << endl;
    }
    else if(dynamic_cast<primitives_poset_schema*>(ptr) != 0)
    {
      cout << itr.item().name() << " is a primitives_poset_schema" << endl;
    }
    else
    {
      cout << itr.item().name() << " is a an unrecognized type" << endl;
    }

    itr.next();
  }

  test_namespace->release_access();

  cout << endl << "####### end member poset test ####################" << endl << endl;

}

int main()
{

  test_namespace = new fiber_bundles_namespace(filename);

  make_triangle(test_namespace);

  cout << *test_namespace << endl;

  make_fiber_schema();

  //  make_section_space_definitions();

  make_sec_rep_space();

  //   make_member_poset_test();

  cout << *test_namespace << endl;

  // Write it to a file; requires read write access.

  test_namespace->get_read_write_access();

  storage_agent sa(hdf_filename, sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(17);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(*test_namespace);

  delete test_namespace;

  return 0;
}


