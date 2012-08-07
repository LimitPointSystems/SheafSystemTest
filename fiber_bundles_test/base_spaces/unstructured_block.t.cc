
// $RCSfile: unstructured_block.t.cc,v $ $Revision: 1.29 $ $Date: 2012/03/01 00:40:32 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example base_spaces/unstructured_block.t.cc
/// Test driver for gen_polyline_mesh.cc.

#include "fiber_bundles_namespace.h"
#include "unstructured_block.h"
#include "sec_at0.h"
#include "std_string.h"
#include "storage_agent.h"
#include "test_sections.impl.h"

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

  base_space_poset* lmesh =
    &xns->new_base_space<unstructured_block>("unstructured_mesh_base_space_0d",
					     "",
					     "",
					     1,
					     true);
  lmesh->get_read_write_access();

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "point");

  unstructured_block lblock(lmesh, lproto_path, xi_size);
  lblock.put_name("unstructured_block_0d", true, false);
  lblock.detach_from_state();

  lmesh->release_access();
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

  base_space_poset* lmesh =
    &xns->new_base_space<unstructured_block>("unstructured_mesh_base_space_1d",
					     "",
					     "",
					     1,
					     true);
  lmesh->get_read_write_access();

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "segment_complex");

  unstructured_block lblock(lmesh, lproto_path, xi_size);
  lblock.put_name("unstructured_block_1d", true, false);
  lblock.detach_from_state();

  lmesh->release_access();
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

  base_space_poset* lmesh =
    &xns->new_base_space<unstructured_block>("unstructured_mesh_base_space_2d",
					     "",
					     "",
					     2,
					     true);
  lmesh->get_read_write_access();

  // Make quad block.

  poset_path lquad_proto_path(unstructured_block::prototypes_poset_name(),
                              "quad_complex");

  unstructured_block lquad_block(lmesh, lquad_proto_path, xi_size, xj_size);
  lquad_block.put_name("unstructured_quad_block_2d", true, false);
  lquad_block.detach_from_state();

  // Make triangle block.

  poset_path ltriangle_proto_path(unstructured_block::prototypes_poset_name(),
                                  "triangle_nodes");

  unstructured_block ltriangle_block(lmesh, ltriangle_proto_path,
                                     xi_size, xj_size);
  ltriangle_block.put_name("unstructured_triangle_block_2d", true, false);
  ltriangle_block.detach_from_state();

  lmesh->release_access();
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

  base_space_poset* lmesh =
    &xns->new_base_space<unstructured_block>("unstructured_mesh_base_space_3d",
					     "",
					     "",
					     3,
					     true);
  lmesh->get_read_write_access();

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "hex_nodes");

  unstructured_block lblock(lmesh, lproto_path, xi_size, xj_size, xk_size);
  lblock.put_name("unstructured_block_3d", true, false);


  // Make non-uniform (property) section space.

  sec_at0::host_type& lprop_space =
    new_host_space<sec_at0>(*xns, "property_section_space",
			    lblock.path());

  sec_at0 lprop(&lprop_space);
  lprop.get_read_write_access();
  lprop.put_name("property", true, false);

  sec_at0::fiber_type::volatile_type lfiber = 2.0;
  lprop = lfiber;

  cout << lprop_space << endl << endl;

  // Clean-up.

  lblock.detach_from_state();
  lmesh->release_access();
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

  base_space_poset* lmesh =
    &xns->new_base_space<unstructured_block>("hex_faces_nodes_base_space",
					     "",
					     "",
					     3,
					     true);
  lmesh->get_read_write_access();

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "hex_faces_nodes");

  unstructured_block lblock(lmesh, lproto_path, xi_size, xj_size, xk_size);
  lblock.put_name("hex_faces_nodes_block", true, false);
  lblock.detach_from_state();

  lmesh->release_access();
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
