

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example vis_iterator.t.cc
/// Simple 2 hex test driver for the cells subposet.

#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "sec_rep_descriptor.h"
#include "section_space_schema_poset.h"
#include "std_sstream.h"
#include "std_string.h"
#include "storage_agent.h"
#include "subposet.h"
#include "subposet_member_iterator.h"
#include "unstructured_block.h"
#include "vtk_unstructured_grid_builder.h"

#include "vtkUnstructuredGrid.h"
#include "vtkUnstructuredGridWriter.h"

#define DIAGNOSTIC_OUTPUT

using namespace tool;

namespace
{

void
make_names(base_space_poset& xbase_space, int xd, const string& xroot)
{
  // Preconditions:

  // Body:

  // Create names for all members of subposet d_cells(xd).
  // Name are of the form "xroot_#" where "#" is sequential
  // from 0 to d_cells(xd).ct()-1.

  base_space_member lmbr;

  subposet& lsp = xbase_space.d_cells(xd);
  subposet_member_iterator* litr = lsp.member_iterator();
  size_type i = 0;
  while(!litr->is_done())
  {
    lmbr.attach_to_state(&xbase_space, litr->index());

    stringstream lstr;
    lstr << xroot << "_" << i;
    lmbr.put_name(lstr.str(), true, true);
    i++;

    litr->next();
  }

  lmbr.detach_from_state();

  delete litr;

  // Postconditions:

  ensure(unexecutable("All members of .d_cells(xd) have names"));

  // Exit:

  return;
}

void
print_cells_subposet(const base_space_poset& xbase_space)
{
  // Preconditions:

  require(xbase_space.state_is_read_accessible());

  // Body:

  // Print the "cells" subposet.

  cout << endl;
  cout << "Cells subposet members:" << endl;
  cout << endl;

  base_space_member lmbr;
  const subposet& lcells_sp = xbase_space.cells();
  subposet_member_iterator* litr = lcells_sp.member_iterator();
  while(!litr->is_done())
  {
    lmbr.attach_to_state(&xbase_space, litr->index());
    cout << setw(8) << litr->index().internal_pod()
         << "  :  " << lmbr.name() << endl;
    litr->next();
  }

  cout << endl;

  lmbr.detach_from_state();

  delete litr;

  // Postconditions:

  // Exit:

  return;
}

base_space_poset*
make_base_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create a base space.

  const string lbase_name("the_base_space");

  base_space_poset* lbase_space =
    &xns.new_base_space<unstructured_block>(lbase_name, "", "", 3, true);

  lbase_space->get_read_write_access();

  // Create an unstructured block with 2 hexes.

  const size_type lnode_id_ct = 16;
  const pod_index_type lnode_ids[16] =
  {
    0, 1, 4, 3, 6, 7, 10,  9,
    1, 2, 5, 4, 7, 8, 11, 10 
  };

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "hex_complex");
                         //"hex_nodes");

  unstructured_block lblock(lbase_space,
                            lproto_path,
                            lnode_ids,
                            lnode_id_ct,
                            true);

  lblock.put_name("hex_block", true, false);

  // Give members names.

  make_names(*lbase_space, 3, "hex");
  make_names(*lbase_space, 2, "quad_face");
  make_names(*lbase_space, 1, "edge");
  make_names(*lbase_space, 0, "vertex");

  lblock.detach_from_state();

  // Postconditions:

  ensure(lbase_space->is_attached());

  // Exit:

  return lbase_space;
}

sec_at1_space*
make_coordinates_section(fiber_bundles_namespace& xns,
                         const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create the coordinates section space.

  poset_path lcoords_path = "coordinates_space";
  poset_path lrep_path = "sec_rep_descriptors/vertex_cells_dlinear";

  sec_at1_space* lcoords_space = 
    &(xns.new_section_space<sec_e3>(lcoords_path, xbase_path, lrep_path, true));

  lcoords_space->get_read_write_access();

  // Create a coordinates section.

  //sec_e3 lcoords(lcoords_space);
  base_space_member lbase_mbr(&xns, xbase_path);

  sec_e3 lcoords(lcoords_space, lbase_mbr);

  lcoords.put_name("coordinates", true, false);

  // Add the coordinates to the coordinates section.
 
  const int lcoords_ct = 36;
  const double lcoords_array[36] =
  {
    0, 0, 0, //  vertex  0
    1, 0, 0, //  vertex  1
    2, 0, 0, //  vertex  2
    0, 1, 0, //  vertex  3
    1, 1, 0, //  vertex  4
    2, 1, 0, //  vertex  5
    0, 0, 1, //  vertex  6
    1, 0, 1, //  vertex  7
    2, 0, 1, //  vertex  8
    0, 1, 1, //  vertex  9
    1, 1, 1, //  vertex 10
    2, 1, 1  //  vertex 11
  };

  e3_lite lfiber;
  size_type i = 0;
  index_space_iterator* ldisc_itr =
    lcoords.schema().discretization_id_space().iterator(true);
  while(!ldisc_itr->is_done())
  {
    double lx = lcoords_array[i++];
    double ly = lcoords_array[i++];
    double lz = lcoords_array[i++];
    lfiber.put_components(lx, ly, lz);

    lcoords.put_fiber(ldisc_itr->id(), lfiber);
    ldisc_itr->next();
  }

  delete ldisc_itr;

  lbase_mbr.detach_from_state();
  lcoords.detach_from_state();

  // Postconditions:

  ensure(lcoords_space->is_attached());

  // Exit:

  return lcoords_space;
}

