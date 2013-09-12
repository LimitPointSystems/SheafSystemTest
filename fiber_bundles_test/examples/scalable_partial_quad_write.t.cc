
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

/// @example examples/scalable_partial_quad_write.t.cc
/// Test driver for test.

#include "abstract_poset_member.h"
#include "biorder_iterator.h"
#include "block_decomposition_iterator.h"
#include "unstructured_block_builder.h"
#include "poset.h"
#include "poset_bounds_descriptor.h"
#include "poset_path.h"
#include "postorder_iterator.h"
#include "ragged_array.h"
#include "fiber_bundles_namespace.h"
#include "assert_contract.h"
#include "std_string.h"
#include "std_strstream.h"
#include "storage_agent.h"
#include "stop_watch.h"
#include "subposet_member_iterator.h"
#include "total_poset_member.h"
#include "unstructured_block.h"

using namespace fiber_bundle;

//
// OBSOLETE: This test driver is obsolete and is only in the repository
// as an example of refinement.  Once another test driver is
// written that uses refinement, this file can be removed.
//

//#define DIAGNOSTIC_OUTPUT

namespace scalable_partial_write
{
typedef int mono_index;

class bi_index
{
public:

  ///
  /// The x-index.
  ///
  mono_index i;

  ///
  /// The y-index.
  ///
  mono_index j;

  ///
  /// Constructor.
  ///
  bi_index(mono_index xi = 0, mono_index xj = 0)
  {
    i = xi;
    j = xj;
  };

  ///
  /// Sum.
  ///
  bi_index operator+(const bi_index& xother) const
  {
    bi_index result(i+xother.i, j+xother.j);
    return result;
  };

  ///
  /// Self-allocated sum.
  ///
  bi_index& operator+=(const bi_index& xother)
  {
    i += xother.i;
    j += xother.j;
    return *this;
  };

};

class bi_index_space
{
public:
  ///
  /// Number in the i factor.
  ///
  mono_index i_ub;

  ///
  /// Number in the j factor.
  ///
  mono_index j_ub;

  ///
  /// Number in the space.
  ///
  mono_index size;

  ///
  /// Creates an instance with bound (0,0).
  ///
  bi_index_space()
  {
    put_bound(0, 0);
  };

  ///
  /// Creates an instance with bound (xct, yct).
  ///
  bi_index_space(mono_index xct, mono_index yct)
  {
    put_bound(xct, yct);
  };

  ///
  /// Sets i_ub = xct and j_ub = yct and recomputes size.
  ///
  void put_bound(mono_index xct = 0, mono_index yct = 0)
  {
    i_ub = xct;
    j_ub = yct;
    size = xct*yct;
  };

  ///
  /// Conversion from mono_index; interpreted as square.
  ///
  bi_index_space(mono_index xl)
  {
    put_bound(xl, xl);
  };

  ///
  /// Sum.
  ///
  bi_index_space operator+(const bi_index_space& xother) const
  {
    bi_index_space result(i_ub+xother.i_ub, j_ub+xother.j_ub);
    return result;
  };

  ///
  /// Cartesian product.
  ///
  bi_index_space operator*(const bi_index_space& xother) const
  {
    bi_index_space result(i_ub*xother.i_ub, j_ub*xother.j_ub);
    return result;
  };

  ///
  /// True if xindex is in this space.
  ///
  bool contains(const bi_index& xindex) const
  {
    bool result =
      (0 <= xindex.i) && (xindex.i < i_ub) &&
      (0 <= xindex.j) && (xindex.j < j_ub);
    return result;
  };

  ///
  /// True if xindex is in this space.
  ///
  bool contains(const mono_index& xindex) const
  {
    return (0 <= xindex) && (xindex < size);
  };

  ///
  /// Converts xindex to a mono_index using row-major ordering.
  ///
  mono_index to_row_major_offset(const bi_index& xindex) const
  {
    return j_ub*xindex.i+ xindex.j;
  };

  ///
  /// Converts xindex to a bi_index using row-major ordering.
  ///
  bi_index from_row_major_offset(const mono_index& xindex) const
  {
    bi_index result(xindex/j_ub, xindex%j_ub);
    return result;
  };

