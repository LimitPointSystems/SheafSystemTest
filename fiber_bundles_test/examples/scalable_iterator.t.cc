
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
#include "std_fstream.h"
#include "stop_watch.h"
#include "storage_agent.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "unstructured_block.h"
#include "zone_nodes_block.h"
#include "block_scaling_test.impl.h"

using namespace std;
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
