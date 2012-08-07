// scalable_partial_write.t.cc,v 1.1.2.4 2003/04/18 00:40:16

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example io/scalable_partial_hex_write.t.cc
/// Test driver for test.

#include "abstract_poset_member.h"
#include "biorder_iterator.h"
#include "block_decomposition_iterator.h"
#include "block_poset_builder.h"
#include "poset.h"
#include "poset_bounds_descriptor.h"
#include "poset_path.h"
#include "postorder_iterator.h"
#include "ragged_array.h"
#include "sheaves_namespace.h"
#include "std_string.h"
#include "std_strstream.h"
#include "storage_agent.h"
#include "subposet_member_iterator.h"
#include "total_poset_member.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

namespace scalable_partial_write
{
typedef int mono_index;

class tri_index
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
  /// The z-index.
  ///
  mono_index k;

  ///
  /// Constructor.
  ///
  tri_index(mono_index xi = 0, mono_index xj = 0, mono_index xk = 0)
  {
    i = xi;
    j = xj;
    k = xk;
  };

  ///
  /// Sum.
  ///
  tri_index operator+(const tri_index& xother) const
  {
    tri_index result(i+xother.i, j+xother.j, k+xother.k);
    return result;
  };

  ///
  /// Self-allocated sum.
  ///
  tri_index& operator+=(const tri_index& xother)
  {
    i += xother.i;
    j += xother.j;
    k += xother.k;
    return *this;
  };

};

