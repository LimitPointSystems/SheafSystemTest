
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example viewer/common/vtk_unstructured_grid_builder_from_file.t.cc
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
#include "section_space_factory.h"
#include "section_space_schema_poset.h"
#include "tern.h"
#include "unstructured_block.h"
#include "wsv_block.h"
#include "vtkDoubleArray.h"
#include "vtk_unstructured_grid_builder.h"
#include "vtkUnstructuredGrid.h"

#define DIAGNOSTIC_OUTPUT

using namespace tool;

namespace
{

///
/// tests vtk_unstructured_grid_builder on xcoord and xprop.
///
void test_grid_builder(sec_vd& xcoord)
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
  vtkUnstructuredGrid* lgrid = lbuilder.build(xcoord);

  vtkIndent lindent;
  lgrid->PrintSelf(cout, lindent);

  xcoord.release_access();

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

#ifdef DIAGNOSTIC_OUTPUT

  cout << xcoord.schema().host()->base_space() << endl;
  cout << *xcoord.host() << endl;
  cout << *xprop.host() << endl;
#endif

  vtk_unstructured_grid_builder lbuilder(*xcoord.name_space());
  vtkUnstructuredGrid* lgrid =
    lbuilder.build(xcoord, xprop);

  vtkIndent lindent;
  lgrid->PrintSelf(cout, lindent);

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


}
; // End unnamed namespace.

int main(int argc, char* argv[])
{

  if(argc < 3)
  {
    cout << "Usage: vitk_unstructured_grid_builder_from_file.t filename coordinates_path [property_path]" << endl;
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

    fiber_bundles_namespace lns("vtk_unstructured_grid_builder.t");
    lns.get_read_write_access();

    storage_agent lsa(lfilename, sheaf_file::READ_ONLY, false);
  
    lsa.read_entire(lns);

    poset_path lcoords_path(argv[2]);

    if(!lns.contains_path(lcoords_path))
    {
      cout << "Warning: namespace does not contain coordinates section " << lcoords_path << endl;
      exit(0);
    }      

    sec_vd lcoords(&lns, lcoords_path, true);

    if(argc == 3)
    {  
      test_grid_builder(lcoords);  
    }
    else
    {
      poset_path lprop_path(argv[3]);

      if(!lns.contains_path(lprop_path))
      {
	cout << "Warning: namespace does not contain property section " << lcoords_path << endl;
	exit(0);
      }
    
      sec_vd lprop(&lns, lprop_path, true);

      test_grid_builder(lcoords, lprop);
    
      lprop.detach_from_state();
    }
  
    lcoords.detach_from_state();
  }
  
  return 0;
}
