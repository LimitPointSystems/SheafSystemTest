
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class ragged_array.

#include "ragged_array.h"
#include "test_sheaves.impl.h"

using namespace sheaf;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // bool

  print_header("Begin testing ragged_array<bool>");
  ltest &= test_any_facet<ragged_array<bool> >();
  ltest &= test_rc_any_facet<ragged_array<bool> >();
  ltest &= test_ragged_array_facet<bool>();
  print_footer("End testing block<bool>");

  // char

  print_header("Begin testing ragged_array<char>");
  ltest &= test_any_facet<ragged_array<char> >();
  ltest &= test_rc_any_facet<ragged_array<char> >();
  ltest &= test_ragged_array_facet<char>();
  print_footer("End testing block<char>");

  // signed char

  print_header("Begin testing ragged_array<signed char>");
  ltest &= test_any_facet<ragged_array<signed char> >();
  ltest &= test_rc_any_facet<ragged_array<signed char> >();
  ltest &= test_ragged_array_facet<signed char>();
  print_footer("End testing block<signed char>");

  // short int

  print_header("Begin testing ragged_array<short int>");
  ltest &= test_any_facet<ragged_array<short int> >();
  ltest &= test_rc_any_facet<ragged_array<short int> >();
  ltest &= test_ragged_array_facet<short int>();
  print_footer("End testing block<short int>");

  // int

  print_header("Begin testing ragged_array<int>");
  ltest &= test_any_facet<ragged_array<int> >();
  ltest &= test_rc_any_facet<ragged_array<int> >();
  ltest &= test_ragged_array_facet<int>();
  print_footer("End testing block<int>");

  // long int

  print_header("Begin testing ragged_array<long int>");
  ltest &= test_any_facet<ragged_array<long int> >();
  ltest &= test_rc_any_facet<ragged_array<long int> >();
  ltest &= test_ragged_array_facet<long int>();
  print_footer("End testing block<long int>");

  // long long int

  print_header("Begin testing ragged_array<long long int>");
  ltest &= test_any_facet<ragged_array<long long int> >();
  ltest &= test_rc_any_facet<ragged_array<long long int> >();
  ltest &= test_ragged_array_facet<long long int>();
  print_footer("End testing block<long long int>");

  // unsigned char

  print_header("Begin testing ragged_array<unsigned char>");
  ltest &= test_any_facet<ragged_array<unsigned char> >();
  ltest &= test_rc_any_facet<ragged_array<unsigned char> >();
  ltest &= test_ragged_array_facet<unsigned char>();
  print_footer("End testing block<unsigned char>");

  // unsigned short int

  print_header("Begin testing ragged_array<unsigned short int>");
  ltest &= test_any_facet<ragged_array<unsigned short int> >();
  ltest &= test_rc_any_facet<ragged_array<unsigned short int> >();
  ltest &= test_ragged_array_facet<unsigned short int>();
  print_footer("End testing block<unsigned short int>");

  // unsigned int

  print_header("Begin testing ragged_array<unsigned int>");
  ltest &= test_any_facet<ragged_array<unsigned int> >();
  ltest &= test_rc_any_facet<ragged_array<unsigned int> >();
  ltest &= test_ragged_array_facet<unsigned int>();
  print_footer("End testing block<unsigned int>");

  // unsigned long int

  print_header("Begin testing ragged_array<unsigned long int>");
  ltest &= test_any_facet<ragged_array<unsigned long int> >();
  ltest &= test_rc_any_facet<ragged_array<unsigned long int> >();
  ltest &= test_ragged_array_facet<unsigned long int>();
  print_footer("End testing block<unsigned long int>");

  // unsigned long long int

  print_header("Begin testing ragged_array<unsigned long long int>");
  ltest &= test_any_facet<ragged_array<unsigned long long int> >();
  ltest &= test_rc_any_facet<ragged_array<unsigned long long int> >();
  ltest &= test_ragged_array_facet<unsigned long long int>();
  print_footer("End testing block<unsigned long long int>");

  // float

  print_header("Begin testing ragged_array<float>");
  ltest &= test_any_facet<ragged_array<float> >();
  ltest &= test_rc_any_facet<ragged_array<float> >();
  ltest &= test_ragged_array_facet<float>();
  print_footer("End testing block<float>");

  // double

  print_header("Begin testing ragged_array<double>");
  ltest &= test_any_facet<ragged_array<double> >();
  ltest &= test_rc_any_facet<ragged_array<double> >();
  ltest &= test_ragged_array_facet<double>();
  print_footer("End testing block<double>");

  // long double

  print_header("Begin testing ragged_array<long double>");
  ltest &= test_any_facet<ragged_array<long double> >();
  ltest &= test_rc_any_facet<ragged_array<long double> >();
  ltest &= test_ragged_array_facet<long double>();
  print_footer("End testing block<long double>");


  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

