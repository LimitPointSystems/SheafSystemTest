#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.6 $ $Date: 2012/07/05 19:18:16 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER pushers)

#
# Library sources.
#
set(SRCS
    average_base_space_map_push_action.cc
    average_push_action.cc
    avg_section_pusher.cc
    base_space_map.cc
    base_space_map_push_action.cc
    body_builder.cc
    body_factory.cc
    body_pusher.cc
    body_pusher_pullback_action.cc
    constant_base_space_map_push_action.cc
    constant_push_action.cc
    copy_base_space_map_push_action.cc
    copy_push_action.cc
    pullback_map.cc
    section_pusher.cc
    section_pusher_pullback_action.cc
    section_pusher_push_action.cc
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
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()