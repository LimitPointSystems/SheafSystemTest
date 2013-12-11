
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

/// @example examples/at0.t.cc
/// Test driver for CTB dof tuple stuff.

#include "abstract_poset_member.h"
#include "at0.h"
#include "binary_section_space_schema_poset.h"
#include "std_cctype.h"
#include "unstructured_block.h"
#include "postorder_iterator.h"
#include "namespace_poset.h"
#include "poset.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_e2.h"
#include "sec_st2_e2.h"
#include "section_dof_iterator.h"
#include "assert_contract.h"
#include "std_cstdlib.h"
#include "storage_agent.h"
#include "st2_e2.h"
#include "std_iostream.h"
#include "subposet.h"
#include "vd.h"

using namespace std;
using namespace fiber_bundle;

typedef struct
{
  void* values;
  int values_ub;
}
Dof_tuple;

#define NODE_ID(i, j) ((i)*node_ct_y + (j))

sec_rep_space*
make_scalar_sec_rep_space(fiber_bundles_namespace* test_namespace,
			  abstract_poset_member* xbase,
			  int edge_ct_x,
			  int edge_ct_y);

Dof_tuple make_scalar_field_dofs(int edge_ct_x, int edge_ct_y);

int
main(int argc, char* argv[])
{
  size_t edge_ct_x = 1;

  if (argc > 1)
    edge_ct_x = atoi(argv[1]);

  size_t edge_ct_y = 1;
  if (argc > 2)
    edge_ct_y = atoi(argv[2]);

  fiber_bundles_namespace test_namespace("test");

  test_namespace.get_read_write_access();

  // Make triangle mesh

  base_space_poset* lmesh =
    &test_namespace.new_base_space<unstructured_block>("triangle_mesh", "", "", 2, true);
  lmesh->get_read_write_access();

  // Make triangle block base space

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "triangle_complex");

  unstructured_block lbase_space(lmesh, lproto_path, edge_ct_x, edge_ct_y, true);
  lbase_space.put_name("triangle_block", true, false);

  // Make the sec_rep_spaces

  sec_rep_space* lat0_srs =
    make_scalar_sec_rep_space(&test_namespace, &lbase_space, edge_ct_x, edge_ct_y);

  cout << test_namespace << endl;

  storage_agent at0_agent("at0.t.hdf");

  cout << endl << "#### writing output file ####" << endl << endl;

  at0_agent.write_entire(test_namespace);

  // Clean-up

  lbase_space.detach_from_state();
  lmesh->release_access();

  return 0;
}

sec_rep_space*
make_scalar_sec_rep_space(fiber_bundles_namespace* test_namespace,
                          abstract_poset_member* xbase,
                          int edge_ct_x,
                          int edge_ct_y)
{
  sec_rep_space* result;

  // Preconditions:

  require(test_namespace != 0);
  require(xbase != 0);
  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // Create the scalar section space

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase->path(false), "");

  poset_path lschema_path =
    test_namespace->new_scalar_section_space_schema<sec_at0>("at0_on_triangle_mesh_schema", largs);

  largs = sec_at0_space::make_arg_list();

  result = &test_namespace->new_scalar_section_space<sec_at0>("at0_on_triangle_mesh",
							      largs, lschema_path);

  // Create a field in the section space

  result->get_read_write_access();

  sec_at0 lfield(result);
  lfield.put_name("scalar", true, false);

  Dof_tuple dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  result->release_access();

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

Dof_tuple
make_scalar_field_dofs(int edge_ct_x, int edge_ct_y)
{
  // Creates a scalar on a rectangular triangle mesh.
  // edge_ct_x = number of edges in x-dir
  // edge_ct_y = number of edgs in y-dir
  //
  // Number of nodes in x-dir = edge_ct_x+1 and
  // similarly for y-dir.

  // Preconditions:

  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  int node_ct_x = edge_ct_x+1;
  int node_ct_y = edge_ct_y+1;

  double delx = 1.0;
  double dely = 1.0;


  // allocate dofs as single index array,
  // but treat as dofs[nx+1][ny+1][2];

  int dofs_ub = node_ct_x*node_ct_y;
  double* dofs = new double[dofs_ub];

  for(int i=0; i<node_ct_x; i++)
  {
    double x = i*delx;
    for(int j=0; j<node_ct_y; j++)
    {
      double y = j*dely;
      int node_id = NODE_ID(i,j);
      dofs[node_id] = x*x + y*y;
    }
  }

  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}




