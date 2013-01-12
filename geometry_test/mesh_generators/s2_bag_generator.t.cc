

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example s2_bag_generator.t.cc

// Generates a tetrahedral mesh for the salt bag portion
// of surface geometry described by s2_bag+2horizons.log
// (Shell_data/truncationtopologyreftests/s2_bag+2horizons.log).

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
  const size_type lnode_id_ct = 318;
  const pod_index_type lnode_ids[318] =
  {
     0,     1,     2,
     1,     3,     2,
     3,     4,     2,
     4,     5,     2,
     5,     6,     2,
     6,     7,     2,
     7,     8,     2,
     8,     9,     2,
     9,    10,     2,
    10,    11,     2,
    11,    12,     2,
    12,    13,     2,
    13,    14,     2,
    14,    15,     2,
    15,    16,     2,
    16,    17,     2,
    17,    18,     2,
    18,    19,     2,
    19,    20,     2,
    20,    21,     2,
    21,    22,     2,
    22,    23,     2,
    23,    24,     2,
    24,    25,     2,
    25,    26,     2,
    26,    27,     2,
    27,    28,     2,
    28,    29,     2,
    29,     0,     2,
     0,    29,    30,
    29,    28,    30,
    28,    27,    30,
    27,    26,    30,
    26,    25,    30,
    25,    24,    30,
    24,    23,    30,
    23,    22,    30,
    22,    21,    30,
    21,    20,    30,
    20,    31,    30,
    31,    32,    30,
    32,    33,    30,
    33,    34,    30,
    34,    35,    30,
    35,    36,    30,
    36,    37,    30,
    37,    38,    30,
    38,    39,    30,
    39,    40,    30,
    40,    41,    30,
    41,    42,    30,
    42,    43,    30,
    43,     5,    30,
     5,     4,    30,
     4,     3,    30,
     3,     1,    30,
     1,     0,    30,
     9,     8,    44,
     8,     7,    44,
     7,     6,    44,
     6,     5,    44,
     5,    45,    44,
    45,    46,    44,
    46,    47,    44,
    47,    48,    44,
    48,    49,    44,
    49,    50,    44,
    50,    51,    44,
    51,    52,    44,
    52,    53,    44,
    53,    20,    44,
    20,    19,    44,
    19,    18,    44,
    18,    17,    44,
    17,    16,    44,
    16,    15,    44,
    15,    14,    44,
    14,    13,    44,
    13,    12,    44,
    12,    11,    44,
    11,    10,    44,
    10,     9,    44,
    20,    53,    54,
    53,    52,    54,
    52,    51,    54,
    51,    50,    54,
    50,    49,    54,
    49,    48,    54,
    48,    47,    54,
    47,    46,    54,
    46,    45,    54,
    45,     5,    54,
     5,    43,    54,
    43,    42,    54,
    42,    41,    54,
    41,    40,    54,
    40,    39,    54,
    39,    38,    54,
    38,    37,    54,
    37,    36,    54,
    36,    35,    54,
    35,    34,    54,
    34,    33,    54,
    33,    32,    54,
    32,    31,    54,
    31,    20,    54
  };

  xconns.assign(lnode_ids, lnode_ids+lnode_id_ct);
}

void
get_coordinates(vector<e3_lite>& xcoords)
{
  const int lcoords_ct = 55;
  const e3_lite lcoords_array[55] =
  {
    e3_lite(       24700,         26329,        1251.6),
    e3_lite(       24700,         25831,        1124.4),
    e3_lite(     26019.3,       23458.3,       1896.95),
    e3_lite(       24700,         24656,         955.8),
    e3_lite(       24700,         22512,         898.1),
    e3_lite(       24700,         22100,       925.138),
    e3_lite(     25279.1,         22100,         945.3),
    e3_lite(     26683.9,         22100,        1050.8),
    e3_lite(     27596.5,         22100,        1193.8),
    e3_lite(     28278.3,         22100,        1274.5),
    e3_lite(     28896.1,         22100,        1400.5),
    e3_lite(     29087.8,         22100,        1539.9),
    e3_lite(     28380.1,         22100,          1633),
    e3_lite(     27241.9,         22100,          1773),
    e3_lite(     26110.8,         22100,        1928.3),
    e3_lite(       27141,         22100,        2199.5),
    e3_lite(     27720.6,         22100,        2369.3),
    e3_lite(     28362.3,         22100,        2653.2),
    e3_lite(     27767.8,         22100,        2994.2),
    e3_lite(     25513.6,         22100,          3164),
    e3_lite(       24700,         22100,        3163.6),
    e3_lite(       24700,         22355,          3185),
    e3_lite(       24700,         24468,        3161.5),
    e3_lite(       24700,         26659,          2878),
    e3_lite(       24700,         26840,        2504.8),
    e3_lite(       24700,         26149,        2238.4),
    e3_lite(       24700,         24655,        1951.1),
    e3_lite(       24700,         24406,        1749.7),
    e3_lite(       24700,         25165,        1519.9),
    e3_lite(       24700,         26665,        1385.2),
    e3_lite(     23355.3,       23506.8,       1889.08),
    e3_lite(       22673,         22100,        3156.6),
    e3_lite(     21497.5,         22100,        2949.3),
    e3_lite(     20961.1,         22100,        2707.7),
    e3_lite(     20695.8,         22100,        2460.5),
    e3_lite(     20712.1,         22100,        2141.7),
    e3_lite(     22614.9,         22100,        1919.4),
    e3_lite(     23149.6,         22100,        1762.8),
    e3_lite(     21949.9,         22100,        1567.7),
    e3_lite(     20262.9,         22100,        1318.3),
    e3_lite(     20510.5,         22100,        1181.7),
    e3_lite(     21518.9,         22100,          1014),
    e3_lite(     22813.3,         22100,         913.4),
    e3_lite(     24088.5,         22100,         908.9),
    e3_lite(     26230.4,       21222.5,       1918.88),
    e3_lite(       24700,         20152,        1038.9),
    e3_lite(       24700,         18627,        1299.4),
    e3_lite(       24700,         17710,        1520.9),
    e3_lite(       24700,         20147,        1728.1),
    e3_lite(       24700,         21392,          1951),
    e3_lite(       24700,         20553,        2158.6),
    e3_lite(       24700,         19459,        2402.2),
    e3_lite(       24700,         18897,        2659.7),
    e3_lite(       24700,         20026,        3005.2),
    e3_lite(     23131.2,         21186,       1910.61)
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

  //string ltetgen_switches = "pYq1.4V"; // 'Y' preserves the original boundaries.
  string ltetgen_switches = "pq1.4V";    // No 'Y' => replace external boundary.
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
