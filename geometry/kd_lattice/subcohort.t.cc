// $RCSfile: subcohort.t.cc,v $ $Revision: 1.2 $ $Date: 2011/10/15 07:04:59 $

//
// Copyright (c) 2010 Limit Point Systems, Inc.
//

/// @example kd_lattice/subcohort.t.cc
/// Unit test driver for class subcohort.

#include "base_space_member_prototype.h"
#include "base_space_poset.h"
#include "block.h"
#include "d_cells_cohort.h"
#include "fiber_bundles_namespace.h"
#include "jim_cohort.h"
#include "std_iostream.h"
#include "subcohort.h"
#include "vertex_cohort.h"

using namespace geometry;
using namespace sheaf;


int main()
{

  fiber_bundles_namespace lns("the_namespace");

  lns.get_read_write_access();

  // Create base space

  base_space_poset& lbase =
    lns.new_base_space<base_space_member_prototype>("the_base_space", "", "",  2, true);

  cohort::auto_name_members() = true;
  cohort::auto_output_cts() = true;

  cout << "+++++++++++++++++++++++++++++++++" << endl;
  cout << " Test class sub_cohort:" << endl;
  cout << " with class vertex_cohort:" << endl;
  cout << "+++++++++++++++++++++++++++++++++" << endl;

  lns.base_space_member_prototypes_poset().get_read_access();
  lbase.begin_jim_edit_mode(true);

  vertex_cohort vertices(lbase, "vertices");
  subcohort points(lbase, "points", vertices);
  
  // Create a point.
  // End_jim_edit_mode(true, ...) will 
  // link new member to top and bottom.

  const int PT_CT = 5;
  block<scoped_index> lpoints(PT_CT);
  lpoints.set_ct(PT_CT);
  
  for(int i=0; i<PT_CT; ++i)
  {
    lpoints[i] = points.new_member();
  }
  

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Delete (inactivate) a point.

  lbase.begin_jim_edit_mode(true);

  for(int i=0; i<PT_CT; ++i)
  {
    lbase.delete_link(lbase.top().index(), lpoints[i]);
    points.delete_member(lpoints[i]);
  }

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Reactivate a point.

  lbase.begin_jim_edit_mode(true);

  for(int i=0; i<PT_CT; ++i)
  {
    lpoints[i] = points.new_member();
  }

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  cout << "+++++++++++++++++++++++++++++++++" << endl;
  cout << " Test class sub_cohort:" << endl;
  cout << " with class d_cells_cohort:" << endl;
  cout << "+++++++++++++++++++++++++++++++++" << endl;

  lbase.begin_jim_edit_mode(true);

  d_cells_cohort segments(lbase, "segments", "segment");
  subcohort line_segments(lbase, "line_segments", segments);

  // Create a line_segment.
  // End_jim_edit_mode(true, ...) will 
  // link new member to top and bottom.

  scoped_index lid = line_segments.new_member();

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Delete (inactivate) a line_segment.

  lbase.begin_jim_edit_mode(true);

  lbase.delete_link(lbase.top().index(), lid);
  lbase.delete_link(lid, lbase.bottom().index());
  line_segments.delete_member(lid);

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Reactivate a line_segment.

  lbase.begin_jim_edit_mode(true);

  lid = line_segments.new_member();

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;


  cout << "+++++++++++++++++++++++++++++++++" << endl;
  cout << " Test class sub_cohort:" << endl;
  cout << " with class jim_cohort:" << endl;
  cout << "+++++++++++++++++++++++++++++++++" << endl;

  lbase.begin_jim_edit_mode(true);

  jim_cohort parts(lbase, "parts", "part");
  subcohort small_parts(lbase, "small_parts", parts);

  // Create a small part.
  // End_jim_edit_mode(true, ...) will 
  // link new member to top and bottom.

  lid = small_parts.new_member();

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Delete (inactivate) a small part.

  lbase.begin_jim_edit_mode(true);

  lbase.delete_link(lbase.top().index(), lid);
  lbase.delete_link(lid, lbase.bottom().index());
  small_parts.delete_member(lid);

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Reactivate a small part.

  lbase.begin_jim_edit_mode(true);

  lid = small_parts.new_member();

  lbase.end_jim_edit_mode(true, true);
  lns.base_space_member_prototypes_poset().release_access();
  
  cout << lbase << endl;



  return 0;
}
