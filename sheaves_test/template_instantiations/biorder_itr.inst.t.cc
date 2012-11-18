// $RCSfile: biorder_itr.inst.t.cc,v $ $Revision: 1.1.2.4 $ $Date: 2012/11/16 00:14:31 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example template_instantiations/biorder_itr.inst.t.cc
/// Unit test driver for template class biorder_itr.

#include "biorder_itr.h"

#include "namespace_poset.h"
#include "test_sheaves.impl.h"
#include "test_utils.h"

using namespace sheaf;

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
  ltest &= test_depth_first_itr_facet<biorder_itr, ZBOOL>(lns);
  ltest &= test_filtered_depth_first_itr_facet<biorder_itr, ZBOOL>(lns);
  print_footer("End testing biorder_itr<zn_to_bool>");

  typedef hash_set<pod_index_type> SET;
  print_header("Begin testing biorder_itr<set<pod_index_type> >");
  ltest &= test_depth_first_itr_facet<biorder_itr, SET >(lns);
  ltest &= test_filtered_depth_first_itr_facet<biorder_itr, SET >(lns);
  print_footer("End testing biorder_itr<set<pod_index_type> >");

  print_header("Begin testing biorder_itr<hash_set<pod_index_type> >");
  typedef hash_set<pod_index_type> HASH_SET;
  ltest &= test_depth_first_itr_facet<biorder_itr, HASH_SET >(lns);
  ltest &= test_filtered_depth_first_itr_facet<biorder_itr, HASH_SET >(lns);
  print_footer("End testing biorder_itr<hash_set<pod_index_type> >");

  //============================================================================

  print_footer("End testing biorder_itr");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

