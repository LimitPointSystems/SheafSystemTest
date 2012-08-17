
// $RCSfile: one_material_with_source_2d.t.cc,v $ $Revision: 1.9 $ $Date: 2012/03/01 00:41:39 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example one_material_with_source_2d.t.cc
///
/// Test case with a source in a single element and a single material.
///
/// Square domain (5x5) with T=0 on x=0 and y=0.
///
/// Adiabatic (symmetry) on x=5 and y=5.
///
/// Number of elements determined by i_size and j_size.
///
/// Heat generation rate for element 0 (corner where x=y=0) set
/// to Q/(element area) with Q = 100.
///
/// Element area = (5*5)/(i_size*j_size).
///
/// Thermal conductivity, k = 2.0.

/// @file
/// Implementation for test case one_material_with_source_2d.t

#include "assert_contract.h"
#include "array_index_map.h"
#include "banded_algebraic_system.h"
#include "banded_pde_solver.h"
#include "base_space_poset.h"
#include "bilinear_2d.h"
#include "block_connectivity.h"
#include "direct_banded_solver.h"
#include "fiber_bundles_namespace.h"
#include "poisson_eqn.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e2.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "subposet.h"
#include "unstructured_block.h"

using namespace solvers;

// Typedefs to facilitate some shorthand.

///
/// The type of cell (element).
///
typedef block_connectivity::cell_type cell_type;

///
/// The type of local coordinate;
/// the scalar type for the local coordinate vector space.
///
typedef chart_point_coord_type coord_type;

///
/// The type of component in the value;
/// the scalar type in the range vector space.
///
typedef vd_value_type value_type;

///
/// The type of degree of freedom.
///
typedef sec_vd_dof_type dof_type;

// Names (paths) for the sections.

poset_path coordinates_path("coordinate_section_space/coordinates_0");
poset_path dirichlet_bcs_path("dirichlet_bc_section_space/dirichlet_bcs_0");
poset_path neumann_bcs_path("neumann_bc_section_space/neumann_bcs_0");
poset_path conductivities_path("material_section_space/conductivities_0");
poset_path heat_generation_rates_path("material_section_space/heat_generation_rates_0");

poset_path mesh_base_path("mesh_base_space/unstructured_block_0");
poset_path dirichlet_bcs_base_path("mesh_base_space/dirichlet_bcs_block_0");
poset_path neumann_bcs_base_path("mesh_base_space/neumann_bcs_block_0");

// Forward declarations.

void make_test_case(fiber_bundles_namespace& xns,
                    size_type xi_size,
                    size_type xj_size,
                    cell_type xcell_type);

void make_base_space(fiber_bundles_namespace& xns,
                     size_type xi_size,
                     size_type xj_size,
                     cell_type xcell_type);

void make_mesh_block(base_space_poset& xmesh_poset,
                     size_type xi_size,
                     size_type xj_size,
                     cell_type xcell_type);

void make_neumann_bc_block(base_space_poset& xmesh_poset,
                           size_type xi_size,
                           size_type xj_size,
                           cell_type xcell_type);

void make_dirichlet_bc_block(base_space_poset& xmesh_poset,
                             size_type xi_size,
                             size_type xj_size,
                             cell_type xcell_type);

void make_coordinates(fiber_bundles_namespace& xns,
                      size_type xi_size,
                      size_type xj_size);

void make_neumann_bcs(fiber_bundles_namespace& xns,
                      size_type xi_size,
                      size_type xj_size);

void make_dirichlet_bcs(fiber_bundles_namespace& xns,
                        size_type xi_size,
                        size_type xj_size);

void make_material_properties(fiber_bundles_namespace& xns,
                              size_type xi_size,
                              size_type xj_size);

void make_bcs_subposet(base_space_poset& xmesh_poset,
                       unstructured_block& xblock,
                       string xname);

