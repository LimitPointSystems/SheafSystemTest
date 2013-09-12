
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

/// @example section_spaces/fields.t.cc
/// Unit test for test.

#include "abstract_poset_member.h"
#include "array_section_dof_map.h"
#include "at0.h"
#include "at0_space.h"
#include "at1_space.h"
#include "base_space_factory.h"
#include "fiber_bundles_namespace.impl.h"
#include "index_space_iterator.h"
#include "postorder_iterator.h"
#include "poset.h"
#include "schema_poset_member.h"
#include "section_space_schema_poset.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e2.h"
#include "sec_st2_e2.h"
#include "sec_stp_space.h"
#include "section_dof_iterator.h"
#include "section_space_schema_poset.h"
#include "assert_contract.h"
#include "sparse_section_dof_map.h"
#include "st2_e2.h"
#include "stp_space.h"
#include "std_cctype.h"
#include "std_cstdlib.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "triangle_connectivity.h"
#include "zone_nodes_block.h"

using namespace fiber_bundle;



// Put all the functions and typedefs in the unnamed namepsace

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

  double delx = 1.0/edge_ct_x;
  double dely = 1.0/edge_ct_y;


  // allocate dofs as single index array,
  // but treat as dofs[nx+1][ny+1][2];

  int dofs_ub = node_ct_x*node_ct_y*2;
  double* dofs = new double[dofs_ub];

  for(int i=0; i<node_ct_x; i++)
  {
    double x = i*delx;
    for(int j=0; j<node_ct_y; j++)
    {
      double y = j*dely;
      int node_id = NODE_ID(i,j);
      dofs[2*node_id] = x;
      dofs[2*node_id+1] = y;
    }
  }

  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}

sec_at1_space&
make_coord_section_space(fiber_bundles_namespace& xns,
			 const poset_path& xbase_path,
			 int edge_ct_x,
			 int edge_ct_y)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // Make the section space schema arguments.

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase_path, "");

  // Make the scalar section space schema.

  poset_path lscalar_schema_path =
    xns.new_scalar_section_space_schema<sec_at0>("at0_on_triangle_mesh_schema", largs);

  // Make the vector section space schema.

  poset_path lvector_schema_path =
    xns.new_vector_section_space_schema<sec_e2>("e2_on_triangle_mesh_schema", largs);

  // Make the section space.

  sec_at1_space& result =
    xns.new_vector_section_space<sec_e2>("e2_on_triangle_mesh",
					 "", // xvector_space_args
					 lvector_schema_path,
					 "at0_on_triangle_mesh",
					 "", // xscalar_space_args
					 lscalar_schema_path);

  result.get_read_write_access();

  // Create a field in the section space

  sec_e2 lfield(&result);
  lfield.put_name("coord field", true, false);

  Dof_tuple dofs = make_coord_field_dofs(edge_ct_x, edge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

Dof_tuple make_scalar_field_dofs(int edge_ct_x, int edge_ct_y)
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

sec_at0_space&
make_scalar_section_space(fiber_bundles_namespace& xns,
			  const poset_path& xbase_path,
			  int edge_ct_x,
			  int edge_ct_y)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // Make the section space schema arguments.

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase_path, "");

  // Make the schema.

  poset_path lschema_path =
    xns.new_scalar_section_space_schema<sec_at0>("at0_on_triangle_mesh_schema", largs);

  // Make the section space arguments.

  largs = sec_at0_space::make_arg_list();

  // Make the section space.

  sec_at0_space& result =
    xns.new_scalar_section_space<sec_at0>("at0_on_triangle_mesh", largs, lschema_path);

  result.get_read_write_access();

  // Create a field with an array_section_dof_map (the default).

  sec_at0 lfield(&result);
  lfield.put_name("scalar field", true, false);

  Dof_tuple dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Create a field with an array_section_dof_map.

  array_section_dof_map* lafld_map = new array_section_dof_map(&result);
  sec_at0 lafield(&result, lafld_map);
  lafield.put_name("array_section_dof_map", true, false);

  index_space_iterator& aitr =
    lafield.schema().row_dof_id_space().get_iterator();
  double i = 0.0;
  while(!aitr.is_done())
  {
    lafield.put_dof(aitr.pod(), &i, sizeof(double));
    aitr.next();
    i += 1.0;
  }
  lafield.schema().row_dof_id_space().release_iterator(aitr);

  // Create a field with a sparse_section_dof_map.

  sparse_section_dof_map* lsfld_map = new sparse_section_dof_map(&result);
  sec_at0 lsfield(&result, lsfld_map);
  lsfield.put_name("sparse_section_dof_map", true, false);

  index_space_iterator& sitr =
    lsfield.schema().row_dof_id_space().get_iterator();
  i = 1.0;
  while(!sitr.is_done())
  {
    lsfield.put_dof(sitr.pod(), &i, sizeof(double));
    sitr.next();
  }
  lsfield.schema().row_dof_id_space().release_iterator(aitr);

  // Detach members so destructor won't complain

  lfield.detach_from_state();
  lafield.detach_from_state();
  lsfield.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

