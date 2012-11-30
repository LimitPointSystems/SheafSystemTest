
// $RCSfile: test_fields.cc,v $ $Revision: 1.11 $ $Date: 2012/03/01 00:41:06 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

// Implementation for test_fields non templated functions.

#include "test_fields.impl.h"

#include "fields.h"
#include "index_space_iterator.h"
#include "poset_path.h"
#include "sec_at1_space.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_rep_space.h"
#include "section_space_factory.h"
#include "std_iostream.h"
#include "std_sstream.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "test_utils.h"

using namespace fields; // Workaround for MS C++ bug.

//==============================================================================
//==============================================================================


using namespace sheaf;
using namespace fiber_bundle;

///
void
fields::
create_section_space_name(const string& xbase_name, string& xresult)
{
  // Preconditions:

  // Body:

  // We have to make up different names (in general) for the sections
  // each time this function is called. So we'll just add "_#" to
  // the end of the names with "#" incremented on very call.

  static int lname_suffix = -1;
  lname_suffix++;
  static ostringstream lname;

  lname.str("");
  lname << xbase_name << "_section_space_" << lname_suffix;

  xresult = lname.str();

  // Postconditions:

  // Exit:  
}

//==============================================================================
// AT0 FACET
//==============================================================================

///
void
fields::
test_field_at0_facet(fiber_bundles_namespace& xns,
                     const poset_path& xbase_path,
                     const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(unexecutable("xns contains xbase_path"));

  // Body:

  string field_name = field_at0::static_class_name();
  print_header("Testing at0 facet for " + field_name);

  //============================================================================

  // Create fields for use in testing.

  static const int num_fields = 4;
  field_at0 lscalar[4];

  make_test_fields(xns, xbase_path, xcoords_path, "scalar_property",
                   lscalar, num_fields);

  //============================================================================

  // Execute the tests.

  print_field(lscalar[0]);

  exp(lscalar[0], lscalar[1], true);
  print_result("exp(lscalar[0], lscalar[1], true):", lscalar[1]);

  fabs(lscalar[0], lscalar[1], true);
  print_result("fabs(lscalar[0], lscalar[1], true):", lscalar[1]);

  log(lscalar[0], lscalar[1], true);
  print_result("log(lscalar[0], lscalar[1], true):", lscalar[1]);

  log10(lscalar[0], lscalar[1], true);
  print_result("log10(lscalar[0], lscalar[1], true):", lscalar[1]);

  sqrt(lscalar[0], lscalar[1], true);
  print_result("sqrt(lscalar[0], lscalar[1], true):", lscalar[1]);

  pow(lscalar[0], 2, lscalar[1], true);
  print_result("pow(lscalar[0], 2, lscalar[1], true):", lscalar[1]);

  ldexp(lscalar[0], 2, lscalar[1], true);
  print_result("ldexp(lscalar[0], 2, lscalar[1], true):", lscalar[1]);

  fmod(lscalar[0], lscalar[1], lscalar[2], true);
  print_result("fmod(lscalar[0], lscalar[1], lscalar[2], true):", lscalar[2]);

  modf(lscalar[0], lscalar[1], lscalar[2], true);
  cout << "modf(lscalar[0], lscalar[1], lscalar[2], true):" << endl;
  print_field(lscalar[0]);
  print_field(lscalar[1]);
  print_field(lscalar[2]);

  frexp(lscalar[0], lscalar[1], lscalar[2], true);
  cout << "frexp(lscalar[0], lscalar[1], lscalar[2], true):" << endl;
  print_field(lscalar[0]);
  print_field(lscalar[1]);
  print_field(lscalar[2]);

  floor(lscalar[0], lscalar[1], true);
  print_result("floor(lscalar[0], lscalar[1], true):", lscalar[1]);

  ceil(lscalar[0], lscalar[1], true);
  print_result("ceil(lscalar[0], lscalar[1], true):", lscalar[1]);

  cosh(lscalar[0], lscalar[1], true);
  print_result("cosh(lscalar[0], lscalar[1], true):", lscalar[1]);

  sinh(lscalar[0], lscalar[1], true);
  print_result("sinh(lscalar[0], lscalar[1], true):", lscalar[1]);

  tanh(lscalar[0], lscalar[1], true);
  print_result("tanh(lscalar[0], lscalar[1], true):", lscalar[1]);

  // Compute cos then acos, etc. so we don't create errors by attempting
  // to evaluate acos outside the range (-1 to +1), etc..

  cos(lscalar[0], lscalar[1], true);
  print_result("cos(lscalar[0], lscalar[1], true):", lscalar[1]);

  acos(lscalar[1], lscalar[2], true);
  print_result("acos(lscalar[1], lscalar[2], true):", lscalar[2]);

  sin(lscalar[0], lscalar[1], true);
  print_result("sin(lscalar[0], lscalar[1], true):", lscalar[1]);

  asin(lscalar[1], lscalar[2], true);
  print_result("asin(lscalar[1], lscalar[2], true):", lscalar[2]);

  tan(lscalar[0], lscalar[1], true);
  print_result("tan(lscalar[0], lscalar[1], true):", lscalar[1]);

  atan(lscalar[1], lscalar[2], true);
  print_result("atan(lscalar[1], lscalar[2], true):", lscalar[2]);

  atan2(lscalar[1], lscalar[2], lscalar[3], true);
  print_result("atan2(lscalar[1], lscalar[2], lscalar[3], true):", lscalar[3]);

  //============================================================================

  // Postconditions:

  // Exit:
}

