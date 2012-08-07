// $RCSfile: trilinear_3d.t.cc,v $ $Revision: 1.14 $ $Date: 2012/03/01 00:40:39 $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example evaluators/trilinear_3d.t.cc
/// Test case for class trilinear_3d

#include "trilinear_3d.h"
#include "assert_contract.h"
#include "std_iostream.h"

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
