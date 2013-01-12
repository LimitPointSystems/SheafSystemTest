
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Test driver for class int_set.

#include "int_set.h"
#include "std_iostream.h"
#include "std_iomanip.h"
#include "subposet.h"
#include "test_utils.h"

using namespace sheaf;

namespace
{
  class int_set_child : public int_set
  {
  public:
    int_set_child() {}
    ~int_set_child() {}
  };
}

int
main()
{
  // Preconditions:

  // Body:

  print_header("Begin testing class int_set.");

  //============================================================================

  cout << boolalpha;
  int lmbrs[4] = {101, 102, 103, 104};

  //int_set();

  int_set lset;
  int_set lset_other;

  //int_set(const int_set& other);

  int_set lset_copy(lset);

  //int_set(const int* xmbrs, int xct);

  int_set lset2(lmbrs, 4);

  //~int_set();

  int_set* lset_ptr = new int_set;
  delete lset_ptr;

  //inline void insert_member(int xmbr);

  lset.insert_member(1);
  lset.insert_member(2);
  lset.insert_member(3);

  //inline void remove_member(int xmbr);

  lset.remove_member(2);

  //void insert_members(const int* xmbrs, int xct);


  lset.insert_members(lmbrs, 4);
  lset_other.insert_members(lmbrs, 4);

  //void insert_members(const subposet* xmbrs);

  // Need a namespace here.
  //subposet lsubposet;
  //lset2.insert_members(&lsubposet);

  //inline bool contains(int xindex) const;

  bool lcontains = lset.contains(3);
  cout << "lcontains = " << lcontains << endl;

  //inline bool contains_member(int xindex) const;

  bool lcontains_member = lset.contains_member(3);
  cout << "lcontains_member = " << lcontains_member << endl;

  //bool is_singleton() const;

  bool lis_singleton = lset.is_singleton();
  cout << "lis_singleton = " << lis_singleton << endl;

  //bool set_includes(const int_set* other,
  //                  bool this_is_much_larger = false) const;

  bool lset_includes_false = lset.set_includes(&lset_other, false);
  cout << "lset_includes_false = " << lset_includes_false << endl;

  bool lset_includes_true = lset.set_includes(&lset_other, true);
  cout << "lset_includes_true = " << lset_includes_true << endl;

  //int_set* set_union(const int_set* other) const;

  int_set* lset_union = lset.set_union(&lset_other);

  //void set_union_pa(const int_set* other, int_set* result) const;

  int_set lresult;
  lset.set_union_pa(&lset_other, &lresult);

  //void set_union_sa(const int_set* other);

  lset.set_union_sa(&lset_other);

  //int_set* set_intersection(const int_set* other) const;

  int_set* lset_intersection = lset.set_intersection(&lset_other);

  //void set_intersection_pa(const int_set* other, int_set* result) const;

  lset.set_intersection_pa(&lset_other, &lresult);

  //void set_intersection_sa(const int_set* other);

  lset.set_intersection_sa(&lset_other);

  //int_set* set_difference(const int_set* other) const;

  int_set* lset_difference = lset.set_difference(&lset_other);

  //void set_difference_pa(const int_set* other, int_set* result) const;

  lset.set_difference_pa(&lset_other, &lresult);

  //void set_difference_sa(int_set* other, bool this_is_much_larger = false);

  lset.set_difference_sa(&lset_other, false);

  lset.set_difference_sa(&lset_other, true);

  //void print() const;

  lset.print();

  //ostream& operator << (ostream& xos, const int_set& xc);

  cout << lset << endl;

  //============================================================================

  //$$HACK: To get better coverage of CTORs and DTORs.

  int_set_child* lchild = new int_set_child;
  delete lchild;

  //============================================================================

  print_footer("End testing class int_set.");

  // Postconditions:

  // Exit:

  return 0;
}

