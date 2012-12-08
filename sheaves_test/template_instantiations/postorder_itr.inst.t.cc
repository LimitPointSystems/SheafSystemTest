// $RCSfile: postorder_itr.inst.t.cc,v $ $Revision: 1.1.2.4 $ $Date: 2012/11/16 00:14:31 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example template_instantiations/postorder_itr.inst.t.cc
/// Unit test driver for template class postorder_itr.

#include "postorder_itr.h"

#include "namespace_poset.h"
#include "test_sheaves.impl.h"
#include "test_utils.h"

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

  print_header("Begin testing postorder_itr");

  bool ltest = true;
  
  //============================================================================

  // Create a namespace_poset.

  namespace_poset lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  // Test the facets:

  typedef zn_to_bool ZBOOL;
  print_header("Begin testing postorder_itr<zn_to_bool>");
  ltest &= test_default_constructor_and_destructor<postorder_itr, ZBOOL>();
  ltest &= test_depth_first_itr_facet<postorder_itr, ZBOOL>(lns);
  ltest &= test_filtered_depth_first_itr_facet<postorder_itr, ZBOOL>(lns);
  print_footer("End testing postorder_itr<zn_to_bool>");

  typedef set<pod_index_type> SET;
  print_header("Begin testing postorder_itr<set<pod_index_type> >");
  ltest &= test_default_constructor_and_destructor<postorder_itr, SET>();
  ltest &= test_depth_first_itr_facet<postorder_itr, SET >(lns);
  ltest &= test_filtered_depth_first_itr_facet<postorder_itr, SET >(lns);
  print_footer("End testing postorder_itr<set<pod_index_type> >");

  print_header("Begin testing postorder_itr<hash_set<pod_index_type> >");
  typedef hash_set<pod_index_type> HASH_SET;
  ltest &= test_default_constructor_and_destructor<postorder_itr, HASH_SET>();
  ltest &= test_depth_first_itr_facet<postorder_itr, HASH_SET >(lns);
  ltest &= test_filtered_depth_first_itr_facet<postorder_itr, HASH_SET >(lns);
  print_footer("End testing postorder_itr<hash_set<pod_index_type> >");

  //============================================================================

  print_footer("End testing postorder_itr");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

