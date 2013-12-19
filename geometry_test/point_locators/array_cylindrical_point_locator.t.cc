
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
/// Unit test driver for class array_cylindrical_point_locator.

#include "array_cylindrical_point_locator.h"

#include "sec_at1_space.h"
#include "sec_e3.h"
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

class array_cylindrical_point_locator_child
  : public array_cylindrical_point_locator
{
public:
  array_cylindrical_point_locator_child(sec_ed& xcoords) 
    : array_cylindrical_point_locator(xcoords) {}

  ~array_cylindrical_point_locator_child() {}

  size_type bin_id(const block<size_type>& xid) const
  {
    return array_cylindrical_point_locator::bin_id(xid);
  }
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

bool
test_array_cylindrical_point_locator_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("test_array_cylindrical_point_locator_facet");

  typedef sec_e3 S;

  cout << "S  = " << S::static_class_name() << endl;
  int DB = 2;
  int DC = 3;

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

  S::host_type& lcoords_space =
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

  array_cylindrical_point_locator llocator(lcoords);

  cout << "llocator = \n" << llocator << endl;

  size_type lsize = llocator.size();
  cout << "lsize  = " << lsize  << endl;

  size_type lcapacity = llocator.capacity();
  cout << "lcapacity  = " << lcapacity  << endl;

  const block<size_type>& lbin_ub = llocator.bin_ub();
  cout << "lbin_ub  = " << lbin_ub  << endl;

  const block<sec_vd_value_type>& lbin_size = llocator.bin_size();
  cout << "lbin_size  = " << lbin_size  << endl;

  size_type lbox_ct = llocator.box_ct();
  cout << "lbox_ct  = " << lbox_ct  << endl;

  bool lis_empty = llocator.is_empty();
  cout << "lis_empty  = " << boolalpha << lis_empty  << endl;

  bool linvariant = llocator.invariant();
  cout << "linvariant  = " << boolalpha << linvariant  << endl;

  //bool is_dlinear_quads(const sec_ed& xcoords) const;
  bool lis_dlinear_quads = llocator.is_dlinear_quads(lcoords);
  cout << "lis_dlinear_quads  = " << boolalpha
       << lis_dlinear_quads  << endl;

  //bool is_dlinear_triangles(const sec_ed& xcoords) const;
  bool lis_dlinear_triangles = llocator.is_dlinear_triangles(lcoords);
  cout << "lis_dlinear_triangles  = " << boolalpha
       << lis_dlinear_triangles  << endl;

  double* lpt = new double[DC];
  for(int i=0; i<DC; ++i)
  {
    lpt[i] = i;
  }

  typedef forward_list<const d_bounding_box<2, 2>*> box_list_type;
  const box_list_type& lbox_list = llocator.box_list(lpt, 2);

  d_bounding_box<2, 2> lbox0;
  llocator.insert_box(&lbox0);

  bool lcontains_box = llocator.contains_box(&lbox0);
  cout << "lcontains_box  = " << boolalpha << lcontains_box  << endl;

  llocator.remove_box(&lbox0);

  //============================================================================

  llocator.clear();

  //============================================================================

  block<size_type> lbin_ub2;
  lbin_ub2.push_back(2);
  lbin_ub2.push_back(3);
  lbin_ub2.push_back(4);

  array_cylindrical_point_locator llocator2(lcoords, lbin_ub2);

  //cout << "llocator2 = \n" << llocator2 << endl;

  //============================================================================


  chart_point_3d lchart_point;
  sec_vd_value_type* lvalue0 = new sec_vd_value_type[DC];
  for(int i=0; i<DC; ++i) lvalue0[i] = i;
  llocator.point_at_value(lvalue0, DC, lchart_point);

  block<chart_point_3d> lchart_points(1);
  llocator.all_points_at_value(lvalue0, DC, lchart_points);

  block<branch_point_pair> lblock(1);
  llocator.branch_points_at_value(lvalue0, DC, lblock);

  //============================================================================

  // Invoke the derived class functions.

  array_cylindrical_point_locator_child* lchild =
    new array_cylindrical_point_locator_child(lcoords);

  block<size_type> lblock2;
  lblock2.push_back(0);
  lblock2.push_back(1);

  size_type lbin_id = lchild->bin_id(lblock2);

  delete lchild;

  //============================================================================

  lcoords.detach_from_state();
  lcoords_space.release_access();

  //============================================================================

  // Postconditions:

  // Exit:

  return true;
}

bool
test_cylindrical_point_locator_facet()
{
  // Preconditions:

  // Body:

  // Need sec_ed xcoords.

  // array_cylindrical_point_locator(sec_ed& xcoords);

  // array_cylindrical_point_locator(sec_ed& xcoords, const block<size_type>& xbin_ub);

  // Postconditions:

  // Exit:

  return true;
}

// bool
// test_array_cylindrical_point_locator_facet()
// {
//   // Preconditions:

//   // Body:

//   // Need sec_ed xcoords.

//   // array_cylindrical_point_locator(sec_ed& xcoords);

//   // array_cylindrical_point_locator(sec_ed& xcoords, const block<size_type>& xbin_ub);

//   // Postconditions:

//   // Exit:

//   return true;
// }

} //end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing array_cylindrical_point_locator facet");

  bool ltest = true;

  //============================================================================

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  //ltest &= test_cylindrical_point_locator_facet();
  ltest &= test_array_cylindrical_point_locator_facet(lns);

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing array_cylindrical_point_locator facet");

  // Postconditions:

  // Exit:

  return lresult;
}
