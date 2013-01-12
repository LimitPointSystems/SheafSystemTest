//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example evaluators/constant_segment.t.cc
/// Test case for class constant_segment

#include "constant_segment.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

typedef section_evaluator::dof_type dof_type;

int main(int argc, char* argv[])
{
  cout << "Testing constant_segment" << endl;

  constant_segment evaluator;
  int ldb = evaluator.db();
  int ldl = evaluator.dl();
  const int ldf = 2;
  const size_type ldofs_ub = 2; // = ldl*ldf

  dof_type dofs[ldofs_ub] = { 1, 3 };

  dof_type m;

  m = evaluator.min(dofs, ldofs_ub);
  cout << "min = " << m << endl;

  m = evaluator.max(dofs, ldofs_ub);
  cout << "max = " << m << endl;

  dof_type local_coords[] = { 0.0 };

  evaluator.basis_at_coord(local_coords, ldb);

  for(int i=0; i<ldl; ++i)
    cout << "basis_values[" << i << "] = " << evaluator.basis_values()[i] << endl;

  // Test value_at_coord.

  // Single component version.

  dof_type* x_dofs = &(dofs[0]);
  dof_type* y_dofs = &(dofs[1]);

  dof_type x_value = evaluator.value_at_coord(x_dofs, ldl, local_coords, ldb);

  cout << "x_value = " << x_value << endl;

  dof_type y_value = evaluator.value_at_coord(y_dofs, ldl, local_coords, ldb);

  cout << "y_value = " << y_value << endl;

  // Multiple component version.

  dof_type values[ldf];

  //cout << "sizeof(values) = " << sizeof(values) << endl;

  evaluator.value_at_coord(dofs, ldofs_ub, local_coords, ldb, values, ldf);

  cout << "x_value = " << values[0] << endl;
  cout << "y_value = " << values[1] << endl;

  // Test dxi_local

  dof_type lresult_dofs[ldofs_ub];

  evaluator.dxi_local(0, dofs, ldofs_ub, lresult_dofs, ldofs_ub);

  cout << "dofs of partial derivative w.r.t. 0-th local coordinate: ";
  for(int i=0; i<ldofs_ub; ++i)
  {
    cout << "  " << lresult_dofs[i];
  }
  cout << endl;


  return 0;
}
