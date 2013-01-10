// $RCSfile: block_scaling_test.cc,v $ $Revision: 1.1.8.2 $ $Date: 2013/01/08 14:59:48 $

// $Name: id-space-merge-4 $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
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

#include "array_index_space_state.h"
#include "hash_index_space_state.h"
#include "interval_index_space_state.h"
#include "list_index_space_state.h"
#include "offset_index_space_state.h"
#include "primary_index_space_state.h"
#include "primary_sum_index_space_state.h"
#include "primitives_index_space_state.h"
#include "section_space_schema_jims_index_space_state.h"
#include "singleton_index_space_state.h"
#include "reserved_primary_index_space_state.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

void
fiber_bundle::
pools_size(size_type& xhandle_ct, size_type& xhandle_deep_size)
{
  // Preconditions:

  // Body:

  // The count of the static handles.

  xhandle_ct =
    interval_index_space_state::handle_pool_ct() +
    mutable_index_space_state::handle_pool_ct() +
    offset_index_space_state::handle_pool_ct() +
    primary_index_space_state::handle_pool_ct() +
    primary_sum_index_space_state::handle_pool_ct() +
    singleton_index_space_state::handle_pool_ct() +
    hub_index_space_handle::handle_pool_ct() +
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
    hub_index_space_handle::iterator_pool_ct() +
    section_space_schema_jims_index_space_state::iterator_pool_ct();

  // The deep size of the static handles.

  xhandle_deep_size =
    interval_index_space_state::handle_pool_deep_size() +
    mutable_index_space_state::handle_pool_deep_size() +
    offset_index_space_state::handle_pool_deep_size() +
    primary_index_space_state::handle_pool_deep_size() +
    primary_sum_index_space_state::handle_pool_deep_size() +
    singleton_index_space_state::handle_pool_deep_size() +
    reserved_primary_index_space_state::handle_pool_deep_size() +
    hub_index_space_handle::handle_pool_deep_size() +
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
    hub_index_space_handle::iterator_pool_deep_size() +
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
    new_host_space<sec_at0>(xns, "property_section_space",
			    "sec_rep_descriptors/vertex_vertex_constant",
			    xblock.path(false));

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
    new_host_space<sec_at0>(xns, "property_section_space",
			    "sec_rep_descriptors/vertex_vertex_constant",
			    xblock.path(false));

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
    new_host_space<sec_at0>(xns, "property_section_space",
			    "sec_rep_descriptors/vertex_vertex_constant",
			    xblock.path(false));

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
    new_host_space<sec_at0>(xns, "property_section_space",
			    xblock.path(false));

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
    new_host_space<sec_at0>(xns, "property_section_space",
			    xblock.path(false));

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
    new_host_space<sec_at0>(xns, "property_section_space",
			    xblock.path(false));

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
    new_host_space<sec_at0>(xns, "property_section_space",
			    xblock.path(false));

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
    new_host_space<sec_at0>(xns, "property_section_space",
			    xblock.path(false));

  // Postconditions:

  // Exit:

  return result;
}

