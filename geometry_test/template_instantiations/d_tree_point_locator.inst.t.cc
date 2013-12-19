
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
/// Unit test driver for class d_tree_point_locator.

#include "d_tree_point_locator.h"
#include "d_tree_point_locator_node.h"
#include "d_tree_point_locator_path.h"

#include "geometry.h"
#include "test_utils.h"

#include "sec_at1_space.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_e4.h"
#include "sec_ed_invertible.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"

#include "geometry.h"
#include "test_utils.h"

#include "std_iomanip.h"
#include "std_sstream.h"


using namespace std;
using namespace geometry;

namespace
{

//==============================================================================

template<int DC, int DB>
class d_tree_point_locator_child : public d_tree_point_locator<DC, DB>
{
public:
  d_tree_point_locator_child(sec_ed& xcoords, size_type xdepth) 
    : d_tree_point_locator<DC, DB>(xcoords, xdepth) {}

  d_tree_point_locator_child(sec_ed& xcoords) 
    : d_tree_point_locator<DC, DB>(xcoords) {}

  ~d_tree_point_locator_child() {}
};


template<int DC, int DB>
class d_tree_point_locator_path_child : public d_tree_point_locator_path<DC, DB>
{
public:
  d_tree_point_locator_path_child(const d_tree_point_locator<DC, DB>* xtree) 
    : d_tree_point_locator_path<DC, DB>(xtree) {}
  
  ~d_tree_point_locator_path_child() {}
};

//==============================================================================

void
make_names_unique(string xnames[], int xnum_names)
{
  // Preconditions:

  require(unexecutable("xnum_names <= dimension of xnames"));

  // Body:

  // Make names "unique" by appending "_#" to each name.

  static int lname_suffix = -1;
  lname_suffix++;

  static ostringstream lname;

  for(int i=0; i<xnum_names; ++i)
  {
    lname.str("");
    lname << xnames[i] << "_" << lname_suffix;
    xnames[i] = lname.str();
  }

  // Postconditions:

  // Exit:

  return;
}

//==============================================================================

poset_path
make_base_space_1d(fiber_bundles_namespace& xns, const string& xbase_space_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xbase_space_name.empty());

  // Body:

  typedef structured_block_1d B;
    
  base_space_poset& lhost = B::standard_host(xns, xbase_space_name, false);

  B lmesh(&lhost, 2, true);
  lmesh.put_name("mesh", true, true);

  poset_path result = lmesh.path(true);
    
  lmesh.detach_from_state();

  // Postconditions:

  ensure(!result.empty());
  //+ other ensure(...)

  // Exit:
    
  return result;
}

poset_path
make_base_space_2d(fiber_bundles_namespace& xns, const string& xbase_space_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xbase_space_name.empty());

  // Body:

  typedef structured_block_2d B;
    
  base_space_poset& lhost = B::standard_host(xns, xbase_space_name, false);

  B lmesh(&lhost, 2, 2, true);
  lmesh.put_name("mesh", true, true);

  poset_path result = lmesh.path(true);
    
  lmesh.detach_from_state();

  // Postconditions:

  ensure(!result.empty());
  //+ other ensure(...)

  // Exit:
    
  return result;
}

poset_path
make_base_space_3d(fiber_bundles_namespace& xns, const string& xbase_space_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xbase_space_name.empty());

  // Body:

  typedef structured_block_3d B;
    
  base_space_poset& lhost = B::standard_host(xns, xbase_space_name, false);

  B lmesh(&lhost, 2, 2, 2, true);
  lmesh.put_name("mesh", true, true);

  poset_path result = lmesh.path(true);
    
  lmesh.detach_from_state();

  // Postconditions:

  ensure(!result.empty());
  //+ other ensure(...)

  // Exit:
    
  return result;
}


