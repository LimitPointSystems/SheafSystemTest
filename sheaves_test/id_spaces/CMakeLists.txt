#
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
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
    test_index_spaces.cc
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
    index_space_family.t.cc
    index_space_interval.t.cc
    product_structure.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
