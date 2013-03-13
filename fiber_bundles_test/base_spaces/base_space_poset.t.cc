
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example base_spaces/base_space_poset.t.cc
/// Unit test for class base_space_poset.

#include "fiber_bundles_namespace.h"
#include "namespace_poset_member.h"
#include "std_iomanip.h"
#include "structured_block_1d.h"
#include "test_utils.h"
//#include "poset_path.h"
//#include "storage_agent.h"
//#include "test_sections.impl.h"

using namespace fiber_bundle;

namespace
{
  ///
  /// Simple derived class to allow access to protected functions
  /// in base_space_poset.
  ///
  class base_space_poset_derived : public base_space_poset
  {
  public:

    base_space_poset_derived() {}

    ~base_space_poset_derived() {}

    base_space_poset_derived(const base_space_poset_derived& xother)
      : base_space_poset(xother)
    {
    }

    base_space_poset_derived(const poset& xother)
      : base_space_poset(xother)
    {
    }

    base_space_poset_derived(const namespace_poset* xhost,
                             pod_index_type xindex)
      : base_space_poset(xhost, xindex)
    {
    }

    base_space_poset_derived(const namespace_poset* xhost,
                             const scoped_index&  xindex)
      : base_space_poset(xhost, xindex)
    {
    }

    base_space_poset_derived(const namespace_poset* xhost,
                             const string& xname)
      : base_space_poset(xhost, xname)
    {
    }

    base_space_poset_derived(const abstract_poset_member* xmbr)
      : base_space_poset(xmbr) 

    {
    }

    virtual void detach_from_state()
    {
      base_space_poset::detach_from_state();
    }

    virtual base_space_poset_derived* clone() const
    {
      base_space_poset* lbsp = base_space_poset::clone();
      base_space_poset_derived* lresult =
        dynamic_cast<base_space_poset_derived*>(lbsp);
      return lresult; 
    }

