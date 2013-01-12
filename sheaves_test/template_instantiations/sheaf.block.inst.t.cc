
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class block instantiations.

#include "block.h"

#include "arg_list.h"
#include "crg_interval.h"
#include "mutable_index_space_handle.h"
#include "poset_dof_map.h"
#include "poset_path.h"
#include "primitive_value.h"
#include "schema_descriptor.h"
#include "subposet.h"
#include "subposet_state.h"
#include "std_list.h"
#include "std_set.h"
#include "test_utils.h"
#include "test_sheaves.impl.h"

using namespace sheaf;
namespace
{

template<typename T>
class block_child : public block<T>
{
public:
  block_child(int xub) : block<T>::block(xub) {}
  ~block_child() {}
};

template<typename T>
bool
test_block_ctors_dtors()
{
  block<T>* lparent = new block<T>(4);
  delete lparent;

  block_child<T>* lchild = new block_child<T>(4);
  delete lchild;

  return true;
}

} // end unnamed namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // bool

  print_header("Begin testing block<bool>");
  ltest &= test_block_ctors_dtors<bool>();
  ltest &= test_block_facet<bool>();
  ltest &= test_block_facet_equal<bool>();
  ltest &= test_block_facet_insertion<bool>();
  ltest &= test_block_facet_deep_size<bool>();
  print_footer("End testing block<bool>");

  // char

  print_header("Begin testing block<char>");
  ltest &= test_block_facet<char>();
  ltest &= test_block_facet_equal<char>();
  ltest &= test_block_facet_insertion<char>();
  ltest &= test_block_facet_deep_size<char>();
  print_footer("End testing block<char>");

  // signed char

  print_header("Begin testing block<signed char>");
  ltest &= test_block_facet<signed char>();
  ltest &= test_block_facet_equal<signed char>();
  ltest &= test_block_facet_insertion<signed char>();
  ltest &= test_block_facet_deep_size<signed char>();
  print_footer("End testing block<signed char>");

  // short int

  print_header("Begin testing block<short int>");
  ltest &= test_block_facet<short int>();
  ltest &= test_block_facet_equal<short int>();
  ltest &= test_block_facet_insertion<short int>();
  ltest &= test_block_facet_deep_size<short int>();
  print_footer("End testing block<short int>");

  // int

  print_header("Begin testing block<int>");
  ltest &= test_block_facet<int>();
  ltest &= test_block_facet_equal<int>();
  ltest &= test_block_facet_insertion<int>();
  ltest &= test_block_facet_deep_size<int>();
  print_footer("End testing block<int>");

  // long int

  print_header("Begin testing block<long int>");
  ltest &= test_block_facet<long int>();
  ltest &= test_block_facet_equal<long int>();
  ltest &= test_block_facet_insertion<long int>();
  ltest &= test_block_facet_deep_size<long int>();
  print_footer("End testing block<long int>");

  // long long int

  print_header("Begin testing block<long long int>");
  ltest &= test_block_facet<long long int>();
  ltest &= test_block_facet_equal<long long int>();
  ltest &= test_block_facet_insertion<long long int>();
  ltest &= test_block_facet_deep_size<long long int>();
  print_footer("End testing block<long long int>");

  // unsigned char

  print_header("Begin testing block<unsigned char>");
  ltest &= test_block_facet<unsigned char>();
  ltest &= test_block_facet_equal<unsigned char>();
  ltest &= test_block_facet_insertion<unsigned char>();
  ltest &= test_block_facet_deep_size<unsigned char>();
  print_footer("End testing block<unsigned char>");

  // unsigned short int

  print_header("Begin testing block<unsigned short int>");
  ltest &= test_block_facet<unsigned short int>();
  ltest &= test_block_facet_equal<unsigned short int>();
  ltest &= test_block_facet_insertion<unsigned short int>();
  ltest &= test_block_facet_deep_size<unsigned short int>();
  print_footer("End testing block<unsigned short int>");

  // unsigned int

  print_header("Begin testing block<unsigned int>");
  ltest &= test_block_facet<unsigned int>();
  ltest &= test_block_facet_equal<unsigned int>();
  ltest &= test_block_facet_insertion<unsigned int>();
  ltest &= test_block_facet_deep_size<unsigned int>();
  print_footer("End testing block<unsigned int>");

  // unsigned long int

  print_header("Begin testing block<unsigned long int>");
  ltest &= test_block_facet<unsigned long int>();
  ltest &= test_block_facet_equal<unsigned long int>();
  ltest &= test_block_facet_insertion<unsigned long int>();
  ltest &= test_block_facet_deep_size<unsigned long int>();
  print_footer("End testing block<unsigned long int>");

  // unsigned long long int

  print_header("Begin testing block<unsigned long long int>");
  ltest &= test_block_facet<unsigned long long int>();
  ltest &= test_block_facet_equal<unsigned long long int>();
  ltest &= test_block_facet_insertion<unsigned long long int>();
  ltest &= test_block_facet_deep_size<unsigned long long int>();
  print_footer("End testing block<unsigned long long int>");

  // float

  print_header("Begin testing block<float>");
  ltest &= test_block_facet<float>();
  ltest &= test_block_facet_equal<float>();
  ltest &= test_block_facet_insertion<float>();
  ltest &= test_block_facet_deep_size<float>();
  print_footer("End testing block<float>");

  // double

  print_header("Begin testing block<double>");
  ltest &= test_block_facet<double>();
  ltest &= test_block_facet_equal<double>();
  ltest &= test_block_facet_insertion<double>();
  ltest &= test_block_facet_deep_size<double>();
  print_footer("End testing block<double>");

  // long double

  print_header("Begin testing block<long double>");
  ltest &= test_block_facet<long double>();
  ltest &= test_block_facet_equal<long double>();
  ltest &= test_block_facet_insertion<long double>();
  ltest &= test_block_facet_deep_size<long double>();
  print_footer("End testing block<long double>");

  // string

  print_header("Begin testing block<string>");
  ltest &= test_block_facet<string>();
  ltest &= test_block_facet_equal<string>();
  ltest &= test_block_facet_insertion<string>();
  ltest &= test_block_facet_deep_size<string>();
  print_footer("End testing block<string>");

  // scoped_index

  print_header("Begin testing block<scoped_index>");
  ltest &= test_block_facet<scoped_index>();
  ltest &= test_block_facet_equal<scoped_index>();
  ltest &= test_block_facet_insertion<scoped_index>();
  ltest &= test_block_facet_deep_size<scoped_index>();
  print_footer("End testing block<scoped_index>");

  // arg_list::arg_type

  print_header("Begin testing block<arg_list::arg_type>");
  ltest &= test_block_facet<arg_list::arg_type>();
  ltest &= test_block_facet_equal<arg_list::arg_type>();
  ltest &= test_block_facet_insertion<arg_list::arg_type>();
  ltest &= test_block_facet_deep_size<arg_list::arg_type>();
  print_footer("End testing block<arg_list::arg_type>");

  // primitive_value

  print_header("Begin testing block<primitive_value>");
  ltest &= test_block_facet<primitive_value>();
  ltest &= test_block_facet_equal<primitive_value>();
  ltest &= test_block_facet_insertion<primitive_value>();
  ltest &= test_block_facet_deep_size<primitive_value>();
  print_footer("End testing block<primitive_value>");

  // schema_descriptor

  print_header("Begin testing block<schema_descriptor>");
  ltest &= test_block_facet<schema_descriptor>();
  ltest &= test_block_facet_equal<schema_descriptor>();
  ltest &= test_block_facet_insertion<schema_descriptor>();
  ltest &= test_block_facet_deep_size<schema_descriptor>();
  print_footer("End testing block<schema_descriptor>");

  // poset_path

  print_header("Begin testing block<poset_path>");
  ltest &= test_block_facet<poset_path>();
  ltest &= test_block_facet_equal<poset_path>();
  ltest &= test_block_facet_insertion<poset_path>();
  ltest &= test_block_facet_deep_size<poset_path>();
  print_footer("End testing block<poset_path>");

  // double*

  print_header("Begin testing block<double*>");
  ltest &= test_block_facet<double*>();
  ltest &= test_block_facet_equal<double*>();
  ltest &= test_block_facet_insertion<double*>();
  ltest &= test_block_facet_deep_size<double*>();
  print_footer("End testing block<double*>");

  // index_space_handle*

  print_header("Begin testing block<index_space_handle*>");
  ltest &= test_block_facet<index_space_handle*>();
  ltest &= test_block_facet_equal<index_space_handle*>();
  ltest &= test_block_facet_insertion<index_space_handle*>();
  ltest &= test_block_facet_deep_size<index_space_handle*>();
  print_footer("End testing block<index_space_handle*>");

  // mutable_index_space_handle*

  print_header("Begin testing block<mutable_index_space_handle*>");
  ltest &= test_block_facet<mutable_index_space_handle*>();
  ltest &= test_block_facet_equal<mutable_index_space_handle*>();
  ltest &= test_block_facet_insertion<mutable_index_space_handle*>();
  ltest &= test_block_facet_deep_size<mutable_index_space_handle*>();
  print_footer("End testing block<mutable_index_space_handle*>");

  // block<double>

  print_header("Begin testing block<block<double> >");
  ltest &= test_block_facet<block<double> >();
  ltest &= test_block_facet_equal<block<double> >();
  ltest &= test_block_facet_insertion<block<double> >();
  ltest &= test_block_facet_deep_size<block<double> >();
  print_footer("End testing block<block<double> >");

  // string*

  print_header("Begin testing block<string*>");
  ltest &= test_block_facet<string*>();
  ltest &= test_block_facet_equal<string*>();
  ltest &= test_block_facet_insertion<string*>();
  //ltest &= test_block_facet_deep_size<string*>();
  print_footer("End testing block<string*>");

  // subposet_state*

  print_header("Begin testing block<subposet_state*>");
  ltest &= test_block_facet<subposet_state*>();
  ltest &= test_block_facet_equal<subposet_state*>();
  ltest &= test_block_facet_insertion<subposet_state*>();
  //ltest &= test_block_facet_deep_size<subposet_state*>();
  print_footer("End testing block<subposet_state*>");

  // poset_dof_map*

  print_header("Begin testing block<poset_dof_map*>");
  ltest &= test_block_facet<poset_dof_map*>();
  ltest &= test_block_facet_equal<poset_dof_map*>();
  ltest &= test_block_facet_insertion<poset_dof_map*>();
  //ltest &= test_block_facet_deep_size<poset_dof_map*>();
  print_footer("End testing block<poset_dof_map*>");

  // block<int>*

  print_header("Begin testing block<block<int>*>");
  ltest &= test_block_facet<block<int>*>();
  ltest &= test_block_facet_equal<block<int>*>();
  ltest &= test_block_facet_insertion<block<int>*>();
  //ltest &= test_block_facet_deep_size<block<int>*>();
  print_footer("End testing block<block<int>*>");

  // block<double>*

  print_header("Begin testing block<block<double>*>");
  ltest &= test_block_facet<block<double>*>();
  ltest &= test_block_facet_equal<block<double>*>();
  ltest &= test_block_facet_insertion<block<double>*>();
  //ltest &= test_block_facet_deep_size<block<double>*>();
  print_footer("End testing block<block<double>*>");

  // subposet

  print_header("Begin testing block<subposet>");
  ltest &= test_block_facet<subposet>();
  //ltest &= test_block_facet_equal<subposet>();
  ltest &= test_block_facet_insertion<subposet>();
  ltest &= test_block_facet_deep_size<subposet>();
  print_footer("End testing block<subposet>");

  // poset_state_handle*

  print_header("Begin testing block<poset_state_handle*>");
  ltest &= test_block_facet<poset_state_handle*>();
  ltest &= test_block_facet_equal<poset_state_handle*>();
  ltest &= test_block_facet_insertion<poset_state_handle*>();
  //ltest &= test_block_facet_deep_size<poset_state_handle*>();
  print_footer("End testing block<poset_state_handle*>");

  // set<int>

  print_header("Begin testing block<set<int> >");
  ltest &= test_block_facet<set<int> >();
  //ltest &= test_block_facet_equal<set<int> >();
  //ltest &= test_block_facet_insertion<set<int> >();
  //ltest &= test_block_facet_deep_size<set<int> >();
  print_footer("End testing block<set<int> >");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

