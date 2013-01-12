

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/refinable_poset.t.cc
/// Test driver for test.

#include "assert_contract.h"

#include "abstract_poset_member.h"
#include "at0.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset_member.h"
#include "poset_member_iterator.h"
#include "poset_path.h"
#include "postorder_iterator.h"
#include "postorder_member_iterator.h"
#include "refinable_poset.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_st2.h"
#include "sec_rep_descriptor.h"
#include "sec_rep_space.h"
#include "section_dof_iterator.h"
#include "std_cctype.h"
#include "std_iostream.h"
#include "std_cstdlib.h"
#include "storage_agent.h"
#include "subposet.h"
#include "total_poset_member.h"
#include "vd.h"

using namespace fiber_bundle;

//
// OBSOLETE: This test driver is obsolete and is only in the repository
// as an example of versioning.  Once another test driver is
// written that uses versioning, this file can be removed.
//

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


Connectivity
make_mesh_connectivity(int edge_ct)
{

  // Preconditions:

  require(edge_ct > 0);

  // Body:

  Connectivity result;

  // allocate node_ids as single index array,
  // but treat as node_ids[edge_ct][2];

  int* node_ids = new int[edge_ct*2];
  int node_ct = 0;

  for(int i=0; i<edge_ct; i++)
  {

    // Connectivity for lower triangle in quad,
    // follow right-hand rule (ccw) starting
    // in llh corner of quad.

    node_ids[node_ct++] = i;
    node_ids[node_ct++] = i+1;
  }

  result.node_ids = node_ids;
  result.node_ids_ub = node_ct;

  // Postconditions:

  // Exit

  return result;
}

