
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @deprecated Use the individual zone_nodes_block examples:
/// base_spaces/zone_nodes_block_1d.t.cc
/// base_spaces/zone_nodes_block_2d.t.cc
/// base_spaces/zone_nodes_block_3d.t.cc

/// @example base_spaces/scalable_zone_nodes_block.t.cc
/// Test driver for timing zone_nodes_block performance.

#include "zone_nodes_block.h"
#include "block_scaling_test.impl.h"

using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:
  plot::plot_type ltime_plot_types[4];
  ltime_plot_types[0] = plot::LINEAR;
  ltime_plot_types[1] = plot::LINEAR;
  ltime_plot_types[2] = plot::CONSTANT;
  ltime_plot_types[3] = plot::LINEAR;

  plot::plot_type lmem_plot_types[5];
  lmem_plot_types[0] = plot::LINEAR;
  lmem_plot_types[1] = plot::LINEAR;
  lmem_plot_types[2] = plot::LINEAR;
  lmem_plot_types[3] = plot::LINEAR;
  lmem_plot_types[4] = plot::CONSTANT;

  test_scaling<zone_nodes_block, 1>(xargc, xargv, ltime_plot_types,lmem_plot_types);
  
  // Postconditions:

  // Exit:

  return 0;
}
