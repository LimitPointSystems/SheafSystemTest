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
    i_index_space.t.cc
    ij_index_space.t.cc
    ijk_index_space.t.cc
    section_space_schema_jims_index_space.t.cc
   )

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

   )

collect_example_sources()
