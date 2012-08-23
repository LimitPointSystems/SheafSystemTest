#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

# RAW is going to need to work with sheaf libs in one of 2 ways: It's either going
# to have a "dev" version; that is a built version in SHEAF_HOME/build, or a snapshot release
# $$TODO: Equip RAW to deal with either -- export the "exported file" in the snapshot target

#
# Initialize the found variable
#
set(SHEAF_FOUND 0)

#
# Find the exports file
#
message(STATUS "Looking for sheafSystem exports file ...")
find_file(SHEAFEXPORTSFILE SheafSystem-exports.cmake
    HINTS ${SHEAFSYSTEM_HOME} ${SHEAFSYSTEM_HOME}/build)
# Not good. The exports file wasn't where SHEAF_HOME claimed it was.    
if(${SHEAFEXPORTSFILE} MATCHES "SHEAFEXPORTSFILE-NOTFOUND")
    message(FATAL_ERROR "sheafSystem-exports.cmake was not found in ${SHEAFSYSTEM_HOME}/build; Is the SHEAFSYSTEM_HOME variable set correctly?")
else()
    message(STATUS "Found ${SHEAFEXPORTSFILE}")
    include(${SHEAFEXPORTSFILE})
    set(SHEAF_FOUND 1)
endif()


   


          