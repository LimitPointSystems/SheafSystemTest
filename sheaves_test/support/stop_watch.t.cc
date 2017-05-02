
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

/// Test driver for class stop_watch.

#include "SheafSystem/stop_watch.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystemTest/test_utils.h"

using namespace std;
using namespace sheaf;

namespace
{
  class stop_watch_child : public stop_watch
  {
  public:
    stop_watch_child() {}
    virtual ~stop_watch_child() {}
  };
}

int
main()
{
  // Preconditions:

  // Body:

  print_header("Begin testing class stop_watch.");

  //stop_watch();

  stop_watch lwatch;

  // Default memberwise copy constructor

  stop_watch lwatch_copy(lwatch);

  //virtual ~stop_watch();

  stop_watch* lwatch_ptr = new stop_watch;
  delete lwatch_ptr ;

 // Default memberwise copy constructor

//   enum time_unit
//   {
//     CPU_TIME,
//     MILLISECONDS,
//     SECONDS
//   };

  //void start();

  lwatch.start();

  // Do something to add time.

  for(int n=0; n<2; ++n)
  {
    lwatch.mark_lap();
    for(int i=0; i<1000000; ++i)
    {
      unsigned long lsquared = i*i;
    }
  }

  //double time(time_unit xunit = SECONDS) const;

  double ltime0 = lwatch.time(stop_watch::CPU_TIME);
  double ltime1 = lwatch.time(stop_watch::MILLISECONDS);
  double ltime2 = lwatch.time(stop_watch::SECONDS);

  cout << "ltime0 = " << ltime0 << endl;
  cout << "ltime1 = " << ltime1 << endl;
  cout << "ltime2 = " << ltime2 << endl;

  //double cumulative_time() const;

  double lcumulative_time = lwatch.cumulative_time();

  //void mark_lap();

  lwatch.mark_lap();

  //double lap_time(int i) const;

  double llap_time = lwatch.lap_time(0);

  //size_t lap_ct() const;

  size_t llab_ct = lwatch.lap_ct();
  cout << "llab_ct = " << llab_ct << endl;

  //void stop();

  lwatch.stop();

  //void reset();

  lwatch.reset();

  //ostream & operator << (ostream& xos, stop_watch& xsw);

  cout << "lwatch = " << lwatch << endl;

  //============================================================================

  //$$HACK: To get better coverage of CTORs and DTORs.

  stop_watch_child* lchild = new stop_watch_child;
  delete lchild;

  //============================================================================

  print_footer("End testing class stop_watch.");

  // Postconditions:

  // Exit:

  return 0;
}

