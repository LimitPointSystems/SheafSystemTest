// $RCSfile: section_pusher_3d.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:11 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example section_pusher_3d.t.cc

/// @file
/// Test driver for section_pusher.


#include "assert_contract.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "field_factory.h"
#include "fields.h"
#include "sec_ed_invertible.h"
#include "section_dof_iterator.h"
#include "section_pusher.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "field_vd.h"
#include "wsv_block.h"

//#define DIAGNOSTIC_OUTPUT 1

using namespace fields;

namespace
{

///
/// Test fine to coarse to fine push.
///
void test_fine_to_coarse_to_fine_1()
{
  fiber_bundles_namespace lns("section_pusher_3d.t");
  lns.get_read_write_access();

  // An 8x8x8 element hex mesh.

  wsv_block<sec_vd_value_type> xlower("-2.0 -2.0 -2.0");
  wsv_block<sec_vd_value_type> xupper("2.0 2.0 2.0");

  field_vd* fine =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "fine",
        8,
        8,
        8,
        true,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);

  // A 2x2x2 element hex mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "coarse",
        2,
        2,
        2,
        true,
        xlower,
        xupper,
        field_factory::zero);


  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;

  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_fine_to_coarse_to_fine_1: after pushing unstructured fine hexs >>"
                              " unstructured coarse hexs:",
                              true,
                              true);

  // Set the coarse field to the exact value and zero out the fine field.

  coarse->put_property_dofs(field_factory::linear_scalar_fcn, true);
  fine->put_property_dofs(field_factory::zero, true);

  // Push the "coarse" field to the "fine" field and
  // print the result compared to the exact value.

  *coarse >> *fine;
  fine->print_property_dofs(cout,
                            field_factory::linear_scalar_fcn,
                            "test_fine_to_coarse_to_fine_1: after pushing unstructured coarse hexs >>"
                            " unstructured fine hexs:",
                            true,
                            true);

}

///
/// Test fine to coarse to fine push.
///
void test_fine_to_coarse_to_fine_2()
{
  fiber_bundles_namespace lns("section_pusher_3d.t");
  lns.get_read_write_access();

  // An 8x8x8 element tet mesh.

  wsv_block<sec_vd_value_type> xlower("-2.0 -2.0 -2.0");
  wsv_block<sec_vd_value_type> xupper("2.0 2.0 2.0");

  field_vd* fine =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "fine",
        8,
        8,
        8,
        false,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);

  // A 2x2x2 element tet mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "coarse",
        2,
        2,
        2,
        false,
        xlower,
        xupper,
        field_factory::zero);


  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;
  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_fine_to_coarse_to_fine_2: after pushing unstructured fine tets >>"
                              " unstructured coarse tets:",
                              true,
                              true);

  // Set the coarse field to the exact value and zero out the fine field.

  coarse->put_property_dofs(field_factory::linear_scalar_fcn, true);
  fine->put_property_dofs(field_factory::zero, true);

  // Push the "coarse" field to the "fine" field and
  // print the result compared to the exact value.

  *coarse >> *fine;
  fine->print_property_dofs(cout,
                            field_factory::linear_scalar_fcn,
                            "test_fine_to_coarse_to_fine_2: after pushing unstructured coarse tets >>"
                            " unstructured fine tets:",
                            true,
                            true);

}

///
/// Test fine to coarse to fine push.
///
void test_fine_to_coarse_to_fine_3()
{
  fiber_bundles_namespace lns("section_pusher_3d.t");
  lns.get_read_write_access();

  // An 8x8x8 element tet mesh.

  wsv_block<sec_vd_value_type> xlower("-2.0 -2.0 -2.0");
  wsv_block<sec_vd_value_type> xupper("2.0 2.0 2.0");

  field_vd* fine =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "fine",
        8,
        8,
        8,
        false,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);

  // A 2x2x2 element hex mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "coarse",
        2,
        2,
        2,
        true,
        xlower,
        xupper,
        field_factory::zero);


  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;
  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_fine_to_coarse_to_fine_3: after pushing unstructured fine tets >>"
                              " unstructured coarse hexs:",
                              true,
                              true);

  // Set the coarse field to the exact value and zero out the fine field.

  coarse->put_property_dofs(field_factory::linear_scalar_fcn, true);
  fine->put_property_dofs(field_factory::zero, true);

  // Push the "coarse" field to the "fine" field and
  // print the result compared to the exact value.

  *coarse >> *fine;
  fine->print_property_dofs(cout,
                            field_factory::linear_scalar_fcn,
                            "test_fine_to_coarse_to_fine_3: after pushing unstructured coarse hexs >> "
                            "unstructured fine tets:",
                            true,
                            true);

}

