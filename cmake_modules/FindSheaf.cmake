#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
# Initialize the found variable
#
set(SHEAF_FOUND 0)

#
# Find the exports file
#
message(STATUS "Looking for SheafSystem exports file ...")
if(EXISTS ${SHEAFSYSTEM_HOME}/${CMAKE_BUILD_TYPE}/config/SheafSystem-exports.cmake.in)
    set(SHEAFEXPORTSFILE ${SHEAFSYSTEM_HOME}/${CMAKE_BUILD_TYPE}/config/SheafSystem-exports.cmake.in)
    configure_file(${SHEAFEXPORTSFILE} ${CMAKE_BINARY_DIR}/SheafSystem-exports.cmake)
    include(${CMAKE_BINARY_DIR}/SheafSystem-exports.cmake)
    set(SHEAF_FOUND 1)
elseif(EXISTS ${SHEAFSYSTEM_HOME}/build/SheafSystem-exports.cmake)
    set(SHEAFEXPORTSFILE ${SHEAFSYSTEM_HOME}/build/SheafSystem-exports.cmake CACHE STRING "Location of SheafSystem Exports file" FORCE)
    include(${SHEAFEXPORTSFILE})
    set(SHEAF_FOUND 1)
else()
    message(FATAL_ERROR "SheafSystem exports file not found; Check the value of SHEAFSYSTEM_HOME.")
endif()    

   


          