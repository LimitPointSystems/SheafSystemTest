// $RCSfile: fiber_bundles_namespace.inst.t.cc,v $ $Revision: 1.1.2.5 $ $Date: 2012/11/05 23:28:35 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example template_instantiations/fiber_bundles_namespace.inst.t.cc
/// Unit test driver for class fiber_bundles_namespace templated functions.

#include "fiber_bundles_namespace.h"

#include "arg_list.h"
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
#include "atp_space.h"
#include "base_space_poset.h"
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
#include "jcb_ed.h"
#include "jcb_space.h"
#include "met.h"
#include "met_e1.h"
#include "met_e2.h"
#include "met_e3.h"
#include "met_ed.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_at2.h"
#include "sec_at2_e2.h"
#include "sec_at2_e3.h"
#include "sec_at3.h"
#include "sec_at3_e3.h"
#include "sec_atp.h"
#include "sec_atp_space.h"
#include "sec_e1.h"
#include "sec_e1_uniform.h"
#include "sec_e2.h"
#include "sec_e2_uniform.h"
#include "sec_e3.h"
#include "sec_e3_uniform.h"
#include "sec_e4.h"
#include "sec_ed.h"
#include "sec_jcb.h"
#include "sec_jcb_e13.h"
#include "sec_jcb_e23.h"
#include "sec_jcb_e33.h"
#include "sec_jcb_ed.h"
#include "sec_jcb_space.h"
#include "sec_met.h"
#include "sec_met_e1.h"
#include "sec_met_e2.h"
#include "sec_met_e3.h"
#include "sec_met_ed.h"
#include "sec_st2.h"
#include "sec_st2_e2.h"
#include "sec_st2_e3.h"
#include "sec_st3.h"
#include "sec_st3_e3.h"
#include "sec_st4.h"
#include "sec_st4_e2.h"
#include "sec_st4_e3.h"
#include "sec_stp.h"
#include "sec_stp_space.h"
#include "sec_t2.h"
#include "sec_t2_e2.h"
#include "sec_t2_e3.h"
#include "sec_t3.h"
#include "sec_t3_e3.h"
#include "sec_t4.h"
#include "sec_t4_e2.h"
#include "sec_t4_e3.h"
#include "sec_tp.h"
#include "sec_tp_space.h"
#include "sec_tuple.h"
#include "sec_tuple_space.h"
#include "sec_vd.h"
#include "sec_vd_space.h"
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
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "t2.h"
#include "t2_e2.h"
#include "t2_e3.h"
#include "t3.h"
#include "t3_e3.h"
#include "t4.h"
#include "t4_e2.h"
#include "t4_e3.h"
#include "test_utils.h"
#include "tp.h"
#include "tp_space.h"
#include "tuple.h"
#include "tuple_space.h"
#include "vd.h"
#include "vd_space.h"

#include "binary_section_space_schema_poset.h"

#include "std_sstream.h"


using namespace fiber_bundle;