///
/// Test fine to coarse to fine push.
///
void test_fine_to_coarse_to_fine_4()
{
  fiber_bundles_namespace lns("section_pusher_3d.t");
  lns.get_read_write_access();

  // An 8x8x8 element hex mesh.

  wsv_block<sec_vd_value_type> xlower("-2.0 -2.0 -2.0");
  wsv_block<sec_vd_value_type> xupper("2.0 2.0 2.0");

  field_vd* fine =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "fine",
        8,
        8,
        8,
        true,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);

  // A 2x2x2 element tet mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "coarse",
        2,
        2,
        2,
        false,
        xlower,
        xupper,
        field_factory::zero);


  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;
  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_fine_to_coarse_to_fine_4: after pushing unstructured fine hexs >>"
                              " unstructured coarse tets:",
                              true,
                              true);

  // Set the coarse field to the exact value and zero out the fine field.

  coarse->put_property_dofs(field_factory::linear_scalar_fcn, true);
  fine->put_property_dofs(field_factory::zero, true);

  // Push the "coarse" field to the "fine" field and
  // print the result compared to the exact value.

  *coarse >> *fine;
  fine->print_property_dofs(cout,
                            field_factory::linear_scalar_fcn,
                            "test_fine_to_coarse_to_fine_4: after pushing unstructured coarse tets >> "
                            "unstructured fine hexs:",
                            true,
                            true);

}


///
/// Test fine to coarse to fine push.
///
void test_fine_to_coarse_to_fine_5()
{
  fiber_bundles_namespace lns("section_pusher_3d.t");
  lns.get_read_write_access();

  // An 8x8x8 element uniform mesh.

  wsv_block<sec_vd_value_type> xlower("-2.0 -2.0 -2.0");
  wsv_block<sec_vd_value_type> xupper("2.0 2.0 2.0");

  field_vd* fine =
    field_factory::new_scalar_field_3d_uniform(lns,
        "fine",
        8,
        8,
        8,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);

  // A 2x2x2 element tet mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "coarse",
        2,
        2,
        2,
        false,
        xlower,
        xupper,
        field_factory::zero);


  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;
  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_fine_to_coarse_to_fine_5: after pushing uniform fine >>"
                              " unstructured coarse tets:",
                              true,
                              true);

  // Set the coarse field to the exact value and zero out the fine field.

  coarse->put_property_dofs(field_factory::linear_scalar_fcn, true);
  fine->put_property_dofs(field_factory::zero, true);

  // Push the "coarse" field to the "fine" field and
  // print the result compared to the exact value.

  *coarse >> *fine;
  fine->print_property_dofs(cout,
                            field_factory::linear_scalar_fcn,
                            "test_fine_to_coarse_to_fine_5: after pushing unstructured coarse tets >> "
                            "uniform fine:",
                            true,
                            true);

}

///
/// Test coarse to fine to coarse push.
///
void test_coarse_to_fine_to_coarse()
{
  fiber_bundles_namespace lns("section_pusher_3d.t");
  lns.get_read_write_access();

  // An 8x8x8 element hex.

  wsv_block<sec_vd_value_type> xlower("-2.0 -2.0 -2.0");
  wsv_block<sec_vd_value_type> xupper("2.0 2.0 2.0");

  field_vd* fine =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "fine",
        8,
        8,
        8,
        true,
        xlower,
        xupper,
        field_factory::zero);

  // A 2x2x2 element hex mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "coarse",
        2,
        2,
        2,
        true,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);


  // Push the "coarse" field to the "fine" field and
  // print the result compared to the exact value.

  *coarse >> *fine;
  fine->print_property_dofs(cout,
                            field_factory::linear_scalar_fcn,
                            "test_coarse_to_fine_to_coarse: after pushing unstructured coarse hexs >>"
                            " unstructured fine hexs:",
                            true,
                            true);

  // Set the fine field to the exact value and zero out the coarse field.

  fine->put_property_dofs(field_factory::linear_scalar_fcn, true);
  coarse->put_property_dofs(field_factory::zero, true);

  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;

  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_coarse_to_fine_to_coarse: after pushing unstructured fine hexs >>"
                              " unstructured coarse hexs:",
                              true,
                              true);


}

