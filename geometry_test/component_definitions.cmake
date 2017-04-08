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
# This file contains declarations and functions unique to this component.
#
#

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(ShfSysTst_add_geometry_test_library_targets)

   #message("Entering geometry_test/component_definitions.cmake:add_library_targets")

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   if(SHFSYSTST_WINDOWS)

      # Create the DLL.

      add_library(${GEOMETRY_TEST_DYNAMIC_LIB} SHARED ${GEOMETRY_TEST_SRCS})
      target_include_directories(${GEOMETRY_TEST_DYNAMIC_LIB}
         PUBLIC ${GEOMETRY_TEST_IPATH} ${CMAKE_BINARY_DIR}/include)
      target_link_libraries(${GEOMETRY_TEST_DYNAMIC_LIB}
         PUBLIC ${FIBER_BUNDLES_TEST_IMPORT_LIB} ${GEOMETRY_IMPORT_LIB})  
      set_target_properties(${GEOMETRY_TEST_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")

      # Override cmake's placing of "${GEOMETRY_TEST_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.

      set_target_properties(${GEOMETRY_TEST_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

   elseif(SHFSYSTST_LINUX)
      
      # Static library

      add_library(${GEOMETRY_TEST_STATIC_LIB} STATIC ${GEOMETRY_TEST_SRCS})
      target_include_directories(${GEOMETRY_TEST_STATIC_LIB} PUBLIC ${GEOMETRY_TEST_IPATH})
      target_link_libraries(${GEOMETRY_TEST_STATIC_LIB} ${GEOMETRY_STATIC_LIB})

      set_target_properties(${GEOMETRY_TEST_STATIC_LIB} PROPERTIES OUTPUT_NAME geometry_test)

      # Shared library

      add_library(${GEOMETRY_TEST_SHARED_LIB} SHARED ${GEOMETRY_TEST_SRCS})
      add_dependencies(${GEOMETRY_TEST_SHARED_LIB} ${FIBER_BUNDLES_TEST_SHARED_LIB} ${GEOMETRY_SHARED_LIB})
      target_include_directories(${GEOMETRY_TEST_SHARED_LIB} PUBLIC ${GEOMETRY_TEST_IPATH})      
      target_link_libraries(${GEOMETRY_TEST_SHARED_LIB} ${FIBER_BUNDLES_TEST_SHARED_LIB} ${GEOMETRY_SHARED_LIB})
      set_target_properties(${GEOMETRY_TEST_SHARED_LIB} PROPERTIES OUTPUT_NAME geometry_test LINKER_LANGUAGE CXX)
      set_target_properties(${GEOMETRY_TEST_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION}) 
      
      # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
      # CMake apparently detects the presence of cdecl_dllspec in the source and places
      # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.

      set_target_properties(${GEOMETRY_TEST_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
      
      # Library alias definitions

      add_custom_target(geometry_test-static-lib)
      add_dependencies(geometry_test-static-lib ${GEOMETRY_TEST_STATIC_LIB})

      add_custom_target(geometry_test-shared-lib)
      add_dependencies(geometry_test-shared-lib ${GEOMETRY_TEST_SHARED_LIB})

   endif()

   #message("Leaving geometry_test/component_definitions.cmake:add_library_targets")

endfunction(ShfSysTst_add_geometry_test_library_targets)
