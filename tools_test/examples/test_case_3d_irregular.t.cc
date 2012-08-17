
#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "storage_agent.h"
#include "test_case_3d_irregular.h"

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

