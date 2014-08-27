
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

/// @example base_spaces/unstructured_block.t.cc
/// Test driver for gen_polyline_mesh.cc.

#include "fiber_bundles_namespace.h"
#include "unstructured_block.h"
#include "sec_at0.h"
#include "std_string.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "test_sections.impl.h"

using namespace std;
using namespace fiber_bundle;

void
make_unstructured_block_0d(fiber_bundles_namespace* xns,
                           size_type xi_size)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());
  require(xi_size > 0);

  // Body:

  unstructured_block::standard_host(*xns, "unstructured_mesh_base_space_0d", 1, true);
  base_space_poset& lmesh = xns->member_poset<base_space_poset>("unstructured_mesh_base_space_0d");

  lmesh.get_read_write_access();

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "point");

  unstructured_block lblock(&lmesh, lproto_path, xi_size);
  lblock.put_name("unstructured_block_0d", true, false);
  lblock.detach_from_state();

  lmesh.release_access();
}

void
make_unstructured_block_1d(fiber_bundles_namespace* xns,
                           size_type xi_size)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());
  require(xi_size > 0);

  // Body:

  unstructured_block::standard_host(*xns, "unstructured_mesh_base_space_1d", 1, true);
  base_space_poset& lmesh = xns->member_poset<base_space_poset>("unstructured_mesh_base_space_1d");

  lmesh.get_read_write_access();

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "segment_complex");

  unstructured_block lblock(&lmesh, lproto_path, xi_size);
  lblock.put_name("unstructured_block_1d", true, false);
  lblock.detach_from_state();

  lmesh.release_access();
}

void
make_unstructured_block_2d(fiber_bundles_namespace* xns,
                           size_type xi_size,
                           size_type xj_size)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());
  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  unstructured_block::standard_host(*xns, "unstructured_mesh_base_space_2d", 2, true);
  base_space_poset& lmesh = xns->member_poset<base_space_poset>("unstructured_mesh_base_space_2d");

  lmesh.get_read_write_access();

  // Make quad block.

  poset_path lquad_proto_path(unstructured_block::prototypes_poset_name(),
                              "quad_complex");

  unstructured_block lquad_block(&lmesh, lquad_proto_path, xi_size, xj_size);
  lquad_block.put_name("unstructured_quad_block_2d", true, false);
  lquad_block.detach_from_state();

  // Make triangle block.

  poset_path ltriangle_proto_path(unstructured_block::prototypes_poset_name(),
                                  "triangle_nodes");

  unstructured_block ltriangle_block(&lmesh, ltriangle_proto_path,
                                     xi_size, xj_size);
  ltriangle_block.put_name("unstructured_triangle_block_2d", true, false);
  ltriangle_block.detach_from_state();

  lmesh.release_access();
}

void
make_unstructured_block_3d(fiber_bundles_namespace* xns,
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

  unstructured_block::standard_host(*xns, "unstructured_mesh_base_space_3d", 3, true);
  base_space_poset& lmesh = xns->member_poset<base_space_poset>("unstructured_mesh_base_space_3d");

  lmesh.get_read_write_access();

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "hex_nodes");

  unstructured_block lblock(&lmesh, lproto_path, xi_size, xj_size, xk_size);
  lblock.put_name("unstructured_block_3d", true, false);


  // Make non-uniform (property) section space.

  sec_at0::host_type& lprop_space =
    sec_at0::standard_host(*xns, lblock.path(false), "", "", "", false);

  sec_at0 lprop(&lprop_space);
  lprop.get_read_write_access();
  lprop.put_name("property", true, false);

  sec_at0::fiber_type::volatile_type lfiber = 2.0;
  lprop = lfiber;

  cout << lprop_space << endl << endl;

  // Clean-up.

  lblock.detach_from_state();
  lmesh.release_access();
  lprop.release_access();
  lprop.detach_from_state();
}

void
make_hex_faces_nodes_block(fiber_bundles_namespace* xns,
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

  unstructured_block::standard_host(*xns, "hex_faces_nodes_base_space", 3, true);
  base_space_poset& lmesh = xns->member_poset<base_space_poset>("hex_faces_nodes_base_space");

  lmesh.get_read_write_access();

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "hex_faces_nodes");

  unstructured_block lblock(&lmesh, lproto_path, xi_size, xj_size, xk_size);
  lblock.put_name("hex_faces_nodes_block", true, false);
  lblock.detach_from_state();

  lmesh.release_access();
}

int
main(int xargc, char* xargv[])
{
  // Command line processing:

  string filename = filename_from_cmdline(*xargv);

  size_type i_size = (xargc > 1) ? atoi(xargv[1]): 1;
  size_type j_size = (xargc > 2) ? atoi(xargv[2]): 2;
  size_type k_size = (xargc > 3) ? atoi(xargv[3]): 3;

  // Preconditions:

  require(i_size > 0);
  require(j_size > 0);
  require(k_size > 0);

  // Body:

  fiber_bundles_namespace* lns = new fiber_bundles_namespace(filename);

  lns->get_read_write_access();

//   make_unstructured_block_0d(lns, i_size);
//   make_unstructured_block_1d(lns, i_size);
//   make_unstructured_block_2d(lns, i_size, j_size);
  make_unstructured_block_3d(lns, i_size, j_size, k_size);
//   make_hex_faces_nodes_block(lns, i_size, j_size, k_size);

  cout << *lns << endl;

  storage_agent sa(filename + ".hdf");
  sa.write_entire(*lns);

  delete lns;


  // Postconditions:

  // Exit:

  return 0;
}
