
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

#include "SheafSystem/sheaves_namespace.h"
#include "SheafSystem/deep_size.h"

using namespace std;
using namespace sheaf;

int
main()
{
  // Create top level poset with primitive type definitions.

  sheaves_namespace lns("test_namespace");
  lns.get_read_write_access();

  size_t ldeep_size = deep_size(lns);

  cout << endl;
  cout << "### deep_size(lns) = " << ldeep_size << endl;
  cout << endl;

  //   poset* empty_poset = new poset( lns, &(lns->primitives().schema()), "empty");

  //   size_t ds = empty_poset->deep_size();
  //   cout << "$$$ empty_poset->deep_size() = " << ds << endl;


  return 0;
}

