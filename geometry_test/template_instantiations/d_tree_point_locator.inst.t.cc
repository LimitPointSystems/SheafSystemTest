// $RCSfile: d_tree_point_locator.inst.t.cc,v $ $Revision: 1.1.2.4 $ $Date: 2012/10/24 02:00:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for class d_tree_point_locator.

#include "d_tree_point_locator.h"

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


using namespace geometry;

namespace
{

//==============================================================================

template<int DC, int DB>
class d_tree_point_locator_child : public d_tree_point_locator<DC, DB>
{
public:
  d_tree_point_locator_child(sec_ed& xcoords) 
    : d_tree_point_locator<DC, DB>(xcoords) {}

  ~d_tree_point_locator_child() {}
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
    
  base_space_poset& lhost = xns.new_base_space<B>(xbase_space_name);

  B lmesh(&lhost, 2);
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
    
  base_space_poset& lhost = xns.new_base_space<B>(xbase_space_name);

  B lmesh(&lhost, 2, 2);
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
    
  base_space_poset& lhost = xns.new_base_space<B>(xbase_space_name);

  B lmesh(&lhost, 2, 2, 2);
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
                      "coordinates_section_space"};

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
    xns.new_section_space<S>(lcoords_space_name, lbase_path);

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

  //cout << "llocator = \n" << llocator << endl; // Hangs in d_tree_point_locator_node::to_string

  const d_tree_point_locator_node<DC, DB>& lroot = llocator.root();

  //cout << "lroot = \n" << lroot << endl;  // Hangs in d_tree_point_locator_node::to_string

  //============================================================================

  typedef slist<const d_bounding_box<DC, DB>*> box_list_type;
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

  typedef slist<const d_bounding_box<DC, DB>*> box_list_type;
  const box_list_type& lbox_list = llocator.box_list(lpt, DC);

  //llocator.remove_box(lbox0);
  //  terminate called after throwing an instance of 'std::logic_error'
  //  what():  'is_empty() ? xpath.depth() > xpath.tree()->depth() : true' in file d_tree_point_locator_node.impl.h at line 363


  //llocator.clear(); // terminate called after throwing an instance of 'std::logic_error'
                       // what():  'is_leaf()' in file d_tree_point_locator_node.impl.h at line 513

  //============================================================================

  d_tree_point_locator<DC, DB> llocator2(lcoords);

  //cout << "llocator2 = \n" << llocator2 << endl;

  //============================================================================


  // d_tree_point_locator default constructor is protected.
  //   d_tree_point_locator_child<DC, DB>* lchild =
  //     new d_tree_point_locator_child<DC, DB>;

  //   delete lchild;

  d_tree_point_locator_child<DC, DB>* lchild =
    new d_tree_point_locator_child<DC, DB>(lcoords);

  delete lchild;
 
// #define SKIP
// #ifndef SKIP

// #endif //SKIP

  //============================================================================

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
  ltest &= test_d_tree_point_locator_facet<sec_e4, 4, 4>(lns);

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing d_tree_point_locator_facet");

  // Postconditions:

  // Exit:

  return lresult;
}

// geometry::d_tree_point_locator<1, 1>;
// geometry::d_tree_point_locator<2, 2>;
// geometry::d_tree_point_locator<3, 3>;
// geometry::d_tree_point_locator<4, 4>;
