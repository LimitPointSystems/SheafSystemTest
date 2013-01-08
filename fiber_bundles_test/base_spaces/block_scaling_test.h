// $RCSfile: block_scaling_test.h,v $ $Revision: 1.10.94.1 $ $Date: 2013/01/08 14:59:48 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

// Interface for class block_scaling_test

#ifndef BLOCK_SCALING_TEST_H
#define BLOCK_SCALING_TEST_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef PLOT_H
#include "plot.h"
#endif

#ifndef SEC_AT0_H
#include "sec_at0.h"
#endif

namespace fiber_bundle
{
class fiber_bundles_namespace;
  
  using namespace sheaf;


 
  ///
  /// Creates a block of type T with index bounds given 
  /// by xsizes and index space dimension given by xdi.
  ///
  template<typename T>
  T*
  make_block(fiber_bundles_namespace* xns, size_type xsizes[], size_type xdi);

  ///
  /// Creates a scalar section for base space of type T.
  /// This function exists so that it can be specialized for point blocks.
  ///
  template<typename T>
  sec_at0::host_type& make_scalar_section_space(fiber_bundles_namespace& xns,
						T& xblock);

  ///
  /// Creates a block of type T with index bounds given 
  /// by xsizes and index space dimension given by xdi,
  /// times the construction and various iterations,
  /// and adds the results to plots xtime_plot and xmem_plot.
  ///
  template<typename T>
  void
  time_block(size_type xsizes[], size_type xdi, plot& xtime_plot, plot& xmem_plot);

  ///
  /// Tests the scaling for blocks of type T with index spaces of dimension D
  /// up to a maximum number of zones given by argv[1].
  /// xtime_plot_types and xmem_plot_types are type of equation of fit.
  ///
  template<typename T, int D>
  void
  test_scaling(int xargc, char* xargv[],
	       plot::plot_type xtime_plot_types[12],
	       plot::plot_type xmem_plot_types[7]);

  ///
  /// Returns the number of static handles, xhandle_ct, and
  /// the deep size the static handles, xhandle_deep_size.
  ///
  SHEAF_DLL_SPEC
  void
  pools_size(size_type& xhandle_ct, size_type& xhandle_deep_size);
 
} // namespace fiber_bundle

#endif // ifndef BLOCK_SCALING_TEST_H