sec_at0_space&
make_scalar_section_space_2(fiber_bundles_namespace& xns,
			    const poset_path& xbase_path,
			    int edge_ct_x,
			    int edge_ct_y)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // Make the section space schema arguments.

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase_path, "");

  // Make the schema.

  poset_path lschema_path =
    xns.new_scalar_section_space_schema<sec_at0>("at0_on_triangle_mesh_2_schema", largs);

  // Make the section space arguments.

  largs = sec_at0_space::make_arg_list();

  // Make the section space.

  sec_at0_space& result =
    xns.new_scalar_section_space<sec_at0>("at0_on_triangle_mesh_2", largs, lschema_path);

  result.get_read_write_access();

  // Create a field with an array_section_dof_map (the default).

  sec_at0 lfield(&result);
  lfield.put_name("scalar field", true, false);

  Dof_tuple dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Create a field with an array_section_dof_map.

  array_section_dof_map* lafld_map = new array_section_dof_map(&result);
  sec_at0 lafield(&result, lafld_map);
  lafield.put_name("array_section_dof_map", true, false);

  index_space_iterator& aitr =
    lafield.schema().row_dof_id_space().get_iterator();
  double i = 0.0;
  while(!aitr.is_done())
  {
    lafield.put_dof(aitr.pod(), &i, sizeof(double));
    aitr.next();
    i += 1.0;
  }
  lafield.schema().row_dof_id_space().release_iterator(aitr);
  
  // Create a field with a sparse_section_dof_map.

  sparse_section_dof_map* lsfld_map = new sparse_section_dof_map(&result);
  sec_at0 lsfield(&result, lsfld_map);
  lsfield.put_name("sparse_section_dof_map", true, false);

  index_space_iterator& sitr =
    lsfield.schema().row_dof_id_space().get_iterator();
  i = 1.0;
  while(!sitr.is_done())
  {
    lsfield.put_dof(sitr.pod(), &i, sizeof(double));
    sitr.next();
  }
  lsfield.schema().row_dof_id_space().release_iterator(aitr);

  // Detach members so destructor won't complain

  lfield.detach_from_state();
  lafield.detach_from_state();
  lsfield.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

Dof_tuple make_stress_field_dofs(int edge_ct_x, int edge_ct_y)
{
  // Creates a "stress" field on a rectangular array of triangles.
  // Used to test instantiation fo st2 field; values of field are meaningless.
  // edge_ct_x = number of edges in x-dir
  // edge_ct_y = number of edgs in y-dir
  //
  // Number of nodes in x-dir = edge_ct_x+1 and
  // similarly for y-dir.

  // Preconditions:

  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // allocate dofs as single index array,
  // but treat as dofs[edge_ct_x][edge_ct_y][3];

  int dofs_ub = edge_ct_x*edge_ct_y*2*3; // 2 triangles for each edge pair, 3 components
  double* dofs = new double[dofs_ub];

  int tri_ct = 0;

  for(int i=0; i<edge_ct_x; i++)
  {
    for(int j=0; j<edge_ct_y; j++)
    {
      // Each (i,j) pair is the lower-left-hand node in
      // a quad containing two triangles.

      // Stress for lower triangle in quad,

      dofs[3*tri_ct]   = tri_ct+0.0; // xx component
      dofs[3*tri_ct+1] = tri_ct+0.1; // xy component
      dofs[3*tri_ct+2] = tri_ct+0.2; // yy component

      //    for(int l=0; l<3; l++) cout << " " << dofs[3*tri_ct+l];
      //    cout << endl;

      tri_ct++;

      // Stress for upper triangle in quad,

      dofs[3*tri_ct]   = tri_ct+0.0; // xx component
      dofs[3*tri_ct+1] = tri_ct+0.1; // xy component
      dofs[3*tri_ct+2] = tri_ct+0.2; // yy component

      //    for(int l=0; l<3; l++) cout << " " << dofs[3*tri_ct+l];
      //    cout << endl;

      tri_ct++;
    }
  }


  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}

