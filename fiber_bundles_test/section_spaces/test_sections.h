
// $RCSfile: test_sections.h,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:58 $

//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @file
/// Interface for fiber test function templates.

#ifndef TEST_SECTIONS_H
#define TEST_SECTIONS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h" // for size_type
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
class poset_path;
}

namespace fiber_bundle
{

using namespace sheaf;

class fiber_bundles_namespace;

//=============================================================================
// TEST ASSIGNMENT
//=============================================================================

///
/// Test assignment operators.
///
template <typename S>
void
test_assignment(fiber_bundles_namespace& xns,
                const poset_path& xbase_path);

//=============================================================================
// ATP FACET
//=============================================================================

///
/// Test the hook (interior) product of the sec_atp facet.
///
template <typename S0, typename S1, typename SR>
void
test_sec_hook_product(fiber_bundles_namespace& xns,
                      const poset_path& xbase_path);

///
/// Test the Hodge star operator of the sec_atp facet.
///
template <typename S0, typename SR>
void
test_sec_star_operator(fiber_bundles_namespace& xns,
                       const poset_path& xbase_path);

///
/// Test the wedge (exterior) product of the sec_atp facet.
///
template <typename S0, typename S1, typename SR>
void
test_sec_wedge_product(fiber_bundles_namespace& xns,
                       const poset_path& xbase_path);

//=============================================================================
// AT0 FACET
//=============================================================================

SHEAF_DLL_SPEC
void
test_sec_at0_facet(fiber_bundles_namespace& xns,
                   const poset_path& xbase_path);

//=============================================================================
// ED FACET
//=============================================================================

///
/// Test the sec_ed facet.
///
template <typename S>
void
test_sec_ed_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path);

//=============================================================================
// E3 FACET
//=============================================================================

///
/// Test the sec_e3 facet.
/// Not templated since it only has meaning for sec_e3 types.
///
SHEAF_DLL_SPEC
void
test_sec_e3_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path);

//=============================================================================
// JCB FACET
//=============================================================================

///
/// Test the sec_jcb facet.
///
/// template @<typename S@>
template <typename SJAC, typename SVECTOR,  typename SCOVECTOR>
void
test_sec_jcb_facet(fiber_bundles_namespace& xns,
                   const poset_path& xbase_path);

//=============================================================================
// MET FACET
//=============================================================================

///
/// Test the sec_met facet.
///
template <typename S>
void
test_sec_met_facet(fiber_bundles_namespace& xns,
                   const poset_path& xbase_path);


//=============================================================================
// ST2 FACET
//=============================================================================


///@todo:
///
/// Test the sec_met facet.
///
// template <typename S>
// void
// test_sec_st2_facet(fiber_bundles_namespace& xns,
//                    const poset_path& xbase_path);

//=============================================================================
// TP FACET
//=============================================================================

///
/// Test the sec_tp facet (alt and sym).
///
template <typename S0>
void
test_sec_tp_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path);


///
/// Test the sec_tp facet (tensor product).
///
template <typename S0, typename S1, typename SR>
void
test_sec_tensor_product(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path);


///
/// Test the sec_tp facet (contract).
///
template <typename S0, typename SR>
void
test_sec_contract(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path);


//=============================================================================
// VD FACET
//=============================================================================

///
/// Test the sec_vd facet.
/// The template parameter S represents section type.
///
template <typename S>
void
test_sec_vd_facet(fiber_bundles_namespace& xns,
                  const poset_path& xbase_path);


//==============================================================================
// OUTPUT FACET
//==============================================================================

///
///  Convenience function to create a unique section space name.
///
SHEAF_DLL_SPEC 
void 
create_section_space_name(const string& xbase_name, string& xresult);

///
/// Convenience function to print a section space to standard out.
///
SHEAF_DLL_SPEC 
void 
print_section_space(fiber_bundles_namespace& xns, const string& xname);

///
/// Convenience function to "pretty-print" print a section to standard out.
///
template <typename T>
void print_section(const T& xsection,
                   const string& xindent = "  ",
                   bool xauto_access = true);

///
/// Convenience function to "pretty-print" print the result of an
/// operation to standard out.
///
template <typename T>
void print_result(const string& xtext,
                  const T& xsection,
                  const string& xindent = "  ",
                  bool xauto_access = true);


//==============================================================================
// BASE SPACE FACET
//==============================================================================

///
/// Make a structured_block_1d base space for testing.
///
SHEAF_DLL_SPEC
const poset_path&
make_test_base_space(fiber_bundles_namespace& xns,
                     const size_type& xi_size);

///
/// Make a structured_block_2d base space for testing.
///
SHEAF_DLL_SPEC
const poset_path&
make_test_base_space(fiber_bundles_namespace& xns,
                     const size_type& xi_size,
                     const size_type& xj_size);

///
/// Make a structured_block_3d base space for testing.
///
SHEAF_DLL_SPEC
const poset_path&
make_test_base_space(fiber_bundles_namespace& xns,
                     const size_type& xi_size,
                     const size_type& xj_size,
                     const size_type& xk_size);

//==============================================================================
// SECTION FACET
//==============================================================================

///
/// Convenience function to make sections for testing.
///
template <typename T>
void make_test_sections(fiber_bundles_namespace& xns,
                        const poset_path& xbase_path,
                        const string& xspace_name,
                        const string& xbase_section_name,
                        T xsections[],
                        int xnum_sections);
///
/// Set the dofs of a section for testing.
///
template <typename T>
void set_dofs(T& xresult);

//==============================================================================
// SECTION SPACE FACET
//==============================================================================

///
/// Creates a new section space with xname on base space with xbase_path.
///
template <typename P>
typename P::host_type&
new_host_space(fiber_bundles_namespace& xns,
	       const string& xname,
	       const poset_path& xbase_path);

///
/// Creates a new section space with xname on base space with xbase_path
/// and representation descriptor xrep_path.
///
template <typename P>
typename P::host_type&
new_host_space(fiber_bundles_namespace& xns,
	       const string& xname,
	       const poset_path& xrep_path,
	       const poset_path& xbase_path);


} // namespace fiber_bundle

#endif // ifndef TEST_SECTIONS_H
