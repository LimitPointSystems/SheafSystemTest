
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
/// Unit test driver for class d_array_point_locator.

#include "SheafSystem/d_array_point_locator.h"
#include "SheafSystem/d_bounding_box.h"

#include "SheafSystem/sec_at1_space.h"
#include "SheafSystem/sec_e1.h"
#include "SheafSystem/sec_e2.h"
#include "SheafSystem/sec_e3.h"
#include "SheafSystem/sec_ed_invertible.h"
#include "SheafSystem/structured_block_1d.h"
#include "SheafSystem/structured_block_2d.h"
#include "SheafSystem/structured_block_3d.h"

#include "SheafSystem/geometry.h"
#include "SheafSystemTest/test_utils.h"

#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_sstream.h"


using namespace std;
using namespace geometry;

namespace
{

//==============================================================================

template<int DC, int DB>
class d_array_point_locator_child : public d_array_point_locator<DC, DB>
{
public:
  d_array_point_locator_child(sec_ed& xcoords, 
			                 bool xpopulate = true, 
			                 size_type xeval_capacity = 256)
    : d_array_point_locator<DC, DB>(xcoords, xpopulate, xeval_capacity) {}


  ~d_array_point_locator_child() {}

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
test_d_array_point_locator_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("test_d_array_point_locator_facet");

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

  d_array_point_locator<DC, DB>llocator(lcoords);

  cout << "llocator = \n" << llocator << endl;

  size_type lsize = llocator.size();
  cout << "lsize  = " << lsize  << endl;

  size_type lcapacity = llocator.capacity();
  cout << "lcapacity  = " << lcapacity  << endl;

  bool linvariant = llocator.invariant();
  cout << "linvariant  = " << boolalpha << linvariant  << endl;

  double lpt[DC];
  for(int i=0; i<DC; ++i)
  {
    lpt[i] = i;
  }

  typedef singly_linked_list<const d_bounding_box<DC, DB>*> box_list_type;
  const box_list_type& lbox_list = llocator.box_list(lpt, DC);


  llocator.clear();

  //============================================================================

  block<size_type> lbin_ub;
  lbin_ub.push_back(2);
  lbin_ub.push_back(3);
  lbin_ub.push_back(4);

  d_array_point_locator<DC, DB> llocator2(lcoords, lbin_ub);

  //cout << "llocator2 = \n" << llocator2 << endl;

  //============================================================================

  // Invoke the derived class functions.

  d_array_point_locator_child<DC, DB>* lchild =
    new d_array_point_locator_child<DC, DB>(lcoords);

  delete lchild;

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

  print_header("Begin testing d_array_point_locator_facet");

  bool ltest = true;

  //============================================================================

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  ltest &= test_d_array_point_locator_facet<sec_e1, 1, 1>(lns);

  ltest &= test_d_array_point_locator_facet<sec_e2, 2, 2>(lns);

  ltest &= test_d_array_point_locator_facet<sec_e3, 3, 1>(lns);

  ltest &= test_d_array_point_locator_facet<sec_e3, 3, 2>(lns);

  ltest &= test_d_array_point_locator_facet<sec_e3, 3, 3>(lns);

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing d_array_point_locator_facet");

  // Postconditions:

  // Exit:

  return lresult;
}


