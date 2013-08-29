

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example base_spaces/point_block_1d.t.cc
/// Test driver for point_block_1d.cc.

#include "chart_point_1d.h"
#include "fiber_bundles_namespace.h"
#include "poset_path.h"
#include "sec_at0.h"
#include "sec_e1.h"
#include "sec_e1_uniform.h"
#include "std_string.h"
#include "point_block_1d.h"
#include "std_string.h"
#include "storage_agent.h"
#include "test_sections.impl.h"

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
    new_host_space<sec_e1_uniform>(lns, "coordinates_section_space", lbase_path);

  sec_e1_uniform lcoords(&luniform_space, 0.0, 1.0, true);
  lcoords.put_name("coordinates", true, true);

  cout << luniform_space << endl;

  // Make non-uniform (property) section.

  sec_at0::host_type& lprop_space =
    new_host_space<sec_at0>(lns, "property_section_space",
			    "sec_rep_descriptors/vertex_vertex_constant",
			    lbase_path);

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
