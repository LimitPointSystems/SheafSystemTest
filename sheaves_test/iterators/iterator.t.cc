
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example iterators/iterator.t.cc
/// ITERATOR cluster tester

#include "postorder_iterator.h"
#include "postorder_member_iterator.h"
#include "preorder_member_iterator.h"
#include "refinable_poset.h"
#include "assert_contract.h"
#include "sheaves_namespace.h"
#include "std_iostream.h"
#include "subposet_member_iterator.h"
#include "total_poset_member.h"
#include "filtered_depth_first_iterator.h"
#include "triorder_iterator.h"
#include "biorder_iterator.h"
#include "linkorder_iterator.h"
using namespace sheaf;

// Global variables:
sheaves_namespace* test_namespace;
refinable_poset*   refinable_triangle;
subposet*          vertices;
subposet*          edges;
subposet*          elements;
subposet*          n_cells;

///
/// Creates a triangle mesh for use as a base space.
///
void
copy_std_triangle()
{
  // Preconditions:

  // Body:

  test_namespace = new sheaves_namespace("iterator.t");

  // Create refinable triangle poset

  test_namespace->make_triangle(test_namespace);

  test_namespace->get_read_access();

  refinable_triangle =
    &test_namespace->member_poset<refinable_poset>(string("cells"), true);

  // Postconditions:

  ensure(test_namespace->state_is_read_accessible());

  // Exit:
}

///
/// Construct a refinable triangle mesh.
///
void
make_refinable_triangle()
{

  copy_std_triangle();

  // Name the cells for convenience.

  refinable_triangle->get_read_write_access();

  // Create some subposets to use as filters.

  // Just the vertices

  vertices = new subposet(refinable_triangle);
  vertices->put_name("__vertices", true, false);
  vertices->insert_member(6);
  vertices->insert_member(7);
  vertices->insert_member(8);

  // Just the edges

  edges = new subposet(refinable_triangle);
  edges->put_name("__edges", true, false);
  edges->insert_member(3);
  edges->insert_member(4);
  edges->insert_member(5);

  // Just the triangles

  elements = new subposet(refinable_triangle);
  elements->put_name("__elements", true, false);
  elements->insert_member(4);

  // All cells of dimension 0, 1, or 2

  n_cells = new subposet(refinable_triangle);
  n_cells->put_name("0-, 1- and 2-cells", true, false);
  vertices->p_union_pa(edges, n_cells);
  n_cells->p_union_sa(elements);

  // Just to be polite and proper...

  refinable_triangle->release_access();
}

///
/// Refine the triangle mesh.
///
void
refine()
{
  // Begin a new refinement

  refinable_triangle->begin_refine_mode(false);

  // Get handles to the existing edge and vertices

  total_poset_member e0(refinable_triangle, "edge 0");
  total_poset_member e1(refinable_triangle, "edge 1");
  total_poset_member e2(refinable_triangle, "edge 2");

  total_poset_member v0(refinable_triangle, "vertex 0");
  total_poset_member v1(refinable_triangle, "vertex 1");
  total_poset_member v2(refinable_triangle, "vertex 2");

  total_poset_member t0(refinable_triangle, "triangle 0");

  // Make another vertex

  total_poset_member v3(refinable_triangle, &(v0.dof_map()));
  v3.put_name("vertex 3", true, false);
  vertices->insert_member(&v3);
  n_cells->insert_member(&v3);
  //vertices_id_map->put_poset_id(v3.index());

  // Make two refined edges, and insert another edge

  total_poset_member e3(refinable_triangle, &(e0.dof_map()));
  e3.put_name("edge 3", true, false);
  edges->insert_member(&e3);
  n_cells->insert_member(&e3);
  //elements_id_map->put_poset_id(e3.index());

  total_poset_member e4(refinable_triangle, &(e0.dof_map()));
  e4.put_name("edge 4", true, false);
  edges->insert_member(&e4);
  n_cells->insert_member(&e4);
  //elements_id_map->put_poset_id(e4.index());

  total_poset_member e5(refinable_triangle, &(e0.dof_map()));
  e5.put_name("edge 5", true, false);
  edges->insert_member(&e5);
  n_cells->insert_member(&e5);
  //elements_id_map->put_poset_id(e5.index());

  // Make two triangles

  total_poset_member t1(refinable_triangle, &(t0.dof_map()));
  t1.put_name("triangle 1", true, false);
  elements->insert_member(&t1);
  n_cells->insert_member(&t1);

  total_poset_member t2(refinable_triangle, &(t0.dof_map()));
  t2.put_name("triangle 2", true, false);
  elements->insert_member(&t2);
  n_cells->insert_member(&t2);

  // Delete obsolete cover links.

  e0.delete_cover_link(&v0);
  e0.delete_cover_link(&v1);

  //  t0.delete_cover_link(&e0);
  t0.delete_cover_link(&e1);
  t0.delete_cover_link(&e2);

  // Insert new links.

  e0.create_cover_link(&e3);
  e0.create_cover_link(&e4);

  e3.create_cover_link(&v0);
  e3.create_cover_link(&v3);

  e4.create_cover_link(&v3);
  e4.create_cover_link(&v1);

  e5.create_cover_link(&v2);
  e5.create_cover_link(&v3);

  t0.create_cover_link(&t2);
  t0.create_cover_link(&t1);

  t1.create_cover_link(&e2);
  t1.create_cover_link(&e3);
  t1.create_cover_link(&e5);

  t2.create_cover_link(&e1);
  t2.create_cover_link(&e4);
  t2.create_cover_link(&e5);

  // The unrefined edge is no longer a jim

  refinable_triangle->jims().remove_member(&e0);
  refinable_triangle->coarsest_common_refinement_jims().remove_member(&e0);

  // The unrefined triangle is no longer a jim

  refinable_triangle->jims().remove_member(&t0);
  refinable_triangle->coarsest_common_refinement_jims().remove_member(&t0);

  refinable_triangle->end_refine_mode(true, false);

  // Clean up

  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();

  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  e3.detach_from_state();
  e4.detach_from_state();
  e5.detach_from_state();

  t0.detach_from_state();
  t1.detach_from_state();
  t2.detach_from_state();

}

