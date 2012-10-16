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
    fb_libstub.cc
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

