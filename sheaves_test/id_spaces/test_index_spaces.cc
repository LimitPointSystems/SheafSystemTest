// $RCSfile: test_index_spaces.cc,v $ $Revision: 1.11 $ $Date: 2012/07/04 16:42:20 $

// $Name: coverage-mod-0-1 $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for id space test functions.

#include "test_index_spaces.h"
#include "test_utils.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "block.h"
#include "gluable_sum_index_space.h"
#include "index_map_iterator.h"
#include "index_space.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "mutable_index_map.h"
#include "scoped_index.h"
#include "std_iostream.h"
#include "std_strstream.h"

// ===========================================================
// INDEX_SPACE FACET
// ===========================================================

sheaf::index_space&
sheaf::
make_id_space(index_space_family& xid_spaces,
	      const string& xname,
	      const string& xspace_class_name,
	      const arg_list& xspace_args)
{
  // Preconditions:

  // Body:

  // Doen't matter if the id space is persistent or not, it is not
  // going to be written to a file.

  xid_spaces.new_secondary_id_space(xname, xspace_class_name,
				    xspace_args, true);

  index_space& result = xid_spaces.id_space(xname);

  print_subheader("Creating new id space");
  cout << "index:        " << result.index() << endl;
  cout << "name:         " << result.name() << endl;
  cout << "space:        " << xspace_class_name << endl;
  cout << "map:          " << (string) xspace_args.value("map_class_name") << endl;
  cout << endl;
  
  // Postconditions:

  // Exit:

  return result;
} 

void
sheaf::
print_map_extrema(const index_space& xspace)
{
  print_subheader("Map extrema for id space, '" + xspace.name() + "'");

  const index_map& lmap = xspace.id_map();

  cout << "ct:           " << lmap.ct() << endl;
  cout << "domain_begin: " << lmap.domain_begin() << endl;
  cout << "domain_end:   " << lmap.domain_end() << endl;
  cout << "range_begin:  " << lmap.range_begin() << endl;
  cout << "range_end:    " << lmap.range_end() << endl;
  cout << endl;
}

// ===========================================================
// TOP ID SPACE FACET
// ===========================================================

void
sheaf::
delete_id(index_space_family& xid_spaces, pod_index_type xid)
{
  // Output the operation.

  strstream lstr;
  lstr << "delete_id(" << xid << ")";

  print_action(lstr.str());

  // Delete the id.

  xid_spaces.top_id_space().delete_id(xid);
}

// ===========================================================
// MUTABLE_INDEX_MAP FACET
// ===========================================================

void
sheaf::
insert_entry(mutable_index_map& xmap,
	     pod_index_type xdomain_id,
	     pod_index_type xrange_id)
{
  // Output the operation.

  strstream lstr;
  lstr << "insert_entry(" << xdomain_id << ", " << xrange_id << ")";

  print_action(lstr.str());

  // Insert the entry.

  xmap.insert_entry(xdomain_id, xrange_id);
}

void
sheaf::
push_back(mutable_index_map& xmap,
	  pod_index_type xrange_id)
{
  // Output the operation.

  strstream lstr;
  lstr << "push_back(" << xrange_id << ")";

  print_action(lstr.str());

  // Push back the range id.

  xmap.push_back(xrange_id);
}
  
void
sheaf::
remove_entry(mutable_index_map& xmap,
	     pod_index_type xid,
	     bool xis_range_id,
	     bool xupdate_extrema)
{
  // Output the operation.

  strstream lstr;
  lstr << "remove_entry(" << xid << ", "
       << (xis_range_id ? "true" : "false") << ", " 
       << (xupdate_extrema ? "true" : "false") << ")";

  print_action(lstr.str());

  // Remove the id.

  xmap.remove_entry(xid, xis_range_id, xupdate_extrema);
}

void
sheaf::
update_extrema(mutable_index_map& xmap)
{
  // Output the operation.

  print_action("update_extrema()");

  // Update the extrema.

  xmap.update_extrema();
}

void
sheaf::
gather(mutable_index_map& xmap)
{
  // Output the operation.

  print_action("gather()");

  // Gather the map.

  xmap.gather();
}

void
sheaf::
clear(mutable_index_map& xmap)
{
  // Output the operation.

  print_action("clear()");

  // Clear the map.

  xmap.clear();
}

// ===========================================================
// ITERATOR FACET
// ===========================================================

void
sheaf::
test_domain_id_iterator(const index_space& xspace)
{
  // Preconditions:

  // Body:

  print_subheader("Iterating over domain ids");
  index_map_iterator* lmap_itr = xspace.id_map().iterator(true);
  while(!lmap_itr->is_done())
  {
    cout << "domain id: " << lmap_itr->domain_id();
    cout << "\trange id: " << lmap_itr->range_id();
    cout << endl;
    lmap_itr->next();
  }
  cout << endl;

  delete lmap_itr;

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::
test_range_id_iterator(const index_space& xspace)
{
  // Preconditions:

  // Body:

  print_subheader("Iterating over range ids");
  index_map_iterator* lmap_itr = xspace.id_map().iterator(false);
  while(!lmap_itr->is_done())
  {
    cout << "range id: " << lmap_itr->range_id();
    cout << "\tdomain id: " << lmap_itr->domain_id();
    cout << endl;
    lmap_itr->next();
  }
  cout << endl;

  delete lmap_itr;

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::
test_space_iterator(const index_space& xspace, bool xis_host_order)
{
  // Preconditions:

  // Body:

  string lmessage =
    xis_host_order ?
    "Iterator over id space in host id order" :
    "Iterator over id space in top id order";

  print_subheader(lmessage);

  index_space_iterator* lspace_itr = xspace.iterator(xis_host_order);
  while(!lspace_itr->is_done())
  {
    if(xis_host_order)
    {
      cout << "id: " << lspace_itr->id();
      cout << "\ttop id: " << lspace_itr->top_id();
    }
    else
    {
      cout << "top id: " << lspace_itr->top_id();
      cout << "\tid: " << lspace_itr->id();
    }
    
    cout << endl;
    lspace_itr->next();
  }
  cout << endl;

  delete lspace_itr;

  // Postconditions:

  // Exit:

  return;
}  
  
// ===========================================================
// Convenience functions
// ===========================================================

// void
// sheaf::
// print_header(const string& xtext)
// {
//   // Preconditions:

//   // Body:

//   static const string nl("\n");
//   static const string s = "=======================================";
//   static const string sep = s + s;

//   cout << nl << sep << nl << xtext << nl << sep << nl;
//   cout << endl;

//   // Postconditions:

//   // Exit:  

//   return;
// }

// void
// sheaf::
// print_subheader(const string& xtext)
// {
//   // Preconditions:

//   // Body:

//   static const string nl("\n");

//   cout << nl << "======== " << xtext << " ========" << nl;
//   cout << endl;

//   // Postconditions:

//   // Exit:

//   return;
// }

// void
// sheaf::
// print_action(const string& xtext)
// {
//   // Preconditons:

//   // Body:

//   cout << ">>>>>>>> " << xtext << endl;

//   // Postconditions:

//   // Exit:

//   return;
// }

