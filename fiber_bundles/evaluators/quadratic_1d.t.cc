// $RCSfile: quadratic_1d.t.cc,v $ $Revision: 1.14 $ $Date: 2012/03/01 00:40:38 $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example evaluators/quadratic_1d.t.cc
/// Test case for class quadratic_1d

#include "quadratic_1d.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

typedef section_evaluator::dof_type dof_type;

int main(int argc, char* argv[])
{
  cout << "Testing linear_2d" << endl;

  quadratic_1d evaluator;

  dof_type dofs[] = { 1, 2, 3 };

  dof_type m;

  m = evaluator.min(dofs, 3);
  cout << "min = " << m << endl;

  m = evaluator.max(dofs, 3);
  cout << "max = " << m << endl;

  double local_coords[] = { 0.0 };

  evaluator.basis_at_coord(local_coords, 1);

  for(int i=0; i<3; ++i)
    cout << "basis_values[" << i << "] = " << evaluator.basis_values()[i] << endl;

  // Test value_at_coord.

  dof_type x_value = evaluator.value_at_coord(dofs, 3, local_coords, 1);

  cout << "x_value = " << x_value << endl;

  // Multiple component version.

  dof_type values[1];

  evaluator.value_at_coord(dofs, 3, local_coords, 1, values, 1);

  cout << "x_value = " << values[0] << endl;

  // Test coord_at_value.

  dof_type global_coords[] = { 1.25 };

  evaluator.coord_at_value(dofs, 3, global_coords, 1, local_coords, 1);

  cout << "local_coords[0] = " << local_coords[0] << endl;

  return 0;
}
