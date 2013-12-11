
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

/// @example fiber.t.cc
/// Test driver for cluster fiber_spaces.

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "at1.h"
#include "at2.h"
#include "at2_e2.h"
#include "at2_e3.h"
#include "atp.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "ed.h"
#include "fiber_bundles_namespace.h"
#include "gl2.h"
#include "gl3.h"
#include "gln.h"
#include "index_space_iterator.h"
#include "jcb.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"
#include "jcb_ed.h"
#include "jcb_ed.h"
#include "met.h"
#include "met_e1.h"
#include "met_e2.h"
#include "met_e3.h"
#include "met_ed.h"
#include "namespace_poset.h"
#include "namespace_poset_member.h"
#include "poset.h"
#include "postorder_member_iterator.h"
#include "primitives_poset_schema.h"
#include "product_index_space.h"
#include "schema_descriptor.h"
#include "sec_rep_descriptor.h"
#include "sec_rep_space.h"
#include "sec_rep_space_member.h"
#include "section_dof_iterator.h"
#include "st2.h"
#include "st2_e2.h"
#include "st2_e3.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "stp.h"
#include "subposet.h"
#include "t2.h"
#include "t2_e2.h"
#include "t2_e3.h"
#include "t3.h"
#include "t3_e3.h"
#include "tuple.h"
#include "tp.h"
#include "vd.h"
#include "wsv_block.h"

using namespace std;
using namespace fiber_bundle;

// Set this filename in accordance with the OS type.


poset* R2_schema;
total_poset_member* x_comp;

//
// OBSOLETE: This test driver is obsolete and is only in the repository
// until it can be determined if it needs reimplemented.
//

///
/// @todo Reimplement this test driver or remove it from the repository.
///

void
make_fiber_schema(fiber_bundles_namespace& xns)
{

  // Preconditions:

  require(xns.is_attached());

  // Body:

  // Get read-write access to the namespace

  xns.get_read_write_access();

  primitives_poset& primitives = xns.primitives();

  // make a new poset

  R2_schema = new poset(&xns, &(primitives.schema()), "R2_schema");

  // Enter edit mode

  R2_schema->begin_jim_edit_mode();

  subposet ltable_dofs(R2_schema);
  subposet lrow_dofs(R2_schema);

  // make the jims

  total_poset_member* dim = new total_poset_member(R2_schema,
                            &(primitives.int_type().dof_map(false)), false, false);
  dim->put_name("dim", true, false);
  ltable_dofs.insert_member(dim);

  x_comp = new total_poset_member(R2_schema,
                                  &(primitives.double_type().dof_map(false)), false, false);
  x_comp->put_name("x_comp", true, false);
  lrow_dofs.insert_member(x_comp);

  total_poset_member* y_comp = new total_poset_member(R2_schema,
                               &(primitives.double_type().dof_map(false)), false, false);
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
  xns.release_access();

  // Postconditions:

  //ensure(ns != 0);
  ensure(xns.is_attached());

  // Exit

  return;
}


void
make_sec_rep_space(fiber_bundles_namespace& xns)
{

  // Preconditions:

  require(xns.state_is_read_accessible());

  // Body:

  // Preliminaries:

  //   get a handle to the base space

  total_poset_member triangle(&xns,"cell definitions/triangle");
  triangle.get_read_write_access();

  //   make the discretization and evaluation subposets

  subposet disc_sp(triangle.host());

  disc_sp.put_name("__vertices", true, false);

  total_poset_member vertex(&xns,"cell definitions/triangle-vertex 0");

  disc_sp.insert_member(&vertex);
  vertex.attach_to_state(&xns,"cell definitions/triangle-vertex 1", false);
  disc_sp.insert_member(&vertex);
  vertex.attach_to_state(&xns,"cell definitions/triangle-vertex 2", false);
  disc_sp.insert_member(&vertex);
  vertex.detach_from_state();

  subposet eval_sp(triangle.host());

  eval_sp.put_name("__elements", true, false);
  eval_sp.insert_member(&triangle);

  //   make the client id_map for the discretization

  disc_sp.new_id_space("array_index_map");
  mutable_index_map* lmap = disc_sp.id_map();

  postorder_member_iterator vitr(triangle, &disc_sp);
  while(!vitr.is_done())
  {
    lmap->push_back(vitr.item().index(), false);
    vitr.next();
  }

  lmap->close();

  disc_sp.detach_from_state();
  eval_sp.detach_from_state();

  make_fiber_schema(xns);

  // Get read-write access to the namespace

  xns.get_read_write_access();

  // Get a handle to the rep descriptor

  sec_rep_descriptor  lrep_mbr(&xns, "sec_rep_descriptors/vertex_element_dlinear");
  lrep_mbr.get_read_access();

  // make the fiber space

  int ldim = 2; // only one table dof, the dimension

  R2_schema->get_read_access();
  poset* R2 = new poset(&xns, &(R2_schema->top()), "R2", &ldim, sizeof(ldim));
  R2->get_read_access();

  // Make the sec rep space

  sec_rep_space* lsec_rep_space = new sec_rep_space(&triangle,
                                  R2,
                                  &lrep_mbr,
                                  "R2 on triangle");
  triangle.detach_from_state();

  // Get access

  lsec_rep_space->get_read_write_access();

  // try to retrieve the table dof

  int ldim2 = 0;

  lsec_rep_space->table_dof_tuple(&ldim2, sizeof(ldim2));
  cout << "table dof: dimension = " << ldim2 << endl;

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
    ldisps.put_dof(ldof_itr->pod(), ldof_ptr, sizeof(double));
    ldof_itr->next();
    ldof_ptr++;
  }
  delete ldof_itr;

  cout << "restriction test:";

  total_poset_member edge1(&xns, "cell definitions/triangle-edge 1");

  ldisps.restrict_to(&edge1, x_comp);

  edge1.detach_from_state();

  index_space_iterator* ldof_itr2 =
    ldisps.schema().row_dof_id_space().iterator(true);
  double ldof2;
  while(!ldof_itr2->is_done())
  {
    ldisps.get_dof(ldof_itr2->pod(), &ldof2, sizeof(ldof2));
    cout << "  " << ldof2;
    ldof_itr2->next();
  }
  cout << endl;

  delete ldof_itr2;

  lcoords.detach_from_state();
  ldisps.detach_from_state();

  // release access to all posets

  lsec_rep_space->release_access();
  R2->release_access();
  R2_schema->release_access();
  lrep_mbr.release_access();
  lrep_mbr.detach_from_state();
  xns.release_access();

  // Postconditions:

  //ensure(ns != 0);
  ensure(xns.state_is_read_accessible());

  // Exit

  return;
}

int
main(int xargc, char* xargv[])
{
  // Create the namespace.

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace ns(filename);
  ns.get_read_write_access();

  // Run tests.

  //...

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  return 0;
}
