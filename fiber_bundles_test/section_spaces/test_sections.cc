
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

// Implementation for test_sections non template functions.

#include "test_sections.impl.h"

#include "fiber_bundles_namespace.h"
#include "sec_e3.h"
#include "sec_e2.h"
#include "sec_tuple.h"
#include "sec_rep_space.h"
#include "std_iostream.h"
#include "std_sstream.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "test_utils.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.
using namespace fiber_bundle::sec_e3_algebra;
using namespace fiber_bundle::sec_at0_algebra;

//==============================================================================
//==============================================================================

///
void
fiber_bundle::
create_section_space_name(const std::string& xbase_name, std::string& xresult)
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
print_section_space(fiber_bundles_namespace& xns, const std::string& xname)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  sec_rep_space& lspace = xns.member_poset<sec_rep_space>(xname, false);
  cout << lspace << endl;

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

  base_space_poset& lmesh = structured_block_1d::standard_host(xns, lresult.poset_name(), false);

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

  base_space_poset& lmesh = structured_block_2d::standard_host(xns, lresult.poset_name(), false);

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

  base_space_poset& lmesh = structured_block_3d::standard_host(xns, lresult.poset_name(), false);

  structured_block_3d lblock(&lmesh, xi_size, xj_size, xk_size, true);
  lblock.put_name(lresult.member_name(), true, true);
  lblock.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(lresult, true));

  // Exit:

  return lresult;
}

sheaf::poset_path
fiber_bundle::
make_test_base_space(int xdim, fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(1 <= xdim && xdim <= 3);

  poset_path lresult;
  if(xdim == 1)
  {
    lresult = make_test_base_space(xns, 2);
  }
  else if(xdim == 2)
  {
    lresult = make_test_base_space(xns, 2, 2);
  }
  else //xdim==3
  {
    lresult = make_test_base_space(xns, 2, 2, 2);
  }

  // Postconditions:

  ensure(!lresult.empty());
  ensure(xns.contains_poset_member(lresult, true));

  // Exit:

  return lresult;
}


template<>
void
fiber_bundle::
test_section_common_unattached<fiber_bundle::sec_tuple>()
{
  // Preconditions:

  // Body:

  //==========================================================================

  cout << boolalpha;

  typedef sec_tuple S;
  typedef S::fiber_type F;

  //static const string& static_class_name();

  print_subheader("Test static const string& static_class_name()");

  const string& lname = S::static_class_name();
  cout << "  lname = " << lname << endl;

  //==========================================================================

  //S();
  print_subheader("Test default constructor: " + lname + "()");

  S lsection;
  cout << "  lsection = " << lsection << endl;

  //S(const S& xother);
  print_subheader("Test copy constructor: " + lname
                  + "(const " + lname +"& xother)");

  S lsection_copy(lsection);
  cout << "  lsection_copy = " << lsection_copy << endl;

  //S& operator=(const S& xother);
  print_subheader("Test assignment operator: " + lname 
                  + "& operator=(const " + lname + "& xother)");
 
  S lsection_assign = lsection;
  cout << "  lsection_assign = " << lsection_assign << endl;

  //S& operator=(const ed_lite& xother);

  ////ed_lite led_lite;
  ////S& lsection_lite_assign = led_lite;

  //$$SCRIBBLE: No tuple::fiber_prototype()

  ////virtual const fiber_type& fiber_prototype() const;
  //print_subheader("Test virtual const fiber_type& fiber_prototype() const"); 

  //const F& lfiber_type = lsection.fiber_prototype();

  // Can't print because it's not attached.
  //cout << "  lfiber_type = " << lfiber_type << endl;

  //virtual S* clone() const;
  print_subheader("Test virtual " + lname +"* clone() const"); 

  S* lsection_clone = lsection.clone();
  cout << "  *lsection_clone = " << *lsection_clone << endl;

  // Not attached; so won't work;
  //S* lsection_clone2 = lsection.clone(false, false);

  //virtual const string& class_name() const;
  print_subheader("Test virtual const string& class_name() const"); 

  const string& lclass_name = lsection.class_name();
  cout << "  lclass_name = " << lclass_name << endl;

  //bool fiber_is_ancestor_of(const any* xother) const;
  print_subheader("Test bool fiber_is_ancestor_of(const any* xother) const"); 

  bool lfiber_is_ancestor_of = lsection.fiber_is_ancestor_of(lsection_clone);
  cout << "lfiber_is_ancestor_of = " << lfiber_is_ancestor_of << endl;

  //bool is_ancestor_of(const any* xother) const;
  print_subheader("Test bool is_ancestor_of(const any* xother) const"); 

  bool lis_ancestor_of = lsection.is_ancestor_of(lsection_clone);
  cout << "lis_ancestor_of = " << lis_ancestor_of << endl;

  //bool invariant() const;
  print_subheader("Test bool invariant() const"); 

  bool linvariant = lsection.invariant();
  cout << "linvariant = " << linvariant  << endl;

  //==========================================================================


  // Postconditions:

  // Exit:

  return;

}

