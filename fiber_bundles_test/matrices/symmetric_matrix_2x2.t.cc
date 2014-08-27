
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

/// @example symmetric_matrix_2x2.t.cc
/// Test driver for class symmetric_matrix_2x2.

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "general_matrix_1x2.h"
#include "general_matrix_2x1.h"
#include "general_matrix_2x2.h"
#include "general_matrix_2x3.h"
#include "symmetric_matrix_2x2.h"
#include "std_iostream.h"

using namespace std;
using namespace fiber_bundle;

///
void test_symmetric_matrix_2x2()
{
  cout << "============================================================" << '\n'
       << "  test_symmetric_matrix_2x2:" << '\n'
       << "============================================================"
       << endl;

  symmetric_matrix_2x2<double> m;
  m[0][0] =  4;  m[0][1] = -2; 
                 m[1][1] =  3; 

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

  symmetric_matrix_2x2<double> im = m.inverse();
  cout << "m.inverse():" << endl;
  cout << im << endl;

  // Transpose:

  symmetric_matrix_2x2<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Adjoint:

  symmetric_matrix_2x2<double> am = m.adjoint();
  cout << "am = m.adjoint():" << endl;
  cout << am << endl;

  // Multiply by a scalar.

  symmetric_matrix_2x2<double> am2 = am.multiply(1.0/det);
  cout << "am2 = am.multiply(1.0/determinant):" << endl; 
  cout << am2 << endl;

  // Diagonalize.

  symmetric_matrix_2x2<double> md;
  md = m.diagonalization();
  cout << "md = m.diagonalization():" << endl;
  cout << md << endl;

  // Identity:

  symmetric_matrix_2x2<double> mi = m.identity(); 
  cout << "mi = m.identity():" << endl;
  cout << mi << endl;

  // Conversion to a general matrix.

  general_matrix_2x2<double> gm2x2 = m;
  cout << "general_matrix_2x2<double> gm2x2 = m:" << endl;
  cout << gm2x2 << endl;

  // Matrix multiply.

  cout << "m.multiply(im):" << endl;
  general_matrix_2x2<double> mm = m.multiply(im);
  cout << mm << endl;

  cout << "m.multiply(mm):" << endl;
  general_matrix_2x2<double> mmm = m.multiply(mm);
  cout << mmm << endl;

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


  // symmetric_matrix_2x2<double>::assign(double const&)

  symmetric_matrix_2x2<double> lsm;
  lsm.assign(123.0);

  //bool is_positive_definite() const

  bool lis_positive_definite = lsm.is_positive_definite();
  cout << "lis_positive_definite = " << boolalpha
       << lis_positive_definite << endl;

  //operator T* ();

  double* lcomp(lsm);

  //operator const T* () const;

  const symmetric_matrix_2x2<double> lsm_const = lsm;

  const double* lcomp_const(lsm_const);

  //============================================================================

}

///
int main()
{
  test_symmetric_matrix_2x2();

  return 0;
}

