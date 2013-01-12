
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example io/read_index.t.cc
/// Test driver for storage_agent::read_index().

#include "index_iterator.h"
#include "poset.h"
#include "poset_bounds_descriptor.h"
#include "namespace_poset.h"
#include "assert_contract.h"
#include "storage_agent.h"


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
