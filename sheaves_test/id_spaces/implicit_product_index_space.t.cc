// $RCSfile: implicit_product_index_space.t.cc,v $ $Revision: 1.6 $ $Date: 2012/07/04 16:42:20 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example id_spaces/implicit_product_index_space.t.cc
/// Test driver for class implicit_product_index_space.

#include "implicit_product_index_space.h"

#include "arg_list.h"
#include "index_space_family.h"
#include "offset_index_map.h"
#include "scoped_index.h"
#include "simple_index_space.h"
#include "std_strstream.h"
#include "test_index_spaces.h"

using namespace sheaf;

namespace
{

///
/// Test binary implicit_product_index_space.
///
void
test_binary(size_type xi_size, size_type xj_size)
{
  print_header("Test binary implicit_product_index_space.");

  // Create the top id space.

  size_type lzone_size = xi_size*xj_size;
  size_type lvertex_size = (xi_size + 1)*(xj_size + 1);
  size_type lsize = 1 + lzone_size + lvertex_size;

  index_space_family lid_spaces;
  lid_spaces.new_primary_id_space(lsize);

  // Create the product id space.

  arg_list lmap_args = offset_index_map::make_arg_list(1, 1+lzone_size);
  arg_list lspace_args =
    implicit_product_index_space::make_arg_list(xi_size, xj_size,
						"offset_index_map",
						lmap_args);

  index_space& lspace = make_id_space(lid_spaces,
				      "test_binary",
				      "implicit_product_index_space",
				      lspace_args);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

}

///
/// Test ternary implicit_product_index_space.
///
void
test_ternary(size_type xi_size, size_type xj_size, size_type xk_size)
{
  print_header("Test ternary implicit_product_index_space.");

  // Create the top id space.

  size_type lzone_size = xi_size*xj_size*xk_size;
  size_type lvertex_size = (xi_size + 1)*(xj_size + 1)*(xk_size + 1);
  size_type lsize = 1 + lzone_size + lvertex_size;

  index_space_family lid_spaces;
  lid_spaces.new_primary_id_space(lsize);

  // Create the product id space.

  arg_list lmap_args = offset_index_map::make_arg_list(1+lzone_size, lsize);
  arg_list lspace_args =
    implicit_product_index_space::make_arg_list(xi_size+1, xj_size+1, xk_size+1,
						"offset_index_map",
						lmap_args);

  index_space& lspace = make_id_space(lid_spaces,
				      "test_ternary",
				      "implicit_product_index_space",
				      lspace_args);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

}

} // unnamed namespace

///
/// Main routine for testing implicit_product_index_space.  Simulate the
/// zone product id space for structured_block_2d (test_binary) and
/// the vertex product id space for structured_block_3d (test_ternary).
///
int main(int argc, char** argv)
{
  size_t li_size = (argc > 1) ? atoi(argv[1]) : 4;
  size_t lj_size = (argc > 2) ? atoi(argv[2]) : 3;
  size_t lk_size = (argc > 3) ? atoi(argv[3]) : 2;

  assertion(li_size > 0);
  assertion(lj_size > 0);
  assertion(lk_size > 0);
  
  test_binary(li_size, lj_size);
  test_ternary(li_size, lj_size, lk_size);

  return 0;
}


