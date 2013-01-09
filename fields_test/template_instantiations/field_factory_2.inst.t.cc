// $RCSfile: field_factory_2.inst.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:04 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example field_factory_2.inst.t.cc

/// @file
/// Test driver for class field_factory_2.

#include "field_factory_2.h"

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"

#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "unstructured_block.h"

#include "homogeneous_block.h"

#include "sec_at0.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_e1_uniform.h"
#include "sec_e2_uniform.h"
#include "sec_e3_uniform.h"

#include "field_vd.h"
#include "wsv_block.h"

#include "test_utils.h"
#include "std_sstream.h"

using namespace fields;

namespace
{

//==============================================================================

void
make_names_unique(string xnames[], int xnum_names)
{
  // Preconditions:

  require(unexecutable("xnum_names <= dimension of xnames"));

  // Body:

  // Make names "unique" by appending "_#" to each name.

  static int lname_suffix = -1;
  lname_suffix++;

  static ostringstream lname;

  for(int i=0; i<xnum_names; ++i)
  {
    lname.str("");
    lname << xnames[i] << "_" << lname_suffix;
    xnames[i] = lname.str();
  }

  // Postconditions:

  // Exit:

  return;
}

//==============================================================================


template<typename C, typename P, typename B>
bool
test_field_factory_2(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  //============================================================================

  // The rep "is vertex_element_dlinear" except for points which are
  // "vertex_vertex_constant".  Decide if we have a point by looking
  // at the prototype path.

  const string lproto_name = B::static_prototype_path().member_name();
  //cout << "lproto_name = " << lproto_name << endl;

  string lrep_path_string;
  if(lproto_name.find("point") == 0) // lproto starts with "point"
  { 
    lrep_path_string = "sec_rep_descriptors/vertex_vertex_constant";
  }
  else
  {
    lrep_path_string = "sec_rep_descriptors/vertex_element_dlinear";
  }

  cout << "lrep_path_string = " << lrep_path_string << endl;

  //============================================================================

  // Make names for the spaces:

  string lnames[3] = {"coordinate_section_space",
                      "property_section_space",
                      "base_space"};

  make_names_unique(lnames, 3);
  
  const string& lcoord_space_name = lnames[0];
  const string& lprop_space_name  = lnames[1];
  const string& lbase_space_name  = lnames[2];

  cout << "lcoord_space_name = " << lcoord_space_name << endl;
  cout << "lprop_space_name  = " << lprop_space_name << endl;
  cout << "lbase_space_name  = " << lbase_space_name << endl;
  poset_path lbase_space_path(lbase_space_name, "block");
  cout << "lbase_space_path  = " << lbase_space_path << endl;

  //============================================================================

  print_subheader("Testing field_factory_2<C, P, B> constructor");

  field_factory_2<C, P, B> lfactory;


  // Need base space dimension. For structured blocks B:DB works,
  // but not for others.

  //$$HACK: Use the names again:
  //  We know ("assume") that the coordinate section names are either
  //  sec_e1, sec_e2, sec_e3, sec_e1_uniform, sec_e2_uniform, or sec_e3_uniform.
  //  So get the dimension from the coordinate section type.

  print_subheader("Testing base_index_ubs(), coord_lb(), and coord_ub()");

  const string& lname_c = C::static_class_name(); 
  if(lname_c.find("sec_e1") == 0)
  {
    lfactory.base_index_ubs() = "4";
    lfactory.coord_lb() = "0";
    lfactory.coord_ub() = "3";
  }
  else if(lname_c.find("sec_e2") == 0)
  {
    lfactory.base_index_ubs() = "4 3";
    lfactory.coord_lb() = "0 0";
    lfactory.coord_ub() = "3 2";
  }
  else if(lname_c.find("sec_e3") == 0)
  {
    lfactory.base_index_ubs() = "4 3 2";
    lfactory.coord_lb() = "0 0 0";
    lfactory.coord_ub() = "3 2 1";
  }

  //============================================================================

  print_subheader("Testing coord_rep_path()");

  lfactory.coord_rep_path() = lrep_path_string;

  print_subheader("Testing coord_section_space_path()");

  lfactory.coord_section_space_path() = lcoord_space_name;

  print_subheader("Testing prop_rep_path()");

  lfactory.prop_rep_path() = lrep_path_string;

  print_subheader("Testing prop_section_space_path()");

  lfactory.prop_section_space_path() = lprop_space_name;

  // new_field (fiber_bundles_namespace &xns, const poset_path &xbase_path,
  //            const poset_path &xcoord_path, const poset_path &xprop_path)

  print_subheader("Testing new_field(...) version 3");

  field_vd* lfield1 = lfactory.new_field(xns,
                                         lbase_space_path,
                                         lcoord_space_name,
                                         lprop_space_name);

  print_subheader("Testing new_field(...) version 2");

  // new_field (fiber_bundles_namespace &xns, const poset_path &xbase_path,
  //            const char *xcoord_name, const char *xprop_name)

  field_vd* lfield2 = lfactory.new_field(xns,
                                         lbase_space_path,
                                         lcoord_space_name.c_str(),
                                         lprop_space_name.c_str());

  print_subheader("Testing new_field(...) version 1");

  // new_field (fiber_bundles_namespace &xns, const poset_path &xbase_path,
  //            const poset_path &xcoord_path, const poset_path &xprop_path)

  poset_path lcoord_path(lcoord_space_name, "coords");
  poset_path lprop_path(lprop_space_name, "props");
  field_vd* lfield3 = lfactory.new_field(xns,
                                         lbase_space_path,
                                         lcoord_path,
                                         lprop_path);

  //============================================================================

  print_subheader("Testing base_schema_path()");

  poset_path& lbase_schema_path = lfactory.base_schema_path();
  cout << "lfactory.base_schema_path() = " << lbase_schema_path << endl;

  print_subheader("Testing local_cell_prototype_path()");

  poset_path& llocal_cell_prototype_path = lfactory.local_cell_prototype_path();
  cout << "lfactory.local_cell_prototype_path() = "
       << llocal_cell_prototype_path << endl;

  print_subheader("Testing coord_lb() again");

  wsv_block<sec_vd_value_type>& lcoord_lb = lfactory.coord_lb();
  cout << "lfactory.coord_lb() = " << lcoord_lb << endl;

  print_subheader("Testing coord_ub() again");

  wsv_block<sec_vd_value_type>& lcoord_ub = lfactory.coord_ub();
  cout << "lfactory.coord_ub() = " << lcoord_ub << endl;

  print_subheader("Testing prop_lb()");

  wsv_block<sec_vd_value_type>& lprop_lb = lfactory.prop_lb();
  cout << "lfactory.prop_lb() = " << lprop_lb << endl;

  print_subheader("Testing prop_ub()");

  wsv_block<sec_vd_value_type>& lprop_ub = lfactory.prop_ub();
  cout << "lfactory.prop_ub() = " << lprop_ub << endl;


  //============================================================================

  // Call new_field with data for the existing fields.

  print_subheader("Testing new_field(...) version 3 again");

  field_vd* lfield1a = lfactory.new_field(xns,
                                         lbase_space_path,
                                         lcoord_space_name,
                                         lprop_space_name);

  print_subheader("Testing new_field(...) version 2 again");

  field_vd* lfield2a = lfactory.new_field(xns,
                                         lbase_space_path,
                                         lcoord_space_name.c_str(),
                                         lprop_space_name.c_str());

  print_subheader("Testing new_field(...) version 1 again");

  field_vd* lfield3a = lfactory.new_field(xns,
                                         lbase_space_path,
                                         lcoord_path,
                                         lprop_path);

  // Call make_base_space with data for the existing field.

  print_subheader("Testing make_base_space(...)");

  B lbase;
  make_base_space(xns,
                  lbase_space_path,
                  lfactory.base_index_ubs(),
                  llocal_cell_prototype_path,
                  lbase);

  // Call make_base_space<base_type>.  It is not called above because there are
  // specializations for all base types.

  print_subheader("Testing make_base_space<base_type>(...)");
 
  homogeneous_block* lbase_type = lbase.clone();
  make_base_space(xns,
                  lbase_space_path,
                  lfactory.base_index_ubs(),
                  llocal_cell_prototype_path,
                  *lbase_type);

  base_space_member* lbase_mbr = lbase.clone();
  make_base_space(xns,
                  lbase_space_path,
                  lfactory.base_index_ubs(),
                  llocal_cell_prototype_path,
                  *lbase_mbr);


  //============================================================================

  // Clean-up

  lbase.detach_from_state();
  lbase_type->detach_from_state();
  delete lbase_type;
  lbase_mbr->detach_from_state();
  delete lbase_mbr;

  // Postconditions:

  // Exit:

  return true;
}


}
// End unnamed namespace.