poset_path
make_base_space(fiber_bundles_namespace& xns,
                const string& xbase_space_name,
                int xd)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xbase_space_name.empty());
  require(1 <= xd && xd <= 3);

  // Body:

  poset_path result;
  if(xd == 1)
  {
    result = make_base_space_1d(xns, xbase_space_name);
  }
  else if (xd == 2)
  {
    result = make_base_space_2d(xns, xbase_space_name);
  }
  else
  {
    result = make_base_space_3d(xns, xbase_space_name);
  }

  // Postconditions:

  ensure(!result.empty());
  //+ other ensure(...)

  // Exit:

  return result;
}

template<typename S>
void
make_dofs(S& xcoords)
{
  // Preconditions:

  // Body:

  typedef typename S::fiber_type::volatile_type volatile_type;

  cout << "volatile_type = " << volatile_type::static_class_name() << endl;

  volatile_type lfiber;
  int ld = lfiber.d();
  cout << "lfiber.d() = " << lfiber.d() << endl;

  size_type ldisc_ct = xcoords.schema().discretization_ct();
  cout << "ldisc_ct = " << ldisc_ct << endl;

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    for(int j=0; j<ld; ++j)
    {
      lfiber.put_component(j, i+j);
    }
    xcoords.put_fiber(i, lfiber);
    //cout << "lfiber = " << lfiber << endl;
  }

  // Postconditions:

  // Exit:

  return;
}

template<typename S, int DC, int DB>
bool
test_d_tree_point_locator_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("test_d_tree_point_locator_facet");

  cout << "DB = " << DB << endl;
  cout << "DC = " << DC << endl;
  cout << "S  = " << S::static_class_name() << endl;

  // Make names for the spaces:

  string lnames[2] = {"base_space",
                      "_coordinates_section_space"};

  make_names_unique(lnames, 2);
 
  const string& lbase_space_name   = lnames[0];
  const string& lcoords_space_name = lnames[1];

  //============================================================================

  poset_path lbase_path = make_base_space(xns, lbase_space_name, DB);

  cout << "lbase_path = " << lbase_path << endl;
  cout << endl;
 
  //============================================================================

   // Create the coordinates section space.

  typename S::host_type& lcoords_space =
    S::standard_host(xns, lbase_path, "", lcoords_space_name, "", false);

  lcoords_space.get_read_write_access();

  cout << "lcoords_space.path() = " << lcoords_space.path() << endl;
  cout << endl;

  //============================================================================

  // Make the coordinates section.

  S lcoords(&lcoords_space);
  lcoords.put_name("coords", true, false);

  cout << "lcoords.path() = " << lcoords.path() << endl;
  cout << endl;

  cout << "lcoords.schema().df() = " << lcoords.schema().df() << endl;
  cout << "lcoords.schema().db() = " << lcoords.schema().db() << endl;

  size_type ldisc_ct = lcoords.schema().discretization_ct();
  cout << "ldisc_ct = " << ldisc_ct << endl;

  // Make dofs:

  make_dofs(lcoords);

  //============================================================================

  cout << endl;

  d_tree_point_locator<DC, DB>llocator(lcoords, 6);

  cout << "llocator.box_ct() = " << llocator.box_ct() << endl;

  d_bounding_box<DC, DB>* lbox0 = new d_bounding_box<DC, DB>;

  llocator.insert_box(lbox0);

  cout << "llocator.box_ct() = " << llocator.box_ct() << endl;

  cout << "llocator = \n" << llocator << endl; // Hangs in d_tree_point_locator_node::to_string

  /////////////////////////////////////////////////////////////////////////////////


//   cout << "depth = " << llocator.depth() << endl;
//   //cout << "root = " << llocator.root() << endl;

//   bool lbool = llocator.invariant();

//   cout << "dc = " << llocator.dc() << endl;


  /////////////////////////////////////////////////////////////////////////////////

  const d_tree_point_locator_node<DC, DB>& lroot = llocator.root();

