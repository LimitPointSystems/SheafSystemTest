#
# Copyright (c) 2013 Limit Point Systems, Inc. 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER ${CMAKE_CURRENT_BINARY_DIR})

#
# Library sources.
#
set(SRCS

   )

ShfSysTst_collect_sources(fiber_bundles_test "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS

   )
  
ShfSysTst_collect_includes(fiber_bundles_test "${SRCS}" "${ADDITIONAL_INCS}") 

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    bilinear_2d.t.cc
    constant_eval_family.t.cc
    constant_hex.t.cc 
    constant_quad.t.cc 
    constant_segment.t.cc 
    constant_tet.t.cc 
    constant_triangle.t.cc 
    dlinear_eval_family.t.cc
    linear_1d.t.cc 
    linear_2d.t.cc 
    linear_3d.t.cc
    quadratic_1d.t.cc
    quadratic_2d.t.cc
    quadratic_3d.t.cc
    trilinear_3d.t.cc
    uniform_1d.t.cc
    uniform_2d.t.cc
    uniform_3d.t.cc
    uniform_eval_family.t.cc
   )

ShfSysTst_collect_unit_test_sources(fiber_bundles_test "${UNIT_TEST_SRCS}")

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

   )

ShfSysTst_collect_example_sources(fiber_bundles_test "${EXAMPLE_SRCS}")

