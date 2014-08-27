
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

/// @example io/scalable_partial_read_write.t.cc
/// Test driver for test.

#include "block_decomposition_iterator.h"
#include "ComLimitPoint/sheaf/index_iterator.h"
#include "ComLimitPoint/sheaf/poset.h"
#include "poset_bounds_descriptor.h"
#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/storage_agent.h"


poset* mesh;

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

namespace scalable_partial_read_write
{
///
/// Refines the block member specified by xmesh and xindex using
/// the connectivity in xconn and writes it to disl using xsa.
///
void
process_block(poset& xmesh,
              abstract_poset_member& xblock,
              storage_agent& xsa_in,
              storage_agent& xsa_out);
///
/// Deletes the down set of the block "in the center" of the
/// neighborhood specified by xindex and syncronizes xsa.
///
void
delete_neighborhood_center(poset& xmesh,
                           abstract_poset_member& xnbrhd,
                           storage_agent& xsa_in,
                           storage_agent& xsa_out);

};


using namespace scalable_partial_read_write;


///
void
scalable_partial_read_write::
process_block(poset& xmesh,
              abstract_poset_member& xblock,
              storage_agent& xsa_in,
              storage_agent& xsa_out)
{
  // Preconditions:


  // Body:

  // Read the down set of the block.

  poset_bounds_descriptor lin_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                     sheaf_constants::BOTTOM_INDEX,
                                     xblock.index());

  xsa_in.read(xmesh, lin_bounds);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "after refining " << xblock.name() << endl;
  cout << xmesh << endl;
#endif

  // Write the block to the output file.

  poset_bounds_descriptor lout_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                      sheaf_constants::BOTTOM_INDEX,
                                      xblock.index());

  xsa_out.write(xmesh,
                lout_bounds,
                poset_bounds_descriptor::BOTTOM_TOP,
                storage_agent::RELEASE_ALL);

  // Delete the block, except for its boundary.

  xblock.delete_down();

#ifdef DIAGNOSTIC_OUTPUT

  cout << "after unrefining " << xblock.name() << endl;
  cout << xmesh << endl;
#endif

  // Postconditions:

  // Exit:

  return;
}


///
void
scalable_partial_read_write::
delete_neighborhood_center(poset& xmesh,
                           abstract_poset_member& xnbrhd,
                           storage_agent& xsa_in,
                           storage_agent& xsa_out)
{
  // Preconditions:

  require(xmesh.state_is_read_write_accessible());
  require(xmesh.contains_member(&xnbrhd));

  // Body:

  // Delete the entire down set of the block "in the center"
  // of the neighborhood xnbrhd.

  string lnbrhd_name = xnbrhd.name();
  string lctr_name(poset_path::block_name(lnbrhd_name));
  total_poset_member lblock(&xmesh, lctr_name);
  lblock.delete_down(true, true);

#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << "after deleting the boundary of block " << lblock.name() << endl;
  cout << xmesh << endl;
#endif

  lblock.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

///
int
main(int argc, char* argv[])
{
  // Preconditions:

  if(argc < 2)
  {
    cout << "usage: scalable_partial_read_write.t <filename>" << endl;
    exit(1);
  }

  // Body:

  // Open the input file.

  string lin_file_name(argv[1]);
  storage_agent sa_in(lin_file_name, sheaf_file::READ_ONLY, false);
  sa_in.put_member_record_buffer_ub(15);

  // Open the output file.

  string lout_file_name("copy_of_" + lin_file_name);
  storage_agent sa_out(lout_file_name);
  sa_out.put_member_record_buffer_ub(15);

  // Read the namespace poset itself;
  // need write access in order to read it.

  namespace_poset ns("scalable_partial_read_write.t");
  ns.get_read_write_access();
  sa_in.read(ns);

  // Write the name space itself.
  // In the current implementation, the namespace poset must be the first poset written
  // and no members can be added or removed from it until the file is closed.

  sa_out.write(ns);

  // Attach a poset handle to the mesh poset

  poset mesh(&ns, "multiblock_quad_mesh");

  // Read the mesh table of contents.

  sa_in.read_toc(mesh);

  mesh.get_read_write_access();

#ifdef DIAGNOSTIC_OUTPUT

  cout << "after reading the mesh toc" << endl;
  cout << mesh << endl;
#endif

  // Read the down set of each member of the block decomposition.

  block_decomposition_iterator lnbrhd_itr(mesh.top());
  while(!lnbrhd_itr.is_done())
  {
    switch(lnbrhd_itr.action())
    {
    case block_decomposition_iterator::BLOCK_ACTION:

      // This is a block member. Read it from the input
      // and write it to the output.

      process_block(mesh, lnbrhd_itr.item(), sa_in, sa_out);
      break;

    case block_decomposition_iterator::NEIGHBORHOOD_ACTION:

      // This is a neighborhood member. We're finished with the
      // member "in the center" of the neighborhood, delete its
      // entire strict down set. (Want to keep the block member
      // itself for the table of contents.)

      delete_neighborhood_center(mesh, lnbrhd_itr.item(), sa_in, sa_out);
      break;
    }
    lnbrhd_itr.next();
  }

  // Releasing write access sets the poset is_modified flag.
  // If poset is_modfied when write_remainder is invoked,
  // the poset will be written out again, so release write access
  // now so that write_toc is the last write of the mesh.

  mesh.release_access();
  mesh.get_read_access();

  // Write table of contents of the mesh;

  sa_out.write_toc(mesh, mesh.subposet_id("__blocks"));

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
