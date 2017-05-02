
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

/// @example iterators/cover_set_iterator.t.cc
/// Unit test driver for class cover_set_iterator.

#include "SheafSystem/cover_set_iterator.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/std_iomanip.h"

///
int
main(int argc, char* argv[])
{
  // Create a default name space.

  namespace_poset lns("cover_set_iterator.t");
  lns.get_read_access();

  // Use alpha formt for bools.

  cout << boolalpha;

  // The primitives poset is convenient to test the iterators.

  // Test ctor and lower cover iteration:

  cover_set_iterator itr(lns.primitives().top().cover_iterator(LOWER));

  cout << endl << "Iterating over lower cover of primitives.top():" << endl << endl;

  while(!itr.is_done())
  {
    cout << "index: " << itr.item()
    << "\t" << left << setw(24) << lns.primitives().member_name(itr.item())
    << endl;

    itr.next();
  }

  // Test reset() and prefix increment:

  cout << endl << "Reset and do it again, with prefix increment:" << endl << endl;

  itr.reset();
  while(!itr.is_done())
  {
    cout << "index: " << itr.item()
    << "\t" << left << setw(24) << lns.primitives().member_name(itr.item())
    << endl;

    ++itr;
  }

  // Test reset() and postfix increment:

  cout << endl << "Reset and do it again, with postfix increment:" << endl << endl;

  itr.reset();
  while(!itr.is_done())
  {
    cout << "index: " << itr.item();
    cout  << "\t" << left << setw(24) << lns.primitives().member_name((itr++).item());
    cout << endl;
  }

  // Restore bool format to default.

  cout << noboolalpha;

  // Get write access to make destructors happy.

  lns.release_access();
  lns.get_read_write_access();

  // Exit:

  return(0);
}