class tri_index_space
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
  /// Number in the k factor.
  ///
  mono_index k_ub;

  ///
  /// Number in the space.
  ///
  mono_index size;

  ///
  /// Creates an instance with bound (0,0,0).
  ///
  tri_index_space()
  {
    put_bound(0, 0, 0);
  };

  ///
  /// Creates an instance with bound (xct, yct, zct).
  ///
  tri_index_space(mono_index xct, mono_index yct, mono_index zct)
  {
    put_bound(xct, yct, zct);
  };

  ///
  /// Sets i_ub = xct and j_ub = yct and k_ub = zct and recomputes size.
  ///
  void put_bound(mono_index xct = 0, mono_index yct = 0, mono_index zct = 0)
  {
    i_ub = xct;
    j_ub = yct;
    k_ub = zct;
    size = xct*yct*zct;
  };

  ///
  /// Conversion from mono_index; interpreted as cube.
  ///
  tri_index_space(mono_index xl)
  {
    put_bound(xl, xl, xl);
  };

  ///
  /// Sum.
  ///
  tri_index_space operator+(const tri_index_space& xother) const
  {
    tri_index_space result(i_ub+xother.i_ub, j_ub+xother.j_ub, k_ub+xother.k_ub);
    return result;
  };

  ///
  /// Cartesian product.
  ///
  tri_index_space operator*(const tri_index_space& xother) const
  {
    tri_index_space result(i_ub*xother.i_ub, j_ub*xother.j_ub, k_ub*xother.k_ub);
    return result;
  };

  ///
  /// True if xindex is in this space.
  ///
  bool contains(const tri_index& xindex) const
  {
    bool result =
      (0 <= xindex.i) && (xindex.i < i_ub) &&
      (0 <= xindex.j) && (xindex.j < j_ub) &&
      (0 <= xindex.k) && (xindex.k < k_ub);
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
  mono_index to_row_major_offset(const tri_index& xindex) const
  {
    return j_ub*k_ub*xindex.i+ k_ub*xindex.j + xindex.k;
  };

  ///
  /// Converts xindex to a tri_index using row-major ordering.
  ///
  tri_index from_row_major_offset(const mono_index& xindex) const
  {
    tri_index result(xindex/(j_ub*k_ub), (xindex%(j_ub*k_ub))/k_ub, (xindex%(j_ub*k_ub))%k_ub);
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

    tri_index lblock_id, lnbr_id;
    ragged_array<mono_index>* result = new ragged_array<mono_index>(27*size);

    for(lblock_id.i=0; lblock_id.i<i_ub; lblock_id.i++)
    {
      for(lblock_id.j=0; lblock_id.j<j_ub; lblock_id.j++)
      {
        for(lblock_id.k=0; lblock_id.k<k_ub; lblock_id.k++)
        {

          // Make a list of the members in the neighborhood of
          // the current member, including the current member itself.

          tri_index ldelta;
          for(ldelta.i=-1; ldelta.i<2; ldelta.i++)
          {
            for(ldelta.j=-1; ldelta.j<2; ldelta.j++)
            {
              for(ldelta.k=-1; ldelta.k<2; ldelta.k++)
              {
                lnbr_id = lblock_id + ldelta;
                if(contains(lnbr_id))
                {
                  result->push_back(to_row_major_offset(lnbr_id));
                }
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
  tri_index_space block_element_index_space;

  ///
  /// Index space of vertices within a block.
  ///
  tri_index_space block_vertex_index_space;

  ///
  /// Index space of blocks within the mesh.
  ///
  tri_index_space block_index_space;

  ///
  /// Index space of elements within the mesh.
  ///
  tri_index_space element_index_space;

  ///
  /// Index space of vertices within the mesh.
  ///
  tri_index_space vertex_index_space;

  ///
  /// Default constructor.
  ///
  multiblock_mesh_descriptor()
  {
    // All index spaces default to (0,0,0);
  };

  ///
  /// Constructor.
  ///
  multiblock_mesh_descriptor(mono_index xblock_element_xct,
                             mono_index xblock_element_yct,
                             mono_index xblock_element_zct,
                             mono_index xblock_xct,
                             mono_index xblock_yct,
                             mono_index xblock_zct)
  {
    block_element_index_space.put_bound(xblock_element_xct, xblock_element_yct, xblock_element_zct);
    block_vertex_index_space = block_element_index_space + 1;
    block_index_space.put_bound(xblock_xct, xblock_yct, xblock_zct);
    element_index_space = block_element_index_space*block_index_space;
    vertex_index_space = element_index_space + 1;
  };

  ///
  /// Converts element or vertex index xblock_rel_id from block relative to
  /// mesh relative.
  ///
  tri_index mesh_relative_index(tri_index xblock_id, tri_index xblock_rel_id) const
  {
    tri_index result;
    result.i = block_element_index_space.i_ub*xblock_id.i + xblock_rel_id.i;
    result.j = block_element_index_space.j_ub*xblock_id.j + xblock_rel_id.j;
    result.k = block_element_index_space.k_ub*xblock_id.k + xblock_rel_id.k;
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
  tri_index block_id;

  ///
  /// The index of the vertex in the LLH corner of this block.
  ///
  tri_index llh_id;

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
  /// The global vertex id of the vertex with block relative tri_index xrel_id.
  ///
  mono_index vertex_id(const tri_index& xrel_id) const
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
  /// Creates connectivity for any block of quads in the mesh described by
  /// xmesh.
  ///
  connectivity(const multiblock_mesh_descriptor& xmesh)
  {
    mesh = xmesh;
    node_ids_ub = 8*mesh.block_element_index_space.size;
    node_ids = new mono_index[node_ids_ub];
  };

  ~connectivity()
  {
    delete [] node_ids;
  };

  ///
  /// Creates the connectivity for block xblock_id.
  ///
  void make_block(const tri_index& xblock_id)
  {
    block_id = xblock_id;

    tri_index zero;
    llh_id = mesh.mesh_relative_index(block_id, zero);

    tri_index_space lele_space = mesh.block_element_index_space;

    mono_index node_ct = 0;
    tri_index lele_id;
    for(lele_id.i = 0; lele_id.i < lele_space.i_ub; lele_id.i++)
    {
      for(lele_id.j = 0; lele_id.j < lele_space.j_ub; lele_id.j++)
      {
        for(lele_id.k = 0; lele_id.k < lele_space.k_ub; lele_id.k++)
        {
          // Each tri_index value is the lower-left-hand node in a hex.
          // When drawing a diagram, note that x is associated with i,
          // y is associated with j and z is associated with k.

          // Connectivity follows right-hand rule (ccw) starting
          // in llh corner of quad.

          tri_index tmp_id(lele_id); // (i,j,k)
          tmp_id.i++; // (i+1,j,k)
          node_ids[node_ct++] = vertex_id(tmp_id);
          tmp_id.i--; // (i,j,k)
          node_ids[node_ct++] = vertex_id(tmp_id);
          tmp_id.j++; // (i,j+1,k)
          node_ids[node_ct++] = vertex_id(tmp_id);
          tmp_id.i++; // (i+1,j+1,k)
          node_ids[node_ct++] = vertex_id(tmp_id);
          tmp_id.j--;
          tmp_id.k++; // (i+1,j,k+1)
          node_ids[node_ct++] = vertex_id(tmp_id);
          tmp_id.i--; // (i,j,k+1)
          node_ids[node_ct++] = vertex_id(tmp_id);
          tmp_id.j++; // (i,j+1,k+1)
          node_ids[node_ct++] = vertex_id(tmp_id);
          tmp_id.i++; // (i+1,j+1,k+1)
          node_ids[node_ct++] = vertex_id(tmp_id);
        }
      }
    }

  };

  ///
  /// Creates the connectivity for block with sequence id xblock_seq_id.
  ///
  void make_block(const mono_index& xblock_seq_id)
  {
    const tri_index_space& lblock_index_space = mesh.block_index_space;
    tri_index lblock_id = lblock_index_space.from_row_major_offset(xblock_seq_id);
    make_block(lblock_id);
  };
};

///
/// Refines the block member specified by xmesh and xindex using
/// the connectivity in xconn and writes it to disl using xsa.
///
void
process_block(poset* xmesh,
              abstract_poset_member& xblock,
              connectivity& xconn,
              storage_agent& xsa,
              bool xverbose);
///
/// Deletes the down set of the block "in the center" of the
/// neighborhood specified by xindex and syncronizes xsa.
///
void
delete_neighborhood_center(poset* xmesh,
                           abstract_poset_member& xnbrhd,
                           storage_agent& xsa);

///
/// Iterates over the blocks in the block decomposition, refining each
/// and writing it to disk.
///
void
process_block_decomposition(const multiblock_mesh_descriptor& xmesh_desc,
                            poset* xmesh,
                            storage_agent& xsa,
                            bool xverbose);
}
; // end namespace

using namespace scalable_partial_write;


///
void
scalable_partial_write::
delete_neighborhood_center(poset* xmesh,
                           abstract_poset_member& xnbrhd,
                           storage_agent& xsa)
{
  // Preconditions:

  require(xmesh != 0);
  require(xmesh->state_is_read_write_accessible());
  require(xmesh->contains_member(&xnbrhd));

  // Body:

  // Delete the entire down set of the block "in the center"
  // of the neighborhood xnbrhd.

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
process_block(poset* xmesh,
              abstract_poset_member& xblock,
              connectivity& xconn,
              storage_agent& xsa,
              bool xverbose)
{
  // Preconditions:

  require(xblock.is_jim());
  require(xblock.is_atom());

  // Body:

  // Make the block connectivity.

  if(xverbose)
  {
    cout << "Building block " << poset_path::block_id(xblock.name()) << endl;
  }

  xconn.make_block(poset_path::block_id(xblock.name()));

  // Refine the block member; build the block under it.

  total_poset_member ltemplate(xmesh->name_space(), "cell definitions/hexahedron", true);
  ltemplate.get_read_access();
  block_poset_builder block_builder(ltemplate.host());
  block_builder.build_block_pa(&ltemplate,
                               xconn.node_ids,
                               xconn.node_ids_ub,
                               &xblock,
                               static_cast<hash_map<int, int>*>(0));
  ltemplate.release_access();
  ltemplate.detach_from_state();

#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << "after refining block " << xblock.name() << endl;
  cout << *xmesh << endl;
  cout << endl << "writing block " << xblock.name() << " to file." << endl;
#endif

  // Write the block.

  poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                      sheaf_constants::BOTTOM_INDEX,
                                      xblock.index());

  xsa.write(*xmesh,
            lrow_bounds,
            poset_bounds_descriptor::BOTTOM_TOP,
            storage_agent::RELEASE_ALL);

  // Delete the interior of the block.

  xblock.delete_down();

#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << "after deleting the interior of block " << xblock.name() << endl;
  cout << *xmesh << endl;
#endif

  // Postconditions:

  // Exit:

  return;
};


///
void
scalable_partial_write::
process_block_decomposition(const multiblock_mesh_descriptor& xmesh_desc,
                            poset* xmesh,
                            storage_agent& xsa,
                            bool xverbose)
{
  // Preconditions:

  require(xmesh != 0);
  require(xmesh->state_is_read_write_accessible());

  // Body:

  connectivity lconn(xmesh_desc);

  int ct = 0;
  block_decomposition_iterator lnbrhd_itr(xmesh->top());
  while(!lnbrhd_itr.is_done())
  {
    switch(lnbrhd_itr.action())
    {
    case block_decomposition_iterator::BLOCK_ACTION:

      // This is a block member; build the block and write it to disk.

      process_block(xmesh, lnbrhd_itr.item(), lconn, xsa, xverbose);
      ct++;
      break;

    case block_decomposition_iterator::NEIGHBORHOOD_ACTION:

      // This is a neighborhood member. We're finished with the
      // member "in the center" of the neighborhood, delete its
      // entire strict down set. (Want to keep the block member
      // itself for the tabel of contents.)

      delete_neighborhood_center(xmesh, lnbrhd_itr.item(), xsa);
      ct--;
      break;

    case block_decomposition_iterator::NOT_AN_ACTION:
      cout << "Unexpected action from block_decomposition_iterator." << endl;
      break;
    }
    lnbrhd_itr.next();
  }

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

  mono_index lblock_element_i_ub  = argc > 1 ? atoi(argv[1]) : 1;
  mono_index lblock_element_j_ub  = argc > 2 ? atoi(argv[2]) : 1;
  mono_index lblock_element_k_ub  = argc > 3 ? atoi(argv[3]) : 1;
  mono_index lblock_i_ub          = argc > 4 ? atoi(argv[4]) : 1;
  mono_index lblock_j_ub          = argc > 5 ? atoi(argv[5]) : 1;
  mono_index lblock_k_ub          = argc > 6 ? atoi(argv[6]) : 1;
  bool lverbose                   = argc > 7;

  multiblock_mesh_descriptor
  mesh_desc(lblock_element_i_ub, lblock_element_j_ub, lblock_element_k_ub, lblock_i_ub, lblock_j_ub, lblock_k_ub);

  // Create the name space.

  string dash("-");
  string lns_name("scalable_partial_hex_write");
  lns_name += dash + (argc > 1 ? argv[1] : "1");
  lns_name += dash + (argc > 2 ? argv[2] : "1");
  lns_name += dash + (argc > 3 ? argv[3] : "1");
  lns_name += dash + (argc > 4 ? argv[4] : "1");
  lns_name += dash + (argc > 5 ? argv[5] : "1");
  lns_name += dash + (argc > 6 ? argv[6] : "1");
  sheaves_namespace* ns = new sheaves_namespace(lns_name);

  ns->get_read_write_access();

  // Initialize the storage agent; opens the file.

  storage_agent sa(lns_name + ".hdf", sheaf_file::READ_WRITE);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_size(64);
  sa.put_dof_tuple_record_buffer_ub(15);

  // Create mesh poset

  poset* mesh = new poset(ns, "local_coordinates_schema/local_coordinates_schema",
                          "multiblock_hex_mesh");

  // Write the name space itself.
  // In the current implementation, the namespace poset must be the first poset
  // written and no members can be added or removed from it until the file is
  // closed.

  sa.write(*ns);

  mesh->get_read_write_access();

  // Create the block decomposition.

  tri_index_space lblock_space = mesh_desc.block_index_space;
  block<int> lblock_ids(lblock_space.size);
  lblock_ids.set_ct(lblock_space.size);
  for(int i=0; i<lblock_ids.ct(); i++)
  {
    lblock_ids[i] = i;
  }
  ragged_array<int>* lblock_nbrs = lblock_space.neighbor_list();
  block_poset_builder::build_block_decomposition(mesh, lblock_ids, *lblock_nbrs);
  delete lblock_nbrs;

  // Create and write down set of each block.

  process_block_decomposition(mesh_desc, mesh, sa, lverbose);

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
