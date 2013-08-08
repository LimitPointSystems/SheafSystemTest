#
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

project(fields_test)

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
