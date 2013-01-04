
// $RCSfile: t2_e3_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example t2_e3_x.t.cc
/// Test driver for class t2_e3.

#include "t2_e3.h"

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
  test_t2_e3_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<t2_e3_lite>();

    test_volatile_row_dofs<t2_e3_lite>();

    test_volatile_tp_facet<t2_e3_lite>();

    //==========================================================================

    typedef double value_type;
    typedef t2_e3_row_dofs_type<double> row_dofs_type;
    typedef general_matrix_3x3<double> matrix_type;

    //t2_e3_lite(const matrix_type& xmatrix);

    matrix_type lmat;
    lmat[0][0] =  10; lmat[0][1] = -10; lmat[0][2] =   0;
    lmat[1][0] = -10; lmat[1][1] =  20; lmat[1][2] = -10;
    lmat[2][0] =   0; lmat[2][1] =   0; lmat[2][2] =  10;

    cout << "lmat = " << endl;
    cout << lmat << endl;

    t2_e3_lite lfiber(lmat);
    const t2_e3_lite lfiber_const(lmat);

    //t2_e3_lite& operator=(const matrix_type& xmatrix);

    t2_e3_lite lfiber_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const);

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    //t2_e3_lite(const value_type& xx_comp,
    //           const value_type& xy_comp,
    //           const value_type& xz_comp,
    //           const value_type& yx_comp,
    //           const value_type& yy_comp,
    //           const value_type& yz_comp,
    //           const value_type& zx_comp,
    //           const value_type& zy_comp,
    //           const value_type& zz_comp);

    const value_type lxx_comp = 11.0;
    const value_type lxy_comp = 12.0;
    const value_type lxz_comp = 13.0;
    const value_type lyx_comp = 21.0;
    const value_type lyy_comp = 22.0;
    const value_type lyz_comp = 23.0;
    const value_type lzx_comp = 31.0;
    const value_type lzy_comp = 32.0;
    const value_type lzz_comp = 33.0;

    t2_e3_lite lfiber2(lxx_comp, lxy_comp, lxz_comp,
                       lyx_comp, lyy_comp, lyz_comp,
                       lzx_comp, lzy_comp, lzz_comp);

    //virtual void put_components(const value_type& xx_comp,
    //                            const value_type& xy_comp,
    //                            const value_type& xz_comp,
    //                            const value_type& yx_comp,
    //                            const value_type& yy_comp,
    //                            const value_type& yz_comp,
    //                            const value_type& zx_comp,
    //                            const value_type& zy_comp,
    //                            const value_type& zz_comp);

   lfiber.put_components(lxx_comp, lxy_comp, lxz_comp,
                         lyx_comp, lyy_comp, lyz_comp,
                         lzx_comp, lzy_comp, lzz_comp);


    //==========================================================================

    // Other constructors and assignment operators:

    //t2_e3_lite(const at2_e3_lite& xother);

    at2_e3_lite lfiber_at2_e3;
    t2_e3_lite lfiber3(lfiber_at2_e3);

    //t2_e3_lite& operator=(const at2_e3_lite& xother);

    t2_e3_lite lfiber3_assign = lfiber_at2_e3;

    //t2_e3_lite(const st2_e3_lite& xother);

    st2_e3_lite lfiber_st2_e3;
     t2_e3_lite lfiber4(lfiber_st2_e3);

    //t2_e3_lite& operator=(const st2_e3_lite& xother);

    t2_e3_lite lfiber4_assign = lfiber_st2_e3;

    //==========================================================================

    //operator t02_e3_row_dofs_type<T>& () const

    t02_e3_row_dofs_type<double>& lrow_dofs3(lmat);

   //==========================================================================

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_prototype0 = lfiber.tp_prototype(0);
    const tp_lite& ltp_prototype1 = lfiber.tp_prototype(1);
    const tp_lite& ltp_prototype2 = lfiber.tp_prototype(2);
    const tp_lite& ltp_prototype3 = lfiber.tp_prototype(3);
    const tp_lite& ltp_prototype4 = lfiber.tp_prototype(4);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_prototype0 = lfiber.atp_prototype(0);
    const atp_lite& latp_prototype1 = lfiber.atp_prototype(1);
    const atp_lite& latp_prototype2 = lfiber.atp_prototype(2);
    const atp_lite& latp_prototype3 = lfiber.atp_prototype(3);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_prototype2 = lfiber.stp_prototype(2);
    const stp_lite& lstp_prototype3 = lfiber.stp_prototype(3);
    const stp_lite& lstp_prototype4 = lfiber.stp_prototype(4);

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

  test_t2_e3_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}