#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.6 $ $Date: 2012/07/05 19:18:15 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
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
    antisymmetric_matrix_2x2.cc
    antisymmetric_matrix_3x3.cc
    general_matrix_1x2.cc
    general_matrix_1x3.cc
    general_matrix_2x1.cc
    general_matrix_2x2.cc
    general_matrix_2x3.cc
    general_matrix_3x1.cc
    general_matrix_3x2.cc
    general_matrix_3x3.cc
    symmetric_matrix_2x2.cc
    symmetric_matrix_3x3.cc
    svd.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    antisymmetric_matrix_2x2.impl.h 
    antisymmetric_matrix_3x3.impl.h 
    general_matrix_1x2.impl.h 
    general_matrix_1x3.impl.h 
    general_matrix_2x1.impl.h 
    general_matrix_2x2.impl.h 
    general_matrix_2x3.impl.h 
    general_matrix_3x1.impl.h 
    general_matrix_3x2.impl.h 
    general_matrix_3x3.impl.h 
    symmetric_matrix_2x2.impl.h 
    symmetric_matrix_3x3.impl.h 
    svd.h
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
