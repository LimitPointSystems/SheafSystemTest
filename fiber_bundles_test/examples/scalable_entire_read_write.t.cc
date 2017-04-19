
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

// Test driver for timing write_ and read_entire.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "SheafSystem/deep_size.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/hex_connectivity.h"
#include "SheafSystem/plot.h"
#include "SheafSystem/std_sstream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/zone_nodes_block.h"

using namespace std;
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
make_zone_nodes_block(fiber_bundles_namespace* xns,
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
    &xns->new_base_space<zone_nodes_block>("unstructured_mesh_base_space_3d", "", "", 3, true);
  lmesh->get_read_write_access();

  hex_connectivity lconn(xi_size, xj_size, xk_size);  

  zone_nodes_block lblock(*lmesh, lconn, true);
  lblock.put_name("hex_block", true, false);
  lblock.detach_from_state();

  lmesh->release_access();
}

void
time_write(fiber_bundles_namespace* xns, int xi, int xj, int xk, double* xpoint)
{
  // Preconditions:

  require(xns != 0);

  // Body:

  stringstream fname_stream;

  fname_stream << "scalable_entire_read_write_" << xi << "_"
  << xj << "_" << xk << ".t.hdf";

  string fname;

  fname_stream >> fname;

  cout << endl << fname << endl;

  storage_agent sa(fname);

  sa.write_entire(*xns);

  cout << "Wrote '" << (xi*xj*xk) << "' elements in '"
  << (sa.time())/(double) CLOCKS_PER_SEC << "' seconds" << endl;

  xpoint[1] = sa.time()/(double) CLOCKS_PER_SEC;

  // Postconditions:

  // Exit:
}

void
time_read(int xi, int xj, int xk, double* xpoint)
{
  // Preconditions:

  // Body:

  stringstream fname_stream;

  fname_stream << "scalable_entire_read_write_" << xi << "_"
  << xj << "_" << xk << ".t.hdf";

  string fname;

  fname_stream >> fname;

  namespace_poset lns(fname);

  lns.get_read_write_access();

  storage_agent sa(fname, sheaf_file::READ_ONLY, false);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.read_entire(lns);

  cout << "Read '" << (xi*xj*xk) << "' elements in '"
  << (sa.time())/(double) CLOCKS_PER_SEC << "' seconds" << endl;

  xpoint[2] = sa.time()/(double) CLOCKS_PER_SEC;

  // Postconditions:

  // Exit:
}

void
time_io(int xi, int xj, int xk, plot& xplot)
{
  // Preconditions:

  // Body:

  fiber_bundles_namespace* lns =
    new fiber_bundles_namespace("scalable_entire_read_write.t");
  lns->get_read_write_access();

  make_zone_nodes_block(lns, xi, xj, xk);

  // Create point

  double* lpoint = xplot.create_point();
  lpoint[0] = (double) (xi * xj * xk);

  // Write test; fills lpoint[1]

  time_write(lns, xi, xj, xk, lpoint);

  // Read test; fills lpoint[2]

  time_read(xi, xj, xk, lpoint);

  // Add point

  xplot.add_point(lpoint);

  // Clean-up

  delete lns;
  delete [] lpoint;

  // Postconditions:

  // Exit:
}

void
time_io(int xi, int xj, int xk, plot& xtime_plot, plot& xmem_plot)
{
  // Preconditions:

  // Body:

  fiber_bundles_namespace* lns =
    new fiber_bundles_namespace("scalable_entire_read_write.t");
  lns->get_read_write_access();

  make_zone_nodes_block(lns, xi, xj, xk);

  //   //===========================================================================
  //   {
  //   base_space_poset* lmesh =
  //     new base_space_poset(lns, "unstructured_mesh_base_space_3d");
  //   lmesh->get_read_access();

  //   size_t lmemory = deep_size(*lmesh);

  //   cout << "###### deep_size(*lmesh) = " << lmemory << endl;

  //   lmesh->release_access();
  //   lmesh->detach_from_state();
  //   }
  //   //===========================================================================


  // Create point

  double* lpoint = xtime_plot.create_point();
  lpoint[0] = (double) (xi * xj * xk);

  // Write test; fills lpoint[1]

  time_write(lns, xi, xj, xk, lpoint);

  //   //===========================================================================
  //   {
  //   base_space_poset* lmesh =
  //     new base_space_poset(lns, "unstructured_mesh_base_space_3d");
  //   lmesh->get_read_access();

  //   size_t lmemory = deep_size(*lmesh);

  //   cout << "?????? deep_size(*lmesh) = " << lmemory << endl;

  //   lmesh->release_access();
  //   lmesh->detach_from_state();
  //   }
  //   //===========================================================================


  // Read test; fills lpoint[2]

  time_read(xi, xj, xk, lpoint);

  // Add point to time plot.

  xtime_plot.add_point(lpoint);

  // Add point to memory plot.

  base_space_poset* lmesh =
    lns->member_poset<base_space_poset>(string("unstructured_mesh_base_space_3d"), false);
  lmesh->get_read_access();

  size_t lmemory = deep_size(*lmesh, false, 0);

  //cout << "deep_size(*lmesh) = " << lmemory << endl;

  lmesh->release_access();

  lpoint[1] = static_cast<double>(lmemory);

  // Add point to memory plot.

  xmem_plot.add_point(lpoint);

  cout << "zone_nodes_block "
  << setw(4) << xi << " x"
  << setw(4) << xj << " x"
  << setw(4) << xk
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

  // Create time plot instance.

  int lnum_curves = 2;
  const char** lcurve_labels = new const char*[lnum_curves];
  lcurve_labels[0] = "read";
  lcurve_labels[1] = "write";

  // Create time plot instance.

  plot ltime_plot("scalable_entire_read_write.t",
                  lcurve_labels,
                  lnum_curves,
                  "Member Count",
                  "Time(ms)");

  // Create memory plot instance.

  int lnum_mem_curves = 1;
  const char** lmem_curve_labels = new const char*[lnum_mem_curves];
  lmem_curve_labels[0] = "zone_nodes_block";

  plot lmem_plot("scalable_entire_read_write_mem.t",
                 lmem_curve_labels,
                 lnum_mem_curves,
                 "Member Count",
                 "Memory(bytes)");

  // Add data points to the plots.

  dimension* ldims = darray();
  int ldarray_size = darray_size();

  for(int di = 0; di < ldarray_size; di++)
  {
    if(ldims[di].num_elements() > max_elements)
      break;

    time_io(ldims[di].i_value(),
            ldims[di].j_value(),
            ldims[di].k_value(),
            ltime_plot, lmem_plot);
  }

  // Postconditions:

  // Exit:
}
