
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example template_instantiations/namespace_poset.inst.t.cc
/// Unit test driver for class namespace_poset template functions.

#include "sheaves_namespace.h"
#include "test_sheaves.impl.h"
#include "test_utils.h"

#include "primitives_poset.h"
#include "primitives_poset_schema.h"
#include "namespace_poset_schema.h"
#include "refinable_poset.h"

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
