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

#
# This file is the system level counterpart to the component_definitions file
# found in the top level of any component. Functions and variables
# that need to have system scope should be declared and/or defined here.
#

#
# Establish the list of components in this system
#
set(COMPONENTS sheaves_test fiber_bundles_test geometry_test fields_test tools_test CACHE STRING "List of components in this system" FORCE)

#
# Set the cmake module path.
#
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules CACHE STRING "Location of Cmake modules")

#
# Platform definitions
#

# OS is 64 bit Windows, compiler is cl 
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows" AND MSVC AND CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(WIN64MSVC ON CACHE BOOL "MS compiler in use." FORCE)
# OS is 64 bit Windows, compiler is icl
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows" AND CMAKE_CXX_COMPILER_ID MATCHES "Intel" AND CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(WIN64INTEL ON CACHE BOOL "Intel compiler in use." FORCE)
# OS is 64 bit linux, compiler is g++
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux" AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(LINUX64GNU ON CACHE BOOL "GNU compiler in use." FORCE)
    set(CMAKE_CXX_FLAGS "-std=c++0x")
# OS is 64 bit linux, compiler is icpc
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux" AND CMAKE_CXX_COMPILER_ID MATCHES "Intel" AND CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(LINUX64INTEL ON CACHE BOOL "Intel compiler in use." FORCE)
    message(STATUS "Using Intel compiler")    
else()
    message(FATAL_ERROR "A 64 bit Windows or Linux environment was not detected; exiting")
endif()

set(EXPORTS_FILE ${PROJECT_NAME}-exports.cmake CACHE STRING "System exports file name")

#
# Delete the exports file at the start of each cmake run
#
execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/${EXPORTS_FILE})

#
# Set the default build type.
#
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug_contracts" CACHE STRING "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(ALL_BIN_TARGETS CACHE STRING "Aggregate list of component bin targets")
    
#
# $$HACK Toggle intel compiler warnings.
#
set(INTELWARN CACHE BOOL "Toggle Intel compiler warnings")

#
# Toggle multi-process compilation in win32.
#
set(ENABLE_WIN32_MP OFF CACHE BOOL "Toggle win32 compiler MP directive. Works for MS and Intel. Default is OFF.")

#
# Default linux installation location is /usr/local
# Set a default where the user has write permission ; in this
# case, the top of the components source tree.
# "lib", "include", and "bin" will be appended to this location.
# See "add_install_target" in cmake_modules/LPSCommon.cmake for source.
#
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE STRING "System install location")

#
# Establish the version number for this build.
# This is only relevant for releases. 0.0.0.0 is chosen here
# to indicate a non-snapshot build..
#
set(LIB_VERSION 0.0.0.0 CACHE STRING "Library version number for release purposes")
mark_as_advanced(LIB_VERSION)

#
# Targets with global scope are declared and optionally defined in 
# target_declarations.cmake; otherwise defined at first use.
#
include(${CMAKE_MODULE_PATH}/target_declarations.cmake)

#
# Prerequisite discovery
#
include(${CMAKE_MODULE_PATH}/find_prerequisites.cmake)
        

# If SHEAFSYSTEM_HOME contains white space, escape it.
file(TO_NATIVE_PATH "${SHEAFSYSTEM_HOME}" SHEAFSYSTEM_HOME)

# When we are dealing with an install, the hdf and tetgen include files are
# in the release include dir. If it's a build directory, then we need to know where
# the prereqs are. The includes below are defined in SheafSystem-exports.cmake
# If there's a RELEASE file in SHEAFSYSTEM_HOME, then we are dealing with a release.
if(NOT EXISTS ${SHEAFSYSTEM_HOME}/RELEASE)
    include_directories(${HDF_INCLUDE_DIR})
    include_directories(${TETGEN_INCLUDE_DIR})
endif()

#
# Enable coverage results
#
set(ENABLE_COVERAGE OFF CACHE BOOL "Set to ON to compile with Intel coverage support. Default is OFF.")

# Set the Coverage dir variable (used by Intel compiler) and create the coverage dir.
if(ENABLE_COVERAGE)
    set(COVERAGE_DIR ${CMAKE_BINARY_DIR}/coverage CACHE STRING "Directory for coverage files")
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${COVERAGE_DIR})
    # Configure the list of files for which we generate coverage data. Use only the SheafSystem
    # and ignore sheaves/std.
    configure_file(${CMAKE_MODULE_PATH}/coverage_files.lst.in ${CMAKE_BINARY_DIR}/coverage_files.lst)
