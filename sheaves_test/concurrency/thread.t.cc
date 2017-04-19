
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

#ifdef _PTHREADS

#include "SheafSystem/std_iostream.h"

#include "SheafSystem/read_write_monitor.h"

#include "SheafSystem/runnable.h"

#include "SheafSystem/singly_linked_list.h"

#include "SheafSystem/thread.h"

#include "SheafSystem/thread_condition_variable.h"

#include "SheafSystem/thread_mutex.h"

thread_mutex               p_mutex;
int                        p;
thread_condition_variable  tcv;
singly_linked_list<int>                *list = 0;
int                        wait_for_nonzero_value = 0;

class test_lock: public runnable {

public:
  void  run();
};

void
test_lock::
run() {

  p_mutex.lock();

  if (list == 0)
    list = new singly_linked_list<int>;
  list->push_front(list->size());

  thread *me = thread::current_thread();
  cout << "My thread is " << hex << me;

  cout << ".  List length is " << dec << list->size();

  if (me != 0) {
    int ct = me->active_count();

    cout << ".  The active count is " << dec << ct;
    cout << ".  p is " << p;

    me->sleep(1); // to give other threads a chance at p in case mutex lock didn't work
    ++p;
    cout << ". I'm changing p to " << p;
  }

  cout << '.' << dec << endl;
  cout.flush();

  p_mutex.unlock();

}

class test_no_lock: public runnable {

public:
  void  run();
};

void
test_no_lock::
run() {

  thread *me = thread::current_thread();
  cout << "My thread is " << hex << me;

  if (me != 0) {
    int ct = me->active_count();

    cout << ".  The active count is " << dec << ct;
    cout << ".  p is " << p;

    me->sleep(1); // to give other threads a chance at p
    ++p;
    cout << ". I'm changing p to " << p;
  }

  cout << '.' << dec << endl;
  cout.flush();

}

class test_cv1: public runnable {

public:

  void run();
};

void
test_cv1::
run() {

  tcv.lock_mutex();

  while(wait_for_nonzero_value == 0) {
    cout << "testcv1: Waiting until signalled." << endl;
    tcv.wait();
  }
  cout << "testcv1: Got the signal.\n" << endl;

  tcv.unlock_mutex();

}

class test_cv2: public runnable {

public:

  void run();
};

void
test_cv2::
run() {

  tcv.lock_mutex();

  cout << "test_cv2: Signalling everyone else to proceed." << endl;
  wait_for_nonzero_value = 1;
  tcv.broadcast();

  tcv.unlock_mutex();
}

void doit(runnable *r);

int main() {

  test_lock   tl;

  cout << "Testing lockable version..." << endl;

  tl.run(); // see if we can run it in main thread

  doit(&tl);

  test_no_lock tnl;

  cout << "Testing no-lock version..." << endl;

  tnl.run();

  doit(&tnl);

  test_cv1  tcv1;
  test_cv2  tcv2;
  thread    t1(&tcv1);
  thread    t2(&tcv2);

  /// @issue
  /// The order of starting threads is critical if compiled without
  /// real thread support.  In purely sequential execution, wait
  /// and signal are no-ops.  Given the pthreads programming idioms
  /// for wait and signal, if you wait first, you'll wait forever.
  /// For purely sequential code to run like real threaded code,
  /// wait() and signal() actually need to do something.

  t2.start();
  t1.start();

  t1.join();
  t2.join();

  return 0;
}
void
doit(runnable* r) {

  // preconditions:

  require(r != 0);

  // body:

  p = 0;

  thread *lotsa_threads[10];

  for (int i = 0; i < 10; ++i)
    lotsa_threads[i] = new thread(r);

  for (int i = 0; i < 10; ++i)
    lotsa_threads[i]->start();

  for (int i = 0; i < 10; ++i)
    lotsa_threads[i]->join();

  for (int i = 0; i < 10; ++i)
    delete lotsa_threads[i];
}

#else // no _PTHREADS

#include "SheafSystem/std_iostream.h"

int main() {
  std::cout << "Not built with -D_PTHREADS" << std::endl;

  return 0;
}

#endif // no _PTHREADS
