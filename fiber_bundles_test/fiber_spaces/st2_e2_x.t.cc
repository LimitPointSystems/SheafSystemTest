
// $RCSfile: st2_e2_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example st2_e2_x.t.cc
/// Test driver for class st2_e2.

#include "st2_e2.h"

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
  test_st2_e2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<st2_e2_lite>();

    test_volatile_row_dofs<st2_e2_lite>();

    test_volatile_tp_facet<st2_e2_lite>();

    //==========================================================================

    typedef double value_type;
    typedef st2_e2_row_dofs_type<double> row_dofs_type;
    typedef symmetric_matrix_2x2<double> matrix_type;

    //st2_e2_lite(const matrix_type& xmatrix);

    matrix_type lmat;
    lmat[0][0] =  4;  lmat[0][1] = -2; 
                      lmat[1][1] =  3; 
 

    cout << "lmat = " << endl;
    cout << lmat << endl;

    st2_e2_lite lfiber(lmat);
    const st2_e2_lite lfiber_const(lmat);

    //st2_e2_lite& operator=(const matrix_type& xmatrix);

    st2_e2_lite lfiber_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const);

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);


    //==========================================================================

    //st2_e2_lite(const value_type& xx_comp,
    //            const value_type& xy_comp,
    //            const value_type& yy_comp);

    value_type lxx_comp = 123.0;
    value_type lxy_comp = 345.0;
    value_type lyy_comp = 678.0;

    st2_e2_lite lfiber2(lxx_comp, lxy_comp, lyy_comp);

    //virtual void put_components(const value_type& xx_comp,
    //                            const value_type& xy_comp,
    //                            const value_type& yy_comp);

    lfiber.put_components(lxx_comp, lxy_comp, lyy_comp);

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

    gl2_lite ltransform;
    st2_e2_lite lresult;

    st2_e2_lite llite(123.0, 345.0, 456.0);
    st2_e2_lite lpd_lite(1.0, 0.0, 1.0);

    //template <> void to_principal_axes(
    //  const st2_e2_lite& xlite, gl2_lite& xtransform, st2_e2_lite& xresult);

    to_principal_axes(llite, ltransform, lresult);

    //template <> void to_principal_axes(
    //  const st2_e2_lite& xlite, const st2_e2_lite& xpd_lite,
    //  gl2_lite& xtransform, st2_e2_lite& xresult);

    to_principal_axes(llite, lpd_lite, ltransform, lresult);

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

  test_st2_e2_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
