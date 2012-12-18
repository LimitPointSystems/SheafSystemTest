// $RCSfile: multisection_pusher.t.cc,v $ $Revision: 1.9 $ $Date: 2012/03/01 00:41:10 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//


/// @example multisection_pusher.t.cc

/// @file
/// test driver for mutli-valued sections.

#include "average_push_action.h"
#include "assert_contract.h"
#include "base_space_member.h"
#include "base_space_poset.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "field_factory_2.h"
#include "preorder_iterator.h"
#include "section_pusher.h"
#include "sec_at0.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_e1_uniform.h"
#include "sec_ed_invertible.h"
#include "sec_rep_space.h"
#include "std_cmath.h"
#include "std_sstream.h"
#include "storage_agent.h"
#include "subposet.h"
#include "subposet_member_iterator.h"
#include "tern.h"

using namespace fields;

namespace
{

///
/// Creates a simple decomposition in the base space of xfield.
///
void make_decomposition(field_vd* xfield)
{
  // Preconditions:

  // Body:

  // Create a decomposition in the base space.

  base_space_poset* lbase_host =
    dynamic_cast<base_space_poset*>(xfield->base_space().host());
  lbase_host->get_read_write_access();

  subposet lparts(lbase_host);
  lparts.put_name("parts", true, false);

  id_map* lele_map = lbase_host->elements().id_map();

  scoped_index lexpansion[4];
  scoped_index lindex = lbase_host->internal_id();
  for(int i=0; i<4; i++)
  {
    lindex = lele_map->poset_id(i);
    lexpansion[i] = lindex;
  }
  
  base_space_member lpart0(lbase_host, lexpansion, 4, tern::NEITHER, false);
  lpart0.put_name("part0", true, true);
  lparts.insert_member(lpart0.index());
  lpart0.detach_from_state();

  for(int i=4; i<8; i++)
  {
    lindex = lele_map->poset_id(i);
    lexpansion[i-4] = lindex;
  }

  base_space_member lpart1(lbase_host, lexpansion, 4, tern::NEITHER, false);
  lpart1.put_name("part1", true, true);
  lparts.insert_member(lpart1.index());
  lpart1.detach_from_state();

  lparts.detach_from_state();
  lbase_host->release_access();

  // Postconditions:

  // Exit:

  return;
}

///
/// Names the vertices in the base space of xfield.
///
void make_names(field_vd* xfield)
{
  // Preconditions:

  // Body:

  base_space_poset* lbase_host =
    dynamic_cast<base_space_poset*>(xfield->base_space().host());
  lbase_host->get_read_write_access();

  subposet& lvertices = lbase_host->vertices();
  id_map* lmap = lvertices.id_map();
  subposet_member_iterator* litr = lvertices.member_iterator();
  while(!litr->is_done())
  {
    stringstream lstr;
    lstr << lmap->client_id(litr->index());
    litr->put_name(lstr.str(), true, false);
    litr->next();
  }

  delete litr;
  lbase_host->release_access();

  // Postconditions:

  // Exit:

  return;
}

///
/// Property dof function that sets all dofs to corresponding coord component.
///
void equals_coords(block<sec_vd_value_type>& xglobal_coords,
                   block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  // Body:

  xproperty_dofs.assign(0.0);

  for(int i=0; i<xproperty_dofs.ct(); ++i)
  {
    xproperty_dofs[i] = xglobal_coords[i];
  }


  // Postconditions:

  ensure_for_all(i, 0, xproperty_dofs.ct(), xproperty_dofs[i] == xglobal_coords[i]);

  // Exit:

  return;
}


///
/// Property dof function that sets all dofs to 0.0
///
void zero(block<sec_vd_value_type>& xglobal_coords,
          block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  // Body:

  xproperty_dofs.assign(0.0);

  // Postconditions:

  ensure_for_all(i, 0, xproperty_dofs.ct(), xproperty_dofs[i] == 0.0);

  // Exit:

  return;
}


///
/// Property dof function that sets all dofs to -1.0
///
void minus_one(block<sec_vd_value_type>& xglobal_coords,
               block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  // Body:

  xproperty_dofs.assign(-1.0);

  // Postconditions:

  ensure_for_all(i, 0, xproperty_dofs.ct(), xproperty_dofs[i] == -1.0);

  // Exit:

  return;
}


///
/// Property dof function that computes sphreical surface from lat-lon coordinates.
///
void sphere(block<sec_vd_value_type>& xglobal_coords,
            block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  // Body:

  double theta = xglobal_coords[0];
  double phi = xglobal_coords[1];

  // -pi/2 < phi < pi/2

  double r_cos_phi = cos(phi); // r = 1.0
  double x = r_cos_phi*cos(theta);
  double y = r_cos_phi*sin(theta);
  double z = sin(phi); // r = 1.0

  xproperty_dofs[0] = x;
  xproperty_dofs[1] = y;
  xproperty_dofs[2] = z;

  // Postconditions:

  // Exit:

  return;
}


///
/// Property dof function that computes sphreical surface from lat-lon coordinates.
///
void plus_shifted_sphere(block<sec_vd_value_type>& xglobal_coords,
                         block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  // Body:

  double theta = xglobal_coords[0];
  double phi = xglobal_coords[1];

  // Shift theta a little so cells a +180 will overlap the dateline;
  // tests handling of cell that straddle the dateline.

  theta += M_PI*0.10;

  // -pi/2 < phi < pi/2

  double r_cos_phi = cos(phi); // r = 1.0
  double x = r_cos_phi*cos(theta);
  double y = r_cos_phi*sin(theta);
  double z = sin(phi); // r = 1.0

  xproperty_dofs[0] = x;
  xproperty_dofs[1] = y;
  xproperty_dofs[2] = z;

  // Postconditions:

  // Exit:

  return;
}


///
/// Property dof function that computes sphreical surface from lat-lon coordinates.
///
void minus_shifted_sphere(block<sec_vd_value_type>& xglobal_coords,
                          block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  // Body:

  double theta = xglobal_coords[0];
  double phi = xglobal_coords[1];

  // Shift theta a little so cells a +180 will overlap the dateline;
  // tests handling of cell that straddle the dateline.

  theta -= M_PI*0.10;

  // -pi/2 < phi < pi/2

  double r_cos_phi = cos(phi); // r = 1.0
  double x = r_cos_phi*cos(theta);
  double y = r_cos_phi*sin(theta);
  double z = sin(phi); // r = 1.0

  xproperty_dofs[0] = x;
  xproperty_dofs[1] = y;
  xproperty_dofs[2] = z;

  // Postconditions:

  // Exit:

  return;
}


///
/// Creates a multi-valued property section in the property space of xfield
///
field_vd* make_property_multi_section_field(field_vd* xfield)
{
  post_information_message("Entering make_property_multi_section_field");

  // Preconditions:

  require(xfield != 0);

  // Body:

  sec_rep_space* lhost = xfield->property().host();
  lhost->get_read_write_access();

  subposet lparts(lhost->schema().base_space().host(), "parts");
  sec_at0 lmulti_section(lhost, lparts, false);
  lmulti_section.put_name("multi_section1", true, false);

  sec_at0 lbranch;

  preorder_iterator litr(lmulti_section, "jims");
  while(!litr.is_done())
  {
    lbranch.attach_to_state(lhost, litr.index());
    int ldisc_ct = lbranch.schema().discretization_ct();

    for(int i=0; i<ldisc_ct; ++i)
    {
      double ldof = i;
      lbranch.put_discretization_dofs(i, false, &ldof, 1);
    }
    litr.truncate();
  }

  lbranch.detach_from_state();
  lparts.detach_from_state();
  lhost->release_access();

  field_vd* result =
    new field_vd(xfield->coordinates(), lmulti_section, true);

  lmulti_section.detach_from_state();


  // Postconditions:


  // Exit:

  post_information_message("Leaving make_property_multi_section_field");
  return result;
}

///
/// Sets xbranch to xcoords with the x component shifted by xshift.
///
void shift_coords(sec_vd& xcoords, sec_vd& xbranch, sec_vd_dof_type xshift)
{
  // Preconditions:


  // Body:

  int ldf = xcoords.schema().df();
  block<sec_vd_dof_type> ldofs(ldf);
  ldofs.set_ct(ldf);

  id_map& lseq_id_map = xbranch.schema().disc_seq_id_map();
  int ldisc_ct = xbranch.schema().discretization_ct();

  for(int i=0; i<ldisc_ct; ++i)
  {
    scoped_index lid = lseq_id_map.poset_id(i);
    xcoords.get_discretization_dofs(lid, true, ldofs.base(), ldofs.ct());

    // Shift the second branch to the left half a unit.

    ldofs[0] += xshift;

    xbranch.put_discretization_dofs(i, false, ldofs.base(), ldofs.ct());
  }


  // Postconditions:


  // Exit:

  return;
}

///
/// Creates a multi-valued coordinate section in the coord space of xfield
///
field_vd* make_coordinate_multi_section_field(field_vd* xfield)
{
  post_information_message("Entering make_coordinate_multi_section_field");

  // Preconditions:

  require(xfield != 0);

  xfield->get_read_write_access(true, true);

  require((1 <= xfield->dc()) && (xfield->dc() <= 3));

  // Body:

  // Get access to the coordinates space.

  sec_rep_space* lhost = xfield->coordinates().host();

  // Create the coordinates multisection.

  subposet lparts(lhost->schema().base_space().host(), "parts");
  sec_ed* lmulti_section;
  switch(xfield->dc())
  {
  case 1:
    lmulti_section = new sec_e1(lhost, lparts, false);
    break;
  case 2:
    lmulti_section = new sec_e2(lhost, lparts, false);
    break;
  case 3:
    lmulti_section = new sec_e3(lhost, lparts, false);
    break;
  }

  lmulti_section->put_name("multi_section1", true, false);

  // Set the dofs for each branch.

  sec_ed lbranch;

  preorder_iterator litr(*lmulti_section, "jims");

  // First branch. Coordinates shifted to right.

  lbranch.attach_to_state(lhost, litr.index());
  shift_coords(xfield->coordinates(), lbranch, 0.5);
  litr.truncate();

  // Second branch. Coordinates shifted to left.

  lbranch.attach_to_state(lhost, litr.index());
  shift_coords(xfield->coordinates(), lbranch, -0.5);
  litr.truncate();

  assertion(litr.is_done());

  lbranch.detach_from_state();
  lparts.detach_from_state();
  xfield->release_access();

  // Create the result with the coordinate multisection
  // and the input property section.

  field_vd* result =
    new field_vd(*lmulti_section, xfield->property(), true);

  lmulti_section->detach_from_state();
  delete lmulti_section;

  // Postconditions:


  // Exit:

  post_information_message("Leaving make_coordinate_multi_section_field");
  return result;
}



///
/// Creates a 1D field space.
///
field_vd* make_1d_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_1d_field_space");

