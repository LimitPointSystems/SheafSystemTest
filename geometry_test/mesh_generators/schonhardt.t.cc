  

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example schonhardt.t.cc
/// Simple test driver for the tetgen mesh generator.
/// Needs the addition of Steiner points to tetrahedralize.

// In geometry, the Schönhardt polyhedron is the simplest
// non-convex polyhedron that cannot be triangulated into
// tetrahedra without adding new vertices. It is named
// after German mathematician Erich Schönhardt, who first
// described it in 1928.

// It is combinatorially an octahedron, twisted so that three
// of its dihedrals are concave. Each vertex is connected by
// edges to four others, but the diagonal to the remaining
// vertex always passes outside the polyhedron, so there is
// no way to place a diagonal inside partitioning the shape
// into tetrahedra.

// Running tetgen with switch "p" creates a tetrahedral mesh
// with 3 Steiner points added to the surface and none interior.
// With switches "pY" 1 Steiner point is added to the interior
// (actually at the centroid) and none on the surface.
 
#include "fiber_bundles_namespace.h"
#include "geometry.h"
#include "index_space_iterator.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "sec_rep_descriptor.h"
#include "section_space_schema_poset.h"
#include "std_cmath.h"
#include "std_fstream.h"
#include "std_sstream.h"
#include "std_string.h"
#include "storage_agent.h"
#include "subposet.h"
#include "subposet_member_iterator.h"
#include "tetgen_generator.h"
#include "unstructured_block.h"
#include "unstructured_block_builder.h"

//#define DIAGNOSTIC_OUTPUT

using namespace geometry;

namespace
{

//$$SCRIBBLE: Except for the following two functions, several test cases
//            have the same code.  It might make sense to put them into
//            a common class or stand alone functions file.

//==============================================================================

void
get_connectivities(vector<mesh_generator::pod_type>& xconns)
{
  const size_type lnode_id_ct = 24;
  const pod_index_type lnode_ids[24] =
  {
    0, 1, 5,
    0, 5, 4,
    0, 4, 2,
    0, 2, 1,
    3, 1, 2,
    3, 2, 4,
    3, 4, 5,
    3, 5, 1
  };

  xconns.assign(lnode_ids, lnode_ids+lnode_id_ct);
}

void
get_coordinates(vector<e3_lite>& xcoords)
{
  static const double C0 = sqrt(1.0 + sqrt(3.0)) / 2.0;
  static const double C1 = sqrt(3.0) / 2.0;

  const int lcoords_ct = 6;
  const e3_lite lcoords_array[6] =
  {
    e3_lite( 0.0,  1.0,  C0), //  vertex  0
    e3_lite(  C1, -0.5,  C0), //  vertex  1
    e3_lite( -C1, -0.5,  C0), //  vertex  2
    e3_lite(-1.0,  0.0, -C0), //  vertex  3
    e3_lite( 0.5,   C1, -C0), //  vertex  4
    e3_lite( 0.5,  -C1, -C0)  //  vertex  5
  };

  xcoords.assign(lcoords_array, lcoords_array+lcoords_ct);
}

//==============================================================================
//==============================================================================

// Making these paths global so they are all in one place and
// not scattered around.

static const poset_path lrep_path = tetgen_generator::rep_path();

static const string lproto_poset_name =
  unstructured_block::prototypes_poset_name();

static const poset_path ltetra_proto_path =
  tetgen_generator::tetra_proto_path();
                             
static const poset_path ltriangle_proto_path(lproto_poset_name,
                                             "triangle_complex");

static const poset_path lsurface_base_space_path("surface_base_space",
                                                 "surface_triangles_block");

static const poset_path lsurface_coordinates_path("surface_coordinates_space",
                                                  "surface_coordinates");

//==============================================================================

// Create a file for viewing with paraview or other vtk viewer.
// The file created is a "legacy" vtk file as opposed to the newer
// xml based file formats.

// If parameter xis_tetra is true, we assume that tetrahedrons are being
// passed in xconns; otherwise we assume triangles.

void
create_vtk_file(const vector<e3_lite>& xcoords,
                const vector<mesh_generator::pod_type>& xconns,
                const string& xfilename,
                bool xis_tetra = true)
{
  // Preconditions:

  require(xis_tetra ? (xcoords.size() >= 4) : (xcoords.size() >= 3));
  require(xis_tetra ? (xconns.size() >= 4) : (xconns.size() >= 3));
  require(xis_tetra ? (xconns.size()%4 == 0) : (xconns.size()%3 == 0));
  require(!xfilename.empty());

  // Body:

  ofstream lofs(xfilename.c_str());
  if(!lofs.is_open())
  {
    cerr << "Warning: Could not open file " << xfilename << endl;
  }
  else
  {
    //==========================================================================

    lofs << "# vtk DataFile Version 2.0" << endl;
    lofs << "Unstructured Grid Example" << endl;
    lofs << "ASCII" << endl;
    lofs << endl;
    lofs << "DATASET UNSTRUCTURED_GRID" << endl;

    //==========================================================================

    size_type lnum_pts = xcoords.size();

    lofs << "POINTS " << lnum_pts << " double" << endl;

    e3_lite lfiber;
    for(size_type i=0; i<lnum_pts; ++i)
    {
      lfiber = xcoords[i];
      lofs << setw(12) << lfiber[0]
           << setw(12) << lfiber[1]
           << setw(12) << lfiber[2] << endl;
    }

    //==========================================================================

    int lnodes_per_element = xis_tetra ? 4 : 3;
    int lvtk_cell_type =  xis_tetra ? 10 : 5;

    size_type lnum_cells = xconns.size()/lnodes_per_element;

    lofs << "CELLS " << lnum_cells << " "
         << lnum_cells*(lnodes_per_element+1) << endl;

    for(size_type i=0, j=0; i<lnum_cells; ++i)
    {
      lofs << lnodes_per_element;
      for(size_type k = 0; k<lnodes_per_element; ++k)
      {
        lofs << setw(8) << xconns[j++];
      }
      lofs << endl;
    }

    lofs << "CELL_TYPES " << lnum_cells << endl;
    for(size_type i=0; i<lnum_cells; ++i)
    {
      lofs << lvtk_cell_type << endl;
    }

    //==========================================================================

    lofs.close();
  }

  // Postconditions:

  // Exit:

}

// This function is only used for debugging.  It just prints
// the members ot the cells (not d_cells) subposet.

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
    cout << setw(8) << litr->index().hub_pod()
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
create_base_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create a base space.

