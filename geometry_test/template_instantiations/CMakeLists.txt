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
    test_geometry.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_geometry.impl.h
)
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    geometry_block.inst.t.cc
    geometry_auto_block.inst.t.cc
    d_bin_coordinates.inst.t.cc
    d_bounding_box.inst.t.cc
)


collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