namespace
{

//==============================================================================

void
make_names_unique(string xnames[], int xnum_names)
{
  // Preconditions:

  require(unexecutable("xnum_names <= dimension of xnames"));

  // Body:

  // Make names "unique" by appending "_#" to each name.

  static int lname_suffix = -1;
  lname_suffix++;

  static ostringstream lname;

  for(int i=0; i<xnum_names; ++i)
  {
    lname.str("");
    lname << xnames[i] << "_" << lname_suffix;
    xnames[i] = lname.str();
  }

  // Postconditions:

  // Exit:

  return;
}

//==============================================================================

poset_path
make_base_space_1d(fiber_bundles_namespace& xns, const string& xbase_space_name)
{
  //xns.get_read_write_access();

  typedef structured_block_1d B;

  //const string lbase_space_name = "base_space_1d";
    
  base_space_poset& lhost = xns.new_base_space<B>(xbase_space_name);

  B lmesh(&lhost, 2);
  lmesh.put_name("mesh", true, true);

  poset_path result = lmesh.path(true);
    
  lmesh.detach_from_state();
    
  return result;
}

poset_path
make_base_space_2d(fiber_bundles_namespace& xns, const string& xbase_space_name)
{
  //xns.get_read_write_access();

  typedef structured_block_2d B;

  //const string lbase_space_name = "base_space_2d";
    
  base_space_poset& lhost = xns.new_base_space<B>(xbase_space_name);

  B lmesh(&lhost, 2, 2);
  lmesh.put_name("mesh", true, true);

  poset_path result = lmesh.path(true);
    
  lmesh.detach_from_state();
    
  return result;
}

poset_path
make_base_space_3d(fiber_bundles_namespace& xns, const string& xbase_space_name)
{
  //xns.get_read_write_access();

  typedef structured_block_3d B;

  //const string lbase_space_name = "base_space_3d";
    
  base_space_poset& lhost = xns.new_base_space<B>(xbase_space_name);

  B lmesh(&lhost, 2, 2, 2);
  lmesh.put_name("mesh", true, true);

  poset_path result = lmesh.path(true);
    
  lmesh.detach_from_state();
    
  return result;
}


poset_path
make_base_space(fiber_bundles_namespace& xns, const string& xbase_space_name, int xd)
{

  poset_path result;
  if(xd == 1)
  {
    result = make_base_space_1d(xns, xbase_space_name);
  }
  else if (xd == 2)
  {
    result = make_base_space_2d(xns, xbase_space_name);
  }
  else
  {
    result = make_base_space_3d(xns, xbase_space_name);
  }

  return result;
}

//==============================================================================

template<typename S>
poset_path
make_section_space(fiber_bundles_namespace& xns,
                   const poset_path& xbase_path,
                   const string& xsection_space_name)
{

  typename S::host_type& lsection_space =
    xns.new_section_space<S>(xsection_space_name, xbase_path);

  cout << "lsection_space.path() = " << lsection_space.path() << endl;
  cout << endl;

  poset_path result = lsection_space.path(true);

  return result;
}


template<typename S>
poset_path
make_scalar_section_space_schema(fiber_bundles_namespace& xns,
                                 const poset_path& xbase_path,
                                 const string& xscalar_section_space_name)
{
  arg_list largs = binary_section_space_schema_poset::make_arg_list("", xbase_path, "");

  const string lscalar_space_schema_name = xscalar_section_space_name + "_schema";

  poset_path lscalar_space_schema_path =
    xns.new_scalar_section_space_schema<S>(lscalar_space_schema_name, largs);

  poset_path result = lscalar_space_schema_path;

  return result;
}


template<typename S>
poset_path
make_scalar_section_space(fiber_bundles_namespace& xns,
                          const poset_path& xbase_path,
                          const poset_path& xscalar_space_schema_path,
                          const string& xscalar_sec_space_name)
{

  typedef typename S::host_type SHOST_TYPE;

  arg_list largs = SHOST_TYPE::make_arg_list();

  SHOST_TYPE& lscalar_sec_space = 
      xns.new_scalar_section_space<S>(xscalar_sec_space_name,
                                      largs,
                                      xscalar_space_schema_path);

  poset_path result = lscalar_sec_space.path(true);

  return result;
}

template<typename V>
poset_path
make_vector_section_space_schema(fiber_bundles_namespace& xns,
                                 const poset_path& xbase_path,
                                 const string& xvector_section_space_name)
{

  arg_list largs = binary_section_space_schema_poset::make_arg_list("", xbase_path, "");

  const string lvector_space_schema_name = xvector_section_space_name + "_schema";

  poset_path lvector_space_schema_path =
    xns.new_vector_section_space_schema<V>(lvector_space_schema_name, largs);

  poset_path result = lvector_space_schema_path;

  return result;
}

template<typename V>
poset_path
make_vector_section_space(fiber_bundles_namespace& xns,
                          const poset_path& xbase_path,
                          const poset_path& xscalar_space_schema_path,
                          const poset_path& xscalar_section_space_path,
                          const poset_path& xvector_space_schema_path,
                          const string& xvector_sec_space_name)
{

  typename V::host_type& lvector_sec_space =
    xns.new_vector_section_space<V>(xvector_sec_space_name,
                                    "",
                                    xvector_space_schema_path,
                                    xscalar_section_space_path,
                                    "",
                                    xscalar_space_schema_path);

  poset_path result = lvector_sec_space.path(true);

  return result;
}


template<typename T>
poset_path
make_tensor_section_space_schema(fiber_bundles_namespace& xns,
                                 const poset_path& xbase_path,
                                 const string& xtensor_section_space_name)
{
  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase_path, "");

  const string ltensor_space_schema_name = xtensor_section_space_name + "_schema";

  poset_path ltensor_space_schema_path =
    xns.new_tensor_section_space_schema<T>(ltensor_space_schema_name, largs);

  poset_path result = ltensor_space_schema_path;

  return result;
}

template<typename T>
poset_path
make_tensor_section_space(fiber_bundles_namespace& xns,
                          const poset_path& xbase_path,
                          const poset_path& xscalar_space_schema_path,
                          const poset_path& xscalar_section_space_path,
                          const poset_path& xvector_space_schema_path,
                          const poset_path& xvector_section_space_path,
                          const poset_path& xtensor_space_schema_path,
                          const string& xtensor_section_space_name)
{
  typename T::host_type& ltensor_sec_space =
    xns.new_tensor_section_space<T>(xtensor_section_space_name,
							        "",
							        xtensor_space_schema_path,
							        xvector_section_space_path,
							        "",
							        xvector_space_schema_path,
							        xscalar_section_space_path,
							        "",
							        xscalar_space_schema_path);

  poset_path result = ltensor_sec_space.path(true);

  return result;
}


//==============================================================================

template<typename S>
bool
test_new_section_space(fiber_bundles_namespace& xns, int xd)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(1 <= xd && xd <= 3);

  // Body:

  print_header("test_new_section_space");

  //============================================================================

  cout << "S::static_class_name() = " << S::static_class_name() << endl;

  //============================================================================

  // Make names for the spaces:

  string lnames[2] = {"base_space",
                      "section_space"};

  make_names_unique(lnames, 2);
 
  const string& lbase_space_name    = lnames[0];
  const string& lsection_space_name = lnames[1];

 // Make a base space.
 
  poset_path lbase_path = make_base_space(xns, lbase_space_name, xd);

  cout << "lbase_path = " << lbase_path << endl;
  cout << endl;
 
  // Create the section space.

  poset_path lsection_space_path =
    make_section_space<S>(xns, lbase_path, lsection_space_name);

  cout << "lsection_space_path = " << lsection_space_path << endl;
  cout << endl;

  // Postconditions:
  
  // Exit:

  return true;
}