    base_space_poset_derived& operator=(const poset_state_handle& xother)
    {
      base_space_poset& lbsp = base_space_poset::operator=(xother);
      base_space_poset_derived* lresult =
        dynamic_cast<base_space_poset_derived*>(&lbsp);
      return *lresult; 
    }
  };

} //end unnamed namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing base_space_poset");

  //============================================================================

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  // Make a mesh with 2 blocks.

  base_space_poset& lbase_space =
    lns.new_base_space<structured_block_1d>("1d_structured_mesh");

  structured_block_1d lblock0(&lbase_space, 2, true);
  lblock0.put_name("1D_structured_block0", true, true);

  structured_block_1d lblock1(&lbase_space, 2, true);
  lblock1.put_name("1D_structured_block1", true, true);

  //============================================================================

  string lname = lbase_space.name();
  scoped_index lindex = lbase_space.index();


  //base_space_poset(const namespace_poset* xhost, pod_index_type xindex);

  base_space_poset_derived lbase_derived4(&lns, lindex.hub_pod());

  //base_space_poset(const namespace_poset* xhost, const scoped_index& xindex);

  base_space_poset_derived lbase_derived5(&lns, lindex);

  //base_space_poset(const namespace_poset* xhost, const string& xname);

  base_space_poset_derived lbase_derived6(&lns, lname);

  //base_space_poset(const base_space_poset& xother);
  base_space_poset_derived lbase_derived7(lbase_derived6);

  //base_space_poset(const poset& xother);
  //base_space_poset_derived lbase_derived7a(lbase_space);

  //base_space_poset(const abstract_poset_member* xmbr);

  namespace_poset_member lnpm(&lns, lindex);
  const abstract_poset_member* lmbr = &lnpm;
  base_space_poset_derived lbase_derived8(lmbr);
 
  poset_state_handle* lpsh = &lbase_derived4;
  base_space_poset_derived lassign;
  lassign = (*lpsh);

  base_space_poset_derived* lclone = lbase_derived4.clone();

  lbase_derived4.detach_from_state();
  lbase_derived5.detach_from_state();
  lbase_derived6.detach_from_state();
  lbase_derived7.detach_from_state();
  lbase_derived8.detach_from_state();
  lnpm.detach_from_state(); 
  lassign.detach_from_state();

  //============================================================================

  //void put_max_db(int xmax_db);

  lbase_space.put_max_db(2);

  //int max_db() const;

  int lmax_db = lbase_space.max_db();
  cout << "lmax_db = " << lmax_db << endl;

  //void update_max_db(int xmax_db);

  lbase_space.update_max_db(++lmax_db);

  //static arg_list make_args(int xmax_db);

  lbase_space.put_max_db(1);

  arg_list larg_list = base_space_poset::make_args(lmax_db);
  cout << "larg_list = " << larg_list << endl;

  //============================================================================

  bool ltest;

  //bool contains_zone_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_zone_id_space(lblock0.index().hub_id(), true);
  cout << "ltest = " << boolalpha << ltest << endl;
 
  //bool contains_zone_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_zone_id_space(lblock0.index(), true);
  cout << "ltest = " << boolalpha << ltest << endl;

  //index_space_handle& get_zone_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  index_space_handle& lhandle0 =
    lbase_space.get_zone_id_space(lblock0.index().hub_id(), true);

  //index_space_handle& get_zone_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  index_space_handle& lhandle1 =
    lbase_space.get_zone_id_space(lblock0.index(), true);

  //void release_zone_id_space(index_space_handle& xid_space, bool xauto_access) const;

  lbase_space.release_zone_id_space(lhandle0, true);

  //index_space_iterator& get_zone_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const;

  index_space_iterator& literator0 =
    lbase_space.get_zone_id_space_iterator(lblock0.index().hub_id(), true);

  //index_space_iterator& get_zone_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const;

  index_space_iterator& literator1 =
    lbase_space.get_zone_id_space_iterator(lblock0.index(), true);

  //void release_zone_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

  lbase_space.release_zone_id_space_iterator(literator0, true);

  //============================================================================

  //bool contains_vertex_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_vertex_id_space(lblock0.index().hub_id(), true);
  cout << "ltest = " << boolalpha << ltest << endl;
 
  //bool contains_vertex_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_vertex_id_space(lblock0.index(), true);
  cout << "ltest = " << boolalpha << ltest << endl;

  //index_space_handle& get_vertex_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  index_space_handle& lhandle2 =
    lbase_space.get_vertex_id_space(lblock0.index().hub_id(), true);

  //index_space_handle& get_vertex_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  index_space_handle& lhandle3 =
    lbase_space.get_vertex_id_space(lblock0.index(), true);

  //void release_vertex_id_space(index_space_handle& xid_space, bool xauto_access) const;

  lbase_space.release_vertex_id_space(lhandle2, true);

  //index_space_iterator& get_vertex_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const;

  index_space_iterator& literator2 =
    lbase_space.get_vertex_id_space_iterator(lblock0.index().hub_id(), true);

  //index_space_iterator& get_vertex_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const;

  index_space_iterator& literator3 =
    lbase_space.get_vertex_id_space_iterator(lblock0.index(), true);

  //void release_vertex_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

  lbase_space.release_vertex_id_space_iterator(literator2, true);

  //============================================================================

  //bool contains_connectivity_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_connectivity_id_space(lblock0.index().hub_id(), true);
  cout << "ltest = " << boolalpha << ltest << endl;
 
  //bool contains_connectivity_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_connectivity_id_space(lblock0.index(), true);
  cout << "ltest = " << boolalpha << ltest << endl;

//   //index_space_handle& get_connectivity_id_space(pod_index_type xmbr_id, bool xauto_access) const;

//   index_space_handle& lhandle4 =
//     lbase_space.get_connectivity_id_space(lblock0.index().hub_id(), true);

//   //index_space_handle& get_connectivity_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

//   index_space_handle& lhandle5 =
//     lbase_space.get_connectivity_id_space(lblock0.index(), true);

//   //void release_connectivity_id_space(index_space_handle& xid_space, bool xauto_access) const;

//   lbase_space.release_connectivity_id_space(lhandle4, true);

//   //index_space_iterator& get_connectivity_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const;

//   index_space_iterator& literator4 =
//     lbase_space.get_connectivity_id_space_iterator(lblock0.index().hub_id(), true);

//   //index_space_iterator& get_connectivity_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const;

//   index_space_iterator& literator5 =
//     lbase_space.get_connectivity_id_space_iterator(lblock0.index(), true);

//   //void release_connectivity_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

//   lbase_space.release_connectivity_id_space_iterator(literator4, true);

  //============================================================================

  //bool contains_adjacency_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_adjacency_id_space(lblock0.index().hub_id(), true);
  cout << "ltest = " << boolalpha << ltest << endl;
 
  //bool contains_adjacency_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_adjacency_id_space(lblock0.index(), true);
  cout << "ltest = " << boolalpha << ltest << endl;

//   //index_space_handle& get_adjacency_id_space(pod_index_type xmbr_id, bool xauto_access) const;

//   index_space_handle& lhandle6 =
//     lbase_space.get_adjacency_id_space(lblock0.index().hub_id(), true);

//   //index_space_handle& get_adjacency_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

