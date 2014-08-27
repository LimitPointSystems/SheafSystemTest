
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

// Implementation of functions for the block scaling tests.

#include "block_scaling_test.h"
#include "sec_at0.h"
#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "unstructured_block.h"
#include "zone_nodes_block.h"
#include "test_sections.impl.h"

#include "ComLimitPoint/sheaf/array_index_space_state.h"
#include "hash_index_space_state.h"
#include "interval_index_space_state.h"
#include "list_index_space_state.h"
#include "ComLimitPoint/sheaf/offset_index_space_state.h"
#include "primary_index_space_state.h"
#include "primary_sum_index_space_state.h"
#include "primitives_index_space_state.h"
#include "section_space_schema_jims_index_space_state.h"
#include "singleton_index_space_state.h"
#include "reserved_primary_index_space_state.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

void
fiber_bundle::
pools_size(size_type& xhandle_ct, size_type& xhandle_deep_size)
{
  // Preconditions:

  // Body:

  // The count of the static handles.

  xhandle_ct =
    array_index_space_state::handle_pool_ct() +
    hash_index_space_state::handle_pool_ct() +
    interval_index_space_state::handle_pool_ct() +
    list_index_space_state::handle_pool_ct() +
    offset_index_space_state::handle_pool_ct() +
    primary_index_space_state::handle_pool_ct() +
    primary_sum_index_space_state::handle_pool_ct() +
    singleton_index_space_state::handle_pool_ct() +
    reserved_primary_index_space_state::handle_pool_ct() +
    section_space_schema_jims_index_space_state::handle_pool_ct() +
    array_index_space_state::iterator_pool_ct() +
    hash_index_space_state::iterator_pool_ct() +
    interval_index_space_state::iterator_pool_ct() +
    list_index_space_state::iterator_pool_ct() +
    offset_index_space_state::iterator_pool_ct() +
    primary_index_space_state::iterator_pool_ct() +
    primary_sum_index_space_state::iterator_pool_ct() +
    reserved_primary_index_space_state::iterator_pool_ct() +
    singleton_index_space_state::iterator_pool_ct() +
    section_space_schema_jims_index_space_state::iterator_pool_ct();

  // The deep size of the static handles.

  xhandle_deep_size =
    array_index_space_state::handle_pool_deep_size() +
    hash_index_space_state::handle_pool_deep_size() +
    interval_index_space_state::handle_pool_deep_size() +
    list_index_space_state::handle_pool_deep_size() +
    offset_index_space_state::handle_pool_deep_size() +
    primary_index_space_state::handle_pool_deep_size() +
    primary_sum_index_space_state::handle_pool_deep_size() +
    singleton_index_space_state::handle_pool_deep_size() +
    reserved_primary_index_space_state::handle_pool_deep_size() +
    section_space_schema_jims_index_space_state::handle_pool_deep_size() +
    array_index_space_state::iterator_pool_deep_size() +
    hash_index_space_state::iterator_pool_deep_size() +
    interval_index_space_state::iterator_pool_deep_size() +
    list_index_space_state::iterator_pool_deep_size() +
    offset_index_space_state::iterator_pool_deep_size() +
    primary_index_space_state::iterator_pool_deep_size() +
    primary_sum_index_space_state::iterator_pool_deep_size() +
    reserved_primary_index_space_state::iterator_pool_deep_size() +
    singleton_index_space_state::iterator_pool_deep_size() +
    section_space_schema_jims_index_space_state::iterator_pool_deep_size();

  // Postconditions:

  ensure(xhandle_ct >= 0);
  ensure(xhandle_deep_size >= 0);

  // Exit:

  return;
}
  
fiber_bundle::sec_rep_space&
fiber_bundle::
make_scalar_section_space(fiber_bundles_namespace& xns,
			  point_block_1d& xblock)
{
  // Preconditions:

  require(xblock.state_is_read_accessible());

  // Body:

  sec_rep_space& result =
    sec_at0::standard_host(xns, xblock.path(false),
			   "sec_rep_descriptors/vertex_vertex_constant",
			   "", "", false);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::sec_rep_space&
fiber_bundle::
make_scalar_section_space(fiber_bundles_namespace& xns,
			  point_block_2d& xblock)
{
  // Preconditions:

  require(xblock.state_is_read_accessible());

  // Body:


  sec_rep_space& result =
    sec_at0::standard_host(xns, xblock.path(false),
			   "sec_rep_descriptors/vertex_vertex_constant",
			   "", "", false);


  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::sec_rep_space&
fiber_bundle::
make_scalar_section_space(fiber_bundles_namespace& xns,
			  point_block_3d& xblock)
{
  // Preconditions:

  require(xblock.state_is_read_accessible());

  // Body:

  sec_rep_space& result =
    sec_at0::standard_host(xns, xblock.path(false),
			   "sec_rep_descriptors/vertex_vertex_constant",
			   "", "", false);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::sec_rep_space&
fiber_bundle::
make_scalar_section_space(fiber_bundles_namespace& xns,
			  structured_block_1d& xblock)
{
  // Preconditions:

  require(xblock.state_is_read_accessible());

  // Body:

  sec_rep_space& result =
    sec_at0::standard_host(xns, xblock.path(false),
			   "sec_rep_descriptors/vertex_vertex_constant",
			   "", "", false);

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::sec_rep_space&
fiber_bundle::
make_scalar_section_space(fiber_bundles_namespace& xns,
			  structured_block_2d& xblock)
{
  // Preconditions:

  require(xblock.state_is_read_accessible());

  // Body:

  sec_rep_space& result =
    sec_at0::standard_host(xns, xblock.path(false),
			   "", "", "", false);

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::sec_rep_space&
fiber_bundle::
make_scalar_section_space(fiber_bundles_namespace& xns,
			  structured_block_3d& xblock)
{
  // Preconditions:

  require(xblock.state_is_read_accessible());

  // Body:

  sec_rep_space& result =
    sec_at0::standard_host(xns, xblock.path(false),
			   "sec_rep_descriptors/vertex_vertex_constant",
			   "", "", false);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::sec_rep_space&
fiber_bundle::
make_scalar_section_space(fiber_bundles_namespace& xns,
			  zone_nodes_block& xblock)
{
  // Preconditions:

  require(xblock.state_is_read_accessible());

  // Body:

  sec_rep_space& result =
    sec_at0::standard_host(xns, xblock.path(false),
			   "sec_rep_descriptors/vertex_vertex_constant",
			   "", "", false);

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::sec_rep_space&
fiber_bundle::
make_scalar_section_space(fiber_bundles_namespace& xns,
			  unstructured_block& xblock)
{
  // Preconditions:

  require(xblock.state_is_read_accessible());

  // Body:

  sec_rep_space& result =
    sec_at0::standard_host(xns, xblock.path(false),
			   "sec_rep_descriptors/vertex_vertex_constant",
			   "", "", false);

  // Postconditions:

  // Exit:

  return result;
}

