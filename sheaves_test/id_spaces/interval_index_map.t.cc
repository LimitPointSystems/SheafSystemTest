// $RCSfile: interval_index_map.t.cc,v $ $Revision: 1.11 $ $Date: 2012/07/04 16:42:20 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example id_spaces/interval_index_map.t.cc
/// Test driver for class interval_index_map.

#include "interval_index_map.h"

#include "arg_list.h"
#include "index_space_family.h"
#include "interval_index_map_iterator.h"
#include "scoped_index.h"
#include "simple_index_space.h"
#include "std_strstream.h"
#include "test_index_spaces.h"
#include "test_utils.h"

using namespace sheaf;

namespace
{

///
/// Insert the interval ([xdomain_begin, xdomain_end] [xrange_begin, xrange_end])
/// into xmap.
///
void
insert_interval(interval_index_map& xmap,
		index_map::pod_type xdomain_begin, index_map::pod_type xdomain_end,
		index_map::pod_type xrange_begin, index_map::pod_type xrange_end)
{
  // Output the operation.

  strstream lstr;
  lstr << "insert_interval(" << xdomain_begin << ", " << xdomain_end << ", "
       << xrange_begin << ", " << xrange_end << ")";

  print_action(lstr.str());

  // Insert the interval.

  xmap.insert_interval(xdomain_begin, xdomain_end, xrange_begin, xrange_end);
}

///
/// Remove the interval [xrange_begin, xrange_end] from xmap.
///
void
remove_interval(interval_index_map& xmap,
		index_map::pod_type xrange_begin,
		index_map::pod_type xrange_end)
{
  // Output the operation.

  strstream lstr;
  lstr << "remove_interval(" << xrange_begin << ", " << xrange_end << ")";

  print_action(lstr.str());

  // Remove the interval.

  xmap.remove_interval(xrange_begin, xrange_end);
}

///
/// Test iterating over the domain intervals of xmap.
///
void
test_domain_interval_iterator(interval_index_map& xmap)
{
  print_subheader("Iterating over the domain intervals");

  interval_index_map_iterator* litr =
    dynamic_cast<interval_index_map_iterator*>(xmap.iterator(true));

  while(!litr->is_done())
  {
    cout << "domain interval: [" << litr->domain_interval_begin() << ", " 
	 << litr->domain_interval_end() << " ]\trange interval: ["
	 << litr->range_interval_begin() << ", "
	 << litr->range_interval_end() << " ]" << endl;

    litr->next_interval();
  }
}

///
/// Test iterating over the range intervals of xmap.
///
void
test_range_interval_iterator(interval_index_map& xmap)
{
  print_subheader("Iterating over the range intervals");

  interval_index_map_iterator* litr =
    dynamic_cast<interval_index_map_iterator*>(xmap.iterator(false));

  while(!litr->is_done())
  {
    cout << "range interval: [" << litr->range_interval_begin() << ", " 
	 << litr->range_interval_end() << " ]\tdomain interval: ["
	 << litr->domain_interval_begin() << ", "
	 << litr->domain_interval_end() << " ]" << endl;

    litr->next_interval();
  }
}

///
/// Test index_space created with an interval_index_map.
///
void
test_interval_id_map(index_space_family& xid_spaces, size_t xoffset, size_t xub)
{
  print_header("Testing interval_index_map");

  // Create a space.

  arg_list lmap_args = interval_index_map::make_arg_list(true);
  arg_list lspace_args =
    simple_index_space::make_arg_list("interval_index_map", lmap_args);

  index_space& lspace = make_id_space(xid_spaces,
				      "test_interval_id_map",
				      "simple_index_space",
				      lspace_args);

  // Initialize id map.

  interval_index_map& lmap = lspace.id_map<interval_index_map>();

  print_header("Initialize the id map.");

  insert_entry(lmap, 0, xoffset);
  insert_entry(lmap, xub, xoffset + xub);
  insert_interval(lmap, 1, (xub/2 - 1), xoffset+1, xoffset + (xub/2 - 1));
  insert_interval(lmap, (xub/2) + 1, xub - 1, xoffset + (xub/2) + 1, xoffset + xub - 1);
  insert_entry(lmap, xub/2, xoffset + (xub/2));

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test removing intervals.

  print_header("Test remove_interval.");

  remove_interval(lmap, xoffset+4, xoffset+5);
  remove_interval(lmap, xoffset+3, xoffset+4);
  remove_interval(lmap, xoffset+5, xoffset+6);
  remove_interval(lmap, xoffset+2, xoffset+4);
  remove_interval(lmap, xoffset+4, xoffset+7);
  remove_interval(lmap, xoffset+1, xoffset+7);
  remove_interval(lmap, xoffset+1, xoffset+8);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test removing first and last entries.

  print_header("Test remove_entry for first and last entries");

  remove_entry(lmap, 0, false, false);
  remove_entry(lmap, xoffset+xub, true, true);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test push back.

  print_subheader("Test push_back.");

  push_back(lmap, (xoffset+xub)*2);
  push_back(lmap, xoffset);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test insert entry.

  print_subheader("Test insert_entry.");

  insert_entry(lmap, xub+15, xoffset+xub+3);
  insert_entry(lmap, xub+10, xoffset+xub+4);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test insert intervals.

  print_subheader("Test insert_interval.");

  insert_interval(lmap, 11, 14, xoffset, xoffset+3);
  insert_interval(lmap, 13, 17, xoffset+2, xoffset+6);

  test_domain_interval_iterator(lmap);
  test_range_interval_iterator(lmap);
  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  // Test gathering.

  print_subheader("Test gather.");

  gather(lmap);

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);

  /// @todo Uncomment this test when interval_index_map supports gathering
  /// with deleted ids (see interval_index_map::map_rep_gather()).

//   // Gather the map after removing top ids.

//   print_header("Gather the map after removing top ids.");

//   delete_id(xid_spaces, xoffset);
//   delete_id(xid_spaces, xoffset+3);
//   delete_id(xid_spaces, xoffset+4);
//   delete_id(xid_spaces, xoffset+14);

//   gather(lmap);

//   test_domain_id_iterator(lspace);
//   test_range_id_iterator(lspace);

  // Test index_space_iterator.

  print_header("Test index_space_iterator.");

  test_space_iterator(lspace, true);
  test_space_iterator(lspace, false);

  // Test empty map.

  print_header("Test empty map.");

  remove_interval(lmap, lmap.range_begin(), (lmap.range_end()-1));

  test_domain_id_iterator(lspace);
  test_range_id_iterator(lspace);
}

} // unnamed namespace

///
/// Main routine for testing simple_id_space.
///
int main(int argc, char** argv)
{
  size_t lub = argc > 1 ? atoi(argv[1]) : 10;
  size_t loffset = argc > 2 ? atoi(argv[2]) : 10;

  assertion(lub >= 10);
  assertion(loffset >= 0);

  // Construct the family.  Construct a top id range that is the
  // offset of the simple id maps plus the upper bound of the
  // simple id maps.  This top id range is needed so the simple
  // id maps can be mapped to the top id space.

  index_space_family lid_spaces;
  lid_spaces.new_primary_id_space(2*(loffset + lub) + 1);
  
  // Test the interval_id_map.

  test_interval_id_map(lid_spaces, loffset, lub);

  return 0;
}


