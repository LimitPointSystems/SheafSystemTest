#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.6 $ $Date: 2012/07/05 19:18:17 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER id_spaces)

#
# Library sources.
#
set(SRCS
    array_implicit_index_map.cc
    array_implicit_index_map_interval.cc
    array_implicit_index_map_iterator.cc
    array_index_map.cc
    array_index_map_iterator.cc
    binary_product_index_map_iterator.cc
    explicit_product_index_space.cc
    gluable_sum_index_map.cc
    gluable_sum_index_map_iterator.cc
    gluable_sum_index_space.cc
    glued_sum_index_map.cc
    glued_sum_index_space.cc
    hash_index_map.cc
    implicit_index_map_interval.cc
    implicit_index_space_interval.cc
    implicit_product_index_space.cc
    index_equivalence_class.cc
    index_equivalence_iterator.cc
    index_map.cc
    index_map_iterator.cc
    index_space.cc
    index_space_family.cc
    index_space_iterator.cc
    interval_index_map.cc
    interval_index_map_iterator.cc
    mutable_index_map.cc
    offset_index_map.cc
    offset_index_map_iterator.cc
    primitives_index_map.cc
    product_index_map.cc
    product_index_space.cc
    simple_index_space.cc
    stl_index_map_iterator.cc
    sum_index_map.cc
    sum_index_map_local_iterator.cc
    sum_index_space.cc
    test_index_spaces.cc
    ternary_product_index_map_iterator.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
        implicit_index_space_interval.impl.h 
        index_space.impl.h 
        stl_index_map_iterator.impl.h
  )
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    array_index_map.t.cc
    hash_index_map.t.cc
    index_space_family.t.cc
    interval_index_map.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
