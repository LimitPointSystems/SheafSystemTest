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

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
#  Define system level variables and initialize to default values.
#
function(ShfSysTst_set_system_variable_defaults)

   #
   # Make sure LIB_VERSION is defined; won't overwrite value if it already exists.
   #
   set(LIB_VERSION 0.0.0.0 CACHE STRING "Library version number for release purposes")
   mark_as_advanced(LIB_VERSION)

   #
   # Define the unique header file scope qualifier and directory path.
   #
   set(SHFSYSTST_HEADER_SCOPE SheafSystemTest
      CACHE STRING "Used to give header files unique scope in include directives.")
   mark_as_advanced(SHFSYSTST_HEADER_SCOPE)  

   set(SHFSYSTST_HEADER_DIR ${CMAKE_BINARY_DIR}/include/${SHFSYSTST_HEADER_SCOPE}
      CACHE PATH "Path to scoped header file directory.")
   mark_as_advanced(SHFSYSTST_HEADER_DIR)  

   #
   # Toggle tests. Only effective in Windows.
   # Enabling all tests types by default can create a really slow VS project.
   # Toggle the test type(s) you need.
   #
   set(SHFSYSTST_ENABLE_UNIT_TEST_LOG_TARGETS OFF CACHE BOOL "Toggle inclusion of Unit Test log targets.")
   mark_as_advanced(FORCE SHFSYSTST_ENABLE_UNIT_TEST_LOG_TARGETS)
   
   set(SHFSYSTST_ENABLE_UNIT_TEST_HDF_LOG_TARGETS OFF CACHE BOOL "Toggle inclusion of Unit Test hdf5 log targets.")
   mark_as_advanced(FORCE SHFSYSTST_ENABLE_UNIT_TEST_HDF_LOG_TARGETS)

   # Number of concurrent jobs for running tests;
   # want it in the basic interface, so not advanced.

   set(SHFSYSTST_TEST_JOBS 1 CACHE STRING "Number of concurrent jobs for running tests.")
   mark_as_advanced(CLEAR SHFSYSTST_TEST_JOBS)
   
   # System level target lists

   set(ALL_UNIT_TEST_TARGETS CACHE STRING "Aggregate list of all unit test targets" FORCE)
   mark_as_advanced(FORCE ALL_UNIT_TEST_TARGETS) 

   set(ALL_BIN_TARGETS CACHE STRING "Aggregate list of all bin targets" FORCE)
   mark_as_advanced(FORCE ALL_BIN_TARGETS) 

   set(ALL_COMP_CHECK_TARGETS CACHE STRING "Aggregate list of all check targets" FORCE)
   mark_as_advanced(FORCE ALL_COMP_CHECK_TARGETS)

   set(ALL_COVERAGE_TARGETS CACHE STRING "Aggregate list of all coverage targets" FORCE)
   mark_as_advanced(FORCE ALL_COVERAGE_TARGETS)

   set(ALL_CHECKLOG_TARGETS CACHE STRING "Aggregate list of all checklog targets" FORCE)
   mark_as_advanced(FORCE ALL_CHECKLOG_TARGETS) 

endfunction(ShfSysTst_set_system_variable_defaults)


