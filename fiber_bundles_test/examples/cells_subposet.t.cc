
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

/// @example examples/cells_subposet.t.cc
/// Simple test driver for cells subposet.

#include "fiber_bundles_namespace.h"
#include "unstructured_block.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "std_string.h"
#include "std_sstream.h"
#include "storage_agent.h"
#include "subposet.h"
#include "subposet_member_iterator.h"

using namespace std;
using namespace fiber_bundle;

namespace
{

void
make_names(base_space_poset& xbase_space, int xd, const string& xroot)
{
  base_space_member lmbr;

  subposet& lsp = xbase_space.d_cells(xd);
  subposet_member_iterator* litr = lsp.member_iterator();
  size_type i = 0;
  while(!litr->is_done())
  {
    //cout << litr->index() << " : " << litr->index().internal_pod() << endl;
    lmbr.attach_to_state(&xbase_space, litr->index());

    stringstream lstr;
    lstr << xroot << "_" << i;
    lmbr.put_name(lstr.str(), true, true);
    i++;

    litr->next();
  }

  lmbr.detach_from_state();

  delete litr;

  return;
}

void
test(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create a base space.

  const string lbase_name("cells_cube_base_space");

  base_space_poset* lbase_space =
    &xns.new_base_space<unstructured_block>(lbase_name, "", "", 3, true);

  lbase_space->get_read_write_access();

  // Create a block of 6 quads which cover the surface of a cube

  const size_type lquad_node_id_ct = 24;
  const pod_index_type lquad_node_ids[24] =
  {
    0, 3, 2, 1,
    4, 5, 6, 7,
    0, 4, 7, 3,
    1, 2, 6, 5,
    0, 1, 5, 4,
    3, 7, 6, 2
  };

  poset_path lquad_proto_path(unstructured_block::prototypes_poset_name(),
                              "quad_nodes");

  unstructured_block lquad_block(lbase_space,
                                 lquad_proto_path,
                                 lquad_node_ids,
                                 lquad_node_id_ct,
                                 true);

  lquad_block.put_name("quad_block", true, false);

  // Give the quads names.

  make_names(*lbase_space, 2, "quad");

  // Give the vertices names.

  make_names(*lbase_space, 0, "vertex");

  //============================================================================

  // Create the coordinates section space.

  poset_path lbase_path = lbase_space->top().path();
  poset_path lcoords_path = "coordinates_space";
  poset_path lrep_path = "sec_rep_descriptors/vertex_cells_dlinear";

  //cout << endl;
  //cout << "lbase_path   = " << lbase_path << endl;
  //cout << "lcoords_path = " << lcoords_path << endl;
  //cout << "lrep_path    = " << lrep_path << endl;
  //cout << endl;

  sec_at1_space* lcoords_space = 
    &(xns.new_section_space<sec_e3>(lcoords_path, lbase_path, lrep_path, true));

  lcoords_space->get_read_write_access();

  // Create a coordinates section.

  sec_e3 lcoords(lcoords_space);
  lcoords.put_name("coordinates", true, false);

  //============================================================================

  // Add the coordinates to the coordinates section.
 
  const int lcoords_ct = 24;
  const double lcoords_array[24] =
  {
    0, 0, 0,
    1, 0, 0,
    1, 1, 0,
    0, 1, 0,
    0, 0, 1,
    1, 0, 1,
    1, 1, 1,
    0, 1, 1
  };

  lcoords.put_dof_tuple(lcoords_array, lcoords_ct*sizeof(double));

  //============================================================================

  // Create a block of 1 hex element which is the interior of
  // the cube.

  const size_type lhex_node_id_ct = 8;
//   const pod_index_type lhex_node_ids[8] =
//   {
//     0, 3, 2, 1,
//     4, 5, 6, 7
//   };

  poset_path lhex_proto_path(unstructured_block::prototypes_poset_name(),
                            "hex_nodes");

  unstructured_block lhex_block(lbase_space,
                                lhex_proto_path,
                                lquad_node_ids,
                                lhex_node_id_ct,
                                true);

  lhex_block.put_name("hex_block", true, false);

  // Give the hex a name.

  make_names(*lbase_space, 3, "hex");

  //============================================================================

  // Test the "cells" subposet.

  cout << endl;
  cout << "Cells subposet members:" << endl;
  cout << endl;

  base_space_member lmbr;
  subposet& lcells_sp = lbase_space->cells();
  subposet_member_iterator* litr = lcells_sp.member_iterator();
  while(!litr->is_done())
  {
    //cout << litr->index() << " : " << litr->index().internal_pod() << endl;
    lmbr.attach_to_state(lbase_space, litr->index());
    cout << setw(8) << litr->index().internal_pod()
         << "  :  " << lmbr.name() << endl;
    litr->next();
  }

  cout << endl;

  lmbr.detach_from_state();

  delete litr;

  //============================================================================

  cout << *lbase_space << endl;
  cout << *lcoords_space << endl;

  // Cleanup.

  lcoords.detach_from_state();
  lcoords_space->release_access();
  lquad_block.detach_from_state();
  lhex_block.detach_from_state();
  lbase_space->release_access();

  //============================================================================

  // Postconditions:

  // Exit:

  return;

}


} // end namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  const string lfilename = filename_from_cmdline(xargv[0]);

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  test(lns);

  //cout << lns << endl;

  storage_agent sa(lfilename + ".hdf");
  sa.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
