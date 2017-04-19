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
# Functions called from <component>/CMakeLists.txt.
#------------------------------------------------------------------------------

# 
# Declare and initialize all variables that are component-specific.
#
function(ShfSysTst_set_component_variables xcomponent_name)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body:

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   # Source collection variables.

   set(${LCOMP_NAME_UC}_SRCS CACHE STRING "${lcomp_name_lc} sources" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SRCS)

   set(${LCOMP_NAME_UC}_INCS CACHE STRING "${lcomp_name_lc} includes" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_INCS)

   set(${LCOMP_NAME_UC}_UNIT_TEST_SRCS CACHE STRING "${lcomp_name_lc} unit test sources" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_UNIT_TEST_SRCS)

   set(${LCOMP_NAME_UC}_EXAMPLE_SRCS CACHE STRING "${lcomp_name_lc} example sources" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_EXAMPLE_SRCS)

   # Library variables.

   if(SHFSYSTST_WINDOWS)

      set(${LCOMP_NAME_UC}_DYNAMIC_LIB ${lcomp_name_lc} 
         CACHE STRING "${lcomp_name_lc} dynamic link library")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_DYNAMIC_LIB)

      set(${LCOMP_NAME_UC}_IMPORT_LIB ${lcomp_name_lc} 
         CACHE STRING "${lcomp_name_lc} import library")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_IMPORT_LIB)

   elseif(SHFSYSTST_LINUX)

      set(${LCOMP_NAME_UC}_SHARED_LIB lib${lcomp_name_lc}.so 
         CACHE STRING "${lcomp_name_lc} shared library")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SHARED_LIB)

      set(${LCOMP_NAME_UC}_STATIC_LIB lib${lcomp_name_lc}.a 
         CACHE STRING "${lcomp_name_lc} static library")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_STATIC_LIB)

   endif(SHFSYSTST_WINDOWS)

   # Executable variables

   set(${LCOMP_NAME_UC}_UNIT_TESTS CACHE STRING "List of unit test binaries" FORCE)
   mark_as_advanced(${LCOMP_NAME_UC}_UNIT_TESTS)

   set(${LCOMP_NAME_UC}_EXAMPLES CACHE STRING "List of example binaries" FORCE)      
   mark_as_advanced(${LCOMP_NAME_UC}_EXAMPLES)    

   set(${LCOMP_NAME_UC}_LOGS CACHE STRING "List of unit test log targets" FORCE)
   mark_as_advanced(${LCOMP_NAME_UC}_LOGS)

endfunction(ShfSysTst_set_component_variables)

#
# Add the list of clusters to this component.
#
function(ShfSysTst_add_clusters clusters)

   foreach(cluster ${clusters})

      # Add each cluster subdir to the project. 

      add_subdirectory(${cluster})

   endforeach()

endfunction(ShfSysTst_add_clusters)

#
# Construct the list of include paths for xclusters.
#
function(ShfSysTst_set_component_ipath_variable xcomponent_name xclusters)

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   set(lipath)
   foreach(cluster ${xclusters})

      # Add the fully-qualified cluster names to this component's ipath var

      set(lipath ${lipath} ${CMAKE_CURRENT_SOURCE_DIR}/${cluster})

   endforeach()

   set(${LCOMP_NAME_UC}_IPATH ${lipath} CACHE STRING "Include paths for ${xcomponent_name}" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_IPATH)

endfunction(ShfSysTst_set_component_ipath_variable)

