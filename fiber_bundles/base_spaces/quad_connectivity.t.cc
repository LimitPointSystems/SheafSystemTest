// $RCSfile: quad_connectivity.t.cc,v $ $Revision: 1.11 $ $Date: 2012/03/01 00:40:31 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example base_spaces/quad_connectivity.t.cc
/// Test case for class quad_connectivity

#include "quad_connectivity.h"
#include "std_iostream.h"

using namespace fiber_bundle;

int main()
{

  quad_connectivity c(2, 3);

  cout << c << endl;

  cout << "c.node_id_ct() = " << c.node_id_ct() << endl;

  quad_connectivity c1;

  cout << c1 << endl;

  cout << "c1.node_id_ct() = " << c1.node_id_ct() << endl;

  quad_connectivity c2(4, 2, 1);

  cout << c2 << endl;

  cout << "c2.node_id_ct() = " << c2.node_id_ct() << endl;


  return 0;

}
