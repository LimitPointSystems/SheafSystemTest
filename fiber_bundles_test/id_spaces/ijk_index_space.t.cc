
// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example ijk_index_space.t.cc
/// Test driver for for the connectivity and adjacency id spaces for
/// a 3-dimensional structured block.

#include "arg_list.h"
#include "ijk_adjacency_index_space_interval.h"
#include "ijk_connectivity_index_space_interval.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "offset_index_space_state.h"
#include "test_index_spaces.h"

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

  make_id_space_interval(lid_spaces, "ijk_connectivity_index_space_interval",
			 largs, lzone_size);

#endif

  // Create adjacency interval.

#ifndef NO_ADJACENCY

  largs =
    ijk_adjacency_index_space_interval::
    make_arg_list(1, li_size, lj_size, lk_size);

  make_id_space_interval(lid_spaces, "ijk_adjacency_index_space_interval",
			 largs, lvertex_size);

#endif

  // Output the id space family.

  cout << lid_spaces << endl;

  return 0;
}

  