  field_factory_2<sec_e1, sec_at0, structured_block_1d> lfactory;

  lfactory.base_index_ubs() = "8";

  lfactory.coord_section_space_path() = "test_1d_coord_section_space";
  lfactory.coord_lb() = "0";
  lfactory.coord_ub() = "8";

  lfactory.prop_section_space_path() = "test_1d_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_1d_base_space/mesh",
                       "coordinates",
                       "property");

  //   lfield->get_read_access();
  //   cout << *lfield->coordinates().host() << endl;
  //   lfield->release_access();


  lfield->put_property_dofs(equals_coords, true);

  post_information_message("Leaving make_1d_field_space");
  return lfield;
}

///
/// Creates a larger 1D field space for the destination.
///
field_vd* make_larger_1d_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_larger_1d_field_space");

  field_factory_2<sec_e1, sec_at0, structured_block_1d> lfactory;

  lfactory.base_index_ubs() = "10";

  lfactory.coord_section_space_path() = "test_larger_1d_coord_section_space";
  lfactory.coord_lb() = "0";
  lfactory.coord_ub() = "10";

  lfactory.prop_section_space_path() = "test_larger_1d_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_larger_1d_base_space/mesh",
                       "coordinates",
                       "property");

  lfield->put_property_dofs(minus_one, true);

  post_information_message("Leaving make_larger_1d_field_space");

  return lfield;
}

