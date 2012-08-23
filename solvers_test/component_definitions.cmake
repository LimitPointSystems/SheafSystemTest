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

include_directories(${STD_IPATH} ${SHEAVES_IPATH} ${FIBER_BUNDLES_IPATH} ${FIELDS_IPATH} ${SOLVERS_IPATH})

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
# Define the component library associated with this test module.
#
set(${COMPONENT}_SHARED_LIB libsolvers.so CACHE STRING "Solvers Shared Library")

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------