//==============================================================================
//==============================================================================

template<typename S>
bool
test_new_scalar_section_space(fiber_bundles_namespace& xns, int xd)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(1 <= xd && xd <= 3);

  // Body:

  print_header("test_new_scalar_section_space");

  //============================================================================

  // Make names for the spaces:

  string lnames[2] = {"base_space",
                      "scalar_section_space"};

  make_names_unique(lnames, 2);
  
  const string& lscalar_section_space_name   = lnames[0];
  const string& lbase_space_name  = lnames[1];

  //============================================================================

  // Make a base space.

  poset_path lbase_path = make_base_space(xns, lbase_space_name, xd);

  cout << "lbase_path = " << lbase_path << endl;
  cout << endl;

  //============================================================================

  // Create the section space schema.

  poset_path lscalar_space_schema_path =
    make_scalar_section_space_schema<S>(xns, lbase_path, lscalar_section_space_name);

  cout << "lscalar_space_schema_path = " << lscalar_space_schema_path << endl;
  cout << endl;

  //============================================================================

  // Create the section space.

  poset_path lscalar_section_space_path =
    make_scalar_section_space<S>(xns,
                                 lbase_path,
                                 lscalar_space_schema_path,
                                 lscalar_section_space_name);

  cout << "lscalar_section_space_path = " << lscalar_section_space_path << endl;
  cout << endl;

  //============================================================================

  // Postconditions:

  // Exit:

  return true;
}

//==============================================================================

//==============================================================================
//==============================================================================

template<typename V>
bool
test_new_vector_section_space(fiber_bundles_namespace& xns, int xd)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:


  print_header("test_new_vector_section_space");

  //============================================================================

  typedef sec_at0 S;

  cout << "V::static_class_name() = " << V::static_class_name() << endl;
  cout << "S::static_class_name() = " << S::static_class_name() << endl;

  //============================================================================

  // Make names for the spaces:

  string lnames[3] = {"base_space",
                      "scalar_section_space",
                      "vector_section_space"};

  make_names_unique(lnames, 3);
  
  const string& lbase_space_name  = lnames[0];
  const string& lscalar_section_space_name   = lnames[1];
  const string& lvector_section_space_name   = lnames[2];

  //============================================================================

  // Make a base space.

  poset_path lbase_path = make_base_space(xns, lbase_space_name, xd);

  cout << "lbase_path = " << lbase_path << endl;
  cout << endl;

  //============================================================================

  // Create the section space schema.

  poset_path lscalar_space_schema_path =
    make_scalar_section_space_schema<S>(xns, lbase_path, lscalar_section_space_name);

  cout << "lscalar_space_schema_path = " << lscalar_space_schema_path << endl;
  cout << endl;

  //============================================================================

  // Create the section space.

  poset_path lscalar_section_space_path =
    make_scalar_section_space<S>(xns,
                                 lbase_path,
                                 lscalar_space_schema_path,
                                 lscalar_section_space_name);

  cout << "lscalar_section_space_path = " << lscalar_section_space_path << endl;
  cout << endl;

  //============================================================================

  // Create the vector space schema.

  poset_path lvector_space_schema_path =
    make_vector_section_space_schema<V>(xns,
                                        lbase_path,
                                        lvector_section_space_name);

  cout << "lvector_space_schema_path = " << lvector_space_schema_path << endl;
  cout << endl;

  //============================================================================

  // Create the vector space.

  poset_path lvector_section_space_path =
    make_vector_section_space<V>(xns,
                                 lbase_path,
                                 lscalar_space_schema_path,
                                 lscalar_section_space_path,
                                 lvector_space_schema_path,
                                 lvector_section_space_name);

  cout << "lvector_section_space_path = " << lvector_section_space_path << endl;
  cout << endl;

  //============================================================================

  // Postconditions:

  // Exit:

  return true;
}


//==============================================================================
//==============================================================================

template<typename V>
bool
test_new_vector_section_space_xx(fiber_bundles_namespace& xns, int xd)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("test_new_vector_section_space");

  //============================================================================

  typedef sec_at0 S;

  cout << "V::static_class_name() = " << V::static_class_name() << endl;

  //============================================================================

  // Make names for the spaces:

  string lnames[3] = {"base_space",
                      "scalar_section_space",
                      "vector_section_space"};

  make_names_unique(lnames, 3);
  
  const string& lbase_space_name             = lnames[0];
  const string& lscalar_section_space_name   = lnames[1];
  const string& lvector_section_space_name   = lnames[2];

  //============================================================================

  // Make a base space.

  poset_path lbase_path = make_base_space(xns, lbase_space_name, xd);

  cout << "lbase_path = " << lbase_path << endl;
  cout << endl;

  //============================================================================

  // Create the section space schema.

  poset_path lscalar_space_schema_path =
    make_scalar_section_space_schema<S>(xns, lbase_path, lscalar_section_space_name);

  cout << "lscalar_space_schema_path = " << lscalar_space_schema_path << endl;
  cout << endl;

  //============================================================================

  // Create the section space.

  poset_path lscalar_section_space_path =
    make_scalar_section_space<S>(xns,
                                 lbase_path,
                                 lscalar_space_schema_path,
                                 lscalar_section_space_name);

  cout << "lscalar_section_space_path = " << lscalar_section_space_path << endl;
  cout << endl;

  //============================================================================

  // Create the vector space schema.

  poset_path lvector_space_schema_path =
    make_vector_section_space_schema<sec_e1>(xns,
                                        lbase_path,
                                        lvector_section_space_name);

  cout << "lvector_space_schema_path = " << lvector_space_schema_path << endl;
  cout << endl;

  //============================================================================

  // Create the vector space.

  poset_path lvector_section_space_path =
    make_vector_section_space<V>(xns,
                                 lbase_path,
                                 lscalar_space_schema_path,
                                 lscalar_section_space_path,
                                 lvector_space_schema_path,
                                 lvector_section_space_name);

  cout << "lvector_section_space_path = " << lvector_section_space_path << endl;
  cout << endl;

  //============================================================================

  // Postconditions:

  // Exit:

  return true;
}


