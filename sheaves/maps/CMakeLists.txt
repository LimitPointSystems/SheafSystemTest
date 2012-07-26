#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.7 $ $Date: 2012/07/05 19:18:17 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER maps)

#
# Library sources.
#
set(SRCS
    name_multimap.cc 
    name_map.cc
    record_map.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    client_index.h 
    name_map.impl.h 
    name_multimap.impl.h 
    record_map.impl.h
  )
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
