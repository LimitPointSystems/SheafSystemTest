#
# $RCSfile: component_definitions.cmake,v $ $Revision: 1.12 $ $Date: 2012/07/05 19:18:16 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#

#
# Include functions and definitions common to all components.
# .
include(${CMAKE_MODULE_PATH}/LPSCommon.cmake)

include_directories(${SHEAVES_IPATHS}) 

#
# Define the clusters for this component.
#
set(clusters concurrency dof_iterators dof_maps examples id_spaces io iterators 
    maps posets support test_posets traversers)

#
# Initialize all variables for this component.
#
set_component_vars()


#
# We don't have to use this decision structure. Windows and linux will ignore the other's lib vars. Just keeps things tidy in the CMake GUI.
#
if(WIN64INTEL OR WIN64MSVC)

    #
    # Set the cumulative import library (win32) var for this component.
    #
    set(${COMPONENT}_IMPORT_LIBS ${${COMPONENT}_IMPORT_LIB} ${SHEAVES_IMPORT_LIBS}  CACHE STRING " Cumulative import libraries (win32) for ${PROJECT_NAME}" FORCE)

else()

    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIB} ${SHEAVES_STATIC_LIBS} CACHE STRING " Cumulative static libraries for ${PROJECT_NAME}" FORCE)
    
    #
    # Set the cumulative shared library var for this component.
    #
    set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIB} ${SHEAVES_SHARED_LIBS} CACHE STRING " Cumulative shared libraries for ${PROJECT_NAME}" FORCE)

endif()

#
# Set the cumulative include path for this component.
#
set(${COMPONENT}_IPATHS ${${COMPONENT}_IPATH} ${SHEAVES_IPATHS} ${CMAKE_BINARY_DIR}/include CACHE STRING " Cumulative include paths for ${PROJECT_NAME}" FORCE)

#
# Check for the presence of system cxx includes.
#
check_cxx_includes()
    

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(add_library_targets)
    if(WIN64INTEL OR WIN64MSVC)

        # Tell the linker where to look for this project's libraries.
        link_directories(${${COMPONENT}_OUTPUT_DIR})

        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${HDF5_DLL_LIBRARY})
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")
        # Override cmake's placing of "${${COMPONENT}_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

    else()

        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_STATIC_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
        add_dependencies(${${COMPONENT}_STATIC_LIB} ${SHEAVES_STATIC_LIBS})

        # Shared library
        add_library(${${COMPONENT}_SHARED_LIB} SHARED ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES LINK_INTERFACE_LIBRARIES "")        
        add_dependencies(${${COMPONENT}_SHARED_LIB} ${SHEAVES_SHARED_LIBS})
 
        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        # CMake apparently detects the presence of cdecl_dllspec in the source and places
        # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
 
        # Define the library version.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION})  
    
        # Library alias definitions
        add_dependencies(${PROJECT_NAME}-shared-lib ${${COMPONENT}_SHARED_LIB})
        add_dependencies(${PROJECT_NAME}-static-lib ${${COMPONENT}_STATIC_LIB})
    
        target_link_libraries(${${COMPONENT}_SHARED_LIB} ${SHEAVES_SHARED_LIBS})
        target_link_libraries(${${COMPONENT}_STATIC_LIB} ${SHEAVES_SHARED_LIBS})
        
    endif()

endfunction(add_library_targets)


