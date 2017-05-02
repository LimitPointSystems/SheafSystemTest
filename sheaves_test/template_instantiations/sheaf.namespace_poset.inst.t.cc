
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

/// @example template_instantiations/namespace_poset.inst.t.cc
/// Unit test driver for class namespace_poset template functions.

#include "SheafSystem/sheaves_namespace.h"
#include "SheafSystemTest/test_sheaves.impl.h"
#include "SheafSystemTest/test_utils.h"

#include "SheafSystem/primitives_poset.h"
#include "SheafSystem/primitives_poset_schema.h"
#include "SheafSystem/namespace_poset_schema.h"
#include "SheafSystem/refinable_poset.h"

using namespace std;
using namespace sheaf;


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing namespace_poset facet");

  bool ltest = true;

  sheaves_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  // primitives_poset

  primitives_poset& lprimitives = lns.primitives();
  ltest &= test_namespace_poset_facet<primitives_poset>(lns, lprimitives);

  // primitives_poset_schema

  primitives_poset_schema& lprimitives_schema = lns.primitives_schema();
  ltest &= test_namespace_poset_facet<primitives_poset_schema>(lns, lprimitives_schema);


   // namespace_poset_schema
 
  namespace_poset_schema& lnamespace_schema = lns.namespace_schema();
  ltest &= test_namespace_poset_facet<namespace_poset_schema>(lns, lnamespace_schema);


  // refinable_poset
 
  // Make a triangle (refinable_poset) in the namespace named "cells".

  sheaves_namespace::make_triangle(&lns);

  // Get the poset with read access.
  refinable_poset& lposet = lns.member_poset<refinable_poset>("cells", true);
  lposet.get_read_access();

  //Test it.

  ltest &= test_namespace_poset_facet<refinable_poset>(lns, lposet);


  //============================================================================

  print_footer("End testing namespace_poset facet");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}


/*
Instantiations:

namespace_poset_schema* sheaf::namespace_poset::member_poset<sheaf::namespace_poset_schema>(sheaf::poset_path const&, bool) const
poset* sheaf::namespace_poset::member_poset<sheaf::poset>(sheaf::poset_path const&, bool) const
poset_state_handle* sheaf::namespace_poset::member_poset<sheaf::poset_state_handle>(sheaf::poset_path const&, bool) const
primitives_poset* sheaf::namespace_poset::member_poset<sheaf::primitives_poset>(sheaf::poset_path const&, bool) const
primitives_poset_schema* sheaf::namespace_poset::member_poset<sheaf::primitives_poset_schema>(sheaf::poset_path const&, bool) const
refinable_poset& sheaf::namespace_poset::new_member_poset<sheaf::refinable_poset>(std::string const&, sheaf::poset_path const&, sheaf::arg_list const&, bool)
refinable_poset* sheaf::namespace_poset::member_poset<sheaf::refinable_poset>(sheaf::poset_path const&, bool) const
refinable_poset* sheaf::namespace_poset::member_poset<sheaf::refinable_poset>(std::string const&, bool) const
*/
