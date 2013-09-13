
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @example section_pusher_1d.t.cc

/// @file
/// Test driver for section_pusher.


#include "assert_contract.h"
#include "base_space_member.h"
#include "base_space_poset.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "field_factory.h"
#include "fields.h"
#include "namespace_poset.h"
#include "sec_at1_space.h"
#include "sec_e1_uniform.h"
#include "sec_ed_invertible.h"
#include "sec_rep_descriptor.h"
#include "section_dof_iterator.h"
#include "section_pusher.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "structured_block_1d.h"
#include "field_vd.h"
#include "wsv_block.h"

//#define DIAGNOSTIC_OUTPUT 1

using namespace fields;

namespace
{

///
/// Test fine to coarse to fine push.
///
void test_fine_to_coarse_to_fine()
{
  //  post_information_message("Entering test_fine_to_coarse_to_fine");

  fiber_bundles_namespace lns("section_pusher_1d.t");
  lns.get_read_write_access();

  // An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  wsv_block<sec_vd_value_type> xlower("-2.0");
  wsv_block<sec_vd_value_type> xupper("2.0");

  field_vd* fine =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "fine",
        8,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);

  // A 3 element coarse mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "coarse",
        3,
        xlower,
        xupper,
        field_factory::zero);


  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;
  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing unstructured fine >>"
                              " unstructured coarse:",
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
                            "After pushing unstructured coarse >>"
                            " unstructured fine:",
                            true,
                            true);

  //  post_information_message("Leaving test_fine_to_coarse_to_fine");
}

///
/// Test fine to coarse to fine push.
///
void test_fine_to_coarse_to_fine_2()
{
  post_information_message("Entering test_fine_to_coarse_to_fine_2");

  fiber_bundles_namespace lns("section_pusher_1d.t");
  lns.get_read_write_access();

  // An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  wsv_block<sec_vd_value_type> xlower("-2.0");
  wsv_block<sec_vd_value_type> xupper("2.0");

  field_vd* fine =
    field_factory::new_scalar_field_1d_uniform(lns,
        "fine",
        8,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);

  // A 3 element coarse mesh with the same bounds and property == 0.
  field_vd* coarse =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "coarse",
        3,
        xlower,
        xupper,
        field_factory::zero);

  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;
  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing uniform fine >> unstructured coarse:",
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
                            "After pushing unstructured coarse >> uniform fine:",
                            true,
                            true);

}

///
/// Test auto allocated push.
///
void test_auto_allocated_push()
{
  post_information_message("Entering test_auto_allocated_push");

  fiber_bundles_namespace lns("section_pusher_1d.t");
  lns.get_read_write_access();

  // An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  wsv_block<sec_vd_value_type> xlower("-2.0");
  wsv_block<sec_vd_value_type> xupper("2.0");

  field_vd* fine =
    field_factory::new_scalar_field_1d_uniform(lns,
        "fine",
        8,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);

  // A 3 element coarse mesh with the same coord bounds.

  poset_path lpath("coarse_mesh_coordinate_section_space/coordinates_0");
  
  string lbase_name("coarse_mesh");

  base_space_poset* lbase_host = &lns.new_base_space<structured_block_1d>(lbase_name);
  structured_block_1d lbase(lbase_host, 3, true);
  lbase.put_name(lbase_name, true, true);

  sec_rep_space& lhost = lns.new_section_space<sec_e1_uniform>(lpath,
							       lbase.path(),
							       "",
							       true);
  lhost.get_read_write_access();  
  
  sec_e1_uniform coarse_coords(&lhost, -2.0, 2.0, true);
  coarse_coords.put_name("coarse_coords", true, true);

  // Push the "fine" field to the "coarse" mesh and
  // print the result compared to the exact value.

  section_pusher lpusher(*fine, coarse_coords, true);
  sec_vd* coarse_prop = lpusher.push(fine->property(), true);
  coarse_prop->put_name("coarse_prop", true, true);


  field_vd* coarse = new field_vd(coarse_coords, *coarse_prop, true);

  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing uniform fine >> uniform coarse:",
                              true,
                              true);

  coarse_coords.detach_from_state();

  //   cout << lns << endl;

  storage_agent sa("section_pusher_1d.t.hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  post_information_message("Leaving test_auto_allocated_push");

  lbase.detach_from_state();
}

void test_coarse_to_fine_to_coarse()
{
  fiber_bundles_namespace lns("section_pusher_1d.t");
  lns.get_read_write_access();

  // An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  wsv_block<sec_vd_value_type> xlower("-2.0");
  wsv_block<sec_vd_value_type> xupper("2.0");

  field_vd* fine =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "fine",
        8,
        xlower,
        xupper,
        field_factory::zero);

  // A 3 element coarse mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "coarse",
        3,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn);


  // Push the "coarse" field to the "fine" field and
  // print the result compared to the exact value.

  *coarse >> *fine;
  fine->print_property_dofs(cout,
                            field_factory::linear_scalar_fcn,
                            "After pushing unstructured coarse >> unstructured fine:",
                            true,
                            true);

  // Set the fine field to the exact value and zero out the coarse field.

  coarse->put_property_dofs(field_factory::zero, true);
  fine->put_property_dofs(field_factory::linear_scalar_fcn, true);

  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;
  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing unstructured fine >> unstructured coarse:",
                              true,
                              true);

}

