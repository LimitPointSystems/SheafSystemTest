
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class fiber_bundles_abstract_poset_member.

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "test_fiber_bundles.impl.h"
#include "test_utils.h"

#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "at2.h"
#include "at2_e2.h"
#include "at2_e3.h"
#include "at3.h"
#include "at3_e3.h"
#include "atp.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "e4.h"
#include "ed.h"
#include "gl2.h"
#include "gl3.h"
#include "gln.h"
#include "gln_space.h"
#include "jcb.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"
#include "jcb_space.h"
#include "met.h"
#include "met_e1.h"
#include "met_e2.h"
#include "met_e3.h"
#include "met_ed.h"
#include "st2.h"
#include "st2_e2.h"
#include "st2_e3.h"
#include "st3.h"
#include "st3_e3.h"
#include "st4.h"
#include "st4_e2.h"
#include "st4_e3.h"
#include "stp.h"
#include "stp_space.h"
#include "t2.h"
#include "t2_e2.h"
#include "t2_e3.h"
#include "t3.h"
#include "t3_e3.h"
#include "t4.h"
#include "t4_e2.h"
#include "t4_e3.h"
#include "tp.h"
#include "tp_space.h"
#include "tuple.h"
#include "vd.h"


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

  ltest &= test_persistent_abstract_poset_member_facet<at1>(lns);
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

  ltest &= test_persistent_abstract_poset_member_facet<ed>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<ed_lite, e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<gl2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<gl2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<gl3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<gl3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<gln>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<gln_lite, gl2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb_e13>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_e13_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb_e23>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_e23_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb_e33>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_e33_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb_ed>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<jcb_ed_lite, jcb_e13_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<jcb>(lns);
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

  ltest &= test_persistent_abstract_poset_member_facet<t2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t2_lite, t2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t3>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t3_lite, t3_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<t4>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<t4_lite, t4_e3_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<tp, t2_e2>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<tp_lite, t2_e2_lite>();

  ltest &= test_persistent_abstract_poset_member_facet<tuple, t2_e2>(lns);
  //ltest &= test_volatile_abstract_poset_member_facet<tuple_lite, t2_e2_lite>();
  //   tuple_lite has no row_dofs_type.

  ltest &= test_persistent_abstract_poset_member_facet<vd>(lns);
  ltest &= test_volatile_abstract_poset_member_facet<vd_lite, e2_lite>();

  //============================================================================

  print_header("End testing abstract_poset_member");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
