
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @example antisymmetric_matrix_3x3.t.cc
/// Test driver for class antisymmetric_matrix_3x3.

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "antisymmetric_matrix_3x3.h"
#include "general_matrix_1x3.h"
#include "general_matrix_2x3.h"
#include "general_matrix_3x1.h"
#include "general_matrix_3x2.h"
#include "general_matrix_3x3.h"
#include "symmetric_matrix_3x3.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

///
void test_antisymmetric_matrix_3x3()
{
  cout << "============================================================" << '\n'
       << "  test_antisymmetric_matrix_3x3:" << '\n'
       << "============================================================"
       << endl;

  antisymmetric_matrix_3x3<double> m;
  m[0][1] = 2;   m[0][2] = 3;
                 m[1][2] = 4; 

  cout << "m = " << endl;
  cout << m << endl;

  // Trace:

  double ltrace = m.trace();
  cout << "trace =  " << ltrace << endl;

  // Determinant:
  // Note that the determinant of all n=odd antisymmetric
  // matrices is zero.

  double det = m.determinant();
  cout << "determinant = " << det << endl;
  cout << endl;

//   // Inverse:

//   antisymmetric_matrix_3x3<double> im = m.inverse();
//   cout << "m.inverse():" << endl;
//   cout << im << endl;

  // Transpose:

  antisymmetric_matrix_3x3<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Adjoint:

  general_matrix_3x3<double> am = m.adjoint();
  cout << "am = m.adjoint():" << endl;
  cout << am << endl;

  // Multiply by a scalar.

//   general_matrix_3x3<double> am2 = am.multiply(1.0/det);
//   cout << "am2 = am.multiply(1.0/determinant):" << endl; 
//   cout << am2 << endl;

  general_matrix_3x3<double> am2 = am.multiply(2.0);
  cout << "am2 = am.multiply(2.0):" << endl; 
  cout << am2 << endl;

  // Diagonalize.

  // Not implemented for antisymmetric matrices (eigenvalues are pure complex).

  // Identity:

  // Not defined for antisymmetric matrices (all diagonal elements are 0).

  // Conversion to a general matrix.

  general_matrix_3x3<double> gm3x3 = m;
  cout << "general_matrix_3x3<double> gm3x3 = m:" << endl;
  cout << gm3x3 << endl;

  // Matrix multiply.

  cout << "mx.multiply(tm):" << endl;
  general_matrix_3x3<double> mm = m.multiply(tm);
  cout << mm << endl;

  general_matrix_3x2<double> m3x2;
  m3x2[0][0] =  1; m3x2[0][1] = 2;
  m3x2[1][0] =  3; m3x2[1][1] = 4;
  m3x2[2][0] =  5; m3x2[2][1] = 6;

  cout << "m3x2 = " << endl;
  cout << m3x2 << endl;

  cout << "m.multiply(m3x2):" << endl;
  general_matrix_3x2<double> mm3x2 = m.multiply(m3x2);
  cout << mm3x2 << endl;

  general_matrix_3x1<double> m3x1;
  m3x1[0][0] =  1;
  m3x1[1][0] =  3;
  m3x1[2][0] =  5;

  cout << "m3x1 = " << endl;
  cout << m3x1 << endl;

  cout << "m.multiply(m3x1):" << endl;
  general_matrix_3x1<double> mm3x1 = m.multiply(m3x1);
  cout << mm3x1 << endl;

  general_matrix_2x3<double> m2x3;
  m2x3[0][0] = 1; m2x3[0][1] = 2; m2x3[0][2] = 3;
  m2x3[1][0] = 4; m2x3[1][1] = 5; m2x3[1][2] = 6;

  cout << "m2x3 = " << endl;
  cout << m2x3 << endl;

  cout << "m2X3.multiply(m):" << endl;
  general_matrix_2x3<double> mm2x3 = m2x3.multiply(m);
  cout << mm2x3 << endl;

  general_matrix_1x3<double> m1x3;
  m1x3[0][0] = 1; m1x3[0][1] = 2; m1x3[0][2] = 3;

  cout << "m1x3 = " << endl;
  cout << m1x3 << endl;

  cout << "m1x3.multiply(m):" << endl;
  general_matrix_1x3<double> mm1x3 = m1x3.multiply(m);
  cout << mm1x3 << endl;


  //============================================================================

  // Extract row.

  general_matrix_1x3<double> row_1 = m.row(1);
  cout << "general_matrix_1x3<double> row_1 = m.row(1):" << endl;
  cout << row_1 << endl;

  // Extract column.

  general_matrix_3x1<double> col_1 = m.column(1);
  cout << "general_matrix_3x1<double> col_1 = m.column(1):" << endl;
  cout << col_1 << endl;

  //============================================================================

  // Miscellaneous.

  // antisymmetric_matrix_3x3<double>::assign(double const&)

  antisymmetric_matrix_3x3<double> lam;
  lam.assign(123.0);

  // No inverse for an antisymmetric matrix with n odd;
  // determinant is always 0.

  ////void inverse(antisymmetric_matrix_3x3<T>& xresult) const;

  //antisymmetric_matrix_3x3<double> lresult;
  //lam.inverse(lresult);

  ////antisymmetric_matrix_3x3<T> inverse() const;

  //antisymmetric_matrix_3x3<double> linverse = lam.inverse();

  //bool is_positive_definite() const

  bool lis_positive_definite = lam.is_positive_definite();
  cout << "lis_positive_definite = " << boolalpha
       << lis_positive_definite << endl;

  //void multiply(const T& xscalar, antisymmetric_matrix_3x3<T>& xresult) const;

  antisymmetric_matrix_3x3<double> lresult;
  lam.multiply(2.0, lresult);

  //antisymmetric_matrix_3x3<T> multiply(const T& xscalar) const;

  antisymmetric_matrix_3x3<double> lmultiply = lam.multiply(2.0);

  //void multiply(const general_matrix_3x3<T>& xother,
  //              general_matrix_3x3<T>& xresult) const;

  general_matrix_3x3<double> lgm;
  lgm[0][0] =  10; lgm[0][1] = -10; lgm[0][2] =   0;
  lgm[1][0] = -10; lgm[1][1] =  20; lgm[1][2] = -10;
  lgm[2][0] =   0; lgm[2][1] =   0; lgm[2][2] =  10;

  general_matrix_3x3<double> lresult2;

  lam.multiply(lgm, lresult2);

  general_matrix_3x3<double> lresult3 = lam.multiply(lgm);

  //operator T* ();

  double* lcomp(lam);

  //operator const T* () const;

  const antisymmetric_matrix_3x3<double> lam_const = lam;

  const double* lcomp_const(lam_const);

  //============================================================================

}

///
int main()
{
  test_antisymmetric_matrix_3x3();

  return 0;
}

