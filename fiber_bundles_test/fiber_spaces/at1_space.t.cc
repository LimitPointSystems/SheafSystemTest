// $RCSfile: at1_space.t.cc,v $ $Revision: 1.7 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example at1_space.t.cc
/// Test driver for at1_space.

#include "at1_space.h"

#include "arg_list.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "assert_contract.h"
#include "error_message.h"
#include "e2.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iomanip.h"
#include "std_iostream.h"
#include "storage_agent.h"
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

//   class at1_space_child : public at1_space
//   {
//   public:
//     at1_space_child()
//       : at1_space()
//     {
//     }

//     at1_space_child(const at1_space& xother)
//       : at1_space(xother)
//     {
//     }

//     at1_space_child(const namespace_poset& xhost,
//                     scoped_index xindex, bool xauto_access)
//       : at1_space(xhost, xindex, xauto_access)
//     {
//     }

//     at1_space_child(const namespace_poset& xhost,
//                     const string& xname, bool xauto_access)
//       : at1_space(xhost, xname, xauto_access)
//     {
//     }

//     at1_space_child(const namespace_poset_member& xmbr, bool xauto_access)
//       : at1_space(xmbr, xauto_access)
//     {
//     }

//     at1_space_child(at1* xtop, at1* xbottom)
//       : at1_space(xtop, xbottom)
//     {
//     }

//     virtual ~at1_space_child() {}

//     at1_space_child& operator=(const poset_state_handle& xother)
//     {
//       at1_space::operator=(xother);
//     }
//   };

//   template <typename T>
//   void test_spaces_common( fiber_bundles_namespace& lns, T& lvector_space2)
//   {
//     // Preconditions:

//     // Body:

//     lvector_space2.get_read_access();

//     poset_path lpath = lvector_space2.path();
//     cout << "lpath = " << lpath << endl;

//     //T lvector_space3(lvector_space2);

//     //T lvector_space4(lns, lvector_space2.index());

//     //T lvector_space5(lns, lvector_space2.path().member_name());

//     T* lvector_space_clone = lvector_space2.clone();
//     cout << "lvector_space_clone = " << lvector_space_clone << endl;

//     bool lis_ancestor_of = lvector_space2.is_ancestor_of(lvector_space_clone);
//     cout << "lis_ancestor_of = " << boolalpha << lis_ancestor_of << endl;

//     //at1_space_child lvector_space3(lvector_space2);
//     at1_space_child* lvector_space3 = new at1_space_child(lvector_space2);

//     //at1_space_child lvector_space4(lns, lvector_space2.index(), true);
//     at1_space_child* lvector_space4 =
//       new at1_space_child(lns, lvector_space2.index(), true);

//     //at1_space_child lvector_space5(lns, lvector_space2.path().poset_name(), true);
//     at1_space_child* lvector_space5 =
//       new at1_space_child(lns, lvector_space2.path().poset_name(), true);

//     lns.get_read_access();
//     namespace_poset_member lmbr(&lns, lvector_space2.index());
//     lns.release_access();

//     at1_space_child* lvector_space6 =
//       new at1_space_child(lmbr, true);

//     lmbr.detach_from_state();

//     at1_space_child* lvector_space7 =
//       new at1_space_child(new at1, new at1);

//     //at1_space& operator=(const poset_state_handle& xother);

//     at1_space_child* lvector_space8 = new at1_space_child;
//     lvector_space5->get_read_access();
//     poset_state_handle* lpsh = lvector_space5;
//     lvector_space8->operator=(*lpsh);

//     // Postconditions:

//     // Exit:
  
//   }

} // end namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  require(xargc > 0);
 
  // Body:

  string filename = filename_from_cmdline(*xargv);

  fiber_bundles_namespace lns(filename);

  // Make a scalar space, use standard schema.

  arg_list lscalar_args = at0_space::make_arg_list();
  poset_path lscalar_schema_path = at0_space::standard_schema_path();
  at0_space* lscalar_space = new at0_space(lns, 
					   "at0_space_test", 
					   lscalar_args,
					   lscalar_schema_path,
					   true);

  poset_path lscalar_path = lscalar_space->path();

  //cout << *lscalar_space << endl;

  // Make a vector space schema; copied from e2::make_standard_schema().

  string ldof_specs = "x DOUBLE false y DOUBLE false";

  schema_poset_member lvector_schema(lns,
                              "at1_space_test_schema",
                              at1_space::standard_schema_path(),
                              ldof_specs,
                              true,
                              true);

  poset_path lvector_schema_path = lvector_schema.path();
  lvector_schema.detach_from_state();

  arg_list lvector_args = at1_space::make_arg_list(lscalar_path);
  
  vd_space* lvector_space = new vd_space(lns, 
					 "at1_space_test", 
					 lvector_args, 
					 lvector_schema_path, 
					 true);

  //cout << *lvector_space << endl;

  // Test deep instantiation.

  at1_space& lvector_space2 =
    lns.new_vector_space<e2>("deep_instantiation_test_e2");

  //============================================================================

  // Test member functions common to all "*_space" classes.

  test_spaces_common<at1_space>(lns, lvector_space2);
  
  //============================================================================
  
  //cout << lns << endl;

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}

  
