
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Test driver for deep_size.

#include "sheaves_namespace.h"
#include "deep_size.h"

using namespace sheaf;

int
main()
{
  // Create top level poset with primitive type definitions.

  sheaves_namespace lns("test_namespace");
  lns.get_read_write_access();

  size_t ldeep_size = deep_size(lns);

  cout << endl;
  cout << "### deep_size(lns) = " << ldeep_size << endl;
  cout << endl;

  //   poset* empty_poset = new poset( lns, &(lns->primitives().schema()), "empty");

  //   size_t ds = empty_poset->deep_size();
  //   cout << "$$$ empty_poset->deep_size() = " << ds << endl;


  return 0;
}

