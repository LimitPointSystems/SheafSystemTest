
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

/// @example
/// Unit test driver for template class list_pool instantiations.

#include "SheafSystem/block.h"

#include "SheafSystem/array_implicit_index_space_iterator.h"
#include "SheafSystem/array_index_space_handle.h"
#include "SheafSystem/array_index_space_iterator.h"
#include "SheafSystem/constant_implicit_index_space_iterator.h"
#include "SheafSystem/forwarding_index_space_handle.h"
#include "SheafSystem/hash_index_space_handle.h"
#include "SheafSystem/hash_index_space_iterator.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/hub_index_space_iterator.h"
#include "SheafSystem/interval_index_space_handle.h"
#include "SheafSystem/interval_index_space_iterator.h"
#include "SheafSystem/list_index_space_handle.h"
#include "SheafSystem/list_index_space_iterator.h"
#include "SheafSystem/offset_index_space_handle.h"
#include "SheafSystem/offset_index_space_iterator.h"
#include "SheafSystem/primary_index_space_handle.h"
#include "SheafSystem/primary_index_space_iterator.h"
#include "SheafSystem/primitives_index_space_handle.h"
#include "SheafSystem/primitives_index_space_iterator.h"
#include "SheafSystem/ragged_array_implicit_index_space_iterator.h"
#include "SheafSystem/reserved_primary_index_space_handle.h"
#include "SheafSystem/reserved_primary_index_space_iterator.h"
#include "SheafSystem/singleton_implicit_index_space_iterator.h"
#include "SheafSystem/singleton_index_space_handle.h"
#include "SheafSystem/singleton_index_space_iterator.h"
#include "SheafSystemTest/test_utils.h"
#include "SheafSystemTest/test_sheaves.impl.h"

using namespace std;
using namespace sheaf;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  print_header("Begin testing list_pool<array_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<array_implicit_index_space_iterator>();
  print_footer("End testing list_pool<array_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<array_index_space_handle>");
  ltest &= test_list_pool_facet<array_index_space_handle>();
  print_footer("End testing list_pool<array_index_space_handle>");

  print_header("Begin testing list_pool<array_index_space_iterator>");
  ltest &= test_list_pool_facet<array_index_space_iterator>();
  print_footer("End testing list_pool<array_index_space_iterator>");

  print_header("Begin testing list_pool<constant_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<constant_implicit_index_space_iterator>();
  print_footer("End testing list_pool<constant_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<forwarding_index_space_handle>");
  ltest &= test_list_pool_facet<forwarding_index_space_handle>();
  print_footer("End testing list_pool<forwarding_index_space_handle>");

  print_header("Begin testing list_pool<hash_index_space_handle>");
  ltest &= test_list_pool_facet<hash_index_space_handle>();
  print_footer("End testing list_pool<hash_index_space_handle>");

  print_header("Begin testing list_pool<hash_index_space_iterator>");
  ltest &= test_list_pool_facet<hash_index_space_iterator>();
  print_footer("End testing list_pool<hash_index_space_iterator>");

  print_header("Begin testing list_pool<hub_index_space_handle>");
  ltest &= test_list_pool_facet<hub_index_space_handle>();
  print_footer("End testing list_pool<hub_index_space_handle>");

  print_header("Begin testing list_pool<hub_index_space_iterator>");
  ltest &= test_list_pool_facet<hub_index_space_iterator>();
  print_footer("End testing list_pool<hub_index_space_iterator>");

  print_header("Begin testing list_pool<interval_index_space_handle>");
  ltest &= test_list_pool_facet<interval_index_space_handle>();
  print_footer("End testing list_pool<interval_index_space_handle>");

  print_header("Begin testing list_pool<interval_index_space_iterator>");
  ltest &= test_list_pool_facet<interval_index_space_iterator>();
  print_footer("End testing list_pool<interval_index_space_iterator>");

  print_header("Begin testing list_pool<list_index_space_handle>");
  ltest &= test_list_pool_facet<list_index_space_handle>();
  print_footer("End testing list_pool<list_index_space_handle>");

  print_header("Begin testing list_pool<list_index_space_iterator>");
  ltest &= test_list_pool_facet<list_index_space_iterator>();
  print_footer("End testing list_pool<list_index_space_iterator>");

  print_header("Begin testing list_pool<offset_index_space_handle>");
  ltest &= test_list_pool_facet<offset_index_space_handle>();
  print_footer("End testing list_pool<offset_index_space_handle>");

  print_header("Begin testing list_pool<offset_index_space_iterator>");
  ltest &= test_list_pool_facet<offset_index_space_iterator>();
  print_footer("End testing list_pool<offset_index_space_iterator>");

  print_header("Begin testing list_pool<primary_index_space_handle>");
  ltest &= test_list_pool_facet<primary_index_space_handle>();
  print_footer("End testing list_pool<primary_index_space_handle>");

  print_header("Begin testing list_pool<primary_index_space_iterator>");
  ltest &= test_list_pool_facet<primary_index_space_iterator>();
  print_footer("End testing list_pool<primary_index_space_iterator>");

  print_header("Begin testing list_pool<primitives_index_space_handle>");
  ltest &= test_list_pool_facet<primitives_index_space_handle>();
  print_footer("End testing list_pool<primitives_index_space_handle>");

  print_header("Begin testing list_pool<primitives_index_space_iterator>");
  ltest &= test_list_pool_facet<primitives_index_space_iterator>();
  print_footer("End testing list_pool<primitives_index_space_iterator>");

  print_header("Begin testing list_pool<ragged_array_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<ragged_array_implicit_index_space_iterator>();
  print_footer("End testing list_pool<ragged_array_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<reserved_primary_index_space_handle>");
  ltest &= test_list_pool_facet<reserved_primary_index_space_handle>();
  print_footer("End testing list_pool<reserved_primary_index_space_handle>");

  print_header("Begin testing list_pool<reserved_primary_index_space_iterator>");
  ltest &= test_list_pool_facet<reserved_primary_index_space_iterator>();
  print_footer("End testing list_pool<reserved_primary_index_space_iterator>");

  print_header("Begin testing list_pool<singleton_implicit_index_space_iterator>");
  ltest &= test_list_pool_facet<singleton_implicit_index_space_iterator>();
  print_footer("End testing list_pool<singleton_implicit_index_space_iterator>");

  print_header("Begin testing list_pool<singleton_index_space_handle>");
  ltest &= test_list_pool_facet<singleton_index_space_handle>();
  print_footer("End testing list_pool<singleton_index_space_handle>");

  print_header("Begin testing list_pool<singleton_index_space_iterator>");
  ltest &= test_list_pool_facet<singleton_index_space_iterator>();
  print_footer("End testing list_pool<singleton_index_space_iterator>");


  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

