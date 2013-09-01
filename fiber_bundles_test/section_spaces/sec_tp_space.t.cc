
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @example sec_tp_space.t.cc
/// Unit test for sec_tp_space.

#include "sec_tp_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_t2_e2.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "structured_block_1d.h"
#include "test_fibers.impl.h"
#include "wsv_block.h"

using namespace fiber_bundle;

namespace
{

  poset_path make_base_space(fiber_bundles_namespace& xns)
  {
    xns.get_read_write_access();

    base_space_poset& lhost = structured_block_1d::standard_host(xns, "base_space_host", false);

    structured_block_1d lmesh(&lhost, 2, true);
    lmesh.put_name("base_space", true, true);

    poset_path result = lmesh.path(true);
    
    lmesh.detach_from_state();
    xns.release_access();
    
    return result;
  }
    
}


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  print_header("Begin testing sec_tp_space");

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  // Make a base space.

  poset_path lbase_space_path = make_base_space(lns);

  // Create a section space.

  sec_tp_space& lspace =
    sec_t2_e2::standard_host(lns, lbase_space_path, "", "", "", false);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<sec_tp_space>(lns, lspace);
  
  //============================================================================

  // Display the namespace.

  cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  print_footer("End testing sec_tp_space");

  // Postconditions:

  // Exit:

  return 0;
}

  

