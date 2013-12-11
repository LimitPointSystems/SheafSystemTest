
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

/// @example base_spaces/line_connectivity.t.cc
/// Test case for class line_connectivity

#include "line_connectivity.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

int main()
{

  line_connectivity c(5);

  cout << c << endl;

  cout << "c.node_id_ct() = " << c.node_id_ct() << endl;

  line_connectivity c1;

  cout << c1 << endl;

  cout << "c1.node_id_ct() = " << c1.node_id_ct() << endl;

  line_connectivity c2(5,1);

  cout << c2 << endl;

  cout << "c2.node_id_ct() = " << c2.node_id_ct() << endl;


  return 0;

}
