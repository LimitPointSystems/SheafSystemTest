
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

/// @example template_instantiations/biorder_itr.inst.t.cc
/// Unit test driver for template class biorder_itr.

#include "biorder_itr.h"

#include "namespace_poset.h"
#include "test_sheaves.impl.h"
#include "test_utils.h"

using namespace std;
using namespace sheaf;

// 75.00	(9/12)	biorder_itr<zn_to_bool>::biorder_itr()
// 100.00	(3/3)	biorder_itr<zn_to_bool>::~biorder_itr()
// 100.00	(5/5)	biorder_itr<zn_to_bool>::invariant() const

// 71.43	(15/21) biorder_itr:zn_to_bool>::biorder_itr(abstract_poset_member const&, scoped_index, bool, bool)
// 62.50	(5/8)	biorder_itr<zn_to_bool>::biorder_itr(abstract_poset_member const&, subposet const*, bool, bool)
// 62.50	(5/8)	biorder_itr<zn_to_bool>::biorder_itr(abstract_poset_member const&, std::string const&, bool, bool)
// 62.50	(5/8)	biorder_itr<zn_to_bool>::biorder_itr(biorder_itr<zn_to_bool> const&)

// 64.29	(9/14)	biorder_itr<zn_to_bool>::clone() const
// 71.43	(5/7)	biorder_itr<zn_to_bool>::is_ancestor_of(any const*) const

namespace
{

//$$TODO: Move this stuff test_sheaves.
//$$SCRIBBLE: It would be nice if we could have the itr_child class
//            as a local class within the function
//            test_default_constructor_and_destructor,
//            but the current compilers don't allow that.
//            Maybe in C++11.

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

  //=====================================================

  //ITR<T> litr0_copy(litr0);
  //  Copy CTOR fails ensure(order() == xother.order());

  bool lis_ancestor = litr0.is_ancestor_of(&litr);
  cout << "lis_ancestor = " << lis_ancestor << endl;

  ITR<T>* litr1_ptr = litr0.clone();

  //===================================================== 

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

  print_header("Begin testing biorder_itr");

  bool ltest = true;

  //============================================================================

  // Create a namespace_poset.

  namespace_poset lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  // Test the facets:

  typedef zn_to_bool ZBOOL;
  print_header("Begin testing biorder_itr<zn_to_bool>");
  ltest &= test_default_constructor_and_destructor<biorder_itr, ZBOOL>();
  ltest &= test_depth_first_itr_facet<biorder_itr, ZBOOL>(lns);
  ltest &= test_filtered_depth_first_itr_facet<biorder_itr, ZBOOL>(lns);
  print_footer("End testing biorder_itr<zn_to_bool>");

  typedef set<pod_index_type> SET;
  print_header("Begin testing biorder_itr<set<pod_index_type> >");
  ltest &= test_default_constructor_and_destructor<biorder_itr, SET>();
  ltest &= test_depth_first_itr_facet<biorder_itr, SET>(lns);
  ltest &= test_filtered_depth_first_itr_facet<biorder_itr, SET>(lns);
  print_footer("End testing biorder_itr<set<pod_index_type> >");

  print_header("Begin testing biorder_itr<hash_set<pod_index_type> >");
  typedef hash_set<pod_index_type> HASH_SET;
  ltest &= test_default_constructor_and_destructor<biorder_itr, HASH_SET>();
  ltest &= test_depth_first_itr_facet<biorder_itr, HASH_SET>(lns);
  ltest &= test_filtered_depth_first_itr_facet<biorder_itr, HASH_SET>(lns);
  print_footer("End testing biorder_itr<hash_set<pod_index_type> >");

  //============================================================================

  print_footer("End testing biorder_itr");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

