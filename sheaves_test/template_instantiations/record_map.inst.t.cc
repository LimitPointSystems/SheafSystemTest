// $RCSfile: record_map.inst.t.cc,v $ $Revision: 1.1.2.5 $ $Date: 2012/10/19 02:23:27 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example template_instantiations/record_map.inst.t.cc
/// Unit test driver for template class record_map.

#include "record_map.h"
#include "test_sheaves.impl.h"

using namespace sheaf;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  print_header("Begin testing record_map<pod_index_type>");
  ltest &= test_record_map_facet<pod_index_type, pod_index_type>();
  print_footer("End testing record_map<pod_index_type>");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

