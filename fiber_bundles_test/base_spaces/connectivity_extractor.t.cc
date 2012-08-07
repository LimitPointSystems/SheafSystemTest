// $RCSfile: connectivity_extractor.t.cc,v $ $Revision: 1.20 $ $Date: 2012/03/01 00:40:30 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example base_spaces/connectivity_extractor.t.cc

#include "connectivity_extractor.h"
#include "fiber_bundles_namespace.h"
#include "unstructured_block.h"
#include "mutable_index_map.h"
#include "namespace_poset.h"
#include "postorder_member_iterator.h"
#include "std_iostream.h"
#include "stencil_extractor.h"

using namespace fiber_bundle;

char* sp_names[3] = {const_cast<char*>("__vertices"),
                     const_cast<char*>("__1_cells"),
                     const_cast<char*>("__elements")};

void
init_id_array(poset* mesh, const string& sp_name, int* domain_mbrs)
{
  subposet sp(mesh, sp_name);

  index_map& id_map = sp.id_map();
  int i=0;
  postorder_member_iterator itr(mesh->top(), &sp);
  while(!itr.is_done())
  {
    domain_mbrs[i++] = id_map.domain_id(itr.item().index());
    itr.next();
  }

  sp.detach_from_state();
}

void
query_connectivity(poset* mesh,
                   int upper_level,
                   int lower_level)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ll_name(sp_names[lower_level]);
  string ul_name(sp_names[upper_level]);

  // Make a  connectivity extractor

  connectivity_extractor ce(mesh, ll_name, ul_name);

  // Get the number of entries in the connectivity array

  ce.count(mesh_top);
  int domain_mbrs_ct = ce.domain_mbrs_ct();
  int conn_cts_ct = ce.connectivity_cts_ct();
  int conn_ct = ce.connectivity_ct();

  // Allocate the connectivity counts and connectivity arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* conn_cts = new int[conn_cts_ct];
  int* conn = new int[conn_ct];

  // Extract the connectivity

  init_id_array(mesh, ul_name, domain_mbrs);

  ce.extract(domain_mbrs, domain_mbrs_ct, conn_cts, conn_cts_ct, conn, conn_ct);

  cout << endl << "===================================================================" << endl;
  cout << "Upper Level    = " << ul_name << endl << endl;
  cout << "Lower Level    = " << ll_name << endl << endl;

  cout << "Domain Members\tConnectivity (poset ids)" << endl;
  cout << "==============\t===========================" << endl;

  int cid = 0;
  for(int i=0; i<domain_mbrs_ct; i++)
  {
    cout << ce.upper_level().id_map().range_id(domain_mbrs[i]) << "\t";

    for(int j=0; j<conn_cts[i]; j++)
    {
      cout << "\t" << ce.lower_level().id_map().range_id(conn[cid++]);
    }

    cout << endl;
  }
  cout << endl << endl;

  cout << "Domain Members\tConnectivity (client ids)" << endl;
  cout << "==============\t===========================" << endl;

  cid = 0;
  for(int i=0; i<domain_mbrs_ct; i++)
  {
    cout << domain_mbrs[i] << "\t";

    for(int j=0; j<conn_cts[i]; j++)
    {
      cout << "\t" << conn[cid++];
    }
    cout << endl;
  }
  cout << endl;
  cout << "===================================================================" << endl;
}

int
main(int argc, char** argv)
{
  size_type edge_ct_x = 1;
  size_type edge_ct_y = 1;

  fiber_bundles_namespace* ns = new fiber_bundles_namespace("connectivity_extractor.t");

  ns->get_read_write_access();

  // Make triangle mesh

  base_space_poset* lmesh = &ns->new_base_space<unstructured_block>("triangle_mesh", "", "", 2, true);
  lmesh->get_read_write_access();

  // Make triangle block base space

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "triangle_complex");

  unstructured_block lbase_space(lmesh, lproto_path, edge_ct_x, edge_ct_y, true);
  lbase_space.put_name("triangle_block", true, false);

  // Output mesh.

  lmesh->to_stream();

  query_connectivity(lmesh, 2,0);
  query_connectivity(lmesh, 2,1);
  query_connectivity(lmesh, 1,0);

  // Clean-up

  lbase_space.detach_from_state();
  lmesh->release_access();
  delete ns;

  return 0;
}
