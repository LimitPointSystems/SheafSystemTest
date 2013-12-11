
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

/// @file
/// Implementation for test_sheaves non template functions.

#include "test_utils.h"
#include "std_iostream.h"

using namespace std;

void
sheaf::
print_header(const std::string& xtext)
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
print_header(const std::string& xtext, const std::string& xtext2)
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
print_footer(const std::string& xtext)
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
print_footer(const std::string& xtext, const std::string& xtext2)
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
print_subheader(const std::string& xtext)
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
print_subheader(const std::string& xtext, const std::string& xtext2)
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
print_action(const std::string& xtext)
{
  // Preconditons:

  // Body:

  cout << ">>>>>>>> " << xtext << endl;

  // Postconditions:

  // Exit:

  return;
}

