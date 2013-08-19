

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Interface for fiber test function templates.

#ifndef TEST_FIBERS_H
#define TEST_FIBERS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef AT0_H
#include "at0.h"
#endif

#ifndef AT2_E2_H
#include "at2_e2.h"
#endif

#ifndef AT2_E3_H
#include "at2_e3.h"
#endif

#ifndef AT3_E3_H
#include "at3_e3.h"
#endif

#ifndef E1_H
#include "e1.h"
#endif

#ifndef E2_H
#include "e2.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

#ifndef E4_H
#include "e4.h"
#endif

#ifndef GL2_H
#include "gl2.h"
#endif

#ifndef GL3_H
#include "gl3.h"
#endif

#ifndef JCB_E13_H
#include "jcb_e13.h"
#endif

#ifndef JCB_E23_H
#include "jcb_e23.h"
#endif

#ifndef JCB_E33_H
#include "jcb_e33.h"
#endif

#ifndef MET_E1_H
#include "met_e1.h"
#endif

#ifndef MET_E2_H
#include "met_e2.h"
#endif

#ifndef MET_E3_H
#include "met_e3.h"
#endif

#ifndef ST2_E2_H
#include "st2_e2.h"
#endif

#ifndef ST2_E3_H
#include "st2_e3.h"
#endif

#ifndef ST3_E3_H
#include "st3_e3.h"
#endif

#ifndef ST4_E2_H
#include "st4_e2.h"
#endif

#ifndef ST4_E3_H
#include "st4_e3.h"
#endif

#ifndef T2_E2_H
#include "t2_e2.h"
#endif

#ifndef T2_E3_H
#include "t2_e3.h"
#endif

#ifndef T3_E3_H
#include "t3_e3.h"
#endif

#ifndef T4_E2_H
#include "t4_e2.h"
#endif

#ifndef T4_E3_H
#include "t4_e3.h"
#endif

#ifndef TP_SPACE_H
#include "tp_space.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef NAMESPACE_POSET_MEMBER_H
#include "namespace_poset_member.h"
#endif

namespace fiber_bundle
{

class fiber_bundles_namespace;

//=============================================================================
// ATP FACET
//=============================================================================

///
/// Test the hook (interior) product of the atp facet.
///
template <typename P0, typename P1, typename PR>
void test_hook_product(fiber_bundles_namespace& xns);

///
/// Test the hook (interior) product of the atp facet
/// (version for volatile types).
///
template <typename P0, typename P1, typename PR>
void test_volatile_hook_product();

///
/// Test the hook (interior) product of the atp facet
/// (version for persistent types).
///
template <typename P0, typename P1, typename PR>
void test_persistent_hook_product(fiber_bundles_namespace& xns);

///
/// Test the Hodge star operator of the atp facet.
///
template <typename P0, typename PR>
void test_star_operator(fiber_bundles_namespace& xns);

///
/// Test the Hodge star operator of the atp facet
/// (version for volatile types).
///
template <typename P0, typename PR>
void test_volatile_star_operator();

///
/// Test the Hodge star operator of the atp facet
/// (version for persistent types).
///
template <typename P0, typename PR>
void test_persistent_star_operator(fiber_bundles_namespace& xns);

///
/// Test the wedge (exterior) product of the atp facet.
///
template <typename P0, typename P1, typename PR>
void test_wedge_product(fiber_bundles_namespace& xns);

///
/// Test the wedge (exterior) product of the atp facet
/// (version for volatile types).
///
template <typename P0, typename P1, typename PR>
void test_volatile_wedge_product();


///
/// Test the wedge (exterior) product of the atp facet
/// (version for persistent types).
///
template <typename P0, typename P1, typename PR>
void test_persistent_wedge_product(fiber_bundles_namespace& xns);


//=============================================================================
// E3 FACET
//=============================================================================

///
/// Test the e3 facet.
/// Not templated since it only has meaning for e3 types.
///
void SHEAF_DLL_SPEC test_e3_facet(fiber_bundles_namespace& xns);

///
/// Test the e3 facet for volatile types.
/// Not templated since it only has meaning for e3 types.
///
void SHEAF_DLL_SPEC test_volatile_e3_facet();

///
/// Test the e3 facet for persistent types.
/// Not templated since it only has meaning for e3 types.
///
void SHEAF_DLL_SPEC test_persistent_e3_facet(fiber_bundles_namespace& xns);


//=============================================================================
// GROUP FACET
//=============================================================================

///
/// Test the group facet for volatile and persistent types.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_group_facet(fiber_bundles_namespace& xns);

///
/// Test the group facet for a volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_group_facet();

///
/// Test the group facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_group_facet(fiber_bundles_namespace& xns);


//=============================================================================
// ATP FACET
//=============================================================================

///
/// Creates a new host of vector type P and calls test_atp_facet
///
template <typename P>
void test_vector_atp_facet(fiber_bundles_namespace& xns);

///
/// Creates a new host of tensor type P and calls test_atp_facet
///
template <typename P>
void test_tensor_atp_facet(fiber_bundles_namespace& xns);

///
/// Test the atp facet for volatile and persistent types.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_atp_facet(typename P::host_type& xhost);

///
/// Test the tp facet for a volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_atp_facet();

///
/// Test the tp facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_atp_facet(typename P::host_type& xhost);


//=============================================================================
// ED FACET
//=============================================================================

///
/// Test the ed facet.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_ed_facet(fiber_bundles_namespace& xns);

///
/// Test the ed facet for a volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_ed_facet();

///
/// Test the ed facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_ed_facet(typename P::host_type& xhost);


//=============================================================================
// JCB FACET
//=============================================================================

///
/// Test the jcb facet for volatile and persistent types.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_jcb_facet(fiber_bundles_namespace& xns);

///
/// Test the jcb facet for a volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_jcb_facet();

///
/// Test the jcb facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_jcb_facet(fiber_bundles_namespace& xns);


//=============================================================================
// MET FACET
//=============================================================================

///
/// Test the met facet for volatile and persistent types.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_met_facet(fiber_bundles_namespace& xns);

///
/// Test the met facet for a volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_met_facet();

///
/// Test the met facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_met_facet(typename P::host_type& xhost,
			       typename P::vector_space_type::host_type& xvector_space_host);


