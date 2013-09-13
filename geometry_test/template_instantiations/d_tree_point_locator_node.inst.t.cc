
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
/// Unit test driver for class d_tree_point_locator_node.

#include "d_tree_point_locator_node.h"

#include "test_utils.h"

#include "std_iostream.h"
#include "std_iomanip.h"

namespace
{

using namespace geometry;


//$$TODO: Move to test_geometry.impl.h.

///
/// Simple derived class for d_tree_point_locator_node with only
/// a default constructor and destructor.
///
template<int DC, int DB>
class d_tree_point_locator_node_child
  : public d_tree_point_locator_node<DC, DB>
{
public:
  d_tree_point_locator_node_child() {}
  ~d_tree_point_locator_node_child() {}
};

template<int DC, int DB>
bool
test_d_tree_point_locator_node_facet()
{
  // Preconditions:

  // Body:

  print_subheader("Testing d_tree_point_locator_node();");

  d_tree_point_locator_node<DC, DB> lnode;

  print_subheader("Testing d_tree_point_locator_node(",
                  "    const d_tree_point_locator_node<DC, DB>& xother)");

  d_tree_point_locator_node<DC, DB> lnode_copy(lnode);

  print_subheader("Testing d_tree_point_locator_node<DC, DB>& operator=(",
                  "    const d_tree_point_locator_node<DC, DB>& xother)");

  d_tree_point_locator_node<DC, DB> lnode_assign = lnode;

  print_subheader("Testing bool operator==(",
                  "    const d_tree_point_locator_node<DC, DB>& xother)");

  bool lequal = (lnode_copy == lnode);
  cout << "lequal = " << boolalpha << lequal << endl;

  // Equal to self.
  lequal = (lnode == lnode);
  cout << "lequal = " << boolalpha << lequal << endl;

  print_subheader("Testing bool invariant() const");

  bool linvariant = lnode.invariant();
  cout << "lnode.invariant() = " << boolalpha << linvariant << endl;

  print_subheader("Testing bool is_leaf() const");

  bool lis_leaf = lnode.is_leaf();
  cout << "lnode.is_leaf() = " << boolalpha << lis_leaf << endl;

  print_subheader("Testing bool is_empty() const");

  bool lis_empty = lnode.is_empty();
  cout << "lnode.is_empty() = " << boolalpha << lis_empty << endl;

  print_subheader("Testing static size_type degree()");

  size_type ldegree = lnode.degree();
  cout << "lnode.degree() = " << ldegree << endl;

  print_subheader("Testing size_type branch_ct() const");

  size_type lbranch_ct = lnode.branch_ct();
  cout << "lnode.branch_ct() = " << lbranch_ct << endl;

  print_subheader("Testing string* to_string() const");

  string* lstring = lnode.to_string();
  cout << "*lstring = " << *lstring << endl;

  print_subheader("Testing operator<<");

  cout << endl;
  cout << lnode << endl;
  cout << endl;

  print_subheader("Testing void clear()");

  lnode.clear();

  //============================================================================

  print_subheader("Testing d_tree_point_locator_node<DC, DB>* branch(",
                  "    int xindex) const");

  d_tree_point_locator_node<DC, DB>* lbranch = lnode.branch(0);
  cout << "lbranch = " << lbranch << endl;


  print_subheader("Testing const box_list_type& box_list(",
                  "    d_tree_point_locator_path<DC, DB>& xpath) const");

  typedef slist<const d_bounding_box<DC, DB>*> box_list_type;
  const box_list_type& lbox_list = lnode.box_list();


  //$$SCRIBBLE: Need a d_tree_point_locator_path object to
  //            invoke these functions.  They are tested in
  //            d_tree_point_locator.inst.t where we create
  //            d_tree_point_locator_paths from instances of
  //            d_tree_point_locator.


//   void insert_box(const d_bounding_box<DC, DB>* xbox,
//                   d_tree_point_locator_path<DC, DB>& xpath);

//   void remove_box(const d_bounding_box<DC, DB>* xbox,
//                   d_tree_point_locator_path<DC, DB>& xpath);

//   bool contains_box(const d_bounding_box<DC, DB>* xbox,
//                     d_tree_point_locator_path<DC, DB>& xpath) const;

//   const box_list_type&
//     box_list(d_tree_point_locator_path<DC, DB>& xpath) const;

  //============================================================================

  print_subheader("Testing derived class CTOR/DTOR");

  d_tree_point_locator_node_child<DC, DB>* lchild =
    new d_tree_point_locator_node_child<DC, DB>;

  delete lchild;

  //============================================================================

  // Postconditions:

  // Exit:

  return true;
}

} //end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing d_tree_point_locator_node_facet");

  bool ltest = true;

  //============================================================================

  print_header("Testing _d_tree_point_locator_node_facet<1, 1>");
  ltest &= test_d_tree_point_locator_node_facet<1, 1>();

  print_header("Testing _d_tree_point_locator_node_facet<2, 2>");
  ltest &= test_d_tree_point_locator_node_facet<2, 2>();

  print_header("Testing _d_tree_point_locator_node_facet<3, 3>");
  ltest &= test_d_tree_point_locator_node_facet<3, 3>();

  // Not instantiated because we cant make a d_tree_point_locator<4, 4>
  //print_header("Testing _d_tree_point_locator_node_facet<4, 4>");
  //ltest &= test_d_tree_point_locator_node_facet<4, 4>();

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing d_tree_point_locator_node_facet");

  // Postconditions:

  // Exit:

  return lresult;
}
