
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

/// @example base_spaces/time_query_mesh.t.cc

#include "adjacency_extractor.h"
#include "connectivity_extractor.h"
#include "fiber_bundles_namespace.h"
#include "unstructured_block.h"
#include "index_map.h"
#include "namespace_poset.h"
#include "neighborhood_extractor.h"
#include "postorder_iterator.h"
#include "std_iostream.h"
#include "std_ctime.h"
#include "stencil_extractor.h"

using namespace std;
using namespace fiber_bundle;

/// @issue const_casts are used to convert literal strings to char *'s
char* sp_names[3] = {const_cast<char*>("__vertices"),
                     const_cast<char*>("__1_cells"),
                     const_cast<char*>("__elements")};

clock_t conn_time[16][3];
clock_t adj_time[16][3];
clock_t nbr_time[16][3];
clock_t sten_time[16][3];
int time_ct;
int query_ct;
int tri_ct[16];


void
init_id_array(poset* mesh, const string& sp_name, int* domain_mbrs)
{
  subposet sp(mesh, sp_name);

  index_map& id_map = sp.id_map();
  int i=0;
  postorder_iterator itr(mesh->top(), &sp);
  while(!itr.is_done())
  {
    domain_mbrs[i++] = id_map.domain_id(itr.index());

    itr.next();
  }

  sp.detach_from_state();
}


void
print_query(const string& query_name,
            const string& ll_name,
            const string& ul_name,
            int* ids,
            int* ids_cts,
            int* domain_mbrs,
            int domain_mbrs_ct)
{
  int* ids_p = ids;

  cout << endl << endl;
  cout << query_name << " for " << ll_name << " and " << ul_name << endl;

  cout << endl;
  for(int i=0; i<domain_mbrs_ct; i++)
  {
    cout << "mbr= " << setw(5) << domain_mbrs[i] << " ids=";

    for(int j=0; j<ids_cts[i]; j++)
    {
      cout << " " << setw(5) << *ids_p;
      ids_p++;
    }
    cout << endl;
  }
  cout << endl << endl;
}


void
query_connectivity(poset* mesh,
                   int upper_level,
                   int lower_level,
                   bool use_poset_api,
                   bool print_it)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ll_name(sp_names[lower_level]);
  string ul_name(sp_names[upper_level]);

  // Make a  connectivity extractor

  connectivity_extractor ae(mesh, ll_name, ul_name);

  // Get the number of entries in the connectivity array

  ae.count(mesh_top);
  int domain_mbrs_ct = ae.domain_mbrs_ct();
  int conn_cts_ct = ae.connectivity_cts_ct();
  int conn_ct = ae.connectivity_ct();

  // Allocate the connectivity counts and connectivity arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* conn_cts = new int[conn_cts_ct];
  int* conn = new int[conn_ct];

  // Extract the connectivity


  if (use_poset_api)
  {
    // Use poset member api

    ae.extract(mesh_top, domain_mbrs, domain_mbrs_ct, conn_cts, conn_cts_ct, conn, conn_ct);

  }
  else
  {
    // Use array api

    // Client will typically have domain of query
    // represented as array of ids, but native sheaf
    // code like this doesn't, so we have to make
    // an array of client ids.

    init_id_array(mesh, ul_name, domain_mbrs);

    clock_t ltime = clock();

    ae.extract(domain_mbrs, domain_mbrs_ct, conn_cts, conn_cts_ct, conn, conn_ct);

    conn_time[time_ct][query_ct] = clock() - ltime;
    query_ct = ++query_ct % 3;
  }


  // Print it

  if (print_it)
    print_query("connectivity" , ll_name, ul_name, conn, conn_cts, domain_mbrs, domain_mbrs_ct);

}



void
query_adjacency(poset* mesh,
                int upper_level,
                int lower_level,
                bool use_poset_api,
                bool print_it)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ul_name(sp_names[upper_level]);
  string ll_name(sp_names[lower_level]);

  // Make a  adjacency extractor

  adjacency_extractor ae(mesh, ll_name, ul_name);

  // Get the number of entries in the adjacency array for the bottom

  ae.count(mesh_top);
  int domain_mbrs_ct = ae.domain_mbrs_ct();
  int adj_cts_ct = ae.adjacency_cts_ct();
  int adj_ct = ae.adjacency_ct();

  // Allocate the adjacency counts and adjacency arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* adj_cts = new int[adj_cts_ct];
  int* adj = new int[adj_ct];

  // Extract the adjacency

  if (use_poset_api)
  {
    // Use poset member api

    ae.extract(mesh_top, domain_mbrs, domain_mbrs_ct, adj_cts, adj_cts_ct, adj, adj_ct);
  }
  else
  {
    // Use array api

    // Client will typically have domain of query
    // represented as array of ids, but native sheaf
    // code like this doesn't, so we have to make
    // an array of client ids.

    init_id_array(mesh, ll_name, domain_mbrs);

    clock_t ltime = clock();

    ae.extract(domain_mbrs, domain_mbrs_ct, adj_cts, adj_cts_ct, adj, adj_ct);

    adj_time[time_ct][query_ct] = clock() - ltime;
    query_ct = ++query_ct % 3;
  }


  // Print it

  if (print_it)
    print_query("adjacency" , ll_name, ul_name, adj, adj_cts, domain_mbrs, domain_mbrs_ct);

}