//==============================================================================


template<typename T>
bool
test_new_tensor_section_space(fiber_bundles_namespace& xns, int xd)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  print_header("test_new_tensor_section_space");

  //============================================================================

  typedef sec_at0 S;
  typedef typename T::vector_space_type V;

  cout << "T::static_class_name() = " << T::static_class_name() << endl;
  cout << "V::static_class_name() = " << V::static_class_name() << endl;
  cout << "S::static_class_name() = " << S::static_class_name() << endl;

  //============================================================================

  // Make names for the spaces:

  string lnames[4] = {"base_space",
                      "scalar_section_space",
                      "vector_section_space",
                      "tensor_section_space"};

  make_names_unique(lnames, 4);
  
  const string& lbase_space_name           = lnames[0];
  const string& lscalar_section_space_name = lnames[1];
  const string& lvector_section_space_name = lnames[2];
  const string& ltensor_section_space_name = lnames[3];

  //============================================================================

  // Make a base space.

  poset_path lbase_path = make_base_space(xns, lbase_space_name, xd);

  cout << "lbase_path = " << lbase_path << endl;
  cout << endl;

  //============================================================================

  // Create the section space schema.

  poset_path lscalar_space_schema_path =
    make_scalar_section_space_schema<S>(xns, lbase_path, lscalar_section_space_name);

  cout << "lscalar_space_schema_path = " << lscalar_space_schema_path << endl;
  cout << endl;

  //============================================================================

  // Create the section space.

  poset_path lscalar_section_space_path =
    make_scalar_section_space<S>(xns,
                                 lbase_path,
                                 lscalar_space_schema_path,
                                 lscalar_section_space_name);

  cout << "lscalar_section_space_path = " << lscalar_section_space_path << endl;
  cout << endl;

  //============================================================================

  // Create the vector space schema.

  poset_path lvector_space_schema_path =
    make_vector_section_space_schema<V>(xns,
                                        lbase_path,
                                        lvector_section_space_name);

  cout << "lvector_space_schema_path = " << lvector_space_schema_path << endl;
  cout << endl;

  //============================================================================

  // Create the vector space.

  poset_path lvector_section_space_path =
    make_vector_section_space<V>(xns,
                                 lbase_path,
                                 lscalar_space_schema_path,
                                 lscalar_section_space_path,
                                 lvector_space_schema_path,
                                 lvector_section_space_name);

  cout << "lvector_section_space_path = " << lvector_section_space_path << endl;
  cout << endl;

  //============================================================================

  // Create the tensor space schema.

  poset_path ltensor_space_schema_path =
    make_tensor_section_space_schema<T>(xns,
                                        lbase_path,
                                        ltensor_section_space_name);

  cout << "ltensor_space_schema_path = " << ltensor_space_schema_path << endl;
  cout << endl;

  //============================================================================

  // Create the tensor space.

  poset_path ltensor_section_space_path =
    make_tensor_section_space<T>(xns,
                                 lbase_path,
                                 lscalar_space_schema_path,
                                 lscalar_section_space_path,
                                 lvector_space_schema_path,
                                 lvector_section_space_path,
                                 ltensor_space_schema_path,
                                 ltensor_section_space_name);

  cout << "ltensor_section_space_path = " << ltensor_section_space_path << endl;
  cout << endl;

  //============================================================================

  // Postconditions:

  // Exit:

  return true;
}


// template<typename T>
// bool
// test_new_tensor_section_space_xx(fiber_bundles_namespace& xns, int xd)
// {
//   // Preconditions:

//   require(xns.state_is_read_write_accessible());

//   // Body:

//   print_header("test_new_tensor_section_space");

//   //============================================================================

//   typedef sec_at0 S;
//   typedef typename T::vector_space_type V;

//   cout << "T::static_class_name() = " << T::static_class_name() << endl;
//   cout << "V::static_class_name() = " << V::static_class_name() << endl;
//   cout << "S::static_class_name() = " << S::static_class_name() << endl;

//   //============================================================================

//   // Make names for the spaces:

//   string lnames[4] = {"base_space",
//                       "scalar_section_space",
//                       "vector_section_space",
//                       "tensor_section_space"};

//   make_names_unique(lnames, 4);
  
//   const string& lbase_space_name           = lnames[0];
//   const string& lscalar_section_space_name = lnames[1];
//   const string& lvector_section_space_name = lnames[2];
//   const string& ltensor_section_space_name = lnames[3];

//   //============================================================================

//   // Make a base space.

