
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


/// @example section_spaces/multi_section.t.cc
/// test driver for mutli-valued sections.

#include "arg_list.h"
#include "assert_contract.h"
#include "at0_space.h"
#include "base_space_member.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_poset.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "preorder_iterator.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_e1.h"
#include "structured_block_1d.h"
#include "structured_block_3d.h"
#include "tern.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
///
/// Creates a 1D base space with a simple decomposition.
///
structured_block_1d* make_1d_base_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create the host.

  base_space_poset& lbase_host = structured_block_1d::standard_host(xns, "1d_base_space", false);

  lbase_host.get_read_write_access();

  // Create the mesh itself.

  structured_block_1d* result =
    new structured_block_1d(&lbase_host, 4, true);
  result->put_name("mesh", true, false);

  // Create a decomposition.

  subposet lparts(&lbase_host);
  lparts.put_name("parts", true, false);

  const index_space_handle& lele_space = lbase_host.elements().id_space();

  scoped_index lexpansion[2];

  lexpansion[0].put(lele_space, 0);
  lexpansion[1].put(lele_space, 1);

  base_space_member lpart0(&lbase_host, lexpansion, 2, tern::NEITHER, false);
  lpart0.put_name("part0", true, true);
  lparts.insert_member(lpart0.index());
  lpart0.detach_from_state();

  lexpansion[0].put(lele_space, 2);
  lexpansion[1].put(lele_space, 3);

  base_space_member lpart1(&lbase_host, lexpansion, 2, tern::NEITHER, false);
  lpart1.put_name("part1", true, true);
  lparts.insert_member(lpart1.index());
  lpart1.detach_from_state();

  lparts.detach_from_state();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_read_write_accessible());

  // Exit:

  return result;
}


///
/// Creates a section space on base space "1d_base_space".
///
sec_at0_space& make_1d_section_space(fiber_bundles_namespace& xns,
				     const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Make the section space.

  sec_at0_space& result =
    sec_at0::standard_host(xns, xbase_path, "", "", "", false);

  result.get_read_write_access();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit:

  return result;
}

///
/// Creates a (single-valued) section in section space xhost.
///
void make_section(sec_at0_space& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  sec_at0 lsec(&xhost);
  lsec.put_name("single_valued_section", true, true);

  sec_at0::fiber_type::volatile_type lfiber = 0.0;
  index_space_iterator& litr =
    lsec.schema().discretization_id_space().get_iterator();
  while(!litr.is_done())
  {
    lsec.put_fiber(litr.pod(), lfiber);
   
    lfiber[0] += 1.0;
    litr.next();
  }
  lsec.schema().discretization_id_space().release_iterator(litr);

  lsec.detach_from_state();

  // Postconditions:

  ensure(xhost.state_is_read_write_accessible());

  // Exit:

  return;
}

///
/// Creates a multi-valued section in section space xhost.
///
void make_multi_section(sec_at0_space& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  base_space_member lpart0(&xhost.schema().host()->base_space(), "part0");

  sec_at0 lsec0(&xhost, lpart0);
  lsec0.put_name("section_on_part0", true, false);

  sec_at0::fiber_type::volatile_type lfiber0 = 0.0;
  index_space_iterator& litr0 =
    lsec0.schema().discretization_id_space().get_iterator();
  while(!litr0.is_done())
  {
    lsec0.put_fiber(litr0.pod(), lfiber0);
   
    lfiber0[0] += 1.0;
    litr0.next();
  }
  lsec0.schema().discretization_id_space().release_iterator(litr0);

  base_space_member lpart1(&xhost.schema().host()->base_space(), "part1");

  sec_at0 lsec1(&xhost, lpart1);
  lsec1.put_name("section_on_part1", true, false);

  sec_at0::fiber_type::volatile_type lfiber1 = 0.0;
  index_space_iterator& litr1 =
    lsec1.schema().discretization_id_space().get_iterator();
  while(!litr1.is_done())
  {
    lsec1.put_fiber(litr1.pod(), lfiber1);
   
    lfiber1[0] += 1.0;
    litr1.next();
  }
  lsec1.schema().discretization_id_space().release_iterator(litr1);

  // Make the multi-section.

  abstract_poset_member* lmulti = lsec0.l_join(&lsec1);
  lmulti->put_name("multi_section0", true, false);


  lpart0.detach_from_state();
  lsec0.detach_from_state();

  lpart1.detach_from_state();
  lsec1.detach_from_state();

  lmulti->detach_from_state();
  delete lmulti;

  // Postconditions:

  ensure(xhost.state_is_read_write_accessible());

  // Exit:

  return;
}

///
/// Creates a multi-valued section in section space xhost
/// using the multi-section constructor.
///
void instantiate_multi_section(sec_at0_space& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  subposet lparts(xhost.schema().base_space().host(), "parts");
  sec_at0 lmulti_section(&xhost, lparts, false);
  lmulti_section.put_name("multi_section1", true, false);

  cout << xhost << endl;

  sec_at0 lbranch;

  preorder_iterator litr(lmulti_section, "jims", DOWN, NOT_STRICT);

  while(!litr.is_done())
  {
    lbranch.attach_to_state(&xhost, litr.index());
    sec_at0::fiber_type::volatile_type lfiber = 0.0;
    index_space_iterator& ldisc_itr =
      lbranch.schema().discretization_id_space().get_iterator();
    while(!ldisc_itr.is_done())
    {
      lbranch.put_fiber(ldisc_itr.pod(), lfiber);
   
      lfiber[0] += 1.0;
      ldisc_itr.next();
    }
    lbranch.schema().discretization_id_space().release_iterator(ldisc_itr);

    litr.truncate();
  }

  lbranch.detach_from_state();
  lparts.detach_from_state();
  lmulti_section.detach_from_state();

  // Postconditions:

  ensure(xhost.state_is_read_write_accessible());

  // Exit:

  return;
}

