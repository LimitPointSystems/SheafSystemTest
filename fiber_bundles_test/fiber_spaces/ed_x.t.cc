
// $RCSfile: ed_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example ed_x.t.cc
/// Test driver for class ed.

#include "ed.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "test_fibers.impl.h"
//#include "storage_agent.h"
//#include "ed_space.h"

#include "std_iomanip.h"
#include "std_iostream.h"

using namespace fiber_bundle;

namespace
{
  void
  test_ed_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================
    // ed facet
    //==========================================================================

    //ed_lite();

    ed_lite led;

    //ed_lite(const ed_lite& xother);

    ed_lite lcopy(led);

    //ed_lite& operator=(const ed_lite& xother);

    ed_lite lassign = led;

    //bool operator==(const ed_lite& xother) const;

//     bool lequalequal = (lcopy == led);

//     cout << "lequalequal =" << boolalpha << lequalequal << endl;

    //virtual ~ed_lite();

    ed_lite* lptr = new ed_lite;
    delete lptr;

//     // ostream& operator<<(ostream& xos, const ed_lite& x0);

//     cout << "led = \n" << led << endl;


    //virtual int p() const;

    int lp = led.p();
    cout << "lp = " << lp << endl;

    //virtual int dd() const;

    int ldd = led.dd();
    cout << "ldd = " << ldd << endl;

    //virtual pod_index_type vector_space_index() const;

    pod_index_type lvector_space_index = led.vector_space_index();
    cout << "lvector_space_index = " << lvector_space_index << endl;


    //==========================================================================

    //$$SCRIBBLE: Can't invoke these because any_lite::row_dofs() is abstract.

    //ed_lite(const row_dofs_type& xrow_dofs);

    //ed_lite::row_dofs_type lrow_dofs;
    //ed_lite led2(lrow_dofs);

    //ed_lite& operator=(const row_dofs_type& xrow_dofs);
    //ed_lite led2_assign = lrow_dofs;

    //==========================================================================
    // at1 facet
    //==========================================================================

    //==========================================================================
    // atp facet
    //==========================================================================

    //==========================================================================
    // tp facet
    //==========================================================================

    //==========================================================================
    // vd facet
    //==========================================================================

    //virtual int d() const;

    int ld = led.d();
    cout << "ld = " << ld << endl;


    //==========================================================================
    // tuple facet
    //==========================================================================

    //virtual int factor_ct() const;

    int lfactor_ct = led.factor_ct();
    cout << "lfactor_ct = " << lfactor_ct << endl;

    //==========================================================================
    // abstract_poset_member facet
    //==========================================================================

    //virtual const string& class_name() const;

    const string& lclass_name = led.class_name();
    cout << "lclass_name = " << lclass_name << endl;

    //static const string& static_class_name();

    const string& lstatic_class_name = vd::static_class_name();
    cout << "lstatic_class_name = " << lstatic_class_name << endl;

    //virtual ed_lite* clone() const;

    ed_lite* lclone = led.clone();
    cout << "lclone = " << lclone << endl;
    delete lclone;

    //table_dofs_type table_dofs() const;
    ed_lite::table_dofs_type ltable_dofs = led.table_dofs();

    //==========================================================================
    // any facet
    //==========================================================================

    //virtual bool is_ancestor_of(const any_lite& xother) const;

    bool lis_ancestor_of = led.is_ancestor_of(lcopy);
    cout << "lis_ancestor_of  =" << boolalpha << lis_ancestor_of  << endl;

    //bool invariant() const;

    bool linvariant = led.invariant();
    cout << "linvariant =" << boolalpha << linvariant << endl;

//     //==========================================================================
//     // vector algebra: tolerance comparison
//     //
//     // $$SCRIBBLE: Test these here because they don't appear to be tested
//     //              elsewhere
//     // $$TODO: Move to the correct location.
//     //==========================================================================

//     ed_lite lvd0;
//     ed_lite lvd1;
//     ed_lite lvd_tolerance;
//     double ltolerance = 0.00001;

//     cout << boolalpha;

//     //bool a_eql(const ed_lite& x0, const ed_lite& x1);

//     bool la_eql = a_eql(lvd0, lvd1);
//     cout << "la_eql = " << la_eql << endl;
  
//     //bool a_eql(const ed_lite& x0, const ed_lite& x1, double xtolerance);

//     bool la_eql_tol0 = a_eql(lvd0, lvd1, ltolerance);
//     cout << "la_eql_tol0 = " << la_eql_tol0 << endl;

//     //bool a_eql(const ed_lite& x0, const ed_lite& x1, const ed_lite& xtolerance);

//     bool la_eql_tol1 = a_eql(lvd0, lvd1, lvd_tolerance);
//     cout << "la_eql_tol1 = " << la_eql_tol1 << endl;

//     //bool r_eql(const ed_lite& x0, const ed_lite& x1);

//     bool lr_eql = r_eql(lvd0, lvd1);
//     cout << "lr_eql = " << lr_eql << endl;
  
//     //bool r_eql(const ed_lite& x0, const ed_lite& x1, double xtolerance);

//     bool lr_eql_tol0 = r_eql(lvd0, lvd1, ltolerance);
//     cout << "lr_eql_tol0 = " << lr_eql_tol0 << endl;

//     //bool r_eql(const ed_lite& x0, const ed_lite& x1, const ed_lite& xtolerance);

//     bool lr_eql_tol1 = r_eql(lvd0, lvd1, lvd_tolerance);
//     cout << "lr_eql_tol1 = " << lr_eql_tol1 << endl;


//     //bool c_eql(const ed_lite& x0, const ed_lite& x1);

//     bool lc_eql = c_eql(lvd0, lvd1);
//     cout << "lc_eql = " << lc_eql << endl;
  
//     //bool c_eql(const ed_lite& x0, const ed_lite& x1, double xtolerance);

//     bool lc_eql_tol0 = c_eql(lvd0, lvd1, ltolerance);
//     cout << "lc_eql_tol0 = " << lc_eql_tol0 << endl;

//     //bool c_eql(const ed_lite& x0, const ed_lite& x1, const ed_lite& xtolerance);

//     bool lc_eql_tol1 = c_eql(lvd0, lvd1, lvd_tolerance);
//     cout << "lc_eql_tol1 = " << lc_eql_tol1 << endl;

//     //==========================================================================

//     //$$SCRIBBLE: There are other vector operations which are not tested for
//     //            ed_lite.  They should probably be tested in the tempplated
//     //            tests in test_fibers.

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

  test_ed_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
