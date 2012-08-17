# $RCSfile: CMakeLists.txt,v $ $Revision: 1.7 $ $Date: 2012/07/04 16:42:30 $

#
# Copyright (c) 2010 Limit Point Systems, Inc.
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER Viewer/common)

#
# Library sources.
#
set(SRCS
    jvm_launcher.cc
    visualization_iterator_1_1.cc
    visualization_iterator_1_3.cc
    visualization_iterator_4_2.cc
    visualization_iterator_4_3.cc
    visualization_iterator.cc
    vtk_poly_data_builder.cc
    vtk_abstract_grid_builder.cc
    vtk_unstructured_grid_builder.cc
    NativeVtk.cc
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
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS
vtk_unstructured_grid_builder_from_file.t.cc
vtk_unstructured_grid_builder.t.cc
vtk_unstructured_grid_writer.t.cc
)

collect_example_sources()

