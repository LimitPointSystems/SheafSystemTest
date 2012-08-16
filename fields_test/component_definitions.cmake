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

#
# Include functions and definitions common to all components.
# 
include(${CMAKE_MODULE_PATH}/LPSCommon.cmake)

#
# Define the clusters for this component.
#
set(clusters fields iterators pushers refiners)

#
# Define the component library associated with this test module.
#
set(${COMPONENT}_SHARED_LIB libfields.so CACHE STRING "Fields Shared Library")


#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------


# 
# Set the commands for the install target
#
function(add_install_target)

        install(TARGETS ${${COMPONENT}_SHARED_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
        install(TARGETS ${${COMPONENT}_STATIC_LIB} ARCHIVE DESTINATION ${CMAKE_BUILD_TYPE}/lib)

        install(TARGETS ${${COMPONENT}_JAVA_BINDING_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
        install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR} DESTINATION ${CMAKE_BUILD_TYPE}/lib)  
        # Only install python binding if the component has a target for it.
        if(TARGET ${${COMPONENT}_PYTHON_BINDING_LIB})
            install(TARGETS ${${COMPONENT}_PYTHON_BINDING_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
        endif()       

        # Include files are independent of build type. Includes and docs install at top level.
        # See system level CMakeLists.txt for "documentation" install directive.
     
        install(FILES ${${COMPONENT}_INCS} DESTINATION include)
        #install(TARGETS ${${COMPONENT}_CHECK_EXECS} RUNTIME DESTINATION bin)
                     
endfunction(add_install_target)