//   poset_path lbase_path;
//   if(xd == 1)
//   {
//     lbase_path = make_base_space_1d(xns, lbase_space_name);
//   }
//   else if (xd == 2)
//   {
//     lbase_path = make_base_space_2d(xns, lbase_space_name);
//   }
//   else
//   {
//     lbase_path = make_base_space_3d(xns, lbase_space_name);
//   }

//   cout << "lbase_path = " << lbase_path << endl;
//   cout << endl;

//   //============================================================================

//   // Create the section space schema.

//   poset_path lscalar_space_schema_path =
//     make_scalar_section_space_schema<S>(xns, lbase_path, lscalar_section_space_name);

//   cout << "lscalar_space_schema_path = " << lscalar_space_schema_path << endl;
//   cout << endl;

//   //============================================================================

//   // Create the section space.

//   poset_path lscalar_section_space_path =
//     make_scalar_section_space<S>(xns,
//                                  lbase_path,
//                                  lscalar_space_schema_path,
//                                  lscalar_section_space_name);

//   cout << "lscalar_section_space_path = " << lscalar_section_space_path << endl;
//   cout << endl;

//   //============================================================================

//   // Create the vector space schema.

//   poset_path lvector_space_schema_path =
//     make_vector_section_space_schema<V>(xns,
//                                         lbase_path,
//                                         lvector_section_space_name);

//   cout << "lvector_space_schema_path = " << lvector_space_schema_path << endl;
//   cout << endl;

//   //============================================================================

//   // Create the vector space.

//   poset_path lvector_section_space_path =
//     //make_vector_section_space<V>(xns,
//     make_vector_section_space<sec_e2>(xns,
//                                  lbase_path,
//                                  lscalar_space_schema_path,
//                                  lscalar_section_space_path,
//                                  lvector_space_schema_path,
//                                  lvector_section_space_name);

//   cout << "lvector_section_space_path = " << lvector_section_space_path << endl;
//   cout << endl;

//   //============================================================================

//   // Create the tensor space schema.

//   poset_path ltensor_space_schema_path =
//     make_tensor_section_space_schema<T>(xns,
//                                         lbase_path,
//                                         ltensor_section_space_name);

//   cout << "ltensor_space_schema_path = " << ltensor_space_schema_path << endl;
//   cout << endl;

//   //============================================================================

//   // Create the tensor space.

//   poset_path ltensor_section_space_path =
//     make_tensor_section_space<T>(xns,
//                                  lbase_path,
//                                  lscalar_space_schema_path,
//                                  lscalar_section_space_path,
//                                  lvector_space_schema_path,
//                                  lvector_section_space_path,
//                                  ltensor_space_schema_path,
//                                  ltensor_section_space_name);

//   cout << "ltensor_section_space_path = " << ltensor_section_space_path << endl;
//   cout << endl;

//   //============================================================================

//   // Postconditions:

//   // Exit:

//   return true;
// }


//==============================================================================


} //end unnamed namespace

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing fiber_bundles_namespace instantiations.");

  bool ltest = true;

  cout << "Begin creating namespace..." << endl;

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  cout << "Finished creating namespace." << endl;

  //#define SKIP
