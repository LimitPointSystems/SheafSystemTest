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

# Setting CMAKE_CONFIGURATION_TYPES prior to the project function call
# will eliminate the default configuration types (debug,release,RelWithDebugInfo, et al.) --
# or at least stop them from appearing in the VS configuration list.
# It does NOT stop cmake from setting all the cache variables associated with those same
# configurations however.

if(WIN32)
    set(CMAKE_CONFIGURATION_TYPES  Debug_contracts RelWithDebInfo_no_contracts 
        CACHE STRING "Supported configuration types" FORCE)
else()
    set(CMAKE_CONFIGURATION_TYPES Debug_contracts Release_no_contracts 
         CACHE STRING "Supported configuration types" FORCE)
endif()

#
# Tell Cmake which configurations it should see and "Debug"
#
set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS "Debug_contracts" ) 

#
# Debug lib should have "_d" appended to filename.
#
if(WIN32)
    set(CMAKE_DEBUG_CONTRACTS_POSTFIX "_d" CACHE STRING "Debug libs suffix")
else()
    set(CMAKE_DEBUG_CONTRACTS_POSTFIX "_debug" CACHE STRING "Debug libs suffix")
endif()
    
#
# Establish the project name
#    
project(SheafSystemTest)

#
# Information omitted from CMake documentation and discussion regarding CTest and CDash:
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
cmake_minimum_required(VERSION 2.8.12)

#
# Include variable definitions and functions
# unique to and/or required at the system level.
#
include(system_definitions.cmake)

#
# Set the compiler optimization level
#
#set_optimization_level()

#
# Add components to the system
#
add_components()

#
# Add the system-level check target.
# This is an aggregate target and will exercise all the components.
# Use "<component>-check" for component level tests. 
# NOTE: add_check_target() must only be called AFTER all component CmakeLists.txt
# files are read.
#
add_check_target()

#
# Add the system coverage target.
# This is an aggregate target and will exercise all the components.
# Use "<component>-coverage" for component level coverage results.
# NOTE: add_coverage_target() must only be called AFTER all component CmakeLists.txt
# files are read.
#
if(ENABLE_COVERAGE)
    add_coverage_target()
endif()

#
# Add the system bin target.
# This is an aggregate target and will exercise all the components.
# All unit tests and examples are built, but not run.
# Use "<component>-bin" for component level binary construction.
# NOTE: add_bin_target() must only be called AFTER all component CmakeLists.txt
# files are read.
#
add_bin_target()

#
# Configure the environment scripts. 
#
if(LINUX64GNU OR LINUX64INTEL)
    configure_file(${CMAKE_MODULE_PATH}/set_env_vars.csh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.csh)
    configure_file(${CMAKE_MODULE_PATH}/set_env_vars.sh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.sh)
endif()

#
# Markup the RELEASE_NOTES file. 
#
#set(RELEASE_DATE)
#get_date(RELEASE_DATE)
#configure_file(${CMAKE_SOURCE_DIR}/RELEASE_NOTES.in ${CMAKE_SOURCE_DIR}/RELEASE_NOTES)
