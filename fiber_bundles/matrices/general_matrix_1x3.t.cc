
// $RCSfile: general_matrix_1x3.t.cc,v $ $Revision: 1.6 $ $Date: 2012/03/01 00:40:52 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example general_matrix_1x3.t.cc
/// Test driver for class general_matrix_1x3.

#include "assert_contract.h"
#include "general_matrix_1x3.h"
#include "general_matrix_1x2.h"
#include "general_matrix_3x1.h"
#include "general_matrix_3x2.h"
#include "general_matrix_3x3.h"
#include "std_iostream.h"


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

}

///
int main()
{
  test_general_matrix_1x3();

  return 0;
}

