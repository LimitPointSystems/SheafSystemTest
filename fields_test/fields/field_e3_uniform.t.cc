
// $RCSfile: field_e3_uniform.t.cc,v $ $Revision: 1.7 $ $Date: 2012/03/01 00:41:03 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example fields/fields/field_e3_uniform.t.cc
/// Unit test for class field_e3_uniform.

#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "field_e3_uniform.h"
#include "std_iostream.h"
#include "wsv_block.h"

using namespace fields;

int main(int argc, char* argv[])
{
//   size_t edge_ct_x = 2;
//   if (argc > 1)
//     edge_ct_x = atoi(argv[1]);

//   size_t edge_ct_y = 3;
//   if (argc > 2)
//     edge_ct_y = atoi(argv[2]);

//   size_t edge_ct_z = 4;
//   if (argc > 3)
//     edge_ct_z = atoi(argv[3]);

//   fiber_bundles_namespace llns("field_e3_uniform.t.hdf");

//   wsv_block<field_vd_dof_type> llower("-2.0 -3.0 -4.0");
//   wsv_block<field_vd_dof_type> lupper("2.0 3.0 4.0");

//   field_rep_space* lhost =
//     field_e3_uniform::new_host(lns, "3d_mesh", edge_ct_x, edge_ct_y, edge_ct_z, true);

//   field_e3_uniform lcoords(lhost, llower, lupper, true);
//   lcoords.put_name("uniform_coordinates", true, true);

//   lns.get_read_access();
//   cout << lns << endl;

//   // Clean-up

//   lns.get_read_write_access(true);
//   lcoords.detach_from_state();

  return 0;
}
