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

project(sheaves_test)

cmake_minimum_required(VERSION 2.8.8)

#
# Include the functions and variable definitions unigue to this component.
#
include(${CMAKE_CURRENT_SOURCE_DIR}/component_definitions.cmake)

#
# Announce current status.
#
status_message("Processing ${PROJECT_NAME}")

#
# Set compiler flags for all build configurations
#
set_compiler_flags()

#
# Add the library targets
#
add_library_targets()

#
# Set up output directories
#
create_output_dirs()

#
# Add the unit test targets
#
if(WIN64MSVC OR WIN64INTEL)
    add_win32_test_targets()
else()
    add_linux_test_targets()
endif()

#
# Add the example targets
#
add_example_targets()

#
# Component specific check target
#
add_component_check_target()

#
# Component specific check target
#
add_component_bin_target()

#
# Component specific coverage target
#
if(ENABLE_COVERAGE)
    status_message("Creating coverage target for ${PROJECT_NAME}")
        add_component_coverage_target()
endif()
