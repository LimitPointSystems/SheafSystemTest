// $RCSfile: standard_dof_tuple_index.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Test driver for class standard_dof_tuple_index.

#include "standard_dof_tuple_index.h"

#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_utils.h"

using namespace sheaf;

int
main()
{
  // Preconditions:

  // Body:

  print_header("Begin testing class standard_dof_tuple_index.");

  //============================================================================

  standard_dof_tuple_index lindex = STANDARD_DOF_TUPLE_INDEX_BEGIN;

  cout << "lindex = " << lindex << endl;

  // standard_dof_tuple_index& operator++(standard_dof_tuple_index& x);

  ++lindex;

  cout << "lindex = " << lindex << endl;

  // const string& standard_dof_tuple_index_to_name(standard_dof_tuple_index xpt);

  const string& lname = standard_dof_tuple_index_to_name(lindex);

  cout << "lname = " << lname << endl;

  const string& lname1 = standard_dof_tuple_index_to_name(++lindex);

  cout << "lname1 = " << lname1 << endl;

  // standard_dof_tuple_index standard_dof_tuple_index_from_name(const string& xname);

  standard_dof_tuple_index lindex1 =
    standard_dof_tuple_index_from_name("EMPTY_DOF_TUPLE_INDEX");

  cout << "lindex1 = " << lindex1 << endl;

  // standard_dof_tuple_index standard_dof_tuple_index_from_index(pod_index_type xindex);

  standard_dof_tuple_index lindex2 = standard_dof_tuple_index_from_index(1);

  cout << "lindex2 = " << lindex2 << endl;

  // bool is_standard_dof_tuple_index(pod_index_type xindex);

  bool lis_standard_dof_tuple_index = is_standard_dof_tuple_index(1);

  cout << "lis_standard_dof_tuple_index = " << boolalpha
       << lis_standard_dof_tuple_index << endl;
   

  //============================================================================

  print_footer("End testing class standard_dof_tuple_index.");

  // Postconditions:

  // Exit:

  return 0;
}

