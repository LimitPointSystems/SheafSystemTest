#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
#
#
# Initialize the "found" variable
#
set(SHEAF_FOUND 0)

# Determine if we are dealing with a build tree or install tree.
message(STATUS "Checking nature of SheafSystem Tree ...")
find_file(SHEAFEXPORTSFILE SheafSystem-exports.cmake
    HINTS ${SHEAFSYSTEM_HOME}/config)
# Not good. The exports file wasn't where SHEAF_HOME claimed it was.    
if(${SHEAFEXPORTSFILE} MATCHES "SHEAFEXPORTSFILE-NOTFOUND")
    message(WARNING "SheafSystem-exports.cmake was not found in ${SHEAFSYSTEM_HOME}/config; checking for a SheafSystem Build Tree ...")
    # it wasnt an install. Check for a build tree
    find_file(SHEAFEXPORTSFILE SheafSystem-exports.cmake
    HINTS ${SHEAFSYSTEM_HOME}/build)
    # Still didn't find it. Die.
    if(${SHEAFEXPORTSFILE} MATCHES "SHEAFEXPORTSFILE-NOTFOUND")
        message(FATAL_ERROR "SheafSystem-exports.cmake was not found in ${SHEAFSYSTEM_HOME}/build either; Is the SHEAFSYSTEM_HOME variable set correctly?")
    else()
        set(SHEAFSYSTEM_IS_BUILD 1)
    endif()
else()
    message(STATUS "Found ${SHEAFEXPORTSFILE}")
    include(${SHEAFEXPORTSFILE})
    set(SHEAF_FOUND 1)
    set(SHEAFSYSTEM_IS_INSTALL 1)
endif()

message(STATUS "SHEAFSYSTEM_IS_BUILD is ${SHEAFSYSTEM_IS_BUILD}")
message(STATUS "SHEAFSYSTEM_IS_INSTALL is ${SHEAFSYSTEM_IS_INSTALL}")
   


          