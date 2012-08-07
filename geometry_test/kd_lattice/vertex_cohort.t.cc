// $RCSfile: vertex_cohort.t.cc,v $ $Revision: 1.2 $ $Date: 2011/10/15 07:04:59 $

//
// Copyright (c) 2010 Limit Point Systems, Inc.
//

/// @example kd_lattice/vertex_cohort.t.cc
/// Unit test driver for class vertex_cohort.

#include "base_space_member_prototype.h"
#include "base_space_poset.h"
#include "cohort.h"
#include "fiber_bundles_namespace.h"
#include "std_iostream.h"
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

  lbase.get_read_write_access();
  
  cohort::auto_name_members() = true;  
  cohort::auto_output_cts() = true;

  cout << "+++++++++++++++++++++++++++++++++" << endl;
  cout << " Test class vertex_structure_set:" << endl;
  cout << "+++++++++++++++++++++++++++++++++" << endl;

  lns.base_space_member_prototypes_poset().get_read_access();
  lbase.begin_jim_edit_mode(true);

  vertex_cohort vertices(lbase, "vertices");

  // Create a vertex.
  // End_jim_edit_mode(true, ...) will 
  // link new member to top and bottom.

  scoped_index lid = vertices.new_member();

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Delete (inactivate) a vertex.

  lbase.begin_jim_edit_mode(true);

  lbase.delete_link(lbase.top().index(), lid);
  vertices.delete_member(lid);

  lbase.end_jim_edit_mode(true, true);
  
  cout << lbase << endl;

  // Reactivate a vertex.

  lbase.begin_jim_edit_mode(true);

  lid = vertices.new_member();

  lbase.end_jim_edit_mode(true, true);
  lns.base_space_member_prototypes_poset().release_access();
  
  cout << lbase << endl;

  return 0;
}