#ifndef SKIP

  //============================================================================

  // Commented out function for new_fiber_spaces, etc. have trailing comments to
  // indicate the failure message (not location though).  Probably should not
  // invoke these for the types (eg: at2), but you can try!

  lns.new_fiber_space<at0>();
  lns.new_fiber_space<at1>();

  ////lns.new_fiber_space<at2>(); //xi >= xj

  lns.new_fiber_space<at2_e2>();
  lns.new_fiber_space<at2_e3>();

  ////lns.new_fiber_space<at3>(); //xi >= xj

  lns.new_fiber_space<at3_e3>();

  ////lns.new_fiber_space<atp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0

  lns.new_fiber_space<e1>();
  lns.new_fiber_space<e2>();
  lns.new_fiber_space<e3>();
  lns.new_fiber_space<e4>();
  lns.new_fiber_space<ed>();
  lns.new_fiber_space<gl2>();
  lns.new_fiber_space<gl3>();
  lns.new_fiber_space<gln>();
  lns.new_fiber_space<jcb_e13>();
  lns.new_fiber_space<jcb_e23>();
  lns.new_fiber_space<jcb_e33>();
  lns.new_fiber_space<jcb_ed>();
  lns.new_fiber_space<jcb>();
  lns.new_fiber_space<met_e1>();
  lns.new_fiber_space<met_e2>();
  lns.new_fiber_space<met_e3>();

  ////lns.new_fiber_space<met_ed>(); //xi >= xj'
  ////lns.new_fiber_space<met>();    //xi >= xj'

  lns.new_fiber_space<st2_e2>();
  lns.new_fiber_space<st2_e3>();

  ////lns.new_fiber_space<st2>(); //xi >= xj'

  lns.new_fiber_space<st3_e3>();

  ////lns.new_fiber_space<st3>(); //xi >= xj'

  lns.new_fiber_space<st4_e2>();
  lns.new_fiber_space<st4_e3>();

  ////lns.new_fiber_space<st4>(); //xi >= xj'
  ////lns.new_fiber_space<stp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0

  lns.new_fiber_space<t2_e2>();
  lns.new_fiber_space<t2_e3>();
  lns.new_fiber_space<t2>();
  lns.new_fiber_space<t3_e3>();
  lns.new_fiber_space<t3>();
  lns.new_fiber_space<t4_e2>();
  lns.new_fiber_space<t4_e3>();
  lns.new_fiber_space<t4>();

  ////lns.new_fiber_space<tp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0

  lns.new_fiber_space<tuple>();
  lns.new_fiber_space<vd>();

  //============================================================================

  lns.new_scalar_space<at0>();

  //============================================================================

  lns.new_vector_space<at1>();
  lns.new_vector_space<e1>();
  lns.new_vector_space<e2>();
  lns.new_vector_space<e3>();
  lns.new_vector_space<e4>();
  lns.new_vector_space<ed>();

  //============================================================================

  ////lns.new_tensor_space<at2>(); //xi >= xj

  lns.new_tensor_space<at2_e2>();
  lns.new_tensor_space<at2_e3>();

  ////lns.new_tensor_space<at3>(); //xi >= xj

  lns.new_tensor_space<at3_e3>();

  ////lns.new_tensor_space<atp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0

  lns.new_tensor_space<met_e1>();
  lns.new_tensor_space<met_e2>();
  lns.new_tensor_space<met_e3>();

  ////lns.new_tensor_space<met_ed>(); //xi >= xj
  ////lns.new_tensor_space<met>();    //xi >= xj

  lns.new_tensor_space<st2_e2>();
  lns.new_tensor_space<st2_e3>();

  ////lns.new_tensor_space<st2>();   //xi >= xj

  lns.new_tensor_space<st3_e3>();

  ////lns.new_tensor_space<st3>();   //xi >= xj

  lns.new_tensor_space<st4_e2>();
  lns.new_tensor_space<st4_e3>();

  ////lns.new_tensor_space<st4>();; //xi >= xj
  ////lns.new_tensor_space<stp>();  //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0

  lns.new_tensor_space<t2_e2>();
  lns.new_tensor_space<t2_e3>();
  lns.new_tensor_space<t2>();
  lns.new_tensor_space<t3_e3>();
  lns.new_tensor_space<t3>();
  lns.new_tensor_space<t4_e2>();
  lns.new_tensor_space<t4_e3>();
  lns.new_tensor_space<t4>();

  ////lns.new_tensor_space<tp>(); //completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0

  //============================================================================

  lns.new_group_space<gl2>();
  lns.new_group_space<gl3>();
  lns.new_group_space<gln>();

  lns.new_jacobian_space<jcb_e13>();
  lns.new_jacobian_space<jcb_e23>();
  lns.new_jacobian_space<jcb_e33>();
  lns.new_jacobian_space<jcb_ed>();
  lns.new_jacobian_space<jcb>();

  //============================================================================


//   test_fiber_bundles_namespace_facet_1d<sec_at0, structured_block_1d>(lns);
//   test_fiber_bundles_namespace_facet_1d<sec_e1, structured_block_1d>(lns);
//   test_fiber_bundles_namespace_facet_1d<sec_e1_uniform, structured_block_1d>(lns);
//   test_fiber_bundles_namespace_facet_1d<sec_met_e1, structured_block_1d>(lns);

//   ////

//   test_fiber_bundles_namespace_facet_2d<sec_at0, structured_block_2d>(lns);
//   test_fiber_bundles_namespace_facet_2d<sec_at2_e2, structured_block_2d>(lns);
//   test_fiber_bundles_namespace_facet_2d<sec_st2_e2, structured_block_2d>(lns);
//   test_fiber_bundles_namespace_facet_2d<sec_st4_e2, structured_block_2d>(lns);
//   test_fiber_bundles_namespace_facet_2d<sec_t2_e2, structured_block_2d>(lns);
//   test_fiber_bundles_namespace_facet_2d<sec_t4_e2, structured_block_2d>(lns);
//   test_fiber_bundles_namespace_facet_2d<sec_e2, structured_block_2d>(lns);
//   test_fiber_bundles_namespace_facet_2d<sec_e2_uniform, structured_block_2d>(lns);
//   test_fiber_bundles_namespace_facet_2d<sec_met_e2, structured_block_2d>(lns);

//   ////

