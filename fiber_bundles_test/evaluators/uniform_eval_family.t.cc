// $RCSfile: uniform_eval_family.t.cc,v $ $Revision: 1.16 $ $Date: 2012/03/01 00:40:39 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example evaluators/uniform_eval_family.t.cc
/// Test case for class uniform_eval_family

#include "assert_contract.h"
#include "factory.h"
#include "fiber_bundles_namespace.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "std_string.h"
#include "uniform_eval_family.h"

using namespace fiber_bundle;

int main(int argc, char* argv[])
{
  cout << "Testing uniform_eval_family:" << endl;

  cout << "  static name = " << uniform_eval_family::static_class_name() << endl;

  bool test = fiber_bundle::eval_family::family_factory().contains_prototype("uniform");

  cout << "  supported = " << boolalpha << test << noboolalpha << endl;

  fiber_bundles_namespace lns("uniform_eval_family.t");
  lns.get_read_write_access();
  fiber_bundle::eval_family* ef = fiber_bundle::eval_family::new_family("uniform", lns);

  cout << "  virtual name = " << ef->class_name() << endl;
  cout << "  size = " << ef->size() << endl;
}
