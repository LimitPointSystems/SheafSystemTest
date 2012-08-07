// $RCSfile: deep_size.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example support/deep_size.t.cc
/// Test driver for deep_size().

#include "sheaves_namespace.h"

int main()
{
  // Create top level poset with primitive type definitions.

  sheaves_namespace* lns = new sheaves_namespace("lns");
  lns->get_read_write_access();

  size_t ldeep_size = deep_size(*lns);

  cout << endl;
  cout << "### deep_size(*lns) = " << ldeep_size << endl;
  cout << endl;

  //   poset* empty_poset = new poset( lns, &(lns->primitives().schema()), "empty");

  //   size_t ds = empty_poset->deep_size();
  //   cout << "$$$ empty_poset->deep_size() = " << ds << endl;

  //lns->detach_from_state();
  //lns->release_access();

  //delete lns;

  return 0;
}

