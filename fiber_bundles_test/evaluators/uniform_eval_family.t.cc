
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

/// @example evaluators/uniform_eval_family.t.cc
/// Test case for class uniform_eval_family

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/factory.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/uniform_eval_family.h"

using namespace std;
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