#
# Set platform definitions
#
function(ShfSysTst_set_platform_variables)

   # Make sure platform variables are defined.

   set(SHFSYSTST_CXX_IMPLICIT_LINK_DIRECTORIES CACHE STRING "C++ compiler library directories." FORCE)
   mark_as_advanced(FORCE SHFSYSTST_CXX_IMPLICIT_LINK_DIRECTORIES)

   set(SHFSYSTST_WINDOWS OFF CACHE BOOL "True if platform is Windows" FORCE)
   mark_as_advanced(FORCE SHFSYSTST_WINDOWS)

   set(SHFSYSTST_LINUX OFF CACHE BOOL "True if platform is Linux" FORCE)
   mark_as_advanced(FORCE SHFSYSTST_LINUX)

   set(SHFSYSTST_WIN64MSVC OFF CACHE BOOL "True if platform is Windows and MS compiler in use." FORCE)
   mark_as_advanced(FORCE SHFSYSTST_WIN64MSVC)

   set(SHFSYSTST_WIN64INTEL OFF CACHE BOOL "True if platorm is Windows and Intel compiler in use." FORCE)
   mark_as_advanced(SHFSYSTST_WIN64INTEL)

   set(SHFSYSTST_LINUX64GNU OFF CACHE BOOL "True if platform is Linux and GNU CXX compiler in use." FORCE)
   mark_as_advanced(SHFSYSTST_LINUX64GNU)

   set(SHFSYSTST_LINUX64INTEL OFF CACHE BOOL "True if platform is Linux and Intel compiler in use." FORCE)
   mark_as_advanced(SHFSYSTST_LINUX64INTEL)   

   if(CMAKE_SIZEOF_VOID_P MATCHES "8")

      if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")

         # OS is 64 bit Windows 

         set(SHFSYSTST_WINDOWS ON CACHE BOOL "True if platform is Windows" FORCE)

         # Toggle multi-process compilation in win32.

         set(SHFSYSTST_ENABLE_WIN32_MP ON
            CACHE BOOL "Toggle win32 compiler MP directive. Works for MS and Intel. Default is ON.")
         mark_as_advanced(FORCE SHFSYSTST_ENABLE_WIN32_MP)

         # Turn on project folders for Visual Studio.

         set_property(GLOBAL PROPERTY USE_FOLDERS ON)

         if(MSVC)

            # OS is 64 bit Windows, compiler is cl 

            set(SHFSYSTST_WIN64MSVC ON CACHE BOOL "True if platform is Windows and MS compiler in use." FORCE)

         elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")

            # OS is 64 bit Windows, compiler is icl

            set(SHFSYSTST_WIN64INTEL ON CACHE BOOL "True if platorm is Windows and Intel compiler in use." FORCE)

            set(INTELWARN CACHE BOOL "Toggle Intel compiler warnings")
            mark_as_advanced(FORCE INTELWARN)

         else()

            message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER_ID} not supported.")

         endif()

      elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")

         # OS is 64 bit Linux 

         set(SHFSYSTST_LINUX ON CACHE BOOL "True if platform is Linux" FORCE)

         if(CMAKE_COMPILER_IS_GNUCXX)

            # OS is 64 bit linux, compiler is g++

            if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9.3)
               message(FATAL "g++ ${CMAKE_CXX_COMPILER_VERSION} is unsupported. Version must be >= 4.9.3")                
            endif()

            set(SHFSYSTST_LINUX64GNU ON CACHE BOOL "True if platform is Linux and GNU CXX compiler in use." FORCE)

         elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")

            # OS is 64 bit linux, compiler is icpc

            set(SHFSYSTST_LINUX64INTEL ON CACHE BOOL "True if platform is Linux and Intel compiler in use." FORCE)

            set(INTELWARN CACHE BOOL "Toggle Intel compiler warnings")
            mark_as_advanced(FORCE INTELWARN)

         else()

            message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER_ID} not supported.")

         endif(CMAKE_COMPILER_IS_GNUCXX)

         # The compiler library path; used to set LD_LIBRARY_PATH in env scripts.

         string(REPLACE ";" ":" lshfsys_lib_dirs "${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES}")
         set(SHFSYSTST_CXX_IMPLICIT_LINK_DIRECTORIES "${lshfsys_lib_dirs}" 
            CACHE STRING "C++ compiler library directories." FORCE)

      else()

         # Neither Windows or Linux

         message(FATAL_ERROR "Operating system ${CMAKE_HOST_SYSTEM_NAME} not supported")

      endif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")

   else(CMAKE_SIZEOF_VOID_P MATCHES "8")

         message(FATAL_ERROR "Only 64 bit platform supported.")

   endif(CMAKE_SIZEOF_VOID_P MATCHES "8")

   dbc_ensure_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

endfunction(ShfSysTst_set_platform_variables)

#
# Set the default value for install location
#
function(ShfSysTst_set_system_install_location_default)

   # There is no notion of installing SheafSystemTest.
   
   set(CMAKE_INSTALL_PREFIX "" CACHE STRING "System install location")
   mark_as_advanced(FORCE CMAKE_INSTALL_PREFIX)

endfunction(ShfSysTst_set_system_install_location_default)


