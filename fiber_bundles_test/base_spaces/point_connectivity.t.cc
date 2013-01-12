
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example base_spaces/point_connectivity.t.cc
/// Test case for class point_connectivity

#include "point_connectivity.h"
#include "std_iostream.h"

using namespace fiber_bundle;

int main()
{

  point_connectivity c(5);

  cout << c << endl;

  cout << "c.node_id_ct() = " << c.node_id_ct() << endl;

  point_connectivity c1;

  cout << c1 << endl;

  cout << "c1.node_id_ct() = " << c1.node_id_ct() << endl;

  point_connectivity c2(5,1);

  cout << c2 << endl;

  cout << "c2.node_id_ct() = " << c2.node_id_ct() << endl;


  return 0;

}
