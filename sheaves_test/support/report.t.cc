// $RCSfile: deep_size.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Test driver for deep_size.

#include "report.h"

#include "block.h"
#include "sheaves_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "stop_watch.h"
#include "test_utils.h"

using namespace sheaf;

namespace
{
  class report_child : public report
  {
  public:
    report_child() {}
    ~report_child() {}
  };
}

int
main()
{

  //============================================================================

  print_header("Begin testing class report");

  // Create top level poset with primitive type definitions.

  sheaves_namespace lns("test_namespace");
  lns.get_read_write_access();

  cout << boolalpha;

  //============================================================================

  // report();

  report lreport0; 

  // report(const namespace_poset* xname_space);

  report lreport(&lns);

  // virtual ~report();

  report* lreport_ptr = new report; 
  delete lreport_ptr;

  // void start(const string& xname);

  lreport.start("report_start");

  // void reset();

  // void point(const string& xname);

  lreport.point("report_point");

  // void write(const string& xfile_name) const;

  lreport.write("report.csv");  

  // inline const namespace_poset* name_space() const;

  const namespace_poset* lname_space = lreport.name_space();

  // inline string title() const;

  string ltitle = lreport.title();

  // inline stop_watch watch() const;

  stop_watch lwatch = lreport.watch();
  
  // inline block<string> names() const;

  block<string> lnames = lreport.names();

  // inline block<size_t> memory() const;

  block<size_t> lmemory = lreport.memory();
 
  // inline block<size_t> memory_part(int lpart) const;

  block<size_t> lmemory_part = lreport.memory_part(0);

  // virtual bool invariant() const;

  bool linvariant = lreport.invariant();
  cout << "linvariant = " << linvariant << endl;

  //ostream & operator << (ostream &os, report& xreport);

  cout << lreport << endl;

  //============================================================================

  report_child* lreport_child_ptr = new report_child;
  delete lreport_child_ptr;

  //============================================================================

  print_footer("End testing class report");

  //============================================================================

  return 0;
}

