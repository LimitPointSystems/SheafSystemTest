
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
/// @file
/// Interface for id space test function.

#ifndef TEST_INDEX_SPACES_H
#define TEST_INDEX_SPACES_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef INDEX_SPACE_FAMILY_H
#include "ComLimitPoint/sheaf/index_space_family.h"
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

class index_space_iterator;
class index_space_handle;
class mutable_index_space_handle;

// ===========================================================
// INDEX_SPACE_FAMILY FACET
// ===========================================================

///
/// Implementation of index_space_family that makes the
/// new_primary_state function public for testing.
///
class SHEAF_DLL_SPEC test_index_space_family : public index_space_family
{
public:

  ///
  /// Default Constructor.
  ///
  test_index_space_family()
    : index_space_family()
  {
  };

  ///
  /// Destructor.
  ///
  virtual ~test_index_space_family()
  {
  };

  ///
  /// Creates a new primary id space state with xct number of ids.
  /// Returns the index of the id space state created.
  ///
  pod_type new_primary_space(size_type xct)
  {
    return new_primary_state(xct);
  };

  ///
  /// Creates a new primary id space state [xid, xid+xct).
  /// Returns the index of the id space state created.
  ///
  pod_type new_primary_space(pod_type xid, size_type xct)
  {
    return new_primary_state(xid, xct);
  };

  ///
  /// Delete the primary id space state with id xid.
  ///
  void delete_primary_space(pod_type xid)
  {
    delete_primary_state(xid);
  };

protected:

private:

};

// ===========================================================
// INDEX_SPACE FACET
// ===========================================================

///
/// Check the id space with ids [xbegin, xbegin+xct) for correctness.
///
SHEAF_DLL_SPEC
bool
check_id_spaces(index_space_family& xid_spaces,
		pod_index_type xbegin, size_type xct);

///
/// Print the count and extrema for the id space xid_space.
///
SHEAF_DLL_SPEC
void 
print_out_map_extrema(const index_space_handle& xid_space);

// ===========================================================
// ID SPACE FAMILY FACET
// ===========================================================

///
/// Test the id space family's state facet.
/// This function tests the base interface for id spaces in
/// the family.  It will test the base interface for index_space_state
/// and index_space_collection.
///
SHEAF_DLL_SPEC
void
test_state_facet(index_space_family& xid_spaces, pod_index_type xspace_id,
		  pod_index_type xid, pod_index_type xhub_id);

// ===========================================================
// TOP ID SPACE FACET
// ===========================================================

///
/// Delete xid from the hub id space of xid_spaces.
///
SHEAF_DLL_SPEC
void
delete_id(index_space_family& xid_spaces, pod_index_type xid);

// ===========================================================
// MUTABLE_INDEX_SPACE FACET
// ===========================================================

///
/// Test the mutable facet.
///
SHEAF_DLL_SPEC
void
test_mutable_facet(index_space_family& xid_spaces, pod_index_type xspace_id);

///
/// Test the mutable facet.
///
SHEAF_DLL_SPEC
void
test_mutable_facet(mutable_index_space_handle& xid_space);

///
/// Insert the entry (xid, xhub_id) into xid_space.
///
SHEAF_DLL_SPEC
void
insert(mutable_index_space_handle& xid_space,
       pod_index_type xid,
       pod_index_type xhub_id);

///
/// Push back hub id, hub_id into xid_space.
///
SHEAF_DLL_SPEC
void
push_back(mutable_index_space_handle& xid_space,
	  pod_index_type xhub_id);

///
/// Remove entry for the id xid from xid_space.
///
SHEAF_DLL_SPEC
void
remove(mutable_index_space_handle& xid_space,
       pod_index_type xid,
       bool xupdate_extrema);

///
/// Remove entry for the hub id xhub_id from xid_space.
///
SHEAF_DLL_SPEC
void
remove_hub(mutable_index_space_handle& xid_space,
	   pod_index_type xhub_id,
	   bool xupdate_extrema);

///
/// Update the extrema for xid_space.
///
SHEAF_DLL_SPEC
void 
update_extrema(mutable_index_space_handle& xid_space);

///
/// Gather xid_space.
///
SHEAF_DLL_SPEC
void 
gather(mutable_index_space_handle& xid_space);

///
/// Clear xid_space.
///
SHEAF_DLL_SPEC
void 
clear(mutable_index_space_handle& xid_space);

// ===========================================================
// HANDLE FACET
// ===========================================================

///
/// Test the handle facet.
/// The template parameter H represents the handle type.
///
template <typename H>
void
test_handle_facet(index_space_family& xid_spaces, pod_index_type xspace_id);

// ===========================================================
// ITERATOR FACET
// ===========================================================

///
/// Test the iterator facet.
/// The template parameter I represents the iterator type.
///
template <typename I>
void
test_iterator_facet(index_space_family& xid_spaces, pod_index_type xspace_id);

///
/// Test the iterator for xid_space.
///
SHEAF_DLL_SPEC
void
test_iterator(const index_space_handle& xid_space);

///
/// Test the iterator for xitr.
///
SHEAF_DLL_SPEC
void
test_iterator(index_space_iterator& xitr);

// ===========================================================
// Convenience functions
// ===========================================================

///
/// Convenience function to print a "header" to standard out.
///
SHEAF_DLL_SPEC
void
print_out_header(const std::string& xtext);

///
/// Convenience function to print a "subheader" to standard out.
///
SHEAF_DLL_SPEC
void
print_out_subheader(const std::string& xtext);

///
/// Convenience function to print an "action" to standard out.
///
SHEAF_DLL_SPEC
void
print_out_action(const std::string& xtext);


// ===========================================================
// SPECIALIZATIONS
// ===========================================================

} // end namespace sheaf

#endif // ifndef TEST_INDEX_SPACES_H
