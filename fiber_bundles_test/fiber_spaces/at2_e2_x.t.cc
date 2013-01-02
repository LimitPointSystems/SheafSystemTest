
// $RCSfile: at2_e2_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example at2_e2_x.t.cc
/// Test driver for class at2_e2.

#include "at2_e2.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers_x.impl.h"
//#include "storage_agent.h"


using namespace fiber_bundle;

namespace
{
  void
  test_at2_e2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<at2_e2_lite>();

    test_volatile_row_dofs<at2_e2_lite>();

    test_volatile_tp_facet<at2_e2_lite>();

    //==========================================================================

    typedef double value_type;
    typedef at2_e2_row_dofs_type<double> row_dofs_type;
    typedef antisymmetric_matrix_2x2<double> matrix_type;

    //at2_e2_lite(const matrix_type& xmatrix);

    matrix_type lmat;
    lmat[0][1] = -2; 

    cout << "lmat = " << endl;
    cout << lmat << endl;

    at2_e2_lite lfiber(lmat);
    const at2_e2_lite lfiber_const(lmat);

    //at2_e2_lite& operator=(const matrix_type& xmatrix);

    at2_e2_lite lfiber_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const);

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //at2_e2_lite(const value_type& xy);

    value_type lvalue = 123.456;
    at2_e2_lite lfiber2(lvalue);

    //virtual void put_component(value_type xy);

    lfiber.put_component(lvalue);

    //==========================================================================

    //operator at2_e2_row_dofs_type<T>& () const

    row_dofs_type lrow_dofs2(lmat);

    //==========================================================================

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);
    const tp_lite& ltp_prototype1 = lfiber.tp_prototype(1);
    const tp_lite& ltp_prototype2 = lfiber.tp_prototype(2);
    const tp_lite& ltp_prototype4 = lfiber.tp_prototype(4);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);
    const atp_lite& latp_prototype1 = lfiber.atp_prototype(1);
    const atp_lite& latp_prototype2 = lfiber.atp_prototype(2);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype2 = lfiber.stp_prototype(2);
    const stp_lite& lstp_prototype4 = lfiber.stp_prototype(4);

    //==========================================================================

    // Hodge star operator functions not exercized elsewhere.

    at2_e2_lite lat2_e2_lite(123.0);
    at0_lite lat0_lite(345.0);
    e2_lite le2_lite(123.0, 345.0);


    //at2_e2_lite* star(const at0_lite& x0);

    at2_e2_lite* lstar_at2_e2 = star(lat0_lite);

    //at0_lite* star(const at2_e2_lite& x0);

    at0_lite* lstar_at0 = star(lat2_e2_lite);

    //e2_lite* star(const e2_lite& x0);

    e2_lite* lstar_e2 = star(le2_lite);

    delete lstar_at2_e2;
    delete lstar_at0;
    delete lstar_e2;
     
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

  test_at2_e2_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
