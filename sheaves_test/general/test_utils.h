
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
/// Interface for fiber test function templates.

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif


namespace sheaf
{

//==============================================================================
// Convenience functions
//==============================================================================

///
/// Convenience function to print a "header" to standard out.
///
SHEAF_DLL_SPEC
void
print_header(const string& xtext);

///
/// Convenience function to print a "header" to standard out.
///
SHEAF_DLL_SPEC
void
print_header(const string& xtext, const string& xtext2);


///
/// Convenience function to print a "footer" to standard out.
///
SHEAF_DLL_SPEC
void
print_footer(const string& xtext);

///
/// Convenience function to print a "footer" to standard out.
///
SHEAF_DLL_SPEC
void
print_footer(const string& xtext, const string& xtext2);

///
/// Convenience function to print a "subheader" to standard out.
///
SHEAF_DLL_SPEC
void
print_subheader(const string& xtext);

///
/// Convenience function to print a "subheader" to standard out.
///
SHEAF_DLL_SPEC
void
print_subheader(const string& xtext, const string& xtext2);

///
/// Convenience function to print an "action" to standard out.
///
SHEAF_DLL_SPEC
void
print_action(const string& xtext);


} // namespace sheaf


#endif // ifndef TEST_UTILS_H
