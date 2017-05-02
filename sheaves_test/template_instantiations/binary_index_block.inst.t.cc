
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
/// Unit test driver for template class binary_index_block.

#include "SheafSystem/binary_index_block.impl.h"
#include "SheafSystemTest/test_utils.h"

using namespace std;
using namespace sheaf;

namespace // unnamed
{

  template<typename T>
  bool
  test_binary_index_block_facet()
  {
    // Preconditions:

    // Body:

    print_header("Begin testing \"binary_index_block\" facet:");

    print_subheader("Test binary_index_block(int xi_ub = 0, int xj_ub = 0)");

    //$$ISSUE: This constructor fails in the "invariant" function.
    //         Does this class work at all? Is it used?

//     binary_index_block<T> lblock(3, 5);
//     cout << lblock << endl;

//     print_subheader("Test binary_index_block(const binary_index_block& xother)");

//     binary_index_block<T> lblock_copy(lblock);
//     cout << lblock_copy << endl;

   print_footer("End testing \"binary_index_block\" facet:");

   // Postconditions:

    // Exit:

    return true;
  }

  template<typename T>
  bool
  run_test(const string& xtype)
  {
    // Preconditions:

    // Body:

    print_header("Begin testing binary_index_block<" + xtype + ">");

    bool xresult = true; 

    xresult &= test_binary_index_block_facet<T>();

    print_footer("End testing binary_index_block<" + xtype + ">");

    // Postconditions:

    // Exit:

    return xresult;
  }

} // end namespace // unnamed

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;
  ltest &= run_test<int>("int");
  ltest &= run_test<double>("double");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

