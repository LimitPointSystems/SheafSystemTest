#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.6 $ $Date: 2012/07/05 19:18:17 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER test_posets)

#
# Library sources.
#
set(SRCS
    sheaves_namespace.cc
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
    sheaves_namespace.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

  )

collect_example_sources()