#! /usr/bin/perl
#
# Copyright (c) 2013 Limit Point Systems, Inc. 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#
# Usage: add_dll_spec.pl file [file ...]
#
# Adds include of sheaf_dll_spec.h to file
# and inserts SHEAF_DLL_SPEC in front of every class or struct definition.
# Writes result to STDOUT.
#
undef $/;       # each read is whole file.
while(<>)
{
  # Include sheaf_dll_spec right after guard definition.

  s/(\#define[^\n]*\n)/$1\n\#ifndef SHEAF_DLL_SPEC_H\n\#include "sheaf_dll_spec.h"\n\#endif\n/;

  # Put SHEAF_DLL_SPEC after "class" in all class declarations.
  # Class declaration is "class " followed by 0 or more chars
  # that are not ";" followed by "{".
  # $1 is contents of first () delimited group in search pattern,
  # leading whitespace, and $2 is second group, class declaration itself.
  # /m modifer is necessary so ^ selects beginning of lines,
  # not just beginning of entire string (i.e. the whole file).

  s/^([ \t]*class)( [^;]*\{)/$1 SHEAF_DLL_SPEC$2/mg;

  # Also put SHEAF_DLL_SPEC in front of all struct declarations.

  s/^([ \t]*struct)( [^;]*\{)/$1 SHEAF_DLL_SPEC$2/mg;

  # alternates that just mark matches, for debugging
  #  s/^([ \t]*class)( [^;]*\{)/\$$1$2\$/mg;
  #  s/^([ \t]*struct)( [^;]*\{)/\$$1$2\$/mg;

  print;
}
