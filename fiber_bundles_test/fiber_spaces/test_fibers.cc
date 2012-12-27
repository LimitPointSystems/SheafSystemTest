
// $RCSfile: test_fibers.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:45 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @file
/// Implementation for test_fibers non template functions.



#include "test_fibers.impl.h"

#include "at0_space.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.impl.h"
#include "std_iostream.h"
#include "test_utils.h"

#include "gln_space.h"

///
string
fiber_bundle::
create_vector_space_name(const string& xvector_class_name)
{
  // Preconditions:

  // Body:

  // We have to make up different names (in general) for the vector spaces
  // each time this function is called. So we'll just add "_space#" to
  // the end of the names with "#" incremented on very call.

  static int lname_suffix = -1;
  lname_suffix++;
  static ostringstream lname;

  lname.str("");
  lname << xvector_class_name << "_space_" << lname_suffix;

  string result = lname.str();

  // Postconditions:

  // Exit:

  return result;
}

using namespace fiber_bundle; // Workaround for MS C++ bug.

///
void
fiber_bundle::
create_host_name(const string& xbase_name, string& xresult)
{
  // Preconditions:

  // Body:

  // We have to make up different names (in general) for the hosts
  // each time this function is called. So we'll just add "_#" to
  // the end of the names with "#" incremented on very call.

  static int lname_suffix = -1;
  lname_suffix++;
  static ostringstream lname;

  lname.str("");
  lname << xbase_name << "_" << lname_suffix;

  xresult = lname.str();

  // Postconditions:

  // Exit:  
}


//==============================================================================
// E3 FACET
//==============================================================================

///
void
fiber_bundle::
test_e3_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  // Body:

  print_header("Testing e3 facet:");

  test_volatile_e3_facet();
  test_persistent_e3_facet(xns);

  // Postconditions:

  // Exit:
}

///
void
fiber_bundle::
test_volatile_e3_facet()
{
  // Preconditions:

  // Body:

  print_subheader("Testing volatile type \"e3_lite\"");

  e3_lite test1(1, 2, 3);
  cout << "e3_lite test1:" << test1 << endl;

  e3_lite test2(4, 5, 6);
  cout << "e3_lite test2:" << test2 << endl;
  cout << endl;

  // Cross product: (1, 2, 3) x (4, 5, 6) = (-3, 6, -3).

  e3_lite* test3 = cross(test1, test2);
  cout << "cross(test1, test2): " << *test3 << endl;
  cout << endl;
  delete test3;

  e3_lite* test4 = test1^test2;
  cout << "test1 ^ test2: " << *test4 << endl;
  cout << endl;
  delete test4;

  e3_lite test5;
  cross(test1, test2, test5);
  cout << "cross(test1, test2, test5): " << test5 << endl;
  cout << endl;

  test5 = test1;
  cross_equal(test5, test2);
  cout << "cross_equal(test5, test2):" << test5 << endl;
  cout << endl;

  test5 = test1;
  test5 ^= test2;
  cout << "test5 ^= test2:" << test5 << endl;
  cout << endl;

  // Postconditions:

  // Exit:
}

///
void
fiber_bundle::
test_persistent_e3_facet(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_subheader("Testing persistent type \"e3\"");

  e3::host_type& host = xns.new_vector_space<e3>();
  host.get_read_write_access();
  
  e3 test7(&host);
  test7.put_name("test7", true, false);

  e3 test8(&host);
  test8.put_name("test8", true, false);

  for(int i=0; i<test7.d(); ++i)
  {
    test7.put_component(i, i+1);
    test8.put_component(i, i+1+test7.d());
  }
  cout << "e3 test7:" << test7 << endl;
  cout << "e3 test8:" << test8 << endl;

  // Cross product: (1, 2, 3) x (4, 5, 6) = (-3, 6, -3).

  e3 test9(&host);
  test9.put_name("test9", true, false);
  cross(test7, test8, test9, false);
  cout << "cross(test7, test8, test9): " << test9 << endl;
  cout << endl;

  cross_equal(test7, test8, false);
  cout << "cross_equal(test7, test8):" << test7 << endl;
  cout << endl;

  test7.detach_from_state();
  test8.detach_from_state();
  test9.detach_from_state();
  host.release_access();

  // Postconditions:

  // Exit:
}

//#define SKIP
#ifndef SKIP
//==============================================================================
// Specializations
//==============================================================================

