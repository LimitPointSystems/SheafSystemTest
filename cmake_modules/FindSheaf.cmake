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
find_file(SHEAFEXPORTSFILE SheafSystem-exports.cmake.in
    HINTS ${SHEAFSYSTEM_HOME}/${CMAKE_BUILD_TYPE}/config ${SHEAFSYSTEM_HOME}/build)
# Not good. The exports file wasn't where SHEAFSYSTEM_HOME claimed it was.    
if(${SHEAFEXPORTSFILE} MATCHES "SHEAFEXPORTSFILE-NOTFOUND")
    message(FATAL_ERROR "SheafSystem-exports.cmake was not found; Is the SHEAFSYSTEM_HOME variable set correctly?")
else()
    message(STATUS "Found ${SHEAFEXPORTSFILE}; configuring ...")
    configure_file(${SHEAFEXPORTSFILE} ${CMAKE_BINARY_DIR}/SheafSystem-exports.cmake)
    include(${CMAKE_BINARY_DIR}/SheafSystem-exports.cmake)
    set(SHEAF_FOUND 1)
endif()


   


          