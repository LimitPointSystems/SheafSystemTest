
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

/// @file
/// Implementation for test_fiber_bundles specializations and
//  non-template functions.

#include "test_fiber_bundles.impl.h"

#include "at0_space.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_poset.h"
#include "binary_section_space_schema_member.impl.h"
#include "fiber_bundles_namespace.h"
#include "sec_at0.h"
#include "sec_rep_descriptor_poset.h"
#include "structured_block_1d.h"
#include "test_utils.h"

using namespace std;

// #include "section_space_schema_poset.h"

//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================


//=============================================================================
// SPECIALIZATIONS FOR NAMESPACE_POSET FACET
//=============================================================================

//===========================================================================
// Specialization for "sec_rep_descriptor_poset":
//===========================================================================

template<>
bool
fiber_bundle::
test_fiber_bundles_namespace_poset_facet<fiber_bundle::sec_rep_descriptor_poset>
(fiber_bundle::fiber_bundles_namespace& xns, const sheaf::poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string& lname = sec_rep_descriptor::standard_host_path().poset_name();

  print_header("Begin testing " + lname);

  bool lresult = true;

  typedef fiber_bundle::sec_rep_descriptor_poset P;

  P& lposet = xns.member_poset<P>(lname);

  lresult &= test_fiber_bundles_namespace_poset_facet(xns, lposet);

  print_footer("End testing " + lname);

  // Postconditions:

  // Exit:

  return lresult;
}

//===========================================================================
// Specialization for "binary_section_space_schema_poset":
//===========================================================================

template<>
bool
fiber_bundle::
test_fiber_bundles_namespace_poset_facet
<fiber_bundle::binary_section_space_schema_poset>
  (fiber_bundle::fiber_bundles_namespace& xns,
   const sheaf::poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string lname = "binary_section_space_schema_poset_test";

  print_header("Begin testing " + lname);

  bool lresult = true;

  typedef fiber_bundle::binary_section_space_schema_poset P;
  typedef fiber_bundle::binary_section_space_schema_member M;
  typedef fiber_bundle::sec_at0 S;

  P& lposet = M::standard_host<S>(xns, xbase_path, sec_at0::standard_rep_path(), "", false);

  lresult &= test_fiber_bundles_namespace_poset_facet<P>(xns, lposet);

  print_footer("End testing " + lname);

  // Postconditions:

  // Exit:

  return lresult;
}

//===========================================================================
// Specialization for "base_space_poset":
//===========================================================================

template<>
bool
fiber_bundle::
test_fiber_bundles_namespace_poset_facet<fiber_bundle::base_space_poset>
  (fiber_bundle::fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  const string lname = "base_space_poset_1d";

  print_header("Begin testing " + lname);

  bool lresult = true;

  typedef fiber_bundle::base_space_poset P;

  P& lposet = fiber_bundle::structured_block_1d::standard_host(xns, lname, false);

  lresult &= test_fiber_bundles_namespace_poset_facet(xns, lposet);

  print_footer("End testing " + lname);

  // Postconditions:

  // Exit:

  return lresult;
}

//=============================================================================
//=============================================================================