void
query_neighborhood(poset* mesh,
                   int upper_level,
                   int lower_level,
                   bool includes_center,
                   bool use_poset_api,
                   bool print_it)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ll_name(sp_names[lower_level]);
  string ul_name(sp_names[upper_level]);

  // Make a  neighborhood extractor

  neighborhood_extractor ae(mesh, ll_name, ul_name, includes_center);

  // Get the number of entries in the neighborhood array

  ae.count(mesh_top);
  int domain_mbrs_ct = ae.domain_mbrs_ct();
  int nbr_cts_ct = ae.neighborhood_cts_ct();
  int nbr_ct = ae.neighborhood_ct();

  // Allocate the neighborhood counts and neighborhood arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* nbr_cts = new int[nbr_cts_ct];
  int* nbr = new int[nbr_ct];

  // Extract the neighborhood

  if (use_poset_api)
  {
    // Use poset member api

    ae.extract(mesh_top, domain_mbrs, domain_mbrs_ct, nbr_cts, nbr_cts_ct, nbr, nbr_ct);
  }
  else
  {
    // Use array api

    // Client will typically have domain of query
    // represented as array of ids, but native sheaf
    // code like this doesn't, so we have to make
    // an array of client ids.

    init_id_array(mesh, ul_name, domain_mbrs);

    clock_t ltime = clock();

    ae.extract(domain_mbrs, domain_mbrs_ct, nbr_cts, nbr_cts_ct, nbr, nbr_ct);

    nbr_time[time_ct][query_ct] = clock() - ltime;
    query_ct = ++query_ct % 3;
  }


  // Print it

  if (print_it)
    print_query("neighborhood" , ll_name, ul_name, nbr, nbr_cts, domain_mbrs, domain_mbrs_ct);

}


void
query_stencil(poset* mesh,
              int upper_level,
              int lower_level,
              bool includes_center,
              bool use_poset_api,
              bool print_it)
{
  // Get a handle to the top of the mesh poset

  abstract_poset_member* mesh_top = &(mesh->top());

  // Get the subposet names

  string ll_name(sp_names[lower_level]);
  string ul_name(sp_names[upper_level]);

  // Make a  stencil extractor

  stencil_extractor ae(mesh, ll_name, ul_name, includes_center);

  // Get the number of entries in the stencil array

  ae.count(mesh_top);
  int domain_mbrs_ct = ae.domain_mbrs_ct();
  int sten_cts_ct = ae.stencil_cts_ct();
  int sten_ct = ae.stencil_ct();

  // Allocate the stencil counts and stencil arrays

  int* domain_mbrs = new int[domain_mbrs_ct];
  int* sten_cts = new int[sten_cts_ct];
  int* sten = new int[sten_ct];

  // Extract the stencil

  if (use_poset_api)
  {
    // Use poset member api

    ae.extract(mesh_top, domain_mbrs, domain_mbrs_ct, sten_cts, sten_cts_ct, sten, sten_ct);
  }
  else
  {
    // Use array api

    // Client will typically have domain of query
    // represented as array of ids, but native sheaf
    // code like this doesn't, so we have to make
    // an array of client ids.

    init_id_array(mesh, ll_name, domain_mbrs);

    clock_t ltime = clock();

    ae.extract(domain_mbrs, domain_mbrs_ct, sten_cts, sten_cts_ct, sten, sten_ct);

    sten_time[time_ct][query_ct] = clock() - ltime;
    query_ct = ++query_ct % 3;
  }


  // Print it

  if (print_it)
    print_query("stencil" , ll_name, ul_name, sten, sten_cts, domain_mbrs, domain_mbrs_ct);

}