  ///
  /// Create a ragged array containing the row major offsets
  /// of the neighbors of each index in the index space.
  ///
  ragged_array<mono_index>* neighbor_list()
  {
    // Preconditions:

    // Body:

    // Create the block neighborhoods.

    bi_index lblock_id, lnbr_id;
    ragged_array<mono_index>* result = new ragged_array<mono_index>(9*size);

    for(lblock_id.i=0; lblock_id.i<i_ub; lblock_id.i++)
    {
      for(lblock_id.j=0; lblock_id.j<j_ub; lblock_id.j++)
      {

        // Make a list of the members in the neighborhood of
        // the current member, including the current member itself.

        bi_index ldelta;
        for(ldelta.i=-1; ldelta.i<2; ldelta.i++)
        {
          for(ldelta.j=-1; ldelta.j<2; ldelta.j++)
          {
            lnbr_id = lblock_id + ldelta;
            if(contains(lnbr_id))
            {
              result->push_back(to_row_major_offset(lnbr_id));
            }
          }
        }

        if(result->row_ct() < size)
        {
          // Move the the next row.

          result->new_back_row();
        }

      }
    }

    // Postconditions:

    ensure(result != 0);
    ensure(result->row_ct() == size);

    // Exit:

    return result;
  };

};



class multiblock_mesh_descriptor
{
public:

  ///
  /// Index space of elements within a block.
  ///
  bi_index_space block_element_index_space;

  ///
  /// Index space of vertices within a block.
  ///
  bi_index_space block_vertex_index_space;

  ///
  /// Index space of blocks within the mesh.
  ///
  bi_index_space block_index_space;

  ///
  /// Index space of elements within the mesh.
  ///
  bi_index_space element_index_space;

  ///
  /// Index space of vertices within the mesh.
  ///
  bi_index_space vertex_index_space;

  ///
  /// Default constructor.
  ///
  multiblock_mesh_descriptor()
  {
    // All index spaces default to (0,0);
  };

  ///
  /// Constructor.
  ///
  multiblock_mesh_descriptor(mono_index xblock_element_xct,
                             mono_index xblock_element_yct,
                             mono_index xblock_xct,
                             mono_index xblock_yct)
  {
    block_element_index_space.put_bound(xblock_element_xct, xblock_element_yct);
    block_vertex_index_space = block_element_index_space + 1;
    block_index_space.put_bound(xblock_xct, xblock_yct);
    element_index_space = block_element_index_space*block_index_space;
    vertex_index_space = element_index_space + 1;
  };

  ///
  /// Converts element or vertex index xindex from block relative to mesh relative.
  ///
  bi_index mesh_relative_index(bi_index xblock_id, bi_index xblock_rel_id) const
  {
    bi_index result;
    result.i = block_element_index_space.i_ub*xblock_id.i + xblock_rel_id.i;
    result.j = block_element_index_space.j_ub*xblock_id.j + xblock_rel_id.j;
    return result;
  };

};


class connectivity
{
public:

  ///
  /// The mesh descriptor.
  ///
  multiblock_mesh_descriptor mesh;

  ///
  /// The block index.
  ///
  bi_index block_id;

  ///
  /// The index of the vertex in the LLH corner of this block.
  ///
  bi_index llh_id;

  ///
  /// Upper bound on array of node ids.
  ///
  mono_index node_ids_ub;

  ///
  /// Array of node ids.
  ///
  mono_index* node_ids;

  //
  // The quads and the blocks are indexed in the following order:
  //
  //     +-----+-----+
  //     |     |     |  y
  //     |     |     |
  //     |  2  |  4  |  ^
  //     |     |     |  |
  //     |     |     |  |
  //     +-----+-----+  +----> x
  //     |     |     |
  //     |     |     |
  //     |  1  |  3  |
  //     |     |     |
  //     |     |     |
  //     +-----+-----+
  //

  ///
  /// The global vertex id of the vertex with block relative bi_index xrel_id.
  ///
  mono_index vertex_id(const bi_index& xrel_id) const
  {
    mono_index result;

    // Preconditions:

    require(mesh.block_vertex_index_space.contains(xrel_id));

    // Body:

    result = mesh.vertex_index_space.to_row_major_offset(xrel_id+llh_id);

    // Postconditions:

    ensure(mesh.vertex_index_space.contains(result));

    // Exit:

    return result;
  }

  ///
  /// Creates connectivity for the block of quads with index xblock_id
  /// in the mesh described by xmesh.
  ///
  connectivity(const multiblock_mesh_descriptor& xmesh)
  {
    mesh = xmesh;
    node_ids_ub = 4*mesh.block_element_index_space.size;
    node_ids = new mono_index[node_ids_ub];
  };

  ///
  /// Destructor.
  ///
  ~connectivity()
  {
    delete [] node_ids;
  }

