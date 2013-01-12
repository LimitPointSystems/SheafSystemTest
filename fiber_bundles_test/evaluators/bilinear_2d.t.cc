//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example evaluators/bilinear_2d.t.cc
/// Test case for class bilinear_2d

#include "bilinear_2d.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;


typedef section_evaluator::dof_type dof_type;

int main(int argc, char* argv[])
{
  cout << "Testing bilinear_2d" << endl;

  bilinear_2d evaluator;

  dof_type dofs[] = { 1, 3, 9, 2, 7, 9, 2, 8 }; //interleaved
  //dof_type dofs[] = { 1, 1, 9, 1, 9, 9, 1, 9 }; //interleaved

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

  dof_type x_dofs[] = { 1, 9, 7, 2 };
  dof_type y_dofs[] = { 3, 2, 9, 8 };

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

  //dof_type global_coords[] = { 5.0, 5.0 };
  dof_type global_coords[] = { 7.0, 9.0  };
  //dof_type global_coords[] = {1.0, 3.0  };

  evaluator.coord_at_value(dofs, 8, global_coords, 2, local_coords, 2);

  cout << "local_coords[0] = " << local_coords[0] << endl;
  cout << "local_coords[1] = " << local_coords[1] << endl;

  // Test dxi_local.

  //evaluator.dxi_local();

  // Test determinant/jacobian

  {
    dof_type l_dofs[] = { 1.0, 1.0, 2.0, 1.0, 2.0, 2.0, 1.0, 2.0 }; //interleaved
    const double l_coords[] =
      {
        1.0, 1.0
      };
    //double det = evaluator.calc_determinant(l_dofs, 8, l_coords);

    //cout << "det = " << det << endl;

    double integrals[1];
    const dof_type integrand[4] =
      {
        1.0, 1.0, 1.0, 1.0
      };

    //evaluator.integrate(l_dofs, 8, 1.0, integrals, 4);
    evaluator.integrate(l_dofs, 8, 2, integrand, 4, integrals, 1);

    cout << integrals[0] << endl;
    //for(int k=0; k<4; ++k)
    //  cout << integrals[k] << endl;
  }

  return 0;
}