///
/// Main routine.
///
int main(int argc, char* argv[])
{
  // Handle input parameters.

  size_type i_size = 5;
  size_type j_size = 5;
  block_connectivity::cell_type lcell_type = block_connectivity::QUAD;
  //block_connectivity::cell_type lcell_type = block_connectivity::TRIANGLE;

  if(argc >= 3)
  {
    i_size = static_cast<size_type>(atoi(argv[1]));
    j_size = static_cast<size_type>(atoi(argv[2]));
  }

  string filename = "one_material_with_source_2d.hdf";

  //===========================================================================

  // Create a fiber_bundles_namespace and get read-write access.

  fiber_bundles_namespace ns("one_material_with_source_2d.t");
  ns.get_read_write_access();

  // Create posets and poset members in the namespace which represent
  // the mesh, coordinates, boundary conditions and material properties
  // neccessary to describe the problem.

  make_test_case(ns, i_size, j_size, lcell_type);

  //===========================================================================

  // Set up and solve the system of linear equations resulting from the
  // finite element analysis.  Note from this point on, the code is
  // exactly the same for 1d, 2d or 3d.

  // Get handles to the field members required by the poisson_eqn
  // (poisson equation) class constructor.

  ///@todo Use the paths everywhere.

  sec_ed  coordinates(&ns, coordinates_path);
  sec_at0 dirichlet_bcs(&ns, dirichlet_bcs_path);
  //sec_at0 neumann_bcs(&ns, neumann_bcs_path);
  sec_at0 conductivities(&ns, conductivities_path);
  sec_at0 heat_generation_rates(&ns, heat_generation_rates_path);

  //===========================================================================

  // Create an instance of a poisson_eqn describing the problem.

  poisson_eqn the_equation(coordinates,
                           dirichlet_bcs,
                           conductivities,
                           heat_generation_rates);

  // Create a banded_algebraic_system for assembling a linear
  // system for the poisson_eqn.

  banded_algebraic_system the_algebraic_system;

  // Create a direct banded linear equation solver for solving
  // the algebraic_system.

  direct_banded_solver the_linear_solver;

  // Create a pde_solver to direct the solution of the of the problem.

  banded_pde_solver the_pde_solver(the_equation,
                                   the_algebraic_system,
                                   the_linear_solver);

  // Solve the pde. The solution is added to the original namespace.

  the_pde_solver.solve();

  // Print out the solution for testing.

  the_pde_solver.print_solution();

  //cout << ns << endl;

  // Write the namespace containing the solution to a sheaf file.

  cout << "Writing test file \"" << filename << "\"" << endl;

  storage_agent sa(filename);
  sa.write_entire(ns);

  cout << "Test file \"" << filename << "\" write complete." << endl;

  //===========================================================================

  // Detach all of the sections.

  coordinates.detach_from_state();
  dirichlet_bcs.detach_from_state();
  //neumann_bcs.detach_from_state();
  conductivities.detach_from_state();
  heat_generation_rates.detach_from_state();

  //===========================================================================

  return 0;
}

///
/// Make the test case.
///
void make_test_case(fiber_bundles_namespace& xns,
                    size_type xi_size,
                    size_type xj_size,
                    cell_type xcell_type)
{
  make_base_space(xns, xi_size, xj_size, xcell_type);
  make_coordinates(xns, xi_size, xj_size);
  //make_neumann_bcs(xns, xi_size, xj_size);
  make_dirichlet_bcs(xns, xi_size, xj_size);

  make_material_properties(xns, xi_size, xj_size);

}

///
/// Make the base space.
///
void make_base_space(fiber_bundles_namespace& xns,
                     size_type xi_size,
                     size_type xj_size,
                     cell_type xcell_type)
{
  // Make the base space.

  base_space_poset* mesh_poset =
    &xns.new_base_space<unstructured_block>(mesh_base_path.poset_name(),
					    "",
					    "",
					    2,
					    true);

  mesh_poset->get_read_write_access();

  make_mesh_block(*mesh_poset, xi_size, xj_size, xcell_type);
  //make_neumann_bc_block(*mesh_poset, xi_size, xj_size, xcell_type);
  make_dirichlet_bc_block(*mesh_poset, xi_size, xj_size, xcell_type);
}

///
/// Make the mesh block.
///
void make_mesh_block(base_space_poset& xmesh_poset,
                     size_type xi_size,
                     size_type xj_size,
                     cell_type xcell_type)
{
  // Preconditions:

  // Body:

  string eval_name = (xcell_type == block_connectivity::TRIANGLE)
                     ? "triangle_nodes" : "quad_nodes";

  poset_path path(base_space_member::prototypes_poset_name(), eval_name);

  unstructured_block mesh(&xmesh_poset, path, xi_size, xj_size, true);
  mesh.put_name(mesh_base_path.member_name(), true, false);

  mesh.detach_from_state();
}

