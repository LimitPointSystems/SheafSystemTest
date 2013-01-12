//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example evaluators/quadratic_3d.t.cc
/// Test case for class quadratic_3d

#include "quadratic_3d.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

typedef section_evaluator::dof_type dof_type;

int main(int argc, char* argv[])
{
  cout << "Testing quadratic_3d" << endl;

  quadratic_3d evaluator;

  dof_type dofs[] = { 0.0, 0.0, 0.0,
                      1.0, 0.0, 0.0,
                      0.0, 1.0, 0.0,
                      0.0, 0.0, 1.0,
                      1.0/3.0, 0.0, 0.0,
                      0.0, 1.0/3.0, 0.0,
                      0.0, 0.0, 1.0/3.0,
                      1.0/3.0, 1.0/3.0, 0.0,
                      0.0, 1.0/3.0, 1.0, 3.0,
                      1.0/3.0, 1.0/3.0, 1.0/3.0 };

  dof_type m;

  m = evaluator.min(dofs, 6);
  cout << "min = " << m << endl;

  m = evaluator.max(dofs, 6);
  cout << "max = " << m << endl;

  //========================================================================


  double local_coords[] = { 0.25, 0.25, 0.25 };
  //double local_coords[] = { 0.0, 0.0, 0.0 };

  evaluator.basis_at_coord(local_coords, 3);

  for(int i=0; i<10; ++i)
    cout << "basis_values[" << i << "] = " << evaluator.basis_values()[i] << endl;

  //   // Test value_at_coord.

  //   // Single component version.

  //   dof_type x_dofs[] = { 0, 1, 0, 0 };
  //   dof_type y_dofs[] = { 0, 0, 1, 0 };
  //   dof_type z_dofs[] = { 0, 0, 0, 1 };

  //   dof_type x_value = evaluator.value_at_coord(x_dofs, 4, local_coords, 3);

  //   cout << "x_value = " << x_value << endl;

  //   dof_type y_value = evaluator.value_at_coord(y_dofs, 4, local_coords, 3);

  //   cout << "y_value = " << y_value << endl;

  //   dof_type z_value = evaluator.value_at_coord(z_dofs, 4, local_coords, 3);

  //   cout << "y_value = " << y_value << endl;

  //   // Multiple component version.

  //   dof_type values[3];

  //   evaluator.value_at_coord(dofs, 12, local_coords, 3, values, 3);

  //   cout << "x_value = " << values[0] << endl;
  //   cout << "y_value = " << values[1] << endl;
  //   cout << "z_value = " << values[2] << endl;

  //   // Test coord_at_value.

  //   dof_type global_coords[] = { 0.25, 0.25, 0.25 };

  //   evaluator.coord_at_value(dofs, 12, global_coords, 3, local_coords, 3);

  //   cout << "local_coords[0] = " << local_coords[0] << endl;
  //   cout << "local_coords[1] = " << local_coords[1] << endl;
  //   cout << "local_coords[2] = " << local_coords[2] << endl;

  //========================================================================

  return 0;
}
