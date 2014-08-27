
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

/// @example template_instantiations/depth_first_itr.inst.t.cc
/// Unit test driver for template class depth_first_itr.

#include "depth_first_itr.h"

#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "test_sheaves.impl.h"
#include "test_utils.h"

using namespace std;
using namespace unordered;
using namespace sheaf;


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing depth_first_itr ...");

  bool ltest = true;

  //============================================================================

  //$$SCRIBBLE: Nothing here yet. depth_first_itr cannot be instantiated because
  //            all of it's constructors are protected. We can, however,
  //            create filtered_depth_first_itr instances which can be used
  //            to test the depth_first_itr facet
  //            (see filtered_depth_first_itr.inst.t.cc).

  //============================================================================

  print_footer("End testing depth_first_itr ...");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

