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


# 
# Establish a system level "bin" target
#
function(ShfSysTst_add_bin_target)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   add_custom_target(bin DEPENDS ${ALL_BIN_TARGETS})

   if(SHFSYSTST_WINDOWS)
      set_target_properties(bin PROPERTIES FOLDER "Bin Targets")
   endif()
   
endfunction(ShfSysTst_add_bin_target)

# 
# Establish a system level "check" target
#
function(ShfSysTst_add_check_target)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body
   
   add_custom_target(check
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "+++ BEGIN SHEAF SYSTEM TESTS +++++++++++++++++++++++++++++++++++"
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_CTEST_COMMAND}
         -T test
         -C ${CMAKE_CFG_INTDIR}
         -O ${CMAKE_BINARY_DIR}/SheafSystemTest.log
         -j ${SHFSYSTST_TEST_JOBS} 
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "+++ END SHEAF SYSTEM TESTS +++++++++++++++++++++++++++++++++++++"
      COMMAND ${CMAKE_COMMAND} -E echo "")
   
   add_dependencies(check bin)

   if(SHFSYSTST_WINDOWS)

      set_target_properties(check PROPERTIES FOLDER "Check Targets")

   endif()

endfunction(ShfSysTst_add_check_target)

# 
# Establish a system level "checklog" target
#
function(ShfSysTst_add_checklog_target)

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   if(SHFSYSTST_WINDOWS)

      add_custom_target(checklog COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_CFG_INTDIR} DEPENDS ${ALL_CHECKLOG_TARGETS})
      set_target_properties(checklog PROPERTIES FOLDER "Checklog Targets")

   elseif(SHFSYSTST_LINUX)

      add_custom_target(checklog COMMAND DEPENDS ${ALL_CHECKLOG_TARGETS})

   endif()

endfunction(ShfSysTst_add_checklog_target)

# 
# Establish a system level "coverage" target
#
function(ShfSysTst_add_coverage_target xproject_name)

   # Preconditions:

   dbc_require(SHFSYSTST_ENABLE_COVERAGE)

   # Body:

   add_custom_target(coverage ALL DEPENDS check    
      COMMAND ${CMAKE_COMMAND} -E chdir ${SHFSYSTST_COVERAGE_DIR} ${PROFMERGE}
      COMMAND ${CMAKE_COMMAND} -E chdir ${SHFSYSTST_COVERAGE_DIR} ${CODECOV} -comp ${CMAKE_BINARY_DIR}/coverage_files.lst ${CODECOV_ARGS} ${xproject_name}   
      )
   
endfunction(ShfSysTst_add_coverage_target)

#
# System level library targets
#
function(ShfSysTst_add_system_library_targets)

   # Preconditions:

   # Requires component level targets already defined.

   dbc_require(SHFSYSTST_LINUX)
   dbc_require_target(fields_test-shared-lib)
   dbc_require_target(fields_test-static-lib)

   # $$ISSUE: do these libs exist?

   dbc_require_target(tools_test-shared-lib)
   dbc_require_target(tools_test-static-lib)

   # Body:

   # "shared-libs" builds solely shared libs
   # Depends directly on tools, tools depends on fields, etc.,
   # but tools libs only built if bindings are on.

   add_custom_target(shared-libs)
   add_dependencies(shared-libs fields_test-shared-lib)

   # "static-libs" builds solely static libs
   # Depends directly on tools, tools depends on fields, etc.,
   # but tools libs only built if bindings are on.

   add_custom_target(static-libs)
   add_dependencies(static-libs fields_test-static-lib)
   
   # Alias for shared lib; backward naming compatability with gnu system

   add_custom_target(lib)
   add_dependencies(lib shared-libs)


endfunction(ShfSysTst_add_system_library_targets)

#
# Realclean target.
#
function(ShfSysTst_add_realclean_target)

   # Preconditions:

   dbc_require(SHFSYSTST_LINUX)

   # Body:

   add_custom_target(realclean 
      COMMAND ${CMAKE_COMMAND} --build  ${CMAKE_BINARY_DIR} --target clean
      COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/documentation) 

endfunction(ShfSysTst_add_realclean_target)

