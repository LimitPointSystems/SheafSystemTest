// $RCSfile: vtk_unstructured_grid_builder.t.cc,v $ $Revision: 1.12 $ $Date: 2012/03/01 00:41:45 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example viewer/common/vtk_unstructured_grid_builder.t.cc
/// Test driver for class vtk_unstructured_grid_builder.

#include "assert_contract.h"
#include "base_space_factory.h"
#include "base_space_member.h"
#include "base_space_poset.h"
#include "block.impl.h"
#include "fiber_bundles_namespace.h"
#include "preorder_iterator.h"
#include "storage_agent.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_st2_e3.h"
#include "sec_rep_space.h"
#include "sec_stp_space.h"
#include "section_space_factory.h"
#include "tern.h"
#include "unstructured_block.h"
#include "wsv_block.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkConeSource.h"
#include "vtkDoubleArray.h"
#include "vtkDataSetMapper.h"
#include "vtkLookupTable.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtk_unstructured_grid_builder.h"
#include "vtkUnstructuredGrid.h"

#include "section_space_schema_poset.h"

//#define DIAGNOSTIC_OUTPUT

using namespace tool;

namespace
{

///
/// tests vtk_unstructured_grid_builder on xcoord and xprop.
///
void test_grid_builder(sec_vd& xcoord, sec_vd& xprop, bool xstart_viewer)
{
  // Preconditions:

  require(xcoord.is_attached());
  require(xprop.is_attached());

  // Body:

  xcoord.get_read_access();
  xprop.get_read_access();

#ifdef DIAGNOSTIC_OUTPUT
  cout << xcoord.schema().host()->base_space() << endl;
  cout << *xcoord.host() << endl;
  cout << *xprop.host() << endl;
#endif

  // Create the vtk grid.

  vtk_unstructured_grid_builder lbuilder(*xcoord.name_space());
  vtkUnstructuredGrid* lgrid = lbuilder.build(xcoord, xprop);

  // Print the vtk grid.

  vtkIndent lindent;
  lgrid->PrintSelf(cout, lindent);

  if(xstart_viewer)
  {

    // Create the vtk mapper.

    vtkDataSetMapper* lgrid_mapper = vtkDataSetMapper::New();
    lgrid_mapper->SetInput(lgrid);

    // Have to tell the mapper what the extrema of the data are,
    // otherwise it appears to use the default range of the lookup
    // table, which is [0, 1].

    at0_lite llb, lub;
    extrema(xprop, llb, lub, false);
    lgrid_mapper->SetScalarRange(llb, lub);

    // Create the grid actor.

    vtkActor* lgrid_actor = vtkActor::New();
    lgrid_actor->SetMapper(lgrid_mapper);

    // Create the vtk renderer.

    vtkRenderer* lren = vtkRenderer::New();
    lren->AddActor(lgrid_actor);
  
    // Create the render window.

    vtkRenderWindow *lren_win = vtkRenderWindow::New();
    lren_win->AddRenderer( lren );
    lren_win->SetSize( 512, 512 );

    // Create and initialize the window interactor.
    // Start() starts the interaction event loop, 
    // which continues until the user types "e".

    vtkRenderWindowInteractor* linteractor = vtkRenderWindowInteractor::New();
    linteractor->SetRenderWindow(lren_win);

    linteractor->Initialize();
    linteractor->Start();
  }
  

  // Clean up.

  xcoord.release_access();
  xprop.release_access();

  // Postconditions:


  // Exit:

  return;
}

///
/// tests vtk_unstructured_grid_builder on xcoord and xprop.
///
void test_grid_builder(sec_vd& xcoord, block<sec_vd*>& xprops)
{
  // Preconditions:

  require(xcoord.is_attached());
  require_for_all(i, 0, xprops.ct(), xprops[i]->is_attached());

  // Body:

  xcoord.get_read_access();
  for(int i=0; i< xprops.ct(); ++i)
  {
    xprops[i]->get_read_access();
  }


  vtk_unstructured_grid_builder lbuilder(*xcoord.name_space());
  vtkUnstructuredGrid* lgrid = lbuilder.build(xcoord, xprops);

  vtkIndent lindent;
  lgrid->PrintSelf(cout, lindent);

  xcoord.release_access();
  for(int i=0; i< xprops.ct(); ++i)
  {
    xprops[i]->release_access();
  }

  // Postconditions:


  // Exit:

  return;
}

///
/// Create a base space and coordinate section.
///
void create_base_space(fiber_bundles_namespace& xns, sec_e3& xcoords)
{
  size_type lxedge_ct = 3;
  size_type lyedge_ct = 2;
  size_type lzedge_ct = 1;

  base_space_poset& lbase_poset = xns.new_base_space<structured_block_3d>("base_space");
  structured_block_3d lbase(&lbase_poset, lxedge_ct, lyedge_ct, lzedge_ct, true);
  lbase.put_name("structured_block_3d", true, true);

  sec_e3::host_type& lcoord_space = xns.new_section_space<sec_e3>("coord_space", lbase.path());
  xcoords.new_jim_state(&lcoord_space);
  xcoords.put_name("coords", true, true);

  // Set the dofs for the coordinates.

  xcoords.get_read_write_access();
  
  size_type lxnode_ct = lxedge_ct + 1;
  size_type lynode_ct = lyedge_ct + 1;
  size_type lznode_ct = lzedge_ct + 1;

  e3_lite lcoord_fiber;
  int n=0;
  for(int i=0; i<lxnode_ct; ++i)
  {
    lcoord_fiber[0] = i;
    for(int j=0; j<lynode_ct; ++j)
    {
      lcoord_fiber[1] = j;
      for(int k=0; k<lznode_ct; ++k)
      {
	lcoord_fiber[2] = k;
	xcoords.put_fiber(n, lcoord_fiber);
	n++;
      }
    }
  }  

  xcoords.release_access();

  lbase.detach_from_state();

  return;
}

///
/// Test vtk_grid_builder with scalar field on 3d structured mesh.
///
void test_scalar_field_3d_structured(fiber_bundles_namespace& xns,
				     sec_e3& xcoords,
				     sec_at0& xprop,
				     bool xstart_viewer = false,
                                     const poset_path& xproperty_rep_path =
				     "sec_rep_descriptors/vertex_element_dlinear")
{

  string ltest_name =
    "test_scalar_field_3d_structured_" + xproperty_rep_path.member_name();

  xcoords.get_read_access();
  structured_block_3d lbase(xcoords.schema().base_space());  

  sec_at0::host_type& lprop_space = xns.new_section_space<sec_at0>(ltest_name + "_prop_space", lbase.path());
  xprop.new_jim_state(&lprop_space);
  xprop.put_name("prop", true, true);

  // Set the dofs for the property..

  xcoords.get_read_access();
  xprop.get_read_write_access();
  
  size_type lxnode_ct = lbase.i_size() + 1;
  size_type lynode_ct = lbase.j_size() + 1;
  size_type lznode_ct = lbase.k_size() + 1;

  e3_lite lcoord_fiber;
  at0_lite lprop_fiber;
  int n=0;
  for(int i=0; i<lxnode_ct; ++i)
  {
    for(int j=0; j<lynode_ct; ++j)
    {
      for(int k=0; k<lznode_ct; ++k)
      {
	xcoords.get_fiber(n, lcoord_fiber);
	lprop_fiber = length(lcoord_fiber);
	cout << "prop fiber: " << lprop_fiber << endl;
	xprop.put_fiber(n, lprop_fiber);
	n++;
      }
    }
  }

  cout << lprop_space << endl;
  

  xcoords.release_access();
  xprop.release_access();

  test_grid_builder(xcoords, xprop, xstart_viewer);

  lbase.detach_from_state();

  return;
}

///
/// Test vtk_grid_builder with vector field on 3d structured mesh.
///
void test_vector_field_3d_structured(fiber_bundles_namespace& xns,
				     sec_e3& xcoords,
				     sec_e3& xprop,
                                     const poset_path& xproperty_rep_path =
				     "sec_rep_descriptors/vertex_element_dlinear")
{

  string ltest_name =
    "test_vector_field_3d_structured_" + xproperty_rep_path.member_name();

  xcoords.get_read_access();
  structured_block_3d lbase(xcoords.schema().base_space());  

  sec_e3::host_type& lprop_space = xns.new_section_space<sec_e3>(ltest_name + "_prop_space", lbase.path());
  xprop.new_jim_state(&lprop_space);
  xprop.put_name("prop", true, true);

  // Set the dofs for the property..

  xcoords.get_read_access();
  xprop.get_read_write_access();
  
  size_type lxnode_ct = lbase.i_size() + 1;
  size_type lynode_ct = lbase.j_size() + 1;
  size_type lznode_ct = lbase.k_size() + 1;

  e3_lite lcoord_fiber;
  e3_lite lprop_fiber;
  int n=0;
  for(int i=0; i<lxnode_ct; ++i)
  {
    for(int j=0; j<lynode_ct; ++j)
    {
      for(int k=0; k<lznode_ct; ++k)
      {
	xcoords.get_fiber(n, lcoord_fiber);
	normalize(lcoord_fiber, lprop_fiber);
	cout << "prop fiber: " << lprop_fiber << endl;
	xprop.put_fiber(n, lprop_fiber);
	n++;
      }
    }
  }

  cout << lprop_space << endl;
  

  xcoords.release_access();
  xprop.release_access();

  test_grid_builder(xcoords, xprop, false);

  lbase.detach_from_state();

  return;
}

///
/// Test vtk_grid_builder with vector field on 3d structured mesh.
///
void test_tensor_field_3d_structured(fiber_bundles_namespace& xns,
				     sec_e3& xcoords,
				     sec_st2_e3& xprop,
                                     const poset_path& xproperty_rep_path =
				     "sec_rep_descriptors/vertex_element_dlinear")
{

  string ltest_name =
    "test_tensor_field_3d_structured_" + xproperty_rep_path.member_name();

  xcoords.get_read_access();
  structured_block_3d lbase(xcoords.schema().base_space());  

  sec_st2_e3::host_type& lprop_space = xns.new_section_space<sec_st2_e3>(ltest_name + "_prop_space", lbase.path());
  xprop.new_jim_state(&lprop_space);
  xprop.put_name("prop", true, true);

  // Set the dofs for the property.
  // Just set all the dofs to 0; don't have any better test.

  assign(xprop, 0.0, true);

  cout << lprop_space << endl;

  test_grid_builder(xcoords, xprop, false);

  lbase.detach_from_state();

  return;
}

