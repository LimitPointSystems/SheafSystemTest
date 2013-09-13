
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

// Unit test driver for template class base_space_factory.

#include "base_space_factory.impl.h"
#include "hex_connectivity.h" 
#include "line_connectivity.h" 
#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "quad_connectivity.h" 
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "tetra_connectivity.h" 
#include "triangle_connectivity.h" 
#include "unstructured_block.h"
#include "zone_nodes_block.h"

#include "fiber_bundles_namespace.h"
#include "test_utils.h"

using namespace fiber_bundle;

namespace
{

  ///
  ///  Common "protected" code.
  ///
  template<typename T>
  bool
  test_base_space_factory(fiber_bundles_namespace& xns,
                          const string& xhost_name,
                          const poset_path& xbase_host_path)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());
    require(!xhost_name.empty());
    require(xns.contains_poset(xhost_name));

    // Body:

    bool lresult = true;

    //==========================================================================

    base_space_factory<T> lfac;
    lfac.path = xbase_host_path;

    base_space_poset* lnew_space = lfac.new_space(xns);

    T* lnew_base = lfac.new_base(xns, string("mesh"));

    cout << "lnew_base->path() = " << lnew_base->path() << endl;

    T* lnew_base2 = lfac.new_base(xns, lnew_base->path());

    //const string lname9 = (lnew_base->path()).poset_name();
    //T* lnew_base9 = lfac.new_base(xns, lname9);

   //===========================================================================

    base_space_factory<T> lfac3;
    string lname3 = xhost_name +"xxx";
    poset_path lpath3(lname3);
    lfac3.path = lpath3;
    lfac3.index_ubs = "1 2 3";

    base_space_poset* lnew_space3 = lfac3.new_space(xns);

   //===========================================================================

    base_space_factory<T>* lfac2 = new base_space_factory<T>();

    delete lfac2;

   //===========================================================================

    // Postconditions:

    // Exit:

    return lresult;
  }


  template<typename T>
  bool
  test_base_space_factory_1d(fiber_bundles_namespace& xns,
                            const string& xhost_name)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());
    require(!xhost_name.empty());
    require(!xns.contains_poset(xhost_name));
    //require(T::DB == 1);

    // Body:

    bool lresult = true;

    //==========================================================================

    // Create a host poset for the mesh.

    base_space_poset& lbase_host = T::standard_host(xns, xhost_name, false);

    lbase_host.get_read_write_access();

    // Create the mesh.

    T* lmesh = new T(&lbase_host, 4, true);

    lmesh->put_name("mesh", true, false);

    cout << "lbase_host.path() = " << lbase_host.path() << endl;

 
    lresult &= test_base_space_factory<T>(xns, xhost_name, lbase_host.path());

    //==========================================================================

    // Postconditions:

    // Exit:

    return lresult;
  }

  template<typename T>
  bool
  test_base_space_factory_2d(fiber_bundles_namespace& xns,
                             const string& xhost_name)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());
    require(!xhost_name.empty());
    require(!xns.contains_poset(xhost_name));
    //require(T::DB == 2);

    // Body:

    bool lresult = true;

    //==========================================================================

    // Create a host poset for the mesh.

    base_space_poset& lbase_host = T::standard_host(xns, xhost_name, false);

    lbase_host.get_read_write_access();

    // Create the mesh.

    T* lmesh = new T(&lbase_host, 4, 4, true);

    lmesh->put_name("mesh", true, false);

    cout << "lbase_host.path() = " << lbase_host.path() << endl;


    lresult &= test_base_space_factory<T>(xns, xhost_name, lbase_host.path());

    //==========================================================================


    // Postconditions:

    // Exit:

    return lresult;
  }


  template<typename T>
  bool
  test_base_space_factory_3d(fiber_bundles_namespace& xns,
                             const string& xhost_name)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());
    require(!xhost_name.empty());
    require(!xns.contains_poset(xhost_name));
    //require(T::DB == 3);

    // Body:

    bool lresult = true;

    //==========================================================================

    // Create a host poset for the mesh.

    base_space_poset& lbase_host = T::standard_host(xns, xhost_name, false);

    lbase_host.get_read_write_access();

    // Create the mesh.

    T* lmesh = new T(&lbase_host, 4, 4, 4, true);

    lmesh->put_name("mesh", true, false);

    cout << "lbase_host.path() = " << lbase_host.path() << endl;

    lresult &= test_base_space_factory<T>(xns, xhost_name, lbase_host.path());

   //==========================================================================

    // Postconditions:

    // Exit:

    return lresult;
  }

  //============================================================================
  // SPECIALIZATION FOR UNSTRUCTURED_BLOCK
  //============================================================================

  template<>
  bool
  test_base_space_factory_2d<unstructured_block>(fiber_bundles_namespace& xns,
                                                 const string& xhost_name)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());
    require(!xhost_name.empty());
    require(!xns.contains_poset(xhost_name));

    // Body:

    bool lresult = true;

    //==========================================================================

    typedef unstructured_block T;

    // Create a host poset for the mesh.

    base_space_poset& lbase_host = T::standard_host(xns, xhost_name, 2, false);

    lbase_host.get_read_write_access();

    cout << "lbase_host.path() = " << lbase_host.path() << endl;
 
     // Create the mesh and give it a name

    unstructured_block lmesh(&lbase_host,
                             "base_space_member_prototypes/triangle_nodes",
                              2, 2, true);

    lmesh.put_name("mesh", true, false);


    lresult &= test_base_space_factory<T>(xns, xhost_name, lbase_host.path());

    //==========================================================================

    // Postconditions:

    // Exit:

    return lresult;
  }

  //============================================================================
  // SPECIALIZATION FOR ZONE_NODES_BLOCK
  //============================================================================

  template<>
  bool
  test_base_space_factory_2d<zone_nodes_block>(fiber_bundles_namespace& xns,
                                               const string& xhost_name)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());
    require(!xhost_name.empty());
    require(!xns.contains_poset(xhost_name));

    // Body:

    bool lresult = true;

    //==========================================================================

    typedef zone_nodes_block T;

    // Create a host poset for the mesh.

    base_space_poset& lbase_host = T::standard_host(xns, xhost_name, 2, false);

    lbase_host.get_read_write_access();

    cout << "lbase_host.path() = " << lbase_host.path() << endl;
 
     // Create the mesh and give it a name

    // Make quad connectivity.

    quad_connectivity lconn(4, 4);

    // Make quad block.

    zone_nodes_block lblock(lbase_host, lconn, true);
    lblock.put_name("mesh", true, false);


    lresult &= test_base_space_factory<T>(xns, xhost_name, lbase_host.path());


    lblock.detach_from_state();
