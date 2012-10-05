#
# $RCSfile: component_definitions.cmake,v $ $Revision: 1.9 $ $Date: 2012/07/05 19:18:17 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#

include_directories(${SOLVERS_IPATHS})

#
# Include functions and definitions common to all components.
# 
include(${CMAKE_MODULE_PATH}/LPSCommon.cmake)

#
# Include cmake test functions and macros
#
include(CTest)

#
# Define the clusters for this component.
#
set(clusters solvers)

#
# Initialize all variables for this component.
#
set_component_vars()

#
# Define the component library associated with this test module.
#
set(${COMPONENT}_EXTERNAL_LIB libsolvers.so CACHE STRING "Solvers Shared Library")

#
# Set the cumulative shared library var for this component.
#
set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIB} ${FIBER_BUNDLES_STATIC_LIBS} CACHE STRING " Cumulative static libraries for ${PROJECT_NAME}" FORCE)

#
# Set the cumulative shared library var for this component.
#
set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIB} ${FIBER_BUNDLES_SHARED_LIBS} CACHE STRING " Cumulative shared libraries for ${PROJECT_NAME}" FORCE)

#
# Set the cumulative Java binding library var for this component.
#
set(${COMPONENT}_JAVA_BINDING_LIBS ${${COMPONENT}_JAVA_BINDING_LIB} ${FIBER_BUNDLES_JAVA_BINDING_LIBS} CACHE STRING " Cumulative Java binding libraries for ${PROJECT_NAME}" FORCE)

#
# Set the cumulative Python binding library var for this component.
#
set(${COMPONENT}_PYTHON_BINDING_LIBS ${${COMPONENT}_PYTHON_BINDING_LIB} ${FIBER_BUNDLES_PYTHON_BINDING_LIBS} CACHE STRING " Cumulative Python binding libraries for ${PROJECT_NAME}" FORCE)

#
# Set the cumulative include path for this component.
#
set(${COMPONENT}_IPATHS ${${COMPONENT}_IPATH} ${FIBER_BUNDLES_IPATHS} CACHE STRING " Cumulative include paths for ${PROJECT_NAME}")

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(add_library_targets)
    if(WIN64)
    
         # Tell the linker where to look for this project's libraries.
        link_directories(${${COMPONENT}_OUTPUT_DIR})
    
        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        
        target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${HDF5_DLL_LIBRARY})
        
        # Override cmake's placing of "${${COMPONENT}_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")
    
    else() # Linux
    
        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_STATIC_LIB} ${FIBER_BUNDLES_STATIC_LIB})
        set_target_properties(${${COMPONENT}_STATIC_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

        # Shared library
        add_library(${${COMPONENT}_SHARED_LIB} SHARED ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES LINK_INTERFACE_LIBRARIES "") 
        add_dependencies(${${COMPONENT}_SHARED_LIB} ${FIBER_BUNDLES_SHARED_LIBS})
        
        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        # CMake apparently detects the presence of cdecl_dllspec in the source and places
        # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
    
        # Define the library version.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION}) 
        
        # Library alias definitions
        add_dependencies(${PROJECT_NAME}-shared-lib ${${COMPONENT}_SHARED_LIBS})
        add_dependencies(${PROJECT_NAME}-static-lib ${${COMPONENT}_STATIC_LIBS})
    
        target_link_libraries(${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_SHARED_LIBS})
        target_link_libraries(${${COMPONENT}_STATIC_LIB} ${${COMPONENT}_STATIC_LIBS})

        add_custom_command(TARGET ${${COMPONENT}_SHARED_LIB} POST_BUILD
            # rename the coverage output files and put them in lib
            COMMAND ${CMAKE_COMMAND} -E  rename ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/pgopti.spi ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_SHARED_LIB}.spi
            COMMAND ${CMAKE_COMMAND} -E  rename ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/pgopti.spl ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_SHARED_LIB}.spl
             )
    endif()

endfunction(add_library_targets)
