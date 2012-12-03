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

// Just testing!
namespace
{
  template <typename T>
  class derived_itr : public postorder_itr<T>
  {
  public:
    derived_itr();
    ~derived_itr();
    int* _values;
  };

  template <typename T>
  derived_itr<T>::
  derived_itr()
    : postorder_itr<T>::postorder_itr()
  {
    _values = new int[5];
  }

  template <typename T>
  derived_itr<T>::
  ~derived_itr()
  {
    delete [] _values;
  }
  
}

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing postorder_itr");

  bool ltest = true;

  //============================================================================

  derived_itr<zn_to_bool> lderived();
  derived_itr<zn_to_bool>* lderived2 = new derived_itr<zn_to_bool>();
  delete lderived2;
  
  //============================================================================

  // Create a namespace_poset.

  namespace_poset lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  // Test the facets:

  typedef zn_to_bool ZBOOL;
  print_header("Begin testing postorder_itr<zn_to_bool>");
  ltest &= test_depth_first_itr_facet<postorder_itr, ZBOOL>(lns);
  ltest &= test_filtered_depth_first_itr_facet<postorder_itr, ZBOOL>(lns);
  print_footer("End testing postorder_itr<zn_to_bool>");

  typedef set<pod_index_type> SET;
  print_header("Begin testing postorder_itr<set<pod_index_type> >");
  ltest &= test_depth_first_itr_facet<postorder_itr, SET >(lns);
  ltest &= test_filtered_depth_first_itr_facet<postorder_itr, SET >(lns);
  print_footer("End testing postorder_itr<set<pod_index_type> >");

  print_header("Begin testing postorder_itr<hash_set<pod_index_type> >");
  typedef hash_set<pod_index_type> HASH_SET;
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

