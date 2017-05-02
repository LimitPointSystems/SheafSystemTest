
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

// Test driver for partial fields.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "SheafSystem/binary_section_space_schema_poset.h"
#include "SheafSystem/discretization_iterator.h"
#include "SheafSystem/structured_block_1d.h"
#include "SheafSystem/sec_e3.h"
#include "SheafSystem/sec_at0_space.h"
#include "SheafSystem/sec_at1_space.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/tern.h"
#include "SheafSystem/total_poset_member.h"

using namespace std;
using namespace fiber_bundle;

///
int
main(int argc, char* argv[])
{
  int result = 0;

  // Preconditions:


  // Body:

  fiber_bundles_namespace lns("partial_field.t");
  lns.get_read_write_access();

  // Make triangle mesh

  base_space_poset& lbase_host = lns.new_base_space<structured_block_1d>("segment_mesh");
  lbase_host.get_read_write_access();

  // Make segment block base space

  structured_block_1d lbase_space(&lbase_host, 8, true);
  lbase_space.put_name("segment_block", true, false);

  // Make two parts.

  subposet lparts(&lbase_host);
  lparts.put_name("parts", true, false);

  const index_space_handle& lele_space = lbase_host.elements().id_space();

  scoped_index lexpansion[4];

  lexpansion[0].put(lele_space, 0);
  lexpansion[1].put(lele_space, 1);
  lexpansion[2].put(lele_space, 2);
  lexpansion[3].put(lele_space, 3);

  base_space_member lpart0(&lbase_host, lexpansion, 4, tern::NEITHER, false);
  lpart0.put_name("part0", true, true);
  lparts.insert_member(lpart0.index());
  lpart0.detach_from_state();

  lexpansion[0].put(lele_space, 4);
  lexpansion[1].put(lele_space, 5);
  lexpansion[2].put(lele_space, 6);
  lexpansion[3].put(lele_space, 7);

  base_space_member lpart1(&lbase_host, lexpansion, 4, tern::NEITHER, false);
  lpart1.put_name("part1", true, true);
  lparts.insert_member(lpart1.index());
  lpart1.detach_from_state();

  lparts.detach_from_state();

  // Create a member equivalent to the base space.

  base_space_member lbase_jem(lbase_space, true);
  lbase_jem.put_name("base_jem", false, false);

  // Make vector field.

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", lbase_space.path(false), "");

  poset_path lscalar_schema_path =
    lns.new_scalar_section_space_schema<sec_at0>("scalar_fields_schema", largs);

  poset_path lvector_schema_path =
    lns.new_vector_section_space_schema<sec_e3>("vector_fields_schema", largs);

  sec_e3::host_type& lsrs =
    lns.new_vector_section_space<sec_e3>("vector_fields", "", lvector_schema_path,
					  "scalar_fields", "", lscalar_schema_path);

  lsrs.get_read_write_access();

  // Create a total field

  sec_e3 ltotal_field(&lsrs);
  ltotal_field.put_name("total_field", true, false);
  sec_e3::dof_type ldof_buf[3];
  sec_e3::dof_type lval = 0.0;
  discretization_iterator ltotal_itr(ltotal_field.schema());
  while(!ltotal_itr.is_done())
  {
    ldof_buf[0] = lval + 0.1;
    ldof_buf[1] = lval + 0.2;
    ldof_buf[2] = lval + 0.3;
    ltotal_field.put_fiber(ltotal_itr.index(), ldof_buf,
			   3*sizeof(sec_e3::dof_type), false);
    lval++;
    ltotal_itr.next();
  }

  ltotal_field.detach_from_state();

  // Create a total field on a jem of the base space.

  sec_e3 ljem_field(&lsrs, lbase_jem);
  ljem_field.put_name("jem_field", true, false);
  lval = 0.0;
  discretization_iterator ljem_itr(ljem_field.schema());
  while(!ljem_itr.is_done())
  {
    ldof_buf[0] = lval + 0.1;
    ldof_buf[1] = lval + 0.2;
    ldof_buf[2] = lval + 0.3;
    ljem_field.put_fiber(ljem_itr.index(), ldof_buf,
			 3*sizeof(sec_e3::dof_type), false);
    lval++;
    ljem_itr.next();
  }

  ljem_field.detach_from_state();

  // Create a partial field on domain 0.

  total_poset_member ldomain(&lbase_host, "part0");

  sec_e3 lpartial_field;
  lpartial_field.new_jim_state(&lsrs, ldomain);
  lpartial_field.put_name("partial_field_on_part0", true, false);
  discretization_iterator lpartial_itr(lpartial_field.schema());
  while(!lpartial_itr.is_done())
  {
    ldof_buf[0] = lval + 0.01;
    ldof_buf[1] = lval + 0.02;
    ldof_buf[2] = lval + 0.03;
    lpartial_field.put_fiber(lpartial_itr.index(), ldof_buf,
			     3*sizeof(sec_e3::dof_type), false);
    lval++;
    lpartial_itr.next();
  }

  // Create a partial field on domain 1.

  ldomain.attach_to_state(&lbase_host, "part1");

  lpartial_field.new_jim_state(&lsrs, ldomain);
  lpartial_field.put_name("partial_field_on_part1", true, false);
  lpartial_itr.put_schema_anchor(lpartial_field.schema());
  lpartial_itr.reset();
  while(!lpartial_itr.is_done())
  {
    ldof_buf[0] = lval + 0.001;
    ldof_buf[1] = lval + 0.002;
    ldof_buf[2] = lval + 0.003;
    lpartial_field.put_fiber(lpartial_itr.index(), ldof_buf,
			     3*sizeof(sec_e3::dof_type), false);
    lval++;
    lpartial_itr.next();
  }

  lpartial_field.detach_from_state();
  ldomain.detach_from_state();

  lsrs.release_access();


  // Print the name space.

  cout << lns << endl;

  // Write the name space to disk.

  storage_agent sa("partial_field.t.hdf");
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);
  sa.write_entire(lns);

  // Clean-up

  lbase_jem.detach_from_state();
  lbase_space.detach_from_state();
  lbase_host.release_access();

  // Postconditions:


  // Exit:

  return result;
}




