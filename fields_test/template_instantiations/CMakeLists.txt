#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.1.2.1 $ $Date: 2012/10/19 02:31:27 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER maps)

#
# Library sources.
#
set(SRCS

)
##    test_fields.cc

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS

)
##    test_fields.impl.h
  
collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    fields_block.inst.t.cc
    fields_auto_block.inst.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