endif()

#
# Utility function to add a component to a system.
#
function(add_components)

    foreach(comp ${COMPONENTS})
        clear_component_variables(${comp})
        add_subdirectory(${comp})
    endforeach()

endfunction(add_components)

#
# Clear cached variables at the start of each cmake run.
#
function(clear_component_variables comp)

    string(TOUPPER ${comp} COMP)

    # clear the srcs vars so consecutive cmake runs don't
    # list the same sources n times.
    unset(${COMP}_SRCS CACHE)
    
    # clear the unit tests var so consecutive cmake runs don't
    # list the same sources n times.
    unset(${COMP}_UNIT_TEST_SRCS CACHE)

    # clear the example binaries var so consecutive cmake runs don't
    # list the same sources n times.
    unset(${COMP}_EXAMPLE_SRCS CACHE)
    
    # clear the unit tests var so consecutive cmake runs don't
    # list the same unit tests n times.
    unset(${COMP}_UNIT_TESTS CACHE)
    
    # clear the unit tests var so consecutive cmake runs don't
    # list the same includes n times.
    unset(${COMP}_INCS CACHE)
    
    # clear the ipath var so consecutive cmake runs don't
    # list the same include paths n times.
    unset(${COMP}_IPATH CACHE)
    
endfunction(clear_component_variables)

# 
#  Make emacs tags
#
function(add_tags_target)

    if(LINUX64GNU OR LINUX64INTEL)
        add_custom_target(tags
            COMMAND find ${CMAKE_CURRENT_SOURCE_DIR} -name build -prune -o -name "*.cc" -print -o -name "*.h" -print -o -name "*.t.cc" -print | etags --c++ --members -
        )
    endif()

endfunction(add_tags_target) 

