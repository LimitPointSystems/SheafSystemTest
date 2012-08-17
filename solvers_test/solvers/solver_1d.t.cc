
// $RCSfile: solver_1d.t.cc,v $ $Revision: 1.9 $ $Date: 2012/03/01 00:41:39 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example solver_1d.t.cc
/// This is a a very simple 1d test case.  It was chosen because it has an
/// exact solution which is easy to obtain.  It is really a 1d problem governed
/// by the equation
///
///    (kT,x),x + Q = 0 on (0<x<L);
///
/// where the ",x" denotes the derivative  with respect x.
/// The boundary conditions are
///
///    T    = D  at x=0 (Dirichlet bc)
///    kT,x = N  at x=L (Neumann bc)
///
/// where k, the thermal conductivity, and Q, the heat generation rate,
/// are constant throughout the volume.
///
/// Straightforward integration of the governing equation yields
///
///    T(x) = ((A - Qx/2)x)/k + B;
///
/// Integration constants A and B are determined from the boundary
/// conditions giving
///
///    T(x) = D + ((N+Q(L-x/2))x)/k;
///
/// With specific values
///
///    k = 2
///    Q = 4
///    D = 10
///    N = 100
///
/// the solution specializes to
///
///     T(x) = 10 + (60 -x)x
///
/// For 1d we specify a line of length L. The number of elements is given by
/// i_size. Specifying T = D at x=0 and kT,x = N at x=L is equivalent to the
/// above 1d problem and should yield the exact solution since a finite element
/// analysis using linear elements produces the exact solution (at the nodes)
/// for this problem.

/// @file
/// Implementation for test case solver_1d.t

#include "assert_contract.h"
#include "array_index_map.h"
#include "banded_algebraic_system.h"
#include "banded_pde_solver.h"
#include "base_space_poset.h"
#include "block_connectivity.h"
#include "direct_banded_solver.h"
#include "fiber_bundles_namespace.h"
#include "linear_1d.h"
#include "poisson_eqn.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e1.h"
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
                    cell_type xcell_type);

void make_base_space(fiber_bundles_namespace& xns,
                     size_type xi_size,
                     cell_type xcell_type);

void make_mesh_block(base_space_poset& xmesh_poset,
                     size_type xi_size,
                     cell_type xcell_type);

void make_neumann_bc_block(base_space_poset& xmesh_poset,
                           size_type xi_size,
                           cell_type xcell_type);

void make_dirichlet_bc_block(base_space_poset& xmesh_poset,
                             size_type xi_size,
                             cell_type xcell_type);

void make_coordinates(fiber_bundles_namespace& xns,
                      size_type xi_size);

void make_neumann_bcs(fiber_bundles_namespace& xns,
                      size_type xi_size);

void make_dirichlet_bcs(fiber_bundles_namespace& xns,
                        size_type xi_size);

void make_material_properties(fiber_bundles_namespace& xns);

void make_bcs_subposet(base_space_poset& xmesh_poset,
                       unstructured_block& xblock,
                       string xname);

void print_solution(pde_solver& xpde_solver);

double exact_solution(dof_type x);

