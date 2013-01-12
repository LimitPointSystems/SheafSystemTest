
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example viewer/common/vtk_unstructured_grid_writer.t.cc
/// Reads in a coordinate section from a file and writes a vtk file.

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
#include "section_space_factory.h"
#include "section_space_schema_poset.h"
#include "tern.h"
#include "unstructured_block.h"
#include "wsv_block.h"
#include "vtkDoubleArray.h"
#include "vtk_unstructured_grid_builder.h"
#include "vtkUnstructuredGrid.h"
#include "vtkXMLUnstructuredGridWriter.h"

//#define DIAGNOSTIC_OUTPUT

using namespace tool;

namespace
{

///
/// Write the coordinate section xcoord to a vtk file with name xfilename.
///
void write_coordinates(const string& xfilename, sec_vd& xcoord, const string& xparts_sp_name)
{
  // Preconditions:

  require(xcoord.is_attached());

  // Body:

  xcoord.get_read_access();

#ifdef DIAGNOSTIC_OUTPUT
  cout << xcoord.schema().host()->base_space() << endl;
  cout << *xcoord.host() << endl;
#endif

  vtk_unstructured_grid_builder lbuilder(*xcoord.name_space());
  vtkUnstructuredGrid* lgrid;

  if(xparts_sp_name.empty())
  {
    lgrid = lbuilder.build(xcoord);
  }
  else
  {
    lgrid = lbuilder.build(xcoord, xparts_sp_name);
  }

  xcoord.release_access();

  vtkXMLUnstructuredGridWriter* writer = vtkXMLUnstructuredGridWriter::New();
  writer->SetInput(lgrid);
  writer->SetFileName(xfilename.c_str());
  writer->SetDataModeToAscii();
  writer->Write();
  writer->Delete();

  // Postconditions:


  // Exit:

  return;
}

}; // End unnamed namespace.

int main(int argc, char* argv[])
{

  if(argc < 3)
  {
    cout << "Usage: vitk_unstructured_grid_writer.t filename coordinates_path [parts_subposet_name]" << endl;
    exit(0);
  }
  else
  {
    // Test for existence of file
    // if the filename is not valid, then exit 0 with warning message.

    string lfilename;
    if (access(argv[1],0) == 0)
    {
      lfilename = argv[1];
    }
    else
    {
      cout << "Warning: no such file " << argv[1] << "\n";
      exit(0);
    }

    fiber_bundles_namespace lns("vtk_unstructured_grid_writer.t");
    lns.get_read_write_access();

    storage_agent lsa(lfilename, sheaf_file::READ_ONLY, false);
  
    lsa.read_entire(lns);

    poset_path lcoords_path(argv[2]);

    if(!lns.contains_path(lcoords_path))
    {
      cout << "Warning: namespace does not contain coordinates section " << lcoords_path << endl;
      exit(0);
    }      

    // Attach to the coordinate section.

    sec_vd lcoords(&lns, lcoords_path, true);

    // Create vtk filename.

    string root_filename;
    string vtk_filename;
    string::size_type pos = lfilename.rfind(".");
    if(pos != string::npos)
    {
      // Found a suffix; strip it.

      root_filename = lfilename.substr(0, pos);
    }
    else
    {
      // No suffix, root is the whole name

      root_filename = lfilename;
    }
    vtk_filename = root_filename + ".vtu";

    // Write the coordinate section.

    string lparts_sp_name;
    if(argc > 3)
    {
      lparts_sp_name = argv[3];
    }

    write_coordinates(vtk_filename, lcoords, lparts_sp_name);

    // Clean-up.

    lcoords.detach_from_state();
  }
  
  return 0;
}
