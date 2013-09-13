
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
/// Unit test driver for template class wsv_block.

#include "wsv_block.h"
#include "schema_descriptor.h"
#include "test_sheaves.impl.h"

using namespace sheaf;

namespace
{

template<typename T>
class wsv_block_child : public wsv_block<T>
{
public:
  wsv_block_child() {}
  ~wsv_block_child() {}
};

template<typename T>
bool
test_wsv_block_ctors_dtors()
{
  wsv_block<T>* lparent = new wsv_block<T>;
  delete lparent;

  wsv_block_child<T>* lchild = new wsv_block_child<T>;
  delete lchild;

  //wsv_block<T>* lparent_copy = new wsv_block<T>(*lparent);
  //delete lparent_copy;
  //delete lparent;

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

  print_header("Begin testing wsv_block<bool>");
  ltest &= test_wsv_block_ctors_dtors<bool>();
  ltest &= test_wsv_block_facet<bool>();
  print_footer("End testing wsv_block<bool>");

  // int

  print_header("Begin testing wsv_block<int>");
  ltest &= test_wsv_block_ctors_dtors<int>();
  ltest &= test_wsv_block_facet<int>();
  print_footer("End testing wsv_block<int>");

  // double

  print_header("Begin testing wsv_block<double>");
  ltest &= test_wsv_block_ctors_dtors<double>();
  ltest &= test_wsv_block_facet<double>();
  print_footer("End testing wsv_block<double>");

  // unsigned

  print_header("Begin testing wsv_block<unsigned>");
  ltest &= test_wsv_block_ctors_dtors<unsigned>();
  ltest &= test_wsv_block_facet<unsigned>();
  print_footer("End testing wsv_block<unsigned>");

  // $$SCRIBBLE: Currently not instantiated.
  //   // unsigned long

  //   print_header("Begin testing wsv_block<unsigned long>");
  //   ltest &= test_wsv_block_ctors_dtors<unsigned long>();
  //   ltest &= test_wsv_block_facet<unsigned long>();
  //   print_footer("End testing wsv_block<unsigned long>");

  // size_type

  print_header("Begin testing wsv_block<size_type>");
  ltest &= test_wsv_block_ctors_dtors<size_type>();
  ltest &= test_wsv_block_facet<size_type>();
  print_footer("End testing wsv_block<size_type>");

  // schema_descriptor

  print_header("Begin testing wsv_block<schema_descriptor>");
  ltest &= test_wsv_block_ctors_dtors<schema_descriptor>();
  ltest &= test_wsv_block_facet<schema_descriptor>();
  print_footer("End testing wsv_block<schema_descriptor>");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

