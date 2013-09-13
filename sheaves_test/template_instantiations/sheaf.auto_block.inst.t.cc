
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
/// @example
/// Unit test driver for template class auto_block instantiations.

#include "auto_block.h"
#include "test_sheaves.impl.h"

using namespace sheaf;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // bool

  print_header("Begin testing auto_block<bool>");
  ltest &= test_auto_block_facet_all<bool>();
  ltest &= test_auto_block_facet_equal_all<bool>();
  ltest &= test_auto_block_facet_equal_equal_all<bool>();
  ltest &= test_auto_block_facet_insertion_all<bool>();
  ltest &= test_auto_block_facet_deep_size_all<bool>();
  print_footer("End testing auto_block<bool>");

  // char

  print_header("Begin testing auto_block<char>");
  ltest &= test_auto_block_facet_all<char>();
  ltest &= test_auto_block_facet_equal_all<char>();
  ltest &= test_auto_block_facet_equal_equal_all<char>();
  ltest &= test_auto_block_facet_insertion_all<char>();
  ltest &= test_auto_block_facet_deep_size_all<char>();
  print_footer("End testing auto_block<char>");
 
  // signed char

  print_header("Begin testing auto_block<signed char>");
  ltest &= test_auto_block_facet_all<signed char>();
  ltest &= test_auto_block_facet_equal_all<signed char>();
  ltest &= test_auto_block_facet_equal_equal_all<signed char>();
  ltest &= test_auto_block_facet_insertion_all<signed char>();
  ltest &= test_auto_block_facet_deep_size_all<signed char>();
  print_footer("End testing auto_block<signed char>");

  // short int

  print_header("Begin testing auto_block<short int>");
  ltest &= test_auto_block_facet_all<short int>();
  ltest &= test_auto_block_facet_equal_all<short int>();
  ltest &= test_auto_block_facet_equal_equal_all<short int>();
  ltest &= test_auto_block_facet_insertion_all<short int>();
  ltest &= test_auto_block_facet_deep_size_all<short int>();
  print_footer("End testing auto_block<short int>");

  // int

  print_header("Begin testing auto_block<int>");
  ltest &= test_auto_block_facet_all<int>();
  ltest &= test_auto_block_facet_equal_all<int>();
  ltest &= test_auto_block_facet_equal_equal_all<int>();
  ltest &= test_auto_block_facet_insertion_all<int>();
  ltest &= test_auto_block_facet_deep_size_all<int>();
  print_footer("End testing auto_auto_block<int>");


  // long int

  print_header("Begin testing auto_block<long int>");
  ltest &= test_auto_block_facet_all<long int>();
  ltest &= test_auto_block_facet_equal_all<long int>();
  ltest &= test_auto_block_facet_equal_equal_all<long int>();
  ltest &= test_auto_block_facet_insertion_all<long int>();
  ltest &= test_auto_block_facet_deep_size_all<long int>();
  print_footer("End testing auto_block<long int>");

  // long long int

  print_header("Begin testing auto_block<long long int>");
  ltest &= test_auto_block_facet_all<long long int>();
  ltest &= test_auto_block_facet_equal_all<long long int>();
  ltest &= test_auto_block_facet_equal_equal_all<long long int>();
  ltest &= test_auto_block_facet_insertion_all<long long int>();
  ltest &= test_auto_block_facet_deep_size_all<long long int>();
  print_footer("End testing auto_block<long long int>");

  // unsigned char

  print_header("Begin testing auto_block<unsigned char>");
  ltest &= test_auto_block_facet_all<unsigned char>();
  ltest &= test_auto_block_facet_equal_all<unsigned char>();
  ltest &= test_auto_block_facet_equal_equal_all<unsigned char>();
  ltest &= test_auto_block_facet_insertion_all<unsigned char>();
  ltest &= test_auto_block_facet_deep_size_all<unsigned char>();
  print_footer("End testing auto_block<unsigned char>");

  // unsigned short int

  print_header("Begin testing auto_block<unsigned short int>");
  ltest &= test_auto_block_facet_all<unsigned short int>();
  ltest &= test_auto_block_facet_equal_all<unsigned short int>();
  ltest &= test_auto_block_facet_equal_equal_all<unsigned short int>();
  ltest &= test_auto_block_facet_insertion_all<unsigned short int>();
  ltest &= test_auto_block_facet_deep_size_all<unsigned short int>();
  print_footer("End testing auto_block<unsigned short int>");

  // unsigned int

  print_header("Begin testing auto_block<unsigned int>");
  ltest &= test_auto_block_facet_all<unsigned int>();
  ltest &= test_auto_block_facet_equal_all<unsigned int>();
  ltest &= test_auto_block_facet_equal_equal_all<unsigned int>();
  ltest &= test_auto_block_facet_insertion_all<unsigned int>();
  ltest &= test_auto_block_facet_deep_size_all<unsigned int>();
  print_footer("End testing auto_block<unsigned int>");

  // unsigned long int

  print_header("Begin testing auto_block<unsigned long int>");
  ltest &= test_auto_block_facet_all<unsigned long int>();
  ltest &= test_auto_block_facet_equal_all<unsigned long int>();
  ltest &= test_auto_block_facet_equal_equal_all<unsigned long int>();
  ltest &= test_auto_block_facet_insertion_all<unsigned long int>();
  ltest &= test_auto_block_facet_deep_size_all<unsigned long int>();
  print_footer("End testing auto_block<unsigned long int>");

  // unsigned long long int

  print_header("Begin testing auto_block<unsigned long long int>");
  ltest &= test_auto_block_facet_all<unsigned long long int>();
  ltest &= test_auto_block_facet_equal_all<unsigned long long int>();
  ltest &= test_auto_block_facet_equal_equal_all<unsigned long long int>();
  ltest &= test_auto_block_facet_insertion_all<unsigned long long int>();
  ltest &= test_auto_block_facet_deep_size_all<unsigned long long int>();
  print_footer("End testing auto_block<unsigned long long int>");

  // float

  print_header("Begin testing auto_block<float>");
  ltest &= test_auto_block_facet_all<float>();
  ltest &= test_auto_block_facet_equal_all<float>();
  ltest &= test_auto_block_facet_equal_equal_all<float>();
  ltest &= test_auto_block_facet_insertion_all<float>();
  ltest &= test_auto_block_facet_deep_size_all<float>();
  print_footer("End testing auto_block<float>");

  // double

  print_header("Begin testing auto_block<double>");
  ltest &= test_auto_block_facet_all<double>();
  ltest &= test_auto_block_facet_equal_all<double>();
  ltest &= test_auto_block_facet_equal_equal_all<double>();
  ltest &= test_auto_block_facet_insertion_all<double>();
  ltest &= test_auto_block_facet_deep_size_all<double>();
  print_footer("End testing auto_block<double>");

  // double*

  print_header("Begin testing auto_block<double*>");
  ltest &= test_auto_block_facet_all<double*>();
  ltest &= test_auto_block_facet_equal_all<double*>();
  ltest &= test_auto_block_facet_equal_equal_all<double*>();
  ltest &= test_auto_block_facet_insertion_all<double*>();
  ltest &= test_auto_block_facet_deep_size_all<double*>();
  print_footer("End testing auto_block<double*>");

  // long double

  print_header("Begin testing auto_block<long double>");
  ltest &= test_auto_block_facet_all<long double>();
  ltest &= test_auto_block_facet_equal_all<long double>();
  ltest &= test_auto_block_facet_equal_equal_all<long double>();
  ltest &= test_auto_block_facet_insertion_all<long double>();
  ltest &= test_auto_block_facet_deep_size_all<long double>();
  print_footer("End testing auto_block<long double>");

  // string

  print_header("Begin testing auto_block<string>");
  ltest &= test_auto_block_facet_un<string>();
  ltest &= test_auto_block_facet_equal_un<string>();
  ltest &= test_auto_block_facet_insertion_un<string>();
  ltest &= test_auto_block_facet_deep_size_un<string>();
  print_footer("End testing auto_block<string>");

  // string*

  print_header("Begin testing auto_block<string*>");
  ltest &= test_auto_block_facet_all<string*>();
  //ltest &= test_auto_block_facet_equal<string*>();
  //ltest &= test_auto_block_facet_equal_equal<string*>();
  ltest &= test_auto_block_facet_insertion_all<string*>();
  //ltest &= test_auto_block_facet_deep_size<string*>();
  print_footer("End testing auto_block<string*>");

  // arg_list::arg_type

  print_header("Begin testing auto_block<arg_list::arg_type>");
  ltest &= test_auto_block_facet_un<arg_list::arg_type>();
  ltest &= test_auto_block_facet_equal_un<arg_list::arg_type>();
  ltest &= test_auto_block_facet_equal_equal_un<arg_list::arg_type>();
  ltest &= test_auto_block_facet_insertion_un<arg_list::arg_type>();
  ltest &= test_auto_block_facet_deep_size_un<arg_list::arg_type>();
  print_footer("End testing auto_block<arg_list::arg_type>");

  // arg_list

  print_header("Begin testing auto_block<arg_list>");
  ltest &= test_auto_block_facet_un<arg_list>();
  //ltest &= test_auto_block_facet_equal_un<arg_list>();
  //ltest &= test_auto_block_facet_equal_equal_un<arg_list>();
  ltest &= test_auto_block_facet_insertion_un<arg_list>();
  //ltest &= test_auto_block_facet_deep_size_un<arg_list>();
  print_footer("End testing auto_block<arg_list>");

  // block<double>

  print_header("Begin testing auto_block<block<double> >");
  ltest &= test_auto_block_facet_all<block<double> >();
  ltest &= test_auto_block_facet_equal_all<block<double> >();
  ltest &= test_auto_block_facet_equal_equal_all<block<double> >();
  ltest &= test_auto_block_facet_insertion_all<block<double> >();
  ltest &= test_auto_block_facet_deep_size_all<block<double> >();
  print_footer("End testing _auto_block<block<double> >");

  // block<double>*

  print_header("Begin testing auto_block<block<double>* >");
  ltest &= test_auto_block_facet_all<block<double>* >();
  ltest &= test_auto_block_facet_equal_all<block<double>* >();
  ltest &= test_auto_block_facet_equal_equal_all<block<double>* >();
  ltest &= test_auto_block_facet_insertion_all<block<double>* >();
  //ltest &= test_auto_block_facet_deep_size_all<block<double>* >();
  ltest &= test_auto_block_facet_deep_size_zero<block<double>* >();
  print_footer("End testing _auto_block<block<double>* >");

  // block<int>*

  print_header("Begin testing auto_block<block<int>* >");
  ltest &= test_auto_block_facet_all<block<int>* >();
  ltest &= test_auto_block_facet_equal_all<block<int>* >();
  ltest &= test_auto_block_facet_equal_equal_all<block<int>* >();
  ltest &= test_auto_block_facet_insertion_all<block<int>* >();
  //ltest &= test_auto_block_facet_deep_size_all<block<int>* >();
  ltest &= test_auto_block_facet_deep_size_zero<block<int>* >();
  print_footer("End testing _auto_block<block<int>* >");

  // primitive_value

  print_header("Begin testing auto_block<primitive_value>");
  ltest &= test_auto_block_facet_all<primitive_value>();
  ltest &= test_auto_block_facet_equal_all<primitive_value>();
  ltest &= test_auto_block_facet_equal_equal_all<primitive_value>();
  ltest &= test_auto_block_facet_insertion_all<primitive_value>();
  ltest &= test_auto_block_facet_deep_size_all<primitive_value>();
  print_footer("End testing auto_block<primitive_value>");

  // primitive_attributes

  print_header("Begin testing auto_block<primitive_attributes>");
  ltest &= test_auto_block_facet_un<primitive_attributes>();
  //ltest &= test_auto_block_facet_equal_un<primitive_attributes>();
  //ltest &= test_auto_block_facet_equal_equal_un<primitive_attributes>();
  ltest &= test_auto_block_facet_insertion_un<primitive_attributes>();
  //ltest &= test_auto_block_facet_deep_size_un<primitive_attributes>();
  print_footer("End testing auto_block<primitive_attributes>");

  // poset_path

  print_header("Begin testing auto_block<poset_path>");
  ltest &= test_auto_block_facet_un<poset_path>();
  ltest &= test_auto_block_facet_equal_un<poset_path>();
  ltest &= test_auto_block_facet_equal_equal_un<poset_path>();
  ltest &= test_auto_block_facet_insertion_un<poset_path>();
  ltest &= test_auto_block_facet_deep_size_un<poset_path>();
  print_footer("End testing auto_block<poset_path>");

  // schema_descriptor

  print_header("Begin testing auto_block<schema_descriptor>");
  ltest &= test_auto_block_facet_un<schema_descriptor>();
  ltest &= test_auto_block_facet_equal_un<schema_descriptor>();
  ltest &= test_auto_block_facet_equal_equal_un<schema_descriptor>();
  ltest &= test_auto_block_facet_insertion_un<schema_descriptor>();
  ltest &= test_auto_block_facet_deep_size_un<schema_descriptor>();
  print_footer("End testing auto_block<schema_descriptor>");

  // poset_dof_map*

  print_header("Begin testing auto_block<poset_dof_map*>");
  ltest &= test_auto_block_facet_all<poset_dof_map*>();
  ltest &= test_auto_block_facet_equal_all<poset_dof_map*>();
  ltest &= test_auto_block_facet_equal_equal_all<poset_dof_map*>();
  ltest &= test_auto_block_facet_insertion_all<poset_dof_map*>();
  //ltest &= test_auto_block_facet_deep_size_all<poset_dof_map*>();
  ltest &= test_auto_block_facet_deep_size_zero<poset_dof_map*>();
  print_footer("End testing auto_block<poset_dof_map*>");

  // subposet_state*

  print_header("Begin testing auto_block<subposet_state*>");
  ltest &= test_auto_block_facet_all<subposet_state*>();
  ltest &= test_auto_block_facet_equal_all<subposet_state*>();
  ltest &= test_auto_block_facet_equal_equal_all<subposet_state*>();
  ltest &= test_auto_block_facet_insertion_all<subposet_state*>();
  //ltest &= test_auto_block_facet_deep_size_all<subposet_state*>();
  ltest &= test_auto_block_facet_deep_size_zero<subposet_state*>();
  print_footer("End testing auto_block<subposet_state*>");

  // subposet

  print_header("Begin testing auto_block<subposet>");
  ltest &= test_auto_block_facet_un<subposet>();
  //ltest &= test_auto_block_facet_equal_un<subposet>();
  //ltest &= test_auto_block_facet_equal_equal_un<subposet>();
  ltest &= test_auto_block_facet_insertion_un<subposet>();
  ltest &= test_auto_block_facet_deep_size_un<subposet>();
  print_footer("End testing auto_block<subposet>");

  // poset_state_handle*

  print_header("Begin testing auto_block<poset_state_handle*>");
  ltest &= test_auto_block_facet_all<poset_state_handle*>();
  ltest &= test_auto_block_facet_equal_all<poset_state_handle*>();
  ltest &= test_auto_block_facet_equal_equal_all<poset_state_handle*>();
  ltest &= test_auto_block_facet_insertion_all<poset_state_handle*>();
  //ltest &= test_auto_block_facet_deep_size_all<poset_state_handle*>();
  ltest &= test_auto_block_facet_deep_size_zero<poset_state_handle*>();
  print_footer("End testing auto_block<poset_state_handle*>");

  // explicit_index_space_state*

  print_header("Begin testing auto_block<explicit_index_space_state*>");
  ltest &= test_auto_block_facet_all<explicit_index_space_state*>();
  ltest &= test_auto_block_facet_equal_all<explicit_index_space_state*>();
  ltest &= test_auto_block_facet_equal_equal_all<explicit_index_space_state*>();
  //ltest &= test_auto_block_facet_insertion_all<explicit_index_space_state*>();
  //ltest &= test_auto_block_facet_deep_size_all<explicit_index_space_state*>();
  print_footer("End testing auto_block<explicit_index_space_state*>");

  // index_space_handle*

  print_header("Begin testing auto_block<index_space_handle*>");
  ltest &= test_auto_block_facet_all<index_space_handle*>();
  ltest &= test_auto_block_facet_equal_all<index_space_handle*>();
  ltest &= test_auto_block_facet_equal_equal_all<index_space_handle*>();
  //ltest &= test_auto_block_facet_insertion_all<index_space_handle*>();
  //ltest &= test_auto_block_facet_deep_size_all<index_space_handle*>();
  print_footer("End testing auto_block<index_space_handle*>");

  // mutable_index_space_handle*

  print_header("Begin testing auto_block<mutable_index_space_handle*>");
  ltest &= test_auto_block_facet_all<mutable_index_space_handle*>();
  ltest &= test_auto_block_facet_equal_all<mutable_index_space_handle*>();
  //ltest &= test_auto_block_facet_equal_equal_all<mutable_index_space_handle*>();
  //ltest &= test_auto_block_facet_insertion_all<mutable_index_space_handle*>();
  //ltest &= test_auto_block_facet_deep_size_all<mutable_index_space_handle*>();
  print_footer("End testing auto_block<mutable_index_space_handle*>");

  // list<scoped_index>

  print_header("Begin testing auto_block<list<scoped_index> >");
  ltest &= test_auto_block_facet_un<list<scoped_index> >(); // initialization problem
  //ltest &= test_auto_block_facet_equal_un<list<scoped_index> >();
  //ltest &= test_auto_block_facet_equal_equal_un<list<scoped_index> >();
  //ltest &= test_auto_block_facet_insertion_un<list<scoped_index> >();
  //ltest &= test_auto_block_facet_deep_size_un<list<scoped_index> >();
  print_footer("End testing auto_block<list<scoped_index> >");


  int lresult = ltest ? 0 : 1;


  // Postconditions:

  // Exit:

  return lresult;
}
