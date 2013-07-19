#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER ${CMAKE_CURRENT_BINARY_DIR})

#
# Library sources.
#
set(SRCS

   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS

   )

collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    body_builder.t.cc
    body_pusher.t.cc
    section_pusher_0d.t.cc
    section_pusher_1d.t.cc
    section_pusher_2d.t.cc
    section_pusher_3d.t.cc
##    multisection_pusher.t.cc
##    multisection_base_space_map.t.cc 
   )

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

   )

collect_example_sources()
