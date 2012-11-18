// $RCSfile: section_space_schema_index_map.t.cc,v $ $Revision: 1.9 $ $Date: 2012/07/04 16:42:09 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example id_spaces/section_space_schema_index_map.t.cc
/// Test driver for class section_space_schema_index_map.

#include "arg_list.h"
#include "array_index_map.h"
#include "explicit_product_index_space.h"
#include "gluable_sum_index_space.h"
#include "index_space_family.h"
#include "simple_index_space.h"
#include "section_space_schema_index_map.h"
#include "scoped_index.h"
#include "std_strstream.h"
#include "test_index_spaces.h"
#include "test_utils.h"

using namespace fiber_bundle;

namespace
{

///
/// Test a product_index_space created with an section_space_schema_index_map.
///
void
test_section_space_schema_id_map(size_t xbase_ub,
				 size_t xfiber_schema_ub,
				 pod_index_type xfiber_schema_top_end)
{
  // Create the base id space.

  print_header("Create the base id space.");

  // Create the base space top id space.

  index_space_family lbase_family;
  lbase_family.top_id_space().new_id(); // top
  lbase_family.top_id_space().new_id(); // bottom
  lbase_family.new_primary_id_space(xbase_ub); // base space interval.

  // Create the discretization id space.

  arg_list ldisc_map_args = array_index_map::make_arg_list(xbase_ub);
  arg_list ldisc_space_args =
    simple_index_space::make_arg_list("array_index_map", ldisc_map_args);

  index_space& ldisc_id_space = make_id_space(lbase_family,
					      "test_disc_id_space",
					      "simple_index_space",
					      ldisc_space_args);
  array_index_map& ldisc_id_map = ldisc_id_space.id_map<array_index_map>();

  for(pod_index_type i=0; i < xbase_ub; i++)
  {
    push_back(ldisc_id_map, i+RESERVED_TERM_SIZE); // Start at the interval.
  }

  test_space_iterator(ldisc_id_space, true);

  // Create the fiber schema id space.

  print_header("Create the fiber schema id space.");

  // Create the fiber schema top id space.

  index_space_family lfiber_schema_family;
  lfiber_schema_family.top_id_space().new_id(); // top
  lfiber_schema_family.top_id_space().new_id(); // bottom
  for(pod_index_type i=0; i < xfiber_schema_ub; i++)
  {
    lfiber_schema_family.top_id_space().new_id(); // fiber component(i)
  }

  // Create the fiber schema id space.
  
  arg_list lfiber_schema_map_args = array_index_map::make_arg_list(xfiber_schema_ub);
  arg_list lfiber_schema_space_args =
    simple_index_space::make_arg_list("array_index_map", lfiber_schema_map_args);

  index_space& lfiber_schema_id_space = make_id_space(lfiber_schema_family,
						      "test_fiber_schema_id_map",
						      "simple_index_space",
						      lfiber_schema_space_args);
  array_index_map& lfiber_schema_id_map = lfiber_schema_id_space.id_map<array_index_map>();

  for(pod_index_type i=0; i < xfiber_schema_ub; i++)
  {
    push_back(lfiber_schema_id_map, i+2); // +2 to skip top and bottom.
  }

  test_space_iterator(lfiber_schema_id_space, true);

  // Test section_space_schema_index_map.

  print_header("Test section_space_schema_index_map.");

  // Create the top id space for the section space schema index.

  index_space_family lproduct_family;
  lproduct_family.new_primary_id_space(ldisc_id_map.range_end() *
				       xfiber_schema_top_end); // interval

  // Create the product id space.

  arg_list lproduct_map_args =
    section_space_schema_index_map::make_arg_list(ldisc_id_map,
						  lfiber_schema_id_map,
						  xfiber_schema_top_end);

  arg_list lproduct_space_args =
    explicit_product_index_space::make_arg_list("section_space_schema_index_map",
						lproduct_map_args);

  index_space& lproduct_id_space = make_id_space(lproduct_family,
						 "test_product_id_space",
						 "explicit_product_index_space",
						 lproduct_space_args);

  // Output the map values.

  print_map_extrema(lproduct_id_space);

  // Test the iterators.

  test_range_id_iterator(lproduct_id_space);
  test_domain_id_iterator(lproduct_id_space);
  test_space_iterator(lproduct_id_space, true);
  test_space_iterator(lproduct_id_space, false);
}

} // unnamed namespace

///
/// Main routine for testing section_space_schema_index_map.
///
int main(int argc, char** argv)
{
  size_t lbase_ub = argc > 1 ? atoi(argv[1]) : 10;
  size_t lfiber_schema_ub = argc > 2 ? atoi(argv[2]) : 3;
  pod_index_type lfiber_schema_top_end = argc > 3 ? atoi(argv[3]) :128;

  assertion(lbase_ub >= 2);
  assertion(lfiber_schema_ub >= 2);
  assertion(lfiber_schema_top_end >= 2*lfiber_schema_ub);

  // Test the section_space_schema_index_map.

  test_section_space_schema_id_map(lbase_ub, lfiber_schema_ub,
				   lfiber_schema_top_end);

  return 0;
}


