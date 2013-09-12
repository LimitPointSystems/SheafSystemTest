
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Interface for class block_scaling_test

#ifndef BLOCK_SCALING_TEST_H
#define BLOCK_SCALING_TEST_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h" // for size_type
#endif

#ifndef PLOT_H
#include "plot.h"
#endif

namespace fiber_bundle
{
  class fiber_bundles_namespace;
  class sec_rep_space;
  class point_block_1d;
  class point_block_2d;
  class point_block_3d;
  class structured_block_1d;
  class structured_block_2d;
  class structured_block_3d;
  class unstructured_block;
  class zone_nodes_block;
  
  using namespace sheaf;

  ///
  /// Creates a block of type T with index bounds given 
  /// by xsizes and index space dimension given by xdi.
  ///
  template<typename T>
  T*
  make_block(fiber_bundles_namespace* xns, size_type xsizes[], size_type xdi);

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
 
  ///
  /// Creates a scalar section for a point_block_1d.
  ///
  SHEAF_DLL_SPEC 
  sec_rep_space&
  make_scalar_section_space(fiber_bundles_namespace& xns,
			    point_block_1d& xblock);

  ///
  /// Creates a scalar section for a point_block_2d.
  ///
  SHEAF_DLL_SPEC 
  sec_rep_space&
  make_scalar_section_space(fiber_bundles_namespace& xns,
			    point_block_2d& xblock);

  ///
  /// Creates a scalar section for a point_block_3d.
  ///
  SHEAF_DLL_SPEC 
  sec_rep_space&
  make_scalar_section_space(fiber_bundles_namespace& xns,
			    point_block_3d& xblock);

  ///
  /// Creates a scalar section for a structured_block_1d.
  ///
  SHEAF_DLL_SPEC 
  sec_rep_space&
  make_scalar_section_space(fiber_bundles_namespace& xns,
			    structured_block_1d& xblock);

  ///
  /// Creates a scalar section for a structured_block_2d.
  ///
  SHEAF_DLL_SPEC 
  sec_rep_space&
  make_scalar_section_space(fiber_bundles_namespace& xns,
			    structured_block_2d& xblock);

  ///
  /// Creates a scalar section for a structured_block_3d.
  ///
  SHEAF_DLL_SPEC 
  sec_rep_space&
  make_scalar_section_space(fiber_bundles_namespace& xns,
			    structured_block_3d& xblock);

  ///
  /// Creates a scalar section for a zone_nodes_block.
  ///
  SHEAF_DLL_SPEC 
  sec_rep_space&
  make_scalar_section_space(fiber_bundles_namespace& xns,
			    zone_nodes_block& xblock);

  ///
  /// Creates a scalar section for a unstructured_block.
  /// This function exists so that it can be specialized for point blocks.
  ///
  SHEAF_DLL_SPEC 
  sec_rep_space&
  make_scalar_section_space(fiber_bundles_namespace& xns,
			    unstructured_block& xblock);

} // namespace fiber_bundle

#endif // ifndef BLOCK_SCALING_TEST_H
