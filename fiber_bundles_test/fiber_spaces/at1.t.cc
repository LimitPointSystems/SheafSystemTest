
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

/// @example at1.t.cc
/// Unit test driver for class at1.

#include "SheafSystem/at1.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/at0_space.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystemTest/test_fibers.impl.h"
//#include "SheafSystem/storage_agent.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  void
  test_at1_volatile()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    test_volatile_common<at1_lite>();

    test_volatile_class_tp_facet<at1_lite>();

    //==========================================================================

    //at1_lite(const row_dofs_type& xrow_dofs);

     at1_lite::row_dofs_type lrow_dofs;
     at1_lite lfiber(lrow_dofs);


     //at1_lite& operator=(const row_dofs_type& xrow_dofs);

     at1_lite lfiber_assign = lrow_dofs;

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

  void
  test_at1_persistent(fiber_bundles_namespace& xns)
  {
    // Preconditions:

    // Body:

    //==========================================================================

    typedef at0 S;
    poset_path lscalar_space_path = S::standard_host(xns, "", true).path(true);

    typedef at1 P;

    P::host_type& lhost = P::new_host(xns,
				      "test_at1_persistent",
				      P::standard_schema_path(),
				      lscalar_space_path,
				      true);
    lhost.get_read_write_access(true);
  
    //test_persistent_type<P>(lhost);

    P* lfiber = new P(&lhost);

    P::host_type* lhost2 = lfiber->host();
    cout << "lhost2 = " << lhost2 << endl;

    const string lmember_name("test_fiber");
    lfiber->put_name(lmember_name, true, false);

    const string& lclass_name = lfiber->class_name();
    cout << "lclass_name = " << lclass_name << endl;


    int lfactor_ct = lfiber->factor_ct();
    cout << "lfactor_ct = " << lfactor_ct << endl;

    //$$SCRIBBLE: Inconsistency amoung classes here???
    //P* lfiber2 = new P(*lfiber);
    P* lfiber2 = new P(lfiber);

    P lfiber3 = *lfiber;

    const scoped_index lindex = lfiber->index();

    const poset* lposet = dynamic_cast<poset*>(&lhost);
    P* lfiber4 = new P(lposet, lmember_name);
    P* lfiber5 = new P(lposet, lindex);

    P* lfiber6 = lfiber5->clone();

    //==========================================================================

    P lfiber7;
    lfiber7 = *lfiber6;

    //==========================================================================

    // virtual const volatile_type& lite_prototype() const

    P::volatile_type lvolatile = lfiber->lite_prototype();

    //virtual volatile_type* lite_type() const;

    P::volatile_type* lvolatile_ptr = lfiber->lite_type();

    //==========================================================================

    lfiber->detach_from_state();
    lfiber2->detach_from_state();
    lfiber3.detach_from_state();
    lfiber4->detach_from_state();
    lfiber5->detach_from_state();
    lfiber6->detach_from_state();

    lfiber7.detach_from_state();

    delete lfiber;
    delete lfiber2;
    delete lfiber4;
    delete lfiber5;
    delete lfiber6;

    lhost.release_access();

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }


} // end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  // Create the namespace.

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  // Run tests.

  test_at1_volatile();
  test_at1_persistent(lns);

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  //storage_agent write_agent(filename + ".hdf");
  //write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
