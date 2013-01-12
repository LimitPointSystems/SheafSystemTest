
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example base_spaces/tetra_connectivity.t.cc
/// Test case for class tetra_connectivity

#include "tetra_connectivity.h"
#include "std_iostream.h"

using namespace fiber_bundle;

int main()
{

  tetra_connectivity c(2, 3, 4);

  cout << c << endl;

  cout << "c.node_id_ct() = " << c.node_id_ct() << endl;

  tetra_connectivity c1;

  cout << c1 << endl;

  cout << "c1.node_id_ct() = " << c1.node_id_ct() << endl;
  
  tetra_connectivity c2(4, 2, 1);

  cout << c2 << endl;

  cout << "c2.node_id_ct() = " << c2.node_id_ct() << endl;


  return 0;

}
