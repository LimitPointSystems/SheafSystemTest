
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example template_instantiations/name_map.inst.t.cc
/// Unit test driver for template class name_map.

#include "name_map.h"
#include "test_sheaves.impl.h"

using namespace sheaf;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // pod_index_type

  print_header("Begin testing name_map<pod_index_type>");
  ltest &= test_any_facet<name_map<pod_index_type> >();
  ltest &= test_name_map_facet<pod_index_type>();
  print_footer("End testing name_map<pod_index_type>");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

