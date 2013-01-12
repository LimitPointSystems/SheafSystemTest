
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for class d_bin_coordinates.

#include "d_bin_coordinates.h"

#include "geometry.h"
#include "test_utils.h"

using namespace geometry;

namespace
{

///
/// Simple derived class for d_bin_coordinates with only
/// a default constructor and destructor.
///
template<int DC, int DB>
class d_bin_coordinates_child : public d_bin_coordinates<DC, DB>
{
public:
  d_bin_coordinates_child() {}
  ~d_bin_coordinates_child() {}
};

template<int DC, int DB>
bool
test_d_bin_coordinates_facet()
{
  // Preconditions:

  // Body:

  bool lresult = true;

  print_subheader("Testing d_bin_coordinates()");

  d_bin_coordinates<DC, DB> lcoords;

  typedef typename d_bin_coordinates<DC, DB>::value_type value_type;
  typedef typename d_bin_coordinates<DC, DB>::int_type int_type;

  value_type* lvalues = new value_type[DC];
  for(int i=0; i<DC; ++i)
  {
    lvalues[i] = 100+i;
  } 
  lcoords = lvalues;

  cout << lcoords << endl;

  d_bin_coordinates<DC, DB> lcoords2(lcoords);

  cout << lcoords2 << endl;

  d_bin_coordinates<DC, DB> lcoords3 = lcoords2;

  cout << lcoords3 << endl;

  bool lequal = (lcoords3 == lcoords);
  cout << "lequal = " << boolalpha << lequal << endl;

  bool lless = (lcoords3 < lcoords);
  cout << "lless = " << boolalpha << lless << endl;

  bool lless_eql = (lcoords3 <= lcoords);
  cout << "lless_eql = " << boolalpha << lless_eql << endl;

  d_bin_coordinates<DC, DB> lcoords4(lvalues);

  cout << lcoords4 << endl;

  //d_bin_coordinates<DC, DB> lcoords5;
  //lcoords5 -= lcoords4;
  //cout << lcoords5 << endl;

  d_bin_coordinates<DC, DB> lcoords6;
  lcoords6 >>= 1;

  cout << lcoords6 << endl;

  //==================================================================

  size_type lbits = lcoords.bits();

  size_type lleftmost = lcoords.leftmost_bit_id();

  size_type lrightmost = lcoords.rightmost_bit_id();

  size_type ldegree = lcoords.degree();

  const int_type& lint_const = lcoords[DC-1];

  int_type& lint = lcoords[DC-1];

  bool leql2 = (lcoords == lint);
  cout << "leql2 = " << boolalpha << leql2 << endl;

  //==================================================================

  lcoords[DC-1] = 0;

  //==================================================================

  // For cases where DB == DC, there are specializations.
  // For cases where DB != DC, the functions are "not_implemented".

  if(DB == DC)
  {
    lcoords.put_branch(0, 0);

    size_type lbranch = lcoords.branch(0);
  }

  //============================================================================

  print_subheader("Testing derived class CTOR/DTOR");

  d_bin_coordinates_child<DC, DB> lchild;

  //============================================================================

  // Cleanup:

  print_subheader("Testing ~d_bin_coordinates via delete");

  //delete lbox_ptr;
  //delete lbox_ptr2;

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

  print_header("Begin testing d_bin_coordinates_facet<DB, DC>:");

  bool ltest = true;

  //============================================================================

  print_header("Testing d_bin_coordinates_facet<1, 0>:");
  ltest &= test_d_bin_coordinates_facet<1, 0>();

  print_header("Testing d_bin_coordinates_facet<2, 0>:");
  ltest &= test_d_bin_coordinates_facet<2, 0>();

  print_header("Testing d_bin_coordinates_facet<3, 0>:");
  ltest &= test_d_bin_coordinates_facet<3, 0>();

  print_header("Testing d_bin_coordinates_facet<4, 0>:");
  ltest &= test_d_bin_coordinates_facet<4, 0>();

  print_header("Testing d_bin_coordinates_facet<1, 1>:");
  ltest &= test_d_bin_coordinates_facet<1, 1>();

  print_header("Testing d_bin_coordinates_facet<3, 1>:");
  ltest &= test_d_bin_coordinates_facet<3, 1>();

  print_header("Testing d_bin_coordinates_facet<2, 2>:");
  ltest &= test_d_bin_coordinates_facet<2, 2>();

  print_header("Testing d_bin_coordinates_facet<3, 2>:");
  ltest &= test_d_bin_coordinates_facet<3, 2>();

  print_header("Testing d_bin_coordinates_facet<3, 3>:");
  ltest &= test_d_bin_coordinates_facet<3, 3>();

  print_header("Testing d_bin_coordinates_facet<4, 4>:");
  ltest &= test_d_bin_coordinates_facet<4, 4>();

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing d_bin_coordinates_facet<DB, DC>:");

  // Postconditions:

  // Exit:

  return lresult;
}