//   string* lstring = lroot.to_string();
  //cout << "lroot = \n" << lroot << endl;  // Hangs in d_tree_point_locator_node::to_string

  //============================================================================

  typedef forward_list<const d_bounding_box<DC, DB>*> box_list_type;
  box_list_type lbox_list2 = lroot.box_list();
  cout << "lbox_list2.size() = " << lbox_list2.size() << endl; 

  cout << "lroot.is_empty() = " << boolalpha << lroot.is_empty() << endl; 
  cout << "lroot.is_leaf() = " << boolalpha << lroot.is_leaf() << endl; 

  cout << endl;

  //============================================================================

  size_type ldepth = llocator.depth();
  cout << "ldepth  = " << ldepth  << endl;

  size_type lmax_depth = llocator.max_depth();
  cout << "lmax_depth  = " << lmax_depth  << endl;

  size_type& ldefault_depth = llocator.default_depth();
  cout << "ldefault_depth  = " << ldefault_depth  << endl;

  size_type lsize = llocator.size();
  cout << "lsize  = " << lsize  << endl;

  size_type lcapacity = llocator.capacity();
  cout << "lcapacity  = " << lcapacity  << endl;

  bool linvariant = llocator.invariant();
  cout << "linvariant  = " << boolalpha << linvariant  << endl;

  //virtual const box_list_type& box_list(sec_vd_value_type* xpt,
  //                                      size_type xpt_ub) const;

  double lpt[DC];
  for(int i=0; i<DC; ++i)
  {
    lpt[i] = i;
  }

  typedef forward_list<const d_bounding_box<DC, DB>*> box_list_type;
  const box_list_type& lbox_list = llocator.box_list(lpt, DC);

  //============================================================================
  // $$SCRIBBLE: Maybe test d_tree_point_locator_node and
  //             d_tree_point_locator_path here since they need
  //             a d_tree_point_locator to be fully tested.
  //============================================================================

  d_tree_point_locator_path<DC, DB> lpath(&llocator);
  d_tree_point_locator_node<DC, DB> lnode;

  //   void insert_box(const d_bounding_box<DC, DB>* xbox,
  //                   d_tree_point_locator_path<DC, DB>& xpath);

  d_bounding_box<DC, DB> lbox2;
  lnode.insert_box(&lbox2, lpath);

  //   bool contains_box(const d_bounding_box<DC, DB>* xbox,
  //                     d_tree_point_locator_path<DC, DB>& xpath) const;

  bool lcontains_box = lnode.contains_box(&lbox2, lpath);
  cout << "lcontains_box   = " << boolalpha << lcontains_box   << endl;

  //   void remove_box(const d_bounding_box<DC, DB>* xbox,
  //                   d_tree_point_locator_path<DC, DB>& xpath);

  lnode.remove_box(&lbox2, lpath);

  // void clear()

  lnode.insert_box(&lbox2, lpath);
  lnode.clear();

  //   const box_list_type& box_list(d_tree_point_locator_path<DC, DB>& xpath) const;
  const box_list_type& lbox_list3 = lnode.box_list(lpath);

  //============================================================================
  //============================================================================

   // void remove_box(const d_bounding_box<DC, DB>* xbox);

  llocator.remove_box(lbox0);

  // void clear()

  llocator.insert_box(lbox0);
  llocator.clear();

  //============================================================================

  d_tree_point_locator<DC, DB>* llocator_ptr1 = 
    new d_tree_point_locator_child<DC, DB>(lcoords, 4);

  delete llocator_ptr1;

  d_tree_point_locator<DC, DB>* llocator_ptr2 = 
    new d_tree_point_locator_child<DC, DB>(lcoords);

  delete llocator_ptr2;

  //============================================================================

  // Invoke the derived class constructors and destructors.  

  d_tree_point_locator_child<DC, DB>* lchild1 =
    new d_tree_point_locator_child<DC, DB>(lcoords, 4);

  delete lchild1;

  d_tree_point_locator_child<DC, DB>* lchild2 =
    new d_tree_point_locator_child<DC, DB>(lcoords);

  delete lchild2;
 
  //============================================================================
  // Test d_tree_point_locator_path
  //============================================================================

  {

  print_subheader("Testing d_tree_point_locator_path");

  //d_tree_point_locator_path(const d_tree_point_locator<DC, DB>* xtree);
  d_tree_point_locator_path<DC, DB> lpath2(&llocator);

  //d_tree_point_locator_path(const d_tree_point_locator_path<DC, DB>& xother);
  d_tree_point_locator_path<DC, DB> lpath_assign = lpath2;

  //d_tree_point_locator_path(const d_tree_point_locator_path<DC, DB>& xother);
  d_tree_point_locator_path<DC, DB> lpath_copy = lpath2;

  //d_tree_point_locator_path(const d_bin_coordinates<DC, DB>& xpt,
  //                          const d_tree_point_locator<DC, DB>* xtree);
  d_bin_coordinates<DC, DB> ld_bin_coords;
  d_tree_point_locator_path<DC, DB> lpath3(ld_bin_coords, &llocator);

  //ostream&
  //operator<<(ostream &os, const d_tree_point_locator_path<DC, DB>& xpath)
  cout << "lpath2 = \n" << lpath2 << endl;

  //virtual bool invariant() const;
  bool linvariant = lpath2.invariant();
  cout << "linvariant  = " << boolalpha << linvariant  << endl;

  // size_type depth() const;
  size_type ldepth = lpath2.depth();
  cout << "ldepth  = " << ldepth  << endl;

  //static size_type max_depth();
  size_type lmax_depth = d_tree_point_locator_path<DC, DB>::max_depth();
  cout << "lmax_depth  = " << lmax_depth  << endl;

  // size_type height() const;
  size_type lheight = lpath2.height();
  cout << "lheight  = " << lheight  << endl;

  //static size_type max_height();
  size_type lmax_height = d_tree_point_locator_path<DC, DB>::max_height();
  cout << "lmax_height  = " << lmax_height  << endl;

  //d_tree_point_locator<DC, DB>* tree() const;
  d_tree_point_locator<DC, DB>* ltree = lpath2.tree();
  cout << "ltree  = " << ltree  << endl;

  //size_type head() const;
  size_type lhead = lpath2. head();
  cout << "lhead  = " << lhead  << endl;

  //void put_head(size_type xhead);
  lpath2.put_head(lhead);

  //bool intersects(const d_bounding_box<DC, DB>* xbox) const;

  //const d_bin_coordinates<DC, DB>& path() const;
  const d_bin_coordinates<DC, DB>& lpath_coords = lpath2.path();

  //static size_type degree();
  size_type ldegree = d_tree_point_locator_path<DC, DB>::degree();
  cout << "ldegree  = " << ldegree  << endl;


  //void descend();
  lpath2.descend();

  //void ascend();
  lpath2.ascend();

  //void reset();
  lpath2.reset();

  // Invoke derived class constructor and destructor.

  d_tree_point_locator_path_child<DC, DB>* lchild  = 
    new d_tree_point_locator_path_child<DC, DB>(&llocator);

  delete lchild;
  
  }
 
  //============================================================================

  // Cleanup.

  lcoords.detach_from_state();
  lcoords_space.release_access();

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

  print_header("Begin testing d_tree_point_locator_facet");

  bool ltest = true;

  //============================================================================

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  ltest &= test_d_tree_point_locator_facet<sec_e1, 1, 1>(lns);

  ltest &= test_d_tree_point_locator_facet<sec_e2, 2, 2>(lns);

  ltest &= test_d_tree_point_locator_facet<sec_e3, 3, 3>(lns);

  // We have no 4d base spaces yet!
  //ltest &= test_d_tree_point_locator_facet<sec_e4, 4, 4>(lns);

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing d_tree_point_locator_facet");

  // Postconditions:

  // Exit:

  return lresult;
}