  // ///
  // /// Test vtk_grid_builder with multiple property fields on 3d structured mesh.
  // ///
  // void test_multi_prop_3d_structured(fiber_bundles_namespace& xns,
  //                                    const poset_path& xproperty_rep_path =
  //                                      "sec_rep_descriptors/vertex_element_dlinear")
  // {

  //   string ltest_name =
  //     "test_multi_prop_3d_structured_" + xproperty_rep_path.member_name();


  //   base_space_factory<structured_block_3d> lbase_factory;
  //   lbase_factory.index_ubs = "3 2 1";
  //   poset_path lbase_path(ltest_name + "_base_space", "structured_block_3d");
  //   structured_block_3d* lbase = lbase_factory.new_base(xns, lbase_path);

  //   section_space_factory<sec_e3> lcoord_factory;
  //   lcoord_factory.base_path = lbase_path;
  //   lcoord_factory.lb = "0 0 0";
  //   lcoord_factory.ub = "3 2 1";
  //   poset_path lcoord_path(ltest_name + "_coord_space", "coords");
  //   sec_e3* lcoords = lcoord_factory.new_section(xns, lcoord_path);

  //   section_space_factory<sec_at0> lscalar_prop_factory;
  //   lscalar_prop_factory.base_path = lbase_path;
  //   lscalar_prop_factory.rep_path = xproperty_rep_path;
  //   poset_path lscalar_prop_path(ltest_name + "_scalar_prop_space", "scalar_prop");
  //   sec_at0* lscalar_prop = lscalar_prop_factory.new_section(xns, lscalar_prop_path);

