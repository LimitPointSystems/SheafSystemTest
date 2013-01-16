#
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
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
    block_scaling_test.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    block_scaling_test.impl.h
  )

collect_includes() 

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    base_space_poset.t.cc
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
# The following files are no longer part of the build.
# they are deprecated and only remain around as a reference
# for future development.
#    connectivity_array.t.cc
#    zone_partition.t.cc
#    material_decomposition.t.cc
#    mesh_decomposition.t.cc
#    mesh_partition.t.cc
#    processor_decomposition.t.cc
#    adjacency_extractor.t.cc
#    connectivity_extractor.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS
    scalable_point_block_1d.t.cc
    scalable_point_block_2d.t.cc
    scalable_point_block_3d.t.cc
    scalable_structured_block_1d.t.cc
    scalable_structured_block_2d.t.cc
    scalable_structured_block_3d.t.cc
    scalable_zone_nodes_block_1d.t.cc
    scalable_zone_nodes_block_2d.t.cc
    scalable_zone_nodes_block_3d.t.cc
    scalable_unstructured_block_1d.t.cc
    scalable_unstructured_block_2d.t.cc
    scalable_unstructured_block_3d.t.cc
 )

collect_example_sources()

