
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

/// @example io/name_limit.t.cc
/// Routine to test ability to store many member names

#include "sheaves_namespace.h"
#include "poset_path.h"
#include "std_sstream.h"
#include "storage_agent.h"
#include "subposet_member_iterator.h"

using namespace std;
using namespace sheaf;


int
main(int argc, char* argv[])
{

  string size_arg;
  size_type size;
  if (argc > 1)
  {
    size = atoi(argv[1]);
    size_arg = argv[1];
  }
  else
  {
    size = 5000;
    size_arg = "5000";
  }

  if(size < 1)
  {
    size = 1;
    size_arg = "1";
  }


  sheaves_namespace* lns = new sheaves_namespace("name_limit.t");

  // cout << *lns << endl;

  lns->get_read_write_access();

  // Make a test poset with number of member names == size + 2.

  poset* lposet = new poset(lns, "primitives_schema/top", "name_test", true);

  lposet->begin_jim_edit_mode(true);

  // There's still a limitation on the number of dof tuples,
  // so make all the members use the same dof tuple.

  scoped_index ltuple_id = lposet->new_row_dof_map();

  for(int i=0; i<size; ++i)
  {
    scoped_index lmbr_id = lposet->new_member(true, ltuple_id);

    stringstream mbr_name_stream;
    string mbr_name;
    mbr_name_stream << lmbr_id.pod();
    mbr_name_stream >> mbr_name;

    // Make names exactly 16 chars long
    // so we know how much storage we're using.

    // mbr_name += "++++++++++++++++";

    string mbr_name_substring = mbr_name.substr(0, 16);

    lposet->put_member_name(lmbr_id, mbr_name_substring, true, false);
  }



  lposet->end_jim_edit_mode(true, true);

  //   lposet->get_read_access();
  //   cout << *lposet << endl;
  //   lposet->release_access();


  string fname = "name_limit.t.hdf";
  storage_agent sa(fname);
  sa.write_entire(*lns);

  delete lns;

  return 0;
}
