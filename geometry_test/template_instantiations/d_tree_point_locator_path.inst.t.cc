
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
/// Unit test driver for class d_tree_point_locator_path.

#include "d_tree_point_locator_path.h"

#include "geometry.h"
#include "test_utils.h"

using namespace std;
using namespace geometry;

#include <cstdlib>


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing d_tree_point_locator_path_facet<???>:");

  bool ltest = true;

  //============================================================================

  //$$SCRIBBLE: We test d_tree_point_locator_path in d_tree_point_locator.inst.t
  //            because we need a d_tree_point_locator to instantiate a
  //            d_tree_point_locator_path and we already create them there.

  cout << "d_tree_point_locator_path is tested in d_tree_point_locator.inst.t"
       << endl;

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing d_tree_point_locator_path_facet<???>:");

  // Postconditions:

  // Exit:

  return lresult;
}
