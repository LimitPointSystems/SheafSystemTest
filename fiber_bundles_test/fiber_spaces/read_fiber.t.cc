
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

/// @example read_fiber.t.cc
/// Test driver for cluster fiber_spaces.

#include "SheafSystem/at0.h"
#include "SheafSystem/at1.h"
#include "SheafSystem/atp.h"
#include "SheafSystem/base_space_poset.h"
#include "SheafSystem/e1.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/e3.h"
#include "SheafSystem/ed.h"
#include "SheafSystem/gl3.h"
#include "SheafSystem/gln.h"
#include "SheafSystem/jcb.h"
#include "SheafSystem/jcb_e13.h"
#include "SheafSystem/jcb_e23.h"
#include "SheafSystem/jcb_e33.h"
#include "SheafSystem/jcb_ed.h"
#include "SheafSystem/jcb_ed.h"
#include "SheafSystem/met.h"
#include "SheafSystem/met_e1.h"
#include "SheafSystem/met_e2.h"
#include "SheafSystem/met_e3.h"
#include "SheafSystem/met_ed.h"
#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/poset.h"
#include "SheafSystem/poset_dof_map.h"
#include "SheafSystem/poset_handle_factory.h"
#include "SheafSystem/sec_rep_space_member.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/st2.h"
#include "SheafSystem/st2_e2.h"
#include "SheafSystem/st2_e3.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/stp.h"
#include "SheafSystem/subposet.h"
#include "SheafSystem/t2.h"
#include "SheafSystem/tuple.h"
#include "SheafSystem/tp.h"
#include "SheafSystem/vd.h"

using namespace std;
using namespace fiber_bundle;

// void
// test_vd(namespace_poset& ns)
// {

//   poset* host = new poset(&ns, "vd_host");
//   host->get_read_write_access();

//   cout << *host << endl;

//   vd* mbr = new vd(host, "test1");

//   cout << "####################\n" << *mbr << endl;

//   double xcomps[2];

//   mbr->components_pa(xcomps, 2);

//   for(int i=0; i<2; i++)
//     cout << xcomps[i] << endl;

//   vd mbr2(host, "test2");
//   double* xcomps2 = mbr2.components();

//   for(int i=0; i<2; i++)
//     cout << xcomps2[i] << endl;

//   mbr2.detach_from_state();

//   //vd* test = new vd(host);


//   //   double xcomps[4];

//   //   test1->components(xcomps);

//   //   for(int i=0; i<4; i++)
//   //     cout << xcomps[i] << endl;

//   //   test2->components(xcomps);

//   //   for(int i=0; i<4; i++)
//   //     cout << xcomps[i] << endl;

//   //   test1->detach_from_state();
//   //   test2->detach_from_state();

//   host->release_access();
// }

// void
// test_ed(namespace_poset& ns)
// {

//   poset* host = new poset(&ns, "ed_host");
//   host->get_read_write_access();

//   cout << *host << endl;

//   ed* mbr = new ed(host, "test1");

//   cout << "####################\n" << *mbr << endl;

//   double comps[2];

//   mbr->components_pa(comps, 2);

//   for(int i=0; i<2; i++)
//   {
//     cout << comps[i] << endl;
//   }

//   host->release_access();
// }


// void
// test_e1(namespace_poset& ns)
// {
//   poset* host = new poset(&ns, "e1_host");
//   host->get_read_write_access();

//   cout << *host << endl;

//   e1* mbr = new e1(host, "test1");

//   cout << "####################\n" << *mbr << endl;

//   cout << mbr->component() << endl;

//   host->release_access();
// }

// void
// test_e2(namespace_poset& ns)
// {

//   poset* host = new poset(&ns, "e2_host");
//   host->get_read_write_access();

//   cout << *host << endl;

//   e2* mbr = new e2(host, "test1");

//   cout << "####################\n" << *mbr << endl;

//   double comps[2];

//   mbr->components_pa(comps, 2);

//   for(int i=0; i<2; i++)
//   {
//     cout << comps[i] << endl;
//   }

//   host->release_access();
// }

// void
// test_e3(namespace_poset& ns)
// {

//   poset* host = new poset(&ns, "e3_host");
//   host->get_read_write_access();

//   cout << *host << endl;

//   e3* mbr = new e3(host, "test1");

//   cout << "####################\n" << *mbr << endl;

//   double comps[3];

//   mbr->components_pa(comps, 3);

//   for(int i=0; i<3; i++)
//   {
//     cout << comps[i] << endl;
//   }

//   host->release_access();
// }

// void
// test_state_tuple(namespace_poset& ns)
// {
//   poset* st_host = new poset(&ns, "state_tuple_1_host");
//   st_host->get_read_write_access();

//   int mbr_ct = st_host->member_ct();

//   cout << "#################### mbr_ct = " << mbr_ct  << endl;

//   for(int i=2; i<mbr_ct; i++)
//   {
//     state_tuple mbr(st_host, i);
//     state_tuple_component* stc = mbr.comp(0); // just 1 comp for this example
//     stc->get_read_access();

//     cout << "#################### srs_mbr = "
//     << *stc
//     << "#################### the_dofs[0] = "
//     << stc->value()
//     << endl;

//     stc->release_access();
//     mbr.detach_from_state();
//   }

//   st_host->release_access();
// }

int
main()
{
  namespace_poset ns("test");
  ns.get_read_write_access();

  storage_agent sa("fiber.t.hdf",sheaf_file::READ_ONLY,false);
  sa.read_entire(ns);

  //test_vd(ns);
  //test_ed(ns);
  //test_e1(ns);
  //test_e2(ns);
  //test_e3(ns);

  ///@todo Add test for all other fiber_space classes.
  ///
  /// @issue The state tuple construct in this test driver will not
  ///          properly execute after refactor-8.  Either, fix this
  ///          test or remove it.
  ///

  //test_state_tuple(&ns);

  return 0;
}
