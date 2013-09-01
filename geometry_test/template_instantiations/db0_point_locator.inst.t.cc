
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for class db0_point_locator.

#include "db0_point_locator.h"

#include "fiber_bundles_namespace.h"
#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "sec_at1_space.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_ed_invertible.h"
#include "sec_rep_descriptor.h" 

#include "geometry.h"
#include "test_utils.h"

#include "std_iomanip.h"
#include "std_sstream.h"

using namespace geometry;

namespace
{

//==============================================================================

template<int DC>
class db0_point_locator_child : public db0_point_locator<DC>
{
public:
  db0_point_locator_child(sec_ed& xcoords) 
    : db0_point_locator<DC>(xcoords) {}

  ~db0_point_locator_child() {}

  // These functions are protected in db0_point_locator;
  // so we cheat a little here to allow invoking them.

  void print_bins(ostream& xos, const string& xmsg) const
  {
    db0_point_locator<DC>::print_bins(xos, xmsg);
  }

  void print_queue(ostream& xos, const string& xmsg) const
  {
    db0_point_locator<DC>::print_queue(xos, xmsg);
  }

  void print_value(ostream& xos,
                   const double xvalue[],
                   const string& xmsg) const
  {
    db0_point_locator<DC>::print_value(xos, xvalue, xmsg);
  }

  void print_coords(ostream& xos,
                    const int xcoords[],
                    const string& xmsg) const
  {
    db0_point_locator<DC>::print_coords(xos, xcoords, xmsg);
  }

  void expand_search_region(const sec_vd_value_type xvalue[])
  {
    db0_point_locator<DC>::expand_search_region(xvalue);
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

  typedef point_block_1d B;
    
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

  typedef point_block_2d B;
    
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

  typedef point_block_3d B;
    
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

//==============================================================================

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

//==============================================================================

template<typename S, int DC>
bool
test_db0_point_locator_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("test_d_tree_point_locator_facet");

  cout << "DC = " << DC << endl;
  cout << "S  = " << S::static_class_name() << endl;

  // Make names for the spaces:

  string lnames[2] = {"base_space",
                      "_coordinates_section_space"};

  make_names_unique(lnames, 2);
 
  const string& lbase_space_name   = lnames[0];
  const string& lcoords_space_name = lnames[1];

  //============================================================================

  poset_path lbase_path = make_base_space(xns, lbase_space_name, DC);

  cout << "lbase_path = " << lbase_path << endl;
  cout << endl;
 
  //============================================================================

   // Create the coordinates section space.

  typename S::host_type& lcoords_space =
    S::standard_host(xns, lbase_path, "sec_rep_descriptors/vertex_vertex_constant", lcoords_space_name, "", false);

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

  // db0_point_locator(sec_ed& xcoords, int xavg_occupancy = 2);

  db0_point_locator<DC> llocator(lcoords);

  //cout << "llocator = \n" << llocator << endl;

  bool lis_empty = llocator.is_empty();
  cout << "lis_empty  = " << boolalpha << lis_empty  << endl;

//   size_type lsize = llocator.size();
//   cout << "lsize  = " << lsize  << endl;

//   size_type lcapacity = llocator.capacity();
//   cout << "lcapacity  = " << lcapacity  << endl;

  bool linvariant = llocator.invariant();
  cout << "linvariant  = " << boolalpha << linvariant  << endl;

  //const block<size_type>& bin_ub() const;
  block<size_type> lbin_ub2 = llocator.bin_ub();
  cout << "lbin_ub2 = " << lbin_ub2 << endl;

  //const block<sec_vd_value_type>& bin_size() const;
  block<sec_vd_value_type> lbin_size = llocator.bin_size();
  cout << "lbin_size = " << lbin_size << endl;


  //============================================================================

  //virtual void point_at_value(const sec_vd_value_type* xvalue,
  //                            size_type xvalue_ub,
  //                            chart_point& xresult);

  chart_point_3d lchart_point;
  sec_vd_value_type lvalue0[DC];
  for(int i=0; i<DC; ++i) lvalue0[i] = i;
  llocator.point_at_value(lvalue0, DC, lchart_point);

  //virtual void all_points_at_value(const sec_vd_value_type* xvalue,
  //                                 size_type xvalue_ub,
  //                                 block<chart_point_3d>& xresult);

  block<chart_point_3d> lchart_points(1);
  llocator.all_points_at_value(lvalue0, DC, lchart_points);
  //  what():  '0 <= xct && xct <= ub()' in file auto_block.impl.h at line 467
  

  //virtual void branch_points_at_value(const sec_vd_value_type* xvalue,
  //                                    size_type xvalue_ub,
  //                                    block<branch_point_pair>& xresult);

  block<branch_point_pair> lblock(1);
  llocator.branch_points_at_value(lvalue0, DC, lblock);
  //  what():  '0 <= xct && xct <= ub()' in file auto_block.impl.h at line 467 
 
  //============================================================================

  // All of these are "protected":

  //llocator.print_bins<DC>(cout , "Bins");
  //llocator.print_queue<DC>(cout , "Queue");

  //sec_vd_value_type lvalue[DC];
  //for(int i=0; i<DC; ++i)
  //  lvalue[i] = i;
  //llocator.print_value<DC>(cout, lvalue, "Value");

  //bin_coord_type lbin_coords[DC];
  //for(int i=0; i<DC; ++i)
  //  lbin_coords = i;
  //llocator.print_value<DC>(cout, lbin_coords, "Bin Coords");

  //============================================================================

  llocator.clear();

  //============================================================================

  block<size_type> lbin_ub;
  lbin_ub.push_back(2);
  lbin_ub.push_back(3);
  lbin_ub.push_back(4);

  db0_point_locator<DC> llocator2(lcoords, lbin_ub);

  //============================================================================

  db0_point_locator_child<DC>* lchild =
    new db0_point_locator_child<DC>(lcoords);

  lchild->print_bins(cout , "Bins");
  lchild->print_queue(cout , "Queue");

  sec_vd_value_type lvalue[DC];
  for(int i=0; i<DC; ++i) lvalue[i] = i;
  lchild->print_value(cout, lvalue, "Value");

  typedef typename db0_point_locator<DC>::bin_coord_type bin_coord_type;
  bin_coord_type lbin_coords[DC];
  for(int i=0; i<DC; ++i) lbin_coords[i] = i;
  lchild->print_coords(cout, lbin_coords, "Bin Coords");

  lchild->expand_search_region(lvalue);

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

  print_header("Begin testing db0_point_locator_facet<DC>:");

  bool ltest = true;

  //============================================================================

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  ltest &= test_db0_point_locator_facet<sec_e1, 1>(lns);

  ltest &= test_db0_point_locator_facet<sec_e2, 2>(lns);

  ltest &= test_db0_point_locator_facet<sec_e3, 3>(lns);

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing db0_point_locator_facet<DC>:");

  // Postconditions:

  // Exit:

  return lresult;
}