  //   sec_at0::fiber_type::volatile_type lfiber = 0.0;

  //   lscalar_prop->get_read_write_access();
  //   *lscalar_prop = lfiber;
  //   lscalar_prop->release_access();

  //   section_space_factory<sec_e3> lvector_prop_factory;
  //   lvector_prop_factory.base_path = lbase_path;
  //   lvector_prop_factory.rep_path = xproperty_rep_path;
  //   poset_path lvector_prop_path(ltest_name + "_vector_prop_space", "vector_prop");
  //   sec_e3* lvector_prop = lvector_prop_factory.new_section(xns, lvector_prop_path);

  //   lvector_prop->get_read_write_access();
  //   //lvector_prop->zero_sa();
  //   lvector_prop->release_access();

  //   section_space_factory<sec_st2_e3> ltensor_prop_factory;
  //   ltensor_prop_factory.base_path = lbase_path;
  //   ltensor_prop_factory.rep_path = xproperty_rep_path;
  //   poset_path ltensor_prop_path(ltest_name + "_tensor_prop_space", "tensor_prop");
  //   sec_st2_e3* ltensor_prop = ltensor_prop_factory.new_section(xns, ltensor_prop_path);

  //   ltensor_prop->get_read_write_access();
  //   //ltensor_prop->zero_sa();
  //   ltensor_prop->release_access();

  //   block<sec_vd*> lprops(3);
  //   lprops.push_back(lscalar_prop);
  //   lprops.push_back(lvector_prop);
  //   lprops.push_back(ltensor_prop);


  //   test_grid_builder(*lcoords, lprops);

  //   return;
  // }


}; // End unnamed namespace.

int main(int argc, char* argv[])
{
  bool lstart_viewer = (argc > 1);
  
  fiber_bundles_namespace lns("vtk_unstructured_grid_builder.t");
  lns.get_read_write_access();

  sec_e3 lcoords;
  create_base_space(lns, lcoords);

  sec_at0 lscalar_prop;
  test_scalar_field_3d_structured(lns, lcoords, lscalar_prop, lstart_viewer);
  //   test_scalar_field_3d_structured(lns, "sec_rep_descriptors/element_element_constant");

  sec_e3 lvector_prop;
  test_vector_field_3d_structured(lns, lcoords, lvector_prop);
  //   test_vector_field_3d_structured(lns, "sec_rep_descriptors/element_element_constant");

  sec_st2_e3 ltensor_prop;
  test_tensor_field_3d_structured(lns, lcoords, ltensor_prop);
  //   test_tensor_field_3d_structured(lns, "sec_rep_descriptors/element_element_constant");

  //   test_multi_prop_3d_structured(lns);


  ltensor_prop.detach_from_state();
  lvector_prop.detach_from_state();
  lscalar_prop.detach_from_state();
  lcoords.detach_from_state();
  

  return 0;
}
