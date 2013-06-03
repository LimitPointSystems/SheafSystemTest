#
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#

#
# Include functions and definitions common to all components.
# 
include(${CMAKE_MODULE_PATH}/LPSCommon.cmake)

#
# Define the clusters for this component.
#
set(clusters fields iterators pushers refiners template_instantiations)

#
# Initialize all variables for this component.
#
set_component_vars()

#
# Add the clusters to the project
#
add_clusters("${clusters}")

if(WIN64INTEL OR WIN64MSVC)

    #
    # Set the cumulative import library (win32) var for this component.
    #
    set(${COMPONENT}_IMPORT_LIBS ${GEOMETRY_TEST_IMPORT_LIBS} ${${COMPONENT}_IMPORT_LIB} ${FIELDS_IMPORT_LIB}  CACHE STRING " Cumulative import libraries (win32) for ${PROJECT_NAME}" FORCE)

else()

    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIB} ${GEOMETRY_STATIC_LIBS} CACHE STRING " Cumulative static libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIB} libfields.so ${GEOMETRY_TEST_SHARED_LIBS} CACHE STRING " Cumulative shared libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative Java binding library var for this component.
    #
    set(${COMPONENT}_JAVA_BINDING_LIBS ${${COMPONENT}_JAVA_BINDING_LIB} ${GEOMETRY_JAVA_BINDING_LIBS} CACHE STRING " Cumulative Java binding libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative Python binding library var for this component.
    #
    set(${COMPONENT}_PYTHON_BINDING_LIBS ${${COMPONENT}_PYTHON_BINDING_LIB} ${GEOMETRY_PYTHON_BINDING_LIBS} CACHE STRING " Cumulative Python binding libraries for ${PROJECT_NAME}" FORCE)

endif()

#
# Set the cumulative include path for this component.
#
set(${COMPONENT}_IPATHS ${GEOMETRY_TEST_IPATHS} ${${COMPONENT}_IPATH} ${FIELDS_IPATH} CACHE STRING " Cumulative include paths for ${PROJECT_NAME}" FORCE)

include_directories(${${COMPONENT}_IPATHS})
#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(add_library_targets)

    include_directories(${${COMPONENT}_IPATHS})
        
    if(${USE_VTK})
        if(EXISTS ${VTK_LIB_DIR})
            link_directories(${VTK_LIB_DIR})
        else()
            link_directories(${INSTALLED_VTK_LIB_DIR})
        endif()
    endif()
    
    if(WIN64INTEL OR WIN64MSVC)
    
        # Tell the linker where to look for this project's libraries.
        link_directories(${${COMPONENT}_OUTPUT_DIR})

        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_DYNAMIC_LIB} ${GEOMETRY_TEST_IMPORT_LIBS} ${FIELDS_IMPORT_LIBS})

        if(${USE_VTK})
            target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${GEOMETRY_TEST_IMPORT_LIBS} ${FIELDS_IMPORT_LIBS} ${VTK_LIBS}) 
        else()
            target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${GEOMETRY_TEST_IMPORT_LIBS} ${FIELDS_IMPORT_LIBS})        
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
        add_dependencies(${${COMPONENT}_SHARED_LIB} ${GEOMETRY_TEST_SHARED_LIBS} ${FIELDS_SHARED_LIBS})
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
    
        target_link_libraries(${${COMPONENT}_SHARED_LIB} ${GEOMETRY_TEST_SHARED_LIBS} ${GEOMETRY_SHARED_LIBS})
        target_link_libraries(${${COMPONENT}_STATIC_LIB} ${GEOMETRY_TEST_SHARED_LIBS} ${GEOMETRY_SHARED_LIBS})  

    endif()

endfunction(add_library_targets)
