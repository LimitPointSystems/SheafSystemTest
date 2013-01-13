
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example sec_jcb_e23.t.cc
/// Unit test for class sec_jcb_e23.

#include "sec_jcb_e23.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "sec_jcb_space.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;

namespace
{
  template<typename S>
  void
  test_section()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    cout << boolalpha;

    typedef typename S::fiber_type F;

    //static const string& static_class_name();

    print_subheader("Test static const string& static_class_name()");

    const string& lname = S::static_class_name();
    cout << "  lname = " << lname << endl;

    //==========================================================================

    //S();
    print_subheader("Test default constructor: " + lname + "()");

    S lsection;
    cout << "  lsection = " << lsection << endl;

    //S(const S& xother);
    print_subheader("Test copy constructor: " + lname
                    + "(const " + lname +"& xother)");

    S lsection_copy(lsection);
    cout << "  lsection_copy = " << lsection_copy << endl;

    //S& operator=(const S& xother);
    print_subheader("Test assignment operator: " + lname 
                    + "& operator=(const " + lname + "& xother)");
 
    S lsection_assign = lsection;
    cout << "  lsection_assign = " << lsection_assign << endl;

    //S& operator=(const ed_lite& xother);

    ////ed_lite led_lite;
    ////S& lsection_lite_assign = led_lite;

    //virtual const fiber_type& fiber_prototype() const;
    print_subheader("Test virtual const fiber_type& fiber_prototype() const"); 

    const F& lfiber_type = lsection.fiber_prototype();

    // Can't print because it's not attached.
    //cout << "  lfiber_type = " << lfiber_type << endl;

    //virtual S* clone() const;
    print_subheader("Test virtual " + lname +"* clone() const"); 

    S* lsection_clone = lsection.clone();
    cout << "  *lsection_clone = " << *lsection_clone << endl;

    // Not attached; so won't work;
    //S* lsection_clone2 = lsection.clone(false, false);

    //virtual const string& class_name() const;
    print_subheader("Test virtual const string& class_name() const"); 

    const string& lclass_name = lsection.class_name();
    cout << "  lclass_name = " << lclass_name << endl;

    //bool fiber_is_ancestor_of(const any* xother) const;
    print_subheader("Test bool fiber_is_ancestor_of(const any* xother) const"); 

    bool lfiber_is_ancestor_of = lsection.fiber_is_ancestor_of(lsection_clone);
    cout << "lfiber_is_ancestor_of = " << lfiber_is_ancestor_of << endl;

    //bool is_ancestor_of(const any* xother) const;
    print_subheader("Test bool is_ancestor_of(const any* xother) const"); 

    bool lis_ancestor_of = lsection.is_ancestor_of(lsection_clone);
    cout << "lis_ancestor_of = " << lis_ancestor_of << endl;

    //bool invariant() const;
    print_subheader("Test bool invariant() const"); 

    bool linvariant = lsection.invariant();
    cout << "linvariant = " << linvariant  << endl;

    //==========================================================================


    // Postconditions:

    // Exit:

    return;

  }

} // end unnamed namespace


int
main()
{
  // Preconditions:

  // Body:

  typedef sec_jcb_e23 S;

  const string& lsection_name = S::static_class_name();

  print_header("Begin testing " + lsection_name);

  // Create the namespace.

  fiber_bundles_namespace lns(lsection_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;
  size_type k_size = 2;

  const poset_path& lbase_path =
    make_test_base_space(lns, i_size, j_size, k_size);

  // Run tests.

  //$$SCRIBBLE: Jacobian not complete in fiber_bundles_namespace.

//   // Test assignment:

//   test_assignment<S>(lns, lbase_path);

//   // Test vd facet:

//   //@issue What does it mean to test the vd facet for jacobians?
//   //       They do derive from sec_vd and therefore should pass
//   //       the vd facet tests.

//   test_sec_vd_facet<S>(lns, lbase_path);

//   // Test jcb facet:

//   test_sec_jcb_facet<sec_jcb_e23, sec_e2, sec_e3>(lns, lbase_path);

  //============================================================================

  test_section<S>();

  //$$SCRIBBLE: Jacobian not complete in fiber_bundles_namespace.
  //test_section2<S>();

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(lsection_name + ".t.hdf");
  //write_agent.write_entire(lns);

  print_footer("End testing " + lsection_name);

  // Postconditions:

  // Exit:

  return 0;
}

