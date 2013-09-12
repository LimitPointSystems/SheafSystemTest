
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

/// Unit test for class sec_met_ed.

#include "sec_met_ed.h"
#include "sec_met_e2.h"

#include "fiber_bundles_namespace.h"
#include "test_sections.impl.h"
#include "test_utils.h"

using namespace fiber_bundle;


int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_met_ed");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  test_section_common_unattached<sec_met_ed>();
  test_section_common_attached<sec_met_ed, sec_met_e2>(lns, 2);

  //============================================================================

  print_footer("Ending testing sec_met_ed");

  // Postconditions:

  // Exit:

  return 0;
}

