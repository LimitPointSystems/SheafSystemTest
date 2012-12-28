
// $RCSfile: test_sheaves.cc,v $ $Revision: 1.1.2.9 $ $Date: 2012/11/16 00:14:31 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @file
/// Implementation for sheaves test template specializations
//  and non template functions.

#include "test_sheaves.impl.h"
#include "test_utils.h"

#include "hub_index_space_handle.h"
#include "index_space_handle.h"
#include "namespace_poset.h"
#include "namespace_poset_member.h"
#include "poset_state_handle.h"
#include "refinable_poset.h"
#include "schema_descriptor.h"
#include "test_utils.h"
#include "total_poset_member.h"
#include "wsv_block.h"

//=============================================================================
// BLOCK FACET
//=============================================================================

//===========================================================================
// Specialization for "poset_state_handle*":
//===========================================================================

template<>
bool
sheaf::
test_block_facet<sheaf::poset_state_handle*>()
{
  // Preconditions:

  // Body:

  typedef poset_state_handle* T;

  // Get a pointer to a poset_state_handle.
  // Class namespace_poset has a public constructor and
  // is a poset_state_handle; so use it.

  namespace_poset lns("test_namespace");
  lns.get_read_write_access();
  T lpsh = &lns;

  print_header("Begin testing \"block\" facet:");

  print_subheader("Test block(index_type xub)");

  block<T> lblock0(5);

  cout << lblock0 << endl;

  print_subheader("Test new block<T>");
  block<T>* lblock_ptr = new block<T>();
  cout << *lblock_ptr << endl;
  delete lblock_ptr;


  print_subheader("Test block(index_type xub, size_type xct, const T* xitems)");

  poset_state_handle* lpshs[5] = {lpsh, lpsh, lpsh, lpsh, lpsh};
  block<T> lblock1(10, 5, lpshs);

  cout << lblock1 << endl;

  print_subheader("Test block(const block& xother)");

  block<T> lblock2(lblock1);

  cout << lblock2 << endl;

  print_subheader("Test block& operator=(const block& xother)");

  block<T> lblock3;
  lblock3 = lblock2;

  cout << lblock3 << endl;

  print_subheader("Test bool operator==(const block<T>& xblk1, const block<T>& xblk2)");

//   bool ltest = (lblock3 == lblock2);
//   cout << "  Test for equality: " << boolalpha << ltest << endl;

  // Test "deep_size":

  //test_deep_size(lblock3);

  print_footer("End testing \"block\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//===========================================================================
// Specialization for "index_space_handle*":
//===========================================================================

template<>
bool
sheaf::
test_block_facet<sheaf::index_space_handle*>()
{
  // Preconditions:

  // Body:

  print_header("Begin testing \"block\" facet:");

  print_subheader("Test block(index_type xub)");

  typedef index_space_handle* T;

  block<T> lblock0(5);

  //cout << lblock0 << endl;

  print_subheader("Test new block<T>");
  block<T>* lblock_ptr = new block<T>();
  //cout << *lblock_ptr << endl;
  delete lblock_ptr;


  print_subheader("Test block(index_type xub, size_type xct, const T *xitems)");

  // Need to create an index space (abstract class).
  // Use index_space_family.hub_id_space().

  sheaf::index_space_family lid_spaces;
  sheaf::hub_index_space_handle& lhub_id_space =
    const_cast<hub_index_space_handle&>(lid_spaces.hub_id_space());
 
  T litem0 = &lhub_id_space;
  T litem1 = &lhub_id_space; 
  T litems[2] = {litem0, litem1};

  block<T> lblock1(10, 2, litems);

  //cout << lblock1 << endl;

  print_subheader("Test block(const block& xother);)");

  block<T> lblock2(lblock1);

  //cout << lblock2 << endl;

  print_subheader("Test block& operator=(const block& xother)");

  block<T> lblock3;
  lblock3 = lblock2;

  //cout << lblock3 << endl;

  print_subheader("Test bool operator==(const block<T>& xblk1, const block<T>& xblk2)");

  bool ltest = (lblock3 == lblock2);
  cout << "  Test for equality: " << boolalpha << ltest << endl;

  // Test "deep_size":

  //test_deep_size(lblock3);

  print_footer("End testing \"block\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//=============================================================================
// WSV_BLOCK FACET
//=============================================================================

//============================================================================
// Specialization of wsv_block_facet for "bool":
//============================================================================

template <>
bool
sheaf::
test_wsv_block_facet<bool>()
{
  // Preconditions:

  // Body:

  print_header("Begin testing \"wsv_block\" facet:");

  print_subheader("Test wsv_block() - default constructor");

  wsv_block<bool> lblock0;

  cout << lblock0 << endl;

  print_subheader("Test wsv_block(const wsv_block& xother)");

  wsv_block<bool> lblock1(lblock0);

  cout << lblock1 << endl;

  print_subheader("Test wsv_block(const char* xlist)");

  char lcharlist[64] = "true false true";
  wsv_block<bool> lblock2(lcharlist);

  cout << lblock2 << endl;

  print_subheader("Test wsv_block(const string& xlist)");

  const string llist = "false true false";
  //const string llist = "false TRUE false";
  wsv_block<bool> lblock3(llist);

  cout << lblock3 << endl;


  print_subheader("Test  wsv_block& operator=(const wsv_block& xother)");

  wsv_block<bool> lblock4;
  lblock4 = lblock3;

  cout << lblock4 << endl;

  print_subheader("Test  wsv_block& operator=(const string& xlist)");

  const string llist4 = "true true false";
  lblock4 = llist4;

  cout << lblock4 << endl;

  print_subheader("Test wsv_block& operator=(const char* xlist)");

  char lcharlist4[64] = "false false true";
  lblock4 = lcharlist4;

  cout << lblock4 << endl;

  print_subheader("Test bool invariant() const");

  bool ltest = lblock4.invariant();
  cout << "lblock4.invariant() = " << boolalpha << ltest << endl;

  print_subheader("Test void push_back(const wsv_block& xother)");

  lblock4.push_back(lblock2);

  cout << lblock4 << endl;

  print_footer("End testing \"wsv_block\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//============================================================================
// Specialization of wsv_block_facet for "schema_descriptor":
//============================================================================

template <>
bool
sheaf::
test_wsv_block_facet<sheaf::schema_descriptor>()
{
  // Preconditions:

  // Body:

  print_header("Begin testing \"wsv_block\" facet:");

  print_subheader("Test wsv_block() - default constructor");

  wsv_block<sheaf::schema_descriptor> lblock0;

  cout << lblock0 << endl;

  print_subheader("Test wsv_block(const wsv_block& xother)");

  wsv_block<sheaf::schema_descriptor> lblock1(lblock0);

  cout << lblock1 << endl;

  print_subheader("Test wsv_block(const char* xlist)");

  char lcharlist[64] = "abc INT true def DOUBLE false";
  wsv_block<sheaf::schema_descriptor> lblock2(lcharlist);

  cout << lblock2 << endl;

  print_subheader("Test wsv_block(const string& xlist)");

  const string llist = "xxx DOUBLE false yyy DOUBLE false";
  wsv_block<sheaf::schema_descriptor> lblock3(llist);

  cout << lblock3 << endl;

  print_subheader("Test  wsv_block& operator=(const wsv_block& xother)");

  wsv_block<sheaf::schema_descriptor> lblock4;
  lblock4 = lblock3;

  cout << lblock4 << endl;

  print_subheader("Test  wsv_block& operator=(const string& xlist)");

  const string llist4 = "units C_STRING true";
  lblock4 = llist4;

  cout << lblock4 << endl;

  print_subheader("Test wsv_block& operator=(const char* xlist)");

  char lcharlist4[64] = "d INT true";
  lblock4 = lcharlist4;

  cout << lblock4 << endl;

  print_subheader("Test bool invariant() const");

  bool ltest = lblock4.invariant();
  cout << "lblock4.invariant() = " << boolalpha << ltest << endl;

  print_subheader("Test void push_back(const wsv_block& xother)");

  lblock4.push_back(lblock2);

  cout << lblock4 << endl;

  print_footer("End testing \"wsv_block\" facet:");

  // Postconditions:

  // Exit:

  return true;
}

//=============================================================================
// ABSTRACT_POSET_MEMBER FACET
//=============================================================================

bool
sheaf::
test_abstract_poset_member_facet()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  namespace_poset lns("test_namespace");
  lns.get_read_write_access();

  namespace_poset_member lnpm(&lns, "primitives");
  const namespace_poset_member& lnpmc = lnpm;

  lns.begin_jim_edit_mode();

  const string& lname = "abstract_poset_member";

  typedef sheaf::abstract_poset_member P;

  print_subheader("Testing sheaf::row_dofs(" + lname + ")");

  P::row_dofs_type& lrow_dofs0 = sheaf::row_dofs<P>(lnpm);
  P::row_dofs_type& lrow_dofs1 = sheaf::row_dofs<P>(lnpm, true);

  const P::row_dofs_type& lrow_dofs2 = sheaf::row_dofs<P>(lnpmc);
  const P::row_dofs_type& lrow_dofs3 = sheaf::row_dofs<P>(lnpmc, true);

  cout << "&lrow_dofs0 = " << &lrow_dofs0 << endl;
  cout << "&lrow_dofs1 = " << &lrow_dofs1 << endl;
  cout << "&lrow_dofs2 = " << &lrow_dofs2 << endl;
  cout << "&lrow_dofs3 = " << &lrow_dofs3 << endl;

  print_subheader("Testing sheaf::table_dofs(" + lname + ")");

  P::table_dofs_type& ltable_dofs0 = sheaf::table_dofs<P>(lnpm);
  P::table_dofs_type& ltable_dofs1 = sheaf::table_dofs<P>(lnpm, true);

  const P::table_dofs_type& ltable_dofs2 = sheaf::table_dofs<P>(lnpmc);
  const P::table_dofs_type& ltable_dofs3 = sheaf::table_dofs<P>(lnpmc, true);

  cout << "&ltable_dofs0 = " << &ltable_dofs0 << endl;
  cout << "&ltable_dofs1 = " << &ltable_dofs1 << endl;
  cout << "&ltable_dofs2 = " << &ltable_dofs2 << endl;
  cout << "&ltable_dofs3 = " << &ltable_dofs3 << endl;

  lns.end_jim_edit_mode();

  lnpm.detach_from_state();
 
  // Postconditions:

  // Exit:

  return lresult;
}


//============================================================================
// GENERAL FACET
//============================================================================

void
sheaf::
make_triangle_poset(namespace_poset& xns, const string& xname)
{
  //$$SCRIBBLE: This functions is a modified copy of the
  //            static make_triangle function in class sheaves_namespace.
  //            It has been has been put here so that it can easily be
  //            mover to SheafSystemTest.  However, in the future it
  //            should probably be moved somewhere else in SheafSystemTest
  //            since it has nothing to do with template instantiations.
 
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());

  // Body:

  // Make a triangle:


  //       t
  //       *
  //      ***
  //     * * *
  //    *  *  *
  //   *   *   *
  // e0    e1   e2
  // *     *     *
  // **   ***   **
  // * * * * * * *
  // *  *  *  *  *
  // * * * * * * *
  // **   ***   **
  // *     *     *
  // v0    v1   v2


  const poset_path& lref_path = xns.primitives().int_type().path();
  arg_list largs = refinable_poset::make_args();

  refinable_poset& ltriangle =
    xns.new_member_poset<refinable_poset>(xname, lref_path, largs, true);

  ltriangle.begin_jim_edit_mode();

  total_poset_member* t  = new total_poset_member(&ltriangle, 0, false, false);
  t->put_name("standard triangle", true, false);
  int ldof = 4;
  t->put_dof_tuple(&ldof,sizeof(ldof));

  total_poset_member* e0 = new total_poset_member(&ltriangle, 0, false, false);
  e0->put_name("e0", true, false);
  ldof = 3;
  e0->put_dof_tuple(&ldof,sizeof(ldof));

  total_poset_member* e1 = new total_poset_member(&ltriangle, 0, false, false);
  e1->put_name("e1", true, false);
  ldof = 3;
  e1->put_dof_tuple(&ldof,sizeof(ldof));

  total_poset_member* e2 = new total_poset_member(&ltriangle, 0, false, false);
  e2->put_name("e2", true, false);
  ldof = 3;
  e2->put_dof_tuple(&ldof,sizeof(ldof));

  total_poset_member* v0 = new total_poset_member(&ltriangle, 0, false, false);
  v0->put_name("v0", true, false);
  ldof = 2;
  v0->put_dof_tuple(&ldof,sizeof(ldof));

  total_poset_member* v1 = new total_poset_member(&ltriangle, 0, false, false);
  v1->put_name("v1", true, false);
  ldof = 2;
  v1->put_dof_tuple(&ldof,sizeof(ldof));

  total_poset_member* v2 = new total_poset_member(&ltriangle, 0, false, false);
  v2->put_name("v2", true, false);
  ldof = 2;
  v2->put_dof_tuple(&ldof,sizeof(ldof));

  t->create_cover_link(e0);
  t->create_cover_link(e1);
  t->create_cover_link(e2);

  e0->create_cover_link(v0);
  e0->create_cover_link(v1);

  e1->create_cover_link(v0);
  e1->create_cover_link(v2);

  e2->create_cover_link(v1);
  e2->create_cover_link(v2);

  ltriangle.end_jim_edit_mode();

  // Postconditions:

  ensure(xns.contains_poset(xname));

  // Exit:

}
 
//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================

