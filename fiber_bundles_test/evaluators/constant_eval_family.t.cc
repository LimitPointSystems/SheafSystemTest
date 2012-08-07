// $RCSfile: constant_eval_family.t.cc,v $ $Revision: 1.12 $ $Date: 2012/03/01 00:40:37 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example evaluators/constant_eval_family.t.cc
/// Test case for class constant_eval_family

#include "assert_contract.h"
#include "constant_eval_family.h"
#include "factory.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "std_string.h"

using namespace fiber_bundle;

int main(int argc, char* argv[])
{
  cout << "Testing constant_eval_family:" << endl;

  cout << "  static name = " << constant_eval_family::static_class_name() << endl;

  bool test = fiber_bundle::eval_family::family_factory().contains_prototype("constant");

  cout << "  supported = " << boolalpha << test << noboolalpha << endl;

  fiber_bundles_namespace lns("constant_eval_family.t");
  lns.get_read_write_access();
  fiber_bundle::eval_family* ef =  fiber_bundle::eval_family::new_family("constant", lns);

  cout << "  virtual name = " << ef->class_name() << endl;
  cout << "  size = " << ef->size() << endl;
}
