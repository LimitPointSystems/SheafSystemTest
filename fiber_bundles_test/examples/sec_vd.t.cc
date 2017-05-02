
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

/// @example examples/sec_vd.t.cc
/// Simple driver to test sec_vd.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/binary_section_space_schema_poset.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_at0_space.h"
#include "SheafSystem/sec_vd.h"
#include "SheafSystem/std_fstream.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/unstructured_block.h"

using namespace std;
using namespace fiber_bundle;

int
main(int argc, char* argv[])
{
  fiber_bundles_namespace* test_namespace = new fiber_bundles_namespace("sec_vd.t");
  test_namespace->get_read_write_access();

  cout << *test_namespace << endl;

  // Make quad mesh

  base_space_poset* lmesh =
    &test_namespace->new_base_space<unstructured_block>("quad_mesh", "", "", 2, true);
  lmesh->get_read_write_access();

  // Make quad block base space

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "quad_complex");

  unstructured_block lbase_space(lmesh, lproto_path, 1, 1, true);
  lbase_space.put_name("quad_block", true, false);

  // Create the scalar section space

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", lbase_space.path(false), "");

  poset_path lschema_path =
    test_namespace->new_scalar_section_space_schema<sec_at0>("at0_on_quad_mesh_schema", largs);

  largs = sec_at0_space::make_arg_list();

  sec_at0::host_type& srs =
    test_namespace->new_scalar_section_space<sec_at0>("at0_on_quad_mesh",
						      largs, lschema_path);

  srs.get_read_write_access();

  // Create a field in the section space

  srs.begin_jim_edit_mode();

  ///@issue Using sec_vd below  blows an assertion in postorder_iterator.cc
  ///         Switching to sec_at0 works.

  //sec_at0 srs_mbr(srs);
  sec_vd srs_mbr(&srs);

  srs_mbr.put_name("scalar field", true, false);

  double dofs[6] = {0.0, 1.0, 2.0, 3.0};
  srs_mbr.put_dof_tuple(dofs, sizeof(dofs));

  srs.end_jim_edit_mode();

  // Write to stdout

  cout << *test_namespace << endl;

  srs_mbr.detach_from_state();

  // Clean-up

  lbase_space.detach_from_state();
  lmesh->release_access();
  delete test_namespace;

  return 0;
}
