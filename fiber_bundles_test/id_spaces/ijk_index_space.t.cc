
// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example ijk_index_space.t.cc
/// Test driver for for the connectivity and adjacency id spaces for
/// a 3-dimensional structured block.

#include "arg_list.h"
#include "ijk_adjacency_index_space_interval.h"
#include "ijk_adjacency_implicit_index_space_iterator.h"
#include "ijk_connectivity_index_space_interval.h"
#include "ijk_connectivity_implicit_index_space_iterator.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "offset_index_space_state.h"
#include "test_index_spaces.impl.h"
#include "std_strstream.h"

//#define NO_CONNECTIVITY
//#define NO_ADJACENCY

using namespace fiber_bundle;

int main( int argc, char* argv[])
{
  // Parse input.

  size_t li_size = argc > 1 ? atoi(argv[1]) : 2;
  size_t lj_size = argc > 2 ? atoi(argv[2]) : 2;
  size_t lk_size = argc > 3 ? atoi(argv[3]) : 2;

  assertion(li_size > 0);
  assertion(lj_size > 0);
  assertion(lk_size > 0);

  // Create the top id space.

  size_type lzone_size = li_size*lj_size*lk_size;
  size_type lvertex_size = (li_size + 1)*(lj_size + 1)*(lk_size + 1);
  size_type lsize = 1 + lzone_size + lvertex_size;

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(lsize);

  // Create zone id space.

  arg_list largs = offset_index_space_state::make_arg_list(1, lzone_size);
  make_id_space(lid_spaces, "zone_id_space", "offset_index_space_state", largs);

  // Create vertex id space.

  largs = offset_index_space_state::make_arg_list(1+lzone_size, lvertex_size);
  make_id_space(lid_spaces, "vertex_id_space", "offset_index_space_state", largs);

  // Create connectivity interval.

#ifndef NO_CONNECTIVITY

  largs =
    ijk_connectivity_index_space_interval::
    make_arg_list(1+lzone_size, lj_size, lk_size);

  pod_index_type lconn_id =
    make_id_space_interval(lid_spaces, "ijk_connectivity_index_space_interval",
			   largs, lzone_size);

  // Give the id space a name.

  strstream lconn_name;
  lconn_name << "conn_" << lconn_id;

  lid_spaces.put_name(lconn_id, lconn_name.str());

  // Test iterator facet.

  test_iterator_facet<ijk_connectivity_implicit_index_space_iterator>(lid_spaces, lconn_id);

  // Test state facet.

  test_state_facet(lid_spaces, lconn_id, 0, lid_spaces.hub_pod(lconn_id, 0));

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  ijk_connectivity_implicit_index_space_iterator lconn_itr(lid_spaces, lconn_id);
  const ijk_connectivity_index_space_interval& lconn_interval =
    reinterpret_cast<const ijk_connectivity_index_space_interval&>(lconn_itr.host());

  cout << "vertex_hub_begin()   = " << lconn_interval.vertex_hub_begin() << endl;
  cout << "vertex_hub_begin(0)  = " << lconn_interval.vertex_hub_begin(0) << endl;
  cout << "j_size()             = " << lconn_interval.j_size() << endl;
  cout << "k_size()             = " << lconn_interval.k_size() << endl;
  cout << "j_vertex_size()()    = " << lconn_interval.j_vertex_size() << endl;
  cout << "k_vertex_size()()    = " << lconn_interval.k_vertex_size() << endl;
  cout << "jk_vertex_size()()   = " << lconn_interval.jk_vertex_size() << endl;

#endif

  // Create adjacency interval.

#ifndef NO_ADJACENCY

  largs =
    ijk_adjacency_index_space_interval::
    make_arg_list(1, li_size, lj_size, lk_size);

  pod_index_type ladj_id =
    make_id_space_interval(lid_spaces, "ijk_adjacency_index_space_interval",
			   largs, lvertex_size);

 // Give the id space a name.

  strstream ladj_name;
  ladj_name << "adj_" << ladj_id;

  lid_spaces.put_name(ladj_id, ladj_name.str());

  // Test iterator facet.

  test_iterator_facet<ijk_adjacency_implicit_index_space_iterator>(lid_spaces, ladj_id);

  // Test state facet.

  test_state_facet(lid_spaces, ladj_id, 0, lid_spaces.hub_pod(ladj_id, 0));

  // Miscellaneous interval tests.

  print_out_header("Testing miscellaneous interval functions");

  ijk_adjacency_implicit_index_space_iterator ladj_itr(lid_spaces, ladj_id);
  const ijk_adjacency_index_space_interval& ladj_interval =
    reinterpret_cast<const ijk_adjacency_index_space_interval&>(ladj_itr.host());

  cout << "zone_hub_begin()   = " << ladj_interval.zone_hub_begin() << endl;
  cout << "zone_hub_begin(0)  = " << ladj_interval.zone_hub_begin(0) << endl;
  cout << "i_size()           = " << ladj_interval.i_size() << endl;
  cout << "j_size()           = " << ladj_interval.j_size() << endl;
  cout << "k_size()           = " << ladj_interval.k_size() << endl;
  cout << "i_vertex_size()    = " << ladj_interval.i_vertex_size() << endl;
  cout << "j_vertex_size()    = " << ladj_interval.j_vertex_size() << endl;
  cout << "k_vertex_size()    = " << ladj_interval.k_vertex_size() << endl;

#endif

  // Output the id space family.

  cout << lid_spaces << endl;

  return 0;
}

  
