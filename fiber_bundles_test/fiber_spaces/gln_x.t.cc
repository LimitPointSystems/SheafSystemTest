// $RCSfile: gln_x.t.cc,v $ $Revision: 1.10 $ $Date: 2012/03/01 00:40:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example gln_x.t.cc
/// Test driver for class gln.

#include "gln.h"

#include "assert_contract.h"
#include "std_iomanip.h"
//#include "test_fibers_x.impl.h"
//#include "fiber_bundles_namespace.h"
//#include "storage_agent.h"

using namespace fiber_bundle;

namespace
{
  void
  test_gln_volatile()
  {
    // Preconditions:

    // Body:

    //typedef gln_lite V;

    cout << boolalpha;

    //==========================================================================
    // gln facet
    //==========================================================================

    //gln_lite();

    gln_lite lfiber;

    //gln_lite(const gln_lite& xother);

    gln_lite lfiber_copy(lfiber);

    //gln_lite& operator=(const gln_lite& xother);

    gln_lite lfiber_assign = lfiber;

    //virtual ~gln_lite();

    gln_lite* lfiber_ptr = new gln_lite;
    delete lfiber_ptr;

    //==========================================================================
    // gln facet
    //==========================================================================

    //virtual int n() const;

    int ln = lfiber.n();
    cout << "ln = " << ln << endl;

    //virtual int d() const;

    int ld = lfiber.d();
    cout << "ld = " << ld << endl;

   //==========================================================================

    typedef gln_row_dofs_type<double> row_dofs_type;
    typedef double value_type;

    //gln_lite(const row_dofs_type& xrow_dofs);
 
    row_dofs_type lrow_dofs;
    gln_lite lfiber_row_dofs(lrow_dofs);
    
    //gln_lite& operator=(const row_dofs_type& xrow_dofs);


    //==========================================================================
    // group facet
    //==========================================================================

    //==========================================================================
    // abstract_poset_member facet
    //==========================================================================

    //virtual const string& class_name() const;

    const string& lclass_name = lfiber.class_name();
    cout << "lclass_name = " << lclass_name << endl; 

    //static const string& static_class_name();

    const string& lstatic_class_name = lfiber.static_class_name();
    cout << "lstatic_class_name = " << lstatic_class_name << endl; 

    //virtual gln_lite* clone() const;

    //gln_lite* lclone = lfiber.clone();
    //cout << "lclone = " << lclone << endl; 
    //delete lclone;

    //==========================================================================
    // any facet
    //==========================================================================

    //virtual bool is_ancestor_of(const any_lite& xother) const;

    bool lis_ancestor_of = lfiber.is_ancestor_of(lfiber_copy);
    cout << "lis_ancestor_of = " << lis_ancestor_of << endl; 

    //bool invariant() const;

    bool linvariant = lfiber.invariant();
    cout << "linvariant = " << linvariant << endl; 

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

  //fiber_bundles_namespace ns(filename);
  //ns.get_read_write_access();

  // Run tests.

  test_gln_volatile();

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf" + ".hdf");
  //write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}
