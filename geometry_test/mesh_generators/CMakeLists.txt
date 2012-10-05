#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.8 $ $Date: 2012/07/05 19:18:16 $
#

#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
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
    cube_with_fault_1.t.cc
    jessen.t.cc
#    oct_generator_2.t.cc
    oct_generator.t.cc
    s2_bag_generator.t.cc
    schonhardt.t.cc
    small_angles.t.cc
    sphere_generator.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