///
/// Creates a 3D base space with a simple decomposition.
///
structured_block_3d* make_3d_base_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create the host.

  base_space_poset& lbase_host = structured_block_3d::standard_host(xns, "3d_base_space", false);

  lbase_host.get_read_write_access();

  // Create the mesh itself.

  structured_block_3d* result =
    new structured_block_3d(&lbase_host, 3, 2, 1, true);
  result->put_name("mesh", true, false);

  // Create a decomposition.

  subposet lparts(&lbase_host);
  lparts.put_name("parts", true, false);

  const index_space_handle& lele_space = lbase_host.elements().id_space();

  scoped_index lexpansion[3];

  lexpansion[0].put(lele_space, 0);
  lexpansion[1].put(lele_space, 1);
  lexpansion[2].put(lele_space, 2);

  base_space_member lpart0(&lbase_host, lexpansion, 3, tern::NEITHER, false);
  lpart0.put_name("part0", true, true);
  lparts.insert_member(lpart0.index());
  lpart0.detach_from_state();

  lexpansion[0].put(lele_space, 3);
  lexpansion[1].put(lele_space, 4);
  lexpansion[2].put(lele_space, 5);

  base_space_member lpart1(&lbase_host, lexpansion, 3, tern::NEITHER, false);
  lpart1.put_name("part1", true, true);
  lparts.insert_member(lpart1.index());
  lpart1.detach_from_state();

  lparts.detach_from_state();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_read_write_accessible());

  // Exit:

  return result;
}


///
/// Creates a section space on base space "3d_base_space".
///
sec_at0_space& make_3d_section_space(fiber_bundles_namespace& xns,
				     const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  sec_at0_space& result =
    sec_at0::standard_host(xns, xbase_path, "", "", "", false);

  result.get_read_write_access();

  // Postconditions:

  ensure(result.state_is_read_write_accessible());

  // Exit:

  return result;
}

///
/// Creates a (single-valued) section in section space xhost.
///
void make_3d_section(sec_at0_space& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  sec_at0 lsec(&xhost);
  lsec.put_name("single_valued_section", true, true);

  sec_at0::fiber_type::volatile_type lfiber = 0.0;
  index_space_iterator& litr =
    lsec.schema().discretization_id_space().get_iterator();
  while(!litr.is_done())
  {
    lsec.put_fiber(litr.pod(), lfiber);
   
    lfiber[0] += 1.0;
    litr.next();
  }
  lsec.schema().discretization_id_space().release_iterator(litr);

  lsec.detach_from_state();

  // Postconditions:

  ensure(xhost.state_is_read_write_accessible());

  // Exit:

  return;
}

///
/// Creates a multi-valued section in section space xhost
/// using the multi-section constructor.
///
void instantiate_3d_multi_section(sec_at0_space& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_write_accessible());

  // Body:

  subposet lparts(xhost.schema().base_space().host(), "parts");
  sec_at0 lmulti_section(&xhost, lparts, false);
  lmulti_section.put_name("multi_section1", true, false);

  cout << xhost << endl;

  sec_at0 lbranch;

  preorder_iterator litr(lmulti_section, "jims", DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    lbranch.attach_to_state(&xhost, litr.index());

    sec_at0::fiber_type::volatile_type lfiber = 0.0;
    index_space_iterator& ldisc_itr =
      lbranch.schema().discretization_id_space().get_iterator();
    while(!ldisc_itr.is_done())
    {
      lbranch.put_fiber(ldisc_itr.pod(), lfiber);
   
      lfiber[0] += 1.0;
      ldisc_itr.next();
    }
    lbranch.schema().discretization_id_space().release_iterator(ldisc_itr);

    litr.truncate();
  }

  lbranch.detach_from_state();
  lparts.detach_from_state();
  lmulti_section.detach_from_state();

  // Postconditions:

  ensure(xhost.state_is_read_write_accessible());

  // Exit:

  return;
}

} // end unnamed namespace

///
/// Main test routine.
///
int main()
{

  fiber_bundles_namespace lns("multi_section.t");

  lns.get_read_write_access();

  structured_block_1d* lmesh = make_1d_base_space(lns);

  cout << *lmesh->host() << endl;

  sec_at0_space& lspace = make_1d_section_space(lns, lmesh->path());

  make_section(lspace);

  make_multi_section(lspace);

  instantiate_multi_section(lspace);

  cout << *lmesh->host() << endl;
  cout << lspace << endl;

  structured_block_3d* lmesh_3d = make_3d_base_space(lns);

  cout << *lmesh_3d->host() << endl;

  sec_at0_space& lspace_3d = make_3d_section_space(lns, lmesh_3d->path());

  make_3d_section(lspace_3d);

  instantiate_3d_multi_section(lspace_3d);

  cout << *lmesh_3d->host() << endl;
  cout << lspace_3d << endl;

  // Exit:

  return 0;
}