abstract_poset_member*
make_base_space(namespace_poset* test_namespace,
                int edge_ct)
{
  // Body:

  // Get the schema for the mesh
  // Note: must allocate poset handle on heap rather than stack,
  // due to bug in abstract_poset_member

  poset* lc_schema = new poset(test_namespace, "local_coordinates_schema");
  lc_schema->get_read_access();
  schema_poset_member lc_schema_mbr(lc_schema, "local_coordinates_schema");

  // Create mesh poset

  poset* mesh = new refinable_poset(test_namespace, &(lc_schema_mbr), "amr_line");

  // Get the edge template
  // Note: must allocate poset handle on heap rather than stack,
  // due to bug in abstract_poset_member

  poset* lcell_defns = new poset(test_namespace, "cell definitions");
  lcell_defns->get_read_access();

  total_poset_member ledge(lcell_defns, "edge");

  mesh->get_read_write_access();
  mesh->begin_jim_edit_mode();

  // Create the  connectivity

  Connectivity conn = make_mesh_connectivity(edge_ct);

  hash_map<int, int> glue_map;

  // Create a block of edges

  total_poset_member edge_mesh(mesh, &ledge, conn.node_ids, conn.node_ids_ub, &glue_map);
  edge_mesh.put_name("amr_line", true, false);

  mesh->end_jim_edit_mode();

  // detach members so destructor won't complain

  lc_schema_mbr.detach_from_state();
  ledge.detach_from_state();
  edge_mesh.detach_from_state();


  abstract_poset_member* result = &(mesh->top());

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

void
update_section_space_schema_base_space_handles(refinable_poset* xbase)
{
  /// @hack update the version of the
  /// base space handles in the section space schema
  /// that use this base space.

  // All section space schema that use this base space
  // are in the upper cover of the namespace member corresponding
  // to the base poset.

  // Get the namespace member corresponding to the base space.

  namespace_poset_member lbase_nspm(xbase->name_space(), xbase->index());

  // Iterate over its upper cover, updating section space schema base space handles.

  poset_member_iterator* up_itr = lbase_nspm.cover_iterator(false);

  int lversion = xbase->version();
  namespace_poset_member lnspm;
  while(!up_itr->is_done())
  {
    lnspm.attach_to_state(up_itr);
    section_space_schema_poset* lsssp = dynamic_cast<section_space_schema_poset*>(lnspm.poset_pointer());
    if ( lsssp != 0)
    {
      // This is a section space schema;
      // update its base space version

      lsssp->base_space().put_version(lversion);
    }
    up_itr->next();
  }
  lnspm.detach_from_state();
  delete up_itr;
  lbase_nspm.detach_from_state();

}


///
void
refine_base_space(refinable_poset* xbase)
{
  // Preconditions:

  // Host must be a refinable poset.
  require(xbase != 0);

  // Body:

  // Begin a new version

  xbase->begin_refine_mode();

  // Get handles to the existing edge and vertices

  total_poset_member e0(xbase, 5);
  e0.put_name("e0", true, false);

  total_poset_member v0(xbase, 3);
  v0.put_name("v0", true, false);

  total_poset_member v1(xbase, 4);
  v1.put_name("v1", true, false);

  subposet elements(xbase, "__elements");
  mutable_index_map* elements_id_map = elements.id_map();

  subposet vertices(xbase, "__vertices");
  mutable_index_map* vertices_id_map = vertices.id_map();


  // Make another vertex and two refined edges

  total_poset_member v2(xbase, &(v0.dof_map()));
  v2.put_name("v2", true, false);
  vertices.insert_member(&v2);

  // Vertex client id map built using put_ids, which is
  // incompatible with put_poset_id, so have to continue
  // using put_ids.

  vertices_id_map->push_back(v2.index(), true);


  total_poset_member e1(xbase, &(e0.dof_map()));
  e1.put_name("e1", true, false);
  elements.insert_member(&e1);
  elements_id_map->push_back(e1.index(), true);


  total_poset_member e2(xbase, &(e0.dof_map()));
  e2.put_name("e2", true, false);
  elements.insert_member(&e2);
  elements_id_map->push_back(e2.index(), true);

  // Delete old links

  e0.delete_cover_link(&v0);
  e0.delete_cover_link(&v1);

  // Insert new links.

  e0.create_cover_link(&e1);
  e0.create_cover_link(&e2);

  e1.create_cover_link(&v0);
  e1.create_cover_link(&v2);

  e2.create_cover_link(&v2);
  e2.create_cover_link(&v1);

  // The refined edge is no longer a jim

  xbase->jims().remove_member(&e0);
  xbase->coarsest_common_refinement_jims().remove_member(&e0);

  xbase->end_refine_mode();

  // Clean up

  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();

  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();

  elements.detach_from_state();
  vertices.detach_from_state();

  /// @hack update the version of the
  /// base space handles in the section space schema
  /// that use this base space.

  update_section_space_schema_base_space_handles(xbase);

  // Postconditions:

  // Exit

  return;
}

///
void
refine_base_space_again(refinable_poset* xbase)
{
  // Preconditions:

  // Host must be a refinable poset.
  require(xbase != 0);

  // Body:

  // Begin a new version

  xbase->begin_refine_mode();

  // Get handles to the existing edge and vertices

  total_poset_member e1(xbase, "e1");
  total_poset_member v0(xbase, "v0");
  total_poset_member v2(xbase, "v2");

  subposet elements(xbase, "__elements");
  mutable_index_map* elements_id_map = elements.id_map();

  subposet vertices(xbase, "__vertices");
  mutable_index_map* vertices_id_map = vertices.id_map();


  // Make another vertex and two refined edges

  total_poset_member v3(xbase, &(v0.dof_map()));
  v3.put_name("v3", true, false);
  vertices.insert_member(&v3);

  // Vertex client id map built using put_ids, which is
  // incompatible with put_poset_id, so have to continue
  // using put_ids.

  vertices_id_map->push_back(v3.index(), true);

  total_poset_member e3(xbase, &(e1.dof_map()));
  e3.put_name("e3", true, false);
  elements.insert_member(&e3);
  elements_id_map->push_back(e3.index(), true);

  total_poset_member e4(xbase, &(e1.dof_map()));
  e4.put_name("e4", true, false);
  elements.insert_member(&e4);
  elements_id_map->push_back(e4.index(), true);

  // Delete old links

  e1.delete_cover_link(&v0);
  e1.delete_cover_link(&v2);

  // Insert new links.

  e1.create_cover_link(&e3);
  e1.create_cover_link(&e4);

  e3.create_cover_link(&v0);
  e3.create_cover_link(&v3);
  elements.insert_member(&e3);

  e4.create_cover_link(&v3);
  e4.create_cover_link(&v2);
  elements.insert_member(&e4);

  // The refined edge is no longer a jim

  xbase->jims().remove_member(&e1);
  xbase->coarsest_common_refinement_jims().remove_member(&e1);

  xbase->end_refine_mode();

  // Clean up

  e1.detach_from_state();
  e3.detach_from_state();
  e4.detach_from_state();

  v0.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();

  elements.detach_from_state();
  vertices.detach_from_state();

  /// @hack update the version of the
  /// base space handles in the section space schema
  /// that use this base space.

  update_section_space_schema_base_space_handles(xbase);

  // Postconditions:

  // Exit

  return;
}


Dof_tuple
make_coord_field_dofs(int edge_ct)
{
  // Creates some arbitrary coordinates for a polyline
  // replace with data read from file if you have some
  // edge_ct = number of edges
  //
  // Number of nodes = edge_ct+1

  // Preconditions:

  require(edge_ct > 0);

  // Body:

  int node_ct = edge_ct+1;

  double xpos = 0.1;
  double ypos = 0.2;
  double delz = 1.0/edge_ct;


  // allocate dofs as single index array,
  // but treat as dofs[node_ct][2];

  int dofs_ub = node_ct*3;
  double* dofs = new double[dofs_ub];

  for(int i=0; i<node_ct; i++)
  {
    double z = -(i*delz);
    dofs[3*i]   = xpos;
    dofs[3*i+1] = ypos;
    dofs[3*i+2] = z;
  }

  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}


sec_rep_space*
make_coord_sec_rep_space(namespace_poset* test_namespace,
                         abstract_poset_member* xbase,
                         int edge_ct)
{
  // Preconditions:

  require(test_namespace != 0);
  require(xbase != 0);
  require(edge_ct > 0);

  // Body:

  // Create the coord section space

  fiber_bundles_namespace* lns = dynamic_cast<fiber_bundles_namespace*>(test_namespace);
  sec_rep_space* result =
    &lns->new_section_space<sec_e3>("e3_on_polyline",
				    xbase->path(),
				    "sec_rep_descriptors/vertex_element_dlinear",
				    true);

  result->get_read_write_access();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}


void
make_coord_field(sec_rep_space* xsrs, const string& xname, int xversion = CURRENT_HOST_VERSION)
{
  // Preconditions:

  require(xsrs != 0);
  require(xsrs->state_is_read_write_accessible());

  // Body:

  // Create a field in the section space

  xsrs->begin_jim_edit_mode();

  sec_rep_space_member* lfield;
  //   if (xversion != -2)
  //   {
  //     lfield = new sec_rep_space_member(xsrs, &(xsrs->base()), xversion);
  //   }
  //   else
  //   {
  //     lfield = new sec_rep_space_member(xsrs);
  //   }

  lfield = new sec_rep_space_member(xsrs, xsrs->base(), xversion);
  lfield->put_name(xname);

  // cout << "field schema version: " << lfield->schema().version() << endl;


  section_dof_iterator* itr = lfield->schema().row_dof_iterator();
  // cout << "itr version: " << itr->anchor().version() << endl;

  double lbuf;
  int lct = 0;
  while(!itr->is_done())
  {
    // cout << "ct:" << lct << " itr index: " << itr->index() << endl;

    int lrem = lct % 3;

    switch(lrem)
    {
    case 0: // xcoord
      lbuf = lrem;
      break;
    case 1: // ycoord
      lbuf = lrem;
      break;
    case 2: // zcoord
      lbuf = lct/3;
      break;
    default:
      break;
    }

    lct++;
    itr->next();
  }

  xsrs->end_jim_edit_mode();

  lfield->detach_from_state();

  // Postconditions:

  ensure(xsrs->contains_member(xname));

  // Exit

  return;
}



Dof_tuple
make_scalar_field_dofs(int edge_ct)
{
  // Creates a scalar on a polyline
  // edge_ct = number of edges in x-dir
  //
  // Number of nodes = edge_ct+1

  // Preconditions:

  require(edge_ct > 0);


  // Body:

  int node_ct = edge_ct+1;

  double delx = 1.0;
  //double dely = 1.0;


  int dofs_ub = node_ct;
  double* dofs = new double[dofs_ub];

  for(int i=0; i<node_ct; i++)
  {
    double x = i*delx;
    dofs[i] = x*x; // totally arbitrary, replace with your own data
  }

  Dof_tuple result = {dofs, dofs_ub*sizeof(double)};

  // Postconditions:

  // Exit

  return result;
}

sec_rep_space*
make_scalar_sec_rep_space(namespace_poset* test_namespace,
                          abstract_poset_member* xbase,
                          int edge_ct)
{
  // Preconditions:

  require(test_namespace != 0);
  require(xbase != 0);
  require(edge_ct > 0);

  // Body:

  // Create the scalar section space

  fiber_bundles_namespace* lns = dynamic_cast<fiber_bundles_namespace*>(test_namespace);
  sec_rep_space* result = 
    &lns->new_section_space<sec_at0>("at0_on_polyline",
				     xbase->path(),
				     "sec_rep_descriptors/vertex_element_dlinear",
				     true);

  result->get_read_write_access();

  // Create a field in the section space

  result->begin_jim_edit_mode();

  sec_at0 lfield(result);
  lfield.put_name("scalar field", true, false);

  Dof_tuple dofs = make_scalar_field_dofs(edge_ct);
  lfield.put_dof_tuple(dofs.values, dofs.values_ub);

  result->end_jim_edit_mode();

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}


int
main(int argc, char* argv[])
{

  int edge_ct = 1;

  namespace_poset* test_namespace = new fiber_bundles_namespace();

  cout << *test_namespace << endl;

  test_namespace->get_read_write_access();

  abstract_poset_member* lbase_mbr = make_base_space(test_namespace, edge_ct);

  refinable_poset* lbase = dynamic_cast<refinable_poset*>(lbase_mbr->host());

  cout << *lbase << endl;

  sec_rep_space* le3_srs = make_coord_sec_rep_space(test_namespace, lbase_mbr, edge_ct);

  make_coord_field(le3_srs, "level_0_coordinates-A");


  refine_base_space(lbase);

  make_coord_field(le3_srs, "level_1_coordinates-A");

  cout << *lbase << endl;

  cout << endl << "##### VERSION 1 #####" << endl;

  // Iterator defaults to version of anchor,
  // version of top() is CURRENT_HOST_VERSION

  postorder_member_iterator itr1(lbase->top());
  while(!itr1.is_done())
  {
    cout << itr1.item() << endl;
    itr1.next();
  }


  lbase->put_version(0);

  cout << endl << "##### VERSION 0 #####" << endl;

  postorder_member_iterator itr0(lbase->top());
  while(!itr0.is_done())
  {
    cout << itr0.item() << endl;
    itr0.next();
  }

  lbase->put_version(COARSEST_COMMON_REFINEMENT_VERSION);

  cout << endl << "##### COARSEST_COMMON_REFINEMENT #####" << endl;

  postorder_member_iterator itr_ccr(lbase->top(), &(lbase->whole()));
  while(!itr_ccr.is_done())
  {
    cout << itr_ccr.item() << endl;
    itr_ccr.next();
  }


  refine_base_space_again(lbase);

  make_coord_field(le3_srs, "level_2_coordinates-A");

  cout << endl << "##### VERSION 2 #####" << endl;

  postorder_member_iterator itr2(lbase->top());
  while(!itr2.is_done())
  {
    cout << itr2.item() << endl;
    itr2.next();
  }


  lbase->put_version(1);

  cout << endl << "##### VERSION 1 #####" << endl;

  itr1.reset();
  while(!itr1.is_done())
  {
    cout << itr1.item() << endl;
    itr1.next();
  }


  lbase->put_version(0);

  cout << endl << "##### VERSION 0 #####" << endl;

  itr0.reset();
  while(!itr0.is_done())
  {
    cout << itr0.item() << endl;
    itr0.next();
  }

  lbase->put_version(COARSEST_COMMON_REFINEMENT_VERSION);

  cout << endl << "##### COARSEST_COMMON_REFINEMENT #####" << endl;

  itr_ccr.reset();
  while(!itr_ccr.is_done())
  {
    cout << itr_ccr.item() << endl;
    itr_ccr.next();
  }

  cout << *lbase << endl;



  make_coord_field(le3_srs, "level_0_coordinates-B", 0);

  make_coord_field(le3_srs, "level_1_coordinates-B", 1);

  make_coord_field(le3_srs, "level_2_coordinates-B", 2);


  cout << endl << "##### E3 ON AMR_MESH #####" << endl;
  cout << *le3_srs << endl;

  //   sec_rep_space* lat0_srs = make_scalar_sec_rep_space(test_namespace, lbase_space, edge_ct);

  cout << *test_namespace << endl;

  storage_agent sa("refinable_poset.t.hdf");
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(*test_namespace);

  return 0;
}
