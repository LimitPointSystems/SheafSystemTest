

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example section_spaces/section.t.cc
/// Unit test for cluster section_spaces.

#include "arg_list.h"
#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "binary_section_space_schema_poset.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.h"
#include "schema_descriptor.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e2.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "unstructured_block.h"

using namespace fiber_bundle;

namespace
{

///
/// The dof values.
///
typedef struct
{
  void* values;
  int values_ub;
}
Dof_tuple;

#define NODE_ID(i, j) ((i)*node_ct_y + (j))

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

  int dofs_ub = node_ct_x*node_ct_y;
  double* dofs = new double[dofs_ub];

  for(int i=0; i<node_ct_x; i++)
  {
    double x = i*delx;
    for(int j=0; j<node_ct_y; j++)
    {
      double y = j*dely;
      int node_id = NODE_ID(i,j);
      dofs[node_id] = 1.1 * (x*x + y*y); // to see decimal point
    }
  }

  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit:

  return result;
}

Dof_tuple
make_coord_field_dofs(int edge_ct_x, int edge_ct_y)
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

  // Create a field in the section space

  sec_at0 lfield(&result);

  lfield.put_name("scalar field", true, false);

  Dof_tuple dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  result.release_access();

  // Postconditions:

  ensure(result.state_is_not_read_accessible());

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

  lfield.put_name("coordinate field", true, false);

  Dof_tuple dofs = make_coord_field_dofs(edge_ct_x, edge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  result.release_access();

  // Postconditions:

  ensure(result.state_is_not_read_accessible());

  // Exit

  return result;
}

void
test_all(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  size_t edge_ct_x = 2;
  size_t edge_ct_y = 2;

  // Make triangle mesh

  /// @todo Remove.
//   base_space_poset* lmesh = &xns.new_base_space<unstructured_block>("triangle_mesh",
// 								    "",
// 								    "",
// 								    2,
// 								    true);

  unstructured_block::new_host(xns, "triangle_mesh", 2, false);
  base_space_poset& lmesh = xns.member_poset<base_space_poset>("triangle_mesh", false);

  lmesh.get_read_write_access();

  // Make triangle block base space

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "triangle_complex");

  unstructured_block lbase(&lmesh, lproto_path, edge_ct_x, edge_ct_y, true);
  lbase.put_name("triangle_block", true, false);

  poset_path lbase_path = lbase.path(true);

  // Make the section spaces

  sec_at0_space& lscalar_space =
    make_scalar_section_space(xns, lbase_path, edge_ct_x, edge_ct_y);

  sec_at1_space& lcoord_space =
    make_coord_section_space(xns, lbase_path, edge_ct_x, edge_ct_y);

  // Clean-up

  lbase.detach_from_state();
  lmesh.release_access();

  // Postconditions:

  // Exit:

  return;
}

} // end unnamed namespace

///
/// Main test routine.
///

int
main(int xargc, char *xargv[])
{
  // Create the namespace

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace ns(filename);
 
  ns.get_read_write_access();

  // Run the tests.

  test_all(ns);

  // Save the namespace to a file

  storage_agent sa(filename + ".hdf");
  sa.write_entire(ns);

  return 0;
}

