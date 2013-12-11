
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


/// @example db0_point_locator.t.cc

/// @file
/// test driver for db0_point_locator.

#include "block.h"
#include "fiber_bundles_namespace.h"
#include "field_factory_2.impl.h"
#include "sec_at0.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_ed_invertible.h"
#include "storage_agent.h"
#include "field_vd.h"

using namespace std;
using namespace geometry;


// namespace
// {

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
/// Creates a field space over a geomertically spherical,
/// topologically cylindrical base space.
///
field_vd* make_cylindrical_src_field_space(fiber_bundles_namespace& xns)
{
  post_information_message("Entering make_src_cylindrical_field_space");

  // Make property versus theta-phi field.

  field_factory_2<sec_e2, sec_at0, point_block_2d> lfactory1;

  lfactory1.base_index_ubs() = "25 13";

  lfactory1.coord_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory1.coord_section_space_path() =
    "test_cylindrical_src_theta_phi_section_space";
  lfactory1.coord_lb().push_back(-M_PI);
  lfactory1.coord_lb().push_back(-M_PI/3.0); // Stay away from the south pole
  lfactory1.coord_ub().push_back(M_PI);
  lfactory1.coord_ub().push_back(M_PI/3.0); // Stay away from the north pole.

  lfactory1.prop_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory1.prop_section_space_path() = "test_cylindrical_src_prop_section_space";

  field_vd* lfield1 =
    lfactory1.new_field(xns,
                        "test_cylindrical_src_base_space/mesh",
                        "theta_phi",
                        "property");

  lfield1->put_property_dofs(zero, true);

  lfield1->print_property_dofs(cout,
                               0,
                               "scalar vs theta-phi"
                               ":",
                               true,
                               true);

  field_factory_2<sec_e2, sec_e3, point_block_2d> lfactory2;


  lfactory2.coord_section_space_path() =
    "test_cylindrical_src_theta_phi_section_space";

  lfactory2.prop_rep_path() = "sec_rep_descriptors/vertex_vertex_constant";
  lfactory2.prop_section_space_path() =
    "test_cylindrical_src_surface_section_space";

  field_vd* lfield2 =
    lfactory2.new_field(xns,
                        "test_cylindrical_src_base_space/mesh",
                        "theta_phi",
                        "sphere");

  lfield2->put_property_dofs(sphere, true);

  lfield2->print_property_dofs(cout,
                               0,
                               "sphere xyz vs theta-phi"
                               ":",
                               true,
                               true);

  sec_e3* ltmp = dynamic_cast<sec_e3*>(&lfield2->property());

  field_vd* result = new field_vd(*ltmp, lfield1->property(), true);


  post_information_message("Leaving make_cylindrical_src_field_space");
  return result;
}

///
/// Test the dc3 point locator.
///
void test_dc3_point_locator(field_vd* xfield)
{
  cout << endl;
  post_information_message("Entering test_dc3_point_locator");

  // Preconditions:


  // Body:

  sec_ed_invertible& lcoords = xfield->coordinates();

  lcoords.get_read_access();
  lcoords.initialize_point_locator(false);

  chart_point_3d lpt;
  sec_vd_value_type lval[3];

  lval[0] = 1.0;
  lval[1] = 0.01;
  lval[2] = 0.01;
  lcoords.point_at_value_ua(lval, 3, lpt);
  cout << lpt << endl;

  lval[0] = -0.51;
  lval[1] = 0.01;
  lval[2] = -0.80;
  lcoords.point_at_value_ua(lval, 3, lpt);
  cout << lpt << endl;

  lval[0] = -0.51;
  lval[1] = 0.01;
  lval[2] = 0.80;
  lcoords.point_at_value_ua(lval, 3, lpt);
  cout << lpt << endl;

  // Postconditions:

  // Exit:

  post_information_message("Leaving test_dc3_point_locator");

  return;
}

//} // end unnamed namespace


///
/// Main routine.
///
int main()
{

  fiber_bundles_namespace lns("db0_point_locator.t");

  lns.get_read_write_access();

  // Spherical tests.

  field_vd* lfield = make_cylindrical_src_field_space(lns);
  test_dc3_point_locator(lfield);


  storage_agent lsa("db0_point_locator.t.hdf", sheaf_file::READ_WRITE, true, false);
  lsa.write_entire(lns);


  // Exit:

  return 0;
}


