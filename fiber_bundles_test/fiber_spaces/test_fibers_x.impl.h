
// $RCSfile: test_fibers_x.impl.h,v $ $Revision: 1.17.36.1 $ $Date: 2012/11/27 20:16:30 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @file
/// Implementation of fiber test function templates.

#ifndef TEST_FIBERS_X_IMPL_H
#define TEST_FIBERS_X_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TEST_FIBERS_X_H
#include "test_fibers_x.h"
#endif


#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef STD_CSTDLIB_H
#include "std_cstdlib.h"
#endif

#ifndef STD_SSTREAM_H
#include "std_sstream.h"
#endif

#ifndef TEST_UTILS_H
#include "test_utils.h"
#endif

namespace fiber_bundle
{
  template<typename V>
  void
  test_volatile_common()
  {
    // Preconditions:

    // Body:

    const string& lfiber_name = V::static_class_name();

    print_header("Begin testing " + lfiber_name + " common");


     // Default constructor.

    print_subheader("Testing " + lfiber_name + "()");

    V lfiber;

    int ld0 = lfiber.d();
    if(ld0 > 0)
    {
      for(int i=0; i<ld0; ++i)
      {
        lfiber.put_component(i, double(100+i));
      }
    }
    
     // Copy constructor.

    print_subheader("Testing " + lfiber_name
                    + "(const "+lfiber_name+"& xother)");

    V lcopy(lfiber);


    // Assignment operator.

    print_subheader("Testing " + lfiber_name
                    + "& = (const "+lfiber_name+"& xother");

    V lassign = lfiber;
   

    print_header("End testing " +lfiber_name+ " common");


    // Destructor.

    print_subheader("Testing ~" +lfiber_name+ "()");

    V* lptr = new V;
    delete lptr;

//     if(xtest_row_dofs)
//     {
//       print_subheader("Testing bool operator==(",
//                       "                  const " +lfiber_name+"& xother) const");

//       bool lequalequal = (lcopy == lfiber);

//       cout << "lequalequal =" << boolalpha << lequalequal << endl;

//       print_subheader("Testing ostream& operator<<(",
//                       "          ostream& xos, const "+lfiber_name+"& x0");

//       cout << "lfiber = \n" << lfiber << endl;
//     }

    //==========================================================================
    // vd facet
    //==========================================================================

    print_subheader("Testing virtual int d() const");

    int ld = lfiber.d();
    cout << "ld = " << ld << endl;

//     if(xtest_row_dofs)
//     {
//       //V(const row_dofs_type& xrow_dofs);

//       typename V::row_dofs_type lrow_dofs;
//       V lfiber_2(lrow_dofs);

//       //V& operator=(const row_dofs_type& xrow_dofs);

//       V lfiber_2_assign = lrow_dofs;

// //     //operator row_dofs_type& ();

// //     typename V::row_dofs_type& lrow_dofs1 = lfiber;

// //     //operator const row_dofs_type& () const;

// //     const V lfiber_const;
// //     const typename V::row_dofs_type& lrow_dofs3 = lfiber_const;

//       //This does basically nothing except call the function in the vd case.

//       typename V::dof_type lresult[4];
//       lfiber.components(lresult, 4);

//       //virtual void put_components(const dof_type xcomps[], int xcomps_dimension);

//       //This does basically nothing except call the function in the vd case.
//       lfiber.put_components(lresult, 4);
//     }

    //==========================================================================


//     //vd_lite& operator=(const value_type& xvalue);

//     typename V::value_type lvalue = 123.0;
//     lfiber = lvalue;

//     //bool operator==(const value_type& xvalue) const;

//     bool leqeq = (lfiber == lvalue);


    //==========================================================================
    // tuple facet
    //==========================================================================

    print_subheader("Testing virtual int factor_ct() const");

    int lfactor_ct = lfiber.factor_ct();
    cout << "lfactor_ct = " << lfactor_ct << endl;


    //==========================================================================
    // abstract_poset_member facet
    //==========================================================================

    print_subheader("Testing virtual const string& class_name() const");

    const string& lclass_name = lfiber.class_name();
    cout << "lclass_name = " << lclass_name << endl;

 
    print_subheader("Testing static const string& static_class_name()");

    const string& lstatic_class_name = V::static_class_name();
    cout << "lstatic_class_name = " << lstatic_class_name << endl;


    print_subheader("Testing virtual " +lfiber_name+ "* clone() const");

    V* lclone = lfiber.clone();
    cout << "lclone = " << lclone << endl;
    delete lclone;

    print_subheader("Testing table_dofs_type table_dofs() const");

    typename V::table_dofs_type ltable_dofs = lfiber.table_dofs();

    //==========================================================================
    // any facet
    //==========================================================================

    print_subheader("Testing virtual bool is_ancestor_of",
                    "                          (const any_lite& xother) const");

    bool lis_ancestor_of = lfiber.is_ancestor_of(lcopy);
    cout << "lis_ancestor_of  = " << boolalpha << lis_ancestor_of  << endl;

 
    print_subheader("Testing bool invariant() const");

    bool linvariant = lfiber.invariant();
    cout << "linvariant = " << boolalpha << linvariant << endl;


    // Postconditions:

    // Exit:

    return;
  }

