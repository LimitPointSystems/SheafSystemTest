// $RCSfile: equivalence_relation.inst.t.cc,v $ $Revision: 1.1.2.4 $ $Date: 2012/10/24 02:00:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for class equivalence_relation.

#include "equivalence_relation.h"

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

  typename equivalence_relation<T>::range_type lequivalences =
    lrelation.all_equivalences();

  T lmbr_id = T(0);
  bool lcontains_representative = lrelation.contains_representative(lmbr_id);

  T lrep_id = T(0);
  bool lcontains_unique_representative =
    lrelation.contains_unique_representative(lrep_id);

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
