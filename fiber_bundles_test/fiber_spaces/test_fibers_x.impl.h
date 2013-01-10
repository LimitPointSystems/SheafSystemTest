
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

    //==========================================================================
    // vd facet
    //==========================================================================

    print_subheader("Testing virtual int d() const");

    int ld = lfiber.d();
    cout << "ld = " << ld << endl;


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

  template<typename PB, typename PD>
  void
  test_persistent_common(fiber_bundles_namespace& xns)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());

    // Body:

    const string& lfiber_name = PB::static_class_name();

    print_header("Begin testing " + lfiber_name);

    //==========================================================================

    typename PD::host_type& lhost = xns.new_fiber_space<PD>();
    lhost.get_read_write_access(true);
  
    //test_persistent_type<PB>(lhost);

    PB* lfiber = new PB(&lhost);

    typename PB::host_type* lhost2 = lfiber->host();
    cout << "lhost2 = " << lhost2 << endl;

    const string lmember_name("test_fiber");
    lfiber->put_name(lmember_name, true, false);

    const string& lclass_name = lfiber->class_name();
    cout << "lclass_name = " << lclass_name << endl;


    int lfactor_ct = lfiber->factor_ct();
    cout << "lfactor_ct = " << lfactor_ct << endl;

    //$$SCRIBBLE: Inconsistency amoung classes here???
    //PB* lfiber2 = new PB(*lfiber);
    PB* lfiber2 = new PB(lfiber);

    PB lfiber3 = *lfiber;

    const scoped_index lindex = lfiber->index();

    const poset* lposet = dynamic_cast<poset*>(&lhost);
    PB* lfiber4 = new PB(lposet, lmember_name);
    PB* lfiber5 = new PB(lposet, lindex);

    PB* lfiber6 = lfiber5->clone();

    //==========================================================================

    PB lfiber7;
    lfiber7 = *lfiber6;

    //e1 lother;
    //lfiber7 = lother;

    //==========================================================================

    // virtual const volatile_type& lite_prototype() const

    typename PB::volatile_type lvolatile = lfiber->lite_prototype();

    //virtual volatile_type* lite_type() const;

    typename PB::volatile_type* lvolatile_ptr = lfiber->lite_type();

    //==========================================================================

    lfiber->detach_from_state();
    lfiber2->detach_from_state();
    lfiber3.detach_from_state();
    lfiber4->detach_from_state();
    lfiber5->detach_from_state();
    lfiber6->detach_from_state();

    lfiber7.detach_from_state();

    delete lfiber;
    delete lfiber2;
    delete lfiber4;
    delete lfiber5;
    delete lfiber6;

    lhost.release_access();

    //==========================================================================

    print_footer("End testing " + lfiber_name);

    // Postconditions:

    // Exit:

    return;

  }

  template<typename PB, typename PD>
  void
  test_persistent_common_2(fiber_bundles_namespace& xns)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());

    // Body:

    const string& lfiber_name = PB::static_class_name();

    print_header("Begin testing " + lfiber_name);

    //==========================================================================

    typename PD::host_type& lhost = xns.new_fiber_space<PD>();
    lhost.get_read_write_access(true);
  
    //test_persistent_type<PB>(lhost);

    PB* lfiber = new PB(&lhost);

    typename PB::host_type* lhost2 = lfiber->host();
    cout << "lhost2 = " << lhost2 << endl;

    const string lmember_name("test_fiber");
    lfiber->put_name(lmember_name, true, false);

    const string& lclass_name = lfiber->class_name();
    cout << "lclass_name = " << lclass_name << endl;


    int lfactor_ct = lfiber->factor_ct();
    cout << "lfactor_ct = " << lfactor_ct << endl;

    //$$SCRIBBLE: Inconsistency amoung classes here???
    PB* lfiber2 = new PB(*lfiber);
    //PB* lfiber2 = new PB(lfiber);

    PB lfiber3 = *lfiber;

    const scoped_index lindex = lfiber->index();

    const poset* lposet = dynamic_cast<poset*>(&lhost);
    PB* lfiber4 = new PB(lposet, lmember_name);
    PB* lfiber5 = new PB(lposet, lindex);

    PB* lfiber6 = lfiber5->clone();

    //==========================================================================

    PB lfiber7;
    lfiber7 = *lfiber6;

    //e1 lother;
    //lfiber7 = lother;

    //==========================================================================

    // virtual const volatile_type& lite_prototype() const

    typename PB::volatile_type lvolatile = lfiber->lite_prototype();

    //virtual volatile_type* lite_type() const;

    typename PB::volatile_type* lvolatile_ptr = lfiber->lite_type();

    //==========================================================================

    lfiber->detach_from_state();
    lfiber2->detach_from_state();
    lfiber3.detach_from_state();
    lfiber4->detach_from_state();
    lfiber5->detach_from_state();
    lfiber6->detach_from_state();

    lfiber7.detach_from_state();

    delete lfiber;
    delete lfiber2;
    delete lfiber4;
    delete lfiber5;
    delete lfiber6;

    lhost.release_access();

    //==========================================================================

    print_footer("End testing " + lfiber_name);

    // Postconditions:

    // Exit:

    return;

  }


} // namespace fiber_bundle

#endif // ifndef TEST_FIBERS_X_IMPL_H
