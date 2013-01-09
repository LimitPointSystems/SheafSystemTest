#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.9 $ $Date: 2012/07/05 19:18:17 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

project(tools)

include(CTest)


cmake_minimum_required(VERSION 2.8.3)

#
# Include the functions and variable definitions unigue to this component.
#
include(${CMAKE_CURRENT_SOURCE_DIR}/component_definitions.cmake)

#
# Announce current status.
#
status_message("Processing ${PROJECT_NAME}")

#
# Initialize all variables for this component.
#
set_component_vars()

#
# Add the clusters to the project
#
add_clusters("${clusters}")

#
# examples will corrupt the scope sources. Include it after.
#
add_subdirectory(examples)

#
# Set compiler flags for all build configurations
#
set_compiler_flags()

#
# Set up output directories
#
create_output_dirs()

#
# Add the library targets
#
#add_library_targets()

#
# Add Bindings targets
#
add_bindings_targets()

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
# Component specific coverage target
#
if(ENABLE_COVERAGE)
status_message("Creating coverage target for ${PROJECT_NAME}")
    add_component_coverage_target()
endif()

#
# Component specific bin target
#
#add_component_bin_target()

#
# Installation target
#
#if(LINUX64)
#    add_install_target()
#endif()

#
# Write this component's lib targets and include paths to an export file.
#
export_targets()
