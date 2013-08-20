

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/fields3d.t.cc
/// Test driver for 3D fields.

#include "abstract_poset_member.h"
#include "at0.h"
#include "at0_space.h"
#include "at1_space.h"
#include "atp_space.h"
#include "binary_section_space_schema_poset.h"
#include "zone_nodes_block.h"
#include "triangle_connectivity.h"
#include "postorder_iterator.h"
#include "poset.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_atp_space.h"
#include "sec_e3.h"
#include "sec_st2_e3.h"
#include "sec_stp_space.h"
#include "sec_at2_e3.h"
#include "sec_t2_e3.h"
#include "sec_t3_e3.h"
#include "sec_tp_space.h"
#include "sec_rep_descriptor.h"
#include "section_dof_iterator.h"
#include "stp_space.h"
#include "assert_contract.h"
#include "std_cctype.h"
#include "fiber_bundles_namespace.impl.h"
#include "std_cstdlib.h"
#include "storage_agent.h"
#include "st2_e3.h"
#include "std_iostream.h"
#include "tp_space.h"
#include "subposet.h"
#include "vd.h"
#include "assert_contract.h"

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

bool isFlat;

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
  // but treat as dofs[nx+1][ny+1][3];

  int dofs_ub = node_ct_x*node_ct_y*3;
  double* dofs = new double[dofs_ub];

  for(int i=0; i<node_ct_x; i++)
  {
    double x = i*delx;
    for(int j=0; j<node_ct_y; j++)
    {
      double y = j*dely;
      int node_id = NODE_ID(i,j);
      dofs[3*node_id] = x;
      dofs[3*node_id+1] = y;

      //double z = isFlat ? 0.0 : (x*x+y*y);
      double z = isFlat ? 0.0 : (1.0-x)*x + (1.0-y)*y;
      dofs[3*node_id+2] = z;
    }
  }

  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}




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

  double delx = 1.0/edge_ct_x;
  double dely = 1.0/edge_ct_y;


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

      //Note: None of this is meaningful. Just a way to create some
      // different fields.
      double d;
      if (step == 0)
        d = x*x + y*y;
      else if (step == 1)
        d = (1.0-x)*x + (1.0-y)*y;
      else if (step == 2)
        d = x;
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

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase.path(false), "");

  poset_path lschema_path =
    xtest_namespace.new_scalar_section_space_schema<sec_at0>("at0_on_triangle_mesh_schema", largs);

  largs = sec_at0_space::make_arg_list();

  sec_at0::host_type& result =
    xtest_namespace.new_scalar_section_space<sec_at0>("at0_on_triangle_mesh",
						      largs, lschema_path);

  result.get_read_write_access();

  // Create a field in the section space

  sec_at0 lfield0(&result);
  lfield0.put_name("temperature 0", true, false);
  Dof_tuple dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y, 0);
  lfield0.put_dof_tuple(dofs.values, dofs.values_ub);

  sec_at0 lfield1(&result);
  lfield1.put_name("temperature 1", true, false);
  dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y, 1);
  lfield1.put_dof_tuple(dofs.values, dofs.values_ub);

  sec_at0 lfield2(&result);
  lfield2.put_name("temperature 2", true, false);
  dofs = make_scalar_field_dofs(edge_ct_x, edge_ct_y, 2);
  lfield2.put_dof_tuple(dofs.values, dofs.values_ub);

  // Make a constant field too.
  sec_at0* lconst = new sec_at0(&result);
  sec_at0::fiber_type::volatile_type lfiber = 1.0;
  *lconst = lfiber;
  lconst->put_name("constant=1.0", true, false);

  // Detach members so destructor won't complain

  lfield0.detach_from_state();
  lfield1.detach_from_state();
  lfield2.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

sec_e3::host_type&
make_coord_sec_rep_space(fiber_bundles_namespace& xtest_namespace,
			 abstract_poset_member& xbase,
			 sec_at0::host_type& xscalar_space,
			 int edge_ct_x,
			 int edge_ct_y)
{
  // Preconditions:

  require(xtest_namespace.state_is_read_write_accessible());
  require(xbase.state_is_read_accessible());
  require(xscalar_space.state_is_read_accessible());
  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  // Body:

  // Create the coord section space

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase.path(false), "");

  poset_path lschema_path =
    xtest_namespace.new_vector_section_space_schema<sec_e3>("e3_on_triangle_mesh_schema", largs);

  sec_e3::host_type& result =
    xtest_namespace.new_vector_section_space<sec_e3>("e3_on_triangle_mesh",
						     "",
						     lschema_path,
						     xscalar_space.path(false),
						     "",
						     xscalar_space.schema().path(false));

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

