// $RCSfile: list_cover_set.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:28 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example posets/list_cover_set.t.cc
/// Test driver for class list_cover_set

#include "list_cover_set.h"
#include "assert_contract.h"
#include "std_iomanip.h"
#include "std_iostream.h"

using namespace sheaf;

int main(int argc, char* argv[])
{
  int result=0;

  // Preconditions:

  // Body:

  // Create a set and insert some members

  list_cover_set cs1;
  cs1.insert_member(scoped_index(0));

  cout << "cs1.is_singleton(): " << cs1.is_singleton() << " should be true" << endl;

  cs1.insert_member(scoped_index(1));

  cout << "cs1.is_singleton(): " << cs1.is_singleton() << " should be false" << endl;

  cs1.insert_member(scoped_index(2));

  cout << "cs1.is_singleton(): " << cs1.is_singleton() << " should be false" << endl;

  cout << "cs1: " << cs1 << " should be 0 1 2" << endl;

  // Copy the set

  list_cover_set cs2(cs1);

  cout << "cs2: " << cs2 << " should be 0 1 2" << endl;

  // The sets should be equal

  cout << "cs1.set_equals(cs2): " << cs1.set_equals(&cs2) << " should be true" << endl;

  // Define the same set in a different order

  list_cover_set cs3;
  cs3.insert_member(scoped_index(1));
  cs3.insert_member(scoped_index(0));
  cs3.insert_member(scoped_index(2));

  cout << "cs3: " << cs3 << " should be 1 0 2" << endl;

  // The cs1 and cs3 should be equal

  cout << "cs1.set_equals(cs3): " << cs1.set_equals(&cs3) << " should be true" << endl;

  // Remove a member from cs3

  cs3.remove_member(scoped_index(0));
  cout << "cs3.remove_member(0): " << cs3 << " should be 1 2" << endl;

  // Now cs1 and cs3 should not be equal

  cout << "cs1.set_equals(cs3): " << cs1.set_equals(&cs3) << " should be false" << endl;

  // cs1 intersect cs3 should equal cs3

  list_cover_set& cs4 = *(cs1.set_intersection(&cs3));
  cout << "cs4 = cs1 intersect cs3: " << cs4 << " should be 1 2" << endl;
  cout << "cs1.set_equals(cs4): " << cs1.set_equals(&cs4) << " should be false" << endl;
  cout << "cs3.set_equals(cs4): " << cs3.set_equals(&cs4) << " should be true" << endl;

  // Make a set which is disjoint from cs1

  list_cover_set cs5;
  cs5.insert_member(scoped_index(3));
  cs5.insert_member(scoped_index(4));
  cs5.insert_member(scoped_index(5));

  cout << "cs5: " << cs5 << " should be 3 4 5" << endl;

  // cs1 intersect cs5 should be empty

  list_cover_set& cs6 = *(cs1.set_intersection(&cs5));
  cout << "cs6 = cs1 intersect cs5: " << cs6 << " should be empty" << endl;
  cout << "cs6.empty(): " << cs6.empty() << " should be true" << endl;

  // Postconditions:

  // Exit

  return result;
}