int
main(int argc, char* argv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing field_factory_2 instantiations");

  bool ltest = true;

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  print_header("Begin testing field_factory_2<sec_e1, sec_at0, point_block_1d>");
  ltest &= test_field_factory_2<sec_e1, sec_at0, point_block_1d>(lns);

  print_header("Begin testing field_factory_2<sec_e1, sec_at0, structured_block_1d>");
  ltest &= test_field_factory_2<sec_e1, sec_at0, structured_block_1d>(lns);

  print_header("Begin testing field_factory_2<sec_e1, sec_at0, unstructured_block>");
  ltest &= test_field_factory_2<sec_e1, sec_at0, unstructured_block>(lns);

  print_header("Begin testing field_factory_2<sec_e1_uniform, sec_at0, structured_block_1d>");
  ltest &= test_field_factory_2<sec_e1_uniform, sec_at0, structured_block_1d>(lns);


  print_header("Begin testing field_factory_2<sec_e2, sec_at0, point_block_2d>");
  ltest &= test_field_factory_2<sec_e2, sec_at0, point_block_2d>(lns);

  print_header("Begin testing field_factory_2<sec_e2, sec_at0, structured_block_2d>");
  ltest &= test_field_factory_2<sec_e2, sec_at0, structured_block_2d>(lns);

  print_header("Begin testing field_factory_2<sec_e2, sec_at0, unstructured_block>");
  ltest &= test_field_factory_2<sec_e2, sec_at0, unstructured_block>(lns);

  print_header("Begin testing field_factory_2<sec_e2_uniform, sec_at0, structured_block_2d>");
  ltest &= test_field_factory_2<sec_e2_uniform, sec_at0, structured_block_2d>(lns);


  print_header("Begin testing field_factory_2<sec_e3, sec_at0, point_block_3d>");
  ltest &= test_field_factory_2<sec_e3, sec_at0, point_block_3d>(lns);

  print_header("Begin testing field_factory_2<sec_e3, sec_at0, structured_block_3d>");
  ltest &= test_field_factory_2<sec_e3, sec_at0, structured_block_3d>(lns);

  print_header("Begin testing field_factory_2<sec_e3, sec_at0, unstructured_block>");
  ltest &= test_field_factory_2<sec_e3, sec_at0, unstructured_block>(lns);

  print_header("Begin testing field_factory_2<sec_e3_uniform, sec_at0, structured_block_3d>");
  ltest &= test_field_factory_2<sec_e3_uniform, sec_at0, structured_block_3d>(lns);

  //============================================================================

  print_header("Begin testing field_factory_2<sec_e1, sec_e1, point_block_1d>");
  ltest &= test_field_factory_2<sec_e1, sec_e1, point_block_1d>(lns);

  print_header("Begin testing field_factory_2<sec_e1, sec_e1, structured_block_1d>");
  ltest &= test_field_factory_2<sec_e1, sec_e1, structured_block_1d>(lns);

  print_header("Begin testing field_factory_2<sec_e1, sec_e1, unstructured_block>");
  ltest &= test_field_factory_2<sec_e1, sec_e1, unstructured_block>(lns);

  print_header("Begin testing field_factory_2<sec_e1_uniform, sec_e1, structured_block_1d>");
  ltest &= test_field_factory_2<sec_e1_uniform, sec_e1, structured_block_1d>(lns);


  print_header("Begin testing field_factory_2<sec_e2, sec_e1, point_block_2d>");
  ltest &= test_field_factory_2<sec_e2, sec_e1, point_block_2d>(lns);

  print_header("Begin testing field_factory_2<sec_e2, sec_e1, structured_block_2d>");
  ltest &= test_field_factory_2<sec_e2, sec_e1, structured_block_2d>(lns);

  print_header("Begin testing field_factory_2<sec_e2, sec_e1, unstructured_block>");
  ltest &= test_field_factory_2<sec_e2, sec_e1, unstructured_block>(lns);

  print_header("Begin testing field_factory_2<sec_e2_uniform, sec_e1, structured_block_2d>");
  ltest &= test_field_factory_2<sec_e2_uniform, sec_e1, structured_block_2d>(lns);


  print_header("Begin testing field_factory_2<sec_e3, sec_e1, point_block_3d>");
  ltest &= test_field_factory_2<sec_e3, sec_e1, point_block_3d>(lns);

  print_header("Begin testing field_factory_2<sec_e3, sec_e1, structured_block_3d>");
  ltest &= test_field_factory_2<sec_e3, sec_e1, structured_block_3d>(lns);

  print_header("Begin testing field_factory_2<sec_e3, sec_e1, unstructured_block>");
  ltest &= test_field_factory_2<sec_e3, sec_e1, unstructured_block>(lns);

  print_header("Begin testing field_factory_2<sec_e3_uniform, sec_e1, structured_block_3d>");
  ltest &= test_field_factory_2<sec_e3_uniform, sec_e1, structured_block_3d>(lns);

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_header("Begin testing field_factory_2 instantiations");

  // Postconditions:

  // Exit:

  return lresult;
}
