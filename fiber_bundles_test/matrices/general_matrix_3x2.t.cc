

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example general_matrix_3x2.t.cc
/// Test driver for class general_matrix_3x2.

#include "assert_contract.h"
#include "general_matrix_1x2.h"
#include "general_matrix_2x1.h"
#include "general_matrix_2x2.h"
#include "general_matrix_2x3.h"
#include "general_matrix_3x1.h"
#include "general_matrix_3x2.h"
#include "general_matrix_3x3.h"
#include "std_iostream.h"

using namespace fiber_bundle;

///
void test_general_matrix_3x2()
{
  cout << "============================================================" << '\n'
       << "  test_general_matrix_3x2:" << '\n'
       << "============================================================"
       << endl;

  general_matrix_3x2<double> m;
  m[0][0] =  1; m[0][1] = 2;
  m[1][0] =  3; m[1][1] = 4;
  m[2][0] =  5; m[2][1] = 6;

  cout << "m = " << endl;
  cout << m << endl;

  // Transpose:

  general_matrix_2x3<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Multiply by a scalar.

  general_matrix_3x2<double> m2 = m.multiply(2.0);
  cout << "m2 = m.multiply(2.0):" << endl; 
  cout << m2 << endl;

  // Matrix multiply.

  cout << "m.multiply(tm):" << endl;
  general_matrix_3x3<double> mm3x3 = m.multiply(tm);
  cout << mm3x3 << endl;

  general_matrix_2x2<double> m2x2;
  m2x2[0][0] =  4; m2x2[0][1] = -2;
  m2x2[1][0] = -2; m2x2[1][1] =  3;

  cout << "m2x2 = " << endl;
  cout << m2x2 << endl;

  general_matrix_3x2<double> mm3x2  = m.multiply(m2x2);

  cout << "mm3x2 = " << endl;
  cout << mm3x2 << endl;

  general_matrix_2x1<double> m2x1;
  m2x1[0][0] = 1;
  m2x1[1][0] = 2;

  cout << "m2x1 = " << endl;
  cout << m2x1 << endl;

  general_matrix_3x1<double> mm3x1  = m.multiply(m2x1);

  cout << "mm3x1 = " << endl;
  cout << mm3x1 << endl;

  //============================================================================

  // Extract row.

  general_matrix_1x2<double> row_1 = m.row(1);
  cout << "general_matrix_1x2<double> row_1 = m.row(1):" << endl;
  cout << row_1 << endl;

  // Extract column.

  general_matrix_3x1<double> col_1 = m.column(1);
  cout << "general_matrix_3x1<double> col_1 = m.column(1):" << endl;
  cout << col_1 << endl;

  //============================================================================

  // Miscellaneous.

  // general_matrix_3x2<double>::assign(double const&)

  general_matrix_3x2<double> lgm;
  lgm.assign(123.0);

  //operator T* ();

  double* lcomp(lgm);

  //operator const T* () const;

  const general_matrix_3x2<double> lgm_const = lgm;

  const double* lcomp_const(lgm_const);

  //============================================================================

}

///
int main()
{
  test_general_matrix_3x2();

  return 0;
}

