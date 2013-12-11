
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

// Unit test driver for class connectivity_array.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "connectivity_array.h"

#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_utils.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  bool
  test_connectivity_array_facet()
  {
    cout << boolalpha;
    typedef connectivity_array::index_type index_type;

    //connectivity_array();

    connectivity_array larray;

    //connectivity_array(index_type* xcol_cts,
    //                   index_type xcol_cts_ub);

    index_type lcol_cts[4] = {2, 2, 2, 2};
    connectivity_array larray2(lcol_cts, 4);

    //connectivity_array(index_type xrow_ct, index_type xvalue_ct);

    connectivity_array larray3(4, 8);

    //connectivity_array(const connectivity_array& xother);

    connectivity_array larray_copy(larray2);

    //virtual ~connectivity_array();

    connectivity_array* larray_ptr = new connectivity_array(larray2);
    delete larray_ptr; 

    //virtual connectivity_array* clone() const;

    connectivity_array* lclone = larray2.clone();
    delete lclone; 

    //virtual bool invariant() const;

    bool linvariant = larray2.invariant();
    cout << "linvariant = " << linvariant << endl; 

    //virtual bool is_ancestor_of(const any* xother) const;

   bool lis_ancestor_of = larray2.is_ancestor_of(&larray3);
    cout << "lis_ancestor_of = " << lis_ancestor_of << endl; 

    //scoped_index* types() const;

    scoped_index* ltypes = larray2.types();

    //scoped_index type(index_type xrow_index) const;

    scoped_index ltype = larray2.type(2);

    return true;
  }
}

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing connectivity_array");

  bool ltest = true;

  ltest &= test_connectivity_array_facet();

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing connectivity_array");

  // Postconditions:

  // Exit:

  return lresult;
}

