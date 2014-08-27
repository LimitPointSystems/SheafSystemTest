
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
#include "at0.h"
#include "at0_space.h"
#include "at1_space.h"
#include "e2.h"
#include "fiber_bundles_namespace.h"
#include "tp_space.h"
#include "ComLimitPoint/sheaf/storage_agent.h"

using namespace std;
using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace ns(filename);
  ns.get_read_write_access();

  e2::host_type& lhost = ns.new_vector_space<e2>();
  lhost.get_read_write_access();

  static const string lhost_name = lhost.name();

  // Check if the poset is in the namespace.
  bool has_poset = ns.contains_poset(lhost_name, false);
  cout << boolalpha << "has_poset = " << has_poset << endl;

  // Fails in this constructor.  See traceback below.
  // Note: This fails for ""e2_position_t2_e2" also.
  //tp_space* lhost2 = new tp_space(&ns, lhost_name);

  //cout << ns << endl;

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  return 0;
}

// (gdb) run
// Starting program: /home/wemason/head/family-factory-dev-2/fiber_bundles/fiber_spaces/test.t
// has_poset = true

// Program received signal SIGSEGV, Segmentation fault.
// 0x00e62dc8 in sheaf::poset_state_handle::is_same_state (this=0x88a8658, xother=0xfd005a)
//     at /home/wemason/head/family-factory-dev-2/sheaves/posets/poset_state_handle.cc:362
// 362       result = (state_obj() == xother->state_obj());
// (gdb) where
// #0  0x00e62dc8 in sheaf::poset_state_handle::is_same_state (this=0x88a8658, xother=0xfd005a)
//     at /home/wemason/head/family-factory-dev-2/sheaves/posets/poset_state_handle.cc:362
// #1  0x003f655e in fiber_bundle::tp_space::get_read_access (this=0x88a8658)
//     at /home/wemason/head/family-factory-dev-2/fiber_bundles/fiber_spaces/tp_space.cc:440
// #2  0x00e63497 in sheaf::poset_state_handle::attach_to_state (this=0x88a8658, xmbr=0xbff54950)
//     at /home/wemason/head/family-factory-dev-2/sheaves/posets/poset_state_handle.cc:523
// #3  0x00e6320f in sheaf::poset_state_handle::attach_to_state (this=0x88a8658, xhost=0xbff54a00,
//     xname=@0x804ad38) at /home/wemason/head/family-factory-dev-2/sheaves/posets/poset_state_handle.cc:456
// #4  0x003f57fc in tp_space (this=0x88a8658, xhost=0xbff54a00, xname=@0x804ad38)
//     at /home/wemason/head/family-factory-dev-2/fiber_bundles/fiber_spaces/tp_space.cc:180
// #5  0x08049624 in main(int xargc, char* xargv[]) () at test.t.cc:32
