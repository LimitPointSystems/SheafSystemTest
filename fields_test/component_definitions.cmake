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
# Define the component library associated with this test module.
#
set(${COMPONENT}_SHARED_LIB libfields.so CACHE STRING "Fields Shared Library")

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

