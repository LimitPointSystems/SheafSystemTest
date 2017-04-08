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
test_case_2d.cc
test_case_3d.cc
   )

ShfSysTst_collect_sources(tools_test "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
 #   lps_environment.h
   )

ShfSysTst_collect_includes(tools_test "${SRCS}" "${ADDITIONAL_INCS}")

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
   )

ShfSysTst_collect_unit_test_sources(tools_test "${UNIT_TEST_SRCS}")

#
# Source for example executables.
#
set(EXAMPLE_SRCS
test_case_2d.t.cc
test_case_3d.t.cc
   )

ShfSysTst_collect_example_sources(tools_test "${EXAMPLE_SRCS}")
