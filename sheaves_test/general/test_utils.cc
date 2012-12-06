
// $RCSfile: test_utils.cc,v $ $Revision: 1.1.2.1 $ $Date: 2012/10/01 22:08:39 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @file
/// Implementation for test_sheaves non template functions.

#include "test_utils.h"
#include "std_iostream.h"

void
sheaf::
print_header(const string& xtext)
{
  // Preconditions:

  // Body:

  static const string nl("\n");
  static const string s = "========================================";
  static const string sep = s + s;

  cout << nl << sep << nl << xtext << nl << sep << nl;
  cout << endl;

  // Postconditions:

  // Exit:  
}

void
sheaf::
print_header(const string& xtext, const string& xtext2)
{
  // Preconditions:

  // Body:

  static const string nl("\n");
  static const string s = "========================================";
  static const string sep = s + s;

  cout << nl << sep << nl << xtext << xtext2 << nl << sep << nl;
  cout << endl;

  // Postconditions:

  // Exit:  
}


void
sheaf::
print_footer(const string& xtext)
{
  // Preconditions:

  // Body:

  // Just do the same as in print_header for now.

  print_header(xtext);

  // Postconditions:

  // Exit:  
}

void
sheaf::
print_footer(const string& xtext, const string& xtext2)
{
  // Preconditions:

  // Body:

  // Just do the same as in print_header for now.

  print_header(xtext, xtext2);

  // Postconditions:

  // Exit:  
}

void
sheaf::
print_subheader(const string& xtext)
{
  // Preconditions:

  // Body:

  static const string nl("\n");

  cout << nl << "======== " << xtext << nl;
  cout << endl;

  // Postconditions:

  // Exit:  
}

void
sheaf::
print_subheader(const string& xtext, const string& xtext2)
{
  // Preconditions:

  // Body:

  static const string nl("\n");

  cout << nl << "======== " << xtext  << nl;
  cout <<       "======== " << xtext2 << nl;
  cout << endl;

  // Postconditions:

  // Exit:  
}


void
sheaf::
print_action(const string& xtext)
{
  // Preconditons:

  // Body:

  cout << ">>>>>>>> " << xtext << endl;

  // Postconditions:

  // Exit:

  return;
}

