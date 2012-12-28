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

set(CLUSTER support)

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
    arg_list.t.cc
    deep_size.t.cc
    error_message.t.cc
    int_set.t.cc
    interval_set.t.cc
    primitive_value.t.cc
    rc.t.cc
    stop_watch.t.cc
    tolerance_comparison.t.cc
    zn_to_bool.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
