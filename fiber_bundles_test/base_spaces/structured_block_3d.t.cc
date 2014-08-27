
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

/// @example base_spaces/structured_block_3d.t.cc
/// Test driver for structured_block_3d.

#include "chart_point_3d.h"
#include "fiber_bundles_namespace.h"
#include "ijk_product_structure.h"
#include "sec_at0.h"
#include "sec_e3.h"
#include "sec_e3_uniform.h"
#include "std_sstream.h"
#include "std_string.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "structured_block_3d.h"
#include "tern.h"
#include "test_sections.impl.h"
#include "wsv_block.h"

using namespace std;
using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{

  string filename = filename_from_cmdline(*xargv);

  size_type size_0 = (xargc > 1) ? atoi(xargv[1]) : 2;
  size_type size_1 = (xargc > 2) ? atoi(xargv[2]) : 2;
  size_type size_2 = (xargc > 3) ? atoi(xargv[3]) : 2;


  fiber_bundles_namespace lns(filename);

  lns.get_read_write_access();

  structured_block_3d::standard_host(lns, "3d_structued_mesh", true);
  base_space_poset& lmesh = lns.member_poset<base_space_poset>("3d_structued_mesh", true);

  structured_block_3d lblock0(&lmesh, size_0, size_1, size_2, true);
  lblock0.put_name("3d_structured_block0", true, true);

  structured_block_3d lblock1(&lmesh, size_0, size_1, size_2, true);
  lblock1.put_name("3d_structured_block1", true, true);

  // Create some jrms contained in block 0.

  lmesh.get_read_write_access();

  index_space_handle& lzone_id_space0 = lblock0.get_zone_id_space(false);
  const ijk_product_structure& lzone_product0 =
    lzone_id_space0.product_structure<ijk_product_structure>();

  index_space_handle& lzone_id_space1 = lblock1.get_zone_id_space(false);
  const ijk_product_structure& lzone_product1 =
    lzone_id_space1.product_structure<ijk_product_structure>();

  pod_index_type lzone_pod;
  scoped_index lzone_id(lzone_id_space0);
  block<scoped_index> lzone_ids(size_1*size_2);
  for(int i=0; i<size_0; ++i)
  {
    lzone_ids.clear();
    for(int j=0; j<size_1; ++j)
    {
      for(int k=0; k<size_2; ++k)
      {
	lzone_product0.ordinal(i, j, k, lzone_pod);
	lzone_id = lzone_pod;
	lzone_ids.push_back(lzone_id);
      }
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

  int ifirst = 0, ilast = size_0 - 1;
  int jfirst = 0, jlast = size_1 - 1;
  
  lzone_ids.clear();
  for(int k=0; k<size_2; ++k)
  {
    lzone_product0.ordinal(ilast, jlast, k, lzone_pod);
    lzone_id = lzone_pod;
    lzone_ids.push_back(lzone_id);
  }

  for(int k=0; k<size_2; ++k)
  {
    lzone_product1.ordinal(ifirst, jfirst, k, lzone_pod);
    lzone_id = lzone_pod;
    lzone_ids.push_back(lzone_id);
  }

  base_space_member ljrm(&lmesh, lzone_ids.base(), lzone_ids.ct(), tern::TRUE, false);
  ljrm.put_name("partial range", true, false);

  // Move to a new version;
  // tests handling of version subposet names by i/o system.

  lmesh.begin_refine_mode(true);
  lmesh.end_refine_mode(true);
  
  poset_path lbase_path = lblock0.path();

  cout << lmesh << endl;

//   // Test the refinement map.

//   cout << endl << "##### Refinement map test ###############" << endl << endl;

//   chart_point_3d lpt(lblock0.index(), -1.0, -1.0, -1.0);

//   chart_point_3d lref_pt;

//   for(double lxcoord= -1.0; lxcoord <= 1.0; lxcoord += 0.5)
//   {
//     lpt.u() = lxcoord;

//     for(double lycoord= -1.0; lycoord <= 1.0; lycoord += 0.5)
//     {
//       lpt.v() = lycoord;

//       for(double lzcoord= -1.0; lzcoord <= 1.0; lzcoord += 0.5)
//       {
//         lpt.w() = lzcoord;
//         lblock0.refine_point_pa(lpt, lref_pt);
//         cout << "point: " << lpt << "\trefined point: " << lref_pt;
//         lblock0.unrefine_point_pa(lref_pt, lpt);
//         cout << "\tunrefined point: " << lpt << endl;
//         cout << endl;
//       }
//     }
//   }

//   cout << endl << "##### End refinement map test ###############" << endl << endl;

  // Make coordinate sec_rep_space.

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
    sec_at0::standard_host(lns, lbase_path, "", "", "", false);

  sec_at0 lprop(&lprop_space);
  lprop.get_read_write_access();
  lprop.put_name("property", true, false);

  sec_at0::fiber_type::volatile_type lfiber = 2.0;
  lprop = lfiber;

  cout << lprop_space << endl << endl;

  // Clean-up.

  lblock0.detach_from_state();
  lblock1.detach_from_state();
  ljrm.detach_from_state();
  lmesh.release_access();
  lcoords.detach_from_state();
  lprop.release_access();
  lprop.detach_from_state();

  // Output namespace.

  cout << lns << endl;

  storage_agent sa(filename + ".hdf");
  sa.put_member_record_buffer_ub(25);
  sa.write_entire(lns);

  return 0;
}
