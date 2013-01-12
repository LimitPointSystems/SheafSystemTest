
// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example i_index_space.t.cc
/// Test driver for for the connectivity and adjacency id spaces for
/// a 1-dimensional structured block.

#include "arg_list.h"
#include "i_adjacency_index_space_interval.h"
#include "i_connectivity_index_space_interval.h"
#include "index_space_family.h"
#include "offset_index_space_state.h"
#include "test_index_spaces.h"

//#define NO_CONNECTIVITY
//#define NO_ADJACENCY

using namespace fiber_bundle;

int main( int argc, char* argv[])
{
  // Parse input.

  size_t li_size = argc > 1 ? atoi(argv[1]) : 4;

  assertion(li_size > 0);

  // Create the top id space.

  size_type lzone_size = li_size;
  size_type lvertex_size = (li_size + 1);
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

  largs = i_connectivity_index_space_interval::make_arg_list(1+lzone_size);

  make_id_space_interval(lid_spaces, "i_connectivity_index_space_interval",
			 largs, lzone_size);

#endif

  // Create adjacency interval.

#ifndef NO_ADJACENCY

  largs = i_adjacency_index_space_interval::make_arg_list(1, li_size);

  make_id_space_interval(lid_spaces, "i_adjacency_index_space_interval",
			 largs, lvertex_size);

#endif

  // Output the id space family.

  cout << lid_spaces << endl;

  return 0;
}

  
