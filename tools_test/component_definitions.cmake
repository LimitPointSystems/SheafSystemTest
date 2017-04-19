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
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(ShfSysTst_add_tools_test_library_targets)

   #message("Entering tools_test/component_definitions.cmake:add_library_targets")

   # Preconditions:

   dbc_require_or(SHFSYSTST_WINDOWS SHFSYSTST_LINUX)

   # Body

   # Target to create copies of header files with path ${SHFSYSTST_HEADER_SCOPE}/*.h,
   # so uniquely scoped paths in include directives will work.

   add_custom_target(tools_test_scoped_headers
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TOOLS_TEST_INCS} ${SHFSYSTST_HEADER_DIR})   

   if(SHFSYSTST_WINDOWS)

      # Create the DLL.

      add_library(${TOOLS_TEST_DYNAMIC_LIB} SHARED ${TOOLS_TEST_SRCS})
      add_dependencies(${TOOLS_TEST_DYNAMIC_LIB} tools_test_scoped_headers)
#      target_include_directories(${SHEAVES_TEST_DYNAMIC_LIB}
#         PUBLIC ${SHEAVES_TEST_IPATH} ${CMAKE_BINARY_DIR}/include)
      target_include_directories(${TOOLS_TEST_DYNAMIC_LIB} PUBLIC ${CMAKE_BINARY_DIR}/include)
      target_link_libraries(${TOOLS_TEST_DYNAMIC_LIB}
         PUBLIC ${FIELDS_TEST_IMPORT_LIB} ${GEOMETRY_IMPORT_LIB})              
      set_target_properties(${TOOLS_TEST_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")

      # Override cmake's placing of "${TOOLS_TEST_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.

      set_target_properties(${TOOLS_TEST_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

   elseif(SHFSYSTST_LINUX)
      
      # Static library

      add_library(${TOOLS_TEST_STATIC_LIB} STATIC ${TOOLS_TEST_SRCS})
      add_dependencies(${TOOLS_TEST_STATIC_LIB} tools_test_scoped_headers)
#      target_include_directories(${TOOLS_TEST_STATIC_LIB} PUBLIC ${TOOLS_TEST_IPATH})
      target_include_directories(${TOOLS_TEST_STATIC_LIB} PUBLIC ${CMAKE_BINARY_DIR}/include)
      
      target_link_libraries(${TOOLS_TEST_STATIC_LIB} ${FIELDS_STATIC_LIB})

      set_target_properties(${TOOLS_TEST_STATIC_LIB} PROPERTIES OUTPUT_NAME tools_test)

      # Shared library

      add_library(${TOOLS_TEST_SHARED_LIB} SHARED ${TOOLS_TEST_SRCS})
      add_dependencies(${TOOLS_TEST_SHARED_LIB} tools_test_scoped_headers)
      add_dependencies(${TOOLS_TEST_SHARED_LIB} ${FIELDS_TEST_SHARED_LIB} ${GEOMETRY_SHARED_LIB})
#      target_include_directories(${TOOLS_TEST_SHARED_LIB} PUBLIC ${TOOLS_TEST_IPATH})
      target_include_directories(${TOOLS_TEST_SHARED_LIB} PUBLIC ${CMAKE_BINARY_DIR}/include)
      
      target_link_libraries(${TOOLS_TEST_SHARED_LIB} ${FIELDS_TEST_SHARED_LIB} ${GEOMETRY_SHARED_LIB})

      set_target_properties(${TOOLS_TEST_SHARED_LIB} PROPERTIES OUTPUT_NAME tools_test)
      set_target_properties(${TOOLS_TEST_SHARED_LIB} PROPERTIES LINKER_LANGUAGE CXX)
      set_target_properties(${TOOLS_TEST_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION}) 
      
      # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
      # CMake apparently detects the presence of cdecl_dllspec in the source and places
      # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.

      set_target_properties(${TOOLS_TEST_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
      
      # Library alias definitions

      add_custom_target(tools_test-static-lib)
      add_dependencies(tools_test-static-lib ${TOOLS_TEST_STATIC_LIB})

      add_custom_target(tools_test-shared-lib)
      add_dependencies(tools_test-shared-lib ${TOOLS_TEST_SHARED_LIB})

   endif()

   #message("Leaving tools_test/component_definitions.cmake:add_library_targets")

endfunction(ShfSysTst_add_tools_test_library_targets)
