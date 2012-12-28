// $RCSfile: stop_watch.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Test driver for class stop_watch.

#include "stop_watch.h"
#include "std_iostream.h"
#include "test_utils.h"

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

