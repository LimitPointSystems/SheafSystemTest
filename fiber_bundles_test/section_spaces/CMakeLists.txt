#
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER section_spaces)

#
# Library sources.
#
set(SRCS
    test_sections.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_sections.impl.h
  )

collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    fields.t.cc
    multi_section.t.cc
    sec_at0.t.cc
    sec_at0_space.t.cc
    sec_at1.t.cc
    sec_at1_space.t.cc
    sec_at2.t.cc
    sec_at2_e2.t.cc
    sec_at2_e3.t.cc
    sec_at3.t.cc
    sec_at3_e3.t.cc
    sec_atp.t.cc
    sec_atp_space.t.cc
    sec_e1.t.cc
    sec_e1_uniform.t.cc
    sec_e1_uniform_x.t.cc
    sec_e2.t.cc
    sec_e2_uniform.t.cc
    sec_e2_uniform_x.t.cc
    sec_e3.t.cc
    sec_e3_uniform.t.cc
    sec_e3_uniform_x.t.cc
    sec_e4.t.cc
    sec_ed.t.cc
    sec_jcb.t.cc
    sec_jcb_e13_x.t.cc
    sec_jcb_e23_x.t.cc
    sec_jcb_e33_x.t.cc
    sec_jcb_ed.t.cc
    sec_met.t.cc
    sec_met_e1.t.cc
    sec_met_e1_x.t.cc
    sec_met_e2.t.cc
    sec_met_e2_x.t.cc
    sec_met_e3.t.cc
    sec_met_e3_x.t.cc
    sec_met_ed.t.cc
    sec_st2.t.cc
    sec_st2_e2.t.cc
    sec_st2_e2_x.t.cc
    sec_st2_e3.t.cc
    sec_st2_e3_x.t.cc
    sec_st3.t.cc
    sec_st3_e3.t.cc
    sec_st3_e3_x.t.cc
    sec_st4.t.cc
    sec_st4_e2.t.cc
    sec_st4_e2_x.t.cc
    sec_st4_e3.t.cc
    sec_st4_e3_x.t.cc
    sec_stp.t.cc
    sec_stp_space.t.cc
    sec_t2.t.cc
    sec_t2_e2.t.cc
    sec_t2_e2_x.t.cc
    sec_t2_e3.t.cc
    sec_t2_e3_x.t.cc
    sec_t3.t.cc
    sec_t3_e3.t.cc
    sec_t3_e3_x.t.cc
    sec_t4.t.cc
    sec_t4_e2.t.cc
    sec_t4_e2_x.t.cc
    sec_t4_e3.t.cc
    sec_t4_e3_x.t.cc
    sec_tp.t.cc
    sec_tp_space.t.cc
    sec_tuple.t.cc
    sec_tuple_space.t.cc
    sec_vd.t.cc
    sec_vd_space.t.cc
    section.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