///
/// Test small to large to small push.
///
void test_small_to_large_to_small()
{
  fiber_bundles_namespace lns("section_pusher_3d.t");
  lns.get_read_write_access();

  // An 2x2x2 element hex mesh.

  wsv_block<sec_vd_value_type> xsmall_lower("-2.0 -2.0 -2.0");
  wsv_block<sec_vd_value_type> xsmall_upper("2.0 2.0 2.0");

  field_vd* small =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "small",
        2,
        2,
        2,
        true,
        xsmall_lower,
        xsmall_upper,
        field_factory::linear_scalar_fcn);

  // A 4x4x4 element hex mesh.

  wsv_block<sec_vd_value_type> xlarge_lower("-3.0 -3.0 -3.0");
  wsv_block<sec_vd_value_type> xlarge_upper("3.0 3.0 3.0");

  field_vd* large =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "large",
        4,
        4,
        4,
        true,
        xlarge_lower,
        xlarge_upper,
        field_factory::zero);


  // Push the "small" field to the "large" field and
  // print the result compared to the exact value.

  *small >> *large;
  large->print_property_dofs(cout,
                             field_factory::linear_scalar_fcn,
                             "test_small_to_large_to_small: after pushing unstructured small hexs >>"
                             "unstructured large hexs:",
                             true,
                             true);

  // Set the large field to the exact value and zero out the small field.

  small->put_property_dofs(field_factory::zero, true);
  large->put_property_dofs(field_factory::linear_scalar_fcn, true);

  // Push the "large" field to the "small" field and
  // print the result compared to the exact value.

  *large >> *small;
  small->print_property_dofs(cout,
                             field_factory::linear_scalar_fcn,
                             "test_small_to_large_to_small: after pushing unstructured large hexs >>"
                             " unstructured small hexs:",
                             true,
                             true);

}