///
/// Creates a field space over a 2D base space.
///
field_vd* make_2d_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_2d_field_space");

  field_factory_2<sec_e2, sec_at0, structured_block_2d> lfactory;

  lfactory.base_index_ubs() = "4 2";

  lfactory.coord_section_space_path() = "test_2d_coord_section_space";
  lfactory.coord_lb() = "0 0";
  lfactory.coord_ub() = "4 2";

  lfactory.prop_section_space_path() = "test_2d_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_2d_base_space/mesh",
                       "coordinates",
                       "property");

  lfield->put_property_dofs(equals_coords, true);

  post_information_message("Leaving make_2d_field_space");
  return lfield;
}


///
/// Creates a field space over a larger 2D base space.
///
field_vd* make_larger_2d_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_larger_2d_field_space");

  field_factory_2<sec_e2, sec_at0, structured_block_2d> lfactory;

  lfactory.base_index_ubs() = "5 2";

  lfactory.coord_section_space_path() = "test_larger_2d_coord_section_space";
  lfactory.coord_lb() = "0 0";
  lfactory.coord_ub() = "5 2";

  lfactory.prop_section_space_path() = "test_larger_2d_prop_section_space";

  field_vd* lfield =
    lfactory.new_field(xns,
                       "test_larger_2d_base_space/mesh",
                       "coordinates",
                       "property");

  lfield->put_property_dofs(minus_one, true);

  post_information_message("Leaving make_larger_2d_field_space");
  return lfield;
}

