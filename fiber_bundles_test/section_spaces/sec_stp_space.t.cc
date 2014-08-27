
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

/// @example sec_stp_space.t.cc
/// Unit test for sec_stp_space.

#include "sec_stp_space.h"

#include "arg_list.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "ComLimitPoint/sheaf/schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_st2_e2.h"
#include "std_iostream.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "stp_space.h"
#include "structured_block_1d.h"
#include "test_fibers.impl.h"
#include "wsv_block.h"

using namespace std;
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


int main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
  
  // Body:

  print_header("Begin testing sec_stp_space");

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  // Make a base space.

  poset_path lbase_space_path = make_base_space(lns);

  // Create a section space.

  sec_stp_space& lspace =
    sec_st2_e2::standard_host(lns, lbase_space_path, "", "", "", false);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<sec_stp_space>(lns, lspace);
  
  //============================================================================

  // Display the namespace.

  cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  print_footer("End testing sec_stp_space");

  // Postconditions:

  // Exit:

  return 0;
}

  