sec_at0_space*
make_dlinear_scalars_section(fiber_bundles_namespace& xns,
                             const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create a scalar section space with "vertex_cells_dlinear" rep. 

  poset_path lscalars_path = "dlinear_space";
  poset_path lrep_path = "sec_rep_descriptors/vertex_cells_dlinear";

  sec_at0_space* lscalars_space = 
    &(xns.new_section_space<sec_at0>(lscalars_path, xbase_path,
                                     lrep_path, true));

  lscalars_space->get_read_write_access();

  const double lscalars_array[12] =
    {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111};

  base_space_member lbase_mbr;
  index_space_iterator* ldisc_itr;
  size_type i;
  at0_lite lfiber;

  //============================================================================

  // Create a scalars section.

  //sec_at0 lscalars(lscalars_space);

  lbase_mbr.attach_to_state(&xns, "the_base_space/hex_block", false);

  sec_at0 lscalars_0(lscalars_space, lbase_mbr);
  lscalars_0.put_name("scalars_0", true, false);


  // Add the dofs to the scalars section.
 
  i = 0;
  ldisc_itr = lscalars_0.schema().discretization_id_space().iterator(true);
  while(!ldisc_itr->is_done())
  {
    double lx = lscalars_array[i++];
    lfiber.put_component(lx);
    lscalars_0.put_fiber(ldisc_itr->id(), lfiber);
    ldisc_itr->next();
  }

  delete ldisc_itr;

  lscalars_0.detach_from_state();

  //============================================================================

  // Create a scalars section only on the boundary.

  lbase_mbr.attach_to_state(&xns, "the_base_space/__bdy_of___block_0", false);

  sec_at0 lscalars_1(lscalars_space, lbase_mbr);
  lscalars_1.put_name("scalars_1", true, false);

  // Add the dofs to the scalars section.
 
  i = 0;
  ldisc_itr = lscalars_1.schema().discretization_id_space().iterator(true);
  while(!ldisc_itr->is_done())
  {
    double lx = lscalars_array[i++];
    lfiber.put_component(lx);
    lscalars_1.put_fiber(ldisc_itr->id(), lfiber);
    ldisc_itr->next();
  }

  delete ldisc_itr;

  lscalars_1.detach_from_state();

  //============================================================================

  // Create a scalars section only on the first hexahedron.

  lbase_mbr.attach_to_state(&xns, "the_base_space/hex_0", false);

  sec_at0 lscalars_2(lscalars_space, lbase_mbr);
  lscalars_2.put_name("scalars_2", true, false);

  // Add the dofs to the scalars section.
 
  i = 0;
  ldisc_itr = lscalars_2.schema().discretization_id_space().iterator(true);
  while(!ldisc_itr->is_done())
  {
    double lx = lscalars_array[i++];
    lfiber.put_component(lx);
    lscalars_2.put_fiber(ldisc_itr->id(), lfiber);
    ldisc_itr->next();
  }

  delete ldisc_itr;

  lscalars_2.detach_from_state();

  //============================================================================

  lbase_mbr.detach_from_state();
  lscalars_space->release_access();

  // Postconditions:

  ensure(lscalars_space->is_attached());

  // Exit:

  return lscalars_space;
}

sec_at0_space*
make_constant_scalars_section(fiber_bundles_namespace& xns,
                              const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create a scalar section space with "element_element_constant" rep. 

  poset_path lscalars_path = "constant_space";
  poset_path lrep_path = "sec_rep_descriptors/element_element_constant";

  sec_at0_space* lscalars_space = 
    &(xns.new_section_space<sec_at0>(lscalars_path, xbase_path,
                                     lrep_path, true));

  lscalars_space->get_read_write_access();

  //============================================================================

  // Create a scalars section.

  //sec_at0 lscalars(lscalars_space);

  base_space_member lbase_mbr(&xns, xbase_path);

  sec_at0 lscalars(lscalars_space, lbase_mbr);
  lscalars.put_name("scalars", true, false);

  // Add the dofs to the scalars section.
 
  const double lscalars_array[2] = {100, 200};

  at0_lite lfiber;
  size_type i = 0;
  index_space_iterator* ldisc_itr =
    lscalars.schema().discretization_id_space().iterator(true);
  while(!ldisc_itr->is_done())
  {
    lfiber.put_component(lscalars_array[i++]);
    lscalars.put_fiber(ldisc_itr->id(), lfiber);
    ldisc_itr->next();
  }

  delete ldisc_itr;

  lbase_mbr.detach_from_state();
  lscalars.detach_from_state();

  lscalars_space->release_access();

  // Postconditions:

  ensure(lscalars_space->is_attached());

  // Exit:

  return lscalars_space;
}

