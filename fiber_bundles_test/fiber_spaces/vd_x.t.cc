
// $RCSfile: vd_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example vd_x.t.cc
/// Test driver for class vd.

#include "vd.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers_x.impl.h"
//#include "storage_agent.h"


using namespace fiber_bundle;

namespace
{
//   template<typename F>
//   void
//   test_volatile_common()
//   {
//     // Preconditions:

//     // Body:

//     const string& lfiber_name = F::static_class_name();

//     print_header("Begin testing " + lfiber_name + " common");


//      // Default constructor.

//     print_subheader("Testing " + lfiber_name + "()");

//     F lfiber;


//      // Copy constructor.

//     print_subheader("Testing " + lfiber_name
//                     + "(const "+lfiber_name+"& xother)");

//     F lcopy(lfiber);


//     // Assignment operator.

//     print_subheader("Testing " + lfiber_name
//                     + "& = (const "+lfiber_name+"& xother");

//     F lassign = lfiber;
   

//     // Destructor.

//     print_subheader("Testing ~" + lfiber_name  + "()");

//     F* lptr = new F;
//     delete lptr;

//     print_subheader("Testing bool operator==(",
//                      "                  const " +lfiber_name+"& xother) const");

//     bool lequalequal = (lcopy == lfiber);

//     cout << "lequalequal =" << boolalpha << lequalequal << endl;

//     print_subheader("Testing ostream& operator<<(",
//                     "          ostream& xos, const "+lfiber_name+"& x0");

//     cout << "lfiber = \n" << lfiber << endl;

//     //==========================================================================
//     // vd facet
//     //==========================================================================

//     print_subheader("Testing virtual int d() const");

//     int ld = lfiber.d();
//     cout << "ld = " << ld << endl;

//     //F(const row_dofs_type& xrow_dofs);

//     const typename F::row_dofs_type lrow_dofs;
//     F lfiber_2(lrow_dofs);

//     //F& operator=(const row_dofs_type& xrow_dofs);

//     F lfiber_2_assign = lrow_dofs;

// //     //operator row_dofs_type& ();

// //     typename F::row_dofs_type& lrow_dofs1 = lfiber;

// //     //operator const row_dofs_type& () const;

// //      const F lfiber_const;
// //      const typename F::row_dofs_type& lrow_dofs3 = lfiber_const;

//     //This does basically nothing except call the function in the vd case.

//     typename F::dof_type lresult[4];
//     lfiber.components(lresult, 4);

//     //virtual void put_components(const dof_type xcomps[], int xcomps_dimension);

//     //This does basically nothing except call the function in the vd case.
//     lfiber.put_components(lresult, 4);

// //     //vd_lite& operator=(const value_type& xvalue);

// //     typename F::value_type lvalue = 123.0;
// //     lfiber = lvalue;

// //     //bool operator==(const value_type& xvalue) const;

// //     bool leqeq = (lfiber == lvalue);

//    //==========================================================================
//     // tuple facet
//     //==========================================================================

//     print_subheader("Testing virtual int factor_ct() const");

//     int lfactor_ct = lfiber.factor_ct();
//     cout << "lfactor_ct = " << lfactor_ct << endl;

//     //==========================================================================
//     // abstract_poset_member facet
//     //==========================================================================

//     print_subheader("Testing virtual const string& class_name() const");

//     const string& lclass_name = lfiber.class_name();
//     cout << "lclass_name = " << lclass_name << endl;

 
//     print_subheader("Testing static const string& static_class_name()");

//     const string& lstatic_class_name = F::static_class_name();
//     cout << "lstatic_class_name = " << lstatic_class_name << endl;


//     print_subheader("Testing virtual " +lfiber_name+ "* clone() const");

//     F* lclone = lfiber.clone();
//     cout << "lclone = " << lclone << endl;
//     delete lclone;


//     print_subheader("Testing table_dofs_type table_dofs() const");

//     typename F::table_dofs_type ltable_dofs = lfiber.table_dofs();


//     //==========================================================================
//     // any facet
//     //==========================================================================

//     print_subheader("Testing virtual bool is_ancestor_of",
//                     "                          (const any_lite& xother) const");

//     bool lis_ancestor_of = lfiber.is_ancestor_of(lcopy);
//     cout << "lis_ancestor_of  = " << boolalpha << lis_ancestor_of  << endl;

 
//     print_subheader("Testing bool invariant() const");

//     bool linvariant = lfiber.invariant();
//     cout << "linvariant = " << boolalpha << linvariant << endl;


//     print_footer("End testing " + lfiber_name + " common");

//     // Postconditions:

//     // Exit:

//     return;
//   }

