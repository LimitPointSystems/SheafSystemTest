
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class sheaves_abstract_poset_member.

#include "test_sheaves.h"
#include "test_utils.h"

using namespace sheaf;


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  print_header("Begin testing abstract_poset_member");

  ltest &= test_abstract_poset_member_facet(); // $$TODO: Parameterize.

  print_header("End testing abstract_poset_member");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

