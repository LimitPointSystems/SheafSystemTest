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

set(CLUSTER fiber_spaces)

#
# Library sources.
#
set(SRCS   
    test_fibers.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    test_fibers.impl.h
)

collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
    e1_x.t.cc
    e2_x.t.cc
    e3_x.t.cc
    ed_x.t.cc   
    at0_x.t.cc
    at1_x.t.cc
    at2_x.t.cc
    at2_e2_x.t.cc
    at2_e3_x.t.cc
    at3_x.t.cc
    at3_e3_x.t.cc
    atp_x.t.cc 
    stp_x.t.cc
    st2_x.t.cc
    st3_x.t.cc
    st4_x.t.cc
    tp_x.t.cc
    t2_x.t.cc
    t3_x.t.cc
    t4_x.t.cc
    vd_x.t.cc   
    basis_transform.t.cc    
    at0_space.t.cc    
    at0.t.cc    
    at1_space.t.cc    
    at2_e2.t.cc    
    at2_e3.t.cc    
    at3_e3.t.cc    
    atp_space.t.cc    
    e1.t.cc    
    e2.t.cc    
    e3.t.cc    
    e4.t.cc    
    gl2.t.cc    
    gl3.t.cc    
    gln_space.t.cc    
    jcb_e13.t.cc    
    jcb_e23.t.cc    
    jcb_e33.t.cc    
    jcb_space.t.cc    
    met_e1.t.cc    
    met_e2.t.cc    
    met_e3.t.cc    
    st2_e2.t.cc    
    st2_e3.t.cc    
    st3_e3.t.cc    
    st4_e2.t.cc    
    st4_e3.t.cc    
    stp_space.t.cc    
    t2_e2.t.cc    
    t2_e3.t.cc    
    t3_e3.t.cc    
    t4_e2.t.cc    
    t4_e3.t.cc    
    tp_space.t.cc    
    tuple_space.t.cc    
    vd_space.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

)

collect_example_sources()