#
# Set debug configuration properties.
#
function(ShfSysTst_set_debug_configuration)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body:

   # Tell CMake which configurations are "debug"

   set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS "Debug_contracts") 

   # Establish the file name suffix for debug type compiler output

   if(SHFSYSTST_WINDOWS)

      set(CMAKE_DEBUG_CONTRACTS_POSTFIX "_d" CACHE STRING "Debug libs suffix")
      mark_as_advanced(FORCE CMAKE_DEBUG_CONTRACTS_POSTFIX)

      set(CMAKE_DEBUG_NO_CONTRACTS_POSTFIX "_d" CACHE STRING "Debug libs suffix")
      mark_as_advanced(FORCE CMAKE_DEBUG_NO_CONTRACTS_POSTFIX)

   elseif(SHFSYSTST_LINUX)

      set(CMAKE_DEBUG_CONTRACTS_POSTFIX "_debug" CACHE STRING "Debug libs suffix")
      mark_as_advanced(FORCE CMAKE_DEBUG_CONTRACTS_POSTFIX)

      set(CMAKE_DEBUG_NO_CONTRACTS_POSTFIX "_debug" CACHE STRING "Debug libs suffix")
      mark_as_advanced(FORCE CMAKE_DEBUG_NO_CONTRACTS_POSTFIX)

   endif()

endfunction(ShfSysTst_set_debug_configuration)

#
# Set the default build type.
#
function(ShfSysTst_set_default_build_type)

   if(NOT CMAKE_BUILD_TYPE)
      set(CMAKE_BUILD_TYPE "Debug_contracts" 
         CACHE 
         STRING 
         "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}."
         FORCE)
   elseif(NOT (CMAKE_BUILD_TYPE IN_LIST CMAKE_CONFIGURATION_TYPES))
      message(FATAL_ERROR "CMAKE_BUILD_TYPE must be one of ${CMAKE_CONFIGURATION_TYPES}")
   endif()

   if(SHFSYSTST_WINDOWS)
      
      # Build type isn't set at configure time in Windows
      # so keep it out of the basic user interface.
      
      mark_as_advanced(FORCE CMAKE_BUILD_TYPE)
   endif()

   # Set STRINGS property so GUI displays cycle-through or drop-down list.
   
   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})   

endfunction(ShfSysTst_set_default_build_type)

function(ShfSysTst_set_coverage_defaults)

   # Disable coverage results by default; won't overwrit existing value.
   # Haven't tested coverage generation, so keep it out of the basic interface.

   set(SHFSYSTST_ENABLE_COVERAGE OFF CACHE BOOL "Set to ON to compile with coverage support. Default is OFF.")
   mark_as_advanced(FORCE SHFSYSTST_ENABLE_COVERAGE)    
   
   set(SHFSYSTST_COVERAGE_DIR CACHE STRING "Directory for coverage files. Default is empty.")
   mark_as_advanced(FORCE SHFSYSTST_COVERAGE_DIR)    

   # Set the location of the coverage folder and then create it.

   if(SHFSYSTST_ENABLE_COVERAGE)

      set(SHFSYSTST_COVERAGE_DIR ${CMAKE_BINARY_DIR}/coverage CACHE STRING "Directory for coverage files" FORCE)
      execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${SHFSYSTST_COVERAGE_DIR})

      #
      # Set some variables for the Intel coverage utilities.
      # $$TODO: Linux only for now -- hook up for Windows as well if we pursue 
      # support for Intel.
      #
      if(SHFSYSTST_LINUX64INTEL)

         set(UNCOVERED_COLOR DE0829 CACHE STRING "Color for uncovered code.")
         set(COVERED_COLOR 319A44 CACHE STRING "Color for covered code.")
         set(PARTIAL_COLOR E1EA43 CACHE STRING "Color for partially covered code.")

         # Lop the compiler name off the end of the CXX string

         string(REPLACE "/icpc" "" INTELPATH ${CMAKE_CXX_COMPILER})

         # The codecov executable

         set(CODECOV "${INTELPATH}/bin/codecov" CACHE STRING "Intel Code coverage utility.")

         # The profmerge executable

         set(PROFMERGE "${INTELPATH}/bin/profmerge" CACHE STRING "Intel dynamic profile merge utility." )

         # The compiler library path.

         set(INTEL_LIBPATH "${INTELPATH}/lib/intel64" CACHE STRING "Intel C++ compiler library path." )

      elseif(SHFSYSTST_LINUX64GNU)

         # Lop the compiler name off the end of the CXX string to get the gnu root.

         string(REPLACE "bin/g++" "" GNUPATH ${CMAKE_CXX_COMPILER})

         # The compiler library path.

         set(GNU_LIBPATH "${GNUPATH}lib64" CACHE STRING "GNU C++ compiler library path." )

      endif(SHFSYSTST_LINUX64INTEL)

   endif(SHFSYSTST_ENABLE_COVERAGE)

   # Postconditions

   dbc_ensure_implies(SHFSYSTST_ENABLE_COVERAGE SHFSYSTST_COVERAGE_DIR)

