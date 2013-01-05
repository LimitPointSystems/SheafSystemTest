
// $RCSfile: test_sheaves.h,v $ $Revision: 1.1.2.10 $ $Date: 2012/11/16 00:14:31 $

//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @file
/// Interface for sheaves test function templates.

#ifndef TEST_SHEAVES_H
#define TEST_SHEAVES_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

#ifndef SCHEMA_DESCRIPTOR_H
#include "schema_descriptor.h"
#endif

#ifndef REFINABLE_POSET_H
#include "refinable_poset.h"
#endif

namespace sheaf
{

//=============================================================================
// ANY FACET
//=============================================================================

///
/// Test the functions of the any class for object xobject.
///
template<typename T>
bool
test_any_facet(const T& xobject);

///
/// Test the functions of the any class.
///
template<typename T>
bool
test_any_facet();


//=============================================================================
// RC_ANY FACET
//=============================================================================

///
/// Test the functions of the rc_any class for object xobject.
///
template<typename T>
bool
test_rc_any_facet(const T& xobject);

///
/// Test the functions of the rc_any class.
///
template<typename T>
bool
test_rc_any_facet();

//=============================================================================
// AUTO_BLOCK FACET
//=============================================================================

template<typename T, typename S>
bool
test_auto_block_facet();

// Test blocks of type auto_block<T == T2*> 

template<typename T, typename T2, typename S>
bool
test_auto_block_facet();

template<typename T, typename S>
bool
test_auto_block_facet_equal();

template<typename T, typename S>
bool
test_auto_block_facet_equal_equal();

template<typename T, typename S>
bool
test_auto_block_facet_insertion();

template<typename T, typename S>
bool
test_auto_block_facet_deep_size();

template<typename T, typename T2, typename S>
bool
test_auto_block_facet_equal();

template<typename T, typename T2, typename S>
bool
test_auto_block_facet_insertion();

template<typename T, typename T2, typename S>
bool
test_auto_block_facet_deep_size();

template<typename T>
bool
test_auto_block_facet_un();

template<typename T>
bool
test_auto_block_facet_invalid();

template<typename T>
bool
test_auto_block_facet_zero();

template<typename T>
bool
test_auto_block_facet_equal_un();

template<typename T>
bool
test_auto_block_facet_equal_invalid();

template<typename T>
bool
test_auto_block_facet_equal_zero();

template<typename T>
bool
test_auto_block_facet_equal_equal_un();

template<typename T>
bool
test_auto_block_facet_equal_equal_invalid();

template<typename T>
bool
test_auto_block_facet_equal_equal_zero();

template<typename T>
bool
test_auto_block_facet_insertion_invalid();

template<typename T>
bool
test_auto_block_facet_insertion_zero();

template<typename T>
bool
test_auto_block_facet_deep_size_un();

template<typename T>
bool
test_auto_block_facet_deep_size_invalid();

template<typename T>
bool
test_auto_block_facet_deep_size_zero();

template<typename T>
bool
test_auto_block_facet_all();

template<typename T>
bool
test_auto_block_facet_equal_all();

template<typename T>
bool
test_auto_block_facet_equal_equal_all();

template<typename T>
bool
test_auto_block_facet_insertion_all();

template<typename T>
bool
test_auto_block_facet_deep_size_all();

template<typename T, typename T2>
bool
test_auto_block_facet_un();

template<typename T, typename T2>
bool
test_auto_block_facet_invalid();

template<typename T, typename T2>
bool
test_auto_block_facet_equal_zero();

template<typename T, typename T2>
bool
test_auto_block_facet_insertion_un();

template<typename T, typename T2>
bool
test_auto_block_facet_insertion_invalid();

template<typename T, typename T2>
bool
test_auto_block_facet_insertion_zero();

template<typename T, typename T2>
bool
test_auto_block_facet_deep_size_un();

template<typename T, typename T2>
bool
test_auto_block_facet_deep_size_invalid();

template<typename T, typename T2>
bool
test_auto_block_facet_deep_size_zero();

template<typename T, typename T2>
bool
test_auto_block_facet_equal_all();

template<typename T, typename T2>
bool
test_auto_block_facet_insertion_all();

template<typename T, typename T2>
bool
test_auto_block_facet_deep_size_all();


//=============================================================================
// BLOCK FACET
//=============================================================================

///
/// Test blocks of type block<T>.
///
template<typename T>
bool
test_block_facet();

///
/// Test blocks of type block<T == T2*> 
///
template<typename T, typename T2>
bool
test_block_facet();

///
/// Specialization for poset_state_handle*.
///
template<>
SHEAF_DLL_SPEC
bool
test_block_facet<poset_state_handle*>();

///
/// Specialization for index_space*.
///
template<>
SHEAF_DLL_SPEC
bool
test_block_facet<index_space*>();

///
/// Test "operator==".
///
template<typename T>
bool
test_block_facet_equal();

///
/// Test "operator<<".
///
template<typename T>
bool
test_block_facet_insertion();

///
/// Test "deep_size".
///
template<typename T>
bool
test_block_facet_deep_size();

//=============================================================================
// WSV_BLOCK FACET
//=============================================================================

///
/// Test blocks of type wsv_block<T>.
///
template<typename T>
bool
test_wsv_block_facet();

///
/// Specialization for wsv_block<bool>.
///
template<>
bool
test_wsv_block_facet<bool>();

///
/// Specialization for wsv_block<schema_descriptor>.
///
template<>
bool
test_wsv_block_facet<schema_descriptor>();

//=============================================================================
// NAME_MULTIMAP FACET
//=============================================================================

///
///
///
template<typename T>
bool
test_name_multimap_facet();


//=============================================================================
// NAME_MAP FACET
//=============================================================================

///
///
///
template<typename T>
bool
test_name_map_facet();

//=============================================================================
// RECORD_MAP FACET
//=============================================================================

///
///
///
template<typename T1, typename T2>
bool
test_record_map_facet();

//=============================================================================
// RAGGED_ARRAY FACET
//=============================================================================

///
///
///
template<typename T>
bool
test_ragged_array_facet();

//=============================================================================
// DEEP_SIZE FACET
//=============================================================================

///
///
///
template<typename T>
bool
test_deep_size(const T& xobject);

//=============================================================================
// ABSTRACT_POSET_MEMBER FACET
//=============================================================================

///
///
///
bool
test_abstract_poset_member_facet();

//============================================================================
// NAMESPACE_POSET FACET
//============================================================================

///
///
///
template<typename T>
bool
test_namespace_poset_facet(namespace_poset& xns,
                           poset_state_handle& xposet);

//============================================================================
// DEPTH_FIRST_ITERATOR FACET
//============================================================================

///
///
///
template <template <typename> class ITR, typename T>
bool
test_depth_first_itr_facet(const refinable_poset& xposet);

//============================================================================
// FILTERED_DEPTH_FIRST_ITERATOR FACET
//============================================================================

///
///
///
template <template <typename> class ITR, typename T>
bool
test_filtered_depth_first_itr_facet(const refinable_poset& xposet);


//============================================================================
// GENERAL FACET
//============================================================================

///
///  Create a refinable_poset in namespace_poset lns with
///  name xname.  The original poset contains a single triangle.
///  Used for testing. 
///
void
make_triangle_poset(namespace_poset& xns, const string& xname);

//============================================================================
//============================================================================

} // namespace sheaf


#endif // ifndef TEST_SHEAVES_H
