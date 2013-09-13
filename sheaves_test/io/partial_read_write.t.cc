
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

/// @example io/partial_read_write.t.cc
/// Test driver for test.

#include "assert_contract.h"
#include "index_iterator.h"
#include "poset.h"
#include "poset_bounds_descriptor.h"
#include "namespace_poset.h"
#include "storage_agent.h"


poset* mesh;

///
int
main(int argc, char* argv[])
{
  // Preconditions:

  require(unexecutable("partial_write.t.hdf exists"));

  // Body:

  // Open the input file.

  storage_agent sa_in("partial_write.t.hdf", sheaf_file::READ_ONLY, false);
  sa_in.put_member_record_buffer_ub(15);

  // Open the output file.

  storage_agent sa_out("partial_read_write.t.hdf");
  sa_out.put_member_record_buffer_ub(15);

  // Read the namespace poset itself;
  // need write access in order to read it.

  namespace_poset ns("partial_write.t");
  ns.get_read_write_access();
  sa_in.read(ns);

  // Write the name space itself.
  // In the current implementation, the namespace poset must be the first poset written
  // and no members can be added or removed from it until the file is closed.

  sa_out.write(ns);

  // Attach a poset handle to the mesh poset

  poset mesh(&ns, "polyline");

  // Read the mesh table of contents.

  sa_in.read_toc(mesh);

  // Try to get a handle to the block decomposition.

  mesh.get_read_write_access();

  cout << mesh << endl;

  subposet lblocks_sp(&mesh, "__blocks");
  if(!lblocks_sp.is_attached())
  {
    post_fatal_error_message("Mesh does not contain blocks subposet.");
  }

  // Read the down set of each member of the block decomposition.

  index_iterator itr = lblocks_sp.indexed_member_iterator();
  while(!itr.is_done())
  {
    poset_bounds_descriptor lin_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                       BOTTOM_INDEX,
                                       itr.item());
    cout << "block mbr id: " << itr.item() << endl;

    sa_in.read(mesh, lin_bounds);

    cout << mesh << endl;

    // Create some new members.

    total_poset_member lmbr1, lmbr2;
    total_poset_member lblock(&mesh, itr.item());
    if(lblock.name() == "__block_0")
    {
      lmbr1.attach_to_state(&mesh, "edge_0");
      lmbr2.attach_to_state(&mesh, "edge_1");
      lmbr1.l_join_sa(&lmbr2);
      lmbr1.put_name("chunk_0", true, false);

      lmbr1.attach_to_state(&mesh, "edge_2");
      lmbr2.attach_to_state(&mesh, "edge_3");
      lmbr1.l_join_sa(&lmbr2);
      lmbr1.put_name("chunk_1", true, false);
    }
    else
    {
      lmbr1.attach_to_state(&mesh, "edge_4");
      lmbr2.attach_to_state(&mesh, "edge_5");
      lmbr1.l_join_sa(&lmbr2);
      lmbr1.put_name("chunk_2", true, false);

      lmbr1.attach_to_state(&mesh, "edge_6");
      lmbr2.attach_to_state(&mesh, "edge_7");
      lmbr1.l_join_sa(&lmbr2);
      lmbr1.put_name("chunk_3", true, false);
    }

    lmbr1.detach_from_state();
    lmbr2.detach_from_state();

    cout << mesh << endl;

    // Write the block to the output file.

    poset_bounds_descriptor
    lout_bounds(poset_bounds_descriptor::MEMBER_MEMBER, BOTTOM_INDEX, itr.item());

    sa_out.write(mesh,
                 lout_bounds,
                 poset_bounds_descriptor::BOTTOM_TOP,
                 storage_agent::RELEASE_ALL);

    // Delete the block, except for its boundary.

    lblock.delete_down();
    lblock.detach_from_state();

    cout << mesh << endl;

    // Synchronize the storage agents with the deletion.

    sa_in.sync_with(mesh);
    sa_out.sync_with(mesh);

    itr.next();
  }

  // Releasing write access sets the poset is_modified flag.
  // If poset is_modfied when write_remainder is invoked,
  // the poset will be written out again, so release write access
  // now so that write_toc is the last write of the mesh.

  mesh.release_access();
  mesh.get_read_access();

  // Write table of contents of the mesh;

  sa_out.write_toc(mesh, lblocks_sp.index());

  lblocks_sp.detach_from_state();
  mesh.release_access();
  mesh.detach_from_state();

  // Read the remainder of the name space.

  sa_in.read_remainder(ns);

  // Write the remainder of the name space.

  sa_out.write_remainder(ns);

  // Postconditions:

  // Exit:

  return 0;
}