endfunction(ShfSysTst_set_coverage_defaults)


#
# Create the build output directories.
#
function(ShfSysTst_create_output_dirs)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body:

   # Create directory for scoped header files.

   file(MAKE_DIRECTORY ${SHFSYSTST_HEADER_DIR})

   # Create directory for documentation files.

   file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/documentation)
   
   # Visual Studio will generate cmake_build_dir folders for the current build type.
   # Linux needs to be told.

   if(SHFSYSTST_WINDOWS)

      set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib PARENT_SCOPE)
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib PARENT_SCOPE)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin PARENT_SCOPE)

      # Create build/lib for libraries.

      file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

      # Create build/bin for executables.

      file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)        

   elseif(SHFSYSTST_LINUX)

      set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib PARENT_SCOPE)
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib PARENT_SCOPE)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin PARENT_SCOPE)
      
      # Create build/lib for libraries.

      file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
      
      # Create build/bin for executables.

      file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)        

   endif(SHFSYSTST_WINDOWS)

endfunction(ShfSysTst_create_output_dirs)

#
# Adds components to the system.
#
function(ShfSysTst_add_components)

   set(lcomponents sheaves_test fiber_bundles_test geometry_test fields_test tools_test)

   foreach(comp ${lcomponents})
      add_subdirectory(${comp})
   endforeach()

endfunction(ShfSysTst_add_components)

