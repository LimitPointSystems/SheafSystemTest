#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

# RAW is going to need to work with sheaf libs in one of 2 ways: It's either going
# to have a "dev" version; that is a built version in SHEAFSYSTEM_HOME/build, or a snapshot release
# $$TODO: Equip RAW to deal with either -- export the "exported file" in the snapshot target

#
# Initialize the found variable
#
set(SHEAF_FOUND 0)

#set(SHEAFSYSTEM_HOME $ENV{SHEAFSYSTEM_HOME} CACHE STRING "Sheaf Home Directory" FORCE)

#
# Find the exports file
#
message(STATUS "Looking for sheafSystem exports file ...")
find_file(SHEAFEXPORTSFILE SheafSystem-exports.cmake.in
    HINTS ${SHEAFSYSTEM_HOME} ${SHEAFSYSTEM_HOME}/${CMAKE_BUILD_TYPE}/config ${SHEAFSYSTEM_HOME}/build)
# Not good. The exports file wasn't where SHEAFSYSTEM_HOME claimed it was.    
if(${SHEAFEXPORTSFILE} MATCHES "SHEAFEXPORTSFILE-NOTFOUND")
    message(FATAL_ERROR "SheafSystem-exports.cmake was not found; Is the SHEAFSYSTEM_HOME variable set correctly?")
else()
    message(STATUS "Found ${SHEAFEXPORTSFILE}; configuring ...")
    configure_file(${SHEAFEXPORTSFILE} ${CMAKE_BINARY_DIR}/SheafSystemExports.cmake)
    include(${SHEAFEXPORTSFILE})
    set(SHEAF_FOUND 1)
endif()


   


          