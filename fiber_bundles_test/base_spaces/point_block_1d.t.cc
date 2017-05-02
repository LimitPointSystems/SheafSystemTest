
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

/// @example base_spaces/point_block_1d.t.cc
/// Test driver for point_block_1d.cc.

#include "SheafSystem/chart_point_1d.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/poset_path.h"
#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_e1.h"
#include "SheafSystem/sec_e1_uniform.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/point_block_1d.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_sections.impl.h"

using namespace std;
using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{

  string filename = filename_from_cmdline(*xargv);

  string size_arg;
  size_type size;

  if (xargc > 1)
  {
    size = atoi(xargv[1]);
    size_arg = xargv[1];
  }
  else
  {
    size = 2;
    size_arg = "2";
  }

  fiber_bundles_namespace lns(filename);

  lns.get_read_write_access();

  // Make the mesh

  point_block_1d::standard_host(lns, "1d_point_mesh", true);
  base_space_poset& lmesh = lns.member_poset<base_space_poset>("1d_point_mesh", true);

  point_block_1d lblock(&lmesh, size, true);
  lblock.get_read_write_access();
  lblock.put_name("1D_point_block", true, false);

  poset_path lbase_path = lblock.path();

  cout << lmesh << endl;

  // Make uniform (coordinate) section.

  sec_e1_uniform::host_type& luniform_space =
    sec_e1_uniform::standard_host(lns, lbase_path, "", "", "", false);

  sec_e1_uniform lcoords(&luniform_space, 0.0, 1.0, true);
  lcoords.put_name("coordinates", true, true);

  cout << luniform_space << endl;

  // Make non-uniform (property) section.

  sec_at0::host_type& lprop_space =
    sec_at0::standard_host(lns, lbase_path, "sec_rep_descriptors/vertex_vertex_constant", "", "", false);

  sec_at0 lprop(&lprop_space);
  lprop.get_read_write_access();
  lprop.put_name("property", true, false);

  sec_at0::fiber_type::volatile_type lfiber = 2.0;
  lprop = lfiber;

  cout << lprop_space << endl << endl;

  // Clean-up.

  lblock.release_access();
  lblock.detach_from_state();
  lcoords.detach_from_state();
  lprop.release_access();
  lprop.detach_from_state();

  // Output namespace.

  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  return 0;
}