///
/// Make the neumann bc block.
///
void make_neumann_bc_block(base_space_poset& xmesh_poset,
                           size_type xi_size,
                           size_type xj_size,
                           cell_type xcell_type)
{
  // Preconditions:

  // Body:

  poset_path path(base_space_member::prototypes_poset_name(), "segment_complex");

  int node_ids_ct = 2*xj_size; // segments

  //int* node_ids = new int[node_ids_ct];
  scoped_index* node_ids = new scoped_index[node_ids_ct];

  int index = 0;
  for(size_type j=0; j<xj_size; ++j)
  {
    int n0 = xi_size*(xj_size+1) + j;
    int n1 = n0 + 1;
    //node_ids[index++] = n0;
    //node_ids[index++] = n1;
    node_ids[index++] = scoped_index(n0);
    node_ids[index++] = scoped_index(n1);
  }

  unstructured_block neumann_block(&xmesh_poset, path, node_ids, node_ids_ct, true);
  neumann_block.put_name(neumann_bcs_base_path.member_name(), true, false);

  make_bcs_subposet(xmesh_poset, neumann_block, "__neumann_face_vertices");

  neumann_block.detach_from_state();

  delete [] node_ids;
}

///
/// Make the dirichlet bc block.
///
void make_dirichlet_bc_block(base_space_poset& xmesh_poset,
                             size_type xi_size,
                             size_type xj_size,
                             cell_type xcell_type)
{
  // Preconditions:

  // Body:

  poset_path path(base_space_member::prototypes_poset_name(), "segment_complex");

  int node_ids_ct = 2*(xi_size + xj_size); // segments

  //int* node_ids = new int[node_ids_ct];
  scoped_index* node_ids = new scoped_index[node_ids_ct];

  // Side y = 0.

  int index = 0;
  for(size_type i=0; i<xi_size; ++i)
  {
    int n0 = i * (xj_size + 1);
    int n1 = n0 + (xj_size + 1);
    //node_ids[index++] = n0;
    //node_ids[index++] = n1;
    node_ids[index++] = scoped_index(n0);
    node_ids[index++] = scoped_index(n1);
  }

  // Side x  = 0;

  for(size_type j=0; j<xj_size; ++j)
  {
    int n0 = j;
    int n1 = n0 + 1;
    //node_ids[index++] = n0;
    //node_ids[index++] = n1;
    node_ids[index++] = scoped_index(n0);
    node_ids[index++] = scoped_index(n1);
  }

  //   int index = 0;
  //   for(size_type i=0; i<xi_size; ++i)
  //   {
  //     int n0 = i + (i + 1)*xj_size;
  //     int n1 = n0 + (xj_size + 1);
  //     node_ids[index++] = n0;
  //     node_ids[index++] = n1;
  //   }

  //   for(size_type j=0; j<xj_size; ++j)
  //   {
  //     int n0 = j + (xj_size + 1)*xi_size;
  //     int n1 = n0 + 1;
  //     node_ids[index++] = n0;
  //     node_ids[index++] = n1;
  //   }

  unstructured_block dirichlet_block(&xmesh_poset, path, node_ids, node_ids_ct, true);
  dirichlet_block.put_name(dirichlet_bcs_base_path.member_name(), true, false);

  make_bcs_subposet(xmesh_poset, dirichlet_block, "__dirichlet_face_vertices");

  dirichlet_block.detach_from_state();

  delete [] node_ids;
}

///
/// Make the coordinates.
///
void make_coordinates(fiber_bundles_namespace& xns,
                      size_type xi_size,
                      size_type xj_size)
{
  // Preconditions:

  // Body:

  // Make coordinate space.

  string name = coordinates_path.poset_name();

  sec_rep_space& coordinates_space = xns.new_section_space<sec_e2>(coordinates_path,
								   mesh_base_path,
								   "sec_rep_descriptors/vertex_element_dlinear",
								   true);
  coordinates_space.get_read_write_access();
  
  // Add dofs to the coordinate space.

  dof_type xmin = 0.0;
  dof_type ymin = 0.0;

  dof_type xmax = 5.0;
  dof_type ymax = 5.0;

  dof_type corner_coordinates[8] =
    {
      xmin, ymin,
      xmax, ymin,
      xmax, ymax,
      xmin, ymax
    };

  block<dof_type> coords;
  size_type dofs_ct = coordinates_space.schema().row_dof_ct();
  coords.reserve(dofs_ct);
  coords.set_ct(dofs_ct);

  bilinear_2d evaluator;

  dof_type local_coordinates[2];
  dof_type values[2];

  dof_type delu = 2.0/xi_size;
  dof_type delv = 2.0/xj_size;

  size_type i_vertex_size = xi_size + 1;
  size_type j_vertex_size = xj_size + 1;

  for(int i=0; i<i_vertex_size; ++i)
  {
    local_coordinates[0] = i*delu - 1.0;

    for(int j=0; j<j_vertex_size; ++j)
    {
      local_coordinates[1] = j*delv - 1.0;

      evaluator.value_at_coord(corner_coordinates,
                               8,
                               local_coordinates,
                               2,
                               values,
                               2);

      int index = 2*(i*(xj_size+1) + j);

      coords[index++] = values[0];
      coords[index]   = values[1];
    }
  }

  sec_e2 coordinates(&coordinates_space);
  coordinates.put_name(coordinates_path.member_name(), true, false);

  for(int i=0; i<coords.ct()/2; ++i)
  {
    coordinates.put_fiber(i, &coords.base()[2*i], 2*sizeof(sec_e2::dof_type));
  }

  coordinates.detach_from_state();

  // Postconditions:

}

