
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

/// Unit test for class sec_jcb.

#include "sec_jcb.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_utils.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  template<typename S>
  void
  test_section()
  {
    // Preconditions:

    // Body:

    //==========================================================================

    cout << boolalpha;

    typedef typename S::fiber_type F;

    //static const string& static_class_name();

    print_subheader("Test static const string& static_class_name()");

    const string& lname = S::static_class_name();
    cout << "  lname = " << lname << endl;

    //==========================================================================

    //S();
    print_subheader("Test default constructor: " + lname + "()");

    S lsection;
    cout << "  lsection = " << lsection << endl;

    //S(const S& xother);
    print_subheader("Test copy constructor: " + lname
                    + "(const " + lname +"& xother)");

    S lsection_copy(lsection);
    cout << "  lsection_copy = " << lsection_copy << endl;

    //S& operator=(const S& xother);
    print_subheader("Test assignment operator: " + lname 
                    + "& operator=(const " + lname + "& xother)");
 
    S lsection_assign = lsection;
    cout << "  lsection_assign = " << lsection_assign << endl;

    //S& operator=(const ed_lite& xother);

    ////ed_lite led_lite;
    ////S& lsection_lite_assign = led_lite;

    //virtual const fiber_type& fiber_prototype() const;
    print_subheader("Test virtual const fiber_type& fiber_prototype() const"); 

    const F& lfiber_type = lsection.fiber_prototype();

    // Can't print because it's not attached.
    //cout << "  lfiber_type = " << lfiber_type << endl;

    //virtual S* clone() const;
    print_subheader("Test virtual " + lname +"* clone() const"); 

    S* lsection_clone = lsection.clone();
    cout << "  *lsection_clone = " << *lsection_clone << endl;

    // Not attached; so won't work;
    //S* lsection_clone2 = lsection.clone(false, false);

    //virtual const string& class_name() const;
    print_subheader("Test virtual const string& class_name() const"); 

    const string& lclass_name = lsection.class_name();
    cout << "  lclass_name = " << lclass_name << endl;

    //bool fiber_is_ancestor_of(const any* xother) const;
    print_subheader("Test bool fiber_is_ancestor_of(const any* xother) const"); 

    bool lfiber_is_ancestor_of = lsection.fiber_is_ancestor_of(lsection_clone);
    cout << "lfiber_is_ancestor_of = " << lfiber_is_ancestor_of << endl;

    //bool is_ancestor_of(const any* xother) const;
    print_subheader("Test bool is_ancestor_of(const any* xother) const"); 

    bool lis_ancestor_of = lsection.is_ancestor_of(lsection_clone);
    cout << "lis_ancestor_of = " << lis_ancestor_of << endl;

    //bool invariant() const;
    print_subheader("Test bool invariant() const"); 

    bool linvariant = lsection.invariant();
    cout << "linvariant = " << linvariant  << endl;

    //==========================================================================


    // Postconditions:

    // Exit:

    return;

  }

} // end unnamed namespace


int
main(int xargc, char *xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing sec_jcb");

  //============================================================================

  test_section<sec_jcb>();

  //============================================================================

  print_footer("Ending testing sec_jcb");

  // Postconditions:

  // Exit:

  return 0;
}

