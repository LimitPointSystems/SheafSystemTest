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

set(CLUSTER posets)

#
# Library sources.
#
set(SRCS
    abstract_poset_member.cc
    cover_set_adapter.cc
    explicit_cover_set_adapter.cc
    implicit_cover_set_adapter.cc
    implicit_crg_range.cc
    list_cover_set.cc
    list_cover_set_adapter.cc
    namespace_member_index.cc
    namespace_poset.cc
    namespace_poset_member.cc
    namespace_poset_schema.cc
    namespace_relative_member_index.cc
    namespace_relative_subposet_index.cc
    namespace_schema_member_index.cc
    partial_poset_member.cc
    poset.cc
    poset_component.cc
    poset_crg_state.cc
    poset_handle_factory.cc
    poset_joiner.cc
    poset_member.cc
    poset_path.cc
    poset_powerset_state.cc
    poset_state.cc
    poset_state_handle.cc
    poset_table_state.cc
    poset_type.cc
    primitives_poset.cc
    primitives_poset_schema.cc
    primitives_schema_member_index.cc
    refinable_poset.cc
    schema_descriptor.cc
    schema_poset_member.cc
    standard_dof_tuple_index.cc
    standard_member_index.cc
    standard_subposet_index.cc
    standard_version_index.cc
    subposet.cc
    subposet_state.cc
    total_poset_member.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    abstract_poset_member.impl.h 
    namespace_poset.impl.h 
    poset_crg_state.impl.h 
    namespace_poset.impl.h 
    poset_state_handle.impl.h
  )

collect_includes()  

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    list_cover_set.t.cc
    member_multiple_names.t.cc
    namespace_poset.t.cc
    poset.t.cc
    poset_joiner.t.cc
    subposet.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()

