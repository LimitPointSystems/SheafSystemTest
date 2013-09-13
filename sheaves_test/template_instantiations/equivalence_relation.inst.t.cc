
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
/// Unit test driver for class equivalence_relation.

#include "equivalence_relation.impl.h"

#include "test_utils.h"

using namespace sheaf;

namespace
{

template<typename T>
bool
test_equivalence_relation_facet()
{
  // Preconditions:

  // Body:

  //$$TODO: Comment.

  bool lresult = true;

  equivalence_relation<T> lrelation;

  equivalence_relation<T> lcopy(lrelation);

  equivalence_relation<T> lassign = lrelation;

  equivalence_relation<T>* lclone = lrelation.clone();

  delete lclone;

  equivalence_relation<T>* lrelation_ptr = new equivalence_relation<T>;

  delete lrelation_ptr;

  bool linvariant = lrelation.invariant();

  bool lis_ancestor_of = lrelation.is_ancestor_of(&lcopy);

  //============================================================================

  const T lmbr_id = T(1);
  const T lrep_id = T(2);
  const T lother_mbr_id = T(3);
  const T lother_rep_id = T(4);

  //void insert_equivalence(const T& xmbr_id, const T& xrep_id);

  lrelation.insert_equivalence(lmbr_id, lrep_id);
  lrelation.insert_equivalence(lother_mbr_id, lother_rep_id);

  //bool contains_representative(const T& xmbr_id) const;

  bool lcontains_representative = lrelation.contains_representative(lmbr_id);


  //bool contains_unique_representative(const T& xrep_id) const;

  bool lcontains_unique_representative =
    lrelation.contains_unique_representative(lrep_id);


  //bool contains_equivalence(const T& xmbr_id, const T& xother_mbr_id) const;

  bool lcontains_equivalence =
    lrelation.contains_equivalence(lmbr_id, lother_mbr_id);

  //T representative(const T& xmbr_id) const;

   T lrepresentative = lrelation.representative(lmbr_id);

  //range_type equivalence_class(const T& xrep_id) const

  typename equivalence_relation<T>::range_type lequivalence_class =
    lrelation.equivalence_class(lrep_id);

  //range_type all_equivalences() const;

  typename equivalence_relation<T>::range_type lequivalences =
    lrelation.all_equivalences();

  //ostream& operator<<(ostream& xos, const range_type& xrange);

  //$$SCRIBBLE: This insertion operator is explicitly instantiated
  //            but the compiler doesn't seem to be able to find it.

  //cout << "lequivalences = \n" << lequivalences << endl;

  //ostream& operator<<(ostream& xos, const equivalence_relation<T>& xer);

  cout << "lrelation = \n" << lrelation << endl;

  //void delete_equivalence(const T& xmbr_id);

  lrelation.delete_equivalence(lmbr_id);

  //============================================================================


  // Postconditions:

  // Exit:

  return lresult;

}


} //end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing equivalence_relation facet");

  bool ltest = true;

  //============================================================================

  ltest &= test_equivalence_relation_facet<int>();

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing equivalence_relation facet");

  // Postconditions:

  // Exit:

  return lresult;
}
