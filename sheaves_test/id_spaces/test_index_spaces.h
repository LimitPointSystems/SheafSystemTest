// $RCSfile: test_index_spaces.h,v $ $Revision: 1.11 $ $Date: 2012/07/04 16:42:20 $

// $Name: coverage-mod-0-1 $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @file
/// Interface for id space test function.

#ifndef TEST_INDEX_SPACES_H
#define TEST_INDEX_SPACES_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

class arg_list;
class index_map;
class index_space;
class index_space_family;
class interval_index_map;
class mutable_index_map;

// ===========================================================
// INDEX_SPACE FACET
// ===========================================================

///
/// Create an id space with name xname, space type xid_space_class_name,
/// and map type xid_map_class_name in the id space family xid_spaces.
/// Output the information to standard out.
///
SHEAF_DLL_SPEC
index_space&
make_id_space(index_space_family& xid_spaces,
	      const string& xname,
	      const string& xid_space_class_name,
	      const arg_list& xspace_args);

///
/// Output the count and extrema for the map in xspace.
///
SHEAF_DLL_SPEC
void 
print_map_extrema(const index_space& xspace);

// ===========================================================
// TOP ID SPACE FACET
// ===========================================================

///
/// Delete xid from the top id space of xid_spaces.
///
SHEAF_DLL_SPEC
void
delete_id(index_space_family& xid_spaces, pod_index_type xid);

// ===========================================================
// MUTABLE_INDEX_MAP FACET
// ===========================================================

///
/// Insert the entry (xdomain_id, xrange_id) into xmap.
///
SHEAF_DLL_SPEC
void
insert_entry(mutable_index_map& xmap,
	     pod_index_type xdomain_id,
	     pod_index_type xrange_id);

///
/// Push back range id, xrange_id into xmap.
///
SHEAF_DLL_SPEC
void
push_back(mutable_index_map& xmap,
	  pod_index_type xrange_id);

///
/// Remove entry for the xid from xmap.
///
SHEAF_DLL_SPEC
void
remove_entry(mutable_index_map& xmap,
	     pod_index_type xid,
	     bool xis_range_id,
	     bool xupdate_extrema);

///
/// Update the extrema for xmap.
///
SHEAF_DLL_SPEC
void 
update_extrema(mutable_index_map& xmap);

///
/// Gather xmap.
///
SHEAF_DLL_SPEC
void 
gather(mutable_index_map& xmap);

///
/// Clear xmap.
///
SHEAF_DLL_SPEC
void 
clear(mutable_index_map& xmap);

// ===========================================================
// ITERATOR FACET
// ===========================================================

///
/// Test the domain id map iterator for xspace.
///
SHEAF_DLL_SPEC
void
test_domain_id_iterator(const index_space& xspace);

///
/// Test the range id map iterator for xspace.
///
SHEAF_DLL_SPEC
void
test_range_id_iterator(const index_space& xspace);

///
/// Test the space iterator for xspace with xis_host_order.
///
SHEAF_DLL_SPEC
void
test_space_iterator(const index_space& xspace, bool xis_host_order);

// ===========================================================
// Convenience functions
// ===========================================================

///
/// Convenience function to print a "header" to standard out.
///
SHEAF_DLL_SPEC
void
print_header(const string& xtext);

///
/// Convenience function to print a "subheader" to standard out.
///
SHEAF_DLL_SPEC
void
print_subheader(const string& xtext);

///
/// Convenience function to print an "action" to standard out.
///
SHEAF_DLL_SPEC
void
print_action(const string& xtext);


// ===========================================================
// SPECIALIZATIONS
// ===========================================================

} // end namespace sheaf

#endif // ifndef TEST_INDEX_SPACES_H
