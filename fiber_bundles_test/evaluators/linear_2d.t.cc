
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

/// @example evaluators/linear_2d.t.cc
/// Test case for class linear_2d

#include "linear_2d.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

typedef section_evaluator::dof_type dof_type;

int main(int argc, char* argv[])
{
  cout << "Testing linear_2d" << endl;

  linear_2d evaluator;

  dof_type dofs[] = { 1, 3, 9, 2, 5, 6 };

  dof_type m;

  m = evaluator.min(dofs, 6);
  cout << "min = " << m << endl;

  m = evaluator.max(dofs, 6);
  cout << "max = " << m << endl;


  //========================================================================


  double local_coords[] = { 0.3333333, 0.3333333 };
  // double local_coords[] = { 0.0, 0.0 };

  evaluator.basis_at_coord(local_coords, 2);

  for(int i=0; i<3; ++i)
    cout << "basis_values[" << i << "] = " << evaluator.basis_values()[i] << endl;

  // Test value_at_coord.

  // Single component version.

  dof_type x_dofs[] = { 1, 9, 5 };
  dof_type y_dofs[] = { 3, 2, 6 };

  dof_type x_value = evaluator.value_at_coord(x_dofs, 3, local_coords, 2);

  cout << "x_value = " << x_value << endl;

  dof_type y_value = evaluator.value_at_coord(y_dofs, 3, local_coords, 2);

  cout << "y_value = " << y_value << endl;

  // Multiple component version.

  dof_type values[2];

  //cout << "sizeof(values) = " << sizeof(values) << endl;

  evaluator.value_at_coord(dofs, 6, local_coords, 2, values, 2);

  cout << "x_value = " << values[0] << endl;
  cout << "y_value = " << values[1] << endl;

  // Test coord_at_value.

  //dof_type global_coords[] = { 5.0, 6.0 };
  //dof_type global_coords[] = {5.0, 7.0  };
  //dof_type global_coords[] = { 1.0, 3.0 };
  dof_type global_coords[] = { 15.0/3.0, 11.0/3.0 };

  evaluator.coord_at_value(dofs, 6, global_coords, 2, local_coords, 2);

  cout << "local_coords[0] = " << local_coords[0] << endl;
  cout << "local_coords[1] = " << local_coords[1] << endl;


  //evaluator.dxi_local();

  //========================================================================

  return 0;
}