///
/// Test the property multi section pusher.
///
void test_property_multi_section_pusher(field_vd* xdst_field_1,
                                        field_vd* xdst_field_2)
{
  post_information_message("Entering test_property_multi_section_pusher");

  // Preconditions:


  // Body:

  // Create a property multi-section source field.

  field_vd* lsrc_field = make_property_multi_section_field(xdst_field_1);

  post_information_message("Initial values for field 1");

  xdst_field_1->get_read_access();
  cout << *xdst_field_1->base_space().host() << endl;
  cout << *xdst_field_1->coordinates().host() << endl;
  cout << *xdst_field_1->property().host() << endl;
  xdst_field_1->release_access();

  // Push it to a new destination section in the property space
  // of xdst_field_1..

  post_information_message("Push to field 1 with default overlap action");

  section_pusher lpusher1(*lsrc_field, *xdst_field_1, true);
  sec_vd* ldst = lpusher1.push(lsrc_field->property(), true);
  ldst->detach_from_state();

  // Replace the default overlap action with average action and
  // push source to a new destination section in the property
  // section space of xdst_field_1.

  post_information_message("Push to field 1 with average overlap action");

  lpusher1.put_overlap_action(*(new average_push_action(1)));
  lpusher1.push(lsrc_field->property(), true);

  // Output the results.

  xdst_field_1->get_read_access();
  cout << *xdst_field_1->base_space().host() << endl;
  cout << *xdst_field_1->coordinates().host() << endl;
  cout << *xdst_field_1->property().host() << endl;
  xdst_field_1->release_access();

  // Push the source to a new section in the space of xdst_field_2;
  // tests the default extension action.

  post_information_message("Push to field 2 with average overlap action");

  section_pusher lpusher2(*lsrc_field, *xdst_field_2, true);
  lpusher2.put_overlap_action(*(new average_push_action(1)));
  lpusher2.push(lsrc_field->property(), true);

  // Output the results.

  xdst_field_2->get_read_access();
  cout << *xdst_field_2->base_space().host() << endl;
  cout << *xdst_field_2->coordinates().host() << endl;
  cout << *xdst_field_2->property().host() << endl;
  xdst_field_2->release_access();

  // Postconditions:


  // Exit:

  post_information_message("Leaving test_property_multi_section_pusher");
  return;
}