Dof_tuple
make_t2_e3_field_dofs(int xedge_ct_x, int xedge_ct_y)
{
  // Creates a 2nd rank tensor field on a rectangular array of triangles.
  // Used to test instantiation fo t2 field; values of field are meaningless.
  // xedge_ct_x = number of edges in x-dir
  // xedge_ct_y = number of edgs in y-dir
  //
  // Number of nodes in x-dir = xedge_ct_x+1 and
  // similarly for y-dir.

  // Preconditions:

  require(xedge_ct_x > 0);
  require(xedge_ct_y > 0);

  // Body:

  // allocate dofs as single index array,
  // but treat as dofs[xedge_ct_x][xedge_ct_y][9];

  int dofs_ub = xedge_ct_x*xedge_ct_y*2*9; // 2 triangles for each edge pair, 9 components
  double* dofs = new double[dofs_ub];

  int tri_ct = 0;

  for(int i=0; i<xedge_ct_x; i++)
  {
    for(int j=0; j<xedge_ct_y; j++)
    {
      // Each (i,j) pair is the lower-left-hand node in
      // a quad containing two triangles.

      // Components for lower triangle in quad,

      dofs[9*tri_ct]   = tri_ct+0.0; // xx component
      dofs[9*tri_ct+1] = tri_ct+0.1; // xy component
      dofs[9*tri_ct+2] = tri_ct+0.2; // xz component
      dofs[9*tri_ct+3] = tri_ct+0.3; // yx component
      dofs[9*tri_ct+4] = tri_ct+0.4; // yy component
      dofs[9*tri_ct+5] = tri_ct+0.5; // yz component
      dofs[9*tri_ct+6] = tri_ct+0.6; // zx component
      dofs[9*tri_ct+7] = tri_ct+0.7; // zy component
      dofs[9*tri_ct+8] = tri_ct+0.8; // zz component

      tri_ct++;

      // Components for upper triangle in quad,

      dofs[9*tri_ct]   = tri_ct+0.0; // xx component
      dofs[9*tri_ct+1] = tri_ct+0.1; // xy component
      dofs[9*tri_ct+2] = tri_ct+0.2; // xz component
      dofs[9*tri_ct+3] = tri_ct+0.3; // yx component
      dofs[9*tri_ct+4] = tri_ct+0.4; // yy component
      dofs[9*tri_ct+5] = tri_ct+0.5; // yz component
      dofs[9*tri_ct+6] = tri_ct+0.6; // zx component
      dofs[9*tri_ct+7] = tri_ct+0.7; // zy component
      dofs[9*tri_ct+8] = tri_ct+0.8; // zz component

      tri_ct++;
    }
  }


  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}