//     lmesh->release_access();

    //==========================================================================

    // Postconditions:

    // Exit:

    return lresult;
  }

} //end namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing base_space_factory");

  //============================================================================

  fiber_bundles_namespace lns("test_namespace");
  lns.get_read_write_access();

  bool ltest = true;

  print_header("Testing base_space_factory<structured_block_1d>");
  ltest &= test_base_space_factory_1d<structured_block_1d>(lns, "my_structured_block_1d");

  print_header("Testing base_space_factory<structured_block_2d>");
  ltest &= test_base_space_factory_2d<structured_block_2d>(lns, "my_structured_block_2d");

  print_header("Testing base_space_factory<structured_block_3d>");
  ltest &= test_base_space_factory_3d<structured_block_3d>(lns, "my_structured_block_3d");

  print_header("Testing base_space_factory<point_block_1d>");
  ltest &= test_base_space_factory_1d<point_block_1d>(lns, "my_point_block_1d");

  print_header("Testing base_space_factory<point_block_2d>");
  ltest &= test_base_space_factory_2d<point_block_2d>(lns, "my_point_block_2d");

  print_header("Testing base_space_factory<point_block_3d>");
  ltest &= test_base_space_factory_3d<point_block_3d>(lns, "my_point_block_3d");

  print_header("Testing base_space_factory<zone_nodes_block>");
  ltest &= test_base_space_factory_2d<zone_nodes_block>(lns, "my_zone_nodes_block");

  // Obsolete?
  print_header("Testing base_space_factory<unstructured_block>");
  ltest &= test_base_space_factory_2d<unstructured_block>(lns, "my_unstructured_block");
  
  //============================================================================

  print_footer("End testing base_space_factory");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
 
//==============================================================================
//==============================================================================