  ///
  /// Creates the connectivity for block xblock_id.
  ///
  void make_block(const bi_index& xblock_id)
  {
    block_id = xblock_id;

    bi_index zero;
    llh_id = mesh.mesh_relative_index(block_id, zero);

    bi_index_space lele_space = mesh.block_element_index_space;

    mono_index node_ct = 0;
    bi_index lele_id;
    for(lele_id.i = 0; lele_id.i < lele_space.i_ub; lele_id.i++)
    {
      for(lele_id.j = 0; lele_id.j < lele_space.j_ub; lele_id.j++)
      {
        // Each bi_index value is the lower-left-hand node in a quad .
        // When drawing a diagram, note that x is associated with i
        // and y is associated with j.

        // Connectivity follows right-hand rule (ccw) starting
        // in llh corner of quad.

        bi_index tmp_id(lele_id); // (i,j)
        node_ids[node_ct++] = vertex_id(tmp_id);
        tmp_id.i++; // (i+1,j)
        node_ids[node_ct++] = vertex_id(tmp_id);
        tmp_id.j++; // (i+1,j+1)
        node_ids[node_ct++] = vertex_id(tmp_id);
        tmp_id.i--; // (i,j_1)
        node_ids[node_ct++] = vertex_id(tmp_id);
      }
    }

  };

  ///
  /// Creates the connectivity for block with sequence id xblock_seq_id.
  ///
  void make_block(const mono_index& xblock_seq_id)
  {
    const bi_index_space& lblock_index_space = mesh.block_index_space;
    bi_index lblock_id = lblock_index_space.from_row_major_offset(xblock_seq_id);
    make_block(lblock_id);
  };
};

///
/// Refines the block member specified by xmesh and xindex using
/// the connectivity in xconn and writes it to disl using xsa.
///
void
process_block(base_space_poset* xmesh,
              abstract_poset_member& xblock,
              connectivity& xconn,
              storage_agent& xsa);
///
/// Deletes the down set of the block "in the center" of the
/// neighborhood specified by xindex and syncronizes xsa.
///
void
delete_neighborhood_center(base_space_poset* xmesh,
                           abstract_poset_member& xnbrhd,
                           storage_agent& xsa);

///
/// Iterates over the blocks in the block decomposition, refining each
/// and writing it to disk.
///
void
process_block_decomposition(const multiblock_mesh_descriptor& xmesh_desc,
                            base_space_poset* xmesh,
                            storage_agent& xsa);
}
; // end namespace

using namespace scalable_partial_write;


///
void
scalable_partial_write::
delete_neighborhood_center(base_space_poset* xmesh,
                           abstract_poset_member& xnbrhd,
                           storage_agent& xsa)
{
  // Preconditions:

  require(xmesh != 0);
  require(xmesh->state_is_read_write_accessible());
  require(xmesh->contains_member(&xnbrhd));

  // Body:

  // We are now completely finished with the block
  // "in the center" of the neighborhood xnbrhd,
  // but its external boundary, if any, is still
  // in memory. Delete it.

  string lnbrhd_name = xnbrhd.name();
  string lctr_name(poset_path::block_name(lnbrhd_name));
  total_poset_member lblock(xmesh, lctr_name);
  lblock.delete_down(true);

#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << "after deleting the boundary of block " << lblock.name() << endl;
  cout << *xmesh << endl;
#endif

  lblock.detach_from_state();

  // Postconditions:


  // Exit:

  return;
};



///
void
scalable_partial_write::
process_block(base_space_poset* xmesh,
              abstract_poset_member& xblock,
              connectivity& xconn,
              storage_agent& xsa)
{
  // Preconditions:

  require(xmesh != 0);
  require(xmesh->state_is_read_write_accessible());
  require(xblock.is_jim());
  require(xblock.is_atom());

  // Body:

  // Make the block connectivity.

  xconn.make_block(poset_path::block_id(xblock.name()));

  // Refine the block member; build the block under it.

  poset_path lproto_path("base_space_member_prototypes/quad_complex");
  unstructured_block lblock(xblock);

  int* lcp = xconn.node_ids;
  int lcp_ub = xconn.node_ids_ub;

  lblock.refine(lproto_path,
                lcp,
                lcp_ub,
                true);

  lblock.detach_from_state();

#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << "after refining block " << xblock.name() << endl;
  cout << *xmesh << endl;
  cout << endl << "writing block " << xblock.name() << " to file." << endl;
#endif

  // Write the block;

  poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                      BOTTOM_INDEX,
                                      xblock.index());

  xsa.write(*xmesh,
            lrow_bounds,
            poset_bounds_descriptor::BOTTOM_TOP,
            storage_agent::RELEASE_ALL);

  assertion(xmesh->state_is_read_write_accessible());

  // Delete the interior of the block.

  xblock.delete_down();

#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << "after deleting the interior of block " << xblock.name() << endl;
  cout << " pool size= " << xmesh->member_index_ub() << endl;
  cout << *xmesh << endl;
