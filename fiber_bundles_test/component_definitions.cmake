#
# $RCSfile: component_definitions.cmake,v $ $Revision: 1.12 $ $Date: 2012/07/05 19:18:15 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#
include_directories(${FIBER_BUNDLES_IPATHS})
#
# Include functions and definitions common to all components.
# 
include(${CMAKE_MODULE_PATH}/LPSCommon.cmake)

#
# Define the clusters for this component.
#
set(clusters base_spaces dof_iterators dof_maps evaluators fiber_spaces general 
    id_spaces iterators matrices section_spaces examples)

#
# Define the component library associated with this test module.
#
set(${COMPONENT}_SHARED_LIB libfiber_bundles.so CACHE STRING "Fiber_bundles Shared Library")


#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------
