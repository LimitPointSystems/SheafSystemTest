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
    at0.t.cc 
    fields3d.t.cc 
    torus.t.cc
    recipe.t.cc 
# The following files are no longer part of the build.
# they are deprecated and only remain around as a reference
# for future development.
#    partial_field.t.cc 
#    discretization_iterator.t.cc 
#    scalable_entire_read_write.t.cc 
#    scalable_iterator.t.cc
   )

ShfSysTst_collect_unit_test_sources(fiber_bundles_test "${UNIT_TEST_SRCS}")

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS
   )

ShfSysTst_collect_example_sources(fiber_bundles_test "${EXAMPLE_SRCS}")
