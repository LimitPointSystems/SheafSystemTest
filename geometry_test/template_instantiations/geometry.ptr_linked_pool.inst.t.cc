
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for class ptr_linked_pool.

#include "ptr_linked_pool.h"

#include "d_tree_point_locator_node.h"
#include "test_utils.h"

namespace
{

using namespace sheaf;
using namespace geometry;


//$$TODO: Move to test_geometry.impl.h.

///
/// Simple derived class for ptr_linked_pool with only
/// a  default constructor and destructor.
///
template<typename T>
class ptr_linked_pool_child : public ptr_linked_pool<T>
{
public:
    ptr_linked_pool_child(size_t xcapacity=16) {}
    ~ptr_linked_pool_child() {}
};

template<typename T>
bool
test_ptr_linked_pool()
{
  // Preconditions:

  // Body:

  print_subheader("Testing ptr_linked_pool<T>(size_t xcapacity = 1024)");

  // Default case.
 
  ptr_linked_pool<T> lpool0;

  // Specify capacity (small number for testing).

  ptr_linked_pool<T> lpool(4);

  print_subheader("Testing void reserve(size_t xcapacity)");

  lpool.reserve(10);

  print_subheader("Testing size_t capacity()");

  size_t lcapacity = lpool.capacity();
  cout << "lpool.capacity() = " << lcapacity << endl;

  print_subheader("Testing size_t free_size()");

  size_t lfree_size = lpool.free_size();
  cout << "lpool.free_size() = " << lfree_size << endl;

  print_subheader("Testing size_t allocated_size()");

  size_t lallocated_size = lpool.allocated_size();
  cout << "lpool.allocated_size() = " << lallocated_size << endl;

  print_subheader("Testing void print()");

  lpool.print();

  print_subheader("Testing T* allocate()");

  // Do this enough times to force increased capacity
  // (could use a loop).

  T* lptr0 = lpool.allocate();
  T* lptr1 = lpool.allocate();
  T* lptr2 = lpool.allocate();
  T* lptr3 = lpool.allocate();
  T* lptr4 = lpool.allocate();
  T* lptr5 = lpool.allocate();
  T* lptr6 = lpool.allocate();
  T* lptr7 = lpool.allocate();
  T* lptr8 = lpool.allocate();
  T* lptr9 = lpool.allocate();
  T* lptr10 = lpool.allocate();

  print_subheader("Testing void deallocate(T* xobject)");

  lpool.deallocate(lptr0);

  print_subheader("Testing ostream& operator<<(",
                  "    ostream& xos,const ptr_linked_pool<T>& xp);)");

  cout << lpool << endl;

  print_subheader("Testing derived class CTOR/DTOR");

  ptr_linked_pool_child<T> lchild;

  // Postconditions:

  // Exit:

  // Just return true for now.

  return true;
}

} //end namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing ptr_linked_pool_facet");

  bool ltest = true;

  //============================================================================

  print_header("Begin testing ptr_linked_pool<d_tree_point_locator_node<1, 1>");
  ltest &= test_ptr_linked_pool<d_tree_point_locator_node<1, 1> >();

  print_header("Begin testing ptr_linked_pool<d_tree_point_locator_node<2, 2>");
  ltest &= test_ptr_linked_pool<d_tree_point_locator_node<2, 2> >();

  print_header("Begin testing ptr_linked_pool<d_tree_point_locator_node<3, 3>");
  ltest &= test_ptr_linked_pool<d_tree_point_locator_node<3, 3> >();

  // d_tree_point_locator_node<4, 4> is not instantiated.
  //print_header("Begin testing ptr_linked_pool<d_tree_point_locator_node<4, 4>");
  //ltest &= test_ptr_linked_pool<d_tree_point_locator_node<4, 4> >();

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing ptr_linked_pool_facet");

  // Postconditions:

  // Exit:

  return lresult;
}
