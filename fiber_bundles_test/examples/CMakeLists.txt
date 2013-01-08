#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.7 $ $Date: 2012/07/05 19:18:15 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

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
    at0.t.cc 
    fields3d.t.cc 
    torus.t.cc
    recipe.t.cc 
# The following files are no longer part of the build.
# they are deprecated and only remain around as a reference
# for future development.
#    partial_field.t.cc 
#    discretization_iterator.t.cc 
#    scalable_entire_read_write.t.cc 
#    scalable_iterator.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS
    fiber_bundles_read.cc 
 )

collect_example_sources()
