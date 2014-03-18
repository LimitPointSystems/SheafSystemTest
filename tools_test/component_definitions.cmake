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

#include_directories(${TOOLS_IPATHS})

#
# Include functions and definitions common to all components.
# 
include(${CMAKE_MODULE_PATH}/component_functions.cmake)

#
# Include cmake test functions and macros
#
include(CTest)

#
# Define the clusters for this component.
#
set(clusters examples)

#
# Initialize all variables for this component.
#
set_component_vars()

#
# Define the component library associated with this test module.
#
#set(${COMPONENT}_EXTERNAL_LIB libtools.so CACHE STRING "Tools Shared Library")

#
# We don't have to use this decision structure. Windows and linux will ignore the other's lib vars. Just keeps things tidy in the CMake GUI.
#
if(WIN64INTEL OR WIN64MSVC)

    #
    # Set the cumulative import library (win32) var for this component.
    #
    set(${COMPONENT}_IMPORT_LIBS ${FIELDS_IMPORT_LIBS} ${${COMPONENT}_IMPORT_LIB} ${TOOLS_IMPORT_LIB} CACHE STRING " Cumulative import libraries (win32) for ${PROJECT_NAME}" FORCE)

else()

    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_STATIC_LIBS ${FIELDS_STATIC_LIBS} ${${COMPONENT}_STATIC_LIB} CACHE STRING " Cumulative static libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIB} ${FIELDS_SHARED_LIB} ${FIELDS_TEST_SHARED_LIBS} CACHE STRING " Cumulative shared libraries for ${PROJECT_NAME}" FORCE)

    #
    # Set the cumulative Java binding library var for this component.
    #
    set(${COMPONENT}_JAVA_BINDING_LIBS ${${COMPONENT}_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_LIBS} CACHE STRING " Cumulative Java binding libraries for ${PROJECT_NAME}" FORCE)
    
endif()


#
# Set the cumulative include path for this component.
#
set(${COMPONENT}_IPATHS ${FIELDS_IPATHS} ${${COMPONENT}_IPATH} CACHE STRING " Cumulative include paths for ${PROJECT_NAME}")

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(add_library_targets)

    include_directories(${${COMPONENT}_IPATHS})
    include_directories(${JDK_INC_DIR} ${JDK_PLATFORM_INC_DIR})
    include_directories(${VTK_INC_DIRS})
           
    link_directories(${VTK_LIB_DIR})
    link_directories(${JDK_LIB_DIR})
    link_directories(${JVM_LIB_DIR})
    link_directories(${XAWT_LIB_DIR})
        
    if(WIN64INTEL OR WIN64MSVC)
    
        # Tell the linker where to look for this project's libraries. 
        link_directories(${${COMPONENT}_OUTPUT_DIR})
    
        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        
        target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${FIELDS_IMPORT_LIBS} toolsdll ${JDK_LIBS} ${VTK_LIBS})
        
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")        
        
        # Override cmake's placing of "${${COMPONENT}_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")
    else()
        # Linux
               
        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_STATIC_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
        add_dependencies(${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIBS})
    
        # Shared library
        add_library(${${COMPONENT}_SHARED_LIB} SHARED ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES LINK_INTERFACE_LIBRARIES "") 
        add_dependencies(${${COMPONENT}_SHARED_LIB} ${FIELDS_SHARED_LIBS})
        
        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        # CMake apparently detects the presence of cdecl_dllspec in the source and places
        # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
         
        # Define the library version.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION}) 
        
        # Library alias definitions
        add_dependencies(${PROJECT_NAME}-shared-lib ${${COMPONENT}_SHARED_LIBS})
        add_dependencies(${PROJECT_NAME}-static-lib ${${COMPONENT}_STATIC_LIBS})
    
        target_link_libraries(${${COMPONENT}_SHARED_LIB} ${FIELDS_SHARED_LIBS} ${JDK_LIBS} ${VTK_LIBS})
        target_link_libraries(${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIBS} ${JDK_LIBS} ${VTK_LIBS})

    endif()
