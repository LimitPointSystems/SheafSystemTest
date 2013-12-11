
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

/// class RC_ANY & RC_PTR tester

#include "assert_contract.h"

#include "rc_any.h"
#include "rc_ptr.impl.h"
#include "std_iostream.h"

using namespace std;
using namespace sheaf;

namespace
{

class rc_test : public rc_any {};

void print_rc(rc_test *rc)
{
  cout << "object    = " << rc << endl;
  if(rc)
  {
    cout << "ref_ct = " << rc->ref_ct() << endl;
    cout << "shared    = " << rc->is_shared() << endl;
  }
}

} // end unnamed namespace

int
main()
{
  cout << "---------------------------------" << endl;
  cout << "Constructing shareable rc_any"  << endl << endl;
  rc_test *rc = new rc_test();
  cout << "RESULT" << endl;
  print_rc(rc);
  cout << "---------------------------------" << endl;
  cout << "Constructing first rc_ptr" << endl << endl;
  cout << "RESULT" << endl;
  rc_ptr<rc_test> *ptr1 = new rc_ptr<rc_test>(rc);
  print_rc(rc);
  cout << "---------------------------------" << endl;
  cout << "Constructing second rc_ptr" << endl << endl;
  cout << "RESULT" << endl;
  rc_ptr<rc_test> *ptr2 = new rc_ptr<rc_test>(rc);
  print_rc(rc);
  cout << "---------------------------------" << endl;
  cout << "Destroying first rc_ptr" << endl << endl;
  cout << "RESULT" << endl;
  delete ptr1;
  print_rc(rc);
  cout << "---------------------------------" << endl;
  cout << "Destroying second rc_ptr" << endl << endl;
  cout << "RESULT" << endl;
  delete ptr2;
  cout << "---------------------------------" << endl;

  return 0;
}



