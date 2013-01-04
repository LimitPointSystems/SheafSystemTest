#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.1.2.11 $ $Date: 2012/11/13 00:14:29 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
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
    test_sheaves.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_sheaves.impl.h
)
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    deep_size.inst.t.cc
    depth_first_itr.inst.t.cc
    equivalence_relation.inst.t
    filtered_depth_first_itr.inst.t.cc
    postorder_itr.inst.t.cc
    preorder_itr.inst.t.cc
    biorder_itr.inst.t.cc
    triorder_itr.inst.t.cc
    linkorder_itr.inst.t.cc
    sheaf.abstract_poset_member.inst.t.cc
    sheaf.block.inst.t.cc
    sheaf.auto_block.inst.t.cc
    name_map.inst.t.cc
    name_multimap.inst.t.cc
    sheaf.namespace_poset.inst.t.cc
    ragged_array.inst.t.cc
    record_map.inst.t.cc
    wsv_block.inst.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()