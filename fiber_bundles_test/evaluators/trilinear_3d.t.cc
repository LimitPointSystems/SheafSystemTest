
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

/// @example evaluators/trilinear_3d.t.cc
/// Test case for class trilinear_3d

#include "SheafSystem/trilinear_3d.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_iostream.h"

using namespace std;
using namespace std;
using namespace fiber_bundle;

typedef section_evaluator::dof_type dof_type;

void basis_at_coord(double* xlocal_coord, size_type xlocal_coord_ub,
                    double* xresult, size_type xresult_ub)
{}


int main(int argc, char* argv[])
{
  cout << "Testing trilinear_3d" << endl;

  trilinear_3d evaluator;

  dof_type dofs[] = { 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0,
                      0.5, 0, 1, 0.5, 0, 1, 1, 0.5, 1, 0, 0.5, 1 }; //interleaved

  dof_type m;

  m = evaluator.min(dofs, 24);
  cout << "min = " << m << endl;

  m = evaluator.max(dofs, 24);
  cout << "max = " << m << endl;

  double local_coords[] = { 0.75, 0.25, 0.0 };

  evaluator.basis_at_coord(local_coords, 3);

  for(int i=0; i<8; ++i)
    cout << "basis_values[" << i << "] = " << evaluator.basis_values()[i] << endl;

  // Test value_at_coord.

  // Single component version.

  dof_type x_dofs[] = { 0, 1, 1, 0, 0, 0.5, 0.5, 0 };

  dof_type y_dofs[] = { 0, 0, 1, 1, 0, 0, 0.5, 0.5 };

  dof_type z_dofs[] = { 0, 0, 0, 0, 1, 1, 1, 1 };

  dof_type x_value = evaluator.value_at_coord(x_dofs, 8, local_coords, 3);

  cout << "x_value = " << x_value << endl;

  dof_type y_value = evaluator.value_at_coord(y_dofs, 8, local_coords, 3);

  cout << "y_value = " << y_value << endl;

  dof_type z_value = evaluator.value_at_coord(z_dofs, 8, local_coords, 3);

  cout << "z_value = " << z_value << endl;

  // Multiple component version.

  dof_type values[3];

  //cout << "sizeof(values) = " << sizeof(values) << endl;

  evaluator.value_at_coord(dofs, 24, local_coords, 3, values, 3);

  cout << "x_value = " << values[0] << endl;
  cout << "y_value = " << values[1] << endl;
  cout << "z_value = " << values[2] << endl;

  // Test coord_at_value.

  dof_type global_coords[] = { 0.75, 0.25, 0.0  };

  // Interleaved dofs.

  evaluator.coord_at_value(dofs, 24, global_coords, 3, local_coords, 3);

  cout << "local_coords[0] = " << local_coords[0] << endl;
  cout << "local_coords[1] = " << local_coords[1] << endl;
  cout << "local_coords[2] = " << local_coords[2] << endl;

  // Test dxi_local.

  //evaluator.dxi_local();


  return 0;
}
