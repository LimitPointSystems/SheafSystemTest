
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

/// @example i_index_space.t.cc
/// Test driver for for the connectivity and adjacency id spaces for
/// a 1-dimensional structured block.

#include "fiber_bundles_namespace.h"
#include "i_adjacency_index_space_interval.h"
#include "i_adjacency_implicit_index_space_iterator.h"
#include "i_connectivity_index_space_interval.h"
#include "i_connectivity_implicit_index_space_iterator.h"
#include "offset_index_space_handle.h"
#include "test_index_spaces.impl.h"
#include "std_sstream.h"

using namespace std;
using namespace fiber_bundle;

int main( int argc, char* argv[])
{
  fiber_bundles_namespace::initialize_id_space_prototypes();

  // Parse input.

  size_t li_size = argc > 1 ? atoi(argv[1]) : 4;

  assertion(li_size > 0);

  // Create the top id space.

  size_type lzone_size = li_size;
  size_type lvertex_size = (li_size + 1);
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

  pod_index_type lconn_id =
    i_connectivity_index_space_interval::new_space(lid_spaces, lzone_size,
						   1+lzone_size).begin();

  // Give the id space a name.

  stringstream lconn_str;
  lconn_str << "conn_" << lconn_id;

  string lconn_name;
  lconn_str >> lconn_name;

  lid_spaces.put_name(lconn_id, lconn_name);

  // Test iterator facet.

  test_iterator_facet<i_connectivity_implicit_index_space_iterator>(lid_spaces, lconn_id);

  // Test state facet.

  test_state_facet(lid_spaces, lconn_id, 0, lid_spaces.hub_pod(lconn_id, 0));

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  i_connectivity_implicit_index_space_iterator lconn_itr(lid_spaces, lconn_id);
  const i_connectivity_index_space_interval& lconn_interval =
    reinterpret_cast<const i_connectivity_index_space_interval&>(lconn_itr.host());

  cout << "vertex_hub_begin()   = " << lconn_interval.vertex_hub_begin() << endl;
  cout << "vertex_hub_begin(0)  = " << lconn_interval.vertex_hub_begin(0) << endl;

  // Create adjacency interval.

  pod_index_type ladj_id =
    i_adjacency_index_space_interval::new_space(lid_spaces, lvertex_size,
						1, li_size).begin();

  // Give the id space a name.

  stringstream ladj_str;
  ladj_str << "adj_" << ladj_id;

  string ladj_name;
  ladj_str >> ladj_name;

  lid_spaces.put_name(ladj_id, ladj_name);

  // Test iterator facet.

  test_iterator_facet<i_adjacency_implicit_index_space_iterator>(lid_spaces, ladj_id);

  // Test state facet.

  test_state_facet(lid_spaces, ladj_id, 0, lid_spaces.hub_pod(ladj_id, 0));

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  i_adjacency_implicit_index_space_iterator ladj_itr(lid_spaces, ladj_id);
  const i_adjacency_index_space_interval& ladj_interval =
    reinterpret_cast<const i_adjacency_index_space_interval&>(ladj_itr.host());

  cout << "zone_hub_begin()   = " << ladj_interval.zone_hub_begin() << endl;
  cout << "zone_hub_begin(0)  = " << ladj_interval.zone_hub_begin(0) << endl;
  cout << "i_size()           = " << ladj_interval.i_size() << endl;

  // Output the id space family.

  cout << lid_spaces << endl;

  return 0;
}

  
