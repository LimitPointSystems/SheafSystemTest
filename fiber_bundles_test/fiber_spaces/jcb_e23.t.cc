
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example jcb_e23.t.cc
/// Unit test driver for class jcb_e23.

#include "jcb_e23.h"

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e2.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "jcb_space.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"

using namespace fiber_bundle;
using namespace fiber_bundle::jcb_algebra;

namespace
{
  void
  test_jcb_e23_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<jcb_e23_lite>();

    //test_volatile_jcb_facet<jcb_e23_lite>();

    //==========================================================================

    typedef double value_type;
    typedef jcb_e23_row_dofs_type<double> row_dofs_type;
    typedef general_matrix_3x2<double> matrix_type;

    jcb_e23_lite lfiber(0.11, 0.12, 0.21, 0.22, 0.31, 0.32);
    lfiber.put_components(0.111, 0.112, 0.121, 0.122, 0.131, 0.132);

    row_dofs_type& lrow_dofs(lfiber);

    const jcb_e23_lite lfiber_const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    matrix_type lmat;
    lmat[0][0] =  1; lmat[0][1] = 2;
    lmat[1][0] =  3; lmat[1][1] = 4;
    lmat[2][0] =  5; lmat[2][1] = 6;

    cout << "lmat = " << endl;
    cout << lmat << endl;

    //jcb_e23_lite(const matrix_type& xmatrix);

    jcb_e23_lite lfiber2(lmat);
    const jcb_e23_lite lfiber2_const(lmat);

    //jcb_e23_lite& operator=(const matrix_type& xmatrix);

    jcb_e23_lite lfiber2_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmatrix_type(lfiber2);

    //operator const matrix_type& () const;

    const matrix_type& lmatrix_type_const(lfiber_const);

    //==========================================================================

    //jcb_e23_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const

    row_dofs_type* lclone_row_dofs = lrow_dofs.clone(true, true);

    //virtual jcb_e23_lite* clone(bool xnew_state, bool xauto_access) const

    jcb_e23_lite* lclone = lfiber.clone(true, true);

    delete lclone_row_dofs; 
    delete lclone;

  //==========================================================================

    //operator jcb_e23_row_dofs_type<T>& () const

    row_dofs_type& lrow_dofs2(lmat);

   //==========================================================================

    //void metric(const jcb_e23_lite& xjcb, st2_e2_lite& xresult);

    st2_e2_lite lresult;
    metric(lfiber2, lresult); 

    //void symmetric_dot_push(const jcb_e23_lite& xjcb,
	//			       const jcb_e23_lite& xother_jcb,
	//			       st2_e2_lite&  xresult);

    symmetric_dot_push(lfiber2, lfiber2, lresult); 

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

  string lfilename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  // Run tests.

  test_persistent_jacobian_type<jcb_e23>(lns);

  test_volatile_type<jcb_e23>();

  test_jacobian_conversions<jcb_e23>(lns);

  // Test vd facet:

  test_jacobian_vd_facet<jcb_e23>(lns);

  // Test jcb facet:

  test_jcb_facet<jcb_e23>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_jcb_e23_volatile();

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(lfilename + ".hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
