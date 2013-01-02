
// $RCSfile: antisymmetric_matrix_2x2.t.cc,v $ $Revision: 1.6 $ $Date: 2012/03/01 00:40:51 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example antisymmetric_matrix_2x2.t.cc
/// Test driver for class antisymmetric_matrix_2x2.

#include "assert_contract.h"
#include "antisymmetric_matrix_2x2.h"
#include "general_matrix_1x2.h"
#include "general_matrix_2x1.h"
#include "general_matrix_2x2.h"
#include "general_matrix_2x3.h"
#include "std_iostream.h"
#include "std_iomanip.h"

using namespace fiber_bundle;

///
void test_antisymmetric_matrix_2x2()
{
  cout << "============================================================" << '\n'
       << "  test_antisymmetric_matrix_2x2:" << '\n'
       << "============================================================"
       << endl;

  antisymmetric_matrix_2x2<double> m;
  m[0][1] = -2; 

  cout << "m = " << endl;
  cout << m << endl;

  // Trace:

  double ltrace = m.trace();
  cout << "trace =  " << ltrace << endl;

  // Determinant:

  double det = m.determinant();
  cout << "determinant = " << det << endl;
  cout << endl;

  // Inverse:

  antisymmetric_matrix_2x2<double> im = m.inverse();
  cout << "m.inverse():" << endl;
  cout << im << endl;

  // Transpose:

  antisymmetric_matrix_2x2<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Adjoint:

  antisymmetric_matrix_2x2<double> am = m.adjoint();
  cout << "am = m.adjoint():" << endl;
  cout << am << endl;

  // Multiply by a scalar.

  antisymmetric_matrix_2x2<double> am2 = am.multiply(1.0/det);
  cout << "am2 = am.multiply(1.0/determinant):" << endl; 
  cout << am2 << endl;

  // Diagonalize.

  // Not implemented for antisymmetric matrices (eigenvalues are pure complex).

  // Identity:

  // Not defined for antisymmetric matrices (all diagonal elements are 0).

  // Conversion to a general matrix.

  general_matrix_2x2<double> gm2x2 = m;
  cout << "general_matrix_2x2<double> gm2x2 = m:" << endl;
  cout << gm2x2 << endl;

  // Matrix multiply.

  cout << "mx.multiply(im):" << endl;
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

  // Miscellaneous.


  // antisymmetric_matrix_2x2<double>::assign(double const&)

  antisymmetric_matrix_2x2<double> lam;
  lam.assign(123.0);

  //bool is_positive_definite() const

  bool lis_positive_definite = lam.is_positive_definite();
  cout << "lis_positive_definite = " << boolalpha
       << lis_positive_definite << endl;

  //void multiply(const general_matrix_2x2<T>& xother,
  //              general_matrix_2x2<T>& xresult) const;

  general_matrix_2x2<double> lgm;
  lgm[0][0] =  4; lgm[0][1] = -2;
  lgm[1][0] = -2; lgm[1][1] =  3;

  general_matrix_2x2<double> lresult;

  lam.multiply(lgm, lresult);

  general_matrix_2x2<double> lresult2 = lam.multiply(lgm);

  //operator T* ();

  double* lcomp(lam);

  //operator const T* () const;

  const antisymmetric_matrix_2x2<double> lam_const = lam;

  const double* lcomp_const(lam_const);

  //============================================================================

}

///
int main()
{
  test_antisymmetric_matrix_2x2();

  return 0;
}

