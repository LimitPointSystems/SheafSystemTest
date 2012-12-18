
// $RCSfile: test_sections.cc,v $ $Revision: 1.11.36.1 $ $Date: 2012/11/29 21:09:49 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

// Implementation for test_sections non templatde functions.

#include "test_sections.impl.h"

#include "fiber_bundles_namespace.h"
#include "sec_e3.h"
#include "sec_rep_space.h"
#include "std_iostream.h"
#include "std_sstream.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "test_utils.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
//==============================================================================

///
void
fiber_bundle::
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
  lname << xbase_name << "_" << lname_suffix;

  xresult = lname.str();

  // Postconditions:

  // Exit:  
}


///
void
fiber_bundle::
print_section_space(fiber_bundles_namespace& xns, const string& xname)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  sec_rep_space* lspace = xns.member_poset<sec_rep_space>(xname, false);
  cout << *lspace << endl;

  // Postconditions:

  // Exit:

  return;
}


//==============================================================================
// AT0 FACET
//==============================================================================

///
void
fiber_bundle::
test_sec_at0_facet(fiber_bundles_namespace& xns,
                   const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(unexecutable("xns contains xbase_path"));

  // Body:

  string section_name = sec_at0::static_class_name();

  print_header("Testing at0 facet for " + section_name);

  //============================================================================

  // Create  attached sections for testing
  // (also creates the base space, section space, and schema  if necessary).

  static const int num_sections = 4;
  sec_at0 lscalar[4];

  make_test_sections(xns,
                     xbase_path,
                     "at0_facet_section_space",
                     "scalar",
                     lscalar,
                     num_sections);

  //============================================================================

  // Execute the tests.

  print_section(lscalar[0]);

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
  print_section(lscalar[0]);
  print_section(lscalar[1]);
  print_section(lscalar[2]);

  frexp(lscalar[0], lscalar[1], lscalar[2], true);
  cout << "frexp(lscalar[0], lscalar[1], lscalar[2], true):" << endl;
  print_section(lscalar[0]);
  print_section(lscalar[1]);
  print_section(lscalar[2]);

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

  // Detach the sections.

  for(int i=0; i<num_sections; ++i)
  {
    lscalar[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

//==============================================================================
// E3 FACET
//==============================================================================

///
void
fiber_bundle::
test_sec_e3_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(unexecutable("xns contains xbase_path"));

  // Body:

  string section_name = sec_e3::static_class_name();

  print_header("Testing e3 facet for " + section_name);

  //============================================================================

  // Create  attached sections for testing
  // (also creates the base space, section space, and schema  if necessary).

  static const int num_sections = 3;
  sec_e3 lvector[3];

  make_test_sections(xns,
                     xbase_path,
                     "e3_facet_vector_section_space",
                     "vector",
                     lvector,
                     num_sections);

  //============================================================================

  // Execute the tests.

  print_section(lvector[0]);
  print_section(lvector[1]);

  // cross: lvector[3] = lvector[0] x lvector[1];

  cross(lvector[0], lvector[1], lvector[2], true);

  // cross_equal: lvector[0] = lvector[0] x lvector[1];

  cross_equal(lvector[0], lvector[1], true);

  cout << "cross_equal(lvector[0], lvector[1]):" << endl;
  print_section(lvector[0]);

  //============================================================================

  // Detach the sections.

  for(int i=0; i<num_sections; ++i)
  {
    lvector[i].detach_from_state();
  }

  // Postconditions:

  // Exit:
}

///
const sheaf::poset_path&
fiber_bundle::
make_test_base_space(fiber_bundles_namespace& xns,
                     const size_type& xi_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xi_size > 0);

  // Body:

  static const poset_path lresult("test_mesh", "test_mesh_block"); 

  base_space_poset& lmesh = xns.new_base_space<structured_block_1d>(lresult.poset_name());

  structured_block_1d lblock(&lmesh, xi_size, true);
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
fiber_bundle::
make_test_base_space(fiber_bundles_namespace& xns,
                     const size_type& xi_size,
                     const size_type& xj_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  static const poset_path lresult("test_mesh", "test_mesh_block"); 

  base_space_poset& lmesh = xns.new_base_space<structured_block_2d>(lresult.poset_name());

  structured_block_2d lblock(&lmesh, xi_size, xj_size, true);
  lblock.put_name(lresult.member_name(), true, true);
  lblock.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(lresult, true));

  // Exit:

  return lresult;
}

///
const sheaf::poset_path&
fiber_bundle::
make_test_base_space(fiber_bundles_namespace& xns,
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

  base_space_poset& lmesh = xns.new_base_space<structured_block_3d>(lresult.poset_name());
  
  structured_block_3d lblock(&lmesh, xi_size, xj_size, xk_size, true);
  lblock.put_name(lresult.member_name(), true, true);
  lblock.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(lresult, true));

  // Exit:

  return lresult;
}