  void
  test_volatile_tolerance_comparison()
  {
    // Preconditions:

    // Body:

    //==========================================================================
    // vector algebra: tolerance comparison
    //==========================================================================

    print_header("Begin testing vector algebra: tolerance comparison");

    vd_lite lvd0;
    vd_lite lvd1;
    vd_lite lvd_tolerance;
    double ltolerance = 0.00001;

    cout << boolalpha;

    //bool a_eql(const vd_lite& x0, const vd_lite& x1);

    bool la_eql = a_eql(lvd0, lvd1);
    cout << "la_eql = " << la_eql << endl;
  
    //bool a_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);

    bool la_eql_tol0 = a_eql(lvd0, lvd1, ltolerance);
    cout << "la_eql_tol0 = " << la_eql_tol0 << endl;

    //bool a_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);

    bool la_eql_tol1 = a_eql(lvd0, lvd1, lvd_tolerance);
    cout << "la_eql_tol1 = " << la_eql_tol1 << endl;

    //bool r_eql(const vd_lite& x0, const vd_lite& x1);

    bool lr_eql = r_eql(lvd0, lvd1);
    cout << "lr_eql = " << lr_eql << endl;
  
    //bool r_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);

    bool lr_eql_tol0 = r_eql(lvd0, lvd1, ltolerance);
    cout << "lr_eql_tol0 = " << lr_eql_tol0 << endl;

    //bool r_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);

    bool lr_eql_tol1 = r_eql(lvd0, lvd1, lvd_tolerance);
    cout << "lr_eql_tol1 = " << lr_eql_tol1 << endl;


    //bool c_eql(const vd_lite& x0, const vd_lite& x1);

    bool lc_eql = c_eql(lvd0, lvd1);
    cout << "lc_eql = " << lc_eql << endl;
  
    //bool c_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);

    bool lc_eql_tol0 = c_eql(lvd0, lvd1, ltolerance);
    cout << "lc_eql_tol0 = " << lc_eql_tol0 << endl;

    //bool c_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);

    bool lc_eql_tol1 = c_eql(lvd0, lvd1, lvd_tolerance);
    cout << "lc_eql_tol1 = " << lc_eql_tol1 << endl;

    print_footer("End testing vector algebra: tolerance comparison");

    // Postconditions:

    // Exit:

    return;
  }

  void
  test_vd_volatile()
  {
    // Preconditions:

    // Body:

    test_volatile_common<vd_lite>();

    test_volatile_tolerance_comparison();

    //==========================================================================
    // vd facet
    //==========================================================================

    vd_lite lvd;

    //vd_lite& operator=(const value_type& xvalue);

    vd_lite::value_type lvalue = 123.0;
    lvd = lvalue;

    //bool operator==(const value_type& xvalue) const;

    bool leqeq = (lvd == lvalue);

    //virtual value_type& operator[] (int xindex);

    //virtual const value_type& operator[] (int xindex) const;

    //==========================================================================

    //static const tp_lite& static_tp_prototype(int xp);

    const tp_lite& lstatic_tp_prototype = vd_lite::static_tp_prototype(2);

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype = lvd.tp_prototype(2);

    //static const atp_lite& static_atp_prototype(int xp);

    const atp_lite& lstatic_atp_prototype = vd_lite::static_atp_prototype(2);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype = lvd.atp_prototype(2);

    //static const stp_lite& static_stp_prototype(int xp);

    const stp_lite& lstatic_stp_prototype = vd_lite::static_stp_prototype(2);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype = lvd.stp_prototype(2);

    //==========================================================================

    //$$SCRIBBLE: There are other vector operations which are not tested for
    //            vd_lite.  They should probably be tested in the tempplated
    //            tests in test_fibers.

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

} // end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  //string filename = filename_from_cmdline(*xargv);

  // Create the namespace.

  //fiber_bundles_namespace lns(filename);
  //lns.get_read_write_access();

  // Run tests.

  test_vd_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