#
# Covclean target
#
function(ShfSysTst_add_covclean_target)

   # Preconditions:

   dbc_require(SHFSYSTST_LINUX)
   dbc_require(SHFSYSTST_ENABLE_COVERAGE)

   # Body:

   # Body:
   
   # Remove html dpi CodeCoverage dir and .lock files for coverage dir

   add_custom_target(covclean 
      COMMAND ${CMAKE_COMMAND} -E remove_directory ${SHFSYSTST_COVERAGE_DIR}/CodeCoverage
      COMMAND ${CMAKE_COMMAND} -E remove -f ${SHFSYSTST_COVERAGE_DIR}/*.dpi
      COMMAND ${CMAKE_COMMAND} -E remove -f ${SHFSYSTST_COVERAGE_DIR}/*.lock
      COMMAND ${CMAKE_COMMAND} -E remove -f ${SHFSYSTST_COVERAGE_DIR}/*.HTML
      COMMAND ${CMAKE_COMMAND} -E remove -f ${SHFSYSTST_COVERAGE_DIR}/*.dyn
      COMMAND ${CMAKE_COMMAND} -E remove -f ${SHFSYSTST_COVERAGE_DIR}/*.spi
      COMMAND ${CMAKE_COMMAND} -E remove -f ${SHFSYSTST_COVERAGE_DIR}/*.spl 
      )


endfunction(ShfSysTst_add_covclean_target)

# 
#  Make emacs tags
#
function(ShfSysTst_add_tags_target)

   # Preconditions:

   dbc_require(SHFSYSTST_LINUX)

   # Body:

   add_custom_target(tags
      COMMAND find ${CMAKE_CURRENT_SOURCE_DIR} -name build -prune -o -name "*.cc" -print -o -name "*.h" -print -o -name "*.t.cc" -print | etags --c++ --members -
      )

endfunction(ShfSysTst_add_tags_target) 

#
# Add help targets.
#
function(SheafSystem_add_help_targets)

   add_custom_target(help-help
      COMMAND ${CMAKE_COMMAND} -E echo "    "     
      COMMAND ${CMAKE_COMMAND} -E echo "    "  
      COMMAND ${CMAKE_COMMAND} -E echo "The following help targets are available: "
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "    help-targets -- lists available system targets."
      COMMAND ${CMAKE_COMMAND} -E echo "    help-cmake-options -- Things you can say to cmake to affect the build system state."
      COMMAND ${CMAKE_COMMAND} -E echo "    "        
      COMMAND ${CMAKE_COMMAND} -E echo "")
   
   add_custom_target(help-cmake-options
      COMMAND ${CMAKE_COMMAND} -E echo "" 
      COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_BUILD_TYPE:"
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Sets the default build type for this run. Only meaningful in Linux "
      COMMAND ${CMAKE_COMMAND} -E echo "    as build type is chosen at compile time in Visual Studio."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Type: string"         
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Default Value: Debug_contracts"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: ./cmboot -DCMAKE_BUILD_TYPE=Release-contracts"
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DCMAKE_BUILD_TYPE=Release-contracts .."        
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "ENABLE_COVERAGE:"
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Toggles Intel compiler flag for generating coverage data. "
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "    Type: boolean"         
      COMMAND ${CMAKE_COMMAND} -E echo "    "         
      COMMAND ${CMAKE_COMMAND} -E echo "    Default Value: OFF"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: ./cmboot -DENABLE_COVERAGE=ON"
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DENABLE_COVERAGE=ON .."        
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "        example -- from build directory: cmake -DBUILD_BINDINGS=ON .."  
      COMMAND ${CMAKE_COMMAND} -E echo "")
   
   add_custom_target(help-targets
      COMMAND ${CMAKE_COMMAND} -E echo "" 
      COMMAND ${CMAKE_COMMAND} -E echo "" 
      COMMAND ${CMAKE_COMMAND} -E echo "The fundamental targets are: "
      COMMAND ${CMAKE_COMMAND} -E echo "    all"
      COMMAND ${CMAKE_COMMAND} -E echo "    bin" 
      COMMAND ${CMAKE_COMMAND} -E echo "    check"
      COMMAND ${CMAKE_COMMAND} -E echo "    coverage"

      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "all [default]:"
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds and runs all unit tests. "
      COMMAND ${CMAKE_COMMAND} -E echo "    Provided make -j1, execution will be in component order. That is -- all "
      COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving "
      COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If value of j is greater than 1, behavior may vary."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: check."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "bin:"
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds all unit test routines and examples." 
      COMMAND ${CMAKE_COMMAND} -E echo "    Does not execute any compiled code."
      COMMAND ${CMAKE_COMMAND} -E echo ""
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
      COMMAND ${CMAKE_COMMAND} -E echo "        Bin targets can be invoked per component. All prerequisite libraries "
      COMMAND ${CMAKE_COMMAND} -E echo "        and executables will be constructed in dependency order if needed."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields_test-bin"
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves_test-bin"
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "check:    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds and runs all unit tests. "
      COMMAND ${CMAKE_COMMAND} -E echo "    Provided make -j1, execution will be in component order. That is -- all "
      COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving "
      COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If value of j is greater than 1, behavior may vary."
      COMMAND ${CMAKE_COMMAND} -E echo "    "            
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
      COMMAND ${CMAKE_COMMAND} -E echo "        Check targets can be invoked per component. All prerequisite libraries "
      COMMAND ${CMAKE_COMMAND} -E echo "        will be constructed in dependency order if needed."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields_test-check"
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves_test-check"
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "coverage:    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Only available if C++ compiler is Intel"
      COMMAND ${CMAKE_COMMAND} -E echo "    Builds all unit test routines using '-prof-gen=srcpos' on  " 
      COMMAND ${CMAKE_COMMAND} -E echo "    linux, or '/Qprof-gen:srcpos' on Windows , executes the unit tests, and generates coverage documentation"
      COMMAND ${CMAKE_COMMAND} -E echo "    Provided make -j1, execution will be in component order. That is -- all"
      COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving"
      COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If value of j is greater than 1, behavior may vary."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    NOTE: The SheafSystem must be built '-prof-gen=srcpos' on linux. or "
      COMMAND ${CMAKE_COMMAND} -E echo "    '/Qprof-gen:srcpos' on Windows for this target to produce coverage results. "
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      COMMAND ${CMAKE_COMMAND} -E echo "    "
      COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
      COMMAND ${CMAKE_COMMAND} -E echo "        Coverage targets can be invoked per component. All prerequisite libraries "
      COMMAND ${CMAKE_COMMAND} -E echo "        and executables will be constructed in dependency order if needed."
      COMMAND ${CMAKE_COMMAND} -E echo "    " 
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields_test-coverage"
      COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves_test-coverage"
      COMMAND ${CMAKE_COMMAND} -E echo ""
      #        COMMAND ${CMAKE_COMMAND} -E echo "[test].t.log:"
      #        COMMAND ${CMAKE_COMMAND} -E echo "    Builds and runs [test].t. Redirects output from run into bin/[test].t.log"
      #        COMMAND ${CMAKE_COMMAND} -E echo "    "
      #        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
      #        COMMAND ${CMAKE_COMMAND} -E echo "    "
      #        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands: check"
      #        COMMAND ${CMAKE_COMMAND} -E echo "    "
      #        COMMAND ${CMAKE_COMMAND} -E echo "       example: make poset.t.log"
      #        COMMAND ${CMAKE_COMMAND} -E echo "    "
      #        COMMAND ${CMAKE_COMMAND} -E echo "    " 
      
      )

endfunction(SheafSystem_add_help_targets)

#
# Add all the system level targets.
#
function(ShfSysTst_add_system_targets)

   if(SHFSYSTST_LINUX)
      ShfSysTst_add_system_library_targets()
      ShfSysTst_add_realclean_target()
      ShfSysTst_add_tags_target()
   endif()

   ShfSysTst_add_check_target()
   ShfSysTst_add_checklog_target()
   ShfSysTst_add_bin_target()

   if(SHFSYSTST_ENABLE_COVERAGE)
      ShfSysTst_add_coverage_target()
      ShfSysTst_add_covclean_target()
   endif()

   SheafSystem_add_help_targets()

endfunction(ShfSysTst_add_system_targets)

