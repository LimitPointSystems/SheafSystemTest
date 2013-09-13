
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

/// @deprecated Use the individual structured_block examples:
/// base_spaces/structured_block_1d.t.cc
/// base_spaces/structured_block_2d.t.cc
/// base_spaces/structured_block_3d.t.cc

/// @example base_spaces/scalable_structured_block.t.cc
/// Test driver for timing write_ and read_entire.

#include "deep_size.h"
#include "fiber_bundles_namespace.h"
#include "plot.h"
#include "structured_block_3d.h"
#include "storage_agent.h"
#include "std_strstream.h"
#include "stop_watch.h"

using namespace fiber_bundle;

typedef struct
{
  int _i_dim;
  int _j_dim;
  int _k_dim;

  int i_value()
  {
    return _i_dim*10;
  }

  int j_value()
  {
    return _j_dim*10;
  }

  int k_value()
  {
    return _k_dim*10;
  }

  int num_elements()
  {
    return (i_value() * j_value() * k_value());
  }
}
dimension;

static int darray_size()
{
  return 12;
}

static dimension* darray()
{
  dimension* ldims = new dimension[darray_size()];

  ldims[0]._i_dim = 2;
  ldims[0]._j_dim = 2;
  ldims[0]._k_dim = 2;

  ldims[1]._i_dim = 2;
  ldims[1]._j_dim = 2;
  ldims[1]._k_dim = 3;

  ldims[2]._i_dim = 2;
  ldims[2]._j_dim = 2;
  ldims[2]._k_dim = 4;

  ldims[3]._i_dim = 2;
  ldims[3]._j_dim = 3;
  ldims[3]._k_dim = 4;

  ldims[4]._i_dim = 3;
  ldims[4]._j_dim = 3;
  ldims[4]._k_dim = 4;

  ldims[5]._i_dim = 4;
  ldims[5]._j_dim = 4;
  ldims[5]._k_dim = 4;

  ldims[6]._i_dim = 4;
  ldims[6]._j_dim = 4;
  ldims[6]._k_dim = 5;

  ldims[7]._i_dim = 4;
  ldims[7]._j_dim = 5;
  ldims[7]._k_dim = 5;

  ldims[8]._i_dim = 5;
  ldims[8]._j_dim = 5;
  ldims[8]._k_dim = 5;

  ldims[9]._i_dim = 5;
  ldims[9]._j_dim = 5;
  ldims[9]._k_dim = 6;

  ldims[10]._i_dim = 5;
  ldims[10]._j_dim = 6;
  ldims[10]._k_dim = 6;

  ldims[11]._i_dim = 6;
  ldims[11]._j_dim = 6;
  ldims[11]._k_dim = 6;

  return ldims;
}

void
make_structured_block_3d(fiber_bundles_namespace* xns,
                         size_type xi_size,
                         size_type xj_size,
                         size_type xk_size)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);

  // Body:

  base_space_poset* lmesh =
    structured_block_3d::standard_host(xns, "structured_mesh_base_space_3d");
  lmesh->get_read_write_access();

  structured_block_3d lblock(lmesh, xi_size, xj_size, xk_size);
  lblock.put_name("structured_block_3d", true, false);

  lblock.detach_from_state();
  lmesh->release_access();

}


void
time_block(int xi, int xj, int xk, plot& xplot)
{
  // Preconditions:

  // Body:

  double* lpoint = xplot.create_point();
  lpoint[0] = (double) (xi*xj*xk);

  fiber_bundles_namespace* lns =
    new fiber_bundles_namespace("scalable_structured_block.t");
  lns->get_read_write_access();

  stop_watch lwatch;

  lwatch.start();

  make_structured_block_3d(lns, xi, xj, xk);

  lwatch.stop();

  cout << "structured_block "
  << setw(4) << xi << "x"
  << setw(4) << xj << "x"
  << setw(4) << xk
  << "\ttime: " << lwatch.time()
  << endl;


  lpoint[1] = lwatch.time();

  // Add point

  xplot.add_point(lpoint);

  // Clean-up

  delete lns;
  delete [] lpoint;

  // Postconditions:

  // Exit:
}

void
time_block(int xi, int xj, int xk, plot& xtime_plot,  plot& xmem_plot)
{
  // Preconditions:

  // Body:

  double* lpoint = xtime_plot.create_point();
  lpoint[0] = (double) (xi*xj*xk);

  fiber_bundles_namespace* lns =
    new fiber_bundles_namespace("scalable_structured_block.t");
  lns->get_read_write_access();

  //   //==========================================================================

  //   size_t ldeep_size1;
  //   {
  //   ldeep_size1 = deep_size(*lns);

  //   //cout << endl;
  //   cout << "A. deep_size(*lns) = " << ldeep_size1 << endl;
  //   //cout << endl;
  //   }
  //   //==========================================================================

  stop_watch lwatch;

  lwatch.start();

  make_structured_block_3d(lns, xi, xj, xk);

  lwatch.stop();

  //   //==========================================================================
  //   size_t ldeep_size2;
  //   {
  //   ldeep_size2 = deep_size(*lns);

  //   //cout << endl;
  //   cout << "B. deep_size(*lns) = " << ldeep_size2 << endl;
  //   cout << "diff = " << ldeep_size2 - ldeep_size1 << endl;
  //   //cout << endl;
  //   }
  //   //==========================================================================


  double ltime = lwatch.time();

  lpoint[1] = ltime;

  // Add point to time plot.

  xtime_plot.add_point(lpoint);

  // Get the "deep size" of the base space poset.

  base_space_poset* lmesh =
    new base_space_poset(lns, "structured_mesh_base_space_3d");
  lmesh->get_read_access();

  size_t lmemory = deep_size(*lmesh);

  //cout << "deep_size(*lmesh) = " << lmemory << endl;

  lmesh->release_access();
  lmesh->detach_from_state();

  lpoint[1] = static_cast<double>(lmemory);

  // Add point to memory plot.

  xmem_plot.add_point(lpoint);

  cout << "structured_block "
  << setw(4) << xi << " x"
  << setw(4) << xj << " x"
  << setw(4) << xk
  << "\ttime: " << ltime
  << " \tmemory: " << lmemory
  << endl;

  // Clean-up

  delete lns;
  delete [] lpoint;

  // Postconditions:

  // Exit:
}

int
main(int xargc, char* xargv[])
{
  // Command line processing:

  size_type max_elements = (xargc > 1) ? atoi(xargv[1]): 16000;

  // Preconditions:

  require(max_elements >= 8000);

  // Body:

  // Create plots

  int lnum_curves = 1;
  const char** lcurve_labels = new const char*[lnum_curves];
  lcurve_labels[0] = "structured_block";

  // Create time plot instance.

  plot ltime_plot("scalable_structured_block.t",
                  lcurve_labels,
                  lnum_curves,
                  "Member Count",
                  "Time(ms)");

  // Create memory plot instance.

  plot lmem_plot("scalable_structured_block_mem.t",
                 lcurve_labels,
                 lnum_curves,
                 "Member Count",
                 "Memory(bytes)");

  // Add data points to the plots.

  dimension* ldims = darray();
  int ldarray_size = darray_size();

  for(int di = 0; di < ldarray_size; di++)
  {
    if(ldims[di].num_elements() > max_elements)
      break;

    time_block(ldims[di].i_value(),
               ldims[di].j_value(),
               ldims[di].k_value(),
               ltime_plot, lmem_plot);
  }

  // Postconditions:

  // Exit:
}