template<>
void
fiber_bundle::
test_section_common_attached<fiber_bundle::sec_tuple, fiber_bundle::sec_e2>
    (fiber_bundles_namespace& xns, int xdim)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(1<=xdim && xdim<=3);

  // Body:

  typedef sec_tuple SB; // base
  typedef sec_e2 SD;    //derived

  typedef SD::fiber_type F;
  typedef F::volatile_type V;

  //==========================================================================

  // Make a base space.

  const poset_path& lbase_path = make_test_base_space(xdim, xns);

  SD lvector[2];
  make_test_sections(xns, lbase_path,
                     "test_section_space", "vector",
                     lvector, 2);

  lvector[0].get_read_write_access();
  lvector[1].get_read_write_access();

  poset_path lpath0 = lvector[0].path();
  poset_path lpath1 = lvector[1].path();

  scoped_index lindex0 = lvector[0].index();
  scoped_index lindex1 = lvector[1].index();

  sec_rep_space* lhost = lvector[0].host();

  //SB(const sec_rep_space* xhost, const scoped_index& xindex);

  SB lsec2(lhost, lindex0);

  lsec2.detach_from_state();

  //SB(const sec_rep_space* xhost, const string& xname);

  SB lsec3(lhost, lpath0.member_name());

  lsec3.detach_from_state();

  //SB(const namespace_poset* xnamespace,
  //     const poset_path& xpath,
  //     bool xauto_access = true);

  SB lsec0(&xns, lpath0, true);

  lsec0.detach_from_state();

  //explicit SB(const sec_rep_space_member* xother);

  SB lsec1(&lvector[0]);

  // Don't detach here so we can use it below.
  //lsec1.detach_from_state();

  //SB(sec_rep_space* xhost,
  //   section_dof_map* xdof_map = 0,
  //   bool xauto_access = true);

  SB lsec4(lhost);

  lsec4.detach_from_state();

  //virtual SB& operator=(const abstract_poset_member& xother);

  abstract_poset_member* lapm = &lsec1;
  lsec1 = *lapm;

  //==========================================================================

  //SB& operator=(V& xfiber);

  //V lfiber_lite;
  //lsec1 = lfiber_lite;

  //SB& operator=(const F& xfiber);

  //typename F::host_type& lfiber_host = xns.new_fiber_space<F>();
  //lfiber_host.get_read_write_access(true);

  //F lfiber(&lfiber_host);
  //lsec1 = lfiber;

  lsec1.detach_from_state();
  //lfiber.detach_from_state();

  //==========================================================================

  //SB& operator=(const SB& xother)

  SB lbase = lvector[0];
  lbase = lvector[1];

  lbase.detach_from_state();

  //==========================================================================

  // Cleanup.

  lvector[0].detach_from_state();
  lvector[1].detach_from_state();

  //==========================================================================

  // Postconditions:

  // Exit:

  return;

}

