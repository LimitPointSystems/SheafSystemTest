#
# $RCSfile: component_definitions.cmake,v $ $Revision: 1.11 $ $Date: 2012/07/05 19:18:17 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#

include_directories(${TOOLS_IPATHS})

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
set(clusters SheafScope common/client_server common/event common/gui common/util 
    viewer/animation viewer/common viewer/event viewer/render viewer/table 
    viewer/user viewer/application)

#
# Define the component library associated with this test module.
#
set(${COMPONENT}_SHARED_LIB libtools.so CACHE STRING "Tools Shared Library")

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------