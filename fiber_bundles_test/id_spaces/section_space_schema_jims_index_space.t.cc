
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

/// @example section_space_schema_jims_index_sapce.t.cc
/// Test driver for the section space schema jims id space.

#include "SheafSystem/section_space_schema_jims_index_space_handle.h"
#include "SheafSystem/section_space_schema_jims_index_space_iterator.h"
#include "SheafSystem/section_space_schema_jims_index_space_state.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/array_index_space_handle.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/ij_product_structure.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystemTest/test_index_spaces.impl.h"

using namespace std;
using namespace fiber_bundle;

int main( int argc, char* argv[])
{
  // Preconditions:

  size_t lbase_ub = argc > 1 ? atoi(argv[1]) : 10;
  size_t lfiber_ub = argc > 2 ? atoi(argv[2]) : 3;
  
  // Body:

  fiber_bundles_namespace::initialize_id_space_prototypes();

  assertion(lbase_ub >= 2);
  assertion(lfiber_ub >= 2);

  // Create the base space family.

  print_out_header("Create Base Space ID Space");

  test_index_space_family lbase_family;
  lbase_family.new_id(); // top
  lbase_family.new_id(); // bottom
  pod_index_type lbase_members_id = lbase_family.new_primary_space(lbase_ub);

  cout << lbase_family << endl;

  // Create the fiber schema family.

  print_out_header("Create Fiber Schema ID Space");

  test_index_space_family lfiber_family;
  lfiber_family.new_id(); // top
  lfiber_family.new_id(); // bottom
  pod_index_type lfiber_members_id = lfiber_family.new_primary_space(lfiber_ub);

  cout << lfiber_family << endl;

  // Create the section space schema family.

  print_out_header("Create Section Space Schema ID Space");

  size_type lsection_ub = lbase_family.hub_id_space().end()*lfiber_family.hub_id_space().end();

  test_index_space_family lsection_family;
  lsection_family.new_id(); // top
  lsection_family.new_id(); // bottom
  pod_index_type lsection_members_id = lsection_family.new_primary_space(lsection_ub);

  cout << lsection_family << endl;

  // Create the product structure of the section space schema members.

  ij_product_structure lsection_space_schema_product(lbase_family.hub_id_space().end(),
						     lfiber_family.hub_id_space().end());
  lsection_family.new_product_structure(lsection_members_id, lsection_space_schema_product);

  // Create base space jims id space (start with only the first half of the
  // base space).

  print_out_header("Create Base Space Jims ID Space");

  array_index_space_handle lbase_jims_id_space =
    array_index_space_handle::new_space(lbase_family, "base_schema_jims",
					false, lbase_ub/2);

  index_space_handle& lbase_id_space = lbase_family.get_id_space(lbase_members_id);
  for(pod_index_type i=0; i<lbase_ub/2; i++)
  {
    push_back(lbase_jims_id_space, lbase_id_space.hub_pod(i));
  }

  // Create the fiber schema jims id space.

  print_out_header("Create Fiber Schema Jims ID Space");

  array_index_space_handle lfiber_jims_id_space =
    array_index_space_handle::new_space(lfiber_family, "fiber_schema_jims",
					false, lfiber_ub);

  index_space_iterator& lfiber_itr = lfiber_family.get_id_space_iterator(lfiber_members_id);
  while(!lfiber_itr.is_done())
  {
    push_back(lfiber_jims_id_space, lfiber_itr.hub_pod());
    lfiber_itr.next();
  }

  lfiber_family.release_id_space_iterator(lfiber_itr);

  // Create the section space schema jims id space.

  print_out_header("Create Section Space Schema Jims ID Space");

  section_space_schema_jims_index_space_handle lsection_jims_id_space =
    section_space_schema_jims_index_space_handle::new_space(lsection_family,
							    "section_space_schema_jims",
							    lbase_jims_id_space,
							    lfiber_jims_id_space,
							    lsection_space_schema_product);

  // Test the handle and iterator facets.

  pod_index_type lspace_id = lsection_jims_id_space.index();

  test_handle_facet<section_space_schema_jims_index_space_handle>(lsection_family, lspace_id);

  test_iterator_facet<section_space_schema_jims_index_space_iterator>(lsection_family, lspace_id);

  test_state_facet(lsection_family, lspace_id, 0, lsection_family.hub_pod(lspace_id, 0));

  // Test modifying the base space.

  print_out_header("Extend Base Space Test");

  for(pod_index_type i=lbase_ub/2; i<lbase_ub; i++)
  {
    push_back(lbase_jims_id_space, lbase_id_space.hub_pod(i));
  }

  lsection_jims_id_space.update();

  test_iterator(lsection_jims_id_space);

  // Done.

  return 0;
}

  
