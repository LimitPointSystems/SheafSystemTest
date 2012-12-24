
// $RCSfile: test_fibers_x.h,v $ $Revision: 1.12 $ $Date: 2012/03/01 00:40:45 $

//
// Copyright (c) 2012 Limit Point Systems, Inc. 
//

/// @file
/// Interface for fiber test function templates.

#ifndef TEST_FIBERS_X_H
#define TEST_FIBERS_X_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef AT0_H
#include "at0.h"
#endif

#ifndef AT2_E2_H
#include "at2_e2.h"
#endif

#ifndef AT2_E3_H
#include "at2_e3.h"
#endif

#ifndef AT3_E3_H
#include "at3_e3.h"
#endif

#ifndef E1_H
#include "e1.h"
#endif

#ifndef E2_H
#include "e2.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

#ifndef E4_H
#include "e4.h"
#endif

#ifndef GL2_H
#include "gl2.h"
#endif

#ifndef GL3_H
#include "gl3.h"
#endif

#ifndef JCB_E13_H
#include "jcb_e13.h"
#endif

#ifndef JCB_E23_H
#include "jcb_e23.h"
#endif

#ifndef JCB_E33_H
#include "jcb_e33.h"
#endif

#ifndef MET_E1_H
#include "met_e1.h"
#endif

#ifndef MET_E2_H
#include "met_e2.h"
#endif

#ifndef MET_E3_H
#include "met_e3.h"
#endif

#ifndef ST2_E2_H
#include "st2_e2.h"
#endif

#ifndef ST2_E3_H
#include "st2_e3.h"
#endif

#ifndef ST3_E3_H
#include "st3_e3.h"
#endif

#ifndef ST4_E2_H
#include "st4_e2.h"
#endif

#ifndef ST4_E3_H
#include "st4_e3.h"
#endif

#ifndef T2_E2_H
#include "t2_e2.h"
#endif

#ifndef T2_E3_H
#include "t2_e3.h"
#endif

#ifndef T3_E3_H
#include "t3_e3.h"
#endif

#ifndef T4_E2_H
#include "t4_e2.h"
#endif

#ifndef T4_E3_H
#include "t4_e3.h"
#endif

#ifndef TP_SPACE_H
#include "tp_space.h"
#endif

namespace fiber_bundle
{
  ///
  ///
  ///
  template<typename F>
  void
  test_volatile_common();

  ///
  ///
  ///
  template<typename F>
  void
  test_volatile_row_dofs();

  ///
  ///
  ///
  template<typename F>
  void
  test_volatile_tp_facet();

} // namespace fiber_bundle


#endif // ifndef TEST_FIBERS_X_H
