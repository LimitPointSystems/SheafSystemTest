
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

/// Unit test for class zn_to_bool.

#include "zn_to_bool.h"

#include "assert_contract.h"
#include "block.h"
#include "index_iterator.h"
#include "index_space_family.h"
#include "namespace_poset.h"
#include "std_iostream.h"

using namespace std;
using namespace sheaf;

int
main()
{

  int true_array[3] = {0,4,32};
  block<int> indices(3,3,true_array);

  zn_to_bool* x = new zn_to_bool(33);
  assertion(x != 0);

  // Create a scope for the index_iterator.

  namespace_poset::initialize_id_space_prototypes();

  index_space_family lid_spaces;
  lid_spaces.new_id(0);
  lid_spaces.new_id(4);
  lid_spaces.new_id(32);

  cout << "new zn_tobool should have ct() = 33: ct() = " << x->ct() << endl;

  cout << "new zn_to_bool should be all zeroes: " << *x << endl;

  x->put(0, true);
  x->put(4, true);
  x->put(32, true);

  cout << "zn_to_bool should have 1st, 5th, and 33rd bits set: " << *x << endl;

  cout << "we should get the same result using operator[]: ";

  for(int i=0;i<x->ub();i++)
  {
    cout << (*x)[i] << ' ';
  }
  cout << endl;

  cout << "the index iterator should visit items 0 4 and 32: ";

  index_iterator itr(x, lid_spaces.hub_id_space());
  while(!itr.is_done())
  {
    cout << itr.item() << " ";
    itr.next();
  }
  cout << endl;


  cout << "true_ct() = " << x->true_ct() << " should be 3" << endl;
  cout << "and false_ct() = " << x->false_ct() << " should be 30" << endl;

  cout << "is_true_for({0,4,32}) = " << x->is_true_for(&indices) << " should be true" << endl;
  cout << "but is_true() = " << x->is_true() << " should be false" << endl;
  cout << "and is_false() = " << x->is_false() << " should be false" << endl;

  x->put( 0, false );
  x->put( 4, false );
  x->put_not(32);

  cout << "now is_false_for({0,4,32}) = " << x->is_false_for(&indices) << " should be true" << endl;


  cout << "in fact, zn_to_bool should be all zeroes again: " << *x << endl;

  cout << "so is_false() = " << x->is_false() << " should be true " << endl;

  cout << "and is_true() = " << x->is_true() << " should be false " << endl;

  x->put(&indices, true);

  cout << "now we've turned 0,4,32 on with a block put: " << *x << endl;

  x->put_not(&indices);

  cout << "now we've turned them off again with a block put_not: " << *x << endl;

  zn_to_bool* y = x->make_true();

  cout << "y = x->make_true so y->is_true() = " << y->is_true() << " should be true" << endl;

  zn_to_bool* z = x->make_false();

  cout << "z = x->make_false so z->is_false() = " << z->is_false() << " should be true" << endl;

  x->put(&indices, true);
  y->put(&indices, false);
  z->put(&indices, true);

  cout << "x->is_equal_to(z) = " << x->is_equal_to(z) << " should be true" << endl;

  cout << "y->is_equal_to(z->b_not()) = " << y->is_equal_to(z->b_not()) << " should be true" << endl;

  cout << "y->b_and(z)->is_false() = " << y->b_and(z)->is_false() << " should be true" << endl;

  cout << "y->b_or(z)->is_true() = " << y->b_or(z)->is_true() << " should be true" << endl;

  cout << "y->b_and_not(z)->is_equal_to(y) = " << y->b_and_not(z)->is_equal_to(y) << " should be true" << endl;

  return 0;
}
