
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

/// @example io/read_index.t.cc
/// Test driver for storage_agent::read_index().

#include "ComLimitPoint/sheaf/index_iterator.h"
#include "ComLimitPoint/sheaf/poset.h"
#include "poset_bounds_descriptor.h"
#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/storage_agent.h"


poset* mesh;

///
int
main(int argc, char* argv[])
{
  string filename;

  // Command line processing:

  if (argc > 1)
  {
    filename = argv[1];
  }
  else
  {
    filename = "write_row_decomposition.t.hdf";
  }

  // Preconditions:

  require(!filename.empty());

  // Body:

  // Initialize the storage agent; opens the file.

  storage_agent sa(filename, sheaf_file::READ_ONLY, false);
  sa.put_member_record_buffer_ub(15);

  // Read the namespace poset itself;
  // need write access in order to read it.

  namespace_poset ns("test");
  ns.get_read_write_access();
  sa.read(ns);

  // Attach a poset handle to the mesh poset

  poset mesh(&ns, "polyline");

  // Read the mesh index.

  sa.read_index(mesh);

  // Output to text.

  mesh.get_read_access();

  cout << mesh << endl;

  mesh.detach_from_state();

  // Postconditions:

  // Exit:

  return 0;
}