//   index_space_handle& lhandle7 =
//     lbase_space.get_adjacency_id_space(lblock0.index(), true);

//   //void release_adjacency_id_space(index_space_handle& xid_space, bool xauto_access) const;

//   lbase_space.release_adjacency_id_space(lhandle6, true);

//   //index_space_iterator& get_adjacency_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const;

//   index_space_iterator& literator6 =
//     lbase_space.get_adjacency_id_space_iterator(lblock0.index().hub_id(), true);

//   //index_space_iterator& get_adjacency_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const;

//   index_space_iterator& literator7 =
//     lbase_space.get_adjacency_id_space_iterator(lblock0.index(), true);

//   //void release_adjacency_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

//   lbase_space.release_adjacency_id_space_iterator(literator6, true);

  //============================================================================

  //bool contains_vertex_client_id_space(pod_index_type xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_vertex_client_id_space(lblock0.index().hub_id(), true);
  cout << "ltest = " << boolalpha << ltest << endl;
 
  //bool contains_vertex_client_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

  ltest = lbase_space.contains_vertex_client_id_space(lblock0.index(), true);
  cout << "ltest = " << boolalpha << ltest << endl;

//   //index_space_handle& get_vertex_client_id_space(pod_index_type xmbr_id, bool xauto_access) const;

//   index_space_handle& lhandle8 =
//     lbase_space.get_vertex_client_id_space(lblock0.index().hub_id(), true);

//   //index_space_handle& get_vertex_client_id_space(const scoped_index& xmbr_id, bool xauto_access) const;

//   index_space_handle& lhandle9 =
//     lbase_space.get_vertex_client_id_space(lblock0.index(), true);

//   //void release_vertex_client_id_space(index_space_handle& xid_space, bool xauto_access) const;

//   lbase_space.release_vertex_client_id_space(lhandle8, true);

//   //index_space_iterator& get_vertex_client_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const;

//   index_space_iterator& literator8 =
//     lbase_space.get_vertex_client_id_space_iterator(lblock0.index().hub_id(), true);

//   //index_space_iterator& get_vertex_client_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const;

//   index_space_iterator& literator9 =
//     lbase_space.get_vertex_client_id_space_iterator(lblock0.index(), true);

//   //void release_vertex_client_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

//   lbase_space.release_vertex_client_id_space_iterator(literator9, true);

  //============================================================================

  //const subposet& blocks() const;
  const base_space_poset* lbase_space_const = &lbase_space;
  const subposet& lblocks = lbase_space_const->blocks();

  //const subposet& block_vertices() const
  const subposet& lblock_vertices = lbase_space_const->block_vertices();

  //const subposet& elements() const;
  const subposet& lelements = lbase_space_const->elements();

  //const subposet& cells() const;
  const subposet& lcells = lbase_space_const->cells();

  //const subposet& d_cells(int xd) const;
  const subposet& ld_cells = lbase_space_const->d_cells(1);

  //const mutable_index_space_handle& d_cells_id_space(int xd) const
  const mutable_index_space_handle& ld_cells_id_space =
    lbase_space_const->d_cells_id_space(1);

//   //void insert_member_in_standard_subposets(pod_index_type xmbr_id);
//   lbase_space.insert_member_in_standard_subposets(lblock1.index().hub_pod());

//   //void insert_member_in_standard_subposets(const scoped_index& xmbr_id);
//   lbase_space.insert_member_in_standard_subposets(lblock1.index());

  //============================================================================

  //void put_refinement_depth(pod_index_type xindex, int xdepth);
  lbase_space.put_refinement_depth(lblock0.index().hub_pod(), 1);

  //void put_refinement_depth(const scoped_index& xindex, int xdepth);
  lbase_space.put_refinement_depth(lblock0.index(), 2);

  //============================================================================

  //virtual bool is_ancestor_of(const any* other) const;

  bool lis_ancestor_of = lbase_space.is_ancestor_of(&lbase_derived4);
  cout << "lis_ancestor_of = " << boolalpha << lis_ancestor_of << endl;

  //============================================================================

  //size_t fiber_bundle::deep_size(const base_space_poset& xp,
  //                               bool xinclude_shallow, size_t xresults[4])
  size_t lresults[4];
  size_t ldeep_size = deep_size(lbase_space, false, lresults);
  cout << "ldeep_size = " << ldeep_size << endl;

  //============================================================================

  // Clean-up.

  lblock0.detach_from_state();
  lblock1.detach_from_state();

  // Output namespace.

  //cout << lns << endl;

  //storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  //sa.write_entire(lns);

  //============================================================================

  print_footer("End testing base_space_poset");

  // Postconditions:

  // Exit:

  return 0;
}