#
# Set the compiler flags per build configuration
#
function(ShfSysTst_set_compiler_flags)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body:
   
   # Toggle multi-process compilation in Windows

   if(SHFSYSTST_ENABLE_WIN32_MP)
      set(MP "/MP")
   else()
      set(MP "")
   endif()
   
   if(SHFSYSTST_WIN64MSVC)

      # Windows with MS Visual C++ compiler.

      set(SHFSYSTST_CXX_FLAGS "${MP} /GR /nologo /DWIN32 /D_WINDOWS /W1 /EHsc /wd4251" 
         CACHE STRING "C++ Compiler Flags")

      set(SHFSYSTST_SHARED_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /MACHINE:X64"
         CACHE STRING "Linker Flags for Shared Libs")

      set(SHFSYSTST_EXE_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /SUBSYSTEM:CONSOLE /MACHINE:X64" 
         CACHE STRING "Linker Flags for Executables")

      set(SHFSYSTST_EXE_LINKER_FLAGS_DEBUG "/DEBUG" CACHE STRING "Debug Linker Flags")

   elseif(SHFSYSTST_WIN64INTEL)

      # Windows with Intel compiler.

      set(SHFSYSTST_CXX_FLAGS "/D_USRDLL ${MP} /GR /nologo /DWIN32 /D_WINDOWS /W1 /wd2651 /EHsc /Qprof-gen:srcpos /D_HDF5USEDLL_" 
         CACHE STRING "C++ Compiler Flags")

      set(SHFSYSTST_SHARED_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /NXCOMPAT /MACHINE:X64" 
         CACHE STRING "Linker Flags") 

      set(SHFSYSTST_EXE_LINKER_FLAGS CACHE STRING "Linker Flags for Executables")

      set(SHFSYSTST_EXE_LINKER_FLAGS_DEBUG CACHE STRING "Debug Linker Flags" )

   elseif(SHFSYSTST_LINUX64INTEL)

      # Linux with Intel compiler.

      if(SHFSYSTST_ENABLE_COVERAGE)
         if(INTELWARN)
            set(SHFSYSTST_CXX_FLAGS "-ansi -m64 -w1 -wd186,1125 -Wno-deprecated -prof-gen=srcpos")
         else()
            set(SHFSYSTST_CXX_FLAGS "-ansi -m64 -w0 -Wno-deprecated  -prof-gen=srcpos")
         endif()
      else()
         if(INTELWARN)
            set(SHFSYSTST_CXX_FLAGS "-ansi -m64 -w1 -wd186,1125 -Wno-deprecated ")
         else()
            set(SHFSYSTST_CXX_FLAGS "-ansi -m64 -w0 -Wno-deprecated ")
         endif()
      endif(SHFSYSTST_ENABLE_COVERAGE)

      set(SHFSYSTST_SHARED_LINKER_FLAGS CACHE STRING "Linker Flags") 

      set(SHFSYSTST_EXE_LINKER_FLAGS CACHE STRING "Linker Flags for Executables")

      set(SHFSYSTST_EXE_LINKER_FLAGS_DEBUG CACHE STRING "Debug Linker Flags" )
        
   elseif(SHFSYSTST_LINUX64GNU)

      # Linux with g++ compiler.

      # 12/20/13 -- added "-Wno-abi to suppress the following:
      #"SheafSystem/sheaves/support/primitive_attributes.h:115: 
      #note: The ABI of passing union with long double has changed in GCC 4.4"
      # The probrem is still there; we have only suppressed the warning.

      set(SHFSYSTST_CXX_FLAGS "-std=c++11 -m64 -Wno-deprecated -Wno-abi") 

      set(SHFSYSTST_SHARED_LINKER_FLAGS CACHE STRING "Linker Flags") 

      set(SHFSYSTST_EXE_LINKER_FLAGS CACHE STRING "Linker Flags for Executables")

      set(SHFSYSTST_EXE_LINKER_FLAGS_DEBUG CACHE STRING "Debug Linker Flags" )

   endif()

   mark_as_advanced(FORCE SHFSYSTST_CXX_FLAGS)
   mark_as_advanced(FORCE SHFSYSTST_SHARED_LINKER_FLAGS)
   mark_as_advanced(FORCE SHFSYSTST_EXE_LINKER_FLAGS)
   mark_as_advanced(FORCE SHFSYSTST_EXE_LINKER_FLAGS_DEBUG)
   
   # Configuration specific flags 

   #                 
   # DEBUG_CONTRACTS section
   #

   if(SHFSYSTST_WINDOWS)

      set(CMAKE_CXX_FLAGS_DEBUG_CONTRACTS "${SHFSYSTST_CXX_FLAGS} /Zi /D\"_ITERATOR_DEBUG_LEVEL=2\" /MDd /LDd /Od " 
         CACHE STRING "Flags used by the C++ compiler for Debug_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} /DEBUG /NODEFAULTLIB:MSVCRT" 
         CACHE STRING "Flags used by the linker for shared libraries for Debug_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for Debug_contracts builds" FORCE)

      set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Debug_contracts linker flags - binding libs" )

   elseif(SHFSYSTST_LINUX) 

      set(CMAKE_CXX_FLAGS_DEBUG_CONTRACTS "${SHFSYSTST_CXX_FLAGS} -g " 
         CACHE STRING "Flags used by the C++ compiler for Debug_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Debug_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS ${CMAKE_EXE_LINKER_FLAGS}  
         CACHE STRING "Flags used by the linker for executables for Debug_contracts builds")

      set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Debug_contracts linker flags - binding libs" )

   endif(SHFSYSTST_WINDOWS)
   
   mark_as_advanced(FORCE 
      CMAKE_CXX_FLAGS_DEBUG_CONTRACTS
      CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS 
      CMAKE_SHARED_LINKER_FLAGS_DEBUG_CONTRACTS
      CMAKE_MODULE_LINKER_FLAGS_DEBUG_CONTRACTS)

   #                 
   # DEBUG_NO_CONTRACTS section
   #      

   if(SHFSYSTST_WINDOWS)

      set(CMAKE_CXX_FLAGS_DEBUG_NO_CONTRACTS "${SHFSYSTST_CXX_FLAGS} /Zi /D\"_ITERATOR_DEBUG_LEVEL=2\" /MDd /LDd /Od /DNDEBUG " 
         CACHE STRING "Flags used by the C++ compiler for Debug_no_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} /DEBUG /NODEFAULTLIB:MSVCRT" 
         CACHE STRING "Flags used by the linker for shared libraries for Debug_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for Debug_no_contracts builds" FORCE)

      set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Debug_no_contracts linker flags - binding libs" )

   elseif(SHFSYSTST_LINUX)

      set(CMAKE_CXX_FLAGS_DEBUG_NO_CONTRACTS "${SHFSYSTST_CXX_FLAGS} -g -DNDEBUG" 
         CACHE STRING "Flags used by the C++ compiler for Debug_no_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Debug_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for Debug_no_contracts builds" FORCE)

      set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Debug_no_contracts linker flags - binding libs" )

   endif(SHFSYSTST_WINDOWS)

   mark_as_advanced(FORCE 
      CMAKE_CXX_FLAGS_DEBUG_NO_CONTRACTS
      CMAKE_EXE_LINKER_FLAGS_DEBUG_NO_CONTRACTS 
      CMAKE_SHARED_LINKER_FLAGS_DEBUG_NO_CONTRACTS
      CMAKE_MODULE_LINKER_FLAGS_DEBUG_NO_CONTRACTS)
   
   #                 
   # RELEASE_CONTRACTS section
   #

   if(SHFSYSTST_WINDOWS)

      set(CMAKE_CXX_FLAGS_RELEASE_CONTRACTS "${SHFSYSTST_CXX_FLAGS}  /MD /LD /O2 " 
         CACHE STRING "Flags used by the C++ compiler for Release_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_RELEASE_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD  /NXCOMPAT" 
         CACHE STRING "Flags used by the linker for executables for Release_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Release_contracts builds" )

      set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Release_contracts linker flags - binding libs" )

   elseif(SHFSYSTST_LINUX)

      set(CMAKE_CXX_FLAGS_RELEASE_CONTRACTS "${SHFSYSTST_CXX_FLAGS} " 
         CACHE STRING "Flags used by the C++ compiler for Release_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_RELEASE_CONTRACTS "${SHFSYSTST_EXE_LINKER_FLAGS}"  
         CACHE STRING "Flags used by the linker for executables for Release_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Release_contracts builds" )

      set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Release_contracts linker flags - binding libs" )

   endif(SHFSYSTST_WINDOWS)
   
   mark_as_advanced(FORCE 
      CMAKE_CXX_FLAGS_RELEASE_CONTRACTS
      CMAKE_EXE_LINKER_FLAGS_RELEASE_CONTRACTS 
      CMAKE_SHARED_LINKER_FLAGS_RELEASE_CONTRACTS
      CMAKE_MODULE_LINKER_FLAGS_RELEASE_CONTRACTS)
   
   #                 
   # RELEASE_NO_CONTRACTS section
   #

   if(SHFSYSTST_WINDOWS)

      set(CMAKE_CXX_FLAGS_RELEASE_NO_CONTRACTS "${SHFSYSTST_CXX_FLAGS}  /MD /LD /O2 /DNDEBUG" 
         CACHE STRING "Flags used by the C++ compiler for Release_no_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD  /NXCOMPAT" 
         CACHE STRING "Flags used by the linker for executables for Release_no_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Release_no_contracts builds" )

      set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Release_no_contracts linker flags - binding libs" )

   elseif(SHFSYSTST_LINUX)

      set(CMAKE_CXX_FLAGS_RELEASE_NO_CONTRACTS "${SHFSYSTST_CXX_FLAGS}  -DNDEBUG" 
         CACHE STRING "Flags used by the C++ compiler for Release_no_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for executables for Release_no_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Release_no_contracts builds" )

      set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Release_no_contracts linker flags - binding libs" )

   endif(SHFSYSTST_WINDOWS)
   
   mark_as_advanced(FORCE 
      CMAKE_CXX_FLAGS_RELEASE_NO_CONTRACTS
      CMAKE_EXE_LINKER_FLAGS_RELEASE_NO_CONTRACTS 
      CMAKE_SHARED_LINKER_FLAGS_RELEASE_NO_CONTRACTS
      CMAKE_MODULE_LINKER_FLAGS_RELEASE_NO_CONTRACTS)

   #                 
   # RelWithDebInfo_contracts section; Windows only.
   #

   if(SHFSYSTST_WINDOWS)

      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_CONTRACTS "${SHFSYSTST_CXX_FLAGS} /MD /LD /O2 " 
         CACHE STRING "RelWithDebInfo_contracts compiler flags" )

      set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS "${SHFSYSTST_EXE_LINKER_FLAGS} /DEBUG /NODEFAULTLIB:MSVCRTD  /NXCOMPAT"
         CACHE STRING "RelWithDebInfo_contracts linker flags - executables" )

      set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS  "${CMAKE_EXE_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for RelWithDebInfo_contracts builds" FORCE)

      set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "RelWithDebInfo_contracts linker flags - binding libs" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "RelWithDebInfo_contracts linker flags - shared libs" ) 
      
      mark_as_advanced(FORCE 
         CMAKE_CXX_FLAGS_RELWITHDEBINFO_CONTRACTS
         CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS 
         CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS
         CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS)

   endif(SHFSYSTST_WINDOWS)
   
   #                 
   # RelWithDebInfo_no_contracts section; Windows only.
   #

   if(SHFSYSTST_WINDOWS)

      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${SHFSYSTST_CXX_FLAGS} /MD /LD /O2 /DNDEBUG" CACHE
         STRING "RelWithDebInfo_no_contracts compiler flags" )

      set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS
         "${CMAKE_EXE_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for RelWithDebInfo_no_contracts builds"
         FORCE)

      set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "RelWithDebInfo_contracts linker flags - shared libs" ) 

      set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${SHFSYSTST_SHARED_LINKER_FLAGS} ${SHFSYSTST_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "RelWithDebInfo_contracts linker flags - binding libs" )
      
      mark_as_advanced(FORCE 
         CMAKE_CXX_FLAGS_RELWITHDEBINFO_NO_CONTRACTS
         CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS 
         CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS
         CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS)

   endif(SHFSYSTST_WINDOWS)
   