void
query_mesh(namespace_poset* ns,
           const string& mesh_name,
           bool use_poset_api, bool print_it)
{
  // Get a handle to the top of the mesh poset

  poset* mesh = ns->member_poset<poset>(mesh_name, false);
  mesh->get_read_access();

  // Query element-nodal connectivity

  query_connectivity(mesh, 2, 0, false, print_it);
  if (use_poset_api)
    query_connectivity(mesh, 2, 0, true, print_it);

  // Query element-edge connectivity

  query_connectivity(mesh, 2, 1, false, print_it);
  if (use_poset_api)
    query_connectivity(mesh, 2, 1, true, print_it);

  // Query edge-nodal connectivity

  query_connectivity(mesh, 1, 0, false, print_it);
  if (use_poset_api)
    query_connectivity(mesh, 1, 0, true, print_it);

  // Query element-nodal adjacency,

  query_adjacency(mesh, 2, 0, false, print_it);
  if (use_poset_api)
    query_adjacency(mesh, 2, 0, true, print_it);

  // Query element-edge adjacency,

  query_adjacency(mesh, 2, 1, false, print_it);
  if (use_poset_api)
    query_adjacency(mesh, 2, 1, true, print_it);

  // Query edge-nodal adjacency,

  query_adjacency(mesh, 1, 0, false, print_it);
  if (use_poset_api)
    query_adjacency(mesh, 1, 0, true, print_it);

  // Query element-nodal neighborhood

  query_neighborhood(mesh, 2, 0, false, false, print_it);
  if (use_poset_api)
    query_neighborhood(mesh, 2, 0, true, true, print_it);

  // Query element-edge neighborhood

  query_neighborhood(mesh, 2, 1, false, false, print_it);
  if (use_poset_api)
    query_neighborhood(mesh, 2, 1, true, true, print_it);

  // Query edge-nodal neighborhood

  query_neighborhood(mesh, 1, 0, false, false, print_it);
  if (use_poset_api)
    query_neighborhood(mesh, 1, 0, true, true, print_it);

  // Query element-nodal stencil

  query_stencil(mesh, 2, 0, false, false, print_it);
  if (use_poset_api)
    query_stencil(mesh, 2, 0, true, true, print_it);

  // Query element-edge stencil

  query_stencil(mesh, 2, 1, false, false, print_it);
  if (use_poset_api)
    query_stencil(mesh, 2, 1, true, true, print_it);

  // Query edge-nodal stencil

  query_stencil(mesh, 1, 0, false, false, print_it);
  if (use_poset_api)
    query_stencil(mesh, 1, 0, true, true, print_it);

}


int
main(int argc, char** argv)
{
  string mesh_name("triangle_mesh");


  int time_ub = argc > 1 ? atoi(argv[1]) :  1;

  bool print_it = argc > 2;
  bool use_poset_api = argc > 3;

  size_type edge_ct_x = 1;
  size_type edge_ct_y = 1;

  query_ct = 0;

  for(time_ct=0; time_ct<time_ub; time_ct++)
  {

    edge_ct_x *= 2;
    edge_ct_y *= 2;

    tri_ct[time_ct] = 2*edge_ct_x*edge_ct_y;

    fiber_bundles_namespace* ns = new fiber_bundles_namespace("time_query_mesh.t");

    ns->get_read_write_access();

    // Make triangle mesh

    base_space_poset* lmesh =
      &ns->new_base_space<unstructured_block>(mesh_name, "", "", 2, true);
    lmesh->get_read_write_access();

    // Make triangle block base space

    poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                           "triangle_complex");

    unstructured_block lbase_space(lmesh, lproto_path, edge_ct_x, edge_ct_y, true);
    lbase_space.put_name("triangle_block", true, false);

    // Query the mesh.

    query_mesh(ns, mesh_name, use_poset_api, print_it);

    // Clean-up

    lbase_space.detach_from_state();
    lmesh->release_access();
    delete ns;
  }


  cout << "triangle counts:" << endl;
  cout << tri_ct[0];
  for(int i=1; i<time_ct; i++)
    cout << ", " << tri_ct[i];
  cout << endl << endl;

  cout << "connectivity times:" << endl;
  for(int j=0; j<3; j++)
  {
    cout << conn_time[0][j];
    for(int i=1; i<time_ct; i++)
      cout << ", " << conn_time[i][j];
    cout << endl;
  }
  cout << endl;

  cout << "adjacency times:" << endl;
  for(int j=0; j<3; j++)
  {
    cout << adj_time[0][j];
    for(int i=1; i<time_ct; i++)
      cout << ", " << adj_time[i][j];
    cout << endl;
  }
  cout << endl;

  cout << "neighborhood times:" << endl;
  for(int j=0; j<3; j++)
  {
    cout << nbr_time[0][j];
    for(int i=1; i<time_ct; i++)
      cout << ", " << nbr_time[i][j];
    cout << endl;
  }
  cout << endl;

  cout << "stencil times:" << endl;
  for(int j=0; j<3; j++)
  {
    cout << sten_time[0][j];
    for(int i=1; i<time_ct; i++)
      cout << ", " << sten_time[i][j];
    cout << endl;
  }
  cout << endl;

  return 0;
}