///
/// Make the neumann bcs section.
///
void make_neumann_bcs(fiber_bundles_namespace& xns,
                      size_type xi_size,
                      size_type xj_size)
{
  // Preconditions:

  // Body:

  string name = neumann_bcs_path.poset_name();

  sec_rep_space& neumann_bc_space = xns.new_section_space<sec_at0>(neumann_bcs_path,
								   neumann_bcs_base_path,
								   "sec_rep_descriptors/neumann_vertex_face_dlinear_2D",
								   true);
  neumann_bc_space.get_read_write_access();
  
  // Add dofs to the space.

  sec_at0 neumann_bcs(&neumann_bc_space);
  neumann_bcs.put_name(neumann_bcs_path.member_name(), true, false);

  sec_at0::fiber_type::volatile_type lfiber = 100.0;
  neumann_bcs = lfiber; // same value for all.

  neumann_bcs.detach_from_state();

  // Postconditions:

}

///
/// Make the dirichlet bcs section.
///
void make_dirichlet_bcs(fiber_bundles_namespace& xns,
                        size_type xi_size,
                        size_type xj_size)
{
  // Preconditions:

  // Body:

  string name = dirichlet_bcs_path.poset_name();

  sec_rep_space& dirichlet_bc_space = xns.new_section_space<sec_at0>(dirichlet_bcs_path,
								     dirichlet_bcs_base_path,
								     "sec_rep_descriptors/dirichlet_vertex_face_dlinear_2D",
								     true);
  dirichlet_bc_space.get_read_write_access();
  
  // Add dofs to the space.

  sec_at0 dirichlet_bcs(&dirichlet_bc_space);
  dirichlet_bcs.put_name(dirichlet_bcs_path.member_name(), true, false);

  sec_at0::fiber_type::volatile_type lfiber = 0.0;
  dirichlet_bcs = lfiber; // same value for all.

  dirichlet_bcs.detach_from_state();

  // Postconditions:

}

///
/// Make the material properties.
///
void make_material_properties(fiber_bundles_namespace& xns,
                              size_type xi_size,
                              size_type xj_size)
{
  // Preconditions:

  // Body:

  // We are using the same poset for both conductivities
  // and heat_generation_rates.

  string name = conductivities_path.poset_name();

  sec_rep_space& material_space = xns.new_section_space<sec_at0>("material_section_space",
								 mesh_base_path,
								 "sec_rep_descriptors/element_element_constant",
								 true);
  material_space.get_read_write_access();

  // Add conductivity dofs to the space.

  sec_at0 conductivities(&material_space);
  conductivities.put_name(conductivities_path.member_name(), true, false);

  sec_at0::fiber_type::volatile_type lfiber = 2.0;
  conductivities = lfiber; // same value for all.

  conductivities.detach_from_state();

  // Add heat generation rate dofs to the space.

  sec_at0 heat_generation_rates(&material_space);
  heat_generation_rates.put_name(heat_generation_rates_path.member_name(), true, false);

  lfiber = 0.0;
  heat_generation_rates = lfiber;

  // Give the element clossect to the origin a non zero value.
  // Ensure the total source value is constant for different xi_size and xj_size.

  double dx = 5.0/xi_size;
  double dy = 5.0/xj_size;

  lfiber = 100.0/(dx*dy);
  heat_generation_rates.put_fiber(0, lfiber);

  heat_generation_rates.detach_from_state();

  // Postconditions:

}

///
/// Make the bcs subposet.
///
void make_bcs_subposet(base_space_poset& xmesh_poset,
                       unstructured_block& xblock,
                       string xname)
{
  subposet face_vertices_sp(&xmesh_poset);
  face_vertices_sp.put_name(xname, true, false);

  face_vertices_sp.new_id_space("array_index_map", array_index_map::make_arg_list(0));
  mutable_index_map& sp_id_map = face_vertices_sp.id_map();

  postorder_iterator itr(xblock, "__vertices");

  while(!itr.is_done())
  {
    scoped_index index = itr.index();
    face_vertices_sp.insert_member(index);
    sp_id_map.push_back(index);

    itr.next();
  }

  face_vertices_sp.detach_from_state();
}
