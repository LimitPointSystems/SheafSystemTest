

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example met_e2_x.t.cc
/// Test driver for class met_e2.

#include "met_e2.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_fibers.impl.h"
//#include "storage_agent.h"


using namespace fiber_bundle;

namespace
{
  void
  test_met_e2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<met_e2_lite>();

    test_volatile_class_tp_facet<met_e2_lite>();

    //==========================================================================

    met_e2_lite lfiber(11.0, 12.0, 22.0);
    lfiber.put_components(111.0, 112.0, 122.0);

    //met_e2_lite::value_type lvalue = lfiber.component();

    met_e2_lite::row_dofs_type& lrow_dofs(lfiber);

    const met_e2_lite lfiber_const;

    const met_e2_lite::row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    typedef double value_type;
    typedef met_e2_row_dofs_type<double> row_dofs_type;
    typedef symmetric_matrix_2x2<double> matrix_type;

    //met_e2_lite(const matrix_type& xmatrix);

    matrix_type lmat;
    lmat[0][0] =  4;  lmat[0][1] = -2; 
                      lmat[1][1] =  3; 

    cout << "lmat = " << endl;
    cout << lmat << endl;

    met_e2_lite lfiber2(lmat);
    const met_e2_lite lfiber_const2(lmat);

    //met_e2_lite& operator=(const matrix_type& xmatrix);

    met_e2_lite lfiber_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber2);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const2);

    //==========================================================================

    //met_e2_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const

    row_dofs_type* lclone_row_dofs = lrow_dofs.clone(true, true);

    //virtual met_e2_lite* clone(bool xnew_state, bool xauto_access) const

    met_e2_lite* lclone = lfiber.clone(true, true);

    delete lclone_row_dofs; 
    delete lclone; 

    //==========================================================================

    //operator met_e2_row_dofs_type<T>& () const

    met_e2_row_dofs_type<double> lrow_dofs2(lmat);

    //==========================================================================

    //virtual const tp_lite& tp_prototype(int xp) const;

    const tp_lite& ltp_lite = lfiber.tp_prototype(2);

    //virtual const atp_lite& atp_prototype(int xp) const;

    const atp_lite& latp_lite = lfiber.atp_prototype(2);

    //virtual const stp_lite& stp_prototype(int xp) const;

    const stp_lite& lstp_lite = lfiber.stp_prototype(2);

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

  test_met_e2_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
