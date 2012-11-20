// $RCSfile: section_space_factory.inst.t.cc,v $ $Revision: 1.1.2.9 $ $Date: 2012/11/08 17:22:07 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class section_space_factory.

#include "section_space_factory.impl.h"

#include "sec_at0.h"

// #include "arg_list.h"
// #include "chart_point_1d.h"
// #include "chart_point_2d.h"
// #include "chart_point_3d.h"
// #include "discretization_context.h"
// #include "e3.h"
// #include "sec_tuple.h"
// #include "sec_vd.h"
// #include "section_evaluator.h"
// #include "differentiable_section_evaluator.h"
// #include "integrable_section_evaluator.h"
// #include "structured_block.h"
// #include "structured_block_1d.h"
// #include "structured_block_1d_crg_range.h"
// #include "structured_block_2d_crg_range.h"
// #include "structured_block_3d_crg_range.h"
// #include "base_space_crg_range.h"
// #include "point_block_crg_range.h"
// #include "zone_nodes_block_crg_range.h"
// #include "homogeneous_block_crg_range.h"
// #include "test_utils.h"
// #include "test_sheaves.impl.h"

using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  section_space_factory<sec_at0> lfac;

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}
