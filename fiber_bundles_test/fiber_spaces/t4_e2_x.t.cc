
// $RCSfile: t4_e2_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example t4_e2_x.t.cc
/// Test driver for class t4_e2.

#include "t4_e2.h"

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
  test_t4_e2_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<t4_e2_lite>();

    test_volatile_row_dofs<t4_e2_lite>();

    test_volatile_tp_facet<t4_e2_lite>();

    //==========================================================================

    typedef double value_type;
    typedef t4_e2_row_dofs_type<double> row_dofs_type;

    t4_e2_lite lfiber;
    const t4_e2_lite lfiber_const;

    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs(lfiber);

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs_const(lfiber_const);

    //==========================================================================

    // Other constructors and assignment operators:

    //t4_e2_lite(const st4_e2_lite& xother);

    st4_e2_lite lfiber_st4_e2;
    t4_e2_lite lfiber4(lfiber_st4_e2);

    //t4_e2_lite& operator=(const st4_e2_lite& xother);

    t4_e2_lite lfiber4_assign = lfiber_st4_e2;

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

    // Sym operator functions not exercized elsewhere.

    t4_e2_lite lt4_e2_lite;
    int ld = lt4_e2_lite.d();
    for(int i=0; i<ld; ++i)
    {
      lt4_e2_lite.put_component(i, 100+i); 
    }

    st4_e2_lite lresult;

    //void sym(const t4_e2_lite& x0, st4_e2_lite& xresult);

    sym(lt4_e2_lite, lresult);

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

  test_t4_e2_volatile();

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
