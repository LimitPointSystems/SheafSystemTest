#
#

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
  d_cells_cohort.t.cc 
  jim_cohort.t.cc
  kd_lattice.t.cc 
  subcohort.t.cc 
  vertex_cohort.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