///
/// Test combination of pushes.
///
void test_combination()
{
  // Tests 3 meshes: 2 fine ones of similar but different resolution, and 1
  // that is substantially coarser.  Tests combinations coarse->fine, fine->coarse,
  // fine->fine.  Also tests cases:
  //
  // (1)  the destination coordinate is not within any source edge
  // (2)  the destination coordinate is identical to some source coordinate
  // (3)  the destination coordinate is within some source edge but not
  // identical to any source coordinate
  //
  // All meshes start with coordinate 0 (exactly).  This tests (2).
  //
  // To test (1), every push should be from a "short" mesh to a "long"
  // mesh.  If we arrange the maximum coordinate of each mesh thusly:
  //      fine2 < coarse < fine1
  // then we guarantee that we test condition (1).
  //
  // To test (3), the destination mesh must have an edge length < total length
  // of the source mesh but not an integer multiple of the source mesh edge
  // length.
  //
  // The following conditions are desirable.  They ensure that the test
  // exercises extension.
  //
  //     coarse_mesh_max_coord < fine_mesh_1_max_coord
  //     fine_mesh_2_max_coord < coarse_mesh_max_coord

  fiber_bundles_namespace lns("section_pusher_3d.t");
  lns.get_read_write_access();

  // Make the "fine_1" test case (hexs).

  wsv_block<sec_vd_value_type> xfine_1_lower("0.0 0.0 0.0");
  wsv_block<sec_vd_value_type> xfine_1_upper("10.0 10.0 10.0");

  field_vd* fine_1 =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "fine_1",
        5,
        5,
        5,
        true,
        xfine_1_lower,
        xfine_1_upper,
        field_factory::linear_scalar_fcn);




  // Make the "fine_2" test case (tets).

  wsv_block<sec_vd_value_type> xfine_2_lower("0.0 0.0 0.0");
  wsv_block<sec_vd_value_type> xfine_2_upper("6.0 6.0 6.0");

  field_vd* fine_2 =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "fine_2",
        4,
        4,
        4,
        false,
        xfine_2_lower,
        xfine_2_upper,
        field_factory::zero);

  // Make the "coarse" test case (hexs).

  wsv_block<sec_vd_value_type> xcoarse_lower("0.0 0.0 0.0");
  wsv_block<sec_vd_value_type> xcoarse_upper("8.0 8.0 8.0");

  field_vd* coarse =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "coarse",
        2,
        2,
        2,
        true,
        xcoarse_lower,
        xcoarse_upper,
        field_factory::zero);


  // Case 1: fine mesh 1 -> fine mesh 2 using section_pusher syntax.
  // Section pusher syntax is more efficient if pushing more than one field
  // between given section spaces because the inverter is only initialized once,
  // instead of once for each field.

  section_pusher sp(*fine_1, *fine_2, true);
  sp.push_pa(fine_1->property(), fine_2->property(), true);

  // Print the results.

  fine_2->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_combination: after pushing fine_1 (hexs) >> fine_2 (tets):",
                              true,
                              true);

  // Case 2: fine mesh 2 -> coarse mesh using member function syntax.
  // Member function syntax is more convenient and just as efficient
  // if pushing only a single field.

  push(*fine_2, *coarse, true);

  // Print the results.

  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_combination: after pushing fine_2 (tets) >> coarse (hexs):",
                              true,
                              true);

  // Case 3: coarse mesh -> fine mesh 1 using operator >> syntax.
  // Operator syntax is most convenient of all, but you have to
  // remember what it means.

  // Zero out destination first so we'll know if we got the right answer.

  fine_1->put_property_dofs(field_factory::zero, true);

  *coarse >> *fine_1;

  // Print the results.

  fine_1->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_combination: after pushing coarse (hexs) >> fine_1 (hexs):",
                              true,
                              true);



  // Of course we could have just used operator syntax for the
  // entire sequence. Reset everything and try it.

  fine_1->put_property_dofs(field_factory::linear_scalar_fcn, true);
  fine_2->put_property_dofs(field_factory::zero, true);
  coarse->put_property_dofs(field_factory::zero, true);

  *fine_1 >> *fine_2 >> *coarse >> *fine_1;

  fine_2->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_combination: after pushing fine_1 >> fine_2 >> course >> fine_1:",
                              true,
                              true);

  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_combination: after pushing fine_1 >> fine_2 >> course >> fine_1:",
                              true,
                              true);

  fine_1->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "test_combination: after pushing fine_1 >> fine_2 >> course >> fine_1:",
                              true,
                              true);


  return;
}

} //namespace

///
/// Main routine.
///
int
main(int argc, char* argv[])
{

  // Test fine to coarse to fine (fine=uniform, coarse=tets).

  test_fine_to_coarse_to_fine_5();

  // Test fine to coarse to fine (all hexs).

  test_fine_to_coarse_to_fine_1();

  // Test fine to coarse to fine (all tets).

  test_fine_to_coarse_to_fine_2();

  // Test fine to coarse to fine (fine=tets, coarse=hexs).

  test_fine_to_coarse_to_fine_3();

  // Test fine to coarse to fine (fine=hexs, coarse=tets).

  test_fine_to_coarse_to_fine_4();

  // Test coarse to fine to coarse (all hexs).

  test_coarse_to_fine_to_coarse();

  // Test small domain to large domain to small domain (all hexs).
  // Small domain only partially covers large domain.

  test_small_to_large_to_small();

  // Test a combination of meshes.
  // Tests 3 meshes: 2 fine ones of similar but different resolution, and 1
  // that is substantially coarser.  Tests combinations coarse->fine, fine->coarse,
  // fine->fine.  Also tests cases:
  //
  // 1)  the destination coordinate is not within any source edge
  // 2)  the destination coordinate is identical to some source coordinate
  // 3)  the destination coordinate is within some source edge but not
  //     identical to any source coordinate.

  test_combination();


  return 0;
}


