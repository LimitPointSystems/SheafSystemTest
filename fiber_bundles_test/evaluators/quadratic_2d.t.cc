
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

/// @example evaluators/quadratic_2d.t.cc
/// Test case for class quadratic_2d

#include "quadratic_2d.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace std;
using namespace std;
using namespace fiber_bundle;

typedef section_evaluator::dof_type dof_type;

int main(int argc, char* argv[])
{
  cout << "Testing quadratic_2d" << endl;

  quadratic_2d evaluator;

  // Corner nodes, then midside nodes (interleaved)

  dof_type dofs[] = { 1, 3, 9, 2, 5, 6,
                      0.5*(1+9), 0.5*(3+2),
                      0.5*(9+5), 0.5*(2+6),
                      0.5*(5+1), 0.5*(6+3)};

  dof_type m;

  m = evaluator.min(dofs, 12);
  cout << "min = " << m << endl;

  m = evaluator.max(dofs, 12);
  cout << "max = " << m << endl;

  //evaluator.basis_at_coord();

  //evaluator.value_at_coord();

  //evaluator.coord_at_value();

  //evaluator.dxi_local();

  //========================================================================


  double local_coords[] = { 0.3333333, 0.3333333 };
  //double local_coords[] = { 0.0, 0.0 };

  evaluator.basis_at_coord(local_coords, 2);

  for(int i=0; i<6; ++i)
    cout << "basis_values[" << i << "] = " << evaluator.basis_values()[i] << endl;

  // Test value_at_coord.

  // Single component version.

  //   dof_type x_dofs[] = { 1, 9, 5 };
  //   dof_type y_dofs[] = { 3, 2, 6 };

  //   dof_type x_value = evaluator.value_at_coord(x_dofs, 3, local_coords, 2);

  //   cout << "x_value = " << x_value << endl;

  //   dof_type y_value = evaluator.value_at_coord(y_dofs, 3, local_coords, 2);

  //   cout << "y_value = " << y_value << endl;

  //   // Multiple component version.

  //   dof_type values[2];

  //   //cout << "sizeof(values) = " << sizeof(values) << endl;

  //   evaluator.value_at_coord(dofs, 6, local_coords, 2, values, 2);

  //   cout << "x_value = " << values[0] << endl;
  //   cout << "y_value = " << values[1] << endl;

  //   // Test coord_at_value.

  //   //dof_type global_coords[] = { 5.0, 6.0 };
  //   //dof_type global_coords[] = {5.0, 7.0  };
  //   //dof_type global_coords[] = { 1.0, 3.0 };
  //   dof_type global_coords[] = { 15.0/3.0, 11.0/3.0 };

  //   evaluator.coord_at_value(dofs, 6, global_coords, 2, local_coords, 2);

  //   cout << "local_coords[0] = " << local_coords[0] << endl;
  //   cout << "local_coords[1] = " << local_coords[1] << endl;

  //========================================================================

  return 0;
}
