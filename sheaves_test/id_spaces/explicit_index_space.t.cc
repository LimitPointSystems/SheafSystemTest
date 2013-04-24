


//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example explicit_index_space.t.cc
/// Test driver for explicit id spaces.

#include "assert_contract.h"
#include "arg_list.h"
#include "error_message.h"
#include "index_space_family.h"
#include "explicit_index_space_handle.h"
#include "explicit_index_space_iterator.h"
#include "offset_index_space_state.h"
#include "namespace_poset.h"
#include "std_iostream.h"
#include "test_index_spaces.impl.h"

using namespace sheaf;

int main( int argc, char* argv[])
{
  // Preconditions:

  // Body:

  namespace_poset::initialize_id_space_prototypes();

  index_space_family lid_spaces;
  lid_spaces.new_primary_state(6);

  string lname("test_explicit_id_space");

  pod_index_type lspace_id =
    make_id_space(lid_spaces,
		  lname,
		  "offset_index_space_state",
		  offset_index_space_state::make_arg_list(2, 4)).index();

  // Test handle facet.

  test_handle_facet<explicit_index_space_handle>(lid_spaces, lspace_id);

  print_out_header("Testing miscellaneous handle functions");

  explicit_index_space_handle lhandle(lid_spaces, lspace_id);

  const index_space_family& lid_spaces2 = lhandle.id_spaces();
  index_space_family& lid_spaces3 = lhandle.id_spaces();

  scoped_index lid0(lid_spaces.hub_id_space(), 2);

  lhandle.put_is_persistent(true);
  cout << "put_is_persistent(true)" << endl;

  cout << "const id_spaces()    = " << &lid_spaces2 << endl;
  cout << "mutable id_spaces()  = " << &lid_spaces3 << endl;
  cout << "ct()                 = " << lhandle.ct() << endl;
  cout << "begin()              = " << lhandle.begin() << endl;
  cout << "end()                = " << lhandle.end() << endl;
  cout << "contains(lid0)       = " << lhandle.contains(lid0) << endl;
  cout << "contains(0)          = " << lhandle.contains(0) << endl;
  cout << "contains_hub(lid0)   = " << lhandle.contains_hub(lid0) << endl;
  cout << "contains_hub(0)      = " << lhandle.contains_hub(0) << endl;
  cout << "contains(lid0, lid0) = " << lhandle.contains(lid0, lid0) << endl;
  cout << "contains(0, 0)       = " << lhandle.contains(0, 0) << endl;
  cout << "pod(lid0)            = " << lhandle.pod(lid0) << endl;
  cout << "pod(2)               = " << lhandle.pod(2) << endl;
  cout << "hub_pod(0)           = " << lhandle.hub_pod(0) << endl;
  cout << "glued_hub_pod(0)     = " << lhandle.glued_hub_pod(0) << endl;
  cout << "is_persistent()      = " << lhandle.is_persistent() << endl;
  cout << "host()               = " << &lhandle.host() << endl;
  cout << "index()              = " << lhandle.index() << endl;
  cout << "is_attached()        = " << lhandle.is_attached() << endl;
  

  // Postconditions:

  // Exit:

  return 0;
}

  