#endif

  assertion(xmesh->state_is_read_write_accessible());

  // Postconditions:

  // Exit:

  return;
};


///
void
scalable_partial_write::
process_block_decomposition(const multiblock_mesh_descriptor& xmesh_desc,
                            base_space_poset* xmesh,
                            storage_agent& xsa)
{
  // Preconditions:

  require(xmesh != 0);
  require(xmesh->state_is_read_write_accessible());

  // Body:

  stop_watch lblock_timer;
  stop_watch ldelete_timer;

  connectivity lconn(xmesh_desc);

  block_decomposition_iterator lnbrhd_itr(xmesh->top());
  while(!lnbrhd_itr.is_done())
  {
    switch(lnbrhd_itr.action())
    {
    case block_decomposition_iterator::BLOCK_ACTION:

      // This is a block member; build the block and write it to disk.

      lblock_timer.start();
      process_block(xmesh, lnbrhd_itr.item(), lconn, xsa);
      lblock_timer.stop();
      break;

    case block_decomposition_iterator::NEIGHBORHOOD_ACTION:

      // This is a neighborhood member. We're finished with the
      // member "in the center" of the neighborhood, delete its
      // entire strict down set. (Want to keep the block member
      // itself for the tabel of contents.)

      ldelete_timer.start();
      delete_neighborhood_center(xmesh, lnbrhd_itr.item(), xsa);
      ldelete_timer.stop();
      break;
    }
    lnbrhd_itr.next();
  }

  cout << " block time: " << lblock_timer.cumulative_time()
  << " delete time: " << ldelete_timer.cumulative_time()
  << endl;

  // Postconditions:

  // Exit:

  return;
};


///
int
main(int argc, char* argv[])
{

  // Body:

  // Command line processing:

  mono_index lblock_element_i_ub  = argc > 1 ? atoi(argv[1]) : 2;
  mono_index lblock_element_j_ub  = argc > 2 ? atoi(argv[2]) : 2;
  mono_index lblock_i_ub          = argc > 3 ? atoi(argv[3]) : 2;
  mono_index lblock_j_ub          = argc > 4 ? atoi(argv[4]) : 2;

  multiblock_mesh_descriptor
  mesh_desc(lblock_element_i_ub, lblock_element_j_ub, lblock_i_ub, lblock_j_ub);

  // Create the name space.

  string dash("-");
  string lns_name("scalable_partial_write");
  lns_name += dash + (argc > 1 ? argv[1] : "1");
  lns_name += dash + (argc > 2 ? argv[2] : "1");
  lns_name += dash + (argc > 3 ? argv[3] : "1");
  lns_name += dash + (argc > 4 ? argv[4] : "1");
  fiber_bundles_namespace* ns = new fiber_bundles_namespace(lns_name);

  ns->get_read_write_access();

  // Initialize the storage agent; opens the file.

  storage_agent sa(lns_name + ".hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(64);
  sa.put_dof_tuple_record_buffer_ub(15);

  // Create mesh poset

  base_space_poset* mesh =
    &ns->new_base_space<unstructured_block>("multiblock_quad_mesh", "", "", 2, true);

  // Write the name space itself.
  // In the current implementation, the namespace poset must be the first poset written
  // and no members can be added or removed from it until the file is closed.

  sa.write(*ns);

  mesh->get_read_write_access();

  // Create the block decomposition.

  bi_index_space lblock_space = mesh_desc.block_index_space;
  block<int> lblock_ids(lblock_space.size);
  lblock_ids.set_ct(lblock_space.size);

  for(int i=0; i<lblock_ids.ct(); i++)
  {
    lblock_ids[i] = i;
  }
  ragged_array<int>* lblock_nbrs = lblock_space.neighbor_list();
  unstructured_block_builder::
  build_block_decomposition(mesh,
                            lblock_ids,
                            2,
                            "base_space_member_prototypes/quad_complex",
                            *lblock_nbrs,
                            true);

  delete lblock_nbrs;

  // Create and write down set of each block.

  process_block_decomposition(mesh_desc, mesh, sa);

  // Releasing write access sets the poset is_modified flag.
  // If poset is_modfied when write_remainder is invoked,
  // the poset will be written out again, so release write access
  // now so that write_toc is the last write of the mesh.

  mesh->release_access();
  mesh->get_read_access();

  // Write table of contents of the mesh;

  sa.write_toc(*mesh, mesh->subposet_id("__blocks"));

  mesh->release_access();

  // Write the remainder of the name space.

  sa.write_remainder(*ns);

  delete ns;

  // Postconditions:

  // Exit:

  return 0;
}
