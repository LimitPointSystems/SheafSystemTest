
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example concurrency/concurrency.t.cc
/// tester for CONCURRENCY cluster

#include "std_iostream.h"

#ifdef _PTHREADS

#ifndef LINE_H
#include "line.h"
#endif

#ifndef NAMESPACE_POSET_H
#include "namespace_poset.h"
#endif

class poset;

#ifndef POSET_MEMBER_H
#include "abstract_poset_member.h"
#endif

#ifndef RUNNABLE_H
#include "runnable.h"
#endif

#ifndef THREAD_H
#include "thread.h"
#endif

#ifndef THREAD_CONDITION_VARIABLE_H
#include "thread_condition_variable.h"
#endif

#ifndef TRIANGLE_H
#include "triangle.h"
#endif

// global variables accessible to all threads:

namespace_poset            nsp("table_of_contents");
// This namespace_poset is accessible by every thread.  The line and
// triangle posets belong to this namespace.
thread_condition_variable  nsp_tcv;
// Used to avoid race conditions in operations on the namespace.
//
line                      *Line;
// A reference to an instance of a class that makes a "line" poset.
poset                     *line_poset     = 0;
// The actual "line" poset.
thread_condition_variable  line_tcv;
// Used to avoid race conditions in operations on the line poset.
triangle                  *Triangle;
// A reference to an instance of a class that makes a "triangle" poset.
poset                     *triangle_poset = 0;
// The actual "triangle" poset.
thread_condition_variable  triangle_tcv;
// Used to avoid race conditions in operations on the triangle poset.

// The following are little classes whose sole function is to define a "run" method
// which does "poset things" in parallel via separate threads.  Invoking "run"
// introduces a new thread of execution, which persists until "run" is
// finished.

class line_maker: public runnable
{

public:

  void  run();
};

void
line_maker::run()
{

  // This routine makes the line poset

  nsp_tcv.lock_mutex();
  // Acquire a mutex on the namespace_poset so we can be sure that there is
  // no race condition in acquiring access to the namespace poset and the
  // primitives poset
  nsp.get_read_write_access();
  // Get write access to namespace_poset so we can insert the line poset into it
  nsp.primitives().get_read_access();
  // Get read access to primitives so a member can be used as the column poset for "line"
  Line = new line(&nsp, &(nsp.primitives().int_type()), false, "line");
  line_poset = Line->get_poset();
  nsp.primitives().release_access();
  // Be polite and release access we no longer need
  nsp.release_access();
  // Be polite and release access we no longer need
  nsp_tcv.broadcast();
  // Tell the world we made line_poset. This is the mechanism that wakes up any
  // other thread that may be waiting on the namespace thread condition variable.
  nsp_tcv.unlock_mutex();
  // Release the mutex.  We're done manipulating the namespace poset.

}

class line_printer: public runnable
{

public:

  void run();
};

void
line_printer::run()
{

  line_tcv.lock_mutex();
  while (line_poset == 0)
    line_tcv.wait();
  line_tcv.unlock_mutex();
  // The above code waits until line_poset becomes non-void, signalling
  // that it no points to a fully constructed object.

  line_poset->get_read_access();
  nsp.primitives().get_read_access();

  cout << "Line poset...\n\n"
  << *line_poset
  << endl;
  ;

  nsp.primitives().release_access();
  line_poset->release_access();

}

class triangle_printer: public runnable
{

public:

  void run();
};

void
triangle_printer::run()
{

  triangle_tcv.lock_mutex();
  while (triangle_poset == 0)
    triangle_tcv.wait();
  triangle_tcv.unlock_mutex();
  // The above code waits until triangle_poset becomes non-void, signalling
  // that it now points to a fully constructed object.

  triangle_poset->get_read_access();
  nsp.primitives().get_read_access();

  cout << "Triangle poset...\n\n"
  << *triangle_poset
  << endl;
  ;

  nsp.primitives().release_access();
  triangle_poset->release_access();

}


class triangle_maker: public runnable
{

public:

  void  run();
};

void
triangle_maker::run()
{

  nsp_tcv.lock_mutex();
  // Acquire a mutex on the namespace_poset so we can be sure that there is
  // no race condition in acquiring access to the namespace poset and the
  // primitives poset
  nsp.get_read_write_access();
  // Get write access to namespace_poset so we can insert the triangle poset into it
  nsp.primitives().get_read_access();
  // Get read access to primitives so a member can be used as the column poset for "triangle"
  Triangle = new triangle(&nsp, &(nsp.primitives().int_type()), false, "triangle");
  triangle_poset = Triangle->get_poset();
  nsp.primitives().release_access();
  // Be polite and release access we no longer need
  nsp.release_access();
  // Be polite and release access we no longer need
  nsp_tcv.broadcast();
  // Tell the world we made triangle_poset. This is the mechanism that wakes up any
  // other thread that may be waiting on the namespace thread condition variable.
  nsp_tcv.unlock_mutex();
  // Release the mutex.  We're done manipulating the namespace poset.


}

class triangle_counter: public runnable
{

public:

  void run();
};

void
triangle_counter::
run()
{

  triangle_poset->get_read_access();

  cout << "Triangle member count is "
  << triangle_poset->member_ct()
  << ", jim_ct is "
  << triangle_poset->jims().member_ct()
  << endl;

  triangle_poset->release_access();

}

main()
{

  void doit();

  doit();

}

void doit()
{

  // construction and printing happen in separate threads from
  // main thread.

  // First, make instances of all classes that are going to do something
  // in separate threads (the "actors").
  line_maker       lm;
  line_printer     lp;
  triangle_maker   tm;
  triangle_printer tp1;
  triangle_printer tp2;
  triangle_printer tp3;

  // Then make separate threads and register the actors with them.
  thread t1(&lm);
  thread t2(&tm);
  thread t3(&lp);
  thread t4(&tp1);
  thread t5(&tp2);
  thread t6(&tp3);

  //  Then start the threads running.
  t1.start();
  t2.start();
  t3.start();
  t4.start();
  t5.start();
  t6.start();

  // Wait here until the actors have all finished their jobs.
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();

  // Create some counters.
  triangle_counter tc1;
  triangle_counter tc2;
  triangle_counter tc3;
  triangle_counter tc4;

  // Create some threads.
  thread t7(&tc1);
  thread t8(&tc2);
  thread t9(&tc3);
  thread t10(&tc4);

  // Run all the counters
  t7.start();
  t8.start();
  t9.start();
  t10.start();

  // Wait here until they've all finished counting.
  t7.join();
  t8.join();
  t9.join();
  t10.join();

}

// The following are various alternatives to doit():

void doit2()
{

  // poset construction happens in separate thread.
  // basically serial.

  line_maker       lm;
  line_printer     lp;

  thread t1(&lm);

  t1.start();

  t1.join();
  lp.run();
}

void doit3()
{

  // everything runs in main thread:

  line_maker       lm;
  line_printer     lp;

  lm.run();
  lp.run();
}

void doit4()
{

  // everything runs in main thread:

  triangle_maker       tm;
  triangle_printer     tp;

  tm.run();
  tp.run();
}

void doit5()
{

  // poset construction happens in separate thread.
  // basically serial.
  triangle_maker       tm;
  triangle_printer     tp;

  thread t1(&tm);

  t1.start();

  t1.join();
  tp.run();
}

#else // no _PTHREADS

int main()
{
  cout << "Not compiled with -D_PTHREADS" << endl;

  return 0;
}

#endif // no _PTHREADS

