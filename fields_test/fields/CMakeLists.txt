#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.6 $ $Date: 2012/07/05 19:18:16 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER fields)

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
    field_at0.t.cc
    field_at2_e2.t.cc
    field_at2_e3.t.cc
    field_at3_e3.t.cc
    field_e1.t.cc
    field_e1_uniform.t.cc
    field_e2.t.cc
    field_e2_uniform.t.cc
    field_e3.t.cc
    field_e3_uniform.t.cc
    field_e4.t.cc
    field_met_e1.t.cc
    field_met_e2.t.cc
    field_met_e3.t.cc
    field_st2_e2.t.cc
    field_st2_e3.t.cc
    field_st3_e3.t.cc
    field_st4_e2.t.cc
    field_st4_e3.t.cc
    field_t2_e2.t.cc
    field_t2_e3.t.cc
    field_t3_e3.t.cc
    field_t4_e2.t.cc
    field_t4_e3.t.cc
    field_factory.t.cc
    field_factory_2.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
