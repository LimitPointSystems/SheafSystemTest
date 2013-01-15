// $RCSfile$ $Revision$ $Date$

// $Name$
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @example primary_sum_index_space_x.t.cc
/// Test driver for primary_sum id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "primary_sum_index_space_handle.h"
#include "primary_sum_index_space_iterator.h"
#include "primary_sum_index_space_state.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  index_space_family lid_spaces;
  lid_spaces.new_id();
  lid_spaces.new_id();

  pod_index_type lspace_id = 0;

  // Test handle facet.

  test_explicit_handle_facet<sum_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  sum_index_space_handle lhandle(lid_spaces, lspace_id);

  sum_index_space_handle::equivalence_class_type leqv;
  cout << "equivalence_class(0, leqv)" << endl;
  lhandle.equivalence_class(0, leqv);
  cout << "equivalence_ct(0)          = " << lhandle.equivalence_ct(0) << endl;
  cout << "contains_rep(0)            = " << lhandle.contains_rep(0) << endl;
  cout << "contains_unique_rep(0)     = " << lhandle.contains_unique_rep(0) << endl;
  cout << "rep(0)                     = " << lhandle.rep(0) << endl;
  cout << "host_rep(0)                = " << lhandle.host_rep(0) << endl;
  cout << "term_id_begin()            = " << lhandle.term_id_begin() << endl;
  cout << "term_id_end()              = " << lhandle.term_id_end() << endl;
  cout << "term(0)                    = " << &lhandle.term(0) << endl;
  cout << "term_of(0)                 = " << &lhandle.term_of(0) << endl;
  cout << "last_term()                = " << &lhandle.last_term() << endl;
  cout << "term_begin(0)              = " << lhandle.term_begin(0) << endl;
  cout << "term_end(0)                = " << lhandle.term_end(0) << endl;
  cout << "term_hub_begin(0)          = " << lhandle.term_hub_begin(0) << endl;
  cout << "term_hub_end(0)            = " << lhandle.term_hub_end(0) << endl;
  cout << "binary(0, lterm_id, llocal)" << endl;
  pod_index_type lterm_id, llocal;
  lhandle.binary(0, lterm_id, llocal);
  cout << "simple(0, 0, lindex)" << endl;
  pod_index_type lindex;
  lhandle.simple(0, 0, lindex);
  cout << "clear()" << endl;
  lhandle.clear();

  // Postconditions:

  // Exit:

  return 0;
}

  
