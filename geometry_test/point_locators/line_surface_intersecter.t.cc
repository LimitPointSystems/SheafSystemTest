

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example point_locators/line_surface_intersecter.t.cc
/// Test driver for line_surface_intersecter

#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "line_surface_intersecter.h"
#include "triangle_connectivity.h"
#include "scoped_index.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "std_string.h"
#include "zone_nodes_block.h"

#include "std_iomanip.h"
#include "std_iostream.h"

using namespace geometry;

void
make_trimesh(fiber_bundles_namespace* xns, size_type xi_size, size_type xj_size)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());
  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  base_space_poset* lmesh =
    &xns->new_base_space<zone_nodes_block>("trimesh_space",
					   "",
					   "",
					   2,
					   true);
  lmesh->get_read_write_access();

  // Make triangle connectivity.

  triangle_connectivity lconn(xi_size, xj_size);

  // Make a trimesh block.

  zone_nodes_block lblock1(*lmesh, lconn, true);
  lblock1.put_name("trimesh1", true, false);
  lblock1.detach_from_state();

  // Make a second trimesh block.

  zone_nodes_block lblock2(*lmesh, lconn, true);
  lblock2.put_name("trimesh2", true, false);
  lblock2.detach_from_state();

  // Make a third trimesh block.

  zone_nodes_block lblock3(*lmesh, lconn, true);
  lblock3.put_name("trimesh3", true, false);
  lblock3.detach_from_state();

  cout << *lmesh << endl;
  lmesh->release_access();

}

sec_e3&
make_coordinates(fiber_bundles_namespace* xns, size_type xi_size, size_type xj_size)
{
  poset_path lsection_space_path("coordinates_space");
  poset_path lbase_space_path("trimesh_space/top");
  
  sec_at1_space& lcoords_space = xns->new_section_space<sec_e3>(lsection_space_path, lbase_space_path);
  
  sec_e3& result = *(new sec_e3(&lcoords_space));
  result.get_read_write_access();
  
  e3_lite lfiber;
  
  pod_index_type lv_id = 0;

  lfiber[2] = 0.0;
  for(pod_index_type i=0; i<=xi_size; ++i)
  {
    lfiber[0] = i;
    for(pod_index_type j=0; j<=xj_size; ++j)
    {
      lfiber[1] = j;

      result.put_fiber(lv_id++, lfiber);
    }
  }

  lfiber[2] = 1.0;
  for(pod_index_type i=0; i<=xi_size; ++i)
  {
    lfiber[0] = i;
    for(pod_index_type j=0; j<=xj_size; ++j)
    {
      lfiber[1] = j;

      result.put_fiber(lv_id++, lfiber);
    }
  }

  for(pod_index_type i=0; i<=xi_size; ++i)
  {
    lfiber[0] = i;
    for(pod_index_type j=0; j<=xj_size; ++j)
    {
      // Fold surface back and forth between extremes in y.
      lfiber[1] = (j%2 == 0) ? 0 : xj_size;
      lfiber[2] = static_cast<sec_vd_dof_type>(j+1)*0.25;
      result.put_fiber(lv_id++, lfiber);
    }
  }


  cout << lcoords_space << endl;
  result.release_access();
    
  return result;
  
}

int
main(int xargc, char* xargv[])
{
  // Command line processing:

  size_type i_size = (xargc > 1) ? atoi(xargv[1]): 1;
  size_type j_size = (xargc > 2) ? atoi(xargv[2]): 2;

  // Preconditions:

  require(i_size > 0);
  require(j_size > 0);

  // Body:

  fiber_bundles_namespace lns("line_surface_intersecter.t.cc");

  lns.get_read_write_access();

  make_trimesh(&lns, i_size, j_size);
  sec_e3& lcoords = make_coordinates(&lns, i_size, j_size);

  block<size_type> lbnds(3);
  lbnds.push_back(10);
  lbnds.push_back(10);
  lbnds.push_back(1);

  //$$ISSUE: Deleting the line_surface_intersecter created here
  //         fails an assertion in the destructor for eval_iterator
  //         on the line with " _schema_anchor->detach_from_state();".
  //         So, we avoid this problem by creating it on the heap
  //         and purposely not deleting it. This is OK, in a test
  //         but the issue needs to be resolved.
  
  //line_surface_intersecter lintersecter(lcoords, lbnds);
  line_surface_intersecter* lintersecter =
    new line_surface_intersecter(lcoords, lbnds);
  
  e3_lite lp0(0.5, 1.5, 1.0);
  e3_lite lp1(0.5, 1.5, -1.0);
  
  typedef line_surface_intersecter::intersection_set_type set_type;
  set_type lset;
  
  //lintersecter.intersect(lp0, lp1, lset);
  lintersecter->intersect(lp0, lp1, lset);
  
  for(set_type::iterator litr = lset.begin(); litr != lset.end(); ++litr)
  {
    cout << "intersection at z= " << litr->first
	 << " in surface " << litr->second
	 <<endl;
  }
  cout << endl;
  
  
  e3_lite lp2(0.5, 1.0, 1.0);
  e3_lite lp3(0.5, 1.0, -1.0);

  //lintersecter.intersect(lp2, lp3, lset);
  lintersecter->intersect(lp2, lp3, lset);
  
  for(set_type::iterator litr = lset.begin(); litr != lset.end(); ++litr)
  {
    cout << "intersection at z= " << litr->first
	 << " in surface " << litr->second
	 <<endl;
  }

  //delete lintersecter;

  //============================================================================
  // Miscellaneous test for code coverage:
  //============================================================================

  //line_surface_intersecter(const line_surface_intersecter& xother);
  //  not_implemented

  //line_surface_intersecter lintersecter_copy(*lintersecter);

  //const sec_e3& coords() const;

  const sec_e3& lcoords2 = lintersecter->coords();

  //virtual bool is_ancestor_of(const any *other) const;

  bool lis_ancestor_of =  lintersecter->is_ancestor_of(lintersecter);
  cout << "lis_ancestor_of = " << boolalpha << lis_ancestor_of << endl;

  //line_surface_intersecter lintersecter2;
  //  protected

  //line_surface_intersecter& operator=(const line_surface_intersecter& xother);
  //  not_implemented

  //ostream& operator<< (ostream &os, const line_surface_intersecter& xp);

  cout << *lintersecter << endl;

  //============================================================================

  // Postconditions:

  // Exit:

  return 0;
}
