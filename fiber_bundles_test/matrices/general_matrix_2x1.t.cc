
// $RCSfile: general_matrix_2x1.t.cc,v $ $Revision: 1.6 $ $Date: 2012/03/01 00:40:52 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example general_matrix_2x1.t.cc
/// Test driver for class general_matrix_2x1.

#include "assert_contract.h"
#include "general_matrix_1x2.h"
#include "general_matrix_1x3.h"
#include "general_matrix_2x1.h"
#include "general_matrix_2x2.h"
#include "general_matrix_2x3.h"
#include "std_iostream.h"

using namespace fiber_bundle;

//==============================================================================
//==============================================================================

///
void test_general_matrix_2x1()
{
  cout << "============================================================" << '\n'
       << "  test_general_matrix_2x1:" << '\n'
       << "============================================================"
       << endl;

  general_matrix_2x1<double> m;
  m[0][0] =  1;
  m[1][0] =  2;

  cout << "m = " << endl;
  cout << m << endl;

  // Transpose:

  general_matrix_1x2<double> tm = m.transpose();
  cout << "tm = m.transpose():" << endl;
  cout << tm << endl;

  // Multiply by a scalar.

  general_matrix_2x1<double> m2 = m.multiply(2.0);
  cout << "m2 = m.multiply(2.0):" << endl;
  cout << m2 << endl;

  // Matrix multiply.

  general_matrix_1x2<double> m1x2;
  m1x2[0][0] = 1;  m1x2[0][1] = 2; 

  cout << "m1x2 = " << endl;
  cout << m1x2 << endl;

  general_matrix_2x2<double> mm2x2 = m.multiply(m1x2);
  cout << "mm2x2 = m.multiply(m1x2):" << endl;
  cout << mm2x2 << endl;

  general_matrix_1x3<double> m1x3;
  m1x3[0][0] = 1;  m1x3[0][1] = 2;  m1x3[0][2] = 3; 

  cout << "m1x3 = " << endl;
  cout << m1x3 << endl;

  general_matrix_2x3<double> mm2x3 = m.multiply(m1x3);
  cout << "mm2x3 = m.multiply(m1x3):" << endl;
  cout << mm2x3 << endl;

}

///
int main()
{
  test_general_matrix_2x1();

  return 0;
}

