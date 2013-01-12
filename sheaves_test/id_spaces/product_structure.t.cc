
// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example product_structure.t.cc
/// Test driver for the product structure classes.

#include "ij_product_structure.h"
#include "ijk_product_structure.h"

#include "assert_contract.h"
#include "error_message.h"
#include "std_iostream.h"

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

  
