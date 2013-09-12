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
    test_fields.cc
   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_fields.impl.h
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
    field_jcb_e13.t.cc
    field_jcb_e23.t.cc
    field_jcb_e33.t.cc
    field_jcb_ed.t.cc
    field_jcb.t.cc
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