///
/// Test the coordinate mulit section pusher.
///
void test_coordinate_multi_section_pusher(field_vd* xdst_field_1,
    field_vd* xdst_field_2)
{
  post_information_message("Entering test_coordinate_multi_section_pusher");

  // Preconditions:

  require(xdst_field_1->base_space().host()->includes_subposet("parts"));

  // Body:

  // Create a coordinates multi-section source field
  // with the same property section as xdst_field_1.

  field_vd* lsrc_field = make_coordinate_multi_section_field(xdst_field_1);

  // Make a new property section for xdst_field_1.

  xdst_field_1->property().new_jim_state();

  // Push the source to xdst_field_1.

  push(*lsrc_field, *xdst_field_1, true);

  // Replace the default overlap action with average action and
  // push source to a new destination section in the property
  // section space of xdst_field_1.

  section_pusher lpusher(*lsrc_field, *xdst_field_1, true);
  lpusher.put_overlap_action(*(new average_push_action(1)));
  lpusher.push(lsrc_field->property(), true);

  // Output the results.

  cout << endl << endl;
  cout << "=================================================" << endl;
  cout << "Results of push to xdst_field_1:" << endl;
  cout << "=================================================" << endl;

  xdst_field_1->get_read_access();
  cout << *xdst_field_1->base_space().host() << endl;
  cout << *xdst_field_1->coordinates().host() << endl;
  cout << *xdst_field_1->property().host() << endl;
  xdst_field_1->release_access();

  // Push the source to a new section in the space of xdst_field_2;
  // tests the default extension action.

  section_pusher lpusher2(*lsrc_field, *xdst_field_2, true);
  lpusher2.put_overlap_action(*(new average_push_action(1)));
  lpusher2.push(lsrc_field->property(), true);

  // Output the results.

  cout << endl << endl;
  cout << "=================================================" << endl;
  cout << "Results of push to xdst_field_2:" << endl;
  cout << "=================================================" << endl;

  xdst_field_2->get_read_access();
  cout << *xdst_field_2->base_space().host() << endl;
  cout << *xdst_field_2->coordinates().host() << endl;
  cout << *xdst_field_2->property().host() << endl;
  xdst_field_2->release_access();

  // Postconditions:


  // Exit:

  post_information_message("Leaving test_coordinate_multi_section_pusher");
  return;
}

///
/// Creates a field space over a cylindrical base space.
///
field_vd* make_cylindrical_src_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_src_cylindrical_field_space");

  // Make property versus theta-phi field.

  field_factory_2<sec_e2, sec_at0, structured_block_2d> lfactory1;

  lfactory1.base_index_ubs() = "10 6";

  lfactory1.coord_section_space_path() =
    "test_cylindrical_src_theta_phi_section_space";
  lfactory1.coord_lb().push_back(-M_PI);
  lfactory1.coord_lb().push_back(-M_PI/3.0); // Stay away from the south pole
  lfactory1.coord_ub().push_back(M_PI);
  lfactory1.coord_ub().push_back(M_PI/3.0); // Stay away from the north pole.

  lfactory1.prop_section_space_path() = "test_cylindrical_src_prop_section_space";

  field_vd* lfield1 =
    lfactory1.new_field(xns,
                        "test_cylindrical_src_base_space/mesh",
                        "theta_phi",
                        "property");

  lfield1->put_property_dofs(equals_coords, true);

  //   lfield1->get_read_access();
  //   cout << *lfield1 << endl;
  //   lfield1->release_access();


  field_factory_2<sec_e2, sec_e3, structured_block_2d> lfactory2;

  lfactory2.coord_section_space_path() =
    "test_cylindrical_src_theta_phi_section_space";

  lfactory2.prop_section_space_path() =
    "test_cylindrical_src_surface_section_space";

  field_vd* lfield2 =
    lfactory2.new_field(xns,
                        "test_cylindrical_src_base_space/mesh",
                        "theta_phi",
                        "sphere");

  lfield2->put_property_dofs(sphere, true);

  field_vd* lfield3 =
    lfactory2.new_field(xns,
                        "test_cylindrical_src_base_space/mesh",
                        "theta_phi",
                        "plus_shifted_sphere");

  lfield3->put_property_dofs(plus_shifted_sphere, true);

  //   lfield2->get_read_access();
  //   cout << *lfield2 << endl;
  //   lfield2->release_access();

  field_vd* result =
    new field_vd(dynamic_cast<sec_ed&>(lfield3->property()), lfield1->property(), true);

  //   result->get_read_access();
  //   cout << *result << endl;
  //   result->release_access();

  post_information_message("Leaving make_cylindrical_src_field_space");
  return result;
}

