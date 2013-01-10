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
    member_multiple_names.t.cc
    namespace_poset.t.cc
    poset.t.cc
    poset_joiner.t.cc
    standard_dof_tuple_index.t.cc
    standard_member_index.t.cc
    standard_subposet_index.t.cc
    standard_version_index.t.cc
    subposet.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()

