// $RCSfile: tuple_space.t.cc,v $ $Revision: 1.8 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example tuple_space.t.cc
/// Test driver for tuple_space.

#include "tuple_space.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "tuple.h"
#include "tuple_space.h"
#include "sec_tuple.h"
#include "sec_tuple_space.h"
#include "wsv_block.h"

#include "namespace_poset_member.h"

using namespace fiber_bundle;

namespace
{
  template <typename T>
  class space_child : public T
  {
  public:

    typedef typename T::member_type M;

    space_child() : T() { }

    space_child(const T& xother) : T(xother) { }

    space_child(const namespace_poset& xhost,
                scoped_index xindex, bool xauto_access)
      : T(xhost, xindex, xauto_access)
    {
    }

    space_child(const namespace_poset& xhost,
                const string& xname, bool xauto_access)
      : T(xhost, xname, xauto_access)
    {
    }

    space_child(const namespace_poset_member& xmbr, bool xauto_access)
      : T(xmbr, xauto_access)
    {
    }

    space_child(M* xtop, M* xbottom)
      : T(xtop, xbottom)
    {
    }

    virtual ~space_child() {}

    space_child& operator=(const poset_state_handle& xother)
    {
      T::operator=(xother);
    }
  };


  template <typename T>
  void test_spaces_common( fiber_bundles_namespace& lns, T& lvector_space2)
  {
    // Preconditions:

    // Body:

    typedef typename T::member_type M;
    typedef space_child<T> TC;

    lvector_space2.get_read_access();

    poset_path lpath = lvector_space2.path();
    cout << "lpath = " << lpath << endl;

    //T lvector_space3(lvector_space2);

    //T lvector_space4(lns, lvector_space2.index());

    //T lvector_space5(lns, lvector_space2.path().member_name());

    T* lvector_space_clone = lvector_space2.clone();
    cout << "lvector_space_clone = " << lvector_space_clone << endl;

    bool lis_ancestor_of = lvector_space2.is_ancestor_of(lvector_space_clone);
    cout << "lis_ancestor_of = " << boolalpha << lis_ancestor_of << endl;

    //TC lvector_space3(lvector_space2);
    TC* lvector_space3 = new TC(lvector_space2);

    //TC lvector_space4(lns, lvector_space2.index(), true);
    TC* lvector_space4 = new TC(lns, lvector_space2.index(), true);

    //TC lvector_space5(lns, lvector_space2.path().poset_name(), true);
    TC* lvector_space5 = new TC(lns, lvector_space2.path().poset_name(), true);

    lns.get_read_access();
    namespace_poset_member lmbr(&lns, lvector_space2.index());
    lns.release_access();

    TC* lvector_space6 =
      new TC(lmbr, true);

    lmbr.detach_from_state();

    TC* lvector_space7 =
      new TC(new M, new M);

    //at1_space& operator=(const poset_state_handle& xother);

    TC* lvector_space8 = new TC;
    lvector_space5->get_read_access();
    poset_state_handle* lpsh = lvector_space5;
    lvector_space8->operator=(*lpsh);

    // Postconditions:

    // Exit:
  
  }
 
} // end unnamed namespace.

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);

  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);
  lns.get_read_write_access();

  // Make a tuple space schema

  string lmember_names = "x DOUBLE false y DOUBLE false";

  schema_poset_member lschema(lns,
                              "tuple_space_test_schema",
                              tuple_space::standard_schema_path(),
                              lmember_names,
                              true,
                              true);

  poset_path lschema_path = lschema.path();

  lschema.detach_from_state();

  arg_list largs = tuple_space::make_arg_list(2);
  
  poset_path lfiber_space_path("tuple_space_test");
  
  tuple::host_type& lspace = lns.new_fiber_space<tuple>(lfiber_space_path, largs, lschema_path, true);

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<tuple_space>(lns, lspace);
 
  //int lfactor_ct(bool) const

  int lfactor_ct = lspace.factor_ct(true);
  cout << "lfactor_ct = " << lfactor_ct << endl;

  //============================================================================
  
  cout << lspace << endl;

  // Done.

  return 0;
}

  