///
/// Creates a field space over a cylindrical base space.
///
field_vd* make_cylindrical_multi_src_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_multi_src_cylindrical_field_space");


  // Make the parts subposet in the base space.

  base_space_poset* lbase_space =
    dynamic_cast<base_space_poset*>(xns.member_poset("test_cylindrical_src_base_space", true));
  lbase_space->get_read_write_access();

  int lzone_ct = lbase_space->elements().member_ct();
  int lpart_1_ct = lzone_ct/2;

  id_map* lzone_map = lbase_space->elements().id_map();
  block<scoped_index> lpart_ids(64);

  scoped_index lindex(lzone_map);

  for(int i=0; i<lpart_1_ct; ++i)
  {
    lindex = i;
    
    lpart_ids.push_back(lindex);
  }
  base_space_member lpart_1(lbase_space, lpart_ids.base(), lpart_ids.ct(), tern::NEITHER, true);
  lpart_1.put_name("part_1", true, true);

  lpart_ids.set_ct(0);
  for(int i=lpart_1_ct; i< lzone_ct; ++i)
  {
    lindex = i;

    lpart_ids.push_back(lindex);
  }
  base_space_member lpart_2(lbase_space, lpart_ids.base(), lpart_ids.ct(), tern::NEITHER, true);
  lpart_2.put_name("part_2", true, true);


  subposet lparts(lbase_space, 0, false);
  lparts.put_name("parts", true, false);
  lparts.insert_member(&lpart_1);
  lparts.insert_member(&lpart_2);

  // Make a surface multi-section.

  sec_rep_space* lsec_space =
    dynamic_cast<sec_rep_space*>(xns.member_poset("test_cylindrical_src_surface_section_space", true));
  lsec_space->get_read_write_access();

  sec_e3 lmulti(lsec_space, lparts, true);
  lmulti.put_name("multi-sphere", true, false);

  // Set the dofs of the branches.

  sec_e2 ltheta_phi(&xns, "test_cylindrical_src_theta_phi_section_space/theta_phi", true);

  preorder_iterator lbranch_itr(lmulti, "jims");

  sec_e3 lbranch_1(lsec_space, lbranch_itr.index());
  field_vd lfield_1(ltheta_phi, lbranch_1, true);
  lfield_1.put_property_dofs(plus_shifted_sphere, true);

  lbranch_itr.next();

  sec_e3 lbranch_2(lsec_space, lbranch_itr.index());
  field_vd lfield_2(ltheta_phi, lbranch_2, true);
  lfield_2.put_property_dofs(minus_shifted_sphere, true);

  lbranch_itr.next();
  assertion(lbranch_itr.is_done());

  // Create the result field, property vs multi-sphere

  sec_at0 lprop(&xns, "test_cylindrical_src_prop_section_space/property", true);

  field_vd* result = new field_vd(lmulti, lprop, true);

  lprop.detach_from_state();
  lbranch_2.detach_from_state();
  lbranch_1.detach_from_state();
  ltheta_phi.detach_from_state();
  lmulti.detach_from_state();
  lsec_space->release_access();
  lparts.detach_from_state();
  lpart_2.detach_from_state();
  lpart_1.detach_from_state();
  lbase_space->release_access();


  //   result->get_read_access();
  //   cout << *result << endl;
  //   result->release_access();

  post_information_message("Leaving make_cylindrical_multi_src_field_space");
  return result;
}

///
/// Creates a field space over a cylindrical base space.
///
field_vd* make_cylindrical_dst_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_cylindrical_dst_field_space");

  // Make property versus theta-phi field.

  field_factory_2<sec_e2, sec_at0, structured_block_2d> lfactory1;

  lfactory1.base_index_ubs() = "12 6";

  lfactory1.coord_section_space_path() =
    "test_cylindrical_dst_theta_phi_section_space";
  lfactory1.coord_lb().push_back(-M_PI);
  lfactory1.coord_lb().push_back(-M_PI/3.0); // Stay away from the south pole
  lfactory1.coord_ub().push_back(M_PI);
  lfactory1.coord_ub().push_back(M_PI/3.0); // Stay away from the north pole.

  lfactory1.prop_section_space_path() = "test_cylindrical_dst_property_section_space";

  field_vd* lfield1 =
    lfactory1.new_field(xns,
                        "test_cylindrical_dst_base_space/mesh",
                        "theta_phi",
                        "property");

  lfield1->put_property_dofs(zero, true);

  field_factory_2<sec_e2, sec_e3, structured_block_2d> lfactory2;

  lfactory2.coord_section_space_path() =
    "test_cylindrical_dst_theta_phi_section_space";

  lfactory2.prop_section_space_path() =
    "test_cylindrical_dst_surface_section_space";

  field_vd* lfield2 =
    lfactory2.new_field(xns,
                        "test_cylindrical_dst_base_space/mesh",
                        "theta_phi",
                        "sphere");

  lfield2->put_property_dofs(sphere, true);

  field_vd* result =
    new field_vd(dynamic_cast<sec_ed&>(lfield2->property()), lfield1->property(), true);

  post_information_message("Leaving make_cylindrical_dst_field_space");
  return result;
}



