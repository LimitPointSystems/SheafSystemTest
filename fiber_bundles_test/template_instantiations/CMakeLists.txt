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
    test_fiber_bundles.cc
   )

ShfSysTst_collect_sources(fiber_bundles_test "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_fiber_bundles.impl.h
   )
  
ShfSysTst_collect_includes(fiber_bundles_test "${SRCS}" "${ADDITIONAL_INCS}")

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    base_space_factory.inst.t.cc
    fiber_bundle.abstract_poset_member.inst.t.cc
    fiber_bundle.auto_block.inst.t.cc
    fiber_bundle.block.inst.t.cc
    fiber_bundle.namespace_poset.inst.t.cc
    fiber_bundle.list_pool.inst.t.cc
   )

ShfSysTst_collect_unit_test_sources(fiber_bundles_test "${UNIT_TEST_SRCS}")

#
# Source for example executables.
#
set(EXAMPLE_SRCS

   )

ShfSysTst_collect_example_sources(fiber_bundles_test "${EXAMPLE_SRCS}")
