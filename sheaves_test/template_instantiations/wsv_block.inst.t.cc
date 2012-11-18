// $RCSfile: wsv_block.inst.t.cc,v $ $Revision: 1.1.2.6 $ $Date: 2012/11/08 17:00:41 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example
/// Unit test driver for template class wsv_block.

#include "wsv_block.impl.h"
#include "schema_descriptor.h"
#include "test_sheaves.impl.h"

using namespace sheaf;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  bool ltest = true;

  // bool

  print_header("Begin testing wsv_block<bool>");
  ltest &= test_wsv_block_facet<bool>();
  print_footer("End testing wsv_block<bool>");

  // int

  print_header("Begin testing wsv_block<int>");
  ltest &= test_wsv_block_facet<int>();
  print_footer("End testing wsv_block<int>");

  // double

  print_header("Begin testing wsv_block<double>");
  ltest &= test_wsv_block_facet<double>();
  print_footer("End testing wsv_block<double>");

  // unsigned

  print_header("Begin testing wsv_block<unsigned>");
  ltest &= test_wsv_block_facet<unsigned>();
  print_footer("End testing wsv_block<unsigned>");

  // $$SCRIBBLE: Currently not instantiated.
  //   // unsigned long

  //   print_header("Begin testing wsv_block<unsigned long>");
  //   ltest &= test_wsv_block_facet<unsigned long>();
  //   print_footer("End testing wsv_block<unsigned long>");

  // size_type

  print_header("Begin testing wsv_block<size_type>");
  ltest &= test_wsv_block_facet<size_type>();
  print_footer("End testing wsv_block<size_type>");

  // schema_descriptor

  print_header("Begin testing wsv_block<schema_descriptor>");
  ltest &= test_wsv_block_facet<schema_descriptor>();
  print_footer("End testing wsv_block<schema_descriptor>");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}

