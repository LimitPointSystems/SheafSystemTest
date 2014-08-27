
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

/// @example template_instantiations/list_pool.inst.t.cc
/// Unit test driver for class list_pool template functions.

#include "fiber_bundles_namespace.h"

#include "i_adjacency_implicit_index_space_iterator.h"
#include "i_connectivity_implicit_index_space_iterator.h"
#include "ij_adjacency_implicit_index_space_iterator.h"
#include "ij_connectivity_implicit_index_space_iterator.h"
#include "ijk_adjacency_implicit_index_space_iterator.h"
#include "ijk_connectivity_implicit_index_space_iterator.h"
#include "section_space_schema_jims_index_space_handle.h"
#include "section_space_schema_jims_index_space_iterator.h"
#include "test_utils.h"
#include "test_sheaves.impl.h"

using namespace std;
using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  print_header("Begin testing list_pool<i_adjacency_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<i_adjacency_implicit_index_space_iterator>();
  print_footer("End testing list_pool<i_adjacency_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<i_connectivity_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<i_connectivity_implicit_index_space_iterator>();
  print_footer("End testing list_pool<i_connectivity_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<ij_adjacency_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<ij_adjacency_implicit_index_space_iterator>();
  print_footer("End testing list_pool<ij_adjacency_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<ij_connectivity_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<ij_connectivity_implicit_index_space_iterator>();
  print_footer("End testing list_pool<ij_connectivity_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<ijk_adjacency_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<ijk_adjacency_implicit_index_space_iterator>();
  print_footer("End testing list_pool<ijk_adjacency_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<ijk_connectivity_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<ijk_connectivity_implicit_index_space_iterator>();
  print_footer("End testing list_pool<ijk_connectivity_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<section_space_schema_jims_index_space_handle>");
  ltest &= test_list_pool_facet<section_space_schema_jims_index_space_handle>();
  print_footer("End testing list_pool<section_space_schema_jims_index_space_handle>");

  print_header("Begin testing list_pool<section_space_schema_jims_index_space_iterator>");
  ltest &= test_list_pool_facet<section_space_schema_jims_index_space_iterator>();
  print_footer("End testing list_pool<section_space_schema_jims_index_space_iterator>");


  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}


