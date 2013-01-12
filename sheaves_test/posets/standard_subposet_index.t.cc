
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Test driver for class standard_subposet_index.

#include "standard_subposet_index.h"

#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_utils.h"

using namespace sheaf;

int
main()
{
  // Preconditions:

  // Body:

  print_header("Begin testing class standard_subposet_index.");

  //============================================================================

  standard_subposet_index lindex = STANDARD_SUBPOSET_INDEX_BEGIN;

  cout << "lindex = " << lindex << endl;

  // standard_subposet_index& operator++(standard_subposet_index& x);

  ++lindex;

  cout << "lindex = " << lindex << endl;

  // const string& standard_subposet_index_to_name(standard_subposet_index xpt);

  const string& lname = standard_subposet_index_to_name(lindex);

  cout << "lname = " << lname << endl;

  const string& lname1 = standard_subposet_index_to_name(++lindex);

  cout << "lname1 = " << lname1 << endl;

  // standard_subposet_index standard_subposet_index_from_name(const string& xname);

  standard_subposet_index lindex1 =
    standard_subposet_index_from_name("WHOLE_INDEX");

  cout << "lindex1 = " << lindex1 << endl;

  // standard_subposet_index standard_subposet_index_from_index(pod_index_type xindex);

  standard_subposet_index lindex2 = standard_subposet_index_from_index(2);

  cout << "lindex2 = " << lindex2 << endl;

  // bool is_standard_subposet_index(pod_index_type xindex);

  bool lis_standard_subposet_index = is_standard_subposet_index(2);

  cout << "lis_standard_subposet_index = " << boolalpha
       << lis_standard_subposet_index << endl;
   

  //============================================================================

  print_footer("End testing class standard_subposet_index.");

  // Postconditions:

  // Exit:

  return 0;
}

