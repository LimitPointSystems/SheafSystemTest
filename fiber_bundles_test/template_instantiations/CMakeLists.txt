#
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER template_instantiations)

#
# Library sources.
#
set(SRCS
    test_fiber_bundles.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_fiber_bundles.impl.h
)
  
collect_includes()

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
    fiber_bundles_namespace.inst.t.cc
    section_space_factory.inst.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
