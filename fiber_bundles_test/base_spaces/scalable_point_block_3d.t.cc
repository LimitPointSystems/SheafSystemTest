// $RCSfile: scalable_point_block_3d.t.cc,v $ $Revision: 1.9 $ $Date: 2012/03/01 00:40:31 $

//
// Copyrbase_spacesight (c) 2012 Limit Point Systems, Inc.
//

/// @example base_spaces/scalable_point_block_3d.t.cc
/// Test driver for timing point_block_3d performance.

#include "point_block_3d.h"
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
  lmem_plot_types[1] = plot::CONSTANT;
  lmem_plot_types[2] = plot::LINEAR;
  lmem_plot_types[3] = plot::LINEAR;
  lmem_plot_types[4] = plot::CONSTANT;

  test_scaling<point_block_3d, 3>(xargc, xargv, ltime_plot_types,
				  lmem_plot_types);
  
  // Postconditions:

  // Exit:

  return 0;
}
