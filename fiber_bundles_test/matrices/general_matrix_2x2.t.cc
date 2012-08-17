
// $RCSfile: general_matrix_2x2.t.cc,v $ $Revision: 1.6 $ $Date: 2012/03/01 00:40:52 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example general_matrix_2x2.t.cc
/// Test driver for class general_matrix_2x2.

#include "antisymmetric_matrix_2x2.h"
#include "assert_contract.h"
#include "general_matrix_1x2.h"
#include "general_matrix_2x1.h"
#include "general_matrix_2x2.h"
#include "general_matrix_2x3.h"
#include "std_iostream.h"
#include "symmetric_matrix_2x2.h"
#include "std_cstring.h"

using namespace fiber_bundle;

///
void test_general_matrix_2x2()
{
  cout << "============================================================" << '\n'
       << "  test_general_matrix_2x2:" << '\n'
       << "============================================================"
       << endl;

  general_matrix_2x2<double> m;
  m[0][0] =  4; m[0][1] = -2;
  m[1][0] = -2; m[1][1] =  3;

  cout << "m = " << endl;
  cout << m << endl;

  // Trace:

  double ltrace = m.trace();
  cout << "trace =  " << ltrace << endl;
  cout << endl;

  // Determinant:

  double det = m.determinant();
  cout << "determinant = " << det << endl;
  cout << endl;

  // Inverse:

  general_matrix_2x2<double> im = m.inverse();
  cout << "m.inverse():" << endl;
  cout << im << endl;

  // Transpose:

  general_matrix_2x2<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Adjoint:

  general_matrix_2x2<double> am = m.adjoint();
  cout << "am = m.adjoint():" << endl;
  cout << am << endl;

  // Multiply by a scalar.

  general_matrix_2x2<double> am2 = am.multiply(1.0/det);
  cout << "am2 = am.multiply(1.0/determinant):" << endl; 
  cout << am2 << endl;

  // Diagonalize.

  general_matrix_2x2<double> md;
  md = m.diagonalization();
  cout << "md = m.diagonalization():" << endl;
  cout << md << endl;

  // Identity:

  general_matrix_2x2<double> mi = m.identity(); 
  cout << "m.identity():" << endl;
  cout << mi << endl;

  // Antisymmetric part.

  general_matrix_2x2<double> mx = m;
  mx[0][1] = 3;

  cout << "mx = " << endl;
  cout << mx << endl;

  antisymmetric_matrix_2x2<double> ap = mx.antisymmetric_part();
  cout << "mx.antisymmetric_part():" << endl;
  cout << ap << endl;

  // Symmetric part.

  symmetric_matrix_2x2<double> sp = mx.symmetric_part();
  cout << "mx.symmetric_part():" << endl;
  cout << sp << endl;

  // Matrix multiply.

  cout << "m.multiply(im):" << endl;
  general_matrix_2x2<double> mm = m.multiply(im);
  cout << mm << endl;

  general_matrix_2x1<double> m2x1;
  m2x1[0][0] = 1;
  m2x1[1][0] = 2;

  cout << "m2x1 = " << endl;
  cout << m2x1 << endl;

  cout << "m.multiply(m2x1):" << endl;
  general_matrix_2x1<double> mm2x1 = m.multiply(m2x1);
  cout << mm2x1 << endl;

  general_matrix_2x3<double> m2x3;
  m2x3[0][0] = 1;   m2x3[0][1] = 2;  m2x3[0][2] = 3;
  m2x3[1][0] = 4;   m2x3[1][1] = 5;  m2x3[1][2] = 6;

  cout << "m2x3 = " << endl;
  cout << m2x3 << endl;

  cout << "m.multiply(m2x3):" << endl;
  general_matrix_2x3<double> mm2x3 = m.multiply(m2x3);
  cout << mm2x3 << endl;

  //============================================================================

  // Extract row.

  general_matrix_1x2<double> row_1 = m.row(1);
  cout << "general_matrix_1x2<double> row_1 = m.row(1):" << endl;
  cout << row_1 << endl;

  // Extract column.

  general_matrix_2x1<double> col_1 = m.column(1);
  cout << "general_matrix_2x1<double> col_1 = m.column(1):" << endl;
  cout << col_1 << endl;

  //============================================================================

  // Test conversions:

  general_matrix_2x2<double> t1(m);
  cout << "general_matrix_2x2<double> t1(m):" << endl;
  cout << t1 << endl;

  general_matrix_2x2<double> t2 = t1;
  cout << "general_matrix_2x2<double> t2 = t1:" << endl;
  cout << t2 << endl;

  general_matrix_2x2<double> t3;
  t3 = t1;
  cout << "general_matrix_2x2<double> t3; t3 = t1:" << endl;
  cout << t3 << endl;

  general_matrix_2x2<double> t4(sp);
  cout << "general_matrix_2x2<double> t4(sp):" << endl;
  cout << t4 << endl;

  general_matrix_2x2<double> t5(ap);
  cout << "general_matrix_2x2<double> t5(ap):" << endl;
  cout << t5 << endl;

  //============================================================================

  // Test. Do we really have a POD type.

  memcpy(&t1, &t4, sizeof(t1));
  cout <<"memcpy(&t1, &t4, sizeof(t1)):" << endl;
  cout << t1 << endl;

  //============================================================================

}

///
int main()
{
  test_general_matrix_2x2();

  return 0;
}
