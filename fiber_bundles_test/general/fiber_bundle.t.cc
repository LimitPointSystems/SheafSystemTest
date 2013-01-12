
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Test driver for fiber_bundle functions.

#include "fiber_bundle.h"

#include "poset_path.h"
#include "std_iostream.h"
#include "test_utils.h"

using namespace fiber_bundle;

int
main(int xargc, char* xargv[])
{
  print_header("Begin testing fiber_bundle functions");

  int result = 0;

  //poset_path standard_section_space_path(const poset_path& xfiber_path,
  //                                       const poset_path& xbase_path);
  

  const poset_path lfiber_path("the_fiber_path");
  const poset_path lbase_path("the_base_path");
  poset_path lpath0 = standard_section_space_path(lfiber_path, lbase_path);

  cout << "lpath0 = " << lpath0 << endl;

  //poset_path standard_section_space_schema_path(
  //  const poset_path& xsection_space_path);

  const poset_path lsection_space_path("the_section_space_path");
  poset_path lpath1 = standard_section_space_schema_path(lsection_space_path);

  cout << "lpath1 = " << lpath1 << endl;

  print_footer("End testing fiber_bundle functions");

  return result;
}
