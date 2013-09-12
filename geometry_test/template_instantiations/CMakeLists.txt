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
    test_geometry_inst.cc
   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_geometry_inst.impl.h
   )
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    d_array_point_locator.inst.t.cc
    d_bin_coordinates.inst.t.cc
    d_bin_point_locator.inst.t.cc
    d_bounding_box.inst.t.cc
    d_tree_point_locator.inst.t.cc
    d_tree_point_locator_node.inst.t.cc
    d_tree_point_locator_path.inst.t.cc
    d_uniform_point_locator.inst.t.cc
    db0_point_locator.inst.t.cc
    geometry.auto_block.inst.t.cc
    geometry.block.inst.t.cc
    geometry.ptr_linked_pool.inst.t.cc
   )


collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

   )

collect_example_sources()