  const string& lbase_name = lsurface_base_space_path.poset_name();
  const string& lmbr_name  = lsurface_base_space_path.member_name();

  base_space_poset* lbase_space =
    &xns.new_base_space<unstructured_block>(lbase_name, "", "", 3, true);

  lbase_space->get_read_write_access();

  // Create the surface connectivities.

  vector<mesh_generator::pod_type> lconns;
  get_connectivities(lconns);

  //unstructured_block_builder::put_name_mode(true);

  unstructured_block lblock(lbase_space,
                            ltriangle_proto_path,
                            &lconns[0],
                            lconns.size(),
                            true);

  lblock.put_name(lmbr_name, true, false);

  // Give members names.

  tetgen_generator::make_names(*lbase_space, 2, "face");
  tetgen_generator::make_names(*lbase_space, 1, "edge");
  tetgen_generator::make_names(*lbase_space, 0, "vertex");

  lblock.detach_from_state();

  // Postconditions:

  ensure(lbase_space->is_attached());

  // Exit:

  return lbase_space;
}

sec_at1_space*
create_coordinates_section(fiber_bundles_namespace& xns,
                           const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create the coordinates section space.

  const string& lspace_name = lsurface_coordinates_path.poset_name();
  const string& lmbr_name   = lsurface_coordinates_path.member_name();

  sec_at1_space* lcoords_space = 
    &(xns.new_section_space<sec_e3>(lspace_name, xbase_path, lrep_path, true));

  lcoords_space->get_read_write_access();

  // Create a coordinates section.

  base_space_member lbase_mbr(&xns, xbase_path);

  sec_e3 lcoords_mbr(lcoords_space, lbase_mbr);

  lcoords_mbr.put_name(lmbr_name, true, false);

  // Add the coordinates to the coordinates section.

  vector<e3_lite> lcoords;
  get_coordinates(lcoords);
 
  index_space_iterator& ldisc_itr =
    lcoords_mbr.schema().discretization_id_space().get_iterator();

  size_type i = 0;
  while(!ldisc_itr.is_done())
  {
    lcoords_mbr.put_fiber(ldisc_itr.pod(), lcoords[i++]);
    ldisc_itr.next();
  }

  lcoords_mbr.schema().discretization_id_space().release_iterator(ldisc_itr);

  lbase_mbr.detach_from_state();
  lcoords_mbr.detach_from_state();

  // Postconditions:

  ensure(lcoords_space->is_attached());

  // Exit:

  return lcoords_space;
}

void
create_surface_in_name_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create a base space.

  base_space_poset* lbase_space = create_base_space(xns);

  // Create the coordinates section space.

  sec_at1_space* lcoords_space =
    create_coordinates_section(xns, lsurface_base_space_path);

#ifdef DIAGNOSTIC_OUTPUT
  print_cells_subposet(*lbase_space);
  cout << *lbase_space << endl;
  cout << *lcoords_space << endl;
#endif

  // Postconditions:

  // Exit:

  return;
}

void
run_tetgen(fiber_bundles_namespace& xns,
           const string& xtetgen_switches,
           const string& xfilename)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Instantiate a tetgen mesh generator.

  tetgen_generator lgenerator(xns,
                              lsurface_base_space_path,
                              lsurface_coordinates_path,
                              xtetgen_switches);

  // Invoke the generator's generate function.

  lgenerator.generate();


#ifdef DIAGNOSTIC_OUTPUT

  // Create vtk files for input in ParaView, etc.

  // ParaView does not like files with more than 1 ".".
  // So, it will not read "xyz.t.vtk".  Replace "." with "_".

  string lrootname = xfilename;
  int lpos = lrootname.find(".");
  while(lpos != string::npos) 
  {
      lrootname.replace(lpos, 1, "_" );
      lpos = lrootname.find(".", lpos+1);
  } 

  // First create a file from the original (input) surface triangles.

  create_vtk_file(lgenerator.tri_coordinates(),
                  lgenerator.tri_connectivities(),
                  lrootname + "_in.vtk",
                  false);

  // Create a second file from the tetgen generated tetrahedrons.

  create_vtk_file(lgenerator.tet_coordinates(),
                  lgenerator.tet_connectivities(),
                  lrootname + "_out.vtk",
                  true);
#endif

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

  string ltetgen_switches = "pYV"; // 'Y' preserves the original boundaries.
                                   // 'V' makes tetgen verbose.
  if(xargc >= 2)
  {
    ltetgen_switches = xargv[1];
  }

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  create_surface_in_name_space(lns);

  run_tetgen(lns, ltetgen_switches, lfilename);

  cout << lns << endl;

  storage_agent sa(lfilename + ".hdf");
  sa.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
