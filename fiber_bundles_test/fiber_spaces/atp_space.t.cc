// $RCSfile: atp_space.t.cc,v $ $Revision: 1.7 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example atp_space.t.cc
/// Test driver for atp_space.

#include "atp_space.h"

#include "arg_list.h"
#include "at0_space.h"
#include "assert_contract.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "vd_space.h"
#include "wsv_block.h"

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

  string lvector_dof_specs = "x DOUBLE false y DOUBLE false";

  schema_poset_member lvector_schema(lns,
                              "vd_space_test_schema",
                              vd_space::standard_schema_path(),
                              lvector_dof_specs,
                              true,
                              true);

  poset_path lvector_schema_path = lvector_schema.path();
  lvector_schema.detach_from_state();

  arg_list lvector_args = vd_space::make_arg_list(lscalar_path);
  
  vd_space* lvector_space = new vd_space(lns, 
					 "vd_space_test", 
					 lvector_args, 
					 lvector_schema_path, 
					 true);
  
  poset_path lvector_path = lvector_space->path();

  //cout << *lvector_space << endl;

  // Make a tensor space schema; copied from t2_e2::make_standard_schema().

  string ltensor_dof_specs = "xx DOUBLE false ";
  ltensor_dof_specs       += "xy DOUBLE false ";
  ltensor_dof_specs       += "yx DOUBLE false ";
  ltensor_dof_specs       += "yy DOUBLE false";


  schema_poset_member ltensor_schema(lns,
                              "atp_space_test_schema",
                              atp_space::standard_schema_path(),
                              ltensor_dof_specs,
                              true,
                              true);

  poset_path ltensor_schema_path = ltensor_schema.path();
  ltensor_schema.detach_from_state();

  arg_list ltensor_args = atp_space::make_arg_list(2, lvector_path);
  
  vd_space* ltensor_space = new tp_space(lns, 
					 "atp_space_test", 
					 ltensor_args, 
					 ltensor_schema_path, 
					 true);
  
  //cout << *ltensor_space << endl;

  //============================================================================

  // Test member functions common to all "*_space" classes.

  // test_spaces_common<atp_space>(lns, ???);
  
  //============================================================================


  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
