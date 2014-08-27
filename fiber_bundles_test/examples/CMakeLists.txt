#
# Copyright (c) 2014 Limit Point Systems, Inc. 
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

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS

   )
  
collect_includes()

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

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS
   )

collect_example_sources()
