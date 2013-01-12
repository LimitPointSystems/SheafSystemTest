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
    test_fields_inst.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_fields_inst.impl.h
)
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    field_factory_2.inst.t.cc
    fields.auto_block.inst.t.cc
    fields.block.inst.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
