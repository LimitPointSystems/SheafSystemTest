#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.7 $ $Date: 2012/07/05 19:18:16 $
#

#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
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
  abstract_cohort.cc 
  cohort.cc 
  d_cells_cohort.cc 
  jim_cohort.cc 
  kd_bounding_box.cc 
  kd_display.cc
  kd_edge.cc 
  kd_edge_cohort.cc 
  kd_enums.cc 
  kd_face.cc 
  kd_face_cohort.cc 
  kd_lattice.cc 
  kd_line.cc 
  kd_line_fragment.cc 
  kd_member.cc 
  kd_plane.cc 
  kd_point.cc 
  kd_region.cc
  kd_segment.cc 
  kd_surface.cc 
  kd_tetgen_generator.cc 
  kd_triangle.cc
  kd_truncation_pair.cc
  kd_truncation.cc
  kd_vertex.cc 
  kd_vertex_cohort.cc 
  kd_zone.cc 
  kd_zone_cohort.cc 
  pooled_cohort.cc 
  subcohort.cc 
  vertex_cohort.cc 
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
  d_cells_cohort.t.cc 
  jim_cohort.t.cc
  kd_lattice.t.cc 
  subcohort.t.cc 
  vertex_cohort.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
