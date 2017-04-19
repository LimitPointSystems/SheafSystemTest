
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

/// @example template_instantiations/fiber_bundles_namespace_poset.inst.t.cc
/// Unit test driver for class namespace_poset template functions.

#include "SheafSystem/fiber_bundles_namespace.h"

#include "SheafSystem/at0.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/at2_e2.h"
#include "SheafSystem/base_space_poset.h"
#include "SheafSystem/binary_section_space_schema_poset.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/gl2.h"
#include "SheafSystem/gln_space.h"
#include "SheafSystem/jcb_e13.h"
#include "SheafSystem/jcb_space.h"
#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_at0_space.h"
#include "SheafSystem/sec_at1_space.h"
#include "SheafSystem/sec_at2_e2.h"
#include "SheafSystem/sec_atp_space.h"
#include "SheafSystem/sec_e2.h"
#include "SheafSystem/sec_rep_descriptor_poset.h"
#include "SheafSystem/sec_rep_space.h"
#include "SheafSystem/sec_st2_e2.h"
#include "SheafSystem/sec_stp_space.h"
#include "SheafSystem/sec_t2_e2.h"
#include "SheafSystem/sec_tuple_space.h"
#include "SheafSystem/sec_vd_space.h"
#include "SheafSystem/st2_e2.h"
#include "SheafSystem/stp_space.h"
#include "SheafSystem/t2_e2.h"
#include "SheafSystemTest/test_fiber_bundles.impl.h"
#include "SheafSystemTest/test_sections.h" // for make_test_base_space
#include "SheafSystemTest/test_utils.h"
#include "SheafSystem/tuple.h"
#include "SheafSystem/vd.h"
// #include "SheafSystem/section_space_schema_poset.h"


using namespace std;
using namespace fiber_bundle;


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  print_header("Begin testing fiber_bundles_namespace instantiations.");

  // Test the instantiations for fibers.

  ltest &= test_fiber_bundles_namespace_poset_facet<at0>(lns);
  ltest &= test_fiber_bundles_namespace_poset_facet<at2_e2>(lns);
  ltest &= test_fiber_bundles_namespace_poset_facet<e2>(lns);
  ltest &= test_fiber_bundles_namespace_poset_facet<gl2>(lns);
  ltest &= test_fiber_bundles_namespace_poset_facet<jcb_e13>(lns);
  ltest &= test_fiber_bundles_namespace_poset_facet<st2_e2>(lns);
  ltest &= test_fiber_bundles_namespace_poset_facet<t2_e2>(lns);

  /// @error The current implementation of test_fiber_bundles_namespace_poset_facet
  ///        does not support abstract fiber and section types.  It should
  ///        be restructured to look like test_persistent_abstract_poset_member_facet.

//   ltest &= test_fiber_bundles_namespace_poset_facet< fiber_bundle::tuple>(lns);
//   ltest &= test_fiber_bundles_namespace_poset_facet<vd>(lns);

  //============================================================================

  // Need a base space for the section tests.
  // Use make_test_base_space function from test_sections to create one. 

  const poset_path& lbase_path = make_test_base_space(lns, 2, 2);

  ltest &= test_fiber_bundles_namespace_poset_facet<sec_at0>(lns, lbase_path);
  ltest &= test_fiber_bundles_namespace_poset_facet<sec_at2_e2>(lns, lbase_path);
  ltest &= test_fiber_bundles_namespace_poset_facet<sec_e2>(lns, lbase_path);
  ltest &= test_fiber_bundles_namespace_poset_facet<sec_st2_e2>(lns, lbase_path);
  ltest &= test_fiber_bundles_namespace_poset_facet<sec_t2_e2>(lns, lbase_path);

  ltest &= test_fiber_bundles_namespace_poset_facet<sec_e2, sec_vd_space>
             (lns, lbase_path);
  ltest &= test_fiber_bundles_namespace_poset_facet<sec_e2, sec_tuple_space>
             (lns, lbase_path);
  ltest &= test_fiber_bundles_namespace_poset_facet<sec_e2, sec_rep_space>
             (lns, lbase_path);

  // No support for sec_jcb* in fiber_bundles_namespace yet.
  //ltest &= test_fiber_bundles_namespace_poset_facet<sec_jcb_e13>(lns, lbase_path);


  // Test the other instantiations.

  // base_space_poset

  ltest &= test_fiber_bundles_namespace_poset_facet<base_space_poset>(lns);

  // binary_section_space_schema_poset

  ltest &= test_fiber_bundles_namespace_poset_facet<binary_section_space_schema_poset>
             (lns, lbase_path);

  // sec_rep_descriptor_poset

  ltest &= test_fiber_bundles_namespace_poset_facet<sec_rep_descriptor_poset>
             (lns, lbase_path);

  //$$TODO:
  // section_space_schema_poset

  //============================================================================

  print_footer("End testing fiber_bundles_namespace_poset instantiations.");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}


