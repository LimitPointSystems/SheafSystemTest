
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

/// @example examples/torus.t.cc
/// Test driver for test.


#include "assert_contract.h"
#include "binary_section_space_schema_poset.h"
#include "fiber_bundles_namespace.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "std_cmath.h"
#include "storage_agent.h"
#include "std_iostream.h"
#include "unstructured_block.h"

using namespace fiber_bundle;

typedef struct
{
  int* node_ids;
  int node_ids_ub;
}
Connectivity;
typedef struct
{
  void* values;
  int values_ub;
}
Dof_tuple;

#define NODE_ID(i, j) ((i)*node_ct_y + (j))

Dof_tuple make_scalar_field_dofs(int edge_ct_x, int edge_ct_y, int step)
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

  // allocate dofs as single index array,
  // but treat as dofs[nx+1][ny+1][2];

  int dofs_ub = node_ct_x*node_ct_y;
  double* dofs = new double[dofs_ub];

  double R = 2.0;
  double r = 1.0;

  double PI = 4.0*atan(1.0);

  double deltax = 2.0*PI/edge_ct_x;
  double deltay = 2.0*PI/edge_ct_y;

  for(int i=0; i<node_ct_x; i++)
  {
    double alpha = i*deltax;
    double cosa = cos(alpha);
    double sina = sin(alpha);
    for(int j=0; j<node_ct_y; j++)
    {
      double beta = j*deltay;
      double p = R + r*cos(beta);
      double x = p*cosa;
      double y = p*sina;
      double z = r*sin(beta);

      int node_id = NODE_ID(i,j);

      //Note: None of this is meaningful. Just a way to create some
      // different fields.
      double d;
      if (step == 0)
        d = z;
      else if (step == 1)
        d = x;
      else if (step == 2)
        d = x*x + y*y;

      if (fabs(d) < 1.0E-12)
        d = 0.0;

      dofs[node_id] = d;
    }
  }

  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}

sec_at0::host_type&
make_scalar_sec_rep_space(fiber_bundles_namespace& xtest_namespace,
			  abstract_poset_member& xbase,
			  int edge_ct_x,
			  int edge_ct_y)
{
  // Preconditions:

  require(xtest_namespace.state_is_read_write_accessible());
  require(xbase.state_is_read_accessible());
  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // Create the scalar section space

  sec_at0::host_type& result =
    sec_at0::standard_host(xtest_namespace, xbase.path(false), "", "", "", false);

  result.get_read_write_access();

  // Create some fields in the section space

  result.begin_jim_edit_mode();

  sec_at0 lfield0(&result, 0, false);
  lfield0.put_name("temperature 0", true, false);
  Dof_tuple dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y, 0);
  lfield0.put_dof_tuple(dofs.values, dofs.values_ub);

  sec_at0 lfield1(&result, 0, false);
  lfield1.put_name("temperature 1", true, false);
  dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y, 1);
  lfield1.put_dof_tuple(dofs.values, dofs.values_ub);

  sec_at0 lfield2(&result, 0, false);
  lfield2.put_name("temperature 2", true, false);
  dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y, 2);
  lfield2.put_dof_tuple(dofs.values, dofs.values_ub);

  sec_at0 lfield3(&result, 0, false);
  sec_at0::fiber_type::volatile_type lfiber = 1.0;
  lfield3 = lfiber;
  lfield3.put_name("constant=1.0", true, false);

  result.end_jim_edit_mode();

  // Detach members so destructor won't complain

  lfield0.detach_from_state();
  lfield1.detach_from_state();
  lfield2.detach_from_state();
  lfield3.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

Dof_tuple make_coord_field_dofs(int edge_ct_x, int edge_ct_y)
{
  // Creates the coordinates for a rectangular triangle mesh.
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

  // allocate dofs as single index array,
  // but treat as dofs[nx+1][ny+1][3];

  int dofs_ub = node_ct_x*node_ct_y*3;
  double* dofs = new double[dofs_ub];

  double R = 2.0;
  double r = 1.0;

  double PI = 4.0*atan(1.0);

  double deltax = 2.0*PI/edge_ct_x;
  double deltay = 2.0*PI/edge_ct_y;

  for(int i=0; i<node_ct_x; i++)
  {
    double alpha = i*deltax;
    double cosa = cos(alpha);
    double sina = sin(alpha);
    for(int j=0; j<node_ct_y; j++)
    {
      double beta = j*deltay;
      double p = R + r*cos(beta);
      double x = p*cosa;
      double y = p*sina;
      double z = r*sin(beta);

      int node_id = NODE_ID(i,j);

      if (fabs(x) < 1.0E-12)
        x = 0.0;
      if (fabs(y) < 1.0E-12)
        y = 0.0;
      if (fabs(z) < 1.0E-12)
        z = 0.0;

      dofs[3*node_id]   = x;
      dofs[3*node_id+1] = y;
      dofs[3*node_id+2] = z;
    }
  }

  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}

sec_e3::host_type&
make_coord_sec_rep_space(fiber_bundles_namespace& xtest_namespace,
			 abstract_poset_member& xbase,
			 int edge_ct_x,
			 int edge_ct_y)
{
  // Preconditions:

  require(xtest_namespace.state_is_read_write_accessible());
  require(xbase.state_is_read_accessible());
  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // Create the coord section space

  sec_e3::host_type& result =
    sec_e3::standard_host(xtest_namespace, xbase.path(false), "", "", "", false);

  result.get_read_write_access();

  // Create a field in the section space

  sec_e3 lfield(&result);
  lfield.put_name("coordinates", true, false);

  Dof_tuple dofs = make_coord_field_dofs(edge_ct_x, edge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}


int main(int argc, char* argv[])
{
  // Command line argument processing:

  int edge_ct_x = 10;
  if (argc > 1)
    edge_ct_x = atoi(argv[1]);
  if (edge_ct_x < 3)
    edge_ct_x = 3;

  int edge_ct_y = 10;
  if (argc > 2)
    edge_ct_y = atoi(argv[2]);
  if (edge_ct_y < 3)
    edge_ct_y = 3;

  // Preconditions:

  require(edge_ct_x >= 3);
  require(edge_ct_y >= 3);

  fiber_bundles_namespace test_namespace ("torus.t");

  test_namespace.get_read_write_access();

  base_space_poset& lbase_host =
    unstructured_block::standard_host(test_namespace, "torus_mesh", 2, false);

  lbase_host.get_read_write_access();

  unstructured_block lbase_space(&lbase_host,
                                 "base_space_member_prototypes/triangle_nodes",
                                 edge_ct_x,
                                 edge_ct_y,
                                 true);

  // cout << *test_namespace << endl;

  sec_at0::host_type& lat0_srs =
    make_scalar_sec_rep_space(test_namespace, lbase_space,
			      edge_ct_x, edge_ct_y);

  sec_e3::host_type& le3_srs =
    make_coord_sec_rep_space(test_namespace, lbase_space,
			     edge_ct_x, edge_ct_y);

  cout << test_namespace << endl;

  storage_agent sa("torus.t.hdf");

  sa.write_entire(test_namespace);

  // Clean-up

  lbase_space.detach_from_state();
  lbase_host.release_access();

  return 0;
}