template <>
void
fiber_bundle::
test_persistent_type<gl2>(typename gl2::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef gl2 P;
  typedef P persistent_type;
  const string& lfiber_name = P::static_class_name();

  print_header("Testing persistent type " + lfiber_name);

  //============================================================================

//   persistent_type* lfiber = new persistent_type(&xhost);

//   const string lmember_name("test_fiber");
//   lfiber->put_name(lmember_name, true, false);

//   const string& lclass_name = lfiber->class_name();
//   cout << "lclass_name = " << lclass_name << endl;

//   //$$SCRIBBLE: gl classes have no factor_ct().
//   //int lfactor_ct = lfiber->factor_ct();
//   //cout << "lfactor_ct = " << lfactor_ct << endl;

//   persistent_type* lfiber2 = new persistent_type(lfiber);

//   persistent_type lfiber3 = *lfiber;

//   typename P::host_type* lhost = lfiber->host();

//   const scoped_index lindex = lfiber->index();

//   //const poset_state_handle* lpsh = dynamic_cast<poset_state_handle*>(lhost);
//   //persistent_type* lfiber4 = new persistent_type(lpsh, lmember_name);
//   //persistent_type* lfiber5 = new persistent_type(lpsh, lindex);

//   lfiber->detach_from_state();
//   lfiber2->detach_from_state();
//   lfiber3.detach_from_state();
//   //lfiber4->detach_from_state();
//   //lfiber5->detach_from_state();

//   delete lfiber;
//   delete lfiber2;
//   //delete lfiber4;
//   //delete lfiber5;

  //============================================================================

  persistent_type* test1 = new persistent_type(&xhost);
  test1->put_name("test1", true, false);

  for(int i=0; i<test1->d(); ++i)
  {
    test1->put_component(i, i+1);
  }

  persistent_type* test2 = new persistent_type(&xhost);
  test2->put_name("test2", true, false);

  for(int i=0; i<test2->d(); ++i)
  {
    test2->put_component(i, i+1+test2->d());
  }

  cout << lfiber_name << " test1:";
  for(int i=0; i<test1->d(); i++)
  {
    cout << " " << test1->component(i);
  }
  cout << endl;

  cout << lfiber_name << " test2:";
  for(int i=0; i<test2->d(); i++)
  {
    cout << " " << test2->component(i);
  }
  cout << endl;
  
  test1->detach_from_state();
  test2->detach_from_state();

  delete test1;
  delete test2;

  //============================================================================

  // Postconditions:

  // Exit:
}

template <>
void
fiber_bundle::
test_persistent_type<gl3>(typename gl3::host_type& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  // Get the various class types, etc.

  typedef gl3 P;
  typedef P persistent_type;
  const string& lfiber_name = P::static_class_name();

  print_header("Testing persistent type " + lfiber_name);

  //============================================================================

//   persistent_type* lfiber = new persistent_type(&xhost);

//   const string lmember_name("test_fiber");
//   lfiber->put_name(lmember_name, true, false);

//   const string& lclass_name = lfiber->class_name();
//   cout << "lclass_name = " << lclass_name << endl;

//   //$$SCRIBBLE: gl classes have no factor_ct().
//   //int lfactor_ct = lfiber->factor_ct();
//   //cout << "lfactor_ct = " << lfactor_ct << endl;

//   persistent_type* lfiber2 = new persistent_type(lfiber);

//   persistent_type lfiber3 = *lfiber;

//   typename P::host_type* lhost = lfiber->host();

//   const scoped_index lindex = lfiber->index();

//   //const poset_state_handle* lpsh = dynamic_cast<poset_state_handle*>(lhost);
//   //persistent_type* lfiber4 = new persistent_type(lpsh, lmember_name);
//   //persistent_type* lfiber5 = new persistent_type(lpsh, lindex);

//   lfiber->detach_from_state();
//   lfiber2->detach_from_state();
//   lfiber3.detach_from_state();
//   //lfiber4->detach_from_state();
//   //lfiber5->detach_from_state();

//   delete lfiber;
//   delete lfiber2;
//   //delete lfiber4;
//   //delete lfiber5;

  //============================================================================

  persistent_type* test1 = new persistent_type(&xhost);
  test1->put_name("test1", true, false);

  for(int i=0; i<test1->d(); ++i)
  {
    test1->put_component(i, i+1);
  }

  persistent_type* test2 = new persistent_type(&xhost);
  test2->put_name("test2", true, false);

  for(int i=0; i<test2->d(); ++i)
  {
    test2->put_component(i, i+1+test2->d());
  }

  cout << lfiber_name << " test1:";
  for(int i=0; i<test1->d(); i++)
  {
    cout << " " << test1->component(i);
  }
  cout << endl;

  cout << lfiber_name << " test2:";
  for(int i=0; i<test2->d(); i++)
  {
    cout << " " << test2->component(i);
  }
  cout << endl;
  
  test1->detach_from_state();
  test2->detach_from_state();

  delete test1;
  delete test2;

  //============================================================================

  // Postconditions:

  // Exit:
}
#endif //SKIP
