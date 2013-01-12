
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example section_pusher_0d.t.cc

/// @file
/// Test driver for section_pusher.


#include "assert_contract.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "field_factory.h"
#include "fields.h"
#include "index_space_iterator.h"
#include "sec_ed_invertible.h"
#include "section_dof_iterator.h"
#include "section_pusher.h"
#include "std_iostream.h"
#include "field_vd.h"
#include "wsv_block.h"

//#define DIAGNOSTIC_OUTPUT 1

using namespace fields;

namespace
{

///
/// Test dc = 1 with dst points = src points.
///
void test_dc_1_a()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2 element quad mesh with xmin = -1.0 and xmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0");

  field_vd* dst =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "dst",
        2,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with same bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.0");
  wsv_block<sec_vd_value_type> lsrc_upper("1.0");

  field_vd* src =
    field_factory::new_scalar_field_1d_points(lns,
        "src",
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  cout << *src << endl;

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=1 points src >>"
                           " equal unstructured dst :",
                           true,
                           true);


}

///
/// Test dc = 1 with src domain larger than dst.
///
void test_dc_1_b()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2 element quad mesh with xmin = -1.0 and xmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0");

  field_vd* dst =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "dst",
        2,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1");

  field_vd* src =
    field_factory::new_scalar_field_1d_points(lns,
        "src",
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=1 points src >>"
                           " smaller unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 1 with src domain slightly smaller than dst.
///
void test_dc_1_c()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2 element quad mesh with xmin = -1.0 and xmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0");

  field_vd* dst =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "dst",
        2,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly compressed bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-0.9");
  wsv_block<sec_vd_value_type> lsrc_upper("0.9");

  field_vd* src =
    field_factory::new_scalar_field_1d_points(lns,
        "src",
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=1 points src >>"
                           " larger unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 1 with src domain larger than dst but finer resolution.
///
void test_dc_1_d()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 8 element quad mesh with xmin = -2.0 and xmax = 2.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0");

  field_vd* dst =
    field_factory::new_scalar_field_1d_unstructured(lns,
        "dst",
        2,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1");

  field_vd* src =
    field_factory::new_scalar_field_1d_points(lns,
        "src",
        8,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=1 fine points src >>"
                           " smaller coarse unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 1 with src domain larger than uniform dst.
///
void test_dc_1_e()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2 element uniform mesh with xmin = -1.0 and xmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0");

  field_vd* dst =
    field_factory::new_scalar_field_1d_uniform(lns,
        "dst",
        2,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1");

  field_vd* src =
    field_factory::new_scalar_field_1d_points(lns,
        "src",
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);
				     
  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=1 points src >>"
                           " smaller uniform dst:",
                           true,
                           true);


}

///
/// Test dc = 2 with dst points = src points.
///
void test_dc_2_a()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2 element quad mesh with xmin and ymin = -1.0 and xmax and ymax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_2d_unstructured(lns,
        "dst",
        2,
        2,
        true,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with same bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.0 -1.0");
  wsv_block<sec_vd_value_type> lsrc_upper("1.0 1.0");

  field_vd* src =
    field_factory::new_scalar_field_2d_points(lns,
        "src",
        2,
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=2 points src >>"
                           " equal unstructured dst :",
                           true,
                           true);


}

///
/// Test dc = 2 with src domain larger than dst.
///
void test_dc_2_b()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2 element quad mesh with xmin and ymin = -1.0 and xmax and ymax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_2d_unstructured(lns,
        "dst",
        2,
        2,
        true,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1 -1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1 1.1");

  field_vd* src =
    field_factory::new_scalar_field_2d_points(lns,
        "src",
        2,
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=2 points src >>"
                           " smaller unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 2 with src domain slightly smaller than dst.
///
void test_dc_2_c()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2 element quad mesh with xmin and ymin = -1.0 and xmax and ymax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_2d_unstructured(lns,
        "dst",
        2,
        2,
        true,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly compressed bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-0.9 -0.9");
  wsv_block<sec_vd_value_type> lsrc_upper("0.9 0.9");

  field_vd* src =
    field_factory::new_scalar_field_2d_points(lns,
        "src",
        2,
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=2 points src >>"
                           " larger unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 2 with src domain larger than dst but finer resolution.
///
void test_dc_2_d()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 8x8 element quad mesh with xmin and ymin = -2.0 and xmax and ymax = 2.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_2d_unstructured(lns,
        "dst",
        2,
        2,
        true,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1 -1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1 1.1");

  field_vd* src =
    field_factory::new_scalar_field_2d_points(lns,
        "src",
        8,
        8,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=2 fine points src >>"
                           " smaller coarse unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 2 with src domain larger than uniform dst.
///
void test_dc_2_e()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2 element uniform mesh with xmin and ymin = -1.0 and xmax and ymax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_2d_uniform(lns,
        "dst",
        2,
        2,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1 -1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1 1.1");

  field_vd* src =
    field_factory::new_scalar_field_2d_points(lns,
        "src",
        2,
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=2 points src >>"
                           " smaller uniform dst:",
                           true,
                           true);


}

///
/// Test dc = 3 with dst points = src points.
///
void test_dc_3_a()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2x2 element hex mesh with xmin, ymin, zmin = -1.0
  // and xmax, ymax, zmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "dst",
        2,
        2,
        2,
        true,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with same bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.0 -1.0 -1.0");
  wsv_block<sec_vd_value_type> lsrc_upper("1.0 1.0 1.0");

  field_vd* src =
    field_factory::new_scalar_field_3d_points(lns,
        "src",
        2,
        2,
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=3 points src >>"
                           " equal unstructured dst :",
                           true,
                           true);


}

///
/// Test dc = 3 with src domain larger than dst.
///
void test_dc_3_b()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2 element hex mesh with xmin, ymin, zmin = -1.0
  // and xmax, ymax, zmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "dst",
        2,
        2,
        2,
        true,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1 -1.1 -1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1 1.1 1.1");

  field_vd* src =
    field_factory::new_scalar_field_3d_points(lns,
        "src",
        2,
        2,
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=3 points src >>"
                           " smaller unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 3 with src domain slightly smaller than dst.
///
void test_dc_3_c()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2x2 element hex mesh with xmin, ymin and zmin = -1.0
  // and xmax, ymax, and zmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "dst",
        2,
        2,
        2,
        true,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly compressed bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-0.9 -0.9 -0.9");
  wsv_block<sec_vd_value_type> lsrc_upper("0.9 0.9 0.9");

  field_vd* src =
    field_factory::new_scalar_field_3d_points(lns,
        "src",
        2,
        2,
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=3 points src >>"
                           " larger unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 3 with src domain larger than dst but finer resolution.
///
void test_dc_3_d()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2x2 element hex mesh with xmin, ymin, zmin = -1.0
  // and xmax, ymax, zmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_3d_unstructured(lns,
        "dst",
        2,
        2,
        2,
        true,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1 -1.1 -1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1 1.1 1.1");

  field_vd* src =
    field_factory::new_scalar_field_3d_points(lns,
        "src",
        8,
        8,
        8,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=3 fine points src >>"
                           " smaller coarse unstructured dst:",
                           true,
                           true);


}

///
/// Test dc = 3 with src domain larger than uniform dst.
///
void test_dc_3_e()
{

  fiber_bundles_namespace lns("section_pusher_0d.t");
  lns.get_read_write_access();

  // An 2x2x2 element uniform mesh with xmin, ymin, zmin = -1.0
  // and xmax, ymax, zmax = 1.0.

  wsv_block<sec_vd_value_type> ldst_lower("-1.0 -1.0 -1.0");
  wsv_block<sec_vd_value_type> ldst_upper("1.0 1.0 1.0");

  field_vd* dst =
    field_factory::new_scalar_field_3d_uniform(lns,
        "dst",
        2,
        2,
        2,
        ldst_lower,
        ldst_upper,
        field_factory::zero);

  // A point mesh with slighly stretched bounds and property == 0.

  wsv_block<sec_vd_value_type> lsrc_lower("-1.1 -1.1 -1.1");
  wsv_block<sec_vd_value_type> lsrc_upper("1.1 1.1 1.1");

  field_vd* src =
    field_factory::new_scalar_field_3d_points(lns,
        "src",
        2,
        2,
        2,
        lsrc_lower,
        lsrc_upper,
        field_factory::zero);

  src->get_read_write_access(false, false);

  // Set the property to the disc id.

  index_space_iterator& ldisc_itr =
    src->property().schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    sec_vd_dof_type ldof = ldisc_itr.pod();
    src->property().put_fiber(ldisc_itr.pod(), &ldof, sizeof(sec_vd_dof_type));
    ldisc_itr.next();
  }
  src->property().schema().discretization_id_space().release_iterator(ldisc_itr);

  // Push the src field to the dst field and print the result.
  // Given the coordinates above, the destation should get the same
  // value as the source.

  *src >> *dst;
  dst->print_property_dofs(cout,
                           0,
                           "After pushing dc=3 points src >>"
                           " smaller uniform dst:",
                           true,
                           true);


}


} //namespace

///
/// Main routine.
///
int
main(int argc, char* argv[])
{

  test_dc_1_a();
  test_dc_1_b();
  test_dc_1_c();
  test_dc_1_d();
  test_dc_1_e();

  test_dc_2_a();
  test_dc_2_b();
  test_dc_2_c();
  test_dc_2_d();
  test_dc_2_e();

  test_dc_3_a();
  test_dc_3_b();
  test_dc_3_c();
  test_dc_3_d();
  test_dc_3_e();

  return 0;
}


