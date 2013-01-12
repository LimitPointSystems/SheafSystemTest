
//
// Copyright (c) 2010 Limit Point Systems, Inc.
//

/// @example kd_lattice/d_cells_cohort.t.cc
/// Unit test driver for class d_cell_cohort.

#include "base_space_member_prototype.h"
#include "base_space_poset.h"
#include "cohort.h"
#include "d_cells_cohort.h"
#include "fiber_bundles_namespace.h"
#include "std_iostream.h"

// #include "fiber_bundles_namespace.impl.h"

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
  cout << " Test class d_cells_cohort:" << endl;
  cout << "+++++++++++++++++++++++++++++++++" << endl;

  lns.base_space_member_prototypes_poset().get_read_access();
  lbase.begin_jim_edit_mode(true);

  d_cells_cohort segments(lbase, "segments", "segment");

  // Create a segment.
  // End_jim_edit_mode(true, ...) will 
  // link new member to top and bottom.

  scoped_index lid = segments.new_member();

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Delete (inactivate) a segment.

  lbase.begin_jim_edit_mode(true);

  lbase.delete_link(lbase.top().index(), lid);
  lbase.delete_link(lid, lbase.bottom().index());
  segments.delete_member(lid);

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Reactivate a segment.

  lbase.begin_jim_edit_mode(true);

  lid = segments.new_member();

  lbase.end_jim_edit_mode(true, true);
  lns.base_space_member_prototypes_poset().release_access();
  
  cout << lbase << endl;

  return 0;
}
