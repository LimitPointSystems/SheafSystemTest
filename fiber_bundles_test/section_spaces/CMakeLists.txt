#
# Copyright (c) 2013 Limit Point Systems, Inc. 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER ${CMAKE_CURRENT_BINARY_DIR})

#
# Library sources.
#
set(SRCS
    test_sections.cc
   )

ShfSysTst_collect_sources(fiber_bundles_test "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_sections.impl.h
   )

ShfSysTst_collect_includes(fiber_bundles_test "${SRCS}" "${ADDITIONAL_INCS}")

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
    sec_e2.t.cc
    sec_e2_uniform.t.cc
    sec_e3.t.cc
    sec_e3_uniform.t.cc
    sec_e4.t.cc
    sec_ed.t.cc
    sec_jcb.t.cc
    sec_jcb_e13.t.cc
    sec_jcb_e23.t.cc
    sec_jcb_e33.t.cc
    sec_jcb_ed.t.cc
    sec_met.t.cc
    sec_met_e1.t.cc
    sec_met_e2.t.cc
    sec_met_e3.t.cc
    sec_met_ed.t.cc
    sec_st2.t.cc
    sec_st2_e2.t.cc
    sec_st2_e3.t.cc
    sec_st3.t.cc
    sec_st3_e3.t.cc
    sec_st4.t.cc
    sec_st4_e2.t.cc
    sec_st4_e3.t.cc
    sec_stp.t.cc
    sec_stp_space.t.cc
    sec_t2.t.cc
    sec_t2_e2.t.cc
    sec_t2_e3.t.cc
    sec_t3.t.cc
    sec_t3_e3.t.cc
    sec_t4.t.cc
    sec_t4_e2.t.cc
    sec_t4_e3.t.cc
    sec_tp.t.cc
    sec_tp_space.t.cc
    sec_tuple.t.cc
    sec_tuple_space.t.cc
    sec_vd.t.cc
    sec_vd_space.t.cc
    section.t.cc
   )

ShfSysTst_collect_unit_test_sources(fiber_bundles_test "${UNIT_TEST_SRCS}")

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS
   )

ShfSysTst_collect_example_sources(fiber_bundles_test "${EXAMPLE_SRCS}")
