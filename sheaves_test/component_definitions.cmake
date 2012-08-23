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

include_directories(${STD_IPATH} ${SHEAVES_IPATH}) 

#
# Define the clusters for this component.
#
set(clusters concurrency dof_iterators dof_maps examples id_spaces io iterators 
    maps posets support test_posets traversers)
    
#
# Define the component library associated with this test module.
#
set(${COMPONENT}_SHARED_LIB libsheaves.so CACHE STRING "Sheaves Shared Library")

#
# Check for the presence of system cxx includes.
#
check_cxx_includes()
    

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------



