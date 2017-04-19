
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

// Interface for fields test functions.

#ifndef TEST_FIELDS_H
#define TEST_FIELDS_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef FIELDS_H
#include "SheafSystem/fields.h"
#endif

#ifndef STD_STRING_H
#include "SheafSystem/std_string.h"
#endif

namespace sheaf
{
class SHEAF_DLL_SPEC poset_path;
}

namespace fiber_bundle
{
class SHEAF_DLL_SPEC fiber_bundles_namespace;
class SHEAF_DLL_SPEC sec_ed;
class SHEAF_DLL_SPEC sec_e1;
class SHEAF_DLL_SPEC sec_e2;
class SHEAF_DLL_SPEC sec_e3;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;

//=============================================================================
// TEST ASSIGNMENT
//=============================================================================

///
/// Test assignment operators.
///
template <typename F>
void
test_field_assignment(fiber_bundles_namespace& xns,
                      const poset_path& xbase_path);

//=============================================================================
/// @name ATP FACET
//=============================================================================
//@{

///
/// Test the hook (interior) product of the field_atp facet.
///
template <typename F0, typename F1, typename FR>
void
test_field_hook_product(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path,
                        const poset_path& xcoords_path);

///
/// Test the Hodge star operator of the field_atp facet.
///
template <typename F0, typename FR>
void
test_field_star_operator(fiber_bundles_namespace& xns,
                         const poset_path& xbase_path,
                         const poset_path& xcoords_path);

///
/// Test the wedge (exterior) product of the field_atp facet.
///
template <typename F0, typename F1, typename FR>
void
test_field_wedge_product(fiber_bundles_namespace& xns,
                         const poset_path& xbase_path,
                         const poset_path& xcoords_path);

//@}

//=============================================================================
/// @name AT0 FACET
//=============================================================================
//@{

void
SHEAF_DLL_SPEC
test_field_at0_facet(fiber_bundles_namespace& xns,
                     const poset_path& xbase_path,
                     const poset_path& xcoords_path);

//@}

//=============================================================================
/// @name ED FACET
//=============================================================================
//@{

///
/// Test the field_ed facet.
///
template <typename F>
void
test_field_ed_facet(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path);

//@}

//=============================================================================
/// @name E3 FACET
//=============================================================================
//@{

///
/// Test the field_e3 facet.
/// Not templated since it only applies to field_e3 type.
///
void
SHEAF_DLL_SPEC
test_field_e3_facet(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path);
//@}

//=============================================================================
/// @name JCB FACET
//=============================================================================
//@{

///
/// Test the field_jcb facet.
///
template <typename FJCB, typename FVECTOR,  typename FCOVECTOR>
void
test_field_jcb_facet(fiber_bundles_namespace& xns,
                     const poset_path& xbase_path,
                     const poset_path& xcoords_path);

//@}

//=============================================================================
/// @name MET FACET
//=============================================================================
//@{

///
/// Test the field_met facet.
///
template <typename F, typename FVECTOR>
void
test_field_met_facet(fiber_bundles_namespace& xns,
                     const poset_path& xbase_path,
                     const poset_path& xcoords_path);

//@}

//=============================================================================
/// @name ST2 FACET
//=============================================================================
//@{

///
/// Test the field_st2 facet.
/// The template parameter F represents field type.
///
template <typename F>
void
test_field_st2_facet(fiber_bundles_namespace& xns,
                     const poset_path& xbase_path,
                     const poset_path& xcoords_path);

//@}

//=============================================================================
/// @name TP FACET
//=============================================================================
//@{

///
/// Test the field_tp facet (alt and sym).
///
template <typename TP, typename ATP, typename STP>
void
test_field_tp_facet(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path);


///
/// Test the field_tp facet (tensor product).
///
template <typename F0, typename F1, typename FR>
void
test_field_tensor_product(fiber_bundles_namespace& xns,
                          const poset_path& xbase_path,
                          const poset_path& xcoords_path);


///
/// Test the field_tp facet (contract).
///
template <typename F0, typename FR>
void
test_field_contract(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path);

//@}

//=============================================================================
/// @name VD FACET
//=============================================================================
//@{

///
/// Test the field_vd facet.
///
template <typename F>
void
test_field_vd_facet(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path);

//@}

//==============================================================================
// CONVENIENCE FUNCTIONS
//==============================================================================

///
///  Convenience function to create a unique section space name.
///
void SHEAF_DLL_SPEC create_section_space_name(const std::string& xbase_name, std::string& xresult);

///
/// Convenience function to "pretty-print" print a section to standard out.
///
template <typename T>
void print_field(const T& xfield,
                 const std::string& xindent = "  ",
                 bool xauto_access = true);

///
/// Convenience function to "pretty-print" print the result of an
/// operation to standard out.
///
template <typename T>
void print_result(const std::string& xtext,
                  const T& xfield,
                  const std::string& xindent = "  ",
                  bool xauto_access = true);

//==============================================================================

///
/// Make a structured_block_1d base space for testing.
///
const SHEAF_DLL_SPEC poset_path&
make_test_base_space(fiber_bundle::fiber_bundles_namespace& xns,
                     const size_type& xi_size);

///
/// Make a structured_block_2d base space for testing.
///
const SHEAF_DLL_SPEC poset_path&
make_test_base_space(fiber_bundle::fiber_bundles_namespace& xns,
                     const size_type& xi_size,
                     const size_type& xj_size);

///
/// Make a structured_block_3d base space for testing.
///
const SHEAF_DLL_SPEC poset_path&
make_test_base_space(fiber_bundle::fiber_bundles_namespace& xns,
                     const size_type& xi_size,
                     const size_type& xj_size,
                     const size_type& xk_size);

//==============================================================================

///
/// Make 1d coordinates for testing.
///
SHEAF_DLL_SPEC sheaf::poset_path 
make_test_coordinates_1d(fiber_bundle::fiber_bundles_namespace& xns,
                         const sheaf::poset_path& xbase_path);

///
/// Make 2d coordinates for testing.
///
SHEAF_DLL_SPEC sheaf::poset_path
make_test_coordinates_2d(fiber_bundle::fiber_bundles_namespace& xns,
                         const sheaf::poset_path& xbase_path);

///
/// Make 3d coordinates for testing.
///
SHEAF_DLL_SPEC sheaf::poset_path
make_test_coordinates_3d(fiber_bundle::fiber_bundles_namespace& xns,
                         const sheaf::poset_path& xbase_path);

//==============================================================================

///
/// Convenience function to make fields for testing.
///
template <typename T>
void make_test_sections(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path,
                        const std::string& xbase_property_name,
                        T xsections[],
                        int xnum_sections);

///
/// Convenience function to make fields for testing.
///
template <typename F>
void make_test_fields(fiber_bundles_namespace& xns,
                      const poset_path& xbase_path,
                      const poset_path& xcoords_path,
                      const std::string& xbase_property_name,
                      F xfields[],
                      int xnum_fields);

///
/// Set the dofs of a section for testing.
///
template <typename T>
void set_dofs(T& xresult);

//==============================================================================

///
/// Test some of the common functions in fields which are not tested
/// elsewhere..
///
template<typename F>
void
test_field_common(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path,
                  const poset_path& xcoords_path);

//==============================================================================


} // namespace fields

#endif // ifndef TEST_FIELDS_H