  template<typename V>
  void
  test_volatile_row_dofs()
  {
    // Preconditions:

    // Body:

    const string& lfiber_name = V::static_class_name();

    V lfiber;

    int ld0 = lfiber.d();
    if(ld0 > 0)
    {
      for(int i=0; i<ld0; ++i)
      {
        lfiber.put_component(i, double(100+i));
      }
    }

    V lcopy(lfiber);

 
    print_subheader("Testing bool operator==(",
                    "                 const " +lfiber_name+"& xother) const");

    bool lequalequal = (lcopy == lfiber);

    cout << "lequalequal =" << boolalpha << lequalequal << endl;

    print_subheader("Testing ostream& operator<<(",
                    "          ostream& xos, const "+lfiber_name+"& x0");

    cout << "lfiber = \n" << lfiber << endl;
 
    //========================================================================

    //V(const row_dofs_type& xrow_dofs);

    typename V::row_dofs_type lrow_dofs;
    V lfiber_2(lrow_dofs);

    //V& operator=(const row_dofs_type& xrow_dofs);

    V lfiber_2_assign = lrow_dofs;

    //     //operator row_dofs_type& ();

    //     typename V::row_dofs_type& lrow_dofs1 = lfiber;

    //     //operator const row_dofs_type& () const;

    //     const V lfiber_const;
    //     const typename V::row_dofs_type& lrow_dofs3 = lfiber_const;

    // Use an array larger than any class d() value here.

    typename V::dof_type lresult[128];
    lfiber.components(lresult, 128);

    //virtual void put_components(const dof_type xcomps[], int xcomps_dimension);

    lfiber.put_components(lresult, 128);

    //==========================================================================

    V* lclone = lfiber.clone(true, true);
    delete lclone;

    //V::row_dofs_type lrow_dofs;
    typename V::row_dofs_type* lclone_row_dofs = lrow_dofs.clone(true, true);
    delete lclone_row_dofs;

    //==========================================================================

    // Postconditions:

    // Exit:

    return;
  }

  template<typename V>
  void
  test_volatile_tp_facet()
  {
    // Preconditions:

    // Body:

    const string& lfiber_name = V::static_class_name();

    print_header("Begin testing " + lfiber_name + " tp facet");

    V lfiber;

    //virtual int p() const;

    int lp = lfiber.p();
    cout << "lp = " << lp << endl;

    //virtual int dd() const;

    int ldd = lfiber.dd();
    cout << "ldd = " << ldd << endl;

    //virtual pod_index_type vector_space_index() const;

    pod_index_type lvector_space_index = lfiber.vector_space_index();
    cout << "lvector_space_index = " << lvector_space_index << endl;

    print_footer("End testing " +lfiber_name+ " tp facet");

    // Postconditions:

    // Exit:

    return;
  }

} // namespace fiber_bundle

#endif // ifndef TEST_FIBERS_X_IMPL_H