//=============================================================================
// ST2 FACET
//=============================================================================

///
/// Test the st2 facet.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_st2_facet(fiber_bundles_namespace& xns);

///
/// Test the st2 facet for a volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_st2_facet();

///
/// Test the st2 facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_st2_facet(typename P::host_type& xhost);

//=============================================================================
// STP FACET
//=============================================================================

///
/// Test the atp facet for volatile and persistent types.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_stp_facet(fiber_bundles_namespace& xns);

///
/// Test the tp facet for a volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_stp_facet();

///
/// Test the tp facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_stp_facet(typename P::host_type& xhost);

//=============================================================================
// TP FACET
//=============================================================================

///
/// Test the tp facet for volatile and persistent types.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_tp_facet(fiber_bundles_namespace& xns);

///
/// Test the tp facet for a volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_tp_facet();

///
/// Test the tp facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_tp_facet(fiber_bundles_namespace& xns);

///
/// Test the tp facet tensor product.
///
template <typename P0, typename P1, typename PR>
void test_tensor(fiber_bundles_namespace& xns);

///
/// Test the tp facet tensor product for a volatile type.
///
template <typename P0, typename P1, typename PR>
void test_volatile_tensor();

///
/// Test the tp facet tensor product for a persistent type.
///
template <typename P0, typename P1, typename PR>
void test_persistent_tensor(fiber_bundles_namespace& xns);

///
/// Test the tp facet contract.
///
template <typename P0, typename PR>
void test_contract(fiber_bundles_namespace& xns);

///
/// Test the tp facet contract for a volatile type.
///
template <typename P0, typename PR>
void test_volatile_contract();

///
/// Test the tp facet contract for a persistent type.
///
template <typename P0, typename PR>
void test_persistent_contract(fiber_bundles_namespace& xns);


//=============================================================================
// VD FACET
//=============================================================================

///
/// Creates a new scalar host then calls test_vd_facet to test
/// the vd (algebra) facet.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_scalar_vd_facet(fiber_bundles_namespace& xns);

///
/// Creates a new vector host then calls test_vd_facet to test
/// the vd (algebra) facet.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_vector_vd_facet(fiber_bundles_namespace& xns);

///
/// Creates a new tensor host then calls test_vd_facet to test
/// the vd (algebra) facet.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_tensor_vd_facet(fiber_bundles_namespace& xns);

///
/// Creates a new jacobian host then calls test_vd_facet to test
/// the vd (algebra) facet.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_jacobian_vd_facet(fiber_bundles_namespace& xns);

// ///
// /// Test the vd (algebra) facet.
// /// The template parameter P represents the associated persistent type.
// ///
// template <typename P>
// void test_vd_facet2(fiber_bundles_namespace& xns);

///
/// Test the vd (algebra) facet.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_vd_facet();

///
/// Test the vd (algebra) facet for a persistent type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_persistent_vd_facet(typename P::host_type& xhost);