///
/// Creates a field space over a cylindrical base space.
///
field_vd* make_cylindrical_multi_dst_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_cylindrical_dst_field_space");

  // Make property versus theta-phi field.

  field_factory_2<sec_e3, sec_at0, structured_block_2d> lfactory2;

  lfactory2.coord_section_space_path() =
    "test_cylindrical_dst_surface_section_space";

  lfactory2.prop_section_space_path() =
    "test_cylindrical_dst_property_section_space";

  field_vd* lfield2 =
    lfactory2.new_field(xns,
                        "test_cylindrical_dst_base_space/mesh",
                        "sphere",
                        "multi-property");

  lfield2->put_property_dofs(zero, true);


  post_information_message("Leaving make_cylindrical_multi_dst_field_space");
  return lfield2;
}

///
/// Test the sylindrical mono section pusher.
///
void test_cylindrical_mono_section_pusher(fiber_bundles_namespace& xns)
{
  post_information_message("Entering test_cylindrical_mono_section_pusher");

  // Preconditions:

  // Body:

  // Create the src and dst.

  field_vd* lsrc = make_cylindrical_src_field_space(xns);
  field_vd* ldst = make_cylindrical_dst_field_space(xns);

  // Push.

  push(*lsrc, *ldst, true);

  // Output the results.

  cout << endl << endl;
  cout << "=================================================" << endl;
  cout << "Results of cylindrical push:" << endl;
  cout << "=================================================" << endl;

  lsrc->get_read_access();
  cout << *lsrc << endl;
  lsrc->release_access();

  ldst->get_read_access();
  cout << *ldst << endl;
  ldst->release_access();

  // Postconditions:


  // Exit:

  post_information_message("Leaving test_cylindrical_mono_section_pusher");
  return;
}

///
/// Text the cylindrical muli section pusher.
///
void test_cylindrical_multi_section_pusher(fiber_bundles_namespace& xns)
{
  post_information_message("Entering test_cylindrical_multi_section_pusher");

  // Preconditions:

  // Body:

  // Create the src and dst.

  field_vd* lsrc = make_cylindrical_multi_src_field_space(xns);
  field_vd* ldst = make_cylindrical_multi_dst_field_space(xns);

  // Push.


  lsrc->push(*ldst, true);

  // Output the results.

  cout << endl << endl;
  cout << "=================================================" << endl;
  cout << "Results of cylindrical multi push:" << endl;
  cout << "=================================================" << endl;

  // Stream insertion operator call print_proerty_dofs,
  // which can't handle multi-sections.

  //   lsrc->get_read_access();
  //   cout << *lsrc << endl;
  //   lsrc->release_access();

  ldst->get_read_access();
  cout << *ldst << endl;
  ldst->release_access();

  // Postconditions:


  // Exit:

  post_information_message("Leaving test_cylindrical_multi_section_pusher");
  return;
}

} // end unnamed namespace

///
/// Main routine.
///
int main()
{

  fiber_bundles_namespace lns("multi_section_pusher.t");

  lns.get_read_write_access();

  // 1D tests:

  field_vd* lfield_1d = make_1d_field_space(lns);
  field_vd* llarger_field_1d = make_larger_1d_field_space(lns);

  make_names(lfield_1d);
  make_decomposition(lfield_1d);
  make_names(llarger_field_1d);

  test_property_multi_section_pusher(lfield_1d, llarger_field_1d);
  test_coordinate_multi_section_pusher(lfield_1d, llarger_field_1d);

  // 2D tests:

  field_vd* lfield_2d = make_2d_field_space(lns);
  field_vd* llarger_field_2d = make_larger_2d_field_space(lns);

  make_names(lfield_2d);
  make_decomposition(lfield_2d);
  make_names(llarger_field_2d);

  test_property_multi_section_pusher(lfield_2d, llarger_field_2d);
  test_coordinate_multi_section_pusher(lfield_2d, llarger_field_2d);

  // Cylndrical tests.

  test_cylindrical_mono_section_pusher(lns);
  test_cylindrical_multi_section_pusher(lns);

  storage_agent lsa("test.hdf", sheaf_file::READ_WRITE, true, false);
  lsa.write_entire(lns);

  // Exit:

  return 0;
}


