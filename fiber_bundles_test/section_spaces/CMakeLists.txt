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

set(CLUSTER section_spaces)

#
# Library sources.
#
set(SRCS
    sec_at0.cc
    sec_at0_space.cc
    sec_at1.cc
    sec_at1_space.cc
    sec_at2_e2.cc
    sec_at2.cc
    sec_at2_e3.cc
    sec_at3.cc
    sec_at3_e3.cc
    sec_atp.cc
    sec_atp_space.cc
    sec_e1.cc
    sec_e1_uniform.cc
    sec_e2.cc
    sec_e2_uniform.cc
    sec_e3.cc
    sec_e3_uniform.cc
    sec_e4.cc
    sec_ed.cc
    sec_jcb.cc
    sec_jcb_space.cc
    sec_jcb_e13.cc
    sec_jcb_e23.cc
    sec_jcb_e33.cc
    sec_jcb_ed.cc
    sec_met.cc
    sec_met_e1.cc
    sec_met_e2.cc
    sec_met_e3.cc
    sec_met_ed.cc
    sec_st2.cc
    sec_st2_e2.cc
    sec_st2_e3.cc
    sec_st3.cc
    sec_st3_e3.cc
    sec_st4.cc
    sec_st4_e2.cc
    sec_st4_e3.cc
    sec_stp.cc
    sec_stp_space.cc
    sec_t2.cc
    sec_t2_e2.cc
    sec_t2_e3.cc
    sec_t3.cc
    sec_t3_e3.cc
    sec_t4.cc
    sec_t4_e3.cc
    sec_t4_e2.cc
    sec_tp.cc
    sec_tp_space.cc
    sec_tuple.cc
    sec_tuple_space.cc
    sec_vd.cc
    sec_vd_space.cc
    sec_rep_descriptor.cc
    sec_rep_descriptor_poset.cc
    sec_rep_space.cc
    sec_rep_space_member.cc
    section_space_factory.cc
    section_space_schema_member.cc
    section_space_schema_poset.cc
    section_traits.cc
    binary_section_space_schema_member.cc
    binary_section_space_schema_poset.cc
    test_sections.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    sec_vd.impl.h 
    sec_rep_descriptor_table_dofs_type.h 
    section_space_factory.impl.h 
    section_space_schema_table_dofs_type.h 
    test_sections.impl.h
  )

collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    fields.t.cc
    multi_section.t.cc
    sec_at0_space.t.cc
    sec_at0.t.cc
    sec_at1_space.t.cc
    sec_at2_e2.t.cc
    sec_at2_e3.t.cc
    sec_at3_e3.t.cc
    sec_atp_space.t.cc
    sec_e1.t.cc
    sec_e1_uniform.t.cc
    sec_e2.t.cc
    sec_e2_uniform.t.cc
    sec_e3.t.cc
    sec_e3_uniform.t.cc
    sec_met_e1.t.cc
    sec_met_e2.t.cc
    sec_met_e3.t.cc
    sec_st2_e2.t.cc
    sec_st2_e3.t.cc
    sec_st3_e3.t.cc
    sec_st4_e2.t.cc
    sec_st4_e3.t.cc
    sec_stp_space.t.cc
    sec_t2_e2.t.cc
    sec_t2_e3.t.cc
    sec_t3_e3.t.cc
    sec_t4_e2.t.cc
    sec_t4_e3.t.cc
    sec_tp_space.t.cc
    sec_tuple_space.t.cc
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