
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example property_disc_iterator.t.cc

/// @file
/// Test driver for class property_disc_iterator.

#include "field_factory.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "property_disc_iterator.h"
#include "storage_agent.h"
#include "sec_ed_invertible.h"
#include "field_vd.h"
#include "wsv_block.h"

using namespace fields;

namespace
{

///
/// tests property_disc_iterator on xfield.
///
void test_property_disc_iterator(field_vd& xfield)
{
  // Preconditions:

  require(xfield.is_attached());

  // Body:

  xfield.get_read_access();

  int ldf = xfield.coordinates().schema().df();

  // Print out the base space.

  cout << *xfield.base_space().host() << endl;

  // Iterate over the property disc.

  cout << endl << endl
  << "Iterating over disc of property :" << xfield.property().name()
  << endl << endl;

  property_disc_iterator* litr = xfield.new_property_disc_iterator();
  while(!litr->is_done())
  {
    cout << "  id: " << litr->index()
    << " db: " << litr->db()
    << " type_id: " << litr->type_id()
    << " type name:" << litr->type_name()
    << endl;

    cout << "    coord disc: " << endl;

    const block<discretization_context>& lcoord_mbrs =
      litr->coordinate_discretization_members();
    size_type lct = lcoord_mbrs.ct();
    for(size_type i=0; i<lct; ++i)
    {
      discretization_context& lcontext = lcoord_mbrs[i];
      cout << "      eval id: " << setw(3) << lcontext.eval_id.pod()
      << "   local id: " << setw(3) << lcontext.local_id
      << "   disc id: " << setw(3) << lcontext.disc_id.pod()
      << endl;
    }

    litr->get_prop_disc_values(xfield.coordinates());

    cout << "    prop disc: " << endl;

    const block<discretization_context>& lprop_mbrs =
      litr->property_discretization_members();

    lct = lprop_mbrs.ct();
    for(size_type i=0; i<lct; ++i)
    {
      discretization_context& lcontext = lprop_mbrs[i];
      cout << "      eval id: " << setw(3) << lcontext.eval_id.pod()
      << "   local id: " << setw(3) << lcontext.local_id
      << "   disc id: " << setw(3) << lcontext.disc_id.pod();

      cout << "   values:";
      for(int i=0; i<ldf; ++i)
      {
        cout << " " << lcontext.values[i];
      }

      cout << endl;
    }


    litr->next();
  }

  delete litr;
  xfield.release_access();

  // Postconditions:


  // Exit:

  return;
}

///
/// Tests new_scalar_field_1d_unstructured.
///
void
test_new_scalar_field_1d_unstructured(fiber_bundles_namespace& xns,
                                      const poset_path& xproperty_rep_path =
                                        "sec_rep_descriptors/vertex_element_dlinear")
{
  // Create a test field.

  wsv_block<sec_vd_value_type> llower("0");
  wsv_block<sec_vd_value_type> lupper("3");

  string lfield_name("test_1d_unstructured_");
  lfield_name += xproperty_rep_path.member_name();

  field_vd* lfield =
    field_factory::new_scalar_field_1d_unstructured(xns,
        lfield_name,
        3,
        llower,
        lupper,
        field_factory::linear_scalar_fcn,
        xproperty_rep_path);

  test_property_disc_iterator(*lfield);

  return;
}

///
/// Tests delete_field_spaces.
///
void test_delete_field_spaces(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0");
  wsv_block<sec_vd_value_type> lupper("3");

  field_vd* lfield =
    field_factory::new_scalar_field_1d_uniform(xns,
        "test_delete_field_spaces",
        3,
        llower,
        lupper,
        "property_dof_function_example");

  cout << endl << "namespace before deleting field spaces:"
  << static_cast<poset_state_handle&>(xns) << endl;

  field_factory::delete_field_spaces(lfield, true, true);

  cout << endl << "namespace after deleting field spaces:"
  << static_cast<poset_state_handle&>(xns) << endl;

  return;
}

///
/// Tests new_scalar_field_1d_uniform.
///
void test_new_scalar_field_1d_uniform(fiber_bundles_namespace& xns,
                                      const poset_path& xproperty_rep_path =
                                        "sec_rep_descriptors/vertex_element_dlinear")
{
  wsv_block<sec_vd_value_type> llower("0");
  wsv_block<sec_vd_value_type> lupper("3");

  string lfield_name("test_1d_uniform_");
  lfield_name += xproperty_rep_path.member_name();

  field_vd* lfield =
    field_factory::new_scalar_field_1d_uniform(xns,
        lfield_name,
        3,
        llower,
        lupper,
        field_factory::property_dof_function("property_dof_function_example"),
        xproperty_rep_path);

  test_property_disc_iterator(*lfield);

  return;
}

///
/// Tests new_scalar_field_2d_unstructured.
///
void test_new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
    const poset_path& xproperty_rep_path =
      "sec_rep_descriptors/vertex_element_dlinear")
{

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("3 2");

  string lfield_name("test_2d_unstructured_");
  lfield_name += xproperty_rep_path.member_name();

  field_vd* lfield =
    field_factory::new_scalar_field_2d_unstructured(xns,
        lfield_name,
        3,
        2,
        true,
        llower,
        lupper,
        field_factory::property_dof_function("property_dof_function_example"),
        xproperty_rep_path);

  test_property_disc_iterator(*lfield);

  return;
}

#ifdef HAVE_VTK

///
/// Tests Delaunay triangulation version of new_scalar_field_2d_unstructured.
///
void test_new_scalar_field_2d_Delaunay(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("3 2");

  field_vd* lfield =
    field_factory::new_scalar_field_2d_unstructured(xns,
        "test_2d_Delaunay",
        12,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

#endif

///
/// Tests new_scalar_field_2d_uniform.
///
void test_new_scalar_field_2d_uniform(fiber_bundles_namespace& xns,
                                      const poset_path& xproperty_rep_path =
                                        "sec_rep_descriptors/vertex_element_dlinear")
{

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("3 2");

  string lfield_name("test_2d_uniform_");
  lfield_name += xproperty_rep_path.member_name();

  field_vd* lfield =
    field_factory::new_scalar_field_2d_uniform(xns,
        lfield_name,
        3,
        2,
        llower,
        lupper,
        field_factory::property_dof_function("property_dof_function_example"),
        xproperty_rep_path);

  test_property_disc_iterator(*lfield);

  return;
}

///
/// Tests new_scalar_field_3d_unstructured.
///
void test_new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
    const poset_path& xproperty_rep_path =
      "sec_rep_descriptors/vertex_element_dlinear")
{

  wsv_block<sec_vd_value_type> llower("0 0 0");
  wsv_block<sec_vd_value_type> lupper("3 2 1");

  string lfield_name("test_3d_unstructured_");
  lfield_name += xproperty_rep_path.member_name();

  field_vd* lfield =
    field_factory::new_scalar_field_3d_unstructured(xns,
        lfield_name,
        3,
        2,
        1,
        true,
        llower,
        lupper,
        field_factory::property_dof_function("property_dof_function_example"),
        xproperty_rep_path);

  test_property_disc_iterator(*lfield);

  return;
}

#ifdef HAVE_VTK

///
/// Tests Delaunay tesselation version new_scalar_field_3d_unstructured.
///
void test_new_scalar_field_3d_Delaunay(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0 0 0");
  wsv_block<sec_vd_value_type> lupper("3 2 1");

  field_vd* lfield =
    field_factory::new_scalar_field_3d_unstructured(xns,
        "test_3d_Delaunay",
        24,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

#endif

///
/// Tests new_scalar_field_3d_uniform.
///
void test_new_scalar_field_3d_uniform(fiber_bundles_namespace& xns,
                                      const poset_path& xproperty_rep_path =
                                        "sec_rep_descriptors/vertex_element_dlinear")
{

  wsv_block<sec_vd_value_type> llower("0 0 0");
  wsv_block<sec_vd_value_type> lupper("3 2 1");

  string lfield_name("test_3d_uniform_");
  lfield_name += xproperty_rep_path.member_name();

  field_vd* lfield =
    field_factory::new_scalar_field_3d_uniform(xns,
        lfield_name,
        3,
        2,
        1,
        llower,
        lupper,
        field_factory::property_dof_function("property_dof_function_example"),
        xproperty_rep_path);

  test_property_disc_iterator(*lfield);

  return;
}

}
; // End unnamed namespace.

///
/// Main routine.
///
int main(int argc, char* argv[])
{

  fiber_bundles_namespace lns("field_factory.t");
  lns.get_read_write_access();

  //  test_delete_field_spaces(lns);

  test_new_scalar_field_1d_unstructured(lns);
  test_new_scalar_field_1d_unstructured(lns, "sec_rep_descriptors/element_element_constant");

  test_new_scalar_field_1d_uniform(lns);
  test_new_scalar_field_1d_uniform(lns, "sec_rep_descriptors/element_element_constant");

  test_new_scalar_field_2d_unstructured(lns);
  test_new_scalar_field_2d_unstructured(lns, "sec_rep_descriptors/element_element_constant");
  //   test_new_scalar_field_2d_Delaunay(lns);
  test_new_scalar_field_2d_uniform(lns);
  test_new_scalar_field_2d_uniform(lns, "sec_rep_descriptors/element_element_constant");

  test_new_scalar_field_3d_unstructured(lns);
  test_new_scalar_field_3d_unstructured(lns, "sec_rep_descriptors/element_element_constant");
  //   test_new_scalar_field_3d_Delaunay(lns);
  test_new_scalar_field_3d_uniform(lns);
  test_new_scalar_field_3d_uniform(lns, "sec_rep_descriptors/element_element_constant");

  //   cout << lns << endl;

  storage_agent sa("property_disc_iterator.t.hdf");
  sa.write_entire(lns);

  return 0;
}