endfunction(ShfSysTst_set_compiler_flags)

# 
# Get the current system date and store it in RESULT
#
macro(get_date RESULT)
   if(WIN32)
      execute_process(COMMAND "cmd" " /C date /T" OUTPUT_VARIABLE ${RESULT})
      string(REGEX REPLACE "(..)/(..)/..(..).*" "\\1/\\2/\\3" ${RESULT} ${${RESULT}})
   elseif(UNIX)
      execute_process(COMMAND "date" "+%m/%d/%Y" OUTPUT_VARIABLE ${RESULT})
      string(REGEX REPLACE "(..)/(..)/..(..).*" "\\1/\\2/\\3" ${RESULT} ${${RESULT}})
   else(WIN32)
      message(WARNING "date not implemented")
      set(${RESULT} 000000)
   endif(WIN32)
endmacro(get_date)

function(ShfSysTst_make_system_definitions)

   ShfSysTst_set_system_variable_defaults()
   ShfSysTst_set_platform_variables()
   ShfSysTst_set_compiler_flags()
   ShfSysTst_set_debug_configuration()
   ShfSysTst_set_default_build_type()
   ShfSysTst_set_system_install_location_default()
   ShfSysTst_set_coverage_defaults()

   include(${SHFSYSTST_CMAKE_MODULE_PATH}/find_prerequisites.cmake)
   ShfSysTst_find_prerequisites()

