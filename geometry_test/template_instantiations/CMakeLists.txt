#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.1.2.1 $ $Date: 2012/10/19 02:28:25 $
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
    test_geometry_inst.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_geometry_inst.impl.h
)
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    d_array_point_locator.inst.t.cc
    d_bin_coordinates.inst.t.cc
    d_bin_point_locator.inst.t.cc
    d_bounding_box.inst.t.cc
    d_tree_point_locator.inst.t.cc
    d_tree_point_locator_node.inst.t.cc
    d_tree_point_locator_path.inst.t.cc
    d_uniform_point_locator.inst.t.cc
    db0_point_locator.inst.t.cc
    geometry.auto_block.inst.t.cc
    geometry.block.inst.t.cc
    geometry.ptr_linked_pool.inst.t.cc
)


collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