//   test_fiber_bundles_namespace_facet_3d<sec_at0, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_at2_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_at3_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_st2_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_st3_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_st4_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_t2_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_t3_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_t4_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_e3, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_e3_uniform, structured_block_3d>(lns);
//   test_fiber_bundles_namespace_facet_3d<sec_met_e3, structured_block_3d>(lns);


  //test_fiber_bundles_namespace_facet<sec_at1, structured_block_2d>(lns);
  //test_fiber_bundles_namespace_facet<sec_at2, structured_block_2d>(lns);
  //test_fiber_bundles_namespace_facet<sec_st2, structured_block_2d>(lns);
  //test_fiber_bundles_namespace_facet<sec_t2, structured_block_2d>(lns);

  //============================================================================

  // Section spaces

  test_new_section_space<sec_at0>(lns, 1);
  test_new_section_space<sec_e1>(lns, 1);
  test_new_section_space<sec_e1_uniform>(lns, 1);
  test_new_section_space<sec_met_e1>(lns, 1);

  test_new_section_space<sec_at0>(lns, 2);
  test_new_section_space<sec_at2_e2>(lns, 2);
  test_new_section_space<sec_st2_e2>(lns, 2);
  test_new_section_space<sec_st4_e2>(lns, 2);
  test_new_section_space<sec_t2_e2>(lns, 2);
  test_new_section_space<sec_t4_e2>(lns, 2);
  test_new_section_space<sec_e2>(lns, 2);
  test_new_section_space<sec_e2_uniform>(lns, 2);
  test_new_section_space<sec_met_e2>(lns, 2);

  test_new_section_space<sec_at0>(lns, 3);
  test_new_section_space<sec_at2_e3>(lns, 3);
  test_new_section_space<sec_at3_e3>(lns, 3);
  test_new_section_space<sec_st2_e3>(lns, 3);
  test_new_section_space<sec_st3_e3>(lns, 3);
  test_new_section_space<sec_st4_e3>(lns, 3);
  test_new_section_space<sec_t2_e3>(lns, 3);
  test_new_section_space<sec_t3_e3>(lns, 3);
  test_new_section_space<sec_t4_e3>(lns, 3);
  test_new_section_space<sec_e3>(lns, 3);
  test_new_section_space<sec_e3_uniform>(lns, 3);
  test_new_section_space<sec_met_e3>(lns, 3);

  //test_new_section_space<sec_at1>(lns, dd);
  //test_new_section_space<sec_at2>(lns, dd);
  //test_new_section_space<sec_st2>(lns, dd);
  //test_new_section_space<sec_t2>(lns, dd);

  //============================================================================

  // Scalar section spaces

  test_new_scalar_section_space<sec_at0>(lns, 1);
  test_new_scalar_section_space<sec_at0>(lns, 2);
  test_new_scalar_section_space<sec_at0>(lns, 3);

  //============================================================================

 // Vector section spaces

  test_new_vector_section_space<sec_e1>(lns, 1);
  test_new_vector_section_space<sec_e2>(lns, 1);
  test_new_vector_section_space<sec_e3>(lns, 1);
  test_new_vector_section_space<sec_e1_uniform>(lns, 1);
  test_new_vector_section_space<sec_e2_uniform>(lns, 1);
  test_new_vector_section_space<sec_e3_uniform>(lns, 1);

  test_new_vector_section_space<sec_e1>(lns, 2);
  test_new_vector_section_space<sec_e2>(lns, 2);
  test_new_vector_section_space<sec_e3>(lns, 2);
  test_new_vector_section_space<sec_e1_uniform>(lns, 2);
  test_new_vector_section_space<sec_e2_uniform>(lns, 2);
  test_new_vector_section_space<sec_e3_uniform>(lns, 2);

  test_new_vector_section_space<sec_e1>(lns, 3);
  test_new_vector_section_space<sec_e2>(lns, 3);
  test_new_vector_section_space<sec_e3>(lns, 3);
  test_new_vector_section_space<sec_e1_uniform>(lns, 3);
  test_new_vector_section_space<sec_e2_uniform>(lns, 3);
  test_new_vector_section_space<sec_e3_uniform>(lns, 3);

  test_new_vector_section_space<sec_e4>(lns, 1);
  test_new_vector_section_space<sec_e4>(lns, 2);
  test_new_vector_section_space<sec_e4>(lns, 3);


  test_new_vector_section_space_xx<sec_ed>(lns, 1);  // df() > 0'
  test_new_vector_section_space_xx<sec_at1>(lns, 1); // df() > 0'
  //test_new_vector_section_space_xx<sec_vd>(lns, 1);  // df() > 0'

  test_new_vector_section_space_xx<sec_ed>(lns, 2);  // df() > 0'
  test_new_vector_section_space_xx<sec_at1>(lns, 2); // df() > 0'
  //test_new_vector_section_space_xx<sec_vd>(lns, 2);  // df() > 0'

  test_new_vector_section_space_xx<sec_ed>(lns, 3);  // df() > 0'
  test_new_vector_section_space_xx<sec_at1>(lns, 3); // df() > 0'
  //test_new_vector_section_space_xx<sec_vd>(lns, 3);  // df() > 0'


  //============================================================================
  //============================================================================

  // Tensor section spaces

  test_new_tensor_section_space<sec_at2_e2>(lns, 2);
  test_new_tensor_section_space<sec_at2_e3>(lns, 3);
  test_new_tensor_section_space<sec_at3_e3>(lns, 3);

  test_new_tensor_section_space<sec_st2_e2>(lns, 2);
  test_new_tensor_section_space<sec_st2_e3>(lns, 3);
  test_new_tensor_section_space<sec_st3_e3>(lns, 3);
  test_new_tensor_section_space<sec_st4_e2>(lns, 2);
  test_new_tensor_section_space<sec_st4_e3>(lns, 3);

  test_new_tensor_section_space<sec_t2_e2>(lns, 2);
  test_new_tensor_section_space<sec_t2_e3>(lns, 3);
  test_new_tensor_section_space<sec_t3_e3>(lns, 3);
  test_new_tensor_section_space<sec_t4_e2>(lns, 2);
  test_new_tensor_section_space<sec_t4_e3>(lns, 3);

  test_new_tensor_section_space<sec_met_e1>(lns, 1);
  test_new_tensor_section_space<sec_met_e2>(lns, 2);
  test_new_tensor_section_space<sec_met_e3>(lns, 3);

#endif // SKIP

  //test_new_tensor_section_space_xx<sec_at2>(lns, 2); // df() >0
  //test_new_tensor_section_space_xx<sec_met_ed>(lns, 2); // df() >0