sec_stp_space&
make_stress_section_space(fiber_bundles_namespace& xns,
			  const poset_path& xbase_path,
			  int edge_ct_x,
			  int edge_ct_y)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // Make the section space schema arguments.

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase_path, "");

  // Make the scalar section space schema.

  poset_path lscalar_schema_path =
    xns.new_scalar_section_space_schema<sec_at0>("at0_on_triangle_mesh_schema", largs);

  // Make the vector section space schema.

  poset_path lvector_schema_path =
    xns.new_vector_section_space_schema<sec_e2>("e2_on_triangle_mesh_schema", largs);

  // Make the tensor section space schema.

  poset_path ltensor_schema_path =
    xns.new_tensor_section_space_schema<sec_st2_e2>("st2_e2_on_triangle_mesh_schema",
						    largs, "",
						    "sec_rep_descriptors/element_element_constant");

  // Make the section space.

  sec_stp_space& result =
    xns.new_tensor_section_space<sec_st2_e2>("st2_e2_on_triangle_mesh",
					     "", // xtensor_space_args
					     ltensor_schema_path,
					     "e2_on_triangle_mesh",
					     "", // xvector_space_args
					     lvector_schema_path,
					     "at0_on_triangle_mesh",
					     "", // xscalar_space_args
					     lscalar_schema_path);
  result.get_read_write_access();

  // Create a field with an array_section_dof_map (the default).

  sec_st2_e2 lfield(&result);
  lfield.put_name("stress tensor", true, false);

  Dof_tuple dofs = make_stress_field_dofs(edge_ct_x, edge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Create a field with a sparse_section_dof_map.

  sparse_section_dof_map* lsfld_map = new sparse_section_dof_map(&result);
  sec_st2_e2 lsfield(&result, lsfld_map);
  lsfield.put_name("sparse_section_dof_map", true, false);

  int ltri_ct = 2*edge_ct_x*edge_ct_y;
  double* lst2_e2_xx_component_dofs = new double[ltri_ct];
  for(int i=0; i<ltri_ct; i++)
  {
    lst2_e2_xx_component_dofs[i] = i+10;
  }

  schema_poset_member lst2_e2_xx_component(&(result.schema().host()->fiber_schema()), "xx");

  lsfield.put_component(lst2_e2_xx_component.index(),
			lst2_e2_xx_component_dofs,
			ltri_ct*sizeof(double), false);


  // Clean up; detach members so destructor won't complain

  lfield.detach_from_state();
  lsfield.detach_from_state();
  lst2_e2_xx_component.detach_from_state();
  delete [] lst2_e2_xx_component_dofs;

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

// } // end anonymous namespace

int main(int xargc, char* xargv[])
{

  string filename = filename_from_cmdline(*xargv);

  size_type edge_ct_x = 1;
  if (xargc > 1)
    edge_ct_x = atoi(xargv[1]);

  size_type edge_ct_y = 1;
  if (xargc > 2)
    edge_ct_y = atoi(xargv[2]);


  fiber_bundles_namespace lns(filename);

  lns.get_read_write_access();

  // Make triangle mesh

  base_space_poset& lmesh =
    lns.new_base_space<zone_nodes_block>("triangle_mesh",
					 "",
					 "",
					 2,
					 true);
  lmesh.get_read_write_access();

  // Make triangle block base space

  triangle_connectivity lconn(edge_ct_x, edge_ct_y);

  zone_nodes_block lbase(lmesh, lconn, true);
  lbase.put_name("triangle_block", true, false);

  poset_path lbase_path = lbase.path(true);

  // Make the section spaces

  // Make an e2 section space.

  sec_at1_space& le2_space =
    make_coord_section_space(lns, lbase_path, edge_ct_x, edge_ct_y);

  // Make a scalar section space.

  sec_at0_space& lat0_space =
    make_scalar_section_space(lns, lbase_path, edge_ct_x, edge_ct_y);

  // Make a second scalar section space using the same fiber space.

  sec_at0_space& lat0_space_2 =
    make_scalar_section_space_2(lns, lbase_path, edge_ct_x, edge_ct_y);

  // Make a st2_e2 section space.

  sec_stp_space& lst2_e2_space =
    make_stress_section_space(lns, lbase_path, edge_ct_x, edge_ct_y);

  cout << lns << endl;

  // Save the namespace to a file

  storage_agent sa(filename + ".hdf");
  sa.write_entire(lns);

  // Clean-up

  lbase.detach_from_state();
  lmesh.release_access();

  return 0;
}

