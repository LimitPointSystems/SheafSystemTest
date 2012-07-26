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

set(CLUSTER general)

#
# Library sources.
#
set(SRCS
    fiber_bundle.cc
    fiber_bundles_namespace.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    fiber_bundle.impl.h 
    fiber_bundles_namespace.impl.h
  )

collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    fiber_bundles_namespace.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()