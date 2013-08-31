
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example gln.t.cc
/// Unit test driver for class gln.

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "gl2.h"
#include "gln.h"
#include "gln_space.h"
#include "test_utils.h"
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

  template<typename PB, typename PD>
  void
  test_persistent_common_3(fiber_bundles_namespace& xns)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());

    // Body:

    const string& lfiber_name = PB::static_class_name();

    print_header("Begin testing " + lfiber_name);

    //==========================================================================

    typename PD::host_type& lhost = PD::standard_host(xns, "", false);
    lhost.get_read_write_access(true);
  
    //test_persistent_type<PB>(lhost);

    PB* lfiber = new PB(&lhost);

    typename PB::host_type* lhost2 = lfiber->host();
    cout << "lhost2 = " << lhost2 << endl;

    const string lmember_name("test_fiber");
    lfiber->put_name(lmember_name, true, false);

    const string& lclass_name = lfiber->class_name();
    cout << "lclass_name = " << lclass_name << endl;

    //$$SCRIBBLE: gln has no factor_ct().

    //     int lfactor_ct = lfiber->factor_ct();
    //     cout << "lfactor_ct = " << lfactor_ct << endl;

    PB* lfiber2 = new PB(lfiber);

    //$$SCRIBBLE: Creating lfiber3 on the stack here
    //            results in a seg fault in the destructor.
    //PB lfiber3 = *lfiber;

    const scoped_index lindex = lfiber->index();

    const poset* lposet = dynamic_cast<poset*>(&lhost);
    PB* lfiber4 = new PB(lposet, lmember_name);
    PB* lfiber5 = new PB(lposet, lindex);

    PB* lfiber6 = lfiber5->clone();

    //==========================================================================

    PB lfiber7;
    lfiber7 = *lfiber6;

    //==========================================================================

    //$$SCRIBBLE: gln has no lite_prototype() or lite_type().

    //     // virtual const volatile_type& lite_prototype() const

    //     typename PB::volatile_type lvolatile = lfiber->lite_prototype();

    //     //virtual volatile_type* lite_type() const;

    //     typename PB::volatile_type* lvolatile_ptr = lfiber->lite_type();

    //==========================================================================

    lfiber->detach_from_state();
    lfiber2->detach_from_state();
    //lfiber3.detach_from_state();
    lfiber4->detach_from_state();
    lfiber5->detach_from_state();
    lfiber6->detach_from_state();

    lfiber7.detach_from_state();

    delete lfiber;
    delete lfiber2;
    delete lfiber4;
    delete lfiber5;
    delete lfiber6;

    lhost.release_access();

    //==========================================================================

    print_footer("End testing " + lfiber_name);

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_gln_persistent()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    // Create the namespace.

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

    // Run tests.

    test_persistent_common_3<gln, gl2>(lns);

    // Write the namespace to standard out.

    //cout << lns << endl;

    // Write the namespace to a file.

    //storage_agent write_agent("test_namespace.hdf");
    //write_agent.write_entire(lns);

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

  // Run tests.

  test_gln_volatile();
  test_gln_persistent();

  // Postconditions:

  // Exit:

  return 0;
}
