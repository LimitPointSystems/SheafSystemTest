
// $Name$
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for id space test functions.

#include "test_index_spaces.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "block.h"
#include "hub_index_space_handle.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "mutable_index_space_handle.h"
#include "scoped_index.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "std_strstream.h"

// ===========================================================
// INDEX_SPACE FACET
// ===========================================================

sheaf::index_space_handle&
sheaf::
make_id_space(index_space_family& xid_spaces,
	      const string& xname,
	      const string& xstate_class_name,
	      const arg_list& xstate_args)
{
  // Preconditions:

  // Body:

  // Doen't matter if the id space is persistent or not, it is not
  // going to be written to a file.

  pod_index_type lspace_id =
    xid_spaces.new_secondary_state(xname, xstate_class_name,
				   xstate_args, true);

  index_space_handle& result = xid_spaces.get_id_space(lspace_id);

  print_out_subheader("Creating new id space");
  cout << "index:        " << result.index() << endl;
  cout << "name:         " << result.name() << endl;
  cout << "space:        " << xstate_class_name << endl;
  cout << endl;

  assertion(check_id_spaces(xid_spaces, lspace_id, 1));
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::
make_id_space_interval(index_space_family& xid_spaces,
		       const string& xinterval_class_name,
		       const arg_list& xinterval_args,
		       size_type xub)
{
  // Preconditions:

  // Body:

  pod_index_type lbegin =
    xid_spaces.new_secondary_interval(xinterval_class_name,
				      xinterval_args,
				      xub);

  print_out_subheader("Creating new id space interval");
  cout << "begin:        " << lbegin << endl;
  cout << "ub:           " << xub << endl;
  cout << "interval:     " << xinterval_class_name << endl;
  cout << endl;

  assertion(check_id_spaces(xid_spaces, lbegin, xub));
  
  // Postconditions:

  // Exit:

  return lbegin;
}

bool
sheaf::
check_id_spaces(index_space_family& xid_spaces,
		pod_index_type xbegin, size_type xct)
{
  bool result = true;

  for(pod_index_type i = 0; i < xct; i++)
  {
    // Test id space order iteration (i.e., domain order).

    pod_index_type lspace_id = xbegin + i;

    index_space_handle& lid_space = xid_spaces.get_id_space(lspace_id);
    index_space_iterator& itr = lid_space.get_iterator();
    pod_index_type lprevious = -1;
    pod_index_type lcurrent;
    while(!itr.is_done())
    {
      lcurrent = itr.pod();
      if(is_valid(lcurrent))
      {
	if(lcurrent <= lprevious)
	{
	  cerr << "ERROR: Id space order not preserved." << endl;
	  cerr << "       space id = " << lspace_id << endl;
	  cerr << "       current  = " << lcurrent << endl;
	  cerr << "       previous = " << lprevious << endl << endl;
	  result = false;
	}

	if(itr.hub_pod() != lid_space.hub_pod(lcurrent))
	{
	  cerr << "ERROR: Hub id in the space is not equal to the iterator." << endl;
	  cerr << "       space id        = " << lspace_id << endl;
	  cerr << "       current         = " << lcurrent << endl;
	  cerr << "       lspace.hub_pod  = " << lid_space.hub_pod(lcurrent) << endl;
	  cerr << "       itr.hub_pod     = " << itr.hub_pod() << endl << endl;
	}
      }
      else
      {
	cerr << "ERROR: Invalid id in id space order." << endl;
	cerr << "       space id = " << lspace_id << endl << endl;
	result = false;
      }

      itr.next();
    }
    lid_space.release_iterator(itr);
    xid_spaces.release_id_space(lid_space);
  }
  
  return result;
}

void
sheaf::
print_out_map_extrema(const index_space_handle& xid_space)
{
  print_out_subheader("Extrema for id space, '" + xid_space.name() + "'");

  cout << "ct:    " << xid_space.ct() << endl;
  cout << "begin: " << xid_space.begin() << endl;
  cout << "end:   " << xid_space.end() << endl;
  cout << endl;
}

// ===========================================================
// ID SPACE FAMILY FACET
// ===========================================================

void
sheaf::
test_state_facet(index_space_family& xid_spaces, pod_index_type xspace_id,
		 pod_index_type xid, pod_index_type xhub_id)
{
  // Preconditions:

  // Body:

  scoped_index lhub_id(xid_spaces.hub_id_space(), xhub_id);
  const string& lname = xid_spaces.name(xspace_id);

  print_out_header("Testing id space family state facet.");

  cout << "ct(xspace_id)                     = " << xid_spaces.ct(xspace_id) << endl;
  cout << "ct(lname)                         = " << xid_spaces.ct(lname) << endl;
  cout << "is_empty(xspace_id)               = " << xid_spaces.is_empty(xspace_id) << endl;
  cout << "is_empty(lname)                   = " << xid_spaces.is_empty(lname) << endl;
  cout << "begin(xspace_id)                  = " << xid_spaces.begin(xspace_id) << endl;
  cout << "begin(lname)                      = " << xid_spaces.begin(lname) << endl;
  cout << "end(xspace_id)                    = " << xid_spaces.end(xspace_id) << endl;
  cout << "end(lname)                        = " << xid_spaces.end(lname) << endl;
  cout << "hub_begin(xspace_id)              = " << xid_spaces.hub_begin(xspace_id) << endl;
  cout << "hub_begin(lname)                  = " << xid_spaces.hub_begin(lname) << endl;
  cout << "is_gathered(xspace_id)            = " << xid_spaces.is_gathered(xspace_id) << endl;
  cout << "is_gathered(lname)                = " << xid_spaces.is_gathered(lname) << endl;
  cout << "contains(xspace_id, xid)          = " << xid_spaces.contains(xspace_id, xid) << endl;
  cout << "contains(lname, xid)              = " << xid_spaces.contains(lname, xid) << endl;
  cout << "contains(xspace_id, lhub_id)      = " << xid_spaces.contains(xspace_id, lhub_id) << endl;
  cout << "contains(lname, lhub_id)          = " << xid_spaces.contains(lname, lhub_id) << endl;
  cout << "contains(xspace_id, xid, lhub_id) = " << xid_spaces.contains(xspace_id, xid, lhub_id) << endl;
  cout << "contains(lname, xid, lhub_id)     = " << xid_spaces.contains(lname, xid, lhub_id) << endl;
  cout << "pod(xspace_id, lhub_id)           = " << xid_spaces.pod(xspace_id, lhub_id) << endl;
  cout << "pod(lname, lhub_id)               = " << xid_spaces.pod(lname, lhub_id) << endl;
  cout << "hub_pod(xspace_id, xid)           = " << xid_spaces.hub_pod(xspace_id, xid) << endl;
  cout << "hub_pod(lname, xid)               = " << xid_spaces.hub_pod(lname, xid) << endl;
  cout << "glued_hub_pod(xspace_id, xid)     = " << xid_spaces.glued_hub_pod(xspace_id, xid) << endl;
  cout << "glued_hub_pod(lname, xid)         = " << xid_spaces.glued_hub_pod(lname, xid) << endl;
  cout << "is_persistent(xspace_id)          = " << xid_spaces.is_persistent(xspace_id) << endl;
  cout << "is_persistent(lname)              = " << xid_spaces.is_persistent(lname) << endl;

  index_space_handle& lhandle0 = xid_spaces.get_id_space(xspace_id);
  cout << "get_id_space(xspace_id)           = " << &lhandle0 << endl;
  cout << "release_id_space(lhandle0)" << endl;
  xid_spaces.release_id_space(lhandle0);

  index_space_handle& lhandle1 = xid_spaces.get_id_space(lname);
  cout << "get_id_space(lname)               = " << &lhandle1 << endl;
  cout << "release_id_space(lhandle1)" << endl;
  xid_spaces.release_id_space(lhandle1);


  index_space_iterator& litr0 = xid_spaces.get_id_space_iterator(xspace_id);
  cout << "get_id_space_iterator(xspace_id)  = " << &litr0 << endl;
  cout << "release_id_space_iterator(litr0)" << endl;
  xid_spaces.release_id_space_iterator(litr0);

  index_space_iterator& litr1 = xid_spaces.get_id_space_iterator(lname);
  cout << "get_id_space_iterator(lname)      = " << &litr1 << endl;
  cout << "release_id_space_iterator(litr1)" << endl;
  xid_spaces.release_id_space_iterator(litr1);

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
// TOP ID SPACE FACET
// ===========================================================

void
sheaf::
delete_id(index_space_family& xid_spaces, pod_index_type xid)
{
  // Print the operation.

  strstream lstr;
  lstr << "delete_id(" << xid << ")";

  print_out_action(lstr.str());

  // Delete the id.

  xid_spaces.delete_id(xid);
}

// ===========================================================
// MUTABLE_INDEX_MAP FACET
// ===========================================================

void
sheaf::
test_mutable_facet(index_space_family& xid_spaces, pod_index_type xspace_id)
{
  // Preconditions:

  // Body:

  print_out_header("Testing Mutable Facet");

  mutable_index_space_handle lhandle(xid_spaces, xspace_id);

  cout << "insert(10, 1)" << endl;
  scoped_index lid(xid_spaces.hub_id_space(), 1);
  lhandle.insert(10, lid);

  cout << "push_back(3)" << endl;
  lid = 3;
  lhandle.push_back(lid);

//   cout << "push(litr, 5)" << endl;
//   index_space_iterator& litr = xid_spaces.get_id_space_iterator(xspace_id);
//   lid = 5;
//   lhandle.push(litr, lid);
//   xid_spaces.release_id_space_iterator(litr);
  
  cout << "remove(5, false)" << endl;
  lhandle.remove(lid, false);

  cout << "remove(3, true)" << endl;
  lid = 3;
  lhandle.remove(lid, true);

  cout << "remove_hub(2, true)" << endl;
  lhandle.remove_hub(2, true);

  cout << "remove_hub(0, false)" << endl;
  lhandle.remove_hub(0, false);

  cout << "update_extrema()" << endl;
  lhandle.update_extrema();

  cout << "next_id()  = " << lhandle.next_id() << endl;

  cout << "capacity() = " << lhandle.capacity() << endl;

  cout << "gather()" << endl;
  lhandle.gather();

  cout << "clear()" << endl;
  lhandle.clear();

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::
insert(mutable_index_space_handle& xid_space,
       pod_index_type xid,
       pod_index_type xhub_id)
{
  // Print the operation.

  strstream lstr;
  lstr << "insert_entry(" << xid << ", " << xhub_id << ")";

  print_out_action(lstr.str());

  // Insert the entry.

  xid_space.insert(xid, xhub_id);
}

void
sheaf::
push_back(mutable_index_space_handle& xid_space,
	  pod_index_type xhub_id)
{
  // Print the operation.

  strstream lstr;
  lstr << "push_back(" << xhub_id << ")";

  print_out_action(lstr.str());

  // Push back the range id.

  xid_space.push_back(xhub_id);
}
  
void
sheaf::
remove(mutable_index_space_handle& xid_space,
       pod_index_type xid,
       bool xupdate_extrema)
{
  // Print the operation.

  strstream lstr;
  lstr << "remove(" << xid << ", "
       << (xupdate_extrema ? "true" : "false") << ")";

  print_out_action(lstr.str());

  // Remove the id.

  xid_space.remove(xid, xupdate_extrema);
}

void
sheaf::
remove_hub(mutable_index_space_handle& xid_space,
	   pod_index_type xhub_id,
	   bool xupdate_extrema)
{
  // Print the operation.

  strstream lstr;
  lstr << "remove_hub(" << xhub_id << ", "
       << (xupdate_extrema ? "true" : "false") << ")";

  print_out_action(lstr.str());

  // Remove the id.

  xid_space.remove_hub(xhub_id, xupdate_extrema);
}

void
sheaf::
update_extrema(mutable_index_space_handle& xid_space)
{
  // Print the operation.

  print_out_action("update_extrema()");

  // Update the extrema.

  xid_space.update_extrema();
}

void
sheaf::
gather(mutable_index_space_handle& xid_space)
{
  // Print the operation.

  print_out_action("gather()");

  // Gather the map.

  xid_space.gather();
}

void
sheaf::
clear(mutable_index_space_handle& xid_space)
{
  // Print the operation.

  print_out_action("clear()");

  // Clear the map.

  xid_space.clear();
}

// ===========================================================
// ITERATOR FACET
// ===========================================================

void
sheaf::
test_iterator(const index_space_handle& xid_space)
{
  // Preconditions:

  // Body:

  index_space_iterator& itr = xid_space.get_iterator();
  test_iterator(itr);
  xid_space.release_iterator(itr);

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::
test_iterator(index_space_iterator& xitr)
{
  // Preconditions:

  // Body:

  string lname;

  if(xitr.name().empty())
  {
    strstream lstr;
    lstr << xitr.index();
    lstr >> lname;
  }
  else
  {
    lname = xitr.name();
  }

  print_out_subheader("Iterating over id space: '" + lname + "'");

  while(!xitr.is_done())
  {
    cout << "id: " << setw(14) << left << xitr.pod();
    cout << "hub id: " << xitr.hub_pod();
    cout << endl;
    xitr.next();
  }
  cout << endl;

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
// Convenience functions
// ===========================================================

void
sheaf::
print_out_header(const string& xtext)
{
  // Preconditions:

  // Body:

  static const string nl("\n");
  static const string s = "=======================================";
  static const string sep = s + s;

  cout << nl << sep << nl << xtext << nl << sep << nl;
  cout << endl;

  // Postconditions:

  // Exit:  

  return;
}

void
sheaf::
print_out_subheader(const string& xtext)
{
  // Preconditions:

  // Body:

  static const string nl("\n");

  cout << nl << "======== " << xtext << " ========" << nl;
  cout << endl;

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::
print_out_action(const string& xtext)
{
  // Preconditons:

  // Body:

  cout << ">>>>>>>> " << xtext << endl;

  // Postconditions:

  // Exit:

  return;
}

