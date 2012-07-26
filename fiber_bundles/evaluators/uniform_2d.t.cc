// $RCSfile: uniform_2d.t.cc,v $ $Revision: 1.13 $ $Date: 2012/03/01 00:40:39 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example evaluators/uniform_2d.t.cc
/// Test case for class uniform_2d

#include "uniform_2d.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

typedef section_evaluator::dof_type dof_type;

int main(int argc, char* argv[])
{
  cout << "Testing uniform_2d" << endl;

  uniform_2d evaluator;

  dof_type dofs[] = { 1, 2, 3, 2, 3, 5, 1, 5 }; //interleaved

  dof_type m;

  m = evaluator.min(dofs, 8);
  cout << "min = " << m << endl;

  m = evaluator.max(dofs, 8);
  cout << "max = " << m << endl;

  //double local_coords[] = { 1.0, 1.0 };
  double local_coords[] = { -1.0, 0.0 };

  evaluator.basis_at_coord(local_coords, 2);

  for(int i=0; i<4; ++i)
    cout << "basis_values[" << i << "] = " << evaluator.basis_values()[i] << endl;

  // Test value_at_coord.

  // Single component version.

  dof_type x_dofs[] = { 1, 3, 3, 1 };
  dof_type y_dofs[] = { 2, 2, 5, 5 };

  dof_type x_value = evaluator.value_at_coord(x_dofs, 4, local_coords, 2);

  cout << "x_value = " << x_value << endl;

  dof_type y_value = evaluator.value_at_coord(y_dofs, 4, local_coords, 2);

  cout << "y_value = " << y_value << endl;

  // Multiple component version.

  // Interleaved dofs.

  dof_type values[2];

  //cout << "sizeof(values) = " << sizeof(values) << endl;

  evaluator.value_at_coord(dofs, 8, local_coords, 2, values, 2);

  cout << "x_value = " << values[0] << endl;
  cout << "y_value = " << values[1] << endl;

  // Test coord_at_value.

  dof_type global_coords[] = { 2, 4 };

  evaluator.coord_at_value(dofs, 8, global_coords, 2, local_coords, 2);

  cout << "local_coords[0] = " << local_coords[0] << endl;
  cout << "local_coords[1] = " << local_coords[1] << endl;

  // Test dxi_local.

  //evaluator.dxi_local();

  return 0;
}
