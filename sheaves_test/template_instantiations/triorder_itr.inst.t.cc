
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
/// @example template_instantiations/triorder_itr.inst.t.cc
/// Unit test driver for template class triorder_itr.

#include "triorder_itr.h"

#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "test_sheaves.impl.h"
#include "test_utils.h"

using namespace std;
using namespace unordered;
using namespace sheaf;

namespace
{

///
/// Simple derived class.  Used to insure coverage of
/// bi/list/post/pre/triorder_itr constructors and destructors
/// (see LPS Forum topic "Code Coverage").
///
template <template <typename> class ITR, typename T>
class itr_child : public ITR<T>
{
public:
  itr_child() {}
  ~itr_child() {}
};

template <template <typename> class ITR, typename T>
bool
test_default_constructor_and_destructor()
{
  // Preconditions:

  // Body:

 ITR<T> litr0;

  ITR<T>* litr0_ptr = new ITR<T>();
  delete litr0_ptr; 


  itr_child<ITR, T> litr;

  itr_child<ITR, T>* lchild_ptr = new itr_child<ITR, T>();
  delete lchild_ptr;

  // Postconditions:

  // Exit:

  return true;
}


} // end unnamed namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing triorder_itr ...");

  bool ltest = true;

  //============================================================================

  // Create a namespace_poset.

  namespace_poset lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  // Test the facets:

  typedef zn_to_bool ZBOOL;
  print_header("Begin testing triorder_itr<zn_to_bool>");
  ltest &= test_default_constructor_and_destructor<triorder_itr, ZBOOL>();
  ltest &= test_depth_first_itr_facet<triorder_itr, ZBOOL>(lns);
  ltest &= test_filtered_depth_first_itr_facet<triorder_itr, ZBOOL>(lns);
  print_footer("End testing triorder_itr<zn_to_bool>");

  typedef set<pod_index_type> SET;
  print_header("Begin testing triorder_itr<set<pod_index_type> >");
  ltest &= test_default_constructor_and_destructor<triorder_itr, SET>();
  ltest &= test_depth_first_itr_facet<triorder_itr, SET >(lns);
  ltest &= test_filtered_depth_first_itr_facet<triorder_itr, SET >(lns);
  print_footer("End testing triorder_itr<set<pod_index_type> >");

  print_header("Begin testing triorder_itr<unordered_set<pod_index_type> >");
  typedef unordered_set<pod_index_type> UNORDERED_SET;
  ltest &= test_default_constructor_and_destructor<triorder_itr, UNORDERED_SET>();
  ltest &= test_depth_first_itr_facet<triorder_itr, UNORDERED_SET >(lns);
  ltest &= test_filtered_depth_first_itr_facet<triorder_itr, UNORDERED_SET >(lns);
  print_footer("End testing triorder_itr<unordered_set<pod_index_type> >");

  //============================================================================

  print_footer("End testing triorder_itr ...");

  print_footer("End testing triorder_itr ...");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