sec_t2_e3::host_type&
make_t2_e3_sec_rep_space(fiber_bundles_namespace& xtest_namespace,
			 abstract_poset_member& xbase,
			 sec_e3::host_type& xvector_space,
			 sec_at0::host_type& xscalar_space,
			 int xedge_ct_x,
			 int xedge_ct_y)
{
  // Preconditions:

  require(xtest_namespace.state_is_read_write_accessible());
  require(xbase.state_is_read_accessible());
  require(xvector_space.state_is_read_accessible());
  require(xscalar_space.state_is_read_accessible());
  require(xedge_ct_x > 0);
  require(xedge_ct_y > 0);

  // Body:

  // Create the tensor section space

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("sec_rep_descriptors/element_element_constant",
						     xbase.path(false), "");

  poset_path lschema_path =
    xtest_namespace.new_tensor_section_space_schema<sec_t2_e3>("t2_e3_on_triangle_mesh_schema", largs);

  sec_t2_e3::host_type& result =
    xtest_namespace.new_tensor_section_space<sec_t2_e3>("t2_e3_on_triangle_mesh",
							"",
							lschema_path,
							xvector_space.path(false),
							"",
							xvector_space.schema().path(false),
							xscalar_space.path(false),
							"",
							xscalar_space.schema().path(false));

  result.get_read_write_access();

  // Create a field in the section space

  sec_t2_e3 lfield(&result);
  lfield.put_name("f0", true, false);

  Dof_tuple dofs = make_t2_e3_field_dofs(xedge_ct_x, xedge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

Dof_tuple
make_st2_e3_field_dofs(int xedge_ct_x, int xedge_ct_y)
{
  // Creates a symmetric tensor field on a rectangular array of triangles.
  // Used to test instantiation fo st2 field; values of field are meaningless.
  // xedge_ct_x = number of edges in x-dir
  // xedge_ct_y = number of edgs in y-dir
  //
  // Number of nodes in x-dir = xedge_ct_x+1 and
  // similarly for y-dir.

  // Preconditions:

  require(xedge_ct_x > 0);
  require(xedge_ct_y > 0);

  // Body:

  // allocate dofs as single index array,
  // but treat as dofs[xedge_ct_x][xedge_ct_y][6];

  int dofs_ub = xedge_ct_x*xedge_ct_y*2*6; // 2 triangles for each edge pair, 6 components
  double* dofs = new double[dofs_ub];

  int tri_ct = 0;

  for(int i=0; i<xedge_ct_x; i++)
  {
    for(int j=0; j<xedge_ct_y; j++)
    {
      // Each (i,j) pair is the lower-left-hand node in
      // a quad containing two triangles.

      // Stress for lower triangle in quad,

      dofs[6*tri_ct]   = tri_ct+0.0; // xx component
      dofs[6*tri_ct+1] = tri_ct+0.1; // xy component
      dofs[6*tri_ct+2] = tri_ct+0.2; // xz component
      dofs[6*tri_ct+3] = tri_ct+0.3; // yy component
      dofs[6*tri_ct+4] = tri_ct+0.4; // yz component
      dofs[6*tri_ct+5] = tri_ct+0.5; // zz component

      //    for(int l=0; l<3; l++) cout << " " << dofs[3*tri_ct+l];
      //    cout << endl;

      tri_ct++;

      // Stress for upper triangle in quad,

      dofs[6*tri_ct]   = tri_ct+0.0; // xx component
      dofs[6*tri_ct+1] = tri_ct+0.1; // xy component
      dofs[6*tri_ct+2] = tri_ct+0.2; // xz component
      dofs[6*tri_ct+3] = tri_ct+0.3; // yy component
      dofs[6*tri_ct+4] = tri_ct+0.4; // yz component
      dofs[6*tri_ct+5] = tri_ct+0.5; // zz component

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


sec_st2_e3::host_type&
make_st2_e3_sec_rep_space(fiber_bundles_namespace& xtest_namespace,
			  abstract_poset_member& xbase,
			  sec_e3::host_type& xvector_space,
			  sec_at0::host_type& xscalar_space,
                          int xedge_ct_x,
                          int xedge_ct_y)
{
  // Preconditions:

  require(xtest_namespace.state_is_read_write_accessible());
  require(xbase.state_is_read_accessible());
  require(xvector_space.state_is_read_accessible());
  require(xscalar_space.state_is_read_accessible());
  require(xedge_ct_x > 0);
  require(xedge_ct_y > 0);

  // Body:

  // Create the tensor section space

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("sec_rep_descriptors/element_element_constant",
						      xbase.path(false), "");

  poset_path lschema_path =
    xtest_namespace.new_tensor_section_space_schema<sec_st2_e3>("st2_e3_on_triangle_mesh_schema", largs);

  sec_st2_e3::host_type& result =
    xtest_namespace.new_tensor_section_space<sec_st2_e3>("st2_e3_on_triangle_mesh",
							 "",
							 lschema_path,
							 xvector_space.path(false),
							 "",
							 xvector_space.schema().path(false),
							 xscalar_space.path(false),
							 "",
							 xscalar_space.schema().path(false));

  result.get_read_write_access();

  // Create a field in the section space

  sec_st2_e3 lfield(&result);
  lfield.put_name("f0", true, false);

  Dof_tuple dofs = make_st2_e3_field_dofs(xedge_ct_x, xedge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

Dof_tuple
make_at2_e3_field_dofs(int xedge_ct_x, int xedge_ct_y)
{
  // Creates a anti symmetric tensor field on a rectangular array of triangles.
  // Used to test instantiation fo at2 field; values of field are meaningless.
  // xedge_ct_x = number of edges in x-dir
  // xedge_ct_y = number of edgs in y-dir
  //
  // Number of nodes in x-dir = xedge_ct_x+1 and
  // similarly for y-dir.

  // Preconditions:

  require(xedge_ct_x > 0);
  require(xedge_ct_y > 0);

  // Body:

  // allocate dofs as single index array,
  // but treat as dofs[xedge_ct_x][xedge_ct_y][3];

  int dofs_ub = xedge_ct_x*xedge_ct_y*2*3; // 2 triangles for each edge pair, 3 component
  double* dofs = new double[dofs_ub];

  int tri_ct = 0;

  for(int i=0; i<xedge_ct_x; i++)
  {
    for(int j=0; j<xedge_ct_y; j++)
    {
      // Component for upper triangle in quad.

      dofs[3*tri_ct]   = tri_ct+0.0;
      dofs[3*tri_ct+1] = tri_ct+0.1;
      dofs[3*tri_ct+2] = tri_ct+0.2;

      tri_ct++;

      // Component for upper triangle in quad,

      dofs[3*tri_ct]   = tri_ct+0.0;
      dofs[3*tri_ct+1] = tri_ct+0.1;
      dofs[3*tri_ct+2] = tri_ct+0.2;

      tri_ct++;
    }
  }


  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}


sec_at2_e3::host_type&
make_at2_e3_sec_rep_space(fiber_bundles_namespace& xtest_namespace,
			  abstract_poset_member& xbase,
			  sec_e3::host_type& xvector_space,
			  sec_at0::host_type& xscalar_space,
                          int xedge_ct_x,
                          int xedge_ct_y)
{
  // Preconditions:

  require(xtest_namespace.state_is_read_write_accessible());
  require(xbase.state_is_read_accessible());
  require(xvector_space.state_is_read_accessible());
  require(xscalar_space.state_is_read_accessible());
  require(xedge_ct_x > 0);
  require(xedge_ct_y > 0);

  // Body:

  // Create the tensor section space

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("sec_rep_descriptors/element_element_constant",
						      xbase.path(false), "");

  poset_path lschema_path =
    xtest_namespace.new_tensor_section_space_schema<sec_at2_e3>("at2_e3_on_triangle_mesh_schema", largs);

  sec_at2_e3::host_type& result =
    xtest_namespace.new_tensor_section_space<sec_at2_e3>("at2_e3_on_triangle_mesh",
							 "",
							 lschema_path,
							 xvector_space.path(false),
							 "",
							 xvector_space.schema().path(false),
							 xscalar_space.path(false),
							 "",
							 xscalar_space.schema().path(false));

  result.get_read_write_access();

  // Create a field in the section space

  sec_at2_e3 lfield(&result);
  lfield.put_name("f0", true, false);

  Dof_tuple dofs = make_at2_e3_field_dofs(xedge_ct_x, xedge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

Dof_tuple
make_t3_e3_field_dofs(int xedge_ct_x, int xedge_ct_y)
{
  // Creates a 2nd rank tensor field on a rectangular array of triangles.
  // Used to test instantiation fo t3 field; values of field are meaningless.
  // xedge_ct_x = number of edges in x-dir
  // xedge_ct_y = number of edgs in y-dir
  //
  // Number of nodes in x-dir = xedge_ct_x+1 and
  // similarly for y-dir.

  // Preconditions:

  require(xedge_ct_x > 0);
  require(xedge_ct_y > 0);

  // Body:

  // allocate dofs as single index array,
  // but treat as dofs[xedge_ct_x][xedge_ct_y][27];

  int dofs_ub = xedge_ct_x*xedge_ct_y*2*27; // 2 triangles for each edge pair, 27 components
  double* dofs = new double[dofs_ub];

  int tri_ct = 0;

  for(int i=0; i<xedge_ct_x; i++)
  {
    for(int j=0; j<xedge_ct_y; j++)
    {
      // Each (i,j) pair is the lower-left-hand node in
      // a quad containing two triangles.

      // Components for lower triangle in quad,

      dofs[27*tri_ct]    = tri_ct+0.00; // xxx component
      dofs[27*tri_ct+1]  = tri_ct+0.01; // xxy component
      dofs[27*tri_ct+2]  = tri_ct+0.02; // xxz component
      dofs[27*tri_ct+3]  = tri_ct+0.03; // xyx component
      dofs[27*tri_ct+4]  = tri_ct+0.04; // xyy component
      dofs[27*tri_ct+5]  = tri_ct+0.05; // xyz component
      dofs[27*tri_ct+6]  = tri_ct+0.06; // xzx component
      dofs[27*tri_ct+7]  = tri_ct+0.07; // xzy component
      dofs[27*tri_ct+8]  = tri_ct+0.08; // xzz component
      dofs[27*tri_ct+9]  = tri_ct+0.10; // yxx component
      dofs[27*tri_ct+10] = tri_ct+0.11; // yxy component
      dofs[27*tri_ct+11] = tri_ct+0.12; // yxz component
      dofs[27*tri_ct+12] = tri_ct+0.13; // yyx component
      dofs[27*tri_ct+13] = tri_ct+0.14; // yyy component
      dofs[27*tri_ct+14] = tri_ct+0.15; // yyz component
      dofs[27*tri_ct+15] = tri_ct+0.16; // yzx component
      dofs[27*tri_ct+16] = tri_ct+0.17; // yzy component
      dofs[27*tri_ct+17] = tri_ct+0.18; // yzz component
      dofs[27*tri_ct+18] = tri_ct+0.19; // zxx component
      dofs[27*tri_ct+19] = tri_ct+0.20; // zxy component
      dofs[27*tri_ct+20] = tri_ct+0.21; // zxz component
      dofs[27*tri_ct+21] = tri_ct+0.22; // zyx component
      dofs[27*tri_ct+22] = tri_ct+0.23; // zyy component
      dofs[27*tri_ct+23] = tri_ct+0.24; // zyz component
      dofs[27*tri_ct+24] = tri_ct+0.25; // zzx component
      dofs[27*tri_ct+25] = tri_ct+0.26; // zzy component
      dofs[27*tri_ct+26] = tri_ct+0.27; // zzz component

      tri_ct++;

      // Components for upper triangle in quad,

      dofs[27*tri_ct]    = tri_ct+0.00; // xxx component
      dofs[27*tri_ct+1]  = tri_ct+0.01; // xxy component
      dofs[27*tri_ct+2]  = tri_ct+0.02; // xxz component
      dofs[27*tri_ct+3]  = tri_ct+0.03; // xyx component
      dofs[27*tri_ct+4]  = tri_ct+0.04; // xyy component
      dofs[27*tri_ct+5]  = tri_ct+0.05; // xyz component
      dofs[27*tri_ct+6]  = tri_ct+0.06; // xzx component
      dofs[27*tri_ct+7]  = tri_ct+0.07; // xzy component
      dofs[27*tri_ct+8]  = tri_ct+0.08; // xzz component
      dofs[27*tri_ct+9]  = tri_ct+0.10; // yxx component
      dofs[27*tri_ct+10] = tri_ct+0.11; // yxy component
      dofs[27*tri_ct+11] = tri_ct+0.12; // yxz component
      dofs[27*tri_ct+12] = tri_ct+0.13; // yyx component
      dofs[27*tri_ct+13] = tri_ct+0.14; // yyy component
      dofs[27*tri_ct+14] = tri_ct+0.15; // yyz component
      dofs[27*tri_ct+15] = tri_ct+0.16; // yzx component
      dofs[27*tri_ct+16] = tri_ct+0.17; // yzy component
      dofs[27*tri_ct+17] = tri_ct+0.18; // yzz component
      dofs[27*tri_ct+18] = tri_ct+0.19; // zxx component
      dofs[27*tri_ct+19] = tri_ct+0.20; // zxy component
      dofs[27*tri_ct+20] = tri_ct+0.21; // zxz component
      dofs[27*tri_ct+21] = tri_ct+0.22; // zyx component
      dofs[27*tri_ct+22] = tri_ct+0.23; // zyy component
      dofs[27*tri_ct+23] = tri_ct+0.24; // zyz component
      dofs[27*tri_ct+24] = tri_ct+0.25; // zzx component
      dofs[27*tri_ct+25] = tri_ct+0.26; // zzy component
      dofs[27*tri_ct+26] = tri_ct+0.27; // zzz component

      tri_ct++;
    }
  }


  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}


sec_t3_e3::host_type&
make_t3_e3_sec_rep_space(fiber_bundles_namespace& xtest_namespace,
			 abstract_poset_member& xbase,
			 sec_e3::host_type& xvector_space,
			 sec_at0::host_type& xscalar_space,
			 int xedge_ct_x,
			 int xedge_ct_y)
{
  // Preconditions:

  require(xtest_namespace.state_is_read_write_accessible());
  require(xbase.state_is_read_accessible());
  require(xvector_space.state_is_read_accessible());
  require(xscalar_space.state_is_read_accessible());
  require(xedge_ct_x > 0);
  require(xedge_ct_y > 0);

  // Body:

  // Create the tensor section space

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("sec_rep_descriptors/element_element_constant",
						      xbase.path(false), "");

  poset_path lschema_path =
    xtest_namespace.new_tensor_section_space_schema<sec_t3_e3>("t3_e3_on_triangle_mesh_schema", largs);

  sec_t3_e3::host_type& result =
    xtest_namespace.new_tensor_section_space<sec_t3_e3>("t3_e3_on_triangle_mesh",
							"",
							lschema_path,
							xvector_space.path(false),
							"",
							xvector_space.schema().path(false),
							xscalar_space.path(false),
							"",
							xscalar_space.schema().path(false));

  result.get_read_write_access();

  // Create a field in the section space

  sec_t3_e3 lfield(&result);
  lfield.put_name("f0", true, false);

  Dof_tuple dofs = make_t3_e3_field_dofs(xedge_ct_x, xedge_ct_y);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit

  return result;
}

int
main(int argc, char* argv[])
{
  // Command line argument processing:

  size_t edge_ct_x = 1;
  if (argc > 1)
    edge_ct_x = atoi(argv[1]);

  size_t edge_ct_y = 1;
  if (argc > 2)
    edge_ct_y = atoi(argv[2]);

  // Preconditions:

  require(edge_ct_x > 0);
  require(edge_ct_y > 0);

  isFlat = (argc > 5);

  // Body:

  fiber_bundles_namespace test_namespace("fields3d.t");

  test_namespace.get_read_write_access();

  // Make triangle mesh

  base_space_poset& lmesh =
    zone_nodes_block::new_host(test_namespace, "triangle_mesh", 2, false);

  lmesh.get_read_write_access();

  // Make triangle block base space

  triangle_connectivity lconn(edge_ct_x, edge_ct_y);

  zone_nodes_block lbase_space(lmesh, lconn, true);
  lbase_space.put_name("triangle_block", true, false);

  sec_at0::host_type& lat0_srs =
    make_scalar_sec_rep_space(test_namespace, lbase_space,
			      edge_ct_x, edge_ct_y);

  sec_e3::host_type& le3_srs =
    make_coord_sec_rep_space(test_namespace, lbase_space,
			     lat0_srs, edge_ct_x, edge_ct_y);

  sec_t2_e3::host_type& lt2_e3_srs =
    make_t2_e3_sec_rep_space(test_namespace, lbase_space,
			     le3_srs, lat0_srs,
			     edge_ct_x, edge_ct_y);

  sec_st2_e3::host_type& lst2_e3_srs =
    make_st2_e3_sec_rep_space(test_namespace, lbase_space,
			      le3_srs, lat0_srs,
			      edge_ct_x, edge_ct_y);

  sec_at2_e3::host_type& lat2_e3_srs =
    make_at2_e3_sec_rep_space(test_namespace, lbase_space,
			      le3_srs, lat0_srs,
			      edge_ct_x, edge_ct_y);

  sec_t3_e3::host_type& lt3_e3_srs =
    make_t3_e3_sec_rep_space(test_namespace, lbase_space,
			     le3_srs, lat0_srs,
			     edge_ct_x, edge_ct_y);

  cout << test_namespace << endl;

  storage_agent sa("fields3d.t.hdf");

  sa.write_entire(test_namespace);

  // Clean-up

  lbase_space.detach_from_state();
  lmesh.release_access();

  return 0;
}
