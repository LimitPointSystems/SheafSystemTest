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


#------------------------------------------------------------------------------ 
# Variable Definition Section
#------------------------------------------------------------------------------

include(CTest)

#
# Turn on project folders for Visual Studio.
#
if(WIN64MSVC OR WIN64INTEL)
    set_property(GLOBAL PROPERTY USE_FOLDERS On)
endif()

#
# Comvert the project name to UC
#
string(TOUPPER ${PROJECT_NAME} COMPONENT)

#
# Tell the linker where to look for COMPONENT libraries.
#
##TODO: This variable should be named "SHEAFSYSTEM_OUTPUT_DIR"
link_directories(${SHEAVES_LIB_OUTPUT_DIR})

#
# Set the location and name of the Intel coverage utilities
# Linux only for now.
#

if(LINUX64INTEL)

    set(UNCOVERED_COLOR DE0829 CACHE STRING "Color for uncovered code.")
    set(COVERED_COLOR 319A44 CACHE STRING "Color for covered code.")
    set(PARTIAL_COLOR E1EA43 CACHE STRING "Color for partially covered code.")
    # Lop the compiler name off the end of the CXX string
    string(REPLACE "/icpc" "" INTELPATH ${CMAKE_CXX_COMPILER})
    # The codecov executable
    set(CODECOV "${INTELPATH}/codecov" CACHE STRING "Intel Code coverage utility.")
    # The profmerge executable
    set(PROFMERGE "${INTELPATH}/profmerge" CACHE STRING "Intel dynamic profile merge utility." )
    set(CODECOV_ARGS -spi ${SHEAFSYSTEM_HOME}/build/coverage/pgopti.spi -bcolor ${UNCOVERED_COLOR} -ccolor ${COVERED_COLOR} -pcolor ${PARTIAL_COLOR} -demang -prj CACHE STRING "Arguments for Intel codecov utility.")
    set(INTEL_LIBPATH "${INTELPATH}/lib/intel64" CACHE STRING "Intel C++ compiler library path." )

elseif(LINUX64GNU)

    # Lop the compiler name off the end of the CXX string to get the gnu root.
    string(REPLACE "bin/g++" "" GNUPATH ${CMAKE_CXX_COMPILER})
    # The compiler library path.
    set(GNU_LIBPATH "${GNUPATH}lib64" CACHE STRING "GNU C++ compiler library path." )

endif()

#
# Toggle tests. Only effective in Windows.
# Enabling all tests types by default can create a really slow VS project.
# Toggle the test type(s) you need.
#
set(ENABLE_BIN_TARGETS OFF CACHE BOOL "Toggle inclusion of bin targets.")
set(ENABLE_UNIT_TEST_LOG_TARGETS OFF CACHE BOOL "Toggle inclusion of Unit Test log targets.")
set(ENABLE_UNIT_TEST_HDF_LOG_TARGETS OFF CACHE BOOL "Toggle inclusion of Unit Test hdf5 log targets.")

#
#------------------------------------------------------------------------------
# Function Definition Section.
#------------------------------------------------------------------------------

