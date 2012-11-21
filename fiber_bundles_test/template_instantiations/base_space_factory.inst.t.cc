// $RCSfile: base_space_factory.inst.t.cc,v $ $Revision: 1.15 $ $Date: 2012/07/04 16:42:07 $

// $Name: unit-test-0 $
//
// Copyright (c) 2012 Limit Point Systems, Inc.
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
  template<typename T>
  bool
  test_base_space_factory(fiber_bundles_namespace& xns,
                          const string& xhost_name)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());

    // Body:

    //================================================================


  base_space_poset* lbase_host =
    &xns.new_base_space<T>(xhost_name);

  lbase_host->get_read_write_access();

  // Create the mesh itself.

  T* result = new T(lbase_host, 4, true); // Need variable args.
  //T* result = new T(lbase_host);
  result->put_name("mesh", true, false);

  cout << "lbase_host->path() = " << lbase_host->path() << endl;

    //================================================================

    base_space_factory<T> lfac;
    lfac.path = lbase_host->path();

    base_space_poset* lnew_space = lfac.new_space(xns);

    T* lnew_base = lfac.new_base(xns, string("mesh"));

    cout << "lnew_base->path() = " << lnew_base->path() << endl;

    T* lnew_base2 = lfac.new_base(xns, lnew_base->path());

    // Postconditions:

    // Exit:

    //return lresult;
    return true;
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

  ltest &= test_base_space_factory<structured_block_1d>(lns, "my_structured_block_1d");
//   ltest &= test_base_space_factory<structured_block_2d>(lns, "my_structured_block_2d");
//   ltest &= test_base_space_factory<structured_block_3d>(lns, "my_structured_block_3d");

//   ltest &= test_base_space_factory<point_block_1d>(lns, "my_point_block_1d");
//   ltest &= test_base_space_factory<point_block_2d>(lns, "my_point_block_2d");
//   ltest &= test_base_space_factory<point_block_3d>(lns, "my_point_block_3d");

//   ltest &= test_base_space_factory<zone_nodes_block>(lns, "my_zone_nodes_block");
//   ltest &= test_base_space_factory<unstructured_block>(lns, "my_unstructured_block");
  
  //============================================================================

  print_footer("End testing base_space_factory");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
 
//==============================================================================
//==============================================================================




