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
# Establish the project name
#    
project(SheafSystemTest)

include(CTest)

#
# Information glaringly omitted from CMake documentation and discussion regarding CTest and CDash:
#
# 1. CTestConfig.cmake must be in the top level of your project.
#
#    1.1 DROP_SITE value must be a FQDN sans "http://". Numerical IP will not work!
#
#    1.2 If the system is multi-component, then the vars in CTestConfig.cmake
#        must be cached so they are placed in the cmake global namespace and 
#        therefore visible to all components.
#
# 2. The prerequisite for all ctest targets e.g. "Experimental" is ALL.
#     If you plan to submit tests to a dashboard, it might be a good idea
#     to carefully review what constitutes "ALL" in your system to avoid
#     uneccessary time consuming tasks.
#
# 3. It is only neccessary to include CTest at the top level of the System.
#    enable_testing() is implied by the inclusion of the CTest modules and
#    therefore an explicit reference to it is redundant and perhaps problematic
#    under certain conditions. 

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
# Add the system checklog target. Action is
# identical to "check", but output is redirected to file.
# Only needs to be called at the system level.
# use "<component>-check" for component level
# tests.
#
#add_checklog_target()

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


