
// $RCSfile: zone_nodes_block.t.cc,v $ $Revision: 1.14 $ $Date: 2012/03/01 00:40:33 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example base_spaces/zone_nodes_block.t.cc
/// Test driver for zone_nodes_block.cc.

#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "hex_connectivity.h"
#include "line_connectivity.h"
#include "point_connectivity.h"
#include "quad_connectivity.h"
#include "scoped_index.h"
#include "std_string.h"
#include "storage_agent.h"
#include "zone_nodes_block.h"

using namespace fiber_bundle;

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
    &xns->new_base_space<zone_nodes_block>("zone_nodes_mesh_base_space_1d",
					   "",
					   "",
					   1,
					   true);
  lmesh->get_read_write_access();

  // Make line connectivity.

  line_connectivity lconn(xi_size);

  // Make block.

  zone_nodes_block lblock(*lmesh, lconn, true);
  lblock.put_name("line_block_1d", true, false);
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
    &xns->new_base_space<zone_nodes_block>("zone_nodes_mesh_base_space_2d",
					   "",
					   "",
					   2,
					   true);
  lmesh->get_read_write_access();

  // Make quad connectivity.

  quad_connectivity lconn(xi_size, xj_size);

  // Make quad block.

  zone_nodes_block lblock(*lmesh, lconn, true);
  lblock.put_name("quad_block_2d", true, false);
  lblock.detach_from_state();

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
    &xns->new_base_space<zone_nodes_block>("zone_nodes_mesh_base_space_3d",
					   "",
					   "",
					   3,
					   true);
  lmesh->get_read_write_access();

  // Make hex connectivity.

  hex_connectivity lconn(xi_size, xj_size, xk_size);

  // Make hex block.

  zone_nodes_block lblock(*lmesh, lconn, true);
  lblock.put_name("hex_block_3d", true, false);
  lblock.detach_from_state();

  lmesh->release_access();
}

void
test_deletion(fiber_bundles_namespace* xns)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());

  // Body:

  base_space_poset* lmesh =
    &xns->new_base_space<zone_nodes_block>("test_deletion_base_space_1d",
					   "",
					   "",
					   1,
					   true);
  lmesh->get_read_write_access();

  // Make line connectivity.

  line_connectivity lconn(3);

  // Make block.

  zone_nodes_block lblock(*lmesh, lconn, true);
  lblock.put_name("test_deletion_line_block_1d", true, false);
  lblock.detach_from_state();

  scoped_index lzone_id(lmesh->elements().id_space(), 1);

  cout << "Before deleting zone 1:" << endl;
  cout << *lmesh << endl;

  base_space_member lzone(lmesh, lzone_id);
  lzone.delete_state(true);

  cout << "After deleting zone 1:" << endl;
  cout << *lmesh << endl;

  scoped_index lnode_id(lmesh->vertices().id_space(), 1);

  cout << "Before deleting node 1:" << endl;
  cout << *lmesh << endl;

  base_space_member lnode(lmesh, lnode_id);
  lnode.delete_state(true);

  cout << "After deleting node 1:" << endl;
  cout << *lmesh << endl;

  //   index_map* lblock_id_map = lmesh->blocks().id_map();
  //   scoped_index lblock_id(0, lblock_id_map);

  //   cout << "Before deleting block 0:" << endl;
  //   cout << *lmesh << endl;

  //   base_space_member lblk(lmesh, lblock_id);
  //   lblk.delete_state(true);

  //   cout << "After deleting block 0:" << endl;
  //   cout << *lmesh << endl;


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

  make_unstructured_block_1d(lns, i_size);
  make_unstructured_block_2d(lns, i_size, j_size);
  make_unstructured_block_3d(lns, i_size, j_size, k_size);

  cout << *lns << endl;

  //  test_deletion(lns);

  storage_agent sa(filename + ".hdf");
  sa.write_entire(*lns);

  delete lns;


  // Postconditions:

  // Exit:

  return 0;
}