// ///
// /// Test the vd (algebra) facet for a persistent type.
// /// The template parameter P represents the associated persistent type.
// ///
// template <typename P>
// void test_persistent_vd_facet2(fiber_bundles_namespace& xns);

//=============================================================================
// MISCELLANEOUS TESTS
//=============================================================================

///
/// Creates a new host of scalar type P and calls test_persistent_type.
///
template <typename P>
void test_persistent_scalar_type(fiber_bundles_namespace& xns);

///
/// Creates a new host of vector type P and calls test_persistent_type.
///
template <typename P>
void test_persistent_vector_type(fiber_bundles_namespace& xns);

///
/// Creates a new host of tensor type P and calls test_persistent_type.
///
template <typename P>
void test_persistent_tensor_type(fiber_bundles_namespace& xns);

///
/// Creates a new host of jacobian type P and calls test_persistent_type.
///
template <typename P>
void test_persistent_jacobian_type(fiber_bundles_namespace& xns);

///
/// Creates a new host of group type P and calls test_persistent_type.
///
template <typename P>
void test_persistent_group_type(fiber_bundles_namespace& xns);

///
/// Test persistent type P.
///
template <typename P>
void test_persistent_type(typename P::host_type& xhost);

///
/// Test persistent type P.
///
template <typename P>
void test_persistent_type(fiber_bundles_namespace& xns);

// ///
// /// Test persistent type P.
// ///
// template <typename P>
// void test_persistent_type2(fiber_bundles_namespace& xns);

///
/// Test volatile type.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_volatile_type();

///
/// Creates a new host of scalar type P and calls test_conversions.
///
template <typename P>
void test_scalar_conversions(fiber_bundles_namespace& xns);

///
/// Creates a new host of vector type P and calls test_conversions.
///
template <typename P>
void test_vector_conversions(fiber_bundles_namespace& xns);

///
/// Creates a new host of tensor type P and calls test_conversions.
///
template <typename P>
void test_tensor_conversions(fiber_bundles_namespace& xns);

///
/// Creates a new host of jacobian type P and calls test_conversions.
///
template <typename P>
void test_jacobian_conversions(fiber_bundles_namespace& xns);

///
/// Creates a new host of group type P and calls test_conversions.
///
template <typename P>
void test_group_conversions(fiber_bundles_namespace& xns);

///
/// Test conversions between the various persistent, volatile,
/// matrix and row_dofs types. The template parameter P
/// represents the persistent type.
///
template <typename P>
void test_conversions(typename P::host_type& xhost);

// ///
// /// Test conversions between the various persistent, volatile,
// /// matrix and row_dofs types. The template parameter P
// /// represents the persistent type.
// ///
// template <typename P>
// void test_conversions2(fiber_bundles_namespace& xns);

///
/// Test conversions between persistent and volatile types.
/// The template parameter P represents the persistent type.
///
template <typename P>
void test_virtual_conversions(typename P::host_type& xhost);

// ///
// /// Test conversions between persistent and volatile types.
// /// The template parameter P represents the persistent type.
// ///
// template <typename P>
// void test_virtual_conversions2(fiber_bundles_namespace& xns);

///
/// Test conversions to and from matrix_types.
/// The template parameter P represents the associated persistent type.
///
template <typename P>
void test_matrix_type_conversions();


//==============================================================================
// Convenience functions
//==============================================================================

///
/// Convenience function to create a unique host poset name for
/// vector spaces.
///
string SHEAF_DLL_SPEC create_vector_space_name(const string& xvector_class_name);

///
/// Convenience function to create a unique host poset name for fibers.
///
void SHEAF_DLL_SPEC create_host_name(const string& xbase_name, string& xresult);



///
/// Convenience function to "pretty-print" print the result of an
/// operation to standard out.
///
template <typename T>
void print_result(const string& xtext, const T& xfiber);

///
/// Convenience function to "pretty-print" print the result of an
/// operation to standard out.
///
template <typename T>
void print_result(const string& xtext,
                  const T& xfiber,
                  const string& xindent,
                  bool xauto_access);

//==============================================================================
// FIBER TRAITS (Used ONLY by the test cases.)
//==============================================================================

template <typename T>
class fiber_traits
{
public:

  ///
  /// The type (T)  of the matrix class.
  /// Note that "T" is just a dummy here.
  ///
  typedef T matrix_type;

  ///
  /// True if the class has an associated matrix type.
  ///
  static bool has_matrix_type();
};

//==============================================================================
// Specializations:
//==============================================================================

template<>
class fiber_traits<at0>
{
public:

