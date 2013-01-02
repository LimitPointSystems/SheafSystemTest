// $RCSfile: interval_set.t.cc,v $ $Revision: 1.8 $ $Date: 2012/07/04 16:42:27 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Test driver for class interval_set.

#include "interval_set.h"
#include "interval_set_iterator.h"
#include "std_string.h"
#include "std_iomanip.h"


using namespace sheaf;

namespace
{

///
/// Print the header of the test.
///
void print_header(const string& xheader)
{
  cout << "===============================================" << endl;
  cout << endl << xheader << endl;
}

///
/// Print the results of test.
///
void print_result(interval_set& xset)
{
  cout << "-----------------------------------------------" << endl;
  cout << xset << endl;
}

///
/// Insert xmbr into xset.
///
void insert_member(interval_set& xset,
		   interval_set::pod_type xmbr)
{
  cout << "insert_member(" << xmbr << ")" << endl;

  xset.insert_member(xmbr);
}

///
/// Insert interval [xbegin, xend] into xset.
///
void insert_interval(interval_set& xset,
		     interval_set::pod_type xbegin,
		     interval_set::pod_type xend)
{
  cout << "insert_interval(" << xbegin << ", " << xend << ")" << endl;

  xset.insert_interval(xbegin, xend);
}
  
///
/// Remove xmbr from xset.
///
void remove_member(interval_set& xset,
		   interval_set::pod_type xmbr)
{
  cout << "remove_member(" << xmbr << ")" << endl;

  xset.remove_member(xmbr);
}

///
/// Remove interval [xbegin, xend] into xset.
///
void remove_interval(interval_set& xset,
		     interval_set::pod_type xbegin,
		     interval_set::pod_type xend)
{
  cout << "remove_interval(" << xbegin << ", " << xend << ")" << endl;

  xset.remove_interval(xbegin, xend);
}

///
/// Test if xset contains xmbr.
///
void contains_member(interval_set& xset,
		     interval_set::pod_type xmbr,
		     bool xexpected)
{
  cout << "contains_member(" << setw(2) << xmbr << ") = "
       << xset.contains_member(xmbr) << " should be "
       << xexpected << endl;
}

///
/// Test if interval [xbegin, xend] is empty in xset.
///
void interval_is_empty(interval_set& xset,
		       interval_set::pod_type xbegin,
		       interval_set::pod_type xend,
		       bool xexpected)
{
  cout << "interval_is_empty(" << setw(2) << xbegin << ", "
       << setw(2) << xend << ") = "
       << xset.interval_is_empty(xbegin, xend)
       << " should be " << xexpected << endl;
}

///
/// Test if interval [xbegin, xend] is full in xset.
///
void interval_is_full(interval_set& xset,
		      interval_set::pod_type xbegin,
		      interval_set::pod_type xend,	
		      bool xexpected)
{
  cout << "interval_is_full(" << setw(2) << xbegin << ", "
       << setw(2) << xend << ") = "
       << xset.interval_is_full(xbegin, xend)
       << " should be " << xexpected << endl;
}

} // unnamed namespace

///
/// Main routine for testing interval_set.
///
int
main()
{
  interval_set lset;
  print_header("Testing empty interval set:");
  print_result(lset);

  // Test single member.

  print_header("Testing single member:");
  insert_member(lset, 5);
  print_result(lset);

  // Test single interval.

  print_header("Testing single interval:");
  insert_interval(lset, 4, 6);
  print_result(lset);

  // Test adjacent intervals.

  print_header("Testing adjacent intervals:");
  insert_interval(lset, 2, 3);
  insert_interval(lset, 6, 7);
  print_result(lset);

  // Test overlapping intervals.

  print_header("Testing overlapping intervals:");
  insert_interval(lset, 1, 5);
  insert_interval(lset, 7, 8);
  insert_interval(lset, 0, 9);

  // Test multiple intervals.

  print_header("Testing multiple intervals:");
  insert_interval(lset, 12, 15);
  insert_member(lset, 20);
  print_result(lset);

  // Test remove intervals.

  print_header("Testing remove intervals:");
  remove_member(lset, 0);
  remove_interval(lset, 8, 9);
  remove_interval(lset, 13, 14);
  remove_member(lset, 20);
  print_result(lset);

  // Test contains member.

  print_header("Testing contains member:");
  contains_member(lset, 0, false);
  contains_member(lset, 1, true);
  contains_member(lset, 5, true);
  contains_member(lset, 7, true);
  contains_member(lset, 8, false);
  contains_member(lset, 12, true);
  contains_member(lset, 14, false);
  contains_member(lset, 16, false);
  contains_member(lset, 20, false);

  // Test interval is empty.

  print_header("Testing interval is empty:");
  interval_is_empty(lset, -2, 0, true);
  interval_is_empty(lset, 0, 4, false);
  interval_is_empty(lset, 1, 4, false);
  interval_is_empty(lset, 1, 7, false);
  interval_is_empty(lset, 5, 7, false);
  interval_is_empty(lset, 6, 8, false);
  interval_is_empty(lset, 8, 10, true);
  interval_is_empty(lset, 8, 11, true);
  interval_is_empty(lset, 10, 12, false);
  interval_is_empty(lset, 12, 15, false);
  interval_is_empty(lset, 15, 15, false);
  interval_is_empty(lset, 16, 50, true);

  // Test interval is empty.

  print_header("Testing interval is full:");
  interval_is_full(lset, -2, 0, false);
  interval_is_full(lset, 0, 4, false);
  interval_is_full(lset, 1, 4, true);
  interval_is_full(lset, 1, 7, true);
  interval_is_full(lset, 5, 7, true);
  interval_is_full(lset, 6, 8, false);
  interval_is_full(lset, 8, 10, false);
  interval_is_full(lset, 8, 11, false);
  interval_is_full(lset, 10, 12, false);
  interval_is_full(lset, 12, 15, false);
  interval_is_full(lset, 15, 15, true);
  interval_is_full(lset, 16, 50, false);

  return 0;
}



