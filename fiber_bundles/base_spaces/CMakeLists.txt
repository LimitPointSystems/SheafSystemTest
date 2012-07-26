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

set(CLUSTER base_spaces)

#
# Library sources.
#
set(SRCS
    adjacency_extractor.cc
    base_space_crg_range.cc
    base_space_factory.cc
    base_space_member.cc
    base_space_member_prototype.cc
    base_space_poset.cc
    binary_index.cc
    binary_index_space.cc
    block_adjacency.cc
    block_connectivity.cc
    block_relation.cc
    chart_point.cc
    chart_point_1d.cc
    chart_point_2d.cc
    chart_point_3d.cc
    connectivity_array.cc
    connectivity_extractor.cc
    hex_connectivity.cc
    homogeneous_block.cc
    homogeneous_block_crg_range.cc
    line_connectivity.cc
    local_base_space_member.cc
    material_decomposition.cc
    mesh_decomposition.cc
    mesh_partition.cc
    neighborhood_extractor.cc
    point_block_1d.cc
    point_block_2d.cc
    point_block_3d.cc
    point_block_crg_range.cc
    point_connectivity.cc
    processor_decomposition.cc
    quad_connectivity.cc
    stencil_extractor.cc
    structured_block.cc
    structured_block_1d.cc
    structured_block_1d_crg_range.cc
    structured_block_2d.cc
    structured_block_2d_crg_range.cc
    structured_block_3d.cc
    structured_block_3d_crg_range.cc
    ternary_index.cc
    ternary_index_space.cc
    tetra_connectivity.cc
    triangle_connectivity.cc
    unary_index_space.cc
    unstructured_block.cc
    unstructured_block_builder.cc
    zone_nodes_block.cc
    zone_nodes_block_crg_range.cc
    zone_partition.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    base_space_factory.impl.h 
    block_scaling_test.h 
    block_scaling_test.impl.h 
    unary_index.h
  )

collect_includes() 

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    adjacency_extractor.t.cc
    connectivity_extractor.t.cc
    hex_connectivity.t.cc
    line_connectivity.t.cc
    point_block_1d.t.cc
    point_block_2d.t.cc
    point_block_3d.t.cc
    point_connectivity.t.cc
    quad_connectivity.t.cc
    structured_block_1d.t.cc
    structured_block_2d.t.cc
    structured_block_3d.t.cc
    tetra_connectivity.t.cc
    triangle_connectivity.t.cc
    unstructured_block.t.cc
    zone_nodes_block.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()