///
/// Test deleting version 0 of the triangle mesh.
///
void test_deletion()
{
  // Preconditions:


  // Body:

  refinable_triangle->get_read_write_access();
  refinable_triangle->begin_jim_edit_mode();

  cout << "\n##### begin POSTORDER_DELETION test at version 0 #####\n";
  refinable_triangle->top().delete_down();
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2 1\n";
  cout << "##### end   unfiltered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n";

  refinable_triangle->end_jim_edit_mode();
  refinable_triangle->release_access();

  // Postconditions:

  // Exit:

  return;
}

///
/// Test creating version 0 of the triangle mesh before refinement.
///
void
test_level_0_before_refinement()
{
  // Preconditions:

  // Body:

  refinable_triangle->get_read_write_access();

  //refinable_triangle->put_version(0);

  cout << "\n##### begin unfiltered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";
  postorder_member_iterator post_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2 1\n";
  cout << "##### end   unfiltered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered strict down set POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";
  post_itr.put_strict(true);
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2\n";
  cout << "##### end   unfiltered strict down set POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered strict up set POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";
  total_poset_member v0(refinable_triangle, "v0");
  post_itr.put_descending(false);
  post_itr.put_anchor(&v0);
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 1 2 3 4\n";
  cout << "##### end   unfiltered strict up set POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin filtered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";
  post_itr.put_descending(true);
  post_itr.put_strict(false);
  post_itr.put_anchor(&(refinable_triangle->top()));
  post_itr.put_filter("__vertices");
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 6 7 8\n";
  cout << "##### end   filtered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n";

  cout << "##### begin filtered link POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " "
    << post_itr.lesser_index().pod()
    << "->"
    << post_itr.greater_index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 6->" << invalid_pod_index() << " 7->" << invalid_pod_index() << " 8->" << invalid_pod_index() << "\n";
  cout << "##### end   filtered link POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered PREORDER_MEMBER_ITERATOR test at version 0 #####\n";
  preorder_member_iterator pre_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 1 2 3 6 0 7 4 8 5\n";
  cout << "##### end   unfiltered PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin filtered PREORDER_MEMBER_ITERATOR test at version 0 #####\n";
  pre_itr.put_anchor(&(refinable_triangle->top()));
  pre_itr.put_filter(*n_cells);
  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 6 7 4 8 5\n";
  cout << "##### end   filtered PREORDER_MEMBER_ITERATOR test at version at version 0 #####\n\n";


  cout << "##### begin filtered link PREORDER_MEMBER_ITERATOR test at version 0 #####\n";
  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.lesser_index().pod() << "->" << pre_itr.greater_index().pod();
    pre_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3->" << invalid_pod_index() << " 6->3 7->3 4->" << invalid_pod_index() << " 8->4 5->" << invalid_pod_index() << "\n";
  cout << "##### end   filtered link PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin truncated filtered PREORDER_MEMBER_ITERATOR test at version 0 #####\n";
  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.truncate();
  }
  cout << "\nshould be:\n";
  cout << " 3 4 5\n";
  cout << "##### end   truncated filtered PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin strict down set PREORDER_MEMBER_ITERATOR test at version 0 #####\n";
  pre_itr.put_strict(true);
  pre_itr.put_anchor(&(refinable_triangle->top()));
  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 2 3 6 0 7 4 8 5\n";
  cout << "##### end   strict down set PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin strict up set PREORDER_MEMBER_ITERATOR test at version 0 #####\n";
  preorder_member_iterator strict_itr(v0, "", UP, STRICT);
  while(!strict_itr.is_done())
  {
    cout << " " << strict_itr.item().index().pod();
    strict_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 2 1 4\n";
  cout << "##### end   strict up set PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin subposet minimals PREORDER_MEMBER_ITERATOR test at version 0 #####\n";

  // Find minimal members of subposet n_cells

  subposet lmins(refinable_triangle);

  preorder_member_iterator ext_itr(refinable_triangle->top(), "", UP, STRICT);

  subposet_member_iterator* sp_itr = n_cells->member_iterator();
  while(!sp_itr->is_done())
  {
    if(!ext_itr.has_visited(*sp_itr))
    {
      // Current member is not bounded some
      // member that has already been visited so
      // assume it is extremal

      lmins.insert_member(sp_itr);

      // Members of the strict down/up-set of current
      // can not be extremal, remove them from result.
      // (Removing non-members doesn't hurt.)
      // By not reseting the visited markers, we ensure
      // that we only traverse the down/up-set of each member
      // once and we don't reinsert some member that has
      // already been removed from the result.

      ext_itr.put_anchor(sp_itr);
      ext_itr.reset(sheaf::NO_RESET);
      while(!ext_itr.is_done())
      {
        lmins.remove_member(ext_itr.item().index().pod());
        ext_itr.next();
      }
    }
    sp_itr->next();
  }



  subposet_member_iterator* lmins_itr = lmins.member_iterator();

  while(!lmins_itr->is_done())
  {
    cout << " " << lmins_itr->index().pod();
    lmins_itr->next();
  }

  cout << "\nshould be:\n";
  cout << " 6 7 8\n";
  cout << "##### end   subposet minimals PREORDER_MEMBER_ITERATOR test at version 0 #####" << endl;

  // Delete lmins; it was just a temporary.
  lmins.delete_state();






  cout << "\n##### begin unfiltered FILTERED_DEPTH_FIRST_ITERATOR postvisit test at version 0 #####\n";
  filtered_depth_first_iterator depth_first_itr(refinable_triangle->top(),
						DOWN,
						NOT_STRICT,
						depth_first_iterator::TRIORDER);
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      cout << " " << depth_first_itr.index().pod();
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2 1\n";
  cout << "##### end   unfiltered FILTERED_DEPTH_FIRST_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered FILTERED_DEPTH_FIRST_ITERATOR linkorder test at version 0 #####\n";
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      cout << " " << depth_first_itr.lesser_index().pod() << "->" << depth_first_itr.greater_index().pod();
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 0->6 6->3 0->7 7->3 3->2 6->4 0->8 8->4 4->2 7->5 8->5 5->2 2->1\n";
  cout << "##### end   unfiltered FILTERED_DEPTH_FIRST_ITERATOR linkorder test at version 0 #####\n\n";


  cout << "##### begin unfiltered strict down set FILTERED_DEPTH_FIRST_ITERATOR postvisit test at version 0 #####\n";
  depth_first_itr.put_strict(true);
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      cout << " " << depth_first_itr.index().pod();
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2\n";
  cout << "##### end   unfiltered strict down set FILTERED_DEPTH_FIRST_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered strict up set FILTERED_DEPTH_FIRST_ITERATOR postvisit test at version 0 #####\n";
  depth_first_itr.put_descending(false);
  depth_first_itr.put_anchor(&v0);
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      cout << " " << depth_first_itr.index().pod();
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 1 2 3 4\n";
  cout << "##### end   unfiltered strict up set FILTERED_DEPTH_FIRST_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin filtered FILTERED_DEPTH_FIRST_ITERATOR postvisit test at version 0 #####\n";
  depth_first_itr.put_descending(true);
  depth_first_itr.put_strict(false);
  depth_first_itr.put_anchor(&(refinable_triangle->top()));
  depth_first_itr.put_filter("__vertices");
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      cout << " " << depth_first_itr.index().pod();
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 6 7 8\n";
  cout << "##### end   filtered FILTERED_DEPTH_FIRST_ITERATOR test at version 0 #####\n\n";

  cout << "##### begin filtered link FILTERED_DEPTH_FIRST_ITERATOR postvisit test at version 0 #####\n";
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      cout << " " << depth_first_itr.lesser_index().pod() << "->" << depth_first_itr.greater_index().pod();
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 6->" << invalid_pod_index() << " 7->" << invalid_pod_index() << " 8->" << invalid_pod_index() << "\n";
  cout << "##### end   filtered link FILTERED_DEPTH_FIRST_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin filtered FILTERED_DEPTH_FIRST_ITERATOR linkorder test at version 0 #####\n";
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      cout << " " << depth_first_itr.lesser_index().pod() << "->" << depth_first_itr.greater_index().pod();
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 0->6 0->7 0->8\n";
  cout << "##### end   filtered FILTERED_DEPTH_FIRST_ITERATOR linkorder test at version 0 #####\n\n";


  cout << "##### begin unfiltered FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n";
  depth_first_itr.put_anchor(&(refinable_triangle->top()));
  depth_first_itr.put_filter(refinable_triangle->whole());
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      cout << " " << depth_first_itr.index().pod();
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 1 2 3 6 0 7 4 8 5\n";
  cout << "##### end   unfiltered FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin filtered FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n";
  depth_first_itr.put_anchor(&(refinable_triangle->top()));
  depth_first_itr.put_filter(*n_cells);
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      cout << " " << depth_first_itr.index().pod();
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 6 7 4 8 5\n";
  cout << "##### end   filtered FILTERED_DEPTH_FIRST_ITERATOR preorder test at version at version 0 #####\n\n";


  cout << "##### begin filtered link FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n";
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      cout << " " << depth_first_itr.lesser_index().pod() << "->" << depth_first_itr.greater_index().pod();
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3->" << invalid_pod_index() << " 6->3 7->3 4->" << invalid_pod_index() << " 8->4 5->" << invalid_pod_index() << "\n";
  cout << "##### end   filtered link FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin truncated filtered FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n";
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      cout << " " << depth_first_itr.index().pod();
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    depth_first_itr.truncate();
  }
  cout << "\nshould be:\n";
  cout << " 3 4 5\n";
  cout << "##### end   truncated filtered FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin strict down set FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n";
  depth_first_itr.put_strict(true);
  depth_first_itr.put_anchor(&(refinable_triangle->top()));
  depth_first_itr.reset();
  while(!depth_first_itr.is_done())
  {
    switch(depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      cout << " " << depth_first_itr.index().pod();
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 2 3 6 0 7 4 8 5\n";
  cout << "##### end   strict down set FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin strict up set FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n";
  filtered_depth_first_iterator strict_depth_first_itr(v0,
						       "",
						       UP,
						       STRICT,
						       depth_first_iterator::TRIORDER);
  while(!strict_depth_first_itr.is_done())
  {
    switch(strict_depth_first_itr.action())
    {
    case filtered_depth_first_iterator::PREVISIT_ACTION:
      cout << " " << strict_depth_first_itr.index().pod();
      break;
    case filtered_depth_first_iterator::LINK_ACTION:
      break;
    case filtered_depth_first_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    strict_depth_first_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 2 1 4\n";
  cout << "##### end   strict up set FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin subposet minimals FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####\n";

  // Find minimal members of subposet n_cells

  subposet ldfi_mins(refinable_triangle);

  filtered_depth_first_iterator ext_depth_first_itr(refinable_triangle->top(),
						    "",
						    UP,
						    STRICT,
						    depth_first_iterator::TRIORDER);

  sp_itr = n_cells->member_iterator();
  while(!sp_itr->is_done())
  {
    if(!ext_depth_first_itr.has_visited(sp_itr))
    {
      // Current member is not bounded some
      // member that has already been visited so
      // assume it is extremal

      ldfi_mins.insert_member(sp_itr);

      // Members of the strict down/up-set of current
      // can not be extremal, remove them from result.
      // (Removing non-members doesn't hurt.)
      // By not reseting the visited markers, we ensure
      // that we only traverse the down/up-set of each member
      // once and we don't reinsert some member that has
      // already been removed from the result.

      ext_depth_first_itr.put_anchor(sp_itr);
      ext_depth_first_itr.reset(NO_RESET);
      while(!ext_depth_first_itr.is_done())
      {
        if(ext_depth_first_itr.action() == filtered_depth_first_iterator::PREVISIT_ACTION)
        {
          ldfi_mins.remove_member(ext_depth_first_itr.index().pod());
        }
        ext_depth_first_itr.next();
      }
    }
    sp_itr->next();
  }

  subposet_member_iterator* ldfi_mins_itr = ldfi_mins.member_iterator();

  while(!ldfi_mins_itr->is_done())
  {
    cout << " " << ldfi_mins_itr->index().pod();
    ldfi_mins_itr->next();
  }

  cout << "\nshould be:\n";
  cout << " 6 7 8\n";
  cout << "##### end   subposet minimals FILTERED_DEPTH_FIRST_ITERATOR preorder test at version 0 #####" << endl;

  // Delete ldfi_mins; it was just a temporary.

  ldfi_mins.delete_state();





  cout << "\n##### begin unfiltered TRIORDER_ITERATOR postvisit test at version 0 #####\n";
  triorder_iterator tri_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      cout << " " << tri_itr.index().pod();
      break;
    default:
      break;
    }
    tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2 1\n";
  cout << "##### end   unfiltered TRIORDER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered TRIORDER_ITERATOR linkorder test at version 0 #####\n";
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      break;
    case triorder_iterator::LINK_ACTION:
      cout << " " << tri_itr.lesser_index().pod() << "->" << tri_itr.greater_index().pod();
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    tri_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 0->6 6->3 0->7 7->3 3->2 6->4 0->8 8->4 4->2 7->5 8->5 5->2 2->1\n";
  cout << "##### end   unfiltered TRIORDER_ITERATOR linkorder test at version 0 #####\n\n";


  cout << "##### begin unfiltered strict down set TRIORDER_ITERATOR postvisit test at version 0 #####\n";
  tri_itr.put_strict(true);
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      cout << " " << tri_itr.index().pod();
      break;
    default:
      break;
    }
    tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2\n";
  cout << "##### end   unfiltered strict down set TRIORDER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered strict up set TRIORDER_ITERATOR postvisit test at version 0 #####\n";
  tri_itr.put_descending(false);
  tri_itr.put_strict(true);
  tri_itr.put_anchor(&v0);
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      cout << " " << tri_itr.index().pod();
      break;
    default:
      break;
    }
    tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 1 2 3 4\n";
  cout << "##### end   unfiltered strict up set TRIORDER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin filtered TRIORDER_ITERATOR postvisit test at version 0 #####\n";
  tri_itr.put_descending(true);
  tri_itr.put_strict(false);
  tri_itr.put_anchor(&(refinable_triangle->top()));
  tri_itr.put_filter("__vertices");
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      cout << " " << tri_itr.index().pod();
      break;
    default:
      break;
    }
    tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 6 7 8\n";
  cout << "##### end   filtered TRIORDER_ITERATOR test at version 0 #####\n\n";

  cout << "##### begin filtered link TRIORDER_ITERATOR postvisit test at version 0 #####\n";
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      cout << " " << tri_itr.lesser_index().pod() << "->" << tri_itr.greater_index().pod();
      break;
    default:
      break;
    }
    tri_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 6->" << invalid_pod_index() << " 7->" << invalid_pod_index() << " 8->" << invalid_pod_index() << "\n";
  cout << "##### end   filtered link TRIORDER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin filtered TRIORDER_ITERATOR linkorder test at version 0 #####\n";
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      break;
    case triorder_iterator::LINK_ACTION:
      cout << " " << tri_itr.lesser_index().pod() << "->" << tri_itr.greater_index().pod();
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    tri_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 0->6 0->7 0->8\n";
  cout << "##### end   filtered TRIORDER_ITERATOR linkorder test at version 0 #####\n\n";


  cout << "##### begin unfiltered TRIORDER_ITERATOR preorder test at version 0 #####\n";
  tri_itr.put_anchor(&(refinable_triangle->top()));
  tri_itr.put_filter(refinable_triangle->whole());
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      cout << " " << tri_itr.index().pod();
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 1 2 3 6 0 7 4 8 5\n";
  cout << "##### end   unfiltered TRIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin filtered TRIORDER_ITERATOR preorder test at version 0 #####\n";
  tri_itr.put_anchor(&(refinable_triangle->top()));
  tri_itr.put_filter(*n_cells);
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      cout << " " << tri_itr.index().pod();
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 6 7 4 8 5\n";
  cout << "##### end   filtered TRIORDER_ITERATOR preorder test at version at version 0 #####\n\n";


  cout << "##### begin filtered link TRIORDER_ITERATOR preorder test at version 0 #####\n";
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      cout << " " << tri_itr.lesser_index().pod() << "->" << tri_itr.greater_index().pod();
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3->" << invalid_pod_index() << " 6->3 7->3 4->" << invalid_pod_index() << " 8->4 5->" << invalid_pod_index() << "\n";
  cout << "##### end   filtered link TRIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin truncated filtered TRIORDER_ITERATOR preorder test at version 0 #####\n";
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      cout << " " << tri_itr.index().pod();
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    tri_itr.truncate();
  }
  cout << "\nshould be:\n";
  cout << " 3 4 5\n";
  cout << "##### end   truncated filtered TRIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin strict down set TRIORDER_ITERATOR preorder test at version 0 #####\n";
  tri_itr.put_strict(true);
  tri_itr.put_anchor(&(refinable_triangle->top()));
  tri_itr.reset();
  while(!tri_itr.is_done())
  {
    switch(tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      cout << " " << tri_itr.index().pod();
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 2 3 6 0 7 4 8 5\n";
  cout << "##### end   strict down set TRIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin strict up set TRIORDER_ITERATOR preorder test at version 0 #####\n";
  triorder_iterator strict_tri_itr(v0, "", UP, STRICT);
  while(!strict_tri_itr.is_done())
  {
    switch(strict_tri_itr.action())
    {
    case triorder_iterator::PREVISIT_ACTION:
      cout << " " << strict_tri_itr.index().pod();
      break;
    case triorder_iterator::LINK_ACTION:
      break;
    case triorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    strict_tri_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 2 1 4\n";
  cout << "##### end   strict up set TRIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin subposet minimals TRIORDER_ITERATOR preorder test at version 0 #####\n";

  // Find minimal members of subposet n_cells

  subposet ltoi_mins(refinable_triangle);

  triorder_iterator ext_tri_itr(refinable_triangle->top(), "", UP, STRICT);

  sp_itr = n_cells->member_iterator();
  while(!sp_itr->is_done())
  {
    if(!ext_tri_itr.has_visited(sp_itr))
    {
      // Current member is not bounded some
      // member that has already been visited so
      // assume it is extremal

      ltoi_mins.insert_member(sp_itr);

      // Members of the strict down/up-set of current
      // can not be extremal, remove them from result.
      // (Removing non-members doesn't hurt.)
      // By not reseting the visited markers, we ensure
      // that we only traverse the down/up-set of each member
      // once and we don't reinsert some member that has
      // already been removed from the result.

      ext_tri_itr.put_anchor(sp_itr);
      ext_tri_itr.reset(NO_RESET);
      while(!ext_tri_itr.is_done())
      {
        if(ext_tri_itr.action() == triorder_iterator::PREVISIT_ACTION)
        {
          ltoi_mins.remove_member(ext_tri_itr.index().pod());
        }
        ext_tri_itr.next();
      }
    }
    sp_itr->next();
  }

  subposet_member_iterator* ltoi_mins_itr = ltoi_mins.member_iterator();

  while(!ltoi_mins_itr->is_done())
  {
    cout << " " << ltoi_mins_itr->index().pod();
    ltoi_mins_itr->next();
  }

  cout << "\nshould be:\n";
  cout << " 6 7 8\n";
  cout << "##### end   subposet minimals TRIORDER_ITERATOR preorder test at version 0 #####" << endl;

  // Delete ltoi_mins; it was just a temporary.

  ltoi_mins.delete_state();

  cout << "\n##### begin unfiltered BIORDER_ITERATOR postvisit test at version 0 #####\n";
  biorder_iterator bi_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!bi_itr.is_done())
  {
    switch(bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      cout << " " << bi_itr.index().pod();
      break;
    default:
      break;
    }
    bi_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2 1\n";
  cout << "##### end   unfiltered BIORDER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered strict down set BIORDER_ITERATOR postvisit test at version 0 #####\n";
  bi_itr.put_strict(true);
  bi_itr.reset();
  while(!bi_itr.is_done())
  {
    switch(bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      cout << " " << bi_itr.index().pod();
      break;
    default:
      break;
    }
    bi_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 0 6 7 3 8 4 5 2\n";
  cout << "##### end   unfiltered strict down set BIORDER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered strict up set BIORDER_ITERATOR postvisit test at version 0 #####\n";
  bi_itr.put_descending(false);
  bi_itr.put_anchor(&v0);
  bi_itr.reset();
  while(!bi_itr.is_done())
  {
    switch(bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      cout << " " << bi_itr.index().pod();
      break;
    default:
      break;
    }
    bi_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 1 2 3 4\n";
  cout << "##### end   unfiltered strict up set BIORDER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin filtered BIORDER_ITERATOR postvisit test at version 0 #####\n";
  bi_itr.put_descending(true);
  bi_itr.put_strict(false);
  bi_itr.put_anchor(&(refinable_triangle->top()));
  bi_itr.put_filter("__vertices");
  bi_itr.reset();
  while(!bi_itr.is_done())
  {
    switch(bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      cout << " " << bi_itr.index().pod();
      break;
    default:
      break;
    }
    bi_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 6 7 8\n";
  cout << "##### end   filtered BIORDER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered BIORDER_ITERATOR preorder test at version 0 #####\n";
  bi_itr.put_anchor(&(refinable_triangle->top()));
  bi_itr.put_filter(refinable_triangle->whole());
  bi_itr.reset();
  while(!bi_itr.is_done())
  {
    switch(bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      cout << " " << bi_itr.index().pod();
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    bi_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 1 2 3 6 0 7 4 8 5\n";
  cout << "##### end   unfiltered BIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin filtered BIORDER_ITERATOR preorder test at version 0 #####\n";
  bi_itr.put_anchor(&(refinable_triangle->top()));
  bi_itr.put_filter(*n_cells);
  bi_itr.reset();
  while(!bi_itr.is_done())
  {
    switch(bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      cout << " " << bi_itr.index().pod();
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    bi_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 6 7 4 8 5\n";
  cout << "##### end   filtered BIORDER_ITERATOR preorder test at version at version 0 #####\n\n";


  cout << "##### begin truncated filtered BIORDER_ITERATOR preorder test at version 0 #####\n";
  bi_itr.reset();
  while(!bi_itr.is_done())
  {
    switch(bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      cout << " " << bi_itr.index().pod();
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    bi_itr.truncate();
  }
  cout << "\nshould be:\n";
  cout << " 3 4 5\n";
  cout << "##### end   truncated filtered BIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin strict down set BIORDER_ITERATOR preorder test at version 0 #####\n";
  bi_itr.put_strict(true);
  bi_itr.put_anchor(&(refinable_triangle->top()));
  bi_itr.reset();
  while(!bi_itr.is_done())
  {
    switch(bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      cout << " " << bi_itr.index().pod();
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    bi_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 2 3 6 0 7 4 8 5\n";
  cout << "##### end   strict down set BIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin strict up set BIORDER_ITERATOR preorder test at version 0 #####\n";
  biorder_iterator strict_bi_itr(v0, "", UP, STRICT);
  while(!strict_bi_itr.is_done())
  {
    switch(strict_bi_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      cout << " " << strict_bi_itr.index().pod();
      break;
    case biorder_iterator::POSTVISIT_ACTION:
      break;
    default:
      break;
    }
    strict_bi_itr.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 2 1 4\n";
  cout << "##### end   strict up set BIORDER_ITERATOR preorder test at version 0 #####\n\n";


  cout << "##### begin subposet minimals BIORDER_ITERATOR preorder test at version 0 #####\n";

  // Find minimal members of subposet n_cells

  subposet lboi_mins(refinable_triangle);

  biorder_iterator ext_bi_itr(refinable_triangle->top(), "", UP, STRICT);

  sp_itr = n_cells->member_iterator();
  while(!sp_itr->is_done())
  {
    if(!ext_bi_itr.has_visited(sp_itr))
    {
      // Current member is not bounded some
      // member that has already been visited so
      // assume it is extremal

      lboi_mins.insert_member(sp_itr);

      // Members of the strict down/up-set of current
      // can not be extremal, remove them from result.
      // (Removing non-members doesn't hurt.)
      // By not reseting the visited markers, we ensure
      // that we only traverse the down/up-set of each member
      // once and we don't reinsert some member that has
      // already been removed from the result.

      ext_bi_itr.put_anchor(sp_itr);
      ext_bi_itr.reset(NO_RESET);
      while(!ext_bi_itr.is_done())
      {
        if(ext_bi_itr.action() == biorder_iterator::PREVISIT_ACTION)
        {
          lboi_mins.remove_member(ext_bi_itr.index().pod());
        }
        ext_bi_itr.next();
      }
    }
    sp_itr->next();
  }

  subposet_member_iterator* lboi_mins_itr = lboi_mins.member_iterator();

  while(!lboi_mins_itr->is_done())
  {
    cout << " " << lboi_mins_itr->index().pod();
    lboi_mins_itr->next();
  }

  cout << "\nshould be:\n";
  cout << " 6 7 8\n";

  // Test the reset function:

  cout << "Reset iterator and print result again:" << endl;

  lboi_mins_itr->reset();
  while(!lboi_mins_itr->is_done())
  {
    cout << " " << lboi_mins_itr->index().pod();
    lboi_mins_itr->next();
  }

  cout << endl
  << "##### end   subposet minimals BIORDER_ITERATOR preorder test at version 0 #####"
  << endl;

  // Delete lboi_mins; it was just a temporary.

  lboi_mins.delete_state();


  cout << "\n##### begin unfiltered LINKORDER_ITERATOR linkorder test at version 0 #####\n";
  linkorder_iterator link_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!link_itr.is_done())
  {
    cout << " " << link_itr.lesser_index().pod() << "->" << link_itr.greater_index().pod();
    link_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 0->6 6->3 0->7 7->3 3->2 6->4 0->8 8->4 4->2 7->5 8->5 5->2 2->1\n";
  cout << "##### end   unfiltered LINKORDER_ITERATOR linkorder test at version 0 #####\n\n";


  cout << "##### begin filtered LINKORDER_ITERATOR linkorder test at version 0 #####\n";
  link_itr.put_anchor(&(refinable_triangle->top()));
  link_itr.put_filter("__vertices");
  link_itr.reset();
  while(!link_itr.is_done())
  {
    cout << " " << link_itr.lesser_index().pod() << "->" << link_itr.greater_index().pod();
    link_itr.next();
  }

  cout << "\nshould be:\n";
  cout << " 0->6 0->7 0->8\n";
  cout << "##### end   filtered LINKORDER_ITERATOR linkorder test at version 0 #####\n\n";


  // Detach so destructor won't complain about needing write access.

  v0.detach_from_state();

}

///
/// Test creating version 0 of the triangle mesh after refinement.
///
void
test_level_0_after_refinement()
{
  // Preconditions:

  // Body:

  refinable_triangle->get_read_access();

  refinable_triangle->put_version(0);

  cout << "\n##### begin unfiltered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";

  postorder_member_iterator post_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 0 3 4 5 6 7 8 9 2 1\n"
  << "##### end   unfiltered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin unfiltered strict down set POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";

  post_itr.put_strict(true);
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 0 3 4 5 6 7 8 9 2\n"
  << "##### end   unfiltered strict down set POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin unfiltered strict up set POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";

  // Iterate over strict up set of vertex 0

  total_poset_member v0(refinable_triangle, "vertex 0");
  post_itr.put_descending(false);
  post_itr.put_anchor(&v0);
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 1 2 9 8 5\n"
  << "##### end   unfiltered strict up set POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin filtered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";

  post_itr.put_descending(true);
  post_itr.put_strict(false);
  post_itr.put_anchor(&(refinable_triangle->top()));
  post_itr.put_filter("__vertices");
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 3 4 6\n"
  << "##### end   filtered POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin filtered link POSTORDER_MEMBER_ITERATOR test at version 0 #####\n";

  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " "
    << post_itr.lesser_index().pod()
    << "->"
    << post_itr.greater_index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 3->11 4->12 6->7\n"
  << "##### end   filtered link POSTORDER_MEMBER_ITERATOR test at version 0 #####\n\n";


  cout << "##### begin unfiltered PREORDER_MEMBER_ITERATOR test at version 0 #####\n";

  preorder_member_iterator pre_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }

  cout << "\nshould be:\n"
  << " 1 2 9 5 3 0 4 7 6 8\n"
  << "##### end   unfiltered PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin filtered PREORDER_MEMBER_ITERATOR test at version 0 #####\n";

  pre_itr.put_anchor(&(refinable_triangle->top()));
  pre_itr.put_filter(*n_cells);
  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }

  cout << "\nshould be:\n"
  << " 9 5 3 4 7 6 8\n"
  << "##### end   filtered PREORDER_MEMBER_ITERATOR test at version at version 0 #####\n\n"
  << "##### begin filtered link PREORDER_MEMBER_ITERATOR test at version 0 #####\n";

  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.lesser_index().pod() << "->" << pre_itr.greater_index().pod();
    pre_itr.next();
  }

  cout << "\nshould be:\n"
  << " 9->2 5->9 3->11 4->12 7->15 6->7 8->14\n"
  << "##### end   filtered link PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin truncated filtered PREORDER_MEMBER_ITERATOR test at version 0 #####\n";

  // Iterate over maximum members of n_cells

  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.truncate();
  }

  cout << "\nshould be:\n"
  << " 9\n"
  << "##### end   truncated filtered PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin strict down set PREORDER_MEMBER_ITERATOR test at version 0 #####\n";

  // Iterate over strict down set of triangle

  pre_itr.put_strict(true);
  pre_itr.put_anchor(&(refinable_triangle->top()));
  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }

  cout << "\nshould be:\n"
  << " 2 9 5 3 0 4 7 6 8\n"
  << "##### end   strict down set PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin strict up set PREORDER_MEMBER_ITERATOR test at version 0 #####\n";

  // Iterate over strict up set of vertex 0

  preorder_member_iterator strict_itr(v0, "", UP, STRICT);
  while(!strict_itr.is_done())
  {
    cout << " " << strict_itr.item().index().pod();
    strict_itr.next();
  }

  cout << "\nshould be:\n"
  << " 8 9 2 1 5\n"
  << "##### end   strict up set PREORDER_MEMBER_ITERATOR test at version 0 #####\n\n"
  << "##### begin subposet minimals PREORDER_MEMBER_ITERATOR test at version 0 #####\n";

  // Find minimal members of subposet n_cells

  subposet lmins(refinable_triangle);

  preorder_member_iterator ext_itr(refinable_triangle->top(), "", UP, STRICT);

  subposet_member_iterator* sp_itr = n_cells->member_iterator();
  while(!sp_itr->is_done())
  {
    if(!ext_itr.has_visited(*sp_itr))
    {
      // Current member is not bounded some
      // member that has already been visited so
      // assume it is extremal

      lmins.insert_member(sp_itr);

      // Members of the strict down/up-set of current
      // can not be extremal, remove them from result.
      // (Removing non-members doesn't hurt.)
      // By not reseting the visited markers, we ensure
      // that we only traverse the down/up-set of each member
      // once and we don't reinsert some member that has
      // already been removed from the result.

      ext_itr.put_anchor(sp_itr);
      ext_itr.reset(sheaf::NO_RESET);
      while(!ext_itr.is_done())
      {
        lmins.remove_member(ext_itr.item().index().pod());
        ext_itr.next();
      }
    }
    sp_itr->next();
  }



  subposet_member_iterator* lmins_itr = lmins.member_iterator();

  while(!lmins_itr->is_done())
  {
    cout << " " << lmins_itr->index().pod();
    lmins_itr->next();
  }

  cout << "\nshould be:\n"
  << " 3 4 6\n"
  << "##### end   subposet minimals PREORDER_MEMBER_ITERATOR test at version 0 #####"
  << endl;

  // Delete lmins; it was just a temporary.
  lmins.delete_state();

  // Detach so destructor won't complain about needing write access.

  v0.detach_from_state();

}

///
/// Test version 1 of the triangle mesh.
///
void
test_level_1()
{
  // Preconditions:

  // Body:

  refinable_triangle->get_read_access();

  refinable_triangle->put_version(1);

  cout << "\n##### begin unfiltered POSTORDER_MEMBER_ITERATOR test at version 1 #####\n";

  postorder_member_iterator post_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 0 3 10 11 4 12 5 6 7 13 15 8 14 9 2 1\n"
  << "##### end   unfiltered POSTORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin unfiltered strict down set POSTORDER_MEMBER_ITERATOR test at version 1 #####\n";

  post_itr.put_strict(true);
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 0 3 10 11 4 12 5 6 7 13 15 8 14 9 2\n"
  << "##### end   unfiltered strict down set POSTORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin unfiltered strict up set POSTORDER_MEMBER_ITERATOR test at version 1 #####\n";

  // Iterate over strict up set of vertex 0

  total_poset_member v0(refinable_triangle, "vertex 0");
  post_itr.put_descending(false);
  post_itr.put_anchor(&v0);
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 1 2 9 14 8 5 11\n"
  << "##### end   unfiltered strict up set POSTORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin filtered POSTORDER_MEMBER_ITERATOR test at version 1 #####\n";

  post_itr.put_descending(true);
  post_itr.put_strict(false);
  post_itr.put_anchor(&(refinable_triangle->top()));
  post_itr.put_filter("__vertices");
  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " " << post_itr.item().index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 3 10 4 6\n"
  << "##### end   filtered POSTORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin filtered link POSTORDER_MEMBER_ITERATOR test at version 1 #####\n";

  post_itr.reset();
  while(!post_itr.is_done())
  {
    cout << " "
    << post_itr.lesser_index().pod()
    << "->"
    << post_itr.greater_index().pod();
    post_itr.next();
  }

  cout << "\nshould be:\n"
  << " 3->11 10->11 4->12 6->7\n"
  << "##### end   filtered link POSTORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin unfiltered PREORDER_MEMBER_ITERATOR test at version 1 #####\n";

  preorder_member_iterator pre_itr(refinable_triangle->top(), DOWN, NOT_STRICT);
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }

  cout << "\nshould be:\n"
  << " 1 2 9 5 11 3 0 10 12 4 15 7 6 13 14 8\n"
  << "##### end   unfiltered PREORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin filtered PREORDER_MEMBER_ITERATOR test at version 1 #####\n";

  pre_itr.put_anchor(&(refinable_triangle->top()));
  pre_itr.put_filter(*n_cells);
  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }

  cout << "\nshould be:\n"
  << " 9 5 11 3 10 12 4 15 7 6 13 14 8\n"
  << "##### end   filtered PREORDER_MEMBER_ITERATOR test at version at version 1 #####\n\n"
  << "##### begin filtered link PREORDER_MEMBER_ITERATOR test at version 1 #####\n";

  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.lesser_index().pod() << "->" << pre_itr.greater_index().pod();
    pre_itr.next();
  }

  cout << "\nshould be:\n"
  << " 9->2 5->9 11->5 3->11 10->11 12->5 4->12 15->9 7->15 6->7 13->15 14->9 8->14\n"
  << "##### end   filtered link PREORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin truncated filtered PREORDER_MEMBER_ITERATOR test at version 1 #####\n";

  // Iterate over maximum members of n_cells

  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.truncate();
  }

  cout << "\nshould be:\n"
  << " 9\n"
  << "##### end   truncated filtered PREORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin strict down set PREORDER_MEMBER_ITERATOR test at version 1 #####\n";

  // Iterate over strict down set of triangle

  pre_itr.put_strict(true);
  pre_itr.put_anchor(&(refinable_triangle->top()));
  pre_itr.reset();
  while(!pre_itr.is_done())
  {
    cout << " " << pre_itr.item().index().pod();
    pre_itr.next();
  }

  cout << "\nshould be:\n"
  << " 2 9 5 11 3 0 10 12 4 15 7 6 13 14 8\n"
  << "##### end   strict down set PREORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin strict up set PREORDER_MEMBER_ITERATOR test at version 1 #####\n";

  // Iterate over strict up set of vertex 0

  pre_itr.put_descending(false);
  preorder_member_iterator strict_itr(v0, DOWN, NOT_STRICT);
  while(!strict_itr.is_done())
  {
    cout << " " << strict_itr.item().index().pod();
    strict_itr.next();
  }

  cout << "\nshould be:\n"
  << " 8 14 9 2 1 11 5\n"
  << "##### end   strict up set PREORDER_MEMBER_ITERATOR test at version 1 #####\n\n"
  << "##### begin subposet minimals PREORDER_MEMBER_ITERATOR test at version 1 #####\n";

  // Find minimal members of subposet n_cells:

  subposet lmins(refinable_triangle);  // a new subposet to hold the result

  preorder_member_iterator ext_itr(refinable_triangle->top(), "", UP, STRICT);

  subposet_member_iterator* sp_itr = n_cells->member_iterator();

  /// @issue n_cells may contain a member not contained in
  /// the current version.  This member gets put into lmins, which
  /// is wrong.  We want to be able to filter out such members, but it's not
  /// obvious how to do so.

  while(!sp_itr->is_done())
  {
    if(!ext_itr.has_visited(*sp_itr))
    {
      // Current member is not bounded by some
      // member that has already been visited so
      // assume it is extremal.  At least it's a
      // candidate.  If not extremal it will be
      // removed in the while loop below.

      lmins.insert_member(sp_itr);

      // Members of the strict down/up-set of current
      // can not be extremal, remove them from result.
      // (Removing non-members doesn't hurt.)
      // By not resetting the visited markers, we ensure
      // that we only traverse the down/up-set of each member
      // once and we don't reinsert some member that has
      // already been removed from the result.

      ext_itr.put_anchor(sp_itr);
      ext_itr.reset(sheaf::NO_RESET);
      while(!ext_itr.is_done())
      {
        lmins.remove_member(ext_itr.item().index().pod());
        ext_itr.next();
      }
    }
    sp_itr->next();
  }

  subposet_member_iterator* lmins_itr = lmins.member_iterator();

  while(!lmins_itr->is_done())
  {
    cout << " " << lmins_itr->index().pod();
    lmins_itr->next();
  }

  cout << "\nshould be:\n"
  << " 3 4 6 10\n"
  << endl;

  // Test the reset function:

  cout << "Reset iterator and print result again:" << endl;

  lmins_itr->reset();
  while(!lmins_itr->is_done())
  {
    cout << " " << lmins_itr->index().pod();
    lmins_itr->next();
  }

  cout << endl
  << "##### end   subposet minimals PREORDER_MEMBER_ITERATOR test at version 1 #####"
  << endl;

  // Delete lmins; it was just a temporary.

  lmins.delete_state();

  // Detach so destructor won't complain about needing write access.

  v0.detach_from_state();

}

///
/// The main routine for this test driver.
///
int
main()
{

  make_refinable_triangle();

  // Makes a single triangle poset and subposet of vertices.

  //  cout << *refinable_triangle << endl;

  test_level_0_before_refinement();

  //   test_deletion();

  //   // Refine the single triangle poset into 2 triangles.

  //   refine();

  //   cout << *refinable_triangle << endl;

  //   test_level_1();

  //   test_level_0_after_refinement();

}