#
# Set the compiler flags per build configuration
#
function(set_compiler_flags)
   
       # Clear all cmake's intrinsic vars. If we don't, then their values will be appended to our
       # compile and link lines.
       set(CMAKE_CXX_FLAGS "" CACHE STRING "CXX Flags" FORCE)
       set(CMAKE_SHARED_LINKER_FLAGS "" CACHE STRING "Shared Linker Flags" FORCE)
       set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "" CACHE STRING "Debug Shared Linker Flags" FORCE)
       set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "Debug Shared Linker Flags" FORCE)
       set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "" CACHE STRING "Debug Shared Linker Flags" FORCE)
       set(CMAKE_EXE_LINKER_FLAGS "" CACHE STRING "Exe Linker Flags" FORCE)
       set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE STRING "Exe Linker Flags" FORCE)
       set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "Exe Linker Flags" FORCE)
       set(CMAKE_MODULE_LINKER_FLAGS "" CACHE STRING "Module Linker Flags" FORCE)
       set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "" CACHE STRING "Module Linker Flags" FORCE)
       set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "Module Linker Flags" FORCE) 

        # Toggle multi-process compilation in Windows
        # Set in system_definitions.cmake
        if(ENABLE_WIN32_MP)
            set(MP "/MP")
        else()
            set(MP "")
        endif()

    if(WIN64MSVC)
       set(LPS_CXX_FLAGS "/D_USRDLL ${MP} /GR /nologo /DWIN32 /D_WINDOWS /W1 /EHsc /D_HDF5USEDLL_ " CACHE STRING "C++ Compiler Flags")
       set(LPS_SHARED_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /DYNAMICBASE /NXCOMPAT /MACHINE:X64"  CACHE STRING "Linker Flags" FORCE)
       set(LPS_EXE_LINKER_FLAGS_DEBUG "/DEBUG" CACHE STRING "Debug Linker Flags" FORCE)
      set(LPS_EXE_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /MACHINE:X64" CACHE STRING "Linker Flags for Executables")
    elseif(WIN64INTEL)
       set(LPS_CXX_FLAGS "/D_USRDLL ${MP} /GR /nologo /DWIN32 /D_WINDOWS /W1 /wd2651 /EHsc ${OPTIMIZATION} /Qprof-gen:srcpos /D_HDF5USEDLL_" CACHE STRING "C++ Compiler Flags" FORCE)
       set(LPS_SHARED_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /DYNAMICBASE /NXCOMPAT /MACHINE:X64"  CACHE STRING "Linker Flags" FORCE) 
    elseif(LINUX64INTEL)
        if(ENABLE_COVERAGE)
            if(INTELWARN)
               set(LPS_CXX_FLAGS "-ansi -m64 -w1 -wd186,1125 -Wno-deprecated ${OPTIMIZATION} -prof-gen=srcpos")
            else()
               set(LPS_CXX_FLAGS "-ansi -m64 -w0 -Wno-deprecated ${OPTIMIZATION} -prof-gen=srcpos")
            endif()
        else()
            if(INTELWARN)
               set(LPS_CXX_FLAGS "-ansi -m64 -w1 -wd186,1125 -Wno-deprecated ${OPTIMIZATION}")
            else()
               set(LPS_CXX_FLAGS "-ansi -m64 -w0 -Wno-deprecated ${OPTIMIZATION}")
            endif()
        endif(ENABLE_COVERAGE)         
     elseif(LINUX64GNU)
         set(LPS_CXX_FLAGS "-m64 -Wno-deprecated")            
    endif()

    #                 
    # debug-contracts section
    #
        
    # Configuration specific flags 
    if(WIN64MSVC OR WIN64INTEL)
         set(CMAKE_CXX_FLAGS_DEBUG_CONTRACTS "${LPS_CXX_FLAGS} /Zi /D\"_ITERATOR_DEBUG_LEVEL=2\" /MDd /LDd /Od" CACHE
            STRING "Flags used by the C++ compiler for Debug_contracts builds" FORCE)
         set(CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS ${CMAKE_EXE_LINKER_FLAGS} ${LPS_EXE_LINKER_FLAGS_DEBUG}  CACHE
            STRING "Flags used by the linker for executables for Debug_contracts builds" FORCE)                      
    else()
        if(LINUX64INTEL)
            set(CMAKE_CXX_FLAGS_DEBUG_CONTRACTS "${LPS_CXX_FLAGS} -g -limf" CACHE
                STRING "Flags used by the C++ compiler for Debug_contracts builds" FORCE)
            set(CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS ${CMAKE_EXE_LINKER_FLAGS}  CACHE
                STRING "Flags used by the linker for executables for Debug_contracts builds" FORCE)                        
        else()
            set(CMAKE_CXX_FLAGS_DEBUG_CONTRACTS "${LPS_CXX_FLAGS} -g " CACHE
                STRING "Flags used by the C++ compiler for Debug_contracts builds" FORCE)
            set(CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS ${CMAKE_EXE_LINKER_FLAGS}  CACHE
                STRING "Flags used by the linker for executables for Debug_contracts builds" FORCE)                        
        endif() 
    endif()
    
    # True for all currently supported platforms    
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_CONTRACTS ${LPS_SHARED_LINKER_FLAGS} CACHE
        STRING "Flags used by the linker for shared libraries for Debug_contracts builds" FORCE)
    mark_as_advanced(CMAKE_CXX_FLAGS_DEBUG_CONTRACTS
                     CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS CMAKE_SHARED_LINKER_FLAGS_DEBUG_CONTRACTS)


    #                 
    # RelWithDebInfo_no_contracts section
    #

    # Configuration specific flags         
    if(WIN64MSVC OR WIN64INTEL)
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${LPS_CXX_FLAGS}  /MD /LD /O2 /DNDEBUG" CACHE
            STRING "RelWithDebInfo_no_contracts compiler flags" )
        set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG /NODEFAULTLIB:MSVCRTD  /NXCOMPAT" CACHE
            STRING "RelWithDebInfo_no_contracts linker flags - executables" )
        set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${LPS_SHARED_LINKER_FLAGS} /DEBUG /NODEFAULTLIB:MSVCRTD  /NXCOMPAT" CACHE
            STRING "RelWithDebInfo_no_contracts linker flags - shared libs" )
    else()
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${LPS_CXX_FLAGS} ${OPTIMIZATION} -DNDEBUG" CACHE
            STRING "RelWithDebInfo_no_contracts compiler flags" )
        set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS}" CACHE
            STRING "RelWithDebInfo_no_contracts linker flags - executables" )
        set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${LPS_SHARED_LINKER_FLAGS}" CACHE
            STRING "RelWithDebInfo_no_contracts linker flags - shared libs" )
    endif()
    
    # True for all currently supported platforms        
    mark_as_advanced(CMAKE_CXX_FLAGS_RELWITHDEBINFO_NO_CONTRACTS
                     CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS
                  )
                  
endfunction(set_compiler_flags)