
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @deprecated Use the individual unstructured_block examples:
/// base_spaces/unstructured_block_1d.t.cc
/// base_spaces/unstructured_block_2d.t.cc
/// base_spaces/unstructured_block_3d.t.cc

/// @example base_spaces/scalable_unstructured_block.t.cc
/// Test driver for timing unstructured_block performance.

#include "unstructured_block.h"
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

  test_scaling<unstructured_block, 3>(xargc, xargv, ltime_plot_types,
				      lmem_plot_types);
  
  // Postconditions:

  // Exit:

  return 0;
}
