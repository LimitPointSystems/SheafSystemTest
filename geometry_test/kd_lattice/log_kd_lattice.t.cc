
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/log_kd_lattice.t.cc
/// Reads kd_lattice log/restart files and rexecutes.

#include "assert_contract.h"
#include "kd_lattice.h"
#include "geometry_namespace.h"
#include "sec_e3.h"
#include "sec_at1_space.h"
#include "std_fstream.h"
#include "std_iostream.h"
#include "storage_agent.h"

using namespace geometry;


namespace
{  
  
} // unnamed namespace


int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:
  
  if(argc == 1)
  {
    cout << "usage: log_kd_lattice.t file [file [file ...]]" << endl;
    exit(0);
  }

  kd_lattice_log llog;

  for(int i=1; i<argc; ++i)
  {    
    ifstream gfile(argv[i]);

    if(!gfile)
    {
      cout << "open failed for file " << argv[i] << endl;
      return 1;
    }

    // Read the file.

    gfile >> llog;

    gfile.close();

  }

  string lfile_name(argv[1]);
  string lbase_file_name(lfile_name.substr(0, lfile_name.find('.')));

  geometry_namespace lns(lbase_file_name);
  lns.get_read_write_access();

  string lerr_msg;

  kd_lattice* lkd_lattice = kd_lattice::restart(lns, llog, false, false, "", lerr_msg);
  if(lkd_lattice == 0)
  {
    // Crashed; Can't restart.

    cerr << lerr_msg << endl;
    cerr << "Restart failed." << endl;
    exit(1);
  }

//   kd_bounding_box lbox(lkd_lattice->bounding_box());
//   e3_lite lsize = lbox.size();

//   if(lfile_name == "c2_simply_branching.log")
//   {
//     lbox.lb()[0] = 12500.0;
//     lbox.lb()[1] = 16000.0;
//     lbox.lb()[2] = 2000.0;

//     lbox.ub()[0] = 16200.0;
//     lbox.ub()[1] = 24000.0;
//     lbox.ub()[2] = 5000.0;
//   }
//   else if(lfile_name == "i4_cross-cutting.log")
//   {
//     lbox.lb()[0] = 19500.0;
//     lbox.lb()[1] = 5800.0;
//     lbox.lb()[2] = 2620.0;

//     lbox.ub()[0] = 22500.0;
//     lbox.ub()[1] = 10000.0;
//     lbox.ub()[2] = 4192.0;
//   }
//   else if(lfile_name == "salt_faults_h1.log")
//   {
//     //        lbox.lb()[0] = 4100.0;
//     lbox.lb()[0] = 23600.0;

//     lbox.lb()[1] = 5100.0;
//     //      lbox.lb()[1] = 9400.0;

//     //      lbox.lb()[2] = -2500.0;
//     lbox.lb()[2] = 500.0;

//     //        lbox.ub()[0] = 30200.0;
//     lbox.ub()[0] = 26700.0;

//     //      lbox.ub()[1] = 17900.0;
//     //lbox.ub()[1] = 21000.0;
//     lbox.ub()[1] = 26700.0;

//     //      lbox.ub()[2] = 8500.0;
//     lbox.ub()[2] = 5000.0;
//   }
//   else if(lfile_name == "salt_faults_h1_h4.log")
//   {
//     //        lbox.lb()[0] = 4100.0;
//     lbox.lb()[0] = 23600.0;

//     lbox.lb()[1] = 5100.0;
//     //      lbox.lb()[1] = 9400.0;

//     //      lbox.lb()[2] = -2500.0;
//     lbox.lb()[2] = 500.0;

//     //        lbox.ub()[0] = 30200.0;
//     lbox.ub()[0] = 26700.0;

//     //      lbox.ub()[1] = 17900.0;
//     //lbox.ub()[1] = 21000.0;
//     lbox.ub()[1] = 26700.0;

//     //      lbox.ub()[2] = 8500.0;
//     lbox.ub()[2] = 5000.0;
//   }
//   else if(lfile_name == "wb_salt_faults_h1_h4.log")
//   {
//     //lbox.lb()[0] = 4100.0;
//     lbox.lb()[0] = 7900.0;
//     //lbox.lb()[0] = 20300.0;
//     //lbox.lb()[0] = 23600.0;

//     lbox.lb()[1] = 5100.0;
//     //      lbox.lb()[1] = 9400.0;

//     //      lbox.lb()[2] = -2500.0;
//     lbox.lb()[2] = 500.0;

//     //        lbox.ub()[0] = 30200.0;
//     lbox.ub()[0] = 26700.0;

//     //      lbox.ub()[1] = 17900.0;
//     //lbox.ub()[1] = 21000.0;
//     lbox.ub()[1] = 26700.0;

//     //      lbox.ub()[2] = 8500.0;
//     //lbox.ub()[2] = 4772.0;
//     lbox.ub()[2] = 5500.0;
//   }
//   else if(lfile_name == "F2_H1.log")
//   {
//     //        lbox.lb()[0] = 4100.0;
//     lbox.lb()[0] = 23600.0;

//     //        lbox.lb()[1] = 5100.0;
//     lbox.lb()[1] = 9400.0;

//     lbox.lb()[2] = 1000.0;

//     //        lbox.ub()[0] = 30200.0;
//     lbox.ub()[0] = 26700.0;

//     //        lbox.ub()[1] = 26700.0;
//     lbox.ub()[1] = 21000.0;

//     lbox.ub()[2] = 5000.0;
//   }
//   else if(lfile_name == "SB5_testdata.log")
//   {
//     //        lbox.lb()[0] = 4100.0;
//     //lbox.lb()[0] = 20300.0;
//     lbox.lb()[0] = 23600.0;

//     //lbox.lb()[1] = 5100.0;
//     lbox.lb()[1] = 9400.0;

//     //      lbox.lb()[2] = -2500.0;
//     lbox.lb()[2] = 500.0;

//     //        lbox.ub()[0] = 30200.0;
//     lbox.ub()[0] = 26700.0;

//     //      lbox.ub()[1] = 17900.0;
//     //lbox.ub()[1] = 21000.0;
//     lbox.ub()[1] = 26700.0;

//     //      lbox.ub()[2] = 8500.0;
//     //lbox.ub()[2] = 4772.0;
//     lbox.ub()[2] = 5500.0;
//   }
//   else
//   {
//     cout << "Don't have bounds for this file, quiting." << endl;
//     return 0;
//   }    

//   cout << endl << "domain: " << lkd_lattice->bounding_box() << endl;
//   cout << "region of interest: " << lbox << endl;    

//   lkd_lattice->insert_region(lbox.lb(), lbox.ub());
    
  lkd_lattice->display(false, false);

  // Create sections for the active part;
  // used for viewing in SheafScope.

  //    lkd_lattice->create_active_sections();


  //    cout << lkd_lattice->name_space() << endl;

  // Output namespace before finishing.
  
  // Namespace destructor requires write access.
 
  //    lkd_lattice->name_space().get_read_write_access();
  //    storage_agent lsa("log_structure.t.hdf");
  //    lsa.write_entire(lkd_lattice->name_space());

  // Done.

  return 0;
}

  