#
# Check for and configure system cxx includes.
#
function(check_cxx_includes)
   include(CheckIncludeFileCXX)

    # C++ Headers for C Library Facilities

    if(NOT HAVE_CASSERT)
        status_message("Looking for C++ Headers For C Library Functions")   
    endif()

    check_include_file_cxx(cassert HAVE_CASSERT)
    check_include_file_cxx(cctype HAVE_CCTYPE)
    check_include_file_cxx(cerrno HAVE_CERRNO)
    check_include_file_cxx(cfloat HAVE_CFLOAT)
    check_include_file_cxx(ciso646 HAVE_CISO646)
    check_include_file_cxx(climits HAVE_CLIMITS)
    check_include_file_cxx(clocale HAVE_CLOCALE)
    check_include_file_cxx(cmath HAVE_CMATH)
    check_include_file_cxx(csetjmp HAVE_CSETJMP)
    check_include_file_cxx(csignal HAVE_CSIGNAL)
    check_include_file_cxx(cstdarg HAVE_CSTDARG)
    check_include_file_cxx(cstddef HAVE_CSTDDEF)
    check_include_file_cxx(cstdio HAVE_CSTDIO)
    check_include_file_cxx(cstdlib HAVE_CSTDLIB)
    check_include_file_cxx(cstring HAVE_CSTRING)
    check_include_file_cxx(ctime HAVE_CTIME)
    check_include_file_cxx(cwchar HAVE_CWCHAR)
    check_include_file_cxx(cwctype HAVE_CWCTYPE)                        


    # C++ Library Headers

    if(NOT HAVE_ALGORITHM)
        status_message("Looking for C++ Standard Library Headers")    
    endif()

    check_include_file_cxx(algorithm HAVE_ALGORITHM)
    check_include_file_cxx(bitset HAVE_BITSET)
    check_include_file_cxx(complex HAVE_COMPLEX)    
    check_include_file_cxx(deque HAVE_DEQUE)
    check_include_file_cxx(exception HAVE_EXCEPTION)    
    check_include_file_cxx(fstream HAVE_FSTREAM)
    check_include_file_cxx(functional HAVE_FUNCTIONAL)
    check_include_file_cxx(iomanip HAVE_IOMANIP)
    check_include_file_cxx(ios HAVE_IOS)
    check_include_file_cxx(iosfwd HAVE_IOSFWD)
    check_include_file_cxx(iostream HAVE_IOSTREAM)
    check_include_file_cxx(iterator HAVE_ITERATOR)
    check_include_file_cxx(limits HAVE_LIMITS)
    check_include_file_cxx(list HAVE_LIST)
    check_include_file_cxx(locale HAVE_LOCALE)
    check_include_file_cxx(map HAVE_MAP)
    check_include_file_cxx(memory HAVE_MEMORY)
    check_include_file_cxx(new HAVE_NEW)
    check_include_file_cxx(numeric HAVE_NUMERIC)
    check_include_file_cxx(ostream HAVE_OSTREAM)
    check_include_file_cxx(queue HAVE_QUEUE)
    check_include_file_cxx(set HAVE_SET)
    check_include_file_cxx(sstream HAVE_SSTREAM)
    check_include_file_cxx(stack HAVE_STACK)
    check_include_file_cxx(stdexcept HAVE_STDEXCEPT)
    check_include_file_cxx(strtream HAVE_STRSTREAM)
    check_include_file_cxx(streambuf HAVE_STREAMBUF)
    check_include_file_cxx(string HAVE_STRING)
    check_include_file_cxx(typeinfo HAVE_TYPEINFO)
    check_include_file_cxx(utility HAVE_UTILITY)
    check_include_file_cxx(valarray HAVE_VALARRAY)
    check_include_file_cxx(vector HAVE_VECTOR)

    # STL

    if(NOT (HAVE_HASH_MAP OR HAVE_EXT_HASH_MAP))
        status_message("Looking for C++ STL Headers")
    endif()

    check_include_file_cxx(hash_map HAVE_HASH_MAP)
    check_include_file_cxx(ext/hash_map HAVE_EXT_HASH_MAP)
    check_include_file_cxx(hash_set HAVE_HASH_SET)
    check_include_file_cxx(ext/hash_set HAVE_EXT_HASH_SET)    
    check_include_file_cxx(slist HAVE_SLIST)
    check_include_file_cxx(ext/slist HAVE_EXT_SLIST)
    
    # C++ TR1 Extensions

    if(NOT (HAVE_UNORDERED_MAP OR HAVE_TR1_UNORDERED_MAP))
        status_message("Looking for C++ TR1 Headers") 
    endif()

    check_include_file_cxx(unordered_map HAVE_UNORDERED_MAP) 
    check_include_file_cxx(tr1/unordered_map HAVE_TR1_UNORDERED_MAP) 
    check_include_file_cxx(unordered_set HAVE_UNORDERED_SET)
    check_include_file_cxx(tr1/unordered_set HAVE_TR1_UNORDERED_SET)

endfunction(check_cxx_includes)


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
         set(LPS_CXX_FLAGS "-ansi -m64 -Wno-deprecated")            
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

#
# Create the build output directories.
#
function(create_output_dirs)
    if(WIN64MSVC OR WIN64INTEL)
        # Create build/include for STD header files.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
        # Create build/lib for libraries.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
        # Create build/bin for executables.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
        
        # These uber-verbose variable names have special meaning to cmake --
        # the cmake counterpart to what GNU autotools calls a "precious" variable.
        # Not a good idea to change them to anything shorter and sweeter; so don't.
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE PATH "Static/Import Library Output Directory")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE PATH "Shared Library Output Directory")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH "Binary Output Directory")
    else()
        # These uber-verbose variable names have special meaning to cmake --
        # the cmake counterpart to what GNU autotools calls a "precious" variable.
        # Not a good idea to change them to anything shorter and sweeter; so don't.
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE} CACHE PATH "Static/Import Library Output Directory")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE} CACHE PATH "Shared Library Output Directory")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} CACHE PATH "Binary Output Directory")
     
        # Create dir for static/import libraries.
        file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
        # Create dir for sheared libraries.
        file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
        # Create dir for executable output.
        file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endif()
endfunction()

