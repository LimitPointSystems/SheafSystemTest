
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
/// Interface for fiber_bundles test function templates.

#ifndef TEST_FIBER_BUNDLES_H
#define TEST_FIBER_BUNDLES_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef SEC_REP_DESCRIPTOR_POSET_H
#include "sec_rep_descriptor_poset.h"
#endif

#ifndef BINARY_SECTION_SPACE_SCHEMA_POSET_H
#include "binary_section_space_schema_poset.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_spaceposet.h"
#endif

namespace fiber_bundle
{

//=============================================================================
// ABSTRACT_POSET_MEMBER FACET
//=============================================================================

//$$TODO: Explain template parameters.

///
/// Test the templated non-class functions of class abstract_poset_member
/// for volatile fiber types.
///
template<typename VB, typename VD>
bool
test_volatile_abstract_poset_member_facet();

///
/// Test the templated non-class functions of class abstract_poset_member.
/// for volatile fiber types.
///
template<typename V>
bool
test_volatile_abstract_poset_member_facet();

///
/// Test the templated non-class functions of class abstract_poset_member.
/// for persistent fiber types.
///
template<typename PB, typename PD>
bool
test_persistent_abstract_poset_member_facet(fiber_bundles_namespace& xns);

///
/// Test the templated non-class functions of class abstract_poset_member.
/// for persistent fiber types.
///
template<typename P>
bool
test_persistent_abstract_poset_member_facet(fiber_bundles_namespace& xns);

///
/// True if B is a base class of D; otherwise false.
/// Function (inefficient) similar to type_traits/is_base_of (c++11),
/// only for use with the above functions.
///
template<typename B, typename D>
bool
is_base_of();

//============================================================================
// NAMESPACE_POSET FACET
//============================================================================

///
///
///
template<typename S>
bool
test_fiber_bundles_namespace_poset_facet(fiber_bundles_namespace& xns,
                                         S& lspace);

///
///
///
template<typename T>
bool
test_fiber_bundles_namespace_poset_facet(fiber_bundles_namespace& xns,
                                         const poset_path& lbase_path);

///
///
///
template<typename T>
bool
test_fiber_bundles_namespace_poset_facet(fiber_bundles_namespace& xns);


///
///
///
template<typename T, typename S>
bool
test_fiber_bundles_namespace_poset_facet(fiber_bundles_namespace& xns,
                                         const poset_path& lbase_path);

///
/// Specialization for sec_rep_descriptor_poset.
///
template<>
SHEAF_DLL_SPEC
bool
test_fiber_bundles_namespace_poset_facet<sec_rep_descriptor_poset>
  (fiber_bundles_namespace& xns, const poset_path& xbase_path);

///
/// Specialization for binary_section_space_schema_poset.
///
template<>
SHEAF_DLL_SPEC
bool
test_fiber_bundles_namespace_poset_facet<binary_section_space_schema_poset>
  (fiber_bundles_namespace& xns, const poset_path& xbase_path);


///
/// Specialization for base_space_poset.
///
template<>
SHEAF_DLL_SPEC
bool
test_fiber_bundles_namespace_poset_facet<base_space_poset>
  (fiber_bundles_namespace& xns);

//=============================================================================

} // namespace fiber_bundle


#endif // ifndef TEST_FIBER_BUNDLES_H