void
make_test(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  //============================================================================

  // Create a base space.

  base_space_poset* lbase_space = make_base_space(xns);

  //============================================================================

  // Create the coordinates section space.

  //poset_path lbase_path = lbase_space->top().path();
  //poset_path lbase_path("the_base_space/__bdy_of___block_0");
  poset_path lbase_path("the_base_space/hex_block");

  sec_at1_space* lcoords_space = make_coordinates_section(xns, lbase_path);

  //============================================================================

   // Create a scalar section space with "vertex_cells_dlinear" rep..

  sec_at0_space* lspace_0 = make_dlinear_scalars_section(xns, lbase_path);

  //============================================================================

  // Create a scalar section space with "element_element_constant" rep..

  sec_at0_space* lspace_1 = make_constant_scalars_section(xns, lbase_path);

  //============================================================================

#ifdef DIAGNOSTIC_OUTPUT
  print_cells_subposet(*lbase_space);
  cout << *lbase_space << endl;
  cout << *lcoords_space << endl;
  cout << *lspace_0 << endl;
  cout << *lspace_1 << endl;
#endif

  // Postconditions:

  // Exit:

  return;
}

///
/// Dumps the vtkUnstructuredGrid *xgrid to stream xos.
/// This dumps what would be normally written to a vtk file.
///
void
dump_vtk_grid_data(vtkUnstructuredGrid* xgrid, ostream& xos)
{
  // Preconditions:

  require(xgrid != 0);

  // Body:

  xos << endl;
  xos << "############################################################" << endl;
  xos << endl;

  // vtkIndent lindent;
  xgrid->Print(xos);

  xos << endl;
  xos << "############################################################" << endl;
  xos << endl;

  vtkUnstructuredGridWriter* writer = vtkUnstructuredGridWriter::New();
  writer->SetInput(xgrid);

  //writer->SetFileName("vis_iterator.t.vtk");
  writer->WriteToOutputStringOn();

  writer->Write();

  xos << writer->GetOutputString() << endl;

  writer->Delete();

  xos << endl;
  xos << "############################################################" << endl;
  xos << endl;

  // Postconditions:

  // Exit:

  return; 
}

///
/// tests vtk_unstructured_grid_builder on xcoord and xprop.
///
void test_grid_builder(sec_vd& xcoord, sec_vd& xprop)
{
  // Preconditions:

  require(xcoord.is_attached());
  require(xprop.is_attached());

  // Body:

  xcoord.get_read_access();
  xprop.get_read_access();

  vtk_unstructured_grid_builder lbuilder(*xcoord.name_space());
  vtkUnstructuredGrid* lgrid = lbuilder.build(xcoord, xprop);

  dump_vtk_grid_data(lgrid, cout);

  xcoord.release_access();
  xprop.release_access();

  // Postconditions:

  // Exit:

  return;
}

///
/// tests vtk_unstructured_grid_builder on xcoord.
///
void test_grid_builder(sec_vd& xcoord)
{
  // Preconditions:

  require(xcoord.is_attached());

  // Body:

  xcoord.get_read_access();

  vtk_unstructured_grid_builder lbuilder(*xcoord.name_space());
  vtkUnstructuredGrid* lgrid = lbuilder.build(xcoord);

  dump_vtk_grid_data(lgrid, cout);

  xcoord.release_access();

  // Postconditions:

  // Exit:

  return;
}

void
test(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_accessible());

  // Body:

  sec_e3 lcoord(&xns, "coordinates_space/coordinates");

  // Test visualization_iterator_1_1:

  sec_at0 lprop_0(&xns, "dlinear_space/scalars_0"); // hex_block.
  //sec_at0 lprop(&xns, "dlinear_space/scalars_1"); // __bdy_of___block_0
  //                                                //     == boundary.
  //sec_at0 lprop(&xns, "dlinear_space/scalars_2"); // hex_0.

  test_grid_builder(lcoord, lprop_0);

  // Test visualization_iterator_1_3:

  sec_at0 lprop_1(&xns, "constant_space/scalars");

  test_grid_builder(lcoord, lprop_1);

  //test_grid_builder(lcoord);

  // Cleanup:

  lprop_0.detach_from_state();
  lprop_1.detach_from_state();
  lcoord.detach_from_state();

  // Postconditions:

  // Exit:

  return;

}


} // end namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  const string lfilename = filename_from_cmdline(xargv[0]);

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  make_test(lns);

#ifdef DIAGNOSTIC_OUTPUT
  test(lns);
#endif

  //cout << lns << endl;

  storage_agent sa(lfilename + ".hdf");
  sa.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
