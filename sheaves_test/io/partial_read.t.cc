
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

/// @example io/partial_read.t.cc
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

  // Initialize the storage agent; opens the file.

  storage_agent sa("partial_write.t.hdf", sheaf_file::READ_ONLY, false);
  sa.put_member_record_buffer_ub(15);

  // Read the namespace poset itself;
  // need write access in order to read it.

  namespace_poset ns("partial_write.t");
  ns.get_read_write_access();
  sa.read(ns);

  // Attach a poset handle to the mesh poset

  poset mesh(&ns, "polyline");

  // Read the mesh table of contents.

  sa.read_toc(mesh);

  // Try to get a handle to the block decomposition.

  mesh.get_read_write_access();

  cout << mesh << endl;

  subposet lblocks_sp(&mesh, "blocks");
  if(!lblocks_sp.is_attached())
  {
    post_fatal_error_message("Mesh does not contain blocks subposet.");
  }

  // Read the down set of each member of the block decomposition.

  index_iterator itr = lblocks_sp.indexed_member_iterator();
  while(!itr.is_done())
  {
    poset_bounds_descriptor
    ldesc(poset_bounds_descriptor::MEMBER_MEMBER, BOTTOM_INDEX, itr.item());

    cout << "block mbr id: " << itr.item() << endl;

    sa.read(mesh, ldesc);

    cout << mesh << endl;

    itr.next();
  }

  lblocks_sp.detach_from_state();
  mesh.release_access();
  mesh.get_read_access();

  cout << mesh << endl;

  mesh.detach_from_state();

  // Postconditions:

  // Exit:

  return 0;
}
