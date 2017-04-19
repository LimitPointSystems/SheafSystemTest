
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

/// Test driver for functions in tolerance_comparison.h

#include "SheafSystem/tolerance_comparison.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_iostream.h"

using namespace std;
using namespace sheaf;

int
main(int argc, char* argv[])
{
  
  cout << boolalpha;
  
  // Test float comparision.

  float lf0 = 0.0f;
  float lf1 = 1.0f;
  float lf2 = 1.0e+32;
  float lf3 = 1.0e-32;

  float lftol = 1.0e-06;
  
  // Test absolute comparison with 0.0f.

  cout << "0.0 == 0.0 default tolerance= " << a_eql_0(lf0) << endl;
  cout << "1.0 == 0.0 default tolerance = " << a_eql_0(lf1) << endl;

  cout << "0.0 == 0.0 specified tolerance= " << a_eql_0(lf0, lftol) << endl;
  cout << "1.0 == 0.0 specified tolerance= " << a_eql_0(lf1, lftol) << endl;
  
  // Test absolute comparison with 1.0f.

  cout << "0.0 == 1.0 default tolerance= " << a_eql_1(lf0) << endl;
  cout << "1.0 == 1.0 default tolerance = " << a_eql_1(lf1) << endl;

  cout << "0.0 == 1.0 specified tolerance= " << a_eql_1(lf0, lftol) << endl;
  cout << "1.0 == 1.0 specified tolerance= " << a_eql_1(lf1, lftol) << endl;
  
  // Test relative comparison of pair.

  cout << "lf2 == lf2 default tolerance= " << r_eql(lf2, lf2) << endl;
  cout << "lf2 == lf3 default tolerance = " << r_eql(lf2, lf3) << endl;

  cout << "lf2 == lf2 specified tolerance= " << r_eql(lf2, lf2, lftol) << endl;
  cout << "lf2 == lf3 specified tolerance= " << r_eql(lf2, lf3, lftol) << endl;
  
  // Test combined comparison of pair.

  cout << "lf2 == lf2 default tolerance= " << c_eql(lf2, lf2) << endl;
  cout << "lf2 == lf3 default tolerance = " << c_eql(lf2, lf3) << endl;

  cout << "lf2 == lf2 specified tolerance= " << c_eql(lf2, lf2, lftol) << endl;
  cout << "lf2 == lf3 specified tolerance= " << c_eql(lf2, lf3, lftol) << endl;

  
  // Test double comparision.

  double ld0 = 0.0;
  double ld1 = 1.0;
  double ld2 = 1.0e+64;
  double ld3 = 1.0e-64;

  double ldtol = 1.0e-12;
  
  // Test absolute comparison with 0.0.

  cout << "0.0 == 0.0 default tolerance= " << a_eql_0(ld0) << endl;
  cout << "1.0 == 0.0 default tolerance = " << a_eql_0(ld1) << endl;

  cout << "0.0 == 0.0 specified tolerance= " << a_eql_0(ld0, ldtol) << endl;
  cout << "1.0 == 0.0 specified tolerance= " << a_eql_0(ld1, ldtol) << endl;
  
  // Test absolute comparison with 1.0.

  cout << "0.0 == 1.0 default tolerance= " << a_eql_1(ld0) << endl;
  cout << "1.0 == 1.0 default tolerance = " << a_eql_1(ld1) << endl;

  cout << "0.0 == 1.0 specified tolerance= " << a_eql_1(ld0, ldtol) << endl;
  cout << "1.0 == 1.0 specified tolerance= " << a_eql_1(ld1, ldtol) << endl;
  
  // Test relative comparison of pair.

  cout << "ld2 == ld2 default tolerance= " << r_eql(ld2, ld2) << endl;
  cout << "ld2 == ld3 default tolerance = " << r_eql(ld2, ld3) << endl;

  cout << "ld2 == ld2 specified tolerance= " << r_eql(ld2, ld2, ldtol) << endl;
  cout << "ld2 == ld3 specified tolerance= " << r_eql(ld2, ld3, ldtol) << endl;
  
  // Test combined comparison of pair.

  cout << "ld2 == ld2 default tolerance= " << c_eql(ld2, ld2) << endl;
  cout << "ld2 == ld3 default tolerance = " << c_eql(ld2, ld3) << endl;

  cout << "ld2 == ld2 specified tolerance= " << c_eql(ld2, ld2, ldtol) << endl;
  cout << "ld2 == ld3 specified tolerance= " << c_eql(ld2, ld3, ldtol) << endl;

  return 0;
}

