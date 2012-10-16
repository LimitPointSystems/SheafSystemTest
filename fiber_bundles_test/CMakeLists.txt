#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.10 $ $Date: 2012/07/05 19:18:15 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

project(fiber_bundles_test)

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
# Add the clusters to the project
#
add_clusters("${clusters}")

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
add_library_targets()

#
# Add the unit test targets
#
add_test_targets()

#
# Add the example targets
#
add_example_targets()

#
# Component specific check target
#
add_component_check_target()

#
# Component specific checklog target
#
add_component_checklog_target()

#
# Component specific coverage target
#
add_component_coverage_target()

#
# Component specific bin target
#
add_component_bin_target()



