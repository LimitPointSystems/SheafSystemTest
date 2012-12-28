// $RCSfile: int_set.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:34 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Test driver for class int_set.

#include "int_set.h"
#include "std_iostream.h"
#include "std_iomanip.h"
#include "test_utils.h"

using namespace sheaf;

// namespace
// {
//   class int_set_child : public int_set
//   {
//   public:
//     int_set_child() {}
//     virtual ~int_set_child() {}
//   };
// }

int
main()
{
  // Preconditions:

  // Body:

  print_header("Begin testing class int_set.");

  //============================================================================

  cout << boolalpha;

  //int_set();

  int_set lset;

  //int_set(const int_set& other);

  int_set lset_copy(lset);

  //int_set(const int* xmbrs, int xct);

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

  int lmbrs[4] = {101, 102, 103, 104};
  lset.insert_members(lmbrs, 4);

  //void insert_members(const subposet* xmbrs);

  //.......

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

  //.......

  //int_set* set_union(const int_set* other) const;

  //void set_union_pa(const int_set* other, int_set* result) const;

  //void set_union_sa(const int_set* other);

  //int_set* set_intersection(const int_set* other) const;

  //void set_intersection_pa(const int_set* other, int_set* result) const;

  //void set_intersection_sa(const int_set* other);

  //int_set* set_difference(const int_set* other) const;

  //void set_difference_pa(const int_set* other, int_set* result) const;

  //void set_difference_sa(int_set* other, bool this_is_much_larger = false);

  //void print() const;

  lset.print();

  //ostream& operator << (ostream& xos, const int_set& xc);

  cout << lset << endl;

  //============================================================================

  //$$HACK: To get better coverage of CTORs and DTORs.

//   int_set_child* lchild = new int_set_child;
//   delete lchild;

  //============================================================================

  print_footer("End testing class int_set.");

  // Postconditions:

  // Exit:

  return 0;
}