///
/// Test fine to coarse to fine push.
///
void test_fine_to_coarse_to_fine_3()
{
  fiber_bundles_namespace lns("section_pusher_1d.t");
  lns.get_read_write_access();

  // An 8 element fine mesh on with xmin = -2.0 and xmax = 2.0.

  wsv_block<sec_vd_value_type> xlower("-2.0");
  wsv_block<sec_vd_value_type> xupper("2.0");

  field_vd* fine =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "fine",
        8,
        xlower,
        xupper,
        field_factory::linear_scalar_fcn,
        "sec_rep_descriptors/element_element_constant");

  // A 3 element coarse mesh with the same bounds and property == 0.

  field_vd* coarse =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "coarse",
        3,
        xlower,
        xupper,
        field_factory::zero,
        "sec_rep_descriptors/element_element_constant");


  // Push the "fine" field to the "coarse" field and
  // print the result compared to the exact value.

  *fine >> *coarse;
  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing constant unstructured fine >>"
                              " constant unstructured coarse:",
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
                            "After pushing constant unstructured coarse >>"
                            " constant unstructured fine:",
                            true,
                            true);

}

///
/// Test small to large to small push.
///
void test_small_to_large_to_small()
{
  fiber_bundles_namespace lns("section_pusher_1d.t");
  lns.get_read_write_access();

  // An 2 element samll mesh on with xmin = -2.0 and xmax = 2.0.

  wsv_block<sec_vd_value_type> xsmall_lower("-2.0");
  wsv_block<sec_vd_value_type> xsmall_upper("2.0");

  field_vd* small =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "small",
        2,
        xsmall_lower,
        xsmall_upper,
        field_factory::linear_scalar_fcn);

  // A 4 element large mesh with xmin = -3.0 and xmax = 3.0.

  wsv_block<sec_vd_value_type> xlarge_lower("-3.0");
  wsv_block<sec_vd_value_type> xlarge_upper("3.0");

  field_vd* large =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "large",
        4,
        xlarge_lower,
        xlarge_upper,
        field_factory::zero);


  // Push the "small" field to the "large" field and
  // print the result compared to the exact value.

  *small >> *large;
  large->print_property_dofs(cout,
                             field_factory::linear_scalar_fcn,
                             "After pushing unstructured small >>"
                             " unstructured large:",
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
                             "After pushing unstructured large >>"
                             " unstructured small:",
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

  fiber_bundles_namespace lns("section_pusher_1d.t");
  lns.get_read_write_access();

  // Make the "fine_1" test case.

  wsv_block<sec_vd_value_type> xfine_1_lower("0.0");
  wsv_block<sec_vd_value_type> xfine_1_upper("10.0");

  field_vd* fine_1 =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "fine_1",
        5,
        xfine_1_lower,
        xfine_1_upper,
        field_factory::linear_scalar_fcn);




  // Make the "fine_2" test case.

  wsv_block<sec_vd_value_type> xfine_2_lower("0.0");
  wsv_block<sec_vd_value_type> xfine_2_upper("6.0");

  field_vd* fine_2 =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "fine_2",
        4,
        xfine_2_lower,
        xfine_2_upper,
        field_factory::zero);

  // Make the "coarse" test case.

  wsv_block<sec_vd_value_type> xcoarse_lower("0.0");
  wsv_block<sec_vd_value_type> xcoarse_upper("8.0");

  field_vd* coarse =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "coarse",
        2,
        xcoarse_lower,
        xcoarse_upper,
        field_factory::zero);


  // Case 1: fine mesh 1 -> fine mesh 2 using section_pusher syntax.
  // Section pusher syntax is more efficient if pushing more than one field
  // between given section spaces because the inverter is only initialized once,
  // instead on once for each field.

  section_pusher sp(*fine_1, *fine_2, true);
  sp.push_pa(fine_1->property(), fine_2->property(), true);

  // Print the results.

  fine_2->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing fine_1 >> fine_2:",
                              true,
                              true);

  // Case 2: fine mesh 2 -> coarse mesh using member function syntax.
  // Member function syntax is more convenient and just as efficient
  // if pushing only a single field.

  push(*fine_2, *coarse, true);

  // Print the results.

  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing fine_2 >> coarse:",
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
                              "After pushing coarse >> fine_1:",
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
                              "After pushing fine_1 >> fine_2 >> course >> fine_1:",
                              true,
                              true);

  coarse->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing fine_1 >> fine_2 >> course >> fine_1:",
                              true,
                              true);

  fine_1->print_property_dofs(cout,
                              field_factory::linear_scalar_fcn,
                              "After pushing fine_1 >> fine_2 >> course >> fine_1:",
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
  // Test auto-allocated push.

  test_auto_allocated_push();

  // Test fine uniform to coarse general to fine uniform.

  test_fine_to_coarse_to_fine_2();

  // Test fine general to coarse general to fine general.

  test_fine_to_coarse_to_fine();

  // Test fine general to coarse general to fine general with
  // element_element_constant property representation..

  test_fine_to_coarse_to_fine_3();

  // Test coarse general to fine general to coarse general.

  test_coarse_to_fine_to_coarse();

  // Test small domain to large domain to small domain (all quads).
  // Small domain only partially covers large domain.

  test_small_to_large_to_small();

  // Test a combination of meshes.
  // Tests 3 meshes: 2 fine ones of similar but different resolution, and 1
  // that is substantially coarser.  Tests combinations coarse->fine, fine->coarse,
  // fine->fine.  Also tests cases:
  //
  // (1)  the destination coordinate is not within any source edge
  // (2)  the destination coordinate is identical to some source coordinate
  // (3)  the destination coordinate is within some source edge but not
  // identical to any source coordinate

  test_combination();

  return 0;
}