endfunction(add_library_targets)


# END ORIGINAL TEXT

#
# Add the clusters to the project
#
add_clusters("${clusters}")

if(WIN64INTEL OR WIN64MSVC)

    #
    # Set the cumulative import library (win32) var for this component.
    #
    set(${COMPONENT}_IMPORT_LIBS ${FIELDS_TEST_IMPORT_LIBS} ${${COMPONENT}_IMPORT_LIB} ${GEOMETRY_IMPORT_LIB} CACHE STRING "Cumulative import libraries (win32) for ${PROJECT_NAME}" FORCE)

else()

    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIBS} CACHE STRING " Cumulative static libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIB} libgeometry.so ${FIELDS_TEST_SHARED_LIBS} CACHE STRING " Cumulative shared libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative Java binding library var for this component.
    #
    set(${COMPONENT}_JAVA_BINDING_LIBS ${${COMPONENT}_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_LIBS} CACHE STRING " Cumulative Java binding libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative Python binding library var for this component.
    #
    set(${COMPONENT}_PYTHON_BINDING_LIBS ${${COMPONENT}_PYTHON_BINDING_LIB} ${FIELDS_PYTHON_BINDING_LIBS} CACHE STRING " Cumulative Python binding libraries for ${PROJECT_NAME}" FORCE)

endif() 
#
# Set the cumulative include path for this component.
#
set(${COMPONENT}_IPATHS ${FIELDS_TEST_IPATHS} ${${COMPONENT}_IPATH} ${GEOMETRY_IPATH} CACHE STRING " Cumulative include paths for ${PROJECT_NAME}" FORCE)

include_directories(${${COMPONENT}_IPATHS})

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(add_library_targets)

    if(${USE_VTK})
        if(EXISTS ${VTK_LIB_DIR})
            link_directories(${VTK_LIB_DIR})
			include_directories(${VTK_INC_DIR})
        else()
            link_directories(${INSTALLED_VTK_LIB_DIR})
        endif()
    endif()

     if(WIN64INTEL OR WIN64MSVC)

        # Tell the linker where to look for this project's libraries.
        link_directories(${${COMPONENT}_OUTPUT_DIR})

        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_DYNAMIC_LIB} ${FIELDS_TEST_IMPORT_LIBS} ${GEOMETRY_IMPORT_LIBS})

        if(${USE_VTK})
            target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${FIELDS_IMPORT_LIBS} ${FIELDS_TEST_IMPORT_LIBS} ${VTK_LIBS}) 
        else()
            target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${FIELDS_IMPORT_LIBS})        
        endif() 
     
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")
        # Override cmake's placing of "${${COMPONENT}_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

    else() # Linux
    
        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_STATIC_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

         # Shared library
        add_library(${${COMPONENT}_SHARED_LIB} SHARED ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_SHARED_LIB} ${FIELDS_TEST_SHARED_LIBS} ${GEOMETRY_SHARED_LIBS})
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES LINK_INTERFACE_LIBRARIES "") 
        
        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        # CMake apparently detects the presence of cdecl_dllspec in the source and places
        # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
 
        # Define the library version.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION}) 
    
        # Library alias definitions
        add_dependencies(${PROJECT_NAME}-shared-lib ${${COMPONENT}_SHARED_LIBS})
        add_dependencies(${PROJECT_NAME}-static-lib ${${COMPONENT}_STATIC_LIBS})
        
        if(${USE_VTK})
            target_link_libraries(${${COMPONENT}_SHARED_LIB} ${FIELDS_TEST_SHARED_LIBS} ${GEOMETRY_SHARED_LIBS} ${VTK_LIBS})
            target_link_libraries(${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIBS} ${VTK_LIBS})    
        else()
            target_link_libraries(${${COMPONENT}_SHARED_LIB} ${FIELDS_TEST_SHARED_LIBS} ${GEOMETRY_SHARED_LIBS})
            target_link_libraries(${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIBS})
        endif()

    endif()

endfunction(add_library_targets)