///
/// Main routine.
///
int main(int argc, char* argv[])
{
  // Handle input parameters.

  size_type i_size = 5;
  block_connectivity::cell_type lcell_type = block_connectivity::LINE;

  if(argc >= 2)
  {
    i_size = static_cast<size_type>(atoi(argv[1]));
  }

  string filename = "solver_1d.hdf";

  //===========================================================================

  // Create a fiber_bundles_namespace and get read-write access.

  fiber_bundles_namespace ns("solver_1d.t");
  ns.get_read_write_access();

  // Create posets and poset members in the namespace which represent
  // the mesh, coordinates, boundary conditions and material properties
  // neccessary to describe the problem.

  make_test_case(ns, i_size, lcell_type);

  //===========================================================================

  // Set up and solve the system of linear equations resulting from the
  // finite element analysis.  Note from this point on, the code is
  // exactly the same for 1d, 2d or 3d.

  // Get handles to the field members required by the poisson_eqn
  // (poisson equation) class constructor.

  sec_ed  coordinates(&ns, coordinates_path);
  sec_at0 dirichlet_bcs(&ns, dirichlet_bcs_path);
  sec_at0 neumann_bcs(&ns, neumann_bcs_path);
  sec_at0 conductivities(&ns, conductivities_path);
  sec_at0 heat_generation_rates(&ns, heat_generation_rates_path);

  // Create an instance of a poisson_eqn describing the problem.

  poisson_eqn the_equation(coordinates,
                           dirichlet_bcs,
                           neumann_bcs,
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

  print_solution(the_pde_solver);

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
  neumann_bcs.detach_from_state();
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
                    cell_type xcell_type)
{
  make_base_space(xns, xi_size, xcell_type);
  make_coordinates(xns, xi_size);
  make_neumann_bcs(xns, xi_size);
  make_dirichlet_bcs(xns, xi_size);

  make_material_properties(xns);
}

///
/// Make the base space.
///
void make_base_space(fiber_bundles_namespace& xns,
                     size_type xi_size,
                     cell_type xcell_type)
{
  // Make the base space.

  base_space_poset* mesh_poset =
    &xns.new_base_space<unstructured_block>(mesh_base_path.poset_name(),
					    "",
					    "",
					    1,
					    true);

  mesh_poset->get_read_write_access();

  make_mesh_block(*mesh_poset, xi_size, xcell_type);
  make_neumann_bc_block(*mesh_poset, xi_size, xcell_type);
  make_dirichlet_bc_block(*mesh_poset, xi_size, xcell_type);
}

///
/// Make the mesh block.
///
void make_mesh_block(base_space_poset& xmesh_poset,
                     size_type xi_size,
                     cell_type xcell_type)
{
  // Preconditions:

  // Body:

  poset_path path(base_space_member::prototypes_poset_name(), "segment_complex");

  unstructured_block mesh(&xmesh_poset, path, xi_size, true);
  mesh.put_name(mesh_base_path.member_name(), true, false);

  mesh.detach_from_state();
}

///
/// Make the neumann bc block.
///
void make_neumann_bc_block(base_space_poset& xmesh_poset,
                           size_type xi_size,
                           cell_type xcell_type)
{
  // Preconditions:

  // Body:

  poset_path path(base_space_member::prototypes_poset_name(), "point");

  //int node_ids[1] = {xi_size};
  int ixi_size = xi_size;
  scoped_index node_ids[1] = {scoped_index(ixi_size)};

  unstructured_block neumann_block(&xmesh_poset, path, node_ids, 1, true);
  neumann_block.put_name(neumann_bcs_base_path.member_name(), true, false);

  make_bcs_subposet(xmesh_poset, neumann_block, "__neumann_face_vertices");

  neumann_block.detach_from_state();
}

///
/// Make the dirichlet bc block.
///
void make_dirichlet_bc_block(base_space_poset& xmesh_poset,
                             size_type xi_size,
                             cell_type xcell_type)
{
  // Preconditions:

  // Body:

  poset_path path(base_space_member::prototypes_poset_name(), "point");

  //int node_ids[1] = {0};
  scoped_index node_ids[1] = {scoped_index(0)};

  unstructured_block dirichlet_block(&xmesh_poset, path, node_ids, 1, true);
  dirichlet_block.put_name(dirichlet_bcs_base_path.member_name(), true, false);

  make_bcs_subposet(xmesh_poset, dirichlet_block, "__dirichlet_face_vertices");

  dirichlet_block.detach_from_state();
}

///
/// Make the coordinates.
///
void make_coordinates(fiber_bundles_namespace& xns,
                      size_type xi_size)
{
  // Preconditions:

  // Body:

  // Make coordinate space.

  string name = coordinates_path.poset_name();

  sec_rep_space& coordinates_space = xns.new_section_space<sec_e1>(coordinates_path,
								   mesh_base_path,
								   "sec_rep_descriptors/vertex_element_dlinear",
								   true);
  coordinates_space.get_read_write_access();
  
  // Add dofs to the coordinate space.

  dof_type xmin = 0.0;

  //dof_type xmax = xi_size;
  dof_type xmax = 5.0;

  dof_type dx = (xmax - xmin)/xi_size;

  block<dof_type> coords;
  dof_type x;
  for(int i=0; i<=xi_size; ++i)
  {
    x = i*dx;
    coords.push_back(x);
  }

  sec_e1 coordinates(&coordinates_space);
  coordinates.put_name(coordinates_path.member_name(), true, false);

  for(int i=0; i<coords.ct(); ++i)
  {
    coordinates.put_fiber(i, &coords.base()[i], sizeof(dof_type));
  }

  coordinates.detach_from_state();

  // Postconditions:

}

///
/// Make the neumann bcs section.
///
void make_neumann_bcs(fiber_bundles_namespace& xns,
                      size_type xi_size)
{
  // Preconditions:

  // Body:

  string name = neumann_bcs_path.poset_name();

  sec_rep_space& neumann_bc_space = xns.new_section_space<sec_at0>(neumann_bcs_path,
								   neumann_bcs_base_path,
								   "sec_rep_descriptors/neumann_vertex_face_dlinear_1D",
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
                        size_type xi_size)
{
  // Preconditions:

  // Body:

  string name = dirichlet_bcs_path.poset_name();

  sec_rep_space& dirichlet_bc_space = xns.new_section_space<sec_at0>(dirichlet_bcs_path,
								     dirichlet_bcs_base_path,
								     "sec_rep_descriptors/dirichlet_vertex_face_dlinear_1D",
								     true);
  dirichlet_bc_space.get_read_write_access();
  
  // Add dofs to the space.

  sec_at0 dirichlet_bcs(&dirichlet_bc_space);
  dirichlet_bcs.put_name(dirichlet_bcs_path.member_name(), true, false);

  sec_at0::fiber_type::volatile_type lfiber = 10.0;
  dirichlet_bcs = lfiber; // same value for all.

  dirichlet_bcs.detach_from_state();

  // Postconditions:

}

///
/// Make the material properties.
///
void make_material_properties(fiber_bundles_namespace& xns)
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

  lfiber = 4.0; // same value for all.
  heat_generation_rates = lfiber;

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

///
/// Print the solution.
///
void print_solution(pde_solver& xpde_solver)
{
  cout << "====================================="
  << "=====================================" << endl;

  cout << "Solution:" << endl;

  cout << "====================================="
  << "=====================================" << endl;

  cout << "    Node     Numerical         Exact   Coordinates" << endl;
  cout << "    ====     =========         =====   ===========" << endl;

  const block<dof_type>& solution = xpde_solver.solution();

  const sec_ed& coordinates = xpde_solver.equation().coordinates();

  dof_type dof[1];
  int disc_ct = coordinates.schema().discretization_ct();
  for(int i=0; i<disc_ct; ++i)
  {
    coordinates.get_fiber(i, dof, sizeof(dof_type));

    dof_type x = dof[0];

    double exact = exact_solution(x);

    cout << setw(8) << i
    << "  "
    << setw(12) << solution[i]
    << "  "
    << setw(12) << exact;

    // Print the coordinates.

    cout << "    ";
    cout << setw(10) << dof[0];

    cout << endl;
  }
  cout << "====================================="
  << "=====================================" << endl;
}

///
/// Extract the solution.
///
double exact_solution(dof_type x)
{
  double result = 10.0 + (60.0 - x) * x;

  return result;
}
