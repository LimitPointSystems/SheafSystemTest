

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example field_e2.t.cc
/// Test driver for class field_e2.

#include "assert_contract.h"
#include "at1_space.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "field_at2_e2.h"
#include "field_e2.h"
#include "sec_at1_space.h"
#include "sec_at2_e2.h"
#include "sec_e2.h"
#include "std_stdexcept.h"
#include "std_iomanip.h"
#include "storage_agent.h"
#include "test_fields.impl.h"

using namespace fields;

namespace
{
  template<typename F>
  void
  test_field_common(fiber_bundles_namespace& xns,
                    const poset_path& xbase_path,
                    const poset_path& xcoords_path)
  {

    // Preconditions:

    require(xns.state_is_read_write_accessible());

    // Body:

    //============================================================================

    F lfield[2];
    make_test_fields(xns, xbase_path, xcoords_path, "property", lfield, 2);

    //virtual const string& class_name() const;

    const string& lclass_name = lfield[0].class_name();
    cout << "lclass_name = " << lclass_name << endl;

    //static const string& static_class_name();

    const string& lstatic_class_name = F::static_class_name();
    cout << "lstatic_class_name = " << lstatic_class_name << endl;

    //virtual bool is_ancestor_of(const any* xother) const;

    bool lis_ancestor_of = lfield[0].is_ancestor_of(&lfield[1]);
    cout << "lis_ancestor_of = " << boolalpha << lis_ancestor_of << endl;

    //bool same_property_fiber_schema(const field_e2& xother,
    //                                 bool xauto_access) const;

    bool lsame_property_fiber_schema =
      lfield[0].same_property_fiber_schema(lfield[0], true);
    cout << "lsame_property_fiber_schema = " << boolalpha
         << lsame_property_fiber_schema << endl;

    //F(const F& xother, bool xauto_access);

    F lcopy = F(lfield[0], true);

    //F(const sec_ed& xcoordinates, const sec_e2& xproperty, bool xauto_access);

    F lfield2 = F(lfield[0].coordinates(), lfield[0].property(), true);

    //virtual field_e2& operator=(const field_vd& xother);

    field_vd* lfield_vd = &lfield[0];
    lfield_vd->get_read_write_access(true, true);
    lfield2 = (*lfield_vd);
    lfield_vd->release_access();

    //virtual F* clone() const;

    F* lclone = lfield[0].clone();
    cout << "lclone = " << lclone << endl;

    //field_e2& operator>>(const field_e2& xsrc, field_e2& xdst);
    //  "not_implemented()"; so catch the exception.

    try
    {
      // Return value is not important in this case since nothing is done.
      operator>>(lfield[0], lfield[1]);
    }
    catch (std::logic_error& le)
    {
      cout << endl;
      cout << "Purposely caught exception: " << le.what () << endl;
      cout << endl;
    }

    //ostream& operator<<(ostream& xos, const field_e2& xfield);

    lfield[0].get_read_access();
    cout << lfield[0] << endl;
    lfield[0].release_access();

    //============================================================================

    // Postconditions:

    // Exit:

  }

} // end unnamed namespace


int
main()
{
  // Preconditions:

  // Body:

  const string& field_name = field_e2::static_class_name();

  print_header("Testing " + field_name);

  // Create the namespace.

  fiber_bundles_namespace lns(field_name + ".t");
  lns.get_read_write_access();

  // Make a base space.

  size_type i_size = 2;
  size_type j_size = 2;

  const poset_path& lbase_path = make_test_base_space(lns, i_size, j_size);

  // Create the coordinates section.

  const poset_path& lcoords_path = make_test_coordinates_2d(lns, lbase_path);

  // Run tests.

  // Test assignment:

  test_field_assignment<field_e2>(lns, lbase_path, lcoords_path);

  // Test vd facet:

  test_field_vd_facet<field_e2>(lns, lbase_path, lcoords_path);

  // Test atp facet:

  test_field_hook_product<field_e2, field_e2, field_at0>
    (lns, lbase_path, lcoords_path);

  test_field_hook_product<field_at2_e2, field_e2, field_e2>
    (lns, lbase_path, lcoords_path);

  test_field_star_operator<field_e2, field_e2>
    (lns, lbase_path, lcoords_path);

  test_field_wedge_product<field_e2, field_e2, field_at2_e2>
    (lns, lbase_path, lcoords_path);

  // Test ed facet:

  test_field_ed_facet<field_e2>(lns, lbase_path, lcoords_path);

  //============================================================================

  test_field_common<field_e2>(lns, lbase_path, lcoords_path);

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(field_name + ".t.hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
