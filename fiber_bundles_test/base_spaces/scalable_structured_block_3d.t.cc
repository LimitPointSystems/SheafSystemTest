// $RCSfile$ $Revision$ $Date$

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example base_spaces/scalable_structured_block_3d.t.cc
/// Test driver for timing structured_block_3d performance.

//#define TEST_SECTION // Test the construction and assignment of a scalar section
//#define TEST_ITR // Test the pre and post order iterators, connectivity and adjacency iterators and upper and lower cover iterators.
//#define TEST_IO // Test the io system
//#define USE_RUSAGE // Use getrusage to test memory performance.  Otherwise, use the deep size function of the block.

#include "structured_block_3d.h"
#include "block_scaling_test.impl.h"

using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  int lnum_curves = 1;

#ifdef TEST_SECTION
  lnum_curves += 2;
#endif

#ifdef TEST_ITR
  lnum_curves += 7;
#endif

#ifdef TEST_IO
  lnum_curves += 2;
#endif

  plot::plot_type* ltime_plot_types = new plot::plot_type[lnum_curves];

  int tid = 0;

  ltime_plot_types[tid++] = plot::LINEAR;

#ifdef TEST_SECTION
  ltime_plot_types[tid++] = plot::CONSTANT;
  ltime_plot_types[tid++] = plot::LINEAR;
#endif

#ifdef TEST_ITR
  ltime_plot_types[tid++] = plot::LINEAR;
  ltime_plot_types[tid++] = plot::CONSTANT;
  ltime_plot_types[tid++] = plot::LINEAR;
  ltime_plot_types[tid++] = plot::LINEAR;
  ltime_plot_types[tid++] = plot::LINEAR;
  ltime_plot_types[tid++] = plot::LINEAR;
  ltime_plot_types[tid++] = plot::LINEAR;
#endif

#ifdef TEST_IO

#ifdef TEST_SECTION
  ltime_plot_types[tid++] = plot::LINEAR;
#else
  ltime_plot_types[tid++] = plot::CONSTANT;
#endif // TEST_SECTION
  ltime_plot_types[tid++] = plot::LINEAR;

#endif // TEST_IO

#ifdef USE_RUSAGE
  plot::plot_type lmem_plot_types[7];
#else
  plot::plot_type lmem_plot_types[6];
#endif

  lmem_plot_types[0] = plot::LINEAR;
  lmem_plot_types[1] = plot::CONSTANT;
  lmem_plot_types[2] = plot::CONSTANT;
  lmem_plot_types[3] = plot::LINEAR;
  lmem_plot_types[4] = plot::CONSTANT;
  lmem_plot_types[5] = plot::CONSTANT;
#ifdef USE_RUSAGE
  lmem_plot_types[6] = plot::LINEAR;
#endif

  test_scaling<structured_block_3d, 3>(xargc, xargv, ltime_plot_types,
				       lmem_plot_types);
  
  // Postconditions:

  // Exit:

  return 0;
}
