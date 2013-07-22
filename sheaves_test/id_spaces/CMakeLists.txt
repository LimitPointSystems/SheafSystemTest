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
    test_index_spaces.cc
   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_index_space.impl.h
   )
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    array_index_space.t.cc
    array_index_space_interval.t.cc
    constant_index_space_interval.t.cc
    explicit_index_space.t.cc
    forwarding_index_space.t.cc
    hash_index_space.t.cc
    index_space_family.t.cc
    index_space_interval.t.cc
    interval_index_space.t.cc
    mutable_index_space.t.cc
    list_index_space.t.cc
    offset_index_space.t.cc
    primary_index_space.t.cc
    ragged_array_index_space_interval.t.cc
    reserved_primary_index_space.t.cc
    singleton_index_space.t.cc
    singleton_index_space_interval.t.cc
    sum_index_space.t.cc
    product_structure.t.cc
   )

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

   )

collect_example_sources()
