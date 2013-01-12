

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
