
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// Test driver for deep_size.

#include "SheafSystem/report.h"

#include "SheafSystem/block.h"
#include "SheafSystem/sheaves_namespace.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/stop_watch.h"
#include "SheafSystemTest/test_utils.h"

using namespace std;
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