// sec_atp
// sec_at2
// sec_at2_e2
// sec_at2_e3
// sec_at3_e3

// sec_stp
// sec_st2
// sec_st3
// sec_st4
// sec_st2_e2
// sec_st2_e3
// sec_st3_e3
// sec_st4_e2
// sec_st4_e3

// sec_tp
// sec_t2
// sec_t3
// sec_t4
// sec_t2_e2
// sec_t2_e3
// sec_t3_e3
// sec_t4_e2
// sec_t4_e3

// sec_met
// sec_met_ed
// sec_met_e1
// sec_met_e2
// sec_met_e3

  //============================================================================
  //============================================================================

  // These return poset_path:
  // All of these tests fail with roughly the same error message:

  // For example:
  // terminate called after throwing an instance of 'std::logic_error'
  //   what():  '(xsection_space_schema_path.full() &&
  // contains_path<section_space_schema_poset>(xsection_space_schema_path, xauto_access)) ||
  // xbase_space_path.full() ||
  // (xsection_space_schema_args.contains_arg("base_space_path") &&
  // poset_path(xsection_space_schema_args.value("base_space_path")).full())'
  // in file fiber_bundles_namespace.cc at line 793

//   // Create a base space poset for 2d structured blocks.

//   poset_path lbase_path("test_base_space");
//   base_space_poset& lbase = lns.new_base_space<structured_block_2d>(lbase_path);

//   // Create a block; has to have a name to use as a base space for a section space.

//   structured_block_2d lblock(&lbase, 2, 2);
//   lblock.put_name("2d_block", true, true);  

//   // Create a name for the section space.

//   poset_path lsec_space_path("test_section_space_at0_on_2d_block");

//   // Create the section space.

//   lns.new_section_space<sec_at0>(lsec_space_path, lblock.path());
  
  // If trying to make a section space schema directly,
  // have to specify a base space one way or another,
  // here we'll use the explicit base space arg.

  //lns.new_section_space_schema<sec_at0>("", "", "", "", lblock.path());

  ////lns.new_section_space_schema<sec_at1>();
  ////lns.new_section_space_schema<sec_at2>();
  ////lns.new_section_space_schema<sec_at2_e2>();
  ////lns.new_section_space_schema<sec_at2_e3>();
  ////lns.new_section_space_schema<sec_at3>();
  ////lns.new_section_space_schema<sec_at3_e3>();
  ////lns.new_section_space_schema<sec_atp>();
  ////lns.new_section_space_schema<sec_e1>();
  ////lns.new_section_space_schema<sec_e1_uniform>();
  ////lns.new_section_space_schema<sec_e2>();
  ////lns.new_section_space_schema<sec_e2_uniform>();
  ////lns.new_section_space_schema<sec_e3>();
  ////lns.new_section_space_schema<sec_e3_uniform>();
  ////lns.new_section_space_schema<sec_e4>();
  ////lns.new_section_space_schema<sec_ed>();


  ////lns.new_section_space_schema<sec_met>();
  ////lns.new_section_space_schema<sec_met_e1>();
  ////lns.new_section_space_schema<sec_met_e2>();
  ////lns.new_section_space_schema<sec_met_e3>();
  ////lns.new_section_space_schema<sec_met_ed>();
  ////lns.new_section_space_schema<sec_st2>();

  ////lns.new_section_space_schema<sec_st2_e2>();
  ////lns.new_section_space_schema<sec_st2_e3>();
  ////lns.new_section_space_schema<sec_st3>();
  ////lns.new_section_space_schema<sec_st3_e3>();
  ////lns.new_section_space_schema<sec_st4>();
  ////lns.new_section_space_schema<sec_st4_e2>();
  ////lns.new_section_space_schema<sec_st4_e3>();
  ////lns.new_section_space_schema<sec_stp>();
  ////lns.new_section_space_schema<sec_t2>();
  ////lns.new_section_space_schema<sec_t2_e2>();
  ////lns.new_section_space_schema<sec_t2_e3>();
  ////lns.new_section_space_schema<sec_t3>();
  ////lns.new_section_space_schema<sec_t3_e3>();
  ////lns.new_section_space_schema<sec_t4>();
  ////lns.new_section_space_schema<sec_t4_e2>();
  ////lns.new_section_space_schema<sec_t4_e3>();
  ////lns.new_section_space_schema<sec_tp>();

  //============================================================================

  ////lns.new_scalar_section_space_schema<sec_at0>();

  //============================================================================

  ////lns.new_vector_section_space_schema<sec_at1>();
  ////lns.new_vector_section_space_schema<sec_e1>();
  ////lns.new_vector_section_space_schema<sec_e1_uniform>();
  ////lns.new_vector_section_space_schema<sec_e2>();
  ////lns.new_vector_section_space_schema<sec_e2_uniform>();
  ////lns.new_vector_section_space_schema<sec_e3>();
  ////lns.new_vector_section_space_schema<sec_e3_uniform>();
  ////lns.new_vector_section_space_schema<sec_e4>();
  ////lns.new_vector_section_space_schema<sec_ed>();
  ////lns.new_vector_section_space_schema<sec_vd>();

  //============================================================================

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing fiber_bundles_namespace instantiations.");


  // Postconditions:

  // Exit:

  return lresult;
}