//==============================================================================
// E3 FACET
//==============================================================================

///
void
fields::
test_field_e3_facet(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(unexecutable("xns contains xbase_path"));

  // Body:

  string section_name = field_e3::static_class_name();
  print_header("Testing e3 facet for " + section_name);

  //============================================================================

  // Create fields for use in testing.

  static const int num_fields = 3;
  field_e3 lvector[3];

  make_test_fields(xns, xbase_path, xcoords_path, "vector_property",
                   lvector, num_fields);

  //============================================================================

  // Execute the tests.

  print_field(lvector[0]);
  print_field(lvector[1]);

  // cross: lvector[3] = lvector[0] x lvector[1];

  cross(lvector[0], lvector[1], lvector[2], true);

  // cross_equal: lvector[0] = lvector[0] x lvector[1];

  cross_equal(lvector[0], lvector[1], true);

  cout << "cross_equal(lvector[0], lvector[1]):" << endl;
  print_field(lvector[0]);

  // Postconditions:

  // Exit:
}


//==============================================================================


///
const sheaf::poset_path&
fields::
make_test_base_space(fiber_bundle::fiber_bundles_namespace& xns,
                     const size_type& xi_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xi_size > 0);

  // Body:

  static const poset_path lresult("test_mesh", "test_mesh_block"); 

  base_space_poset* lmesh = &xns.new_base_space<structured_block_1d>(lresult.poset_name());

  structured_block_1d lblock(lmesh, xi_size, true);
  lblock.put_name(lresult.member_name(), true, true);
  lblock.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(lresult, true));

  // Postconditions:

  // Exit:

  return lresult;
}

///
const sheaf::poset_path&
fields::
make_test_base_space(fiber_bundle::fiber_bundles_namespace& xns,
                     const size_type& xi_size,
                     const size_type& xj_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  static const poset_path lresult("test_mesh", "test_mesh_block"); 
  
  base_space_poset* lmesh = &xns.new_base_space<structured_block_2d>(lresult.poset_name());
  
  structured_block_2d lblock(lmesh, xi_size, xj_size, true);
  lblock.put_name(lresult.member_name(), true, true);
  lblock.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(lresult, true));

  // Exit:

  return lresult;
}

///
const sheaf::poset_path&
fields::
make_test_base_space(fiber_bundle::fiber_bundles_namespace& xns,
                     const size_type& xi_size,
                     const size_type& xj_size,
                     const size_type& xk_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);

  // Body:

  static const poset_path lresult("test_mesh", "test_mesh_block"); 

  base_space_poset* lmesh = &xns.new_base_space<structured_block_3d>(lresult.poset_name());
  
  structured_block_3d lblock(lmesh, xi_size, xj_size, xk_size, true);
  lblock.put_name(lresult.member_name(), true, true);
  lblock.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(lresult, true));

  // Exit:

  return lresult;
}

