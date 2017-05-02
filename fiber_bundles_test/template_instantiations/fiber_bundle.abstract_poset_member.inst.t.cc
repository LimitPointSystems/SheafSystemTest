
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

/// @example
/// Unit test driver for template class fiber_bundles_abstract_poset_member.

#include "SheafSystem/abstract_poset_member.impl.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystemTest/test_fiber_bundles.impl.h"
#include "SheafSystemTest/test_utils.h"

#include "SheafSystem/at0.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/at2.h"
#include "SheafSystem/at2_e2.h"
#include "SheafSystem/at2_e3.h"
#include "SheafSystem/at3.h"
#include "SheafSystem/at3_e3.h"
#include "SheafSystem/atp.h"
#include "SheafSystem/e1.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/e3.h"
#include "SheafSystem/e4.h"
#include "SheafSystem/ed.h"
#include "SheafSystem/gl2.h"
#include "SheafSystem/gl3.h"
#include "SheafSystem/gln.h"
#include "SheafSystem/gln_space.h"
#include "SheafSystem/jcb.h"
#include "SheafSystem/jcb_e13.h"
#include "SheafSystem/jcb_e23.h"
#include "SheafSystem/jcb_e33.h"
#include "SheafSystem/jcb_space.h"
#include "SheafSystem/met.h"
#include "SheafSystem/met_e1.h"
#include "SheafSystem/met_e2.h"
#include "SheafSystem/met_e3.h"
#include "SheafSystem/met_ed.h"
#include "SheafSystem/st2.h"
#include "SheafSystem/st2_e2.h"
#include "SheafSystem/st2_e3.h"
#include "SheafSystem/st3.h"
#include "SheafSystem/st3_e3.h"
#include "SheafSystem/st4.h"
#include "SheafSystem/st4_e2.h"
#include "SheafSystem/st4_e3.h"
#include "SheafSystem/stp.h"
#include "SheafSystem/stp_space.h"
#include "SheafSystem/t2.h"
#include "SheafSystem/t2_e2.h"
#include "SheafSystem/t2_e3.h"
#include "SheafSystem/t3.h"
#include "SheafSystem/t3_e3.h"
#include "SheafSystem/t4.h"
#include "SheafSystem/t4_e2.h"
#include "SheafSystem/t4_e3.h"
#include "SheafSystem/tp.h"
#include "SheafSystem/tp_space.h"
#include "SheafSystem/tuple.h"
#include "SheafSystem/vd.h"


using namespace std;
using namespace fiber_bundle;


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  print_header("Begin testing abstract_poset_member");

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  //============================================================================

  ltest &= test_persistent_abstract_poset_member_facet<at0>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<at0_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<at1, e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<at1_lite, e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<at2, at2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<at2_lite, at2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<at3, at3_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<at3_lite, at3_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<atp, at2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<atp_lite, at2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<at2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<at2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<at2_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<at2_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<at3_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<at3_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<e1>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<e1_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<e4>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<e4_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<ed, e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<ed_lite, e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<gl2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<gl2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<gl3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<gl3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<gln, gl2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<gln_lite, gl2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb_e13>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_e13_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb_e23>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_e23_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb_e33>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_e33_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb_ed, jcb_e23>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_ed_lite, jcb_e13_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb, jcb_e23>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_lite, jcb_e13_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<met_e1>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<met_e1_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<met_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<met_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<met_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<met_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<met_ed, met_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<met_ed_lite, met_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<met, met_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<met_lite, met_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<st2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<st2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<st2_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<st2_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<st3_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<st3_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<st4_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<st4_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<st4_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<st4_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t2_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t2_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t3_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t3_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t4_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t4_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t4_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t4_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<st2, st2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<st2_lite, st2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<st3, st3_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<st3_lite, st3_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<st4, st4_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<st4_lite, st4_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<stp, st2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<stp_lite, st2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t2, t2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t2_lite, t2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t3, t3_e3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t3_lite, t3_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t4, t4_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t4_lite, t4_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<tp, t2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<tp_lite, t2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet< fiber_bundle::tuple, t2_e2>(lns);
  //ltest &= test_volatile_abstract_poset_member_facet<tuple_lite, t2_e2_lite>();
  //   tuple_lite has no row_dofs_type.

  ltest &= test_persistent_abstract_poset_member_facet<vd, e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<vd_lite, e2_lite>();

  //============================================================================

  print_header("End testing abstract_poset_member");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
