#
# $RCSfile: component_definitions.cmake,v $ $Revision: 1.14 $ $Date: 2012/07/05 19:18:16 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#
include_directories(${FIELDS_IPATHS})
#
# Include functions and definitions common to all components.
# 
include(${CMAKE_MODULE_PATH}/LPSCommon.cmake)

#
# Define the clusters for this component.
#
set(clusters fields iterators pushers refiners)

#
# Initialize all variables for this component.
#
set_component_vars()

if(WIN64INTEL OR WIN64MSVC)

    #
    # Set the cumulative import library (win32) var for this component.
    #
    set(${COMPONENT}_IMPORT_LIBS ${${COMPONENT}_IMPORT_LIB} ${GEOMETRY_IMPORT_LIBS} CACHE STRING " Cumulative import libraries (win32) for ${PROJECT_NAME}" FORCE)

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
set(${COMPONENT}_IPATHS ${${COMPONENT}_IPATH} ${GEOMETRY_IPATHS} CACHE STRING " Cumulative include paths for ${PROJECT_NAME}")

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
        # $$HACK: Once we resolve the DLL boundary issue, we only need depend on ${${COMPONENT}_SRCS}
        #
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS} ${GEOMETRY_SRCS} ${FIBER_BUNDLES_SRCS} ${SHEAVES_SRCS})
        if(${USE_VTK})
            target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${TETGEN_LIB} ${HDF5_DLL_LIBRARY} ${VTK_LIBS}) 
        else()
            target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${TETGEN_LIB} ${HDF5_DLL_LIBRARY})        
        endif()  

        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES FOLDER "Component Library Targets")   
        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

    else() # Linux
        # $$TODO: Why does fields want to link against vtk?
        link_directories(${VTK_LIB_DIR})   
        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_STATIC_LIB} ${GEOMETRY_STATIC_LIBS})
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
