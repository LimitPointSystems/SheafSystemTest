#
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER matrices)

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
    antisymmetric_matrix_2x2.t.cc
    antisymmetric_matrix_3x3.t.cc
    general_matrix_1x2.t.cc
    general_matrix_1x3.t.cc
    general_matrix_2x1.t.cc
    general_matrix_2x2.t.cc
    general_matrix_2x3.t.cc
    general_matrix_3x1.t.cc
    general_matrix_3x2.t.cc
    general_matrix_3x3.t.cc
    symmetric_matrix_2x2.t.cc
    symmetric_matrix_3x3.t.cc
    svd.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
