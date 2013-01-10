// $RCSfile$ $Revision$ $Date$

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example mesh_generators/tetgen_generator.t.cc
/// Test driver for tetgen_generator.cc.

#ifdef _WIN32
#include "io.h"
#endif

#include "tetgen_generator.h"

#include "fiber_bundles_namespace.h"
#include "std_fstream.h"
#include "std_iostream.h"
#include "storage_agent.h"

using namespace geometry;

int
main(int argc, const char* argv[])
{
  string lprogname(argv[0]);
  string lfilename;

if (argc > 1)
 {
   // test for existence of file
   // if the filename is not valid, then exit 0 with warning message
  if (access(argv[1],0) == 0)
   {
     lfilename = argv[1];
   }
   else
   {
     cout << "warning: no such filename " << argv[1] << "\n";
     exit(0);
   }
 }
else
 {
   cout << "Usage: " << lprogname << " sheaf_file [enable_error_report]" << endl;
    exit(0);
 }

  // Make the default namespace

  //fiber_bundles_namespace lns(lprogname);
  fiber_bundles_namespace lns("test");

  // Read the namespace from the file.
  // Need read access to read it and read/write access to delete
  // the namespace.

  lns.get_read_write_access();
  bool lenable_error_report = (argc > 2);
  storage_agent sa(lfilename, sheaf_file::READ_ONLY, false,
                   lenable_error_report);
  sa.read_entire(lns);

  // Dump the namespace.

  //cout << lns << endl;

  cout << "######################################" << endl;
  cout << lns.path() << endl;
  cout << lns.path().poset_name() << endl;
  cout << lns.path().member_name() << endl;
  cout << "######################################" << endl;

  //============================================================================

  // Instantiate a tetgen mesh generator and invoke its generate function.

  poset_path lbase_member_path("line_web_structure", "active_surface");
  poset_path lcoords_member_path("coordinates_on_lines",
                                 "line_coordinates");
  tetgen_generator lgen(lns, lbase_member_path, lcoords_member_path);

  // Invoke the generate function.

  lgen.generate();

  //============================================================================

  cout << lns << endl;

//   //storage_agent sa2(lfilename);
//   storage_agent sa2("test.hdf");
//   sa2.write_entire(lns);

  //============================================================================

  return 0;
}
