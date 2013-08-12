

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example base_spaces/structured_block_2d.t.cc
/// Test driver for structured_block_2d.

#include "chart_point_2d.h"
#include "fiber_bundles_namespace.h"
#include "ij_product_structure.h"
#include "sec_at0.h"
#include "sec_e2.h"
#include "sec_e2_uniform.h"
#include "std_sstream.h"
#include "std_string.h"
#include "storage_agent.h"
#include "structured_block_2d.h"
#include "tern.h"
#include "test_sections.impl.h"
#include "wsv_block.h"

using namespace fiber_bundle;


int
main(int xargc, char* xargv[])
{

  string filename = filename_from_cmdline(*xargv);

  size_type size_0 = (xargc > 1) ? atoi(xargv[1]) : 2;
  size_type size_1 = (xargc > 2) ? atoi(xargv[2]) : 2;

  fiber_bundles_namespace lns(filename);

  lns.get_read_write_access();

  // Make the mesh

  structured_block_2d::new_host(lns, "2d_structued_mesh", true);
  base_space_poset& lmesh = lns.member_poset<base_space_poset>("2d_structued_mesh", true);

  structured_block_2d lblock0(&lmesh, size_0, size_1, true);
  lblock0.put_name("2d_structured_block0", true, true);

  structured_block_2d lblock1(&lmesh, size_0, size_1, true);
  lblock1.put_name("2d_structured_block1", true, true);

  // Create some jrms contained in block 0..

  lmesh.get_read_write_access();

  index_space_handle& lzone_id_space0 = lblock0.get_zone_id_space(false);
  const ij_product_structure& lzone_product0 =
    lzone_id_space0.product_structure<ij_product_structure>();

  index_space_handle& lzone_id_space1 = lblock1.get_zone_id_space(false);
  const ij_product_structure& lzone_product1 =
    lzone_id_space1.product_structure<ij_product_structure>();

  pod_index_type lzone_pod;
  scoped_index lzone_id(lzone_id_space0);
  block<scoped_index> lzone_ids(size_1);
  for(int i=0; i<size_0; ++i)
  {
    lzone_ids.clear();
    for(int j=0; j<size_1; ++j)
    {
      lzone_product0.ordinal(i, j, lzone_pod);
      lzone_id = lzone_pod;
      lzone_ids.push_back(lzone_id);
    }
    base_space_member lpart(&lmesh, lzone_ids.base(), lzone_ids.ct(), tern::TRUE, false);
    stringstream lstrm;
    lstrm << i;
    lpart.put_name("part"+lstrm.str(), true, true);
    lpart.detach_from_state();
  }

  lblock0.release_zone_id_space(lzone_id_space0, false);
  lblock1.release_zone_id_space(lzone_id_space1, false);

  // Create a jrm containing the last col of zones
  // in block 0 and the first col of zones in block 2.
  // This jrm is not contained in either block0 or block1,
  // but contains part of each in its down set.
  // Reading just this jrm is an important test for the
  // i/o system.

  int first = 0, last = size_0 - 1;
  
  lzone_ids.clear();
  for(int j=0; j<size_1; ++j)
  {
    lzone_product0.ordinal(last, j, lzone_pod);
    lzone_id = lzone_pod;
    lzone_ids.push_back(lzone_id);
  }

  for(int j=0; j<size_1; ++j)
  {
    lzone_product1.ordinal(first, j, lzone_pod);
    lzone_id = lzone_pod;
    lzone_ids.push_back(lzone_id);
  }

  base_space_member ljrm(&lmesh, lzone_ids.base(), lzone_ids.ct(), tern::TRUE, false);
  ljrm.put_name("partial range", true, false);
  
  poset_path lbase_path = lblock0.path();

  //  cout << lmesh << endl;  

//   // Test the refinement map.

//   cout << endl << "##### Refinement map test ###############" << endl << endl;

//   chart_point_2d lpt(lblock0.index(), -1.0, -1.0);

//   chart_point_2d lref_pt;

//   for(double lxcoord= -1.0; lxcoord <= 1.0; lxcoord += 0.5)
//   {
//     lpt.u() = lxcoord;

//     for(double lycoord= -1.0; lycoord <= 1.0; lycoord += 0.5)
//     {
//       lpt.v() = lycoord;

//       lblock0.refine_point_pa(lpt, lref_pt);
//       cout << "point: " << lpt << "\trefined point: " << lref_pt;
//       lblock0.unrefine_point_pa(lref_pt, lpt);
//       cout << "\tunrefined point: " << lpt << endl;
//       cout << endl;
//     }

//   }

//   cout << endl << "##### End refinement map test ###############" << endl << endl;

  // Make uniform (coordinate) section space.

  sec_e2_uniform::host_type& luniform_space =
    new_host_space<sec_e2_uniform>(lns, "coordinates_section_space", lbase_path);

  wsv_block<sec_vd_dof_type> llower("0.0 0.0");
  wsv_block<sec_vd_dof_type> lupper("1.0 1.0");

  sec_e2_uniform lcoords(&luniform_space, llower, lupper, true);
  lcoords.put_name("coordinates", true, true);

  //  cout << luniform_space << endl;

  // Make non-uniform (property) section space.

  sec_at0::host_type& lprop_space =
    new_host_space<sec_at0>(lns, "property_section_space", lbase_path);

  sec_at0 lprop(&lprop_space);
  lprop.get_read_write_access();
  lprop.put_name("property", true, false);

  sec_at0::fiber_type::volatile_type lfiber = 2.0;
  lprop = lfiber;

  //  cout << lprop_space << endl << endl;

  // Clean-up.

  lblock0.detach_from_state();
  lblock1.detach_from_state();
  ljrm.detach_from_state();
  lmesh.release_access();
  lcoords.detach_from_state();
  lprop.release_access();
  lprop.detach_from_state();

  // Output namespace.

  //  cout << lns << endl;

  storage_agent sa(filename + ".hdf");
  sa.write_entire(lns);

  cout << lns << endl;
  //cout << lmesh << endl;  

  return 0;
}
