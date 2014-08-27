
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

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "ComLimitPoint/sheaf/storage_agent.h"
#include "test_case_3d_irregular.h"

using namespace std;
using namespace tool;

int main(int argc, char* argv[])
{
  // First, make sure the environment variables have been set.

  //sheaf_constants::check_lps_script_has_run();

  size_type num_points = 50;

  if(argc == 2)
  {
    num_points = static_cast<size_type>(atoi(argv[1]));
  }

  string filename = "test_case_3d_irregular.t.hdf";

  cout << "Generating test file \"" << filename << "\"" << endl;

  fiber_bundles_namespace lns("test_case_3d_irregular.t");
  lns.get_read_write_access();

  test_case_3d_irregular tc(lns, num_points);

  storage_agent sa(filename);
  sa.write_entire(lns);

  cout << "Test file \"" << filename << "\" write complete." << endl;

  return 0;
}

