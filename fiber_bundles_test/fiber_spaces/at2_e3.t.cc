
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example at2_e3.t.cc
/// Unit test driver for class at2_e3.

#include "at2_e3.h"

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "at2.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"

using namespace fiber_bundle;
using namespace fiber_bundle::atp_algebra;

namespace
{
  void
  test_at2_e3_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<at2_e3_lite>();

    test_volatile_row_dofs<at2_e3_lite>();
 
    test_volatile_class_tp_facet<at2_e3_lite>();

    //==========================================================================

    typedef double value_type;
    typedef at2_e3_row_dofs_type<double> row_dofs_type;
    typedef antisymmetric_matrix_3x3<double> matrix_type;

    //at2_e3_lite(const matrix_type& xmatrix);

    matrix_type lmat;
    lmat[0][1] = 2; lmat[0][2] = 3;
                    lmat[1][2] = 4; 

    cout << "lmat = " << endl;
    cout << lmat << endl;

    at2_e3_lite lfiber(lmat);
    const at2_e3_lite lfiber_const(lmat);

    //at2_e3_lite& operator=(const matrix_type& xmatrix);

    at2_e3_lite lfiber_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const);

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    //at2_e3_lite(const value_type& xy_comp,
    //            const value_type& xz_comp,
    //            const value_type& yz_comp);

    value_type lxy_comp = 123.0;
    value_type lxz_comp = 345.0;
    value_type lyz_comp = 678.0;

    at2_e3_lite lfiber2(lxy_comp, lxz_comp, lyz_comp);

    //virtual void put_components(const value_type& xy_comp,
    //                            const value_type& xz_comp,
    //                            const value_type& yz_comp);

    lfiber.put_components(lxy_comp, lxz_comp, lyz_comp);

    //==========================================================================

    //operator at2_e3_row_dofs_type<T>& () const

    row_dofs_type lrow_dofs2(lmat);

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

    // Hodge star operator functions not exercized elsewhere.

    e3_lite le3_lite(123.0, 345.0, 678.0);
    at2_e3_lite lat2_e3_lite(123.0, 345.0, 678.0);

    //e3_lite* star(const at2_e3_lite& x0);

    e3_lite* lstar_e3 = star(lat2_e3_lite);

    //at2_e3_lite* star(const e3_lite& x0);

    at2_e3_lite* lstar_at2_e3 = star(le3_lite);

    delete lstar_e3;
    delete lstar_at2_e3;

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

} // end unnamed namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  string filename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace lns(filename);
  lns.get_read_write_access();

  // Run tests.

  test_persistent_tensor_type<at2_e3>(lns);

  test_volatile_type<at2_e3>();

  test_tensor_conversions<at2_e3>(lns);

  // Test vd facet:

  test_tensor_vd_facet<at2_e3>(lns);

  // Test tp facet:

  test_tensor<at2_e3, e3, t3_e3>(lns);

  // Test atp facet:

  test_tensor_atp_facet<at2_e3>(lns);

#ifndef _WIN32

  test_hook_product<at2_e3, e3, e3>(lns);

  test_star_operator<at2_e3, e3>(lns);
  test_star_operator<e3, at2_e3>(lns);

  test_wedge_product<e3, e3, at2_e3>(lns);

#endif

  //============================================================================

  // Test class member functions and other not test above.

  test_at2_e3_volatile();

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
