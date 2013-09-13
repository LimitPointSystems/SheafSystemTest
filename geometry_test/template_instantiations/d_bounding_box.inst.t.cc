
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

/// @example
/// Unit test driver for class d_bounding_box.

#include "d_bounding_box.h"

#include "constant_quad.h"  // concrete section_evaluator
#include "d_bin_coordinates.h"
#include "geometry.h"
#include "geometry_namespace.h"
#include "test_utils.h"

using namespace geometry;

namespace
{
template<int DC, int DB>
class d_bounding_box_child : public d_bounding_box<DC, DB>
{
public:
  d_bounding_box_child() {}
  ~d_bounding_box_child() {}
};

template<int DC, int DB>
bool
test_d_bounding_box_ctors_dtors()
{
  d_bounding_box<DC, DB>* lparent = new d_bounding_box<DC, DB>;
  delete lparent;

  d_bounding_box_child<DC, DB>* lchild = new d_bounding_box_child<DC, DB>;
  delete lchild;

  return true;
}

template<int DC, int DB>
bool
test_d_bounding_box_facet()
{
  // Preconditions:

  // Body:

  // Construct a member and branch scoped ids.

  geometry_namespace::initialize_id_space_prototypes();

  index_space_family lid_spaces;
  lid_spaces.new_id(123);
  lid_spaces.new_id(345);

  scoped_index lmember_id(lid_spaces.hub_id_space(), 123);
  scoped_index lbranch_id(lid_spaces.hub_id_space(), 345);

  bool lresult = true;

  print_subheader("Testing d_bounding_box()");

  d_bounding_box<DC, DB> lbox;

  print_subheader("Testing void put_member_id(const scoped_index& xid)");

  lbox.put_member_id(lmember_id);

  print_subheader("Testing scoped_index member_id() const");

  scoped_index lmember_id2 = lbox.member_id();
  cout << "lmember_id2 = " << lmember_id2 << endl;

  print_subheader("Testing void put_branch_id(const scoped_index& xid)");

  lbox.put_branch_id(lbranch_id);

  print_subheader("Testing scoped_index branch_id() const");

  scoped_index lbranch_id2 = lbox.branch_id();
  cout << "lbranch_id2 = " << lbranch_id2 << endl;

  print_subheader("Testing ostream& operator<<(ostream& xos, const d_bounding_box<DC, DB>& xbox)");

  cout << lbox << endl;

  //============================================================================

  print_subheader("Testing d_bounding_box(const d_bounding_box<DC, DB>& xbox)");

  d_bounding_box<DC, DB> lbox2(lbox);

  cout << lbox2 << endl;

  print_subheader("Testing d_bounding_box<DC, DB>& operator=(const d_bounding_box<DC, DB>& xbox)");

  d_bounding_box<DC, DB> lbox3 = lbox2;

  cout << lbox3 << endl;

  print_subheader("Testing d_bounding_box<DC, DB>* = new d_bounding_box<DC, DB>()");

  d_bounding_box<DC, DB>* lbox_ptr = new d_bounding_box<DC, DB>();

  cout << *lbox_ptr << endl;

  print_subheader("Testing  d_bounding_box<DC, DB>* = new d_bounding_box<DC, DB>(const d_bounding_box<DC, DB>& xbox)");

  d_bounding_box<DC, DB>* lbox_ptr2 = new d_bounding_box<DC, DB>(lbox);

  cout << *lbox_ptr2 << endl;

  print_subheader("Testing bool operator==(const d_bounding_box<DC, DB>& xbox) const");

  bool lequal = (lbox == lbox2);
  cout << "lequal = " << boolalpha << lequal << endl;

  //============================================================================


  print_subheader("Testing static int dc()");

  int ldc = lbox.dc();
  cout << "ldc = " << ldc << endl;

  print_subheader("Testing void size_pa(d_bin_coordinates<DC, DB>& xresult) const");

  d_bin_coordinates<DC, DB> lcoords;
  lbox.size_pa(lcoords);
  cout << "lcoords = " << lcoords << endl;

  print_subheader("Testing bool contains_point(const d_bin_coordinates<DC, DB>& xpt) const");

  bool lcontains_point = lbox.contains_point(lcoords);
  cout << "lcontains_point = " << boolalpha << lcontains_point << endl;

  // Setting the upper and lower bounds to the same (doesn't matter
  // for purposes of just successfully calling the put_lb/_ub functions.

  print_subheader("Testing void put_lb(const d_bin_coordinates<DC, DB>& xlb)");

  lbox.put_lb(lcoords);

  print_subheader("Testing const d_bin_coordinates<DC, DB>& lb() const");

  const d_bin_coordinates<DC, DB>& lcoords_lb = lbox.lb();
  cout << "lcoords_lb = " << lcoords_lb << endl;

  print_subheader("Testing void put_ub(const d_bin_coordinates<DC, DB>& xub)");

  lbox.put_ub(lcoords);

  print_subheader("Testing const d_bin_coordinates<DC, DB>& ub() const");

  const d_bin_coordinates<DC, DB>& lcoords_ub = lbox.ub();
  cout << "lcoords_ub = " << lcoords_ub << endl;

  print_subheader("Testing void put_dof_ct(size_type xct)");

  lbox.put_dof_ct(8);

  print_subheader("Testing size_type dof_ct() const");

  size_type ldoc_ct = lbox.dof_ct();
  cout << "ldoc_ct = " << ldoc_ct << endl;

  print_subheader("Testing void put_dofs_index(size_type xindex)");

  lbox.put_dofs_index(16);

  print_subheader("Testing size_type dofs_index() const");

  size_type ldofs_index = lbox.dofs_index();
  cout << "ldofs_index = " << ldofs_index << endl;

  //============================================================================

  // Just pick any evaluator.

  print_subheader("Testing void put_evaluator(section_evaluator* xevaluator);");

  constant_quad leval;
  lbox.put_evaluator(&leval);

  print_subheader("Testing section_evaluator* evaluator() const");

  section_evaluator* leval_ptr = lbox.evaluator();
  cout << "leval_ptr = " << leval_ptr << endl;

  //============================================================================

  // Cleanup:

  print_subheader("Testing ~d_bounding_box() via delete");

  delete lbox_ptr;
  delete lbox_ptr2;

  //============================================================================

 // Postconditions:

  // Exit:

  return lresult;
}

} //end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing d_bounding_box_facet<DB, DC>:");

  bool ltest = true;

  //============================================================================

  print_header("Testing d_bounding_box_facet<1, 0>:");
  ltest &= test_d_bounding_box_ctors_dtors<1, 0>();
  ltest &= test_d_bounding_box_facet<1, 0>();

  print_header("Testing d_bounding_box_facet<1, 1>:");
  ltest &= test_d_bounding_box_ctors_dtors<1, 1>();
  ltest &= test_d_bounding_box_facet<1, 1>();

  print_header("Testing d_bounding_box_facet<2, 0>:");
  ltest &= test_d_bounding_box_ctors_dtors<2, 0>();
  ltest &= test_d_bounding_box_facet<2, 0>();

  print_header("Testing d_bounding_box_facet<2, 2>:");
  ltest &= test_d_bounding_box_ctors_dtors<2, 2>();
  ltest &= test_d_bounding_box_facet<2, 2>();

  print_header("Testing d_bounding_box_facet<3, 0>:");
  ltest &= test_d_bounding_box_ctors_dtors<3, 0>();
  ltest &= test_d_bounding_box_facet<3, 0>();

  print_header("Testing d_bounding_box_facet<3, 1>:");
  ltest &= test_d_bounding_box_ctors_dtors<3, 1>();
  ltest &= test_d_bounding_box_facet<3, 1>();

  print_header("Testing d_bounding_box_facet<3, 2>:");
  ltest &= test_d_bounding_box_ctors_dtors<3, 2>();
  ltest &= test_d_bounding_box_facet<3, 2>();

  print_header("Testing d_bounding_box_facet<3, 3>:");
  ltest &= test_d_bounding_box_ctors_dtors<3, 3>();
  ltest &= test_d_bounding_box_facet<3, 3>();

  print_header("Testing d_bounding_box_facet<4, 4>:");
  ltest &= test_d_bounding_box_ctors_dtors<4, 4>();
  ltest &= test_d_bounding_box_facet<4, 4>();

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing d_bounding_box_facet<DB, DC>:");

  // Postconditions:

  // Exit:

  return lresult;
}