endfunction(ShfSysTst_make_system_definitions)

# 
# Convenience wrapper for the message function.
# The Eclipse Cmakeed plugin renders this pretty much obsolete
# from a pregramming viewpoint, but the syntax is prettier
# than what it wraps.
#
function(ShfSysTst_status_message txt)

   # Let the user know what's being configured

   message(STATUS " ")
   message(STATUS "${txt} - ")
   message(STATUS " ")

#   message( " ")
#   message( "${txt} - ")
#   message( " ")

endfunction(ShfSysTst_status_message)

#
# Configures the set_env_var scripts.
#
function(ShfSysTst_configure_set_env_var_scripts)

   # Set the path to the SheafSytem lib directory; used by set_env_var scripts.

   set(SHEAFSYSTEM_LIB_DIR ${SHFSYSTST_SHEAFSYSTEM_ROOT}/${CMAKE_BUILD_TYPE}/lib
      CACHE STRING "Path to SheafSystem library directory" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_LIB_DIR)   

   configure_file(${SHFSYSTST_CMAKE_MODULE_PATH}/set_env_vars.csh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.csh)
   configure_file(${SHFSYSTST_CMAKE_MODULE_PATH}/set_env_vars.sh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.sh)
   
endfunction(ShfSysTst_configure_set_env_var_scripts)
