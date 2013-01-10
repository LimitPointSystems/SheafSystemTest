// $RCSfile: vd_space.t.cc,v $ $Revision: 1.7 $ $Date: 2012/07/04 16:42:08 $

// $Name: HEAD $
//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @example vd_space.t.cc
/// Test driver for vd_space.

#include "vd_space.h"

#include "arg_list.h"
#include "at0_space.h"
#include "assert_contract.h"
#include "error_message.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "storage_agent.h"
#include "vd.h"
#include "wsv_block.h"

#include "namespace_poset_member.h"

using namespace fiber_bundle;

namespace
{

  poset_path make_vector_space_schema(fiber_bundles_namespace& xns)
  {
    // Make a vector space schema; copied from e2::make_standard_schema().

    string ldof_specs = "x DOUBLE false y DOUBLE false";

    schema_poset_member lvector_schema(xns,
				       "shallow_instantiation_test_vd_space_schema",
				       vd_space::standard_schema_path(),
				       ldof_specs,
				       true,
				       true);

    poset_path result = lvector_schema.path();
    lvector_schema.detach_from_state();

    return result;
  }

  void test_shallow_instantiation(fiber_bundles_namespace& xns, const poset_path& xvector_schema_path)
  {
    // Make a scalar space, use standard schema.

    arg_list lscalar_args = at0_space::make_arg_list();
    poset_path lscalar_schema_path = at0_space::standard_schema_path();
    at0_space* lscalar_space = new at0_space(xns, 
					     "shallow_instantiation_test_at0_space", 
					     lscalar_args,
					     lscalar_schema_path,
					     true);

    poset_path lscalar_path = lscalar_space->path();

    //    cout << *lscalar_space << endl;

    arg_list lvector_args = vd_space::make_arg_list(lscalar_path);
  
    vd_space* lvector_space = new vd_space(xns, 
					   "shallow_instantiation_test_vd_space", 
					   lvector_args, 
					   xvector_schema_path, 
					   true);
  
    //    cout << *lvector_space << endl;

    return;
  }

  void test_deep_instantiation(fiber_bundles_namespace& xns, const poset_path& xvector_schema_path)
  {

    poset_path lpath("deep_instantiation_test_vd_space", "");
    arg_list lvector_args = vd_space::make_arg_list("");


    vd_space& lspace = xns.new_vector_space<vd>(lpath, lvector_args, xvector_schema_path);
    
    
    //    cout << lspace << endl;

    return;
  }
 
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

  poset_path lvector_schema_path = make_vector_space_schema(lns);

  test_shallow_instantiation(lns, lvector_schema_path);
  
  test_deep_instantiation(lns, lvector_schema_path);

  //============================================================================

  //$$SCRIBBLE: Have test_deep_instantiation return lspace so we don't
  //            need to recreate it.

  // Test member functions common to all "*_space" classes.

  poset_path lpath("deep_instantiation_test_vd_space", "");
  arg_list lvector_args = vd_space::make_arg_list("");

  vd_space& lspace =
    lns.new_vector_space<vd>(lpath, lvector_args, lvector_schema_path);
    
    
  // Test member functions common to all "*_space" classes.

  test_spaces_common<vd_space>(lns, lspace);
 
  //int factor_ct(int xd) const

  int lfactor_ct = lspace.factor_ct(2);
  cout << "lfactor_ct = " << lfactor_ct << endl;

  //void print_prereq_paths(ostream &xos, 
  //			  const vd_space& xspace, 
  //			  const string& xheading,
  //			  const string& xindent,
  //			  bool xauto_access = true);

  print_prereq_paths(cout, lspace, "vd space prereq paths:", "  ");
 
  //============================================================================

  lns.get_read_write_access();
  storage_agent sa(filename + ".hdf", sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  // Done.

  return 0;
}

  