# 
# Create a cmake test for each unit test executable, Windows version.
#
function(ShfSysTst_add_component_win32_unit_test_targets xcomponent_name)

   # Preconditions:

   dbc_require(SHFSYSTST_WINDOWS)

   # Body

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)
   
   # Let the user know what's being configured

   ShfSysTst_status_message("Configuring Unit Tests for ${xcomponent_name}")   

   # Set the path to the SheafSystem bin directory; used by test and debugger paths below.
   
   set(SHEAFSYSTEM_BIN_DIR "${PREREQ_SHEAFSYSTEM_HOME}/bin"
      CACHE STRING "Path to SheafSystem bin directory" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_BIN_DIR)   
   
   foreach(t_cc_file ${${LCOMP_NAME_UC}_UNIT_TEST_SRCS})
      
      # Extract name of executable from source filename

      string(REPLACE .t.cc .t t_file_with_path ${t_cc_file})
      
      # Remove path information  

      get_filename_component(t_file ${t_file_with_path} NAME)
      
      # Add the executable to the list

      set(${LCOMP_NAME_UC}_UNIT_TESTS ${${LCOMP_NAME_UC}_UNIT_TESTS} ${t_file} 
         CACHE STRING "List of unit test binaries" FORCE)

      if(NOT TARGET ${t_file})

         # Target does not already exist; create it now.

         ShfSysTst_status_message("Creating ${t_file} from ${t_cc_file}")

         add_executable(${t_file} ${t_cc_file})

         # unit_test.hdf.log -> unit_test.hdf -> unit_test.log -> unit_test

         target_link_libraries(${t_file} ${${LCOMP_NAME_UC}_IMPORT_LIB})                                         

         # Supply the *_DLL_IMPORTS directive to preprocessor

         set_target_properties(${t_file} PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")

         # Create a test for the target.

         add_test(NAME ${t_file}
            WORKING_DIRECTORY $<TARGET_FILE_DIR:${t_file}>
            COMMAND $<TARGET_FILE:${t_file}> )

         # Add the SheafSystemTest and SheafSystem dll locations to the path for the test.
         
         set(TESTPATH "PATH=$ENV{PATH}")
         set(TESTPATH "${TESTPATH};${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>")
         set(TESTPATH "${TESTPATH};${SHEAFSYSTEM_BIN_DIR}/$<CONFIG>")

         # Unfortunately, Windows uses the semicolon as a path delimiter,
         # but the semicolon has special meaning to Cmake as well.
         # Escape the semicolons in the PATH so cmake doesn't see them as
         # list item separators.

         string(REPLACE ";" "\\;" TESTPATH "${TESTPATH}")
	 file(TO_NATIVE_PATH "${TESTPATH}" TESTPATH)
         
         set_tests_properties(${t_file} PROPERTIES ENVIRONMENT "${TESTPATH}")

         # Insert the unit tests into the VS folder "unit test targets"

         set_target_properties(${t_file} PROPERTIES FOLDER "Unit Test Targets/Executables")

         # Tag the test with the name of the current component.

         set_property(TEST ${t_file} PROPERTY LABELS "${xcomponent_name}")

         if(SHFSYSTST_ENABLE_UNIT_TEST_LOG_TARGETS)

            # Generate a log file for each .t.
            # "make <test>.log will build and run a given executable.

            add_custom_target(${t_file}.exe.log)
            add_custom_command(TARGET ${t_file}.exe.log 
               POST_BUILD 
               COMMAND ${CMAKE_CTEST_COMMAND} -C ${xcomponent_name} -R "^${t_file}$"
               WORKING_DIRECTORY ${OUTDIR})

            # Insert the unit tests into the VS folder "unit test targets"

            set_target_properties(${t_file}.exe.log
               PROPERTIES FOLDER "Unit Test Targets/Log Targets")

         endif(SHFSYSTST_ENABLE_UNIT_TEST_LOG_TARGETS)
         
         if(SHFSYSTST_ENABLE_UNIT_TEST_HDF_LOG_TARGETS)

            # Generate a log file for each .t.hdf
            # "make <test>.hdf will build and run a given executable.

            add_custom_target(${t_file}.exe.hdf
               DEPENDS ${t_file}.exe.log
               WORKING_DIRECTORY ${OUTDIR})

            # Insert the unit tests into the VS folder "Unit Test HDF Targets"

            set_target_properties(${t_file}.exe.hdf
               PROPERTIES FOLDER "Unit Test Targets/HDF Targets")

            # Find out what component $t_file belongs to
            # and create the appropriate hdf log target type

            get_property(PROJ_MEMBER TEST ${t_file} PROPERTY LABELS)
            
            if(${PROJ_MEMBER} MATCHES "sheaves_test")

               # Generate a log file for each .t.hdf.
               # "make <test>.hdf will build and run a given executable.

               add_custom_target(${t_file}.exe.hdf.log
                  DEPENDS sheaves_read ${t_file}.exe.hdf
                  WORKING_DIRECTORY ${OUTDIR})

               # Insert the target into the VS folder "Unit Test HDF Log Targets"

               set_target_properties(${t_file}.exe.hdf.log
                  PROPERTIES FOLDER "Unit Test Targets/HDF Log Targets")

               add_custom_command(TARGET ${t_file}.exe.hdf.log
                  WORKING_DIRECTORY ${OUTDIR}
                  POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E echo "Reading ${t_file}.exe.hdf ... "
                  COMMAND ${OUTDIR}/sheaves_read.exe ${t_file}.exe.hdf > ${t_file}.exe.hdf.log
                  )

            elseif(${PROJ_MEMBER} MATCHES "fiber_bundles_test")

               # Generate a log file for each .t.hdf
               # "make <test>.hdf will build and run a given executable.

               add_custom_target(${t_file}.exe.hdf.log 
                  DEPENDS fiber_bundles_read ${t_file}.exe.hdf
                  WORKING_DIRECTORY ${OUTDIR})

               # Insert the target into the VS folder "Unit Test HDF Log Targets"

               set_target_properties(${t_file}.exe.hdf.log PROPERTIES FOLDER "Unit Test Targets/HDF Log Targets")

               add_custom_command(TARGET ${t_file}.exe.hdf.log
                  WORKING_DIRECTORY ${OUTDIR}
                  POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E echo "Reading ${t_file}.exe.hdf ... "
                  COMMAND ${OUTDIR}/fiber_bundles_read.exe ${t_file}.exe.hdf > ${t_file}.exe.hdf.log
                  ) 

            endif()                

         endif(SHFSYSTST_ENABLE_UNIT_TEST_HDF_LOG_TARGETS)

      endif(NOT TARGET ${t_file})

      # Set up the debugger environment for this target.
      # Apparently CMake or Visual Studio automatically appends the build type.

      set(SHFSYSTST_DEBUGGER_PATH1 "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
      file(TO_NATIVE_PATH "${SHFSYSTST_DEBUGGER_PATH1}" SHFSYSTST_DEBUGGER_PATH1)

      set(SHFSYSTST_DEBUGGER_PATH2 "${SHEAFSYSTEM_BIN_DIR}")
      file(TO_NATIVE_PATH "${SHFSYSTST_DEBUGGER_PATH2}" SHFSYSTST_DEBUGGER_PATH2)
      
      configure_file(${SHFSYSTST_CMAKE_MODULE_PATH}/project.vcxproj.user.in 
         ${CMAKE_BINARY_DIR}/${xcomponent_name}/${t_file}.vcxproj.user @ONLY)
      
   endforeach()

endfunction(ShfSysTst_add_component_win32_unit_test_targets)

# 
# Create a cmake test for each unit test executable, Linux version.
#
function(ShfSysTst_add_component_linux_unit_test_targets xcomponent_name)

   #message("Entering component_functions:ShfSysTst_add_component_linux_unit_test_targets")
   #message("xcomponent_name = ${xcomponent_name}")

   # Preconditions:

   dbc_require(SHFSYSTST_LINUX)

   # Body

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)
   
   # Let the user know what's being configured

   ShfSysTst_status_message("Configuring Unit Tests for ${xcomponent_name}")   
   
   foreach(t_cc_file ${${LCOMP_NAME_UC}_UNIT_TEST_SRCS})

      # Extract name of executable from source filename

      string(REPLACE .t.cc .t t_file_with_path ${t_cc_file})

      # Remove path information  

      get_filename_component(t_file ${t_file_with_path} NAME)

      set(${LCOMP_NAME_UC}_UNIT_TESTS ${${LCOMP_NAME_UC}_UNIT_TESTS} ${t_file} 
         CACHE STRING "List of unit test binaries" FORCE)

      if(NOT TARGET ${t_file})

         # The target does not already exist, create it.

         ShfSysTst_status_message("Creating ${t_file} from ${t_cc_file}")

         add_executable(${t_file} ${t_cc_file})

         # Target links with shared library for this component.
         # target_link_libraries with automatically set up
         # dependence on shared library target and "usage requirements"
         # will propagate.

         target_link_libraries(${t_file} ${${LCOMP_NAME_UC}_SHARED_LIB})
         
         # Add a test target for ${t_file}

         add_test(NAME ${t_file} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND $<TARGET_FILE:${t_file}>)

         # Tag the test with the name of the current component. 
         # Query the test for component membership by getting labels property.

         set_property(TEST ${t_file} PROPERTY LABELS "${xcomponent_name}") 

         # Set the PATH variable for CTest

         set_tests_properties(${t_file} PROPERTIES ENVIRONMENT "PATH=%PATH%;${CMAKE_CFG_INTDIR}")   
         
         if(SHFSYSTST_ENABLE_UNIT_TEST_LOG_TARGETS)   

            # Generate a log file for each .t. "make <test>.log will build and run a given executable.

            add_custom_target(${t_file}.log 
               WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} 
               COMMAND ${t_file} > ${t_file}.log)

            add_dependencies(${t_file}.log ${t_file})
            
            # Insert the unit tests into the VS folder "unit test targets"

            set_target_properties(${t_file}.log PROPERTIES FOLDER "Unit Test Log Targets")
            
            # Note that this var should be named component_test_logs, 
            # but the components are named x_test. Not pretty.

            set(${LCOMP_NAME_UC}_LOGS ${${LCOMP_NAME_UC}_LOGS} ${t_file}.log 
               CACHE STRING "List of unit test log targets" FORCE)

         endif(SHFSYSTST_ENABLE_UNIT_TEST_LOG_TARGETS)                                               
         
         if(SHFSYSTST_ENABLE_UNIT_TEST_HDF_LOG_TARGETS)

            # Generate a log file for each .t.hdf;
            # "make <test>.hdf will build and run a given executable.

            add_custom_target(${t_file}.hdf)

            add_dependencies(${t_file}.hdf ${t_file}.log)
            
            # Insert the unit tests into the VS folder "Unit Test HDF Targets"

            set_target_properties(${t_file}.hdf PROPERTIES FOLDER "Unit Test HDF Targets")
            
            # Find out what component $t_file belongs to, and create the appropriate hdf log target type

            get_property(PROJ_MEMBER TEST ${t_file} PROPERTY LABELS)
            
            if(${PROJ_MEMBER} MATCHES "sheaves_test")

               # $$ISSUE: It appears this branch and the next are inoperative, since
               # the executables sheaves_read and fiber_bundles_read don't seem to exist

               # Generate a log file for each .t.hdf;
               # "make <test>.hdf will build and run a given executable.

               add_custom_target(${t_file}.hdf.log  
                  DEPENDS sheaves_read ${t_file}.hdf 
                  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

               # Insert the target into the VS folder "Unit Test HDF Log Targets"

               set_target_properties(${t_file}.hdf.log PROPERTIES FOLDER "Unit Test HDF Log Targets")
               add_custom_command(TARGET ${t_file}.hdf.log WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                  POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E echo "Reading ${t_file}.hdf ... "
                  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sheaves_read ${t_file}.hdf > ${t_file}.hdf.log
                  )

            elseif(${PROJ_MEMBER} MATCHES "fiber_bundles_test")

               # Generate a log file for each .t.hdf;
               # "make <test>.hdf will build and run a given executable.

               add_custom_target(${t_file}.hdf.log  
                  DEPENDS fiber_bundles_read ${t_file}.hdf 
                  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

               # Insert the target into the VS folder "Unit Test HDF Log Targets"

               set_target_properties(${t_file}.hdf.log PROPERTIES FOLDER "Unit Test HDF Log Targets")

               add_custom_command(TARGET ${t_file}.hdf.log WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                  POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E echo "Reading ${t_file}.hdf ... "
                  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fiber_bundles_read ${t_file}.hdf > ${t_file}.hdf.log
                  )                                             

            endif()
         endif(SHFSYSTST_ENABLE_UNIT_TEST_HDF_LOG_TARGETS)
         
         if(ENABLE_COVERAGE)

            # Create file-scope coverage target.

            add_custom_target(${t_file}.cov DEPENDS ${t_file}.log
               COMMAND ${CMAKE_COMMAND} -E chdir ${SHFSYSTST_COVERAGE_DIR} ${PROFMERGE}
               COMMAND ${CMAKE_COMMAND} -E chdir ${SHFSYSTST_COVERAGE_DIR} ${CODECOV} -comp ${CMAKE_BINARY_DIR}/coverage_files.lst ${CODECOV_ARGS} ${t_file} 
               ) 
            
         endif(ENABLE_COVERAGE)

      endif(NOT TARGET ${t_file})

   endforeach()

   #message("Leaving component_functions:ShfSysTst_add_component_linux_unit_test_targets")

endfunction(ShfSysTst_add_component_linux_unit_test_targets)

# 
# Create a cmake test for each unit test executable.
#
function(ShfSysTst_add_component_unit_test_targets xcomponent_name)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   if(SHFSYSTST_WINDOWS)
      ShfSysTst_add_component_win32_unit_test_targets(${xcomponent_name})
   elseif(SHFSYSTST_LINUX)
      ShfSysTst_add_component_linux_unit_test_targets(${xcomponent_name})
   endif()

endfunction(ShfSysTst_add_component_unit_test_targets xcomponent_name)

# 
# Create a target for each example.
#
function(ShfSysTst_add_component_example_targets xcomponent_name)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   # $$TODO: Decompose into OS specific routines as test_tagets above.

   foreach(t_cc_file ${${LCOMP_NAME_UC}_EXAMPLE_SRCS})

      # Let the user know what's being configured

      ShfSysTst_status_message("Configuring example executables for ${xcomponent_name}")   

      # Deduce name of executable from source filename

      string(REPLACE .cc "" t_file_with_path ${t_cc_file})

      # Remove path information so the executable goes into build/bin (or build/VisualStudio)
      # and not into build/bin/examples (or build/VisualStudio/examples)

      get_filename_component(t_file ${t_file_with_path} NAME)
      set(${LCOMP_NAME_UC}_EXAMPLES ${${LCOMP_NAME_UC}_EXAMPLES} ${t_file} CACHE STRING "List of example binaries" FORCE)      

      # Add building of executable and link with shared library

      ShfSysTst_status_message("Creating ${t_file} from ${t_cc_file}")

      add_executable(${t_file} ${t_cc_file})
      
      # Make sure the library is up to date

      if(SHFSYSTST_WINDOWS)

         add_dependencies(${t_file} ${${LCOMP_NAME_UC}_IMPORT_LIB})
         target_link_libraries(${t_file} ${${LCOMP_NAME_UC}_IMPORT_LIB})

         # Insert the unit tests into the VS folder "unit_tests"

         set_target_properties(${t_file} PROPERTIES FOLDER "Example Targets")

      elseif(SHFSYSTST_LINUX)

         add_dependencies(${t_file} ${${LCOMP_NAME_UC}_SHARED_LIB})
         target_link_libraries(${t_file} ${${LCOMP_NAME_UC}_SHARED_LIB})

      endif()
      
      # Supply the *_DLL_IMPORTS directive to preprocessor

      set_target_properties(${t_file} PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")
      
   endforeach()

endfunction(ShfSysTst_add_component_example_targets)

#
# Add component specific check targets. e.g., "sheaves-check", "tools-check", etc.
#
function(ShfSysTst_add_component_check_target xcomponent_name)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   add_custom_target(${lcomp_name_lc}-check)

   add_custom_command(TARGET ${lcomp_name_lc}-check 
      POST_BUILD 
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "+++ BEGIN TESTS FOR ${xcomponent_name}+++++++++++++++++++++++++++++++++++"
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_CTEST_COMMAND}
         -T test
         -C ${CMAKE_CFG_INTDIR}
         -L ${xcomponent_name}
         -O ${CMAKE_BINARY_DIR}/${xcomponent_name}.log
         -j ${SHFSYSTST_TEST_JOBS} 
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "+++ END TESTS FOR ${xcomponent_name}+++++++++++++++++++++++++++++++++++++"
      COMMAND ${CMAKE_COMMAND} -E echo "")

   if(SHFSYSTST_WINDOWS)       

      add_dependencies(${lcomp_name_lc}-check ${${LCOMP_NAME_UC}_IMPORT_LIB} ${${LCOMP_NAME_UC}_UNIT_TESTS})
      set_target_properties(${lcomp_name_lc}-check PROPERTIES FOLDER "Check Targets")

   elseif(SHFSYSTST_LINUX)

      add_dependencies(${lcomp_name_lc}-check ${${LCOMP_NAME_UC}_SHARED_LIB} ${${LCOMP_NAME_UC}_UNIT_TESTS})        

   endif()
   
   # Add a check target for this component to the system list. "make check" will invoke this list.

   set(ALL_UNIT_TEST_TARGETS ${ALL_UNIT_TEST_TARGETS} ${${LCOMP_NAME_UC}_UNIT_TESTS} 
      CACHE STRING "Aggregate list of unit test targets" FORCE)

   set(ALL_COMP_CHECK_TARGETS ${ALL_COMP_CHECK_TARGETS} ${lcomp_name_lc}-check 
      CACHE STRING "Aggregate list of component check targets" FORCE)
   
endfunction(ShfSysTst_add_component_check_target)

#
# Add component specific bin targets. e.g., "sheaves-test-bin", etc.
#
function(ShfSysTst_add_component_bin_target xcomponent_name)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   if(SHFSYSTST_WINDOWS)

      add_custom_target(${lcomp_name_lc}-bin)

      add_dependencies(${lcomp_name_lc}-bin 
         ${${LCOMP_NAME_UC}_IMPORT_LIB} ${${LCOMP_NAME_UC}_UNIT_TESTS} ${${LCOMP_NAME_UC}_EXAMPLES})

      set_target_properties(${lcomp_name_lc}-bin PROPERTIES FOLDER "Bin Targets")

   elseif(SHFSYSTST_LINUX)

      add_custom_target(${lcomp_name_lc}-bin)

      add_dependencies(${lcomp_name_lc}-bin 
         ${${LCOMP_NAME_UC}_SHARED_LIB} ${${LCOMP_NAME_UC}_UNIT_TESTS} ${${LCOMP_NAME_UC}_EXAMPLES})

   endif()

   # Add a bin target for this component to the system list. "make bin" will invoke this list.

   set(ALL_BIN_TARGETS ${ALL_BIN_TARGETS} ${lcomp_name_lc}-bin 
      CACHE STRING "Aggregate list of component bin targets" FORCE)

endfunction(ShfSysTst_add_component_bin_target)

#
# Add component specific coverage targets. e.g., "sheaves-coverage", "tools-coverage", etc.
#
function(ShfSysTst_add_component_coverage_target xcomponent_name)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   # If the component unit test list is not empty, generate coverage data.   

   if(NOT ${LCOMP_NAME_UC}_UNIT_TEST_SRCS MATCHES "")

      add_custom_target(${lcomp_name_lc}-coverage DEPENDS ${lcomp_name_lc}-check
         COMMAND ${CMAKE_COMMAND} -E chdir ${SHFSYSTST_COVERAGE_DIR} ${PROFMERGE}
         COMMAND ${CMAKE_COMMAND} -E chdir ${SHFSYSTST_COVERAGE_DIR} ${CODECOV} -comp ${CMAKE_BINARY_DIR}/coverage_files.lst ${CODECOV_ARGS} ${xcomponent_name}
         )
   else()

      # Component has no unit tests associated with it, make target an "informational no-op"

      add_custom_target(${lcomp_name_lc}-coverage
         COMMAND ${CMAKE_COMMAND} -E echo " " 
         COMMAND ${CMAKE_COMMAND} -E echo "   There are currently no unit tests for the ${xcomponent_name} component. Coverage results will not be generated." 
         COMMAND ${CMAKE_COMMAND} -E echo " "                      
         )
   endif()

   set_target_properties(${lcomp_name_lc}-coverage PROPERTIES FOLDER "Component Coverage Targets")

   # Append the coverage target to the system wide list

   set(ALL_COVERAGE_TARGETS ${ALL_COVERAGE_TARGETS} ${lcomp_name_lc}-coverage 
      CACHE STRING "Aggregate list of component coverage targets" FORCE)
   
endfunction(ShfSysTst_add_component_coverage_target)

#
# Add component specific checklog targets. e.g., "sheaves-checklog", "tools-checklog", etc.
#
function(ShfSysTst_add_component_checklog_target xcomponent_name)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   if(SHFSYSTST_WINDOWS)

      add_custom_target(${lcomp_name_lc}-checklog)
      add_dependencies(${lcomp_name_lc}-checklog ${${LCOMP_NAME_UC}_IMPORT_LIB} ${${LCOMP_NAME_UC}_LOGS})
      set_target_properties(${lcomp_name_lc}-checklog PROPERTIES FOLDER "Checklog Targets")

   elseif(SHFSYSTST_LINUX)

      add_custom_target(${lcomp_name_lc}-checklog)
      add_dependencies(${lcomp_name_lc}-checklog ${${LCOMP_NAME_UC}_IMPORT_LIB} ${${LCOMP_NAME_UC}_LOGS})

   endif()

   set(ALL_CHECKLOG_TARGETS ${ALL_CHECKLOG_TARGETS} ${${LCOMP_NAME_UC}_LOGS} 
      CACHE STRING "Aggregate list of component checklog targets" FORCE)

endfunction(ShfSysTst_add_component_checklog_target)

#------------------------------------------------------------------------------
# Functions called from <cluster>/CMakeLists.txt.
#------------------------------------------------------------------------------

#
# Append the sources in xsrcs to <xcomponent_name>_SRCS
# Used in cluster level CMakeLists.txt
#
function(ShfSysTst_collect_sources xcomponent_name xsrcs)

   # Prepend the cluster name to each member of the srcs list

   set(lsrcs)
   foreach(src ${xsrcs})
      list(APPEND lsrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
   endforeach()
   
   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)

   set(${LCOMP_NAME_UC}_SRCS ${${LCOMP_NAME_UC}_SRCS} ${lsrcs} 
      CACHE STRING "${xcomponent_name} sources." FORCE)

endfunction(ShfSysTst_collect_sources)

#
# Append incs to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(ShfSysTst_collect_includes xcomponent_name xsrcs xadditional_incs)

   get_filename_component(CLUSTERNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

   # Prepend the cluster name to each member of the srcs list

   set(lincs)
#   if(NOT ${CLUSTERNAME} STREQUAL "template_instantiations")
      foreach(src ${xsrcs})
         string(REGEX REPLACE ".cc$" ".h"  inc ${src})
         list(APPEND lincs ${CMAKE_CURRENT_SOURCE_DIR}/${inc})
      endforeach()
#   endif()
   
   # Prepend the cluster name to each member of the additional_incs list

   foreach(inc ${xadditional_incs})
      list(APPEND lincs ${CMAKE_CURRENT_SOURCE_DIR}/${inc})
   endforeach()

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)

   set(${LCOMP_NAME_UC}_INCS ${${LCOMP_NAME_UC}_INCS} ${lincs} 
      CACHE STRING "${xcomponent_name} includes." FORCE)

endfunction(ShfSysTst_collect_includes)

#
# Append unit test executables to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(ShfSysTst_collect_unit_test_sources xcomponent_name xunit_test_srcs)

   # Prepend the path to each member of the unit test srcs list

   set(chksrcs)
   foreach(src ${xunit_test_srcs})
      list(APPEND chksrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
   endforeach()
   
   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)

   set(${LCOMP_NAME_UC}_UNIT_TEST_SRCS ${${LCOMP_NAME_UC}_UNIT_TEST_SRCS} ${chksrcs} 
      CACHE STRING "Unit test sources." FORCE)
   
endfunction(ShfSysTst_collect_unit_test_sources)

#
# Append standalone executables to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(ShfSysTst_collect_example_sources xcomponent_name xexample_srcs)

   # Prepend the path to each member of the execs list

   set(execsrcs)
   foreach(src ${xexample_srcs})
      list(APPEND execsrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
   endforeach()

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)

   set(${LCOMP_NAME_UC}_EXAMPLE_SRCS ${${LCOMP_NAME_UC}_EXAMPLE_SRCS} ${execsrcs} 
      CACHE STRING "EXEC sources." FORCE)

endfunction(ShfSysTst_collect_example_sources)


#------------------------------------------------------------------------------
# Misc functions
#------------------------------------------------------------------------------

#
# Return string with backslash path separators escaped
# e.g., "c:\my\files" is returned "c:\\my\\files"
# Usage :
#    set(VAR "c:\my\files" )
#    esc_backslash(VAR)
#
macro(esc_backslash RESULT)
   if(WIN32)
      string(REPLACE "\\" "\\\\" RESULT "${RESULT}")
   endif()
endmacro(esc_backslash RESULT)

#
# Query git for the info regarding this repository.
#
function(ShfSysTst_get_repository_info)

   #
   # Get the current branch tag from git
   #
   execute_process(
      COMMAND git rev-parse --abbrev-ref HEAD 
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE TAG
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
   set(GIT_TAG ${TAG} CACHE STRING "Name of this git branch" FORCE)
   
   #
   # Get the hash associated with this branch
   #
   execute_process(
      COMMAND git rev-parse ${GIT_TAG}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE HASH
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
   set(GIT_HASH ${HASH} CACHE STRING "Hash for this git branch" FORCE)

endfunction(ShfSysTst_get_repository_info)
