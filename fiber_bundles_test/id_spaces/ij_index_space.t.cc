
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

/// @example ij_index_space.t.cc
/// Test driver for for the connectivity and adjacency id spaces for
/// a 2-dimensional structured block.

#include "fiber_bundles_namespace.h"
#include "ij_adjacency_index_space_interval.h"
#include "ij_adjacency_implicit_index_space_iterator.h"
#include "ij_connectivity_index_space_interval.h"
#include "ij_connectivity_implicit_index_space_iterator.h"
#include "offset_index_space_handle.h"
#include "test_index_spaces.impl.h"
#include "std_strstream.h"

using namespace std;
using namespace fiber_bundle;

int main( int argc, char* argv[])
{
  fiber_bundles_namespace::initialize_id_space_prototypes();

  // Parse input.

  size_t li_size = argc > 1 ? atoi(argv[1]) : 2;
  size_t lj_size = argc > 2 ? atoi(argv[2]) : 2;

  assertion(li_size > 0);
  assertion(lj_size > 0);

  // Create the top id space.

  size_type lzone_size = li_size*lj_size;
  size_type lvertex_size = (li_size + 1)*(lj_size + 1);
  size_type lsize = 1 + lzone_size + lvertex_size;

  test_index_space_family lid_spaces;
  lid_spaces.new_primary_space(lsize);

  // Create zone id space.

  offset_index_space_handle::new_space(lid_spaces, "zone_id_space",
				       1, lzone_size);

  // Create vertex id space.

  offset_index_space_handle::new_space(lid_spaces, "vertex_id_space",
				       1+lzone_size, lvertex_size);

  // Create connectivity interval.

#ifndef NO_CONNECTIVITY

  pod_index_type lconn_id =
    ij_connectivity_index_space_interval::new_space(lid_spaces, lzone_size,
						    1+lzone_size, lj_size).begin();

  // Give the id space a name.

  strstream lconn_name;
  lconn_name << "conn_" << lconn_id;

  lid_spaces.put_name(lconn_id, lconn_name.str());

  // Test iterator facet.

  test_iterator_facet<ij_connectivity_implicit_index_space_iterator>(lid_spaces, lconn_id);

  // Test state facet.

  test_state_facet(lid_spaces, lconn_id, 0, lid_spaces.hub_pod(lconn_id, 0));

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  ij_connectivity_implicit_index_space_iterator lconn_itr(lid_spaces, lconn_id);
  const ij_connectivity_index_space_interval& lconn_interval =
    reinterpret_cast<const ij_connectivity_index_space_interval&>(lconn_itr.host());

  cout << "vertex_hub_begin()   = " << lconn_interval.vertex_hub_begin() << endl;
  cout << "vertex_hub_begin(0)  = " << lconn_interval.vertex_hub_begin(0) << endl;
  cout << "j_size()             = " << lconn_interval.j_size() << endl;
  cout << "j_vertex_size()()    = " << lconn_interval.j_vertex_size() << endl;

#endif

  // Create adjacency interval.

#ifndef NO_ADJACENCY

  pod_index_type ladj_id =
    ij_adjacency_index_space_interval::new_space(lid_spaces, lvertex_size,
						 1, li_size, lj_size).begin();

  // Give the id space a name.

  strstream ladj_name;
  ladj_name << "adj_" << ladj_id;

  lid_spaces.put_name(ladj_id, ladj_name.str());

  // Test iterator facet.

  test_iterator_facet<ij_adjacency_implicit_index_space_iterator>(lid_spaces, ladj_id);

  // Test state facet.

  test_state_facet(lid_spaces, ladj_id, 0, lid_spaces.hub_pod(ladj_id, 0));

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  ij_adjacency_implicit_index_space_iterator ladj_itr(lid_spaces, ladj_id);
  const ij_adjacency_index_space_interval& ladj_interval =
    reinterpret_cast<const ij_adjacency_index_space_interval&>(ladj_itr.host());

  cout << "zone_hub_begin()   = " << ladj_interval.zone_hub_begin() << endl;
  cout << "zone_hub_begin(0)  = " << ladj_interval.zone_hub_begin(0) << endl;
  cout << "i_size()           = " << ladj_interval.i_size() << endl;
  cout << "j_size()           = " << ladj_interval.j_size() << endl;
  cout << "i_vertex_size()    = " << ladj_interval.i_vertex_size() << endl;
  cout << "j_vertex_size()    = " << ladj_interval.j_vertex_size() << endl;

#endif

  // Output the id space family.

  cout << lid_spaces << endl;

  return 0;
}

  
