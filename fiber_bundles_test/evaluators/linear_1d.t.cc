//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example evaluators/linear_1d.t.cc
/// Test case for class linear_1d

#include "linear_1d.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

typedef section_evaluator::dof_type dof_type;

int main(int argc, char* argv[])
{
  cout << "Testing linear_2d" << endl;

  linear_1d evaluator;

  dof_type dofs[] = { 1, 2 };

  dof_type m;

  m = evaluator.min(dofs, 2);
  cout << "min = " << m << endl;

  m = evaluator.max(dofs, 2);
  cout << "max = " << m << endl;

  double local_coords[] = { 0.5 };

  evaluator.basis_at_coord(local_coords, 1);

  for(int i=0; i<2; ++i)
    cout << "basis_values[" << i << "] = " << evaluator.basis_values()[i] << endl;

  // Test value_at_coord.

  // Single component version.

  dof_type x_dofs[] = { 1, 2 };
  dof_type y_dofs[] = { 2, 1 };

  dof_type x_value = evaluator.value_at_coord(x_dofs, 2, local_coords, 1);

  cout << "x_value = " << x_value << endl;

  dof_type y_value = evaluator.value_at_coord(y_dofs, 2, local_coords, 1);

  cout << "y_value = " << y_value << endl;

  // Multiple component version.

  dof_type values[1];

  //cout << "sizeof(values) = " << sizeof(values) << endl;

  evaluator.value_at_coord(dofs, 2, local_coords, 1, values, 1);

  cout << "x_value = " << values[0] << endl;

  // Test coord_at_value.

  dof_type global_coords[] = { 1.25 };

  evaluator.coord_at_value(dofs, 2, global_coords, 1, local_coords, 1);

  cout << "local_coords[0] = " << local_coords[0] << endl;

  return 0;
}
