#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.16 $ $Date: 2012/07/05 19:18:14 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

# Setting CMAKE_CONFIGURATION_TYPES prior to the project function call
# will eliminate the default configuration types (debug,release,RelWithDebugInfo, et al.) --
# or at least stop them from appearing in the VS configuration list.
# It does NOT stop cmake from setting all the cache variables associated with those same
# configurations however.

set(CMAKE_CONFIGURATION_TYPES Debug-contracts Debug-no-contracts Release-contracts Release-no-contracts CACHE
    STRING "Supported configuration types"
    FORCE)

#
# Extablich the project name
#    
project(SheafSystemTest)

#
# Ensure that we have the required cmake version.
#
cmake_minimum_required(VERSION 2.8.3)

#
# Include variable definitions and functions
# unique to and/or required at the system level.
#
include(system_definitions.cmake)

#
# Set the compiler optimization level
#
set_optimization_level()

#
# Add components to the system
#
add_components()

#
# Set up output directories
#
create_output_dirs()

#
# Snapshot target for Visual Studio
#
if(WIN64)
    create_vswin64_snapshot_target()
endif()

#
# Add the system check target.
# Only needs to be called at the system level.
# use "<component>-check" for component level
# tests.
#
add_check_target()

#
# Add the system coverage target.
# Only needs to be called at the system level.
# use "<component>-coverage" for component level
# coverage results.
#
add_coverage_target()

#
# Add the documentation targets (doc, docclean)
# Doc targets are system level and system scope.
# currently there is no notion of building a single
# component's documentation.
#
add_doc_targets()

#
# Add files to the clean target
#
add_clean_files()

#
# Target to generate emacs tags
#
add_tags_target()

#
# Add the system bin target.
# All unit tests and examples are built, but not run.
# Only needs to be called at the system level.
# use "<component>-bin" for component level
# binaries.
#
add_bin_target()

#
# Configure the environment scripts. 
#
configure_file(${CMAKE_MODULE_PATH}/set_env_vars.csh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.csh)
configure_file(${CMAKE_MODULE_PATH}/set_env_vars.sh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.sh)

#
# System level is responsible for installing the documentation. The component list (see system_definitions.cmake)
# determines what components are included in the docs.
#
install(DIRECTORY ${CMAKE_BINARY_DIR}/documentation/ DESTINATION documentation)

#
# Cpack Setup
#
if(LINUX64)
    set(CPACK_PACKAGE_VERSION "${LIB_VERSION}") 
    set(CPACK_GENERATOR "TBZ2")
    include(CPack)
endif()

#
# If we are using VTK, then append VTK vars to the exports file
#
if(${USE_VTK})
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(USE_VTK ON CACHE BOOL \"Set to link against VTK libs\" FORCE)\n")
    file(APPEND  ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
endif()

#
# Append the list of components from this system to the exports file
#
#file(APPEND  ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
#file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(SDM_COMPONENTS ${COMPONENTS} CACHE STRING \"List of external components\")\n")