  typedef at0_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<at2_e2>
{
public:

  typedef at2_e2_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<at2_e3>
{
public:

  typedef at2_e3_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<at3_e3>
{
public:

  typedef at3_e3_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<e1>
{
public:

  typedef e1_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<e2>
{
public:

  typedef e2_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<e3>
{
public:

  typedef e3_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<e4>
{
public:

  typedef e3_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<gl2>
{
public:

  typedef gl2_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<gl3>
{
public:

  typedef gl3_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<jcb_e13>
{
public:

  typedef e1 persistent_vector_type;
  typedef e1_lite volatile_vector_type;

  typedef e3 persistent_covector_type;
  typedef e3_lite volatile_covector_type;

  typedef jcb_e13_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<jcb_e23>
{
public:

  typedef e2 persistent_vector_type;
  typedef e2_lite volatile_vector_type;

  typedef e3 persistent_covector_type;
  typedef e3_lite volatile_covector_type;

  typedef jcb_e23_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<jcb_e33>
{
public:

  typedef e3 persistent_vector_type;
  typedef e3_lite volatile_vector_type;

  typedef e3 persistent_covector_type;
  typedef e3_lite volatile_covector_type;

  typedef jcb_e33_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<met_e1>
{
public:

  typedef met_e1_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<met_e2>
{
public:

  typedef met_e2_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<met_e3>
{
public:

  typedef met_e3_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<st2_e2>
{
public:

  typedef st2_e2_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<st2_e3>
{
public:

  typedef st2_e3_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<st3_e3>
{
public:

  typedef st3_e3_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<st4_e2>
{
public:

  typedef st4_e2_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<st4_e3>
{
public:

  typedef st4_e3_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<t2_e2>
{
public:

  typedef t2_e2_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<t2_e3>
{
public:

  typedef t2_e3_row_dofs_type<double>::matrix_type matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = true;
    return result;
  }
};

template<>
class fiber_traits<t3_e3>
{
public:

  typedef t3_e3_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<t4_e2>
{
public:

  typedef t4_e2_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

template<>
class fiber_traits<t4_e3>
{
public:

  typedef t4_e3_row_dofs_type<double> matrix_type;

  static bool has_matrix_type()
  {
    static const bool result = false;
    return result;
  }
};

//==============================================================================
// Tests for member functions of fiber and fiber space classes.
//==============================================================================

///
/// Test member functions common to all volatile fiber classes.
///
template<typename V>
void
test_volatile_common();

///
/// Test member functions common to all volatile row dofs classes.
///
template<typename V>
void
test_volatile_row_dofs();

///
/// Test member functions of the tp facet of the appropriate
/// volatile  fiber classes.
///
template<typename V>
void
test_volatile_class_tp_facet();

///
/// Test member functions common to all persistent fiber classes.
/// Requires both a base type (PB) and a derived type (PD).
///
template<typename PB, typename PD>
void
test_persistent_common(fiber_bundles_namespace& xns);

///
/// Test member functions common to all persistent fiber classes
//  (slightly different version to the above due to some inconsistences).
/// Requires both a base type (PB) and a derived type (PD).
///
template<typename PB, typename PD>
void
test_persistent_common_2(fiber_bundles_namespace& xns);

///
/// Test member functions common to all fiber space classes.
///
template<typename T>
void
test_spaces_common(fiber_bundles_namespace& lns, T& lspace);

///
/// A class derived from fiber space of type T whose sole
/// purpose is to allow invoking the protected functions
/// of class T; thus allowing better code coverage.
///
template <typename T>
class derived_space : public T
{
public:

  typedef typename T::member_type M;

  derived_space() : T() { }

  derived_space(const T& xother) : T(xother) { }

  derived_space(const namespace_poset& xhost,
                scoped_index xindex, bool xauto_access)
    : T(xhost, xindex, xauto_access)
  {
  }

  derived_space(const namespace_poset& xhost,
                pod_index_type xindex, bool xauto_access)
    : T(xhost, xindex, xauto_access)
  {
  }


  derived_space(const namespace_poset& xhost,
                const string& xname, bool xauto_access)
    : T(xhost, xname, xauto_access)
  {
  }

  derived_space(const namespace_poset_member& xmbr, bool xauto_access)
    : T(xmbr, xauto_access)
  {
  }

  derived_space(M* xtop, M* xbottom)
    : T(xtop, xbottom)
  {
  }

  virtual ~derived_space() {}

  derived_space& operator=(const poset_state_handle& xother)
  {
	 T::operator=(xother);
	 return *this;
  }
};


} // namespace fiber_bundle


#endif // ifndef TEST_FIBERS_H