//==============================================================================

///
const sheaf::poset_path&
fields::
make_test_coordinates_1d(fiber_bundle::fiber_bundles_namespace& xns,
                         const sheaf::poset_path& xbase_path)
{
  typedef fiber_bundle::sec_e1 SEC_TYPE;

  static const poset_path lresult("coordinates_section_space",
                                  "coordinates_section"); 

  string lname = "coordinates_section_space";
  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  sec_rep_space& lhost = xns.new_section_space<SEC_TYPE>(lname, xbase_path, lpath, true);
  lhost.get_read_write_access();
  
  // Make the coordinates section.

  SEC_TYPE* lcoords = new SEC_TYPE(&lhost);
  lcoords->put_name("coordinates_section", true, false);

  // Set the coordinates dofs;

  SEC_TYPE::fiber_type::volatile_type lfiber;
  index_space_iterator* litr =
    lcoords->schema().discretization_id_space().iterator(true);
  for(pod_index_type i=0; !litr->is_done(); litr->next(), ++i)
  {
    lfiber[0] = 10*i;
    lcoords->put_fiber(litr->pod(), lfiber);
  }
  delete litr;

  //cout << *lhost << endl;

  lhost.release_access();

  lcoords->detach_from_state();
  delete lcoords;

  return lresult;

}

///
const sheaf::poset_path&
fields::
make_test_coordinates_2d(fiber_bundle::fiber_bundles_namespace& xns,
                         const sheaf::poset_path& xbase_path)
{
  typedef fiber_bundle::sec_e2 SEC_TYPE;

  static const poset_path lresult("coordinates_section_space",
                                  "coordinates_section"); 

  string lname = "coordinates_section_space";
  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  sec_rep_space& lhost = xns.new_section_space<SEC_TYPE>(lname, xbase_path, lpath, true);
  lhost.get_read_write_access();
  
  // Make the coordinates section.

  SEC_TYPE* lcoords = new SEC_TYPE(&lhost);
  lcoords->put_name("coordinates_section", true, false);

  // Set the coordinates dofs;

  SEC_TYPE::fiber_type::volatile_type lfiber;
  index_space_iterator* litr =
    lcoords->schema().discretization_id_space().iterator(true);
  for(pod_index_type i=0; !litr->is_done(); litr->next(), ++i)
  {
    lfiber[0] = 10*i;
    lfiber[1] = 20*i;
    lcoords->put_fiber(litr->pod(), lfiber);
  }
  delete litr;
  
  //cout << *lhost << endl;

  lhost.release_access();

  lcoords->detach_from_state();
  delete lcoords;

  return lresult;

}

///
const sheaf::poset_path&
fields::
make_test_coordinates_3d(fiber_bundle::fiber_bundles_namespace& xns,
                         const sheaf::poset_path& xbase_path)
{
  typedef fiber_bundle::sec_e3 SEC_TYPE;

  static const poset_path lresult("coordinates_section_space",
                                  "coordinates_section"); 

  string lname = "coordinates_section_space";
  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  sec_rep_space& lhost = xns.new_section_space<SEC_TYPE>(lname, xbase_path, lpath, true);
  lhost.get_read_write_access();
  
  // Make the coordinates section.

  SEC_TYPE* lcoords = new SEC_TYPE(&lhost);
  lcoords->put_name("coordinates_section", true, false);

  // Set the coordinates dofs;

  SEC_TYPE::fiber_type::volatile_type lfiber;
  index_space_iterator* litr =
    lcoords->schema().discretization_id_space().iterator(true);
  for(pod_index_type i=0; !litr->is_done(); litr->next(), ++i)
  {
    lfiber[0] = 10*i;
    lfiber[1] = 20*i;
    lfiber[2] = 30*i;
    lcoords->put_fiber(litr->pod(), lfiber);
  }
  delete litr;

  //cout << *lhost << endl;

  lhost.release_access();

  lcoords->detach_from_state();
  delete lcoords;

  return lresult;

}

//==============================================================================

