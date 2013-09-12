
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

/// @example general_matrix_3x3.t.cc
/// Test driver for class general_matrix_3x3.

#include "antisymmetric_matrix_3x3.h"
#include "assert_contract.h"
#include "general_matrix_1x3.h"
#include "general_matrix_2x3.h"
#include "general_matrix_3x1.h"
#include "general_matrix_3x2.h"
#include "general_matrix_3x3.h"
#include "std_iostream.h"
#include "symmetric_matrix_3x3.h"

using namespace fiber_bundle;

///
void test_general_matrix_3x3()
{
  cout << "============================================================" << '\n'
       << "  test_general_matrix_3x3:" << '\n'
       << "============================================================"
       << endl;

  general_matrix_3x3<double> m;
  m[0][0] =  10; m[0][1] = -10; m[0][2] =   0;
  m[1][0] = -10; m[1][1] =  20; m[1][2] = -10;
  m[2][0] =   0; m[2][1] =   0; m[2][2] =  10;

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

  general_matrix_3x3<double> im = m.inverse();
  cout << "m.inverse():" << endl;
  cout << im << endl;

  // Transpose:

  general_matrix_3x3<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Adjoint:

  general_matrix_3x3<double> am = m.adjoint();
  cout << "am = m.adjoint():" << endl;
  cout << am << endl;

  // Multiply by a scalar.

  general_matrix_3x3<double> am2 = am.multiply(1.0/det);
  cout << "am2 = am.multiply(1.0/determinant):" << endl; 
  cout << am2 << endl;

  // Diagonalize.

  general_matrix_3x3<double> md;
  md = m.diagonalization();
  cout << "md = m.diagonalization():" << endl;
  cout << md << endl;

  cout << "m.is_diagonal():  " << (m.is_diagonal() ? "true" : "false") << endl;
  cout << "md.is_diagonal(): " << (md.is_diagonal() ? "true" : "false") << endl;
  cout << endl;

  // Identity:

  general_matrix_3x3<double> mi = m.identity(); 
  cout << "m.identity():" << endl;
  cout << mi << endl;
 
  cout << "m.is_identity():  " << (m.is_identity() ? "true" : "false") << endl;
  cout << "mi.is_identity(): " << (mi.is_identity() ? "true" : "false") << endl;
  cout << endl;

  // Antisymmetric part.

  general_matrix_3x3<double> mx = m;
  mx[0][2] = 3;

  cout << "mx = " << endl;
  cout << mx << endl;

  antisymmetric_matrix_3x3<double> ap = mx.antisymmetric_part();
  cout << "mx.antisymmetric_part():" << endl;
  cout << ap << endl;

  // Symmetric part.

  symmetric_matrix_3x3<double> sp = mx.symmetric_part();
  cout << "mx.symmetric_part():" << endl;
  cout << sp << endl;

  // Matrix multiply.

  cout << "m.multiply(im):" << endl;
  general_matrix_3x3<double> mm = m.multiply(im);
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


  //general_matrix_3x3<double> p1;
  //p1[0][0] = 1; p1[0][1] = 2; p1[0][2] = 3;
  //p1[1][0] = 2; p1[1][1] = 4; p1[1][2] = 5;
  //p1[2][0] = 3; p1[2][1] = 5; p1[2][2] = 6;

  symmetric_matrix_3x3<double> p1;
  p1[0][0] = 1; p1[0][1] = 2; p1[0][2] = 3;
                p1[1][1] = 4; p1[1][2] = 5;
                              p1[2][2] = 6;


  general_matrix_3x3<double> p2;
  p2[0][0] = -0.736976; p2[0][1] =  0.591009; p2[0][2] = 0.327985;
  p2[1][0] = -0.327985; p2[1][1] = -0.736976; p2[1][2] = 0.591009;
  p2[2][0] =  0.591009; p2[2][1] =  0.327985; p2[2][2] = 0.736976;

  general_matrix_3x3<double> p3 = p1.multiply(p2); 

  cout << "p1:" << endl << p1 << endl;
  cout << "p2:" << endl << p2 << endl;
  cout << "p3:" << endl << p3 << endl;

  //============================================================================

  // Miscellaneous.

  // general_matrix_3x3<double>::assign(double const&)

  general_matrix_3x3<double> lgm;
  lgm.assign(123.0);

  lgm[0][0] =  10; lgm[0][1] = -10; lgm[0][2] =   0;
  lgm[1][0] = -10; lgm[1][1] =  20; lgm[1][2] = -10;
  lgm[2][0] =   0; lgm[2][1] =   0; lgm[2][2] =  10;

  //bool is_positive_definite() const

  bool lis_positive_definite = lgm.is_positive_definite();
  cout << "lis_positive_definite = " << boolalpha
       << lis_positive_definite << endl;

  //bool is_symmetric() const

  bool lis_symmetric = lgm.is_symmetric();
  cout << "lis_symmetric = " << boolalpha
       << lis_symmetric << endl;

  //bool is_antisymmetric() const

  bool lis_antisymmetric = lgm.is_antisymmetric();
  cout << "lis_antisymmetric = " << boolalpha
       << lis_antisymmetric << endl;

  //operator T* ();

  double* lcomp(lgm);

  //operator const T* () const;

  const general_matrix_3x3<double> lgm_const = lgm;

  const double* lcomp_const(lgm_const);

  //============================================================================

}

///
int main()
{
  test_general_matrix_3x3();

  return 0;
}

