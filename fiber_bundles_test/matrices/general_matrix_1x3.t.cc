
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

/// @example general_matrix_1x3.t.cc
/// Test driver for class general_matrix_1x3.

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/general_matrix_1x3.h"
#include "SheafSystem/general_matrix_1x2.h"
#include "SheafSystem/general_matrix_3x1.h"
#include "SheafSystem/general_matrix_3x2.h"
#include "SheafSystem/general_matrix_3x3.h"
#include "SheafSystem/std_iostream.h"


using namespace std;
using namespace fiber_bundle;

///
void test_general_matrix_1x3()
{
  cout << "============================================================" << '\n'
       << "  test_general_matrix_1x3:" << '\n'
       << "============================================================"
       << endl;

  general_matrix_1x3<double> m;
  m[0][0] =  1; m[0][1] =  2; m[0][2] =  3;

  cout << "m = " << endl;
  cout << m << endl;

  // Transpose:

  general_matrix_3x1<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Multiply by a scalar.

  general_matrix_1x3<double> m2 = m.multiply(2.0);
  cout << "m2 = m.multiply(2.0):" << endl; 
  cout << m2 << endl;

  // Matrix multiply.

  general_matrix_3x3<double> m3x3;
  m3x3[0][0] = 1;  m3x3[0][1] = 2;  m3x3[0][2] = 3; 
  m3x3[1][0] = 4;  m3x3[1][1] = 5;  m3x3[1][2] = 6; 
  m3x3[2][0] = 7;  m3x3[2][1] = 8;  m3x3[2][2] = 9; 

  cout << "m3x3 = " << endl;
  cout << m3x3 << endl;

  general_matrix_1x3<double> mm1x3 = m.multiply(m3x3);
  cout << "mm1x3 = m.multiply(m3x3):" << endl;
  cout << mm1x3 << endl;

  general_matrix_3x2<double> m3x2;
  m3x2[0][0] = 1;  m3x2[0][1] = 2;
  m3x2[1][0] = 3;  m3x2[1][1] = 4;
  m3x2[2][0] = 5;  m3x2[2][1] = 6;

  cout << "m3x2 = " << endl;
  cout << m3x2 << endl;

  general_matrix_1x2<double> mm1x2 = m.multiply(m3x2);
  cout << "mm1x2 = m.multiply(m3x2):" << endl;
  cout << mm1x2 << endl;


  //============================================================================

  // Miscellaneous.


  // general_matrix_1x3<double>::assign(double const&)

  general_matrix_1x3<double> lgm;
  lgm.assign(123.0);

  general_matrix_3x1<double> lgm3x1;
  lgm.assign(2.0);

  // void multiply(const general_matrix_3x1<T>& xother, T& xresult) const

  double lresult;
  lgm.multiply(lgm3x1, lresult);
  
  // T multiply(const general_matrix_3x1<T>& xother) const

  lresult = lgm.multiply(lgm3x1);

  //operator T* ();

  double* lcomp(lgm);

  //operator const T* () const;

  const general_matrix_1x3<double> lgm_const = lgm;

  const double* lcomp_const(lgm_const);

  //============================================================================

}

///
int main()
{
  test_general_matrix_1x3();

  return 0;
}

