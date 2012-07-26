// $RCSfile: triangle_connectivity.t.cc,v $ $Revision: 1.12 $ $Date: 2012/03/01 00:40:32 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example base_spaces/triangle_connectivity.t.cc
/// Test case for class triangle_connectivity

#include "triangle_connectivity.h"
#include "std_iostream.h"

using namespace fiber_bundle;

int main()
{

  triangle_connectivity c(2, 3);

  cout << c << endl;

  cout << "c.node_id_ct() = " << c.node_id_ct() << endl;

  triangle_connectivity c1;

  cout << c1 << endl;

  cout << "c1.node_id_ct() = " << c1.node_id_ct() << endl;

  triangle_connectivity c2(4, 2, 1);

  cout << c2 << endl;

  cout << "c2.node_id_ct() = " << c2.node_id_ct() << endl;


  pod_index_type lnode_ids3[6] = {0,1,2,0,2,3}; 
  triangle_connectivity c3(lnode_ids3, 6, 4);
  
  cout << c3 << endl;
  cout << "c3.node_id_ct() = " << c3.node_id_ct() << endl;
  cout << "c3.node_ct() = " << c3.node_ct() << endl;
  cout << "c3.start_id() = " << c3.start_id() << endl;

  pod_index_type lnode_ids4[6] = {1,2,3,1,3,4}; 
  triangle_connectivity c4(lnode_ids4, 6, 0);
  
  cout << c4 << endl;
  cout << "c4.node_id_ct() = " << c4.node_id_ct() << endl;
  cout << "c4.node_ct() = " << c4.node_ct() << endl;
  cout << "c4.start_id() = " << c4.start_id() << endl;
  

  return 0;

}
