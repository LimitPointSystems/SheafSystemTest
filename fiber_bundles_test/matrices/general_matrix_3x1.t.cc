
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

/// @example general_matrix_3x1.t.cc
/// Test driver for class general_matrix_3x1.

#include "assert_contract.h"
#include "general_matrix_1x2.h"
#include "general_matrix_1x3.h"
#include "general_matrix_3x1.h"
#include "general_matrix_3x2.h"
#include "general_matrix_3x3.h"
#include "std_iostream.h"

using namespace fiber_bundle;

//==============================================================================
//==============================================================================

///
void test_general_matrix_3x1()
{
  cout << "============================================================" << '\n'
       << "  test_general_matrix_3x1:" << '\n'
       << "============================================================"
       << endl;

  general_matrix_3x1<double> m;
  m[0][0] =  1;
  m[1][0] =  2;
  m[2][0] =  3;

  cout << "m = " << endl;
  cout << m << endl;

  // Transpose:

  general_matrix_1x3<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Multiply by a scalar.

  general_matrix_3x1<double> m2 = m.multiply(2.0); 
  cout << "m2 = m.multiply(2.0:" << endl;
  cout << m2 << endl;

  // Matrix multiply.

  general_matrix_1x2<double> m1x2;
  m1x2[0][0] = 1;  m1x2[0][1] = 2; 

  cout << "m1x2 = " << endl;
  cout << m1x2 << endl;

  general_matrix_3x2<double> mm3x2 = m.multiply(m1x2);
  cout << "mm3x2 = m.multiply(m1x2):" << endl;
  cout << mm3x2 << endl;

  general_matrix_1x3<double> m1x3;
  m1x3[0][0] = 1;  m1x3[0][1] = 2;  m1x3[0][2] = 3; 

  cout << "m1x3 = " << endl;
  cout << m1x3 << endl;

  general_matrix_3x3<double> mm3x3 = m.multiply(m1x3);
  cout << "mm3x3 = m.multiply(m1x3):" << endl;
  cout << mm3x3 << endl;

  //============================================================================

  // Miscellaneous.

  // general_matrix_3x1<double>::assign(double const&)

  general_matrix_3x1<double> lgm;
  lgm.assign(123.0);

  //operator T* ();

  double* lcomp(lgm);

  //operator const T* () const;

  const general_matrix_3x1<double> lgm_const = lgm;

  const double* lcomp_const(lgm_const);

  //============================================================================

}

///
int main()
{
  test_general_matrix_3x1();

  return 0;
}

