

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for test_fiber_bundles specializations and
//  non-template functions.

#include "test_fiber_bundles.impl.h"

#include "base_space_poset.h"
#include "binary_section_space_schema_poset.h"
#include "fiber_bundles_namespace.h"
#include "sec_at0.h"
#include "sec_rep_descriptor_poset.h"
#include "structured_block_1d.h"
#include "test_utils.h"

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

  arg_list largs = P::make_arg_list("", xbase_path, "");

  poset_path lschema_path =
    xns.new_scalar_section_space_schema<fiber_bundle::sec_at0>
      ("binary_sss_schema", largs);

  P& lposet = xns.member_poset<P>(lschema_path, true);

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

  P& lposet = fiber_bundle::structured_block_1d::new_host(xns, lname, false);

  lresult &= test_fiber_bundles_namespace_poset_facet(xns, lposet);

  print_footer("End testing " + lname);

  // Postconditions:

  // Exit:

  return lresult;
}

//=============================================================================
//=============================================================================


