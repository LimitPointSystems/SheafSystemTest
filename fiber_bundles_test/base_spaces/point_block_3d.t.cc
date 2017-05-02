

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example base_spaces/point_block_3d.t.cc
/// Test driver for point_block_3d.cc.

#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/poset_path.h"
#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_e3.h"
#include "SheafSystem/sec_e3_uniform.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/point_block_3d.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_sections.impl.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{

  string filename = filename_from_cmdline(*xargv);

  size_type size_0 = (xargc > 1) ? atoi(xargv[1]) : 3;
  size_type size_1 = (xargc > 2) ? atoi(xargv[2]) : 3;
  size_type size_2 = (xargc > 3) ? atoi(xargv[3]) : 3;

  fiber_bundles_namespace lns(filename);

  lns.get_read_write_access();

  // Make the mesh

  point_block_3d::standard_host(lns, "3d_point_mesh", true);
  base_space_poset& lmesh = lns.member_poset<base_space_poset>("3d_point_mesh", true);

  point_block_3d lblock(&lmesh, size_0, size_1, size_2, true);
  lblock.get_read_write_access();
  lblock.put_name("3D_point_block", true, false);

  poset_path lbase_path = lblock.path();

  cout << lmesh << endl;

  // Make uniform (coordinate) section space.

  sec_e3_uniform::host_type& luniform_space =
    sec_e3_uniform::standard_host(lns, lbase_path, "", "", "", false);

  wsv_block<sec_vd_dof_type> llower("0.0 0.0 0.0");
  wsv_block<sec_vd_dof_type> lupper("1.0 1.0 1.0");

  sec_e3_uniform lcoords(&luniform_space, llower, lupper, true);
  lcoords.put_name("coordinates", true, true);

  cout << luniform_space << endl;

  // Make non-uniform (property) section space.

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