# 
#  Append file types to CMake's default clean list.
#
function(add_clean_files)
    
    #Define the file types to be included in the clean operation.
    
    file(GLOB_RECURSE HDF_FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/*.hdf)
    file(GLOB_RECURSE CSV_FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/*.csv)
    
    if(ENABLE_COVERAGE)  
        # Clean up the mess left by the Intel coverage tool
        file(GLOB_RECURSE DYN_FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*.dyn)
        file(GLOB_RECURSE DPI_FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*.dpi)
        file(GLOB_RECURSE SPI_FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*.spi)
    endif()                

    # Append them to the list
    list(APPEND CLEAN_FILES ${HDF_FILES})
    list(APPEND CLEAN_FILES ${CSV_FILES})
      
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CLEAN_FILES}")

endfunction(add_clean_files) 

# 
# Establish a system level "bin" target
#
function(add_bin_target)

    add_custom_target(bin DEPENDS ${ALL_BIN_TARGETS})
    if(WIN64MSVC OR WIN64INTEL)
        set_target_properties(bin PROPERTIES FOLDER "Bin Targets")
    endif()
            
endfunction(add_bin_target)

#
# Add component specific bin targets. e.g., "sheaves-bin", "tools-bin", etc.
#
function(add_component_bin_target)

    if(WIN64MSVC OR WIN64INTEL)
        add_custom_target(${PROJECT_NAME}-bin DEPENDS ${${COMPONENT}_IMPORT_LIB} ${${COMPONENT}_UNIT_TESTS} ${${COMPONENT}_EXAMPLES})
        set_target_properties(${PROJECT_NAME}-bin PROPERTIES FOLDER "Bin Targets")
    else()
        add_custom_target(${PROJECT_NAME}-bin DEPENDS ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_UNIT_TESTS} ${${COMPONENT}_EXAMPLES})
    endif()
    # Add a bin target for this component to the system list. "make bin" will invoke this list.
    set(ALL_BIN_TARGETS ${ALL_BIN_TARGETS} ${PROJECT_NAME}-bin CACHE STRING "Aggregate list of component bin targets" FORCE)
    mark_as_advanced(ALL_BIN_TARGETS) 

endfunction(add_component_bin_target)

# 
# Establish a system level "check" target
#
function(add_check_target)

   if(WIN64MSVC OR WIN64INTEL)
        add_custom_target(check DEPENDS ${ALL_COMP_CHECK_TARGETS})
        set_target_properties(check PROPERTIES FOLDER "Check Targets")
    else()
       add_custom_target(check DEPENDS ${ALL_COMP_CHECK_TARGETS})
  endif()

endfunction(add_check_target)

#
# Add component specific check targets. e.g., "sheaves-check", "tools-check", etc.
#
function(add_component_check_target)

        add_custom_target(${PROJECT_NAME}-check)
        add_custom_command(TARGET ${PROJECT_NAME}-check POST_BUILD COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_CFG_INTDIR} -O ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.log)
        if(WIN64MSVC OR WIN64INTEL)       
            add_dependencies(${PROJECT_NAME}-check ${${COMPONENT}_IMPORT_LIB} ${${COMPONENT}_UNIT_TESTS})
            set_target_properties(${PROJECT_NAME}-check PROPERTIES FOLDER "Check Targets")
        else()
            add_dependencies(${PROJECT_NAME}-check ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_UNIT_TESTS})        
        endif()
 
    # Add a check target for this component to the system list. "make check" will invoke this list.
    set(ALL_UNIT_TEST_TARGETS ${ALL_UNIT_TEST_TARGETS} ${${COMPONENT}_UNIT_TESTS} CACHE STRING "Aggregate list of unit test targets" FORCE)
    set(ALL_COMP_CHECK_TARGETS ${ALL_COMP_CHECK_TARGETS} ${PROJECT_NAME}-check CACHE STRING "Aggregate list of component check targets" FORCE)
    mark_as_advanced(ALL_UNIT_TEST_TARGETS)
    mark_as_advanced(ALL_COMP_CHECK_TARGETS)
    
endfunction(add_component_check_target)

#
# Add component specific coverage targets. e.g., "sheaves-coverage", "tools-coverage", etc.
#
function(add_component_coverage_target)

       # if the component unit test list is not empty, generate coverage data.   
        if(NOT ${COMPONENT}_UNIT_TEST_SRCS MATCHES "")
            add_custom_target(${PROJECT_NAME}-coverage DEPENDS ${PROJECT_NAME}-check
                COMMAND ${CMAKE_COMMAND} -E chdir ${COVERAGE_DIR} ${PROFMERGE}
                COMMAND ${CMAKE_COMMAND} -E chdir ${COVERAGE_DIR} ${CODECOV} -comp ${CMAKE_BINARY_DIR}/coverage_files.lst ${CODECOV_ARGS} ${PROJECT_NAME}
                 )
        else()
            # Component has no unit tests associated with it, make target an "informational no-op"
            add_custom_target(${PROJECT_NAME}-coverage
                COMMAND ${CMAKE_COMMAND} -E echo " " 
                COMMAND ${CMAKE_COMMAND} -E echo "   There are currently no unit tests for the ${PROJECT_NAME} component. Coverage results will not be generated." 
                COMMAND ${CMAKE_COMMAND} -E echo " "                      
                )
        endif()
            # Append the coverage target to the system wide list
            set(ALL_COVERAGE_TARGETS ${ALL_COVERAGE_TARGETS} ${PROJECT_NAME}-coverage CACHE STRING "Aggregate list of component coverage targets" FORCE)
            mark_as_advanced(ALL_COVERAGE_TARGETS)
    set_target_properties(${PROJECT_NAME}-coverage PROPERTIES FOLDER "Component Coverage Targets")
    
endfunction()

# 
# Establish a system level "coverage" target
#
function(add_coverage_target)

    add_custom_target(coverage ALL DEPENDS check    
        COMMAND ${CMAKE_COMMAND} -E chdir ${COVERAGE_DIR} ${PROFMERGE}
        COMMAND ${CMAKE_COMMAND} -E chdir ${COVERAGE_DIR} ${CODECOV} -comp ${CMAKE_BINARY_DIR}/coverage_files.lst ${CODECOV_ARGS} ${PROJECT_NAME}   
    )
    
endfunction()

#
# Add component specific checklog targets. e.g., "sheaves-checklog", "tools-checklog", etc.
#
function(add_component_checklog_target)
    if(WIN64MSVC OR WIN64INTEL)
        add_custom_target(${PROJECT_NAME}-checklog DEPENDS ${${COMPONENT}_IMPORT_LIB} ${${COMPONENT}_LOGS})
        set_target_properties(${PROJECT_NAME}-checklog PROPERTIES FOLDER "Checklog Targets")
    else()
        add_custom_target(${PROJECT_NAME}-checklog DEPENDS ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_LOGS})
    endif()
    set(ALL_CHECKLOG_TARGETS ${ALL_CHECKLOG_TARGETS} ${${COMPONENT}_LOGS} CACHE STRING "Aggregate list of component checklog targets" FORCE)
    mark_as_advanced(ALL_CHECKLOG_TARGETS) 

endfunction(add_component_checklog_target)

# 
# Establish a system level "checklog" target
#
function(add_checklog_target)

    if(WIN64MSVC OR WIN64INTEL)
        add_custom_target(checklog COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_CFG_INTDIR} DEPENDS ${ALL_CHECKLOG_TARGETS})
        set_target_properties(checklog PROPERTIES FOLDER "Checklog Targets")
    else()
        add_custom_target(checklog COMMAND DEPENDS ${ALL_CHECKLOG_TARGETS})
    endif()

endfunction(add_checklog_target)

# 
# Create a cmake test for each unit test executable.
#
function(add_win32_test_targets)

    # Now get ctest's location
    get_filename_component(__TMP_DIR "${CMAKE_COMMAND}" PATH)
    set(CTEST_COMMAND "${__TMP_DIR}/ctest.exe" CACHE PATH "" FORCE)
    
    if(EXISTS ${HDF_INCLUDE_DIR})
        include_directories(${HDF_INCLUDE_DIR})
    endif()

    # link_directories only applies to targets created after it is called.
    link_directories(${${COMPONENT}_OUTPUT_DIR} ${SHEAVES_LIB_OUTPUT_DIR})

    # Let the user know what's being configured
    status_message("Configuring Unit Tests for ${PROJECT_NAME}")   
    
    foreach(t_cc_file ${${COMPONENT}_UNIT_TEST_SRCS})
        
        # Extract name of executable from source filename
        string(REPLACE .t.cc .t t_file_with_path ${t_cc_file})
        
        # Remove path information  
        get_filename_component(t_file ${t_file_with_path} NAME)
        
        set(${COMPONENT}_UNIT_TESTS ${${COMPONENT}_UNIT_TESTS} ${t_file} CACHE STRING "List of unit test binaries" FORCE)
        mark_as_advanced(${COMPONENT}_UNIT_TESTS)
        
        # If the target already exists, don't try to create it.
        if(NOT TARGET ${t_file})
             status_message("Creating ${t_file} from ${t_cc_file}")
             add_executable(${t_file} ${t_cc_file})

            # Supply the *_DLL_IMPORTS directive to preprocessor
            set_target_properties(${t_file} PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")
            add_dependencies(${t_file} ${${COMPONENT}_IMPORT_LIBS})

            #
            # unit_test.hdf.log -> unit_test.hdf -> unit_test.log -> unit_test
            #
            target_link_libraries(${t_file} ${${COMPONENT}_IMPORT_LIBS})                                         

            add_test(NAME ${t_file} WORKING_DIRECTORY $<TARGET_FILE_DIR:${t_file}> COMMAND $<TARGET_FILE:${t_file}> )
            
            #
            # Get the location of the SheafSystem Lib dir from the sheaves export info;
            # specifically the sheaves lib target.
            # TODO: We should probably be exporting this info explicitly in the SS exports file.
            #
            get_target_property(SS_DC_LIB_LOC sheaves IMPORTED_LOCATION_DEBUG_CONTRACTS)
            get_filename_component(SS_DC_LIB_PATH "${SS_DC_LIB_LOC}" PATH)
            get_target_property(SS_RWDI_LIB_LOC sheaves IMPORTED_LOCATION_RELWITHDEBINFO_NO_CONTRACTS)
            get_filename_component(SS_RWDI_LIB_PATH "${SS_RWDI_LIB_LOC}" PATH)                
            # Having both directories (DC and RNC) in the path is no problem. Cmake knows what it's looking for.
            set(TESTPATH "PATH=$ENV{PATH};${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE};${SS_DC_LIB_PATH};${SS_RWDI_LIB_PATH}")
            # Unfortunately, Windows uses the semicolon as a path delimiter, but the semicolon has special meaning to Cmake as well. Escape the semicolons in the PATH so cmake
            # doesn't see them as list item separators.
            string(REPLACE ";" "\\;" TESTPATH "${TESTPATH}")
			file(TO_NATIVE_PATH "${TESTPATH}" TESTPATH)
            set_tests_properties(${t_file} PROPERTIES ENVIRONMENT "${TESTPATH}")
            # Insert the unit tests into the VS folder "unit test targets"
            set_target_properties(${t_file} PROPERTIES FOLDER "Unit Test Targets/Executables")
            # Tag the test with the name of the current component.
            set_property(TEST ${t_file} PROPERTY LABELS "${PROJECT_NAME}")

            if(ENABLE_UNIT_TEST_LOG_TARGETS)
                # Generate a log file for each .t. "make <test>.log will build and run a given executable.
                add_custom_target(${t_file}.exe.log)
                add_custom_command(TARGET ${t_file}.exe.log POST_BUILD COMMAND ${CTEST_COMMAND} -C ${PROJECT_NAME} -R "^${t_file}$" WORKING_DIRECTORY ${OUTDIR})
               # Insert the unit tests into the VS folder "unit test targets"
               set_target_properties(${t_file}.exe.log PROPERTIES FOLDER "Unit Test Targets/Log Targets")
            endif(ENABLE_UNIT_TEST_LOG_TARGETS)
              
            if(ENABLE_UNIT_TEST_HDF_LOG_TARGETS)
                # Generate a log file for each .t.hdf "make <test>.hdf will build and run a given executable.
                add_custom_target(${t_file}.exe.hdf DEPENDS ${t_file}.exe.log WORKING_DIRECTORY ${OUTDIR})
                # Insert the unit tests into the VS folder "Unit Test HDF Targets"
                set_target_properties(${t_file}.exe.hdf PROPERTIES FOLDER "Unit Test Targets/HDF Targets")

                # Find out what component $t_file belongs to, and create the appropriate hdf log target type
                get_property(PROJ_MEMBER TEST ${t_file} PROPERTY LABELS)
                                            
                if(${PROJ_MEMBER} MATCHES "sheaves_test")
                    # Generate a log file for each .t.hdf "make <test>.hdf will build and run a given executable.
                    add_custom_target(${t_file}.exe.hdf.log DEPENDS sheaves_read ${t_file}.exe.hdf WORKING_DIRECTORY ${OUTDIR})
                    # Insert the target into the VS folder "Unit Test HDF Log Targets"
                    set_target_properties(${t_file}.exe.hdf.log PROPERTIES FOLDER "Unit Test Targets/HDF Log Targets")
                    add_custom_command(TARGET ${t_file}.exe.hdf.log WORKING_DIRECTORY ${OUTDIR}
                    POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Reading ${t_file}.exe.hdf ... "
                       COMMAND ${OUTDIR}/sheaves_read.exe ${t_file}.exe.hdf > ${t_file}.exe.hdf.log
                    )
                elseif(${PROJ_MEMBER} MATCHES "fiber_bundles_test")
                    # Generate a log file for each .t.hdf "make <test>.hdf will build and run a given executable.
                    add_custom_target(${t_file}.exe.hdf.log DEPENDS fiber_bundles_read ${t_file}.exe.hdf WORKING_DIRECTORY ${OUTDIR})
                    # Insert the target into the VS folder "Unit Test HDF Log Targets"
                    set_target_properties(${t_file}.exe.hdf.log PROPERTIES FOLDER "Unit Test Targets/HDF Log Targets")
                    add_custom_command(TARGET ${t_file}.exe.hdf.log WORKING_DIRECTORY ${OUTDIR}
                    POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Reading ${t_file}.exe.hdf ... "
                       COMMAND ${OUTDIR}/fiber_bundles_read.exe ${t_file}.exe.hdf > ${t_file}.exe.hdf.log
                    )                                             
                endif()                
            endif(ENABLE_UNIT_TEST_HDF_LOG_TARGETS)                                         
        endif()
    endforeach()
endfunction(add_win32_test_targets)

# 
# Create a cmake test for each unit test executable.
#
function(add_linux_test_targets)
    
    # link_directories only applies to targets created after it is called.
    link_directories(${${COMPONENT}_OUTPUT_DIR} ${SHEAVES_LIB_OUTPUT_DIR})
    
    # Let the user know what's being configured
    status_message("Configuring Unit Tests for ${PROJECT_NAME}")   
    
    foreach(t_cc_file ${${COMPONENT}_UNIT_TEST_SRCS})
        # Extract name of executable from source filename
        string(REPLACE .t.cc .t t_file_with_path ${t_cc_file})
        # Remove path information  
        get_filename_component(t_file ${t_file_with_path} NAME)
        set(${COMPONENT}_UNIT_TESTS ${${COMPONENT}_UNIT_TESTS} ${t_file} CACHE STRING "List of unit test binaries" FORCE)
        mark_as_advanced(${COMPONENT}_UNIT_TESTS)
        # If the target already exists, don't try to create it.
        if(NOT TARGET ${t_file})
             status_message("Creating ${t_file} from ${t_cc_file}")
             add_executable(${t_file} ${t_cc_file})

            # Make sure the library is up to date
            add_dependencies(${t_file} ${${COMPONENT}_SHARED_LIBS})
            target_link_libraries(${t_file} ${${COMPONENT}_SHARED_LIBS})
            
            # Add a test target for ${t_file}
            add_test(NAME ${t_file} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND $<TARGET_FILE:${t_file}>)

            # Tag the test with the name of the current component. Query the test for component membership by getting labels property.
            set_property(TEST ${t_file} PROPERTY LABELS "${PROJECT_NAME}") 

            # Set the PATH variable for CTest               
             set_tests_properties(${t_file} PROPERTIES ENVIRONMENT "PATH=%PATH%;${CMAKE_CFG_INTDIR};${SHEAVES_BIN_DIR}")   
     
            if(ENABLE_UNIT_TEST_LOG_TARGETS)   
                # Generate a log file for each .t. "make <test>.log will build and run a given executable.
                add_custom_target(${t_file}.log WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND ${t_file} > ${t_file}.log DEPENDS ${t_file} )
    
                # Insert the unit tests into the VS folder "unit test targets"
                set_target_properties(${t_file}.log PROPERTIES FOLDER "Unit Test Log Targets")
         
                # Note that this var should be named component_test_logs, but the components are named x_test. Not pretty.
                set(${COMPONENT}_LOGS ${${COMPONENT}_LOGS} ${t_file}.log CACHE STRING "List of unit test log targets" FORCE)
                mark_as_advanced(${COMPONENT}_LOGS)
            endif(ENABLE_UNIT_TEST_LOG_TARGETS)                                               
            
            if(ENABLE_UNIT_TEST_HDF_LOG_TARGETS)
                # Generate a log file for each .t.hdf "make <test>.hdf will build and run a given executable.
                add_custom_target(${t_file}.hdf DEPENDS ${t_file}.log )
     
                    # Insert the unit tests into the VS folder "Unit Test HDF Targets"
                set_target_properties(${t_file}.hdf PROPERTIES FOLDER "Unit Test HDF Targets")
                
                # Find out what component $t_file belongs to, and create the appropriate hdf log target type
                get_property(PROJ_MEMBER TEST ${t_file} PROPERTY LABELS)
                                                
                if(${PROJ_MEMBER} MATCHES "sheaves_test")
                    # Generate a log file for each .t.hdf "make <test>.hdf will build and run a given executable.
                    add_custom_target(${t_file}.hdf.log  DEPENDS sheaves_read ${t_file}.hdf WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
                    # Insert the target into the VS folder "Unit Test HDF Log Targets"
                    set_target_properties(${t_file}.hdf.log PROPERTIES FOLDER "Unit Test HDF Log Targets")
                    add_custom_command(TARGET ${t_file}.hdf.log WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                    POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Reading ${t_file}.hdf ... "
                       COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sheaves_read ${t_file}.hdf > ${t_file}.hdf.log
                    )
                elseif(${PROJ_MEMBER} MATCHES "fiber_bundles_test")
                    # Generate a log file for each .t.hdf "make <test>.hdf will build and run a given executable.
                    add_custom_target(${t_file}.hdf.log  DEPENDS fiber_bundles_read ${t_file}.hdf WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
                    # Insert the target into the VS folder "Unit Test HDF Log Targets"
                    set_target_properties(${t_file}.hdf.log PROPERTIES FOLDER "Unit Test HDF Log Targets")
                    add_custom_command(TARGET ${t_file}.hdf.log WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                    POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Reading ${t_file}.hdf ... "
                       COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fiber_bundles_read ${t_file}.hdf > ${t_file}.hdf.log
                    )                                             
                endif()
            endif(ENABLE_UNIT_TEST_HDF_LOG_TARGETS)            
            if(ENABLE_COVERAGE)
                # Create file-scope coverage target.
                add_custom_target(${t_file}.cov DEPENDS ${t_file}.log
                    COMMAND ${CMAKE_COMMAND} -E chdir ${COVERAGE_DIR} ${PROFMERGE}
                    COMMAND ${CMAKE_COMMAND} -E chdir ${COVERAGE_DIR} ${CODECOV} -comp ${CMAKE_BINARY_DIR}/coverage_files.lst ${CODECOV_ARGS} ${t_file} 
                    )               
            endif(ENABLE_COVERAGE)
        endif(NOT TARGET ${t_file})
    endforeach()

endfunction(add_linux_test_targets)

# 
# Create a target for each example.
#
function(add_example_targets)
# $$TODO: Decompose into OS specific routines as test_tagets above.
    foreach(t_cc_file ${${COMPONENT}_EXAMPLE_SRCS})
        # link_directories only applies to targets created after it is called.
        if(LINUX64GNU OR LINUX64INTEL)
            link_directories(${${COMPONENT}_OUTPUT_DIR} ${SHEAVES_LIB_OUTPUT_DIR})
        else()
            link_directories(${${COMPONENT}_OUTPUT_DIR}/${CMAKE_BUILD_TYPE} ${SHEAVES_LIB_OUTPUT_DIR})
        endif()    
        # Let the user know what's being configured
        status_message("Configuring example executables for ${PROJECT_NAME}")   
        # Deduce name of executable from source filename
        string(REPLACE .cc "" t_file_with_path ${t_cc_file})
        # Remove path information so the executable goes into build/bin (or build/VisualStudio)
        # and not into build/bin/examples (or build/VisualStudio/examples)
        get_filename_component(t_file ${t_file_with_path} NAME)
        set(${COMPONENT}_EXAMPLES ${${COMPONENT}_EXAMPLES} ${t_file} CACHE STRING "List of example binaries" FORCE)
        
        mark_as_advanced(${COMPONENT}_EXAMPLES)    
        # Add building of executable and link with shared library
        status_message("Creating ${t_file} from ${t_cc_file}")
        add_executable(${t_file} ${t_cc_file})
    
        # Make sure the library is up to date
        if(WIN64MSVC OR WIN64INTEL)
            add_dependencies(${t_file} ${${COMPONENT}_IMPORT_LIBS})
            target_link_libraries(${t_file} ${${COMPONENT}_IMPORT_LIBS})
            # Insert the unit tests into the VS folder "unit_tests"
            set_target_properties(${t_file} PROPERTIES FOLDER "Example Targets")
        else()
           add_dependencies(${t_file} ${${COMPONENT}_SHARED_LIBS})
           target_link_libraries(${t_file} ${${COMPONENT}_SHARED_LIBS})
        endif()
    
        # Supply the *_DLL_IMPORTS directive to preprocessor
        set_target_properties(${t_file} PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")
    
    endforeach()

endfunction(add_example_targets)

#
# Add the list of clusters to this component.
#
function(add_clusters clusters)

    foreach(cluster ${clusters})
        #Add each cluster subdir to the project. 
        add_subdirectory(${cluster})
        # Add the fully-qualified cluster names to this component's ipath var
        set(${COMPONENT}_IPATH ${${COMPONENT}_IPATH} ${CMAKE_CURRENT_SOURCE_DIR}/${cluster} CACHE STRING "test" FORCE)
    endforeach()

endfunction(add_clusters)

# 
# Declare and initialize all variables that are component-specific.
#
function(set_component_vars)

    if(WIN64MSVC OR WIN64INTEL)
        set(${COMPONENT}_DYNAMIC_LIB ${PROJECT_NAME} CACHE STRING "${PROJECT_NAME} dynamic link library")
        set(${COMPONENT}_IMPORT_LIB ${PROJECT_NAME} CACHE STRING "${PROJECT_NAME} import library")
    else()
        set(${COMPONENT}_SHARED_LIB lib${PROJECT_NAME}.so CACHE STRING "${PROJECT_NAME} shared library")
        set(${COMPONENT}_STATIC_LIB lib${PROJECT_NAME}.a CACHE STRING "${PROJECT_NAME} static library")
    endif()

    set(${COMPONENT}_COMMON_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/src CACHE STRING "${PROJECT_NAME} common binding source directory")
    set(${COMPONENT}_SWIG_COMMON_INTERFACE ${PROJECT_NAME}_common_binding.i CACHE STRING "${PROJECT_NAME} common interface filename")
    set(${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE ${PROJECT_NAME}_common_binding_includes.i CACHE STRING "${PROJECT_NAME} common includes interface filename" )
      
    set(${COMPONENT}_JAVA_BINDING_LIB ${PROJECT_NAME}_java_binding CACHE STRING "${PROJECT_NAME} java binding library basename")
    set(${COMPONENT}_JAVA_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/java/src CACHE STRING "${PROJECT_NAME} java binding source directory")
    set(${COMPONENT}_SWIG_JAVA_INTERFACE ${PROJECT_NAME}_java_binding.i CACHE STRING "${PROJECT_NAME} java binding interface file")

    set(${COMPONENT}_JAVA_BINDING_JAR ${PROJECT_NAME}_java_binding.jar CACHE STRING "${PROJECT_NAME} java binding jar name")
    
    set(${COMPONENT}_PYTHON_BINDING_LIB _${PROJECT_NAME}_python_binding CACHE STRING "${PROJECT_NAME} python binding library name")
    set(${COMPONENT}_PYTHON_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/python/src CACHE STRING "${PROJECT_NAME} python source directory")
    set(${COMPONENT}_SWIG_PYTHON_INTERFACE ${PROJECT_NAME}_python_binding.i CACHE STRING "${PROJECT_NAME} python binding interface file")

    # Mark all the above as "advanced"
    mark_as_advanced(FORCE ${COMPONENT}_BINARY_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_LIB_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_DYNAMIC_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_IMPORT_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_SHARED_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_STATIC_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_COMMON_BINDING_SRC_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_COMMON_INTERFACE)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE)
    mark_as_advanced(FORCE ${COMPONENT}_JAVA_BINDING_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_JAVA_BINDING_SRC_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_JAVA_INTERFACE)
    mark_as_advanced(FORCE ${COMPONENT}_JAVA_BINDING_JAR)
    mark_as_advanced(FORCE ${COMPONENT}_PYTHON_BINDING_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_PYTHON_BINDING_SRC_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_PYTHON_INTERFACE)

endfunction(set_component_vars)

#
# Export this component's library targets and list of includes
#
function(export_targets)

    status_message("Writing ${PROJECT_NAME} detail to ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}")
    if(WIN64MSVC OR WIN64INTEL)
        export(TARGETS ${${COMPONENT}_DYNAMIC_LIB} APPEND FILE ${CMAKE_BINARY_DIR}/${EXPORTS_FILE})
    else()
        export(TARGETS ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_STATIC_LIB} APPEND FILE ${CMAKE_BINARY_DIR}/${EXPORTS_FILE})
    endif()
    file(APPEND  ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_INCS ${${COMPONENT}_INCS} CACHE STRING \"${PROJECT_NAME} includes\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_IPATH ${${COMPONENT}_IPATH} CACHE STRING \"${PROJECT_NAME} include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_CLASSPATH ${${COMPONENT}_CLASSPATH} CACHE STRING \"${PROJECT_NAME} Java classpath\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_BIN_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} binary output directory\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_LIB_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} library output directory\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")

endfunction(export_targets)

#
# Append sources to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(collect_sources)

    # Prepend the cluster name to each member of the srcs list
    foreach(src ${SRCS})
        list(APPEND lsrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    endforeach()
        
    set(${COMPONENT}_SRCS ${${COMPONENT}_SRCS} ${lsrcs} CACHE STRING "${PROJECT} sources." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_SRCS)

endfunction()

#
# Append incs to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(collect_includes)

    # Prepend the cluster name to each member of the srcs list
    foreach(src ${SRCS})
        string(REGEX REPLACE ".cc$" ".h"  inc ${src})
        list(APPEND lincs ${CMAKE_CURRENT_SOURCE_DIR}/${inc})
    endforeach()

    # Prepend the cluster name to each member of the additional_incs list
    foreach(inc ${ADDITIONAL_INCS})
        list(APPEND lincs ${CMAKE_CURRENT_SOURCE_DIR}/${inc})
    endforeach()

    set(${COMPONENT}_INCS ${${COMPONENT}_INCS} ${lincs} CACHE STRING "${PROJECT} includes." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_INCS)

endfunction(collect_includes)

#
# Append unit test executables to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(collect_unit_test_sources)

    # Prepend the path to each member of the check_execs list
    foreach(src ${UNIT_TEST_SRCS})
        list(APPEND chksrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    endforeach()
    
    set(${COMPONENT}_UNIT_TEST_SRCS ${${COMPONENT}_UNIT_TEST_SRCS} ${chksrcs} CACHE STRING "Unit test sources." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_UNIT_TEST_SRCS)
    
endfunction(collect_unit_test_sources)

#
# Append standalone executables to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(collect_example_sources)

    # Prepend the path to each member of the execs list
    foreach(src ${EXAMPLE_SRCS})
        list(APPEND execsrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    endforeach()

    set(${COMPONENT}_EXAMPLE_SRCS ${${COMPONENT}_EXAMPLE_SRCS} ${execsrcs} CACHE STRING "EXEC sources." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_EXAMPLE_SRCS)

endfunction(collect_example_sources)

# 
# Convenience routine for diagnostic output during configure phase.
# Variable of interest goes between the double quotes
#
function(status_message txt)

    message(STATUS " ")
    message(STATUS "${txt} - ")
    message(STATUS " ")

endfunction()

# 
# Convenience routine for diagnostic output during configure phase.
# Displays list of included directories for module in which it is called.
#
function(showincs)
    status_message("Displaying include directories for ${PROJECT_NAME}:")
   status_message("===================================================")    
    get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    foreach(dir ${dirs})
        message(STATUS "dir='${dir}'")
    endforeach() 
    status_message("===================================================")       
endfunction()
  

