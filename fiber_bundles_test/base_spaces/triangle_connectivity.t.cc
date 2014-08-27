
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

/// @example base_spaces/triangle_connectivity.t.cc
/// Test case for class triangle_connectivity

#include "triangle_connectivity.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

int main()
{

  triangle_connectivity c(2, 3);

  cout << c << endl;

  cout << "c.node_id_ct() = " << c.node_id_ct() << endl;

  triangle_connectivity c1;

  cout << c1 << endl;

  cout << "c1.node_id_ct() = " << c1.node_id_ct() << endl;

  triangle_connectivity c2(4, 2, 1);

  cout << c2 << endl;

  cout << "c2.node_id_ct() = " << c2.node_id_ct() << endl;


  pod_index_type lnode_ids3[6] = {0,1,2,0,2,3}; 
  triangle_connectivity c3(lnode_ids3, 6, 4);
  
  cout << c3 << endl;
  cout << "c3.node_id_ct() = " << c3.node_id_ct() << endl;
  cout << "c3.node_ct() = " << c3.node_ct() << endl;
  cout << "c3.start_id() = " << c3.start_id() << endl;

  pod_index_type lnode_ids4[6] = {1,2,3,1,3,4}; 
  triangle_connectivity c4(lnode_ids4, 6, 0);
  
  cout << c4 << endl;
  cout << "c4.node_id_ct() = " << c4.node_id_ct() << endl;
  cout << "c4.node_ct() = " << c4.node_ct() << endl;
  cout << "c4.start_id() = " << c4.start_id() << endl;
  

  return 0;

}
