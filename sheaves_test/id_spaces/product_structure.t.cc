
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

/// @example product_structure.t.cc
/// Test driver for the product structure classes.

#include "ij_product_structure.h"
#include "ijk_product_structure.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "std_iostream.h"

using namespace std;
using namespace sheaf;

namespace
{
  ///
  /// Print the ordinal and 2-tuple values.
  ///
  void print_product(pod_index_type xordinal,
		     pod_index_type xi,
		     pod_index_type xj)
  {
    cout << "    " << xordinal << " [" << xi << ", " << xj << "]";
  }

  /// Print the ordinal and 3-tuple values.
  ///
  void print_product(pod_index_type xordinal,
		     pod_index_type xi,
		     pod_index_type xj,
		     pod_index_type xk)
  {
    cout << "    " << xordinal << " [" << xi << ", " << xj << ", " << xk << "]";
  }

  ///
  /// Test abstract product interface.
  ///
  void test_abstract(abstract_product_structure& xproduct,
		     size_t* xubs, size_type xd)
  {
    // Test put_ub().

    xproduct.put_ubs(reinterpret_cast<size_type*>(xubs));

    pod_index_type* ltuple = new pod_index_type[xd];
    pod_index_type lordinal;
    for(pod_index_type i=0; i<xproduct.ordinal_ub(); ++i)
    {
      xproduct.tuple(i, ltuple);
      xproduct.ordinal(ltuple, lordinal);

      if(lordinal != i)
      {
	cerr << "ERROR: tuple and ordinal does not match for ordinal index: " << i << endl;
	assertion(lordinal == i);
      }
    }
  }

  ///
  /// Test the ij_product_structure.
  ///
  void test_ij(size_type xi_ub, size_type xj_ub)
  {
    ij_product_structure lproduct(xi_ub, xj_ub);

    pod_index_type ordinal, i, j;

    // Test the tuple to ordinal coversion.

    cout << "2-tuple to ordinal conversion: " << endl;
    for(i=0; i < xi_ub; ++i)
    {
      for(j=0; j < xj_ub; ++j)
      {
	lproduct.ordinal(i, j, ordinal);

	print_product(ordinal, i, j);
      }
    }
    cout << endl << endl;

    // Test the oridinal to tuple conversion.

    cout << "ordinal to 2-tuple conversion: " << endl;
    for(ordinal=0; ordinal < lproduct.ordinal_ub(); ++ordinal)
    {
      lproduct.tuple(ordinal, i, j);

      print_product(ordinal, i, j);
    }
    cout << endl << endl;

    // Test copy constructor.

    ij_product_structure lproduct2(lproduct);

    // Test put_ubs(xi_ub, xj_ub).

    lproduct2.put_ubs(xi_ub+1, xj_ub+1);

    // Test the abstract interface.

    size_type* lubs = new size_type[2];
    lubs[0] = xi_ub+2;
    lubs[1] = xj_ub+2;
    test_abstract(lproduct, reinterpret_cast<size_t*>(lubs), 2);
  }

  ///
  /// Test the ijk_product_structure.
  ///
  void test_ijk(size_type xi_ub, size_type xj_ub, size_type xk_ub)
  {
    ijk_product_structure lproduct(xi_ub, xj_ub, xk_ub);

    pod_index_type ordinal, i, j, k;

    // Test the tuple to ordinal coversion.

    cout << "3-tuple to ordinal conversion: " << endl;
    for(i=0; i < xi_ub; ++i)
    {
      for(j=0; j < xj_ub; ++j)
      {
	for(k=0; k < xk_ub; ++k)
	{
	  lproduct.ordinal(i, j, k, ordinal);

	  print_product(ordinal, i, j, k);
	}
      }
    }
    cout << endl << endl;

    // Test the oridinal to tuple conversion.

    cout << "ordinal to 3-tuple conversion: " << endl;
    for(ordinal=0; ordinal < lproduct.ordinal_ub(); ++ordinal)
    {
      lproduct.tuple(ordinal, i, j, k);

      print_product(ordinal, i, j, k);
    }
    cout << endl << endl;

    // Test copy constructor.

    ijk_product_structure lproduct2(lproduct);

    // Test put_ubs(xi_ub, xj_ub).

    lproduct2.put_ubs(xi_ub+1, xj_ub+1, xk_ub+1);

    // Test the abstract interface.

    size_type* lubs = new size_type[3];
    lubs[0] = xi_ub+2;
    lubs[1] = xj_ub+2;
    lubs[2] = xk_ub+2;
    test_abstract(lproduct, reinterpret_cast<size_t*>(lubs), 3);
  }
}

int main( int argc, char* argv[])
{
  if((argc > 1) && (argv[1][0] == '-'))
  {
    cout << "Usage: product_structure.t.t [i_ub] [j_ub] [k_ub]" << endl;
    return 0;
  }

  size_t i_ub = argc > 1 ? atoi(argv[1]) : 4;
  size_t j_ub = argc > 2 ? atoi(argv[2]) : 3;
  size_t k_ub = argc > 3 ? atoi(argv[3]) : 2;

  test_ij(i_ub, j_ub);
  test_ijk(i_ub, j_ub, k_ub);
  
  // Done.

  return 0;
}

  
