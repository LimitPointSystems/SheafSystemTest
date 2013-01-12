
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Test driver for timing iterator performance.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "fiber_bundles_namespace.h"
#include "plot.h"
#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "postorder_iterator.h"
#include "preorder_iterator.h"
#include "std_strstream.h"
#include "std_fstream.h"
#include "stop_watch.h"
#include "storage_agent.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "unstructured_block.h"
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

  plot::plot_type lmem_plot_types[4];
  lmem_plot_types[0] = plot::LINEAR;
  lmem_plot_types[1] = plot::LINEAR;
  lmem_plot_types[2] = plot::LINEAR;
  lmem_plot_types[3] = plot::CONSTANT;

  test_scaling<zone_nodes_block, 3>(xargc, xargv, ltime_plot_types,
				    lmem_plot_types);
  
  // Postconditions:

  // Exit:

  return 0;
}
