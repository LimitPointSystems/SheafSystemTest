
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

/// @example symmetric_matrix_3x3.t.cc
/// Test driver for class symmetric_matrix_3x3.

#include "ComLimitPoint/sheaf/assert_contract.h"
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
void test_symmetric_matrix_3x3()
{
  cout << "============================================================" << '\n'
       << "  test_symmetric_matrix_3x3:" << '\n'
       << "============================================================"
       << endl;

  symmetric_matrix_3x3<double> m;
  m[0][0] = 1;  m[0][1] = 2;  m[0][2] = 3;
                m[1][1] = 4;  m[1][2] = 5;
                              m[2][2] = 6;

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

  symmetric_matrix_3x3<double> im = m.inverse();
  cout << "m.inverse():" << endl;
  cout << im << endl;

  // Transpose:

  symmetric_matrix_3x3<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Adjoint:

  symmetric_matrix_3x3<double> am = m.adjoint();
  cout << "am = m.adjoint():" << endl;
  cout << am << endl;

  // Multiply by a scalar.

  symmetric_matrix_3x3<double> am2 = am.multiply(1.0/det);
  cout << "am2 = am.multiply(1.0/determinant):" << endl; 
  cout << am2 << endl;

  // Diagonalize.

  symmetric_matrix_3x3<double> md;
  md = m.diagonalization();
  cout << "md = m.diagonalization():" << endl;
  cout << md << endl;

  // Identity:

  symmetric_matrix_3x3<double> mi = m.identity(); 
  cout << "mi = m.identity():" << endl;
  cout << mi << endl;

  // Conversion to a general matrix.

  general_matrix_3x3<double> gm3x3 = m;
  cout << "general_matrix_3x3<double> gm3x3 = m:" << endl;
  cout << gm3x3 << endl;

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

  // Miscellaneous.


  // symmetric_matrix_3x3<double>::assign(double const&)

  symmetric_matrix_3x3<double> lsm;
  lsm.assign(123.0);

  lsm[0][0] = 2;  lsm[0][1] =-1;  lsm[0][2] = 0;
                  lsm[1][1] = 2;  lsm[1][2] =-1;
                                  lsm[2][2] = 2;

  //bool is_positive_definite() const

  bool lis_positive_definite = lsm.is_positive_definite();
  cout << "lis_positive_definite = " << boolalpha
       << lis_positive_definite << endl;

  //operator T* ();

  double* lcomp(lsm);

  //operator const T* () const;

  const symmetric_matrix_3x3<double> lsm_const = lsm;

  const double* lcomp_const(lsm_const);

  //============================================================================

}

///
int main()
{
  test_symmetric_matrix_3x3();

  return 0;
}

