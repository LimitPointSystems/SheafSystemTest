#
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
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
    any_lite.t.cc
    at0.t.cc    
    at0_space.t.cc    
    at1.t.cc
    at1_space.t.cc    
    at2.t.cc
    at2_e2.t.cc    
    at2_e3.t.cc    
    at3.t.cc
    at3_e3.t.cc    
    atp.t.cc 
    atp_space.t.cc    
    basis_transform.t.cc    
    e1.t.cc    
    e2.t.cc    
    e3.t.cc    
    e4.t.cc    
    ed.t.cc   
    gl2.t.cc    
    gl3.t.cc    
    gln.t.cc
    gln_space.t.cc    
    group.t.cc
    jcb.t.cc
    jcb_e13.t.cc    
    jcb_e23.t.cc    
    jcb_e33.t.cc    
    jcb_ed.t.cc
    jcb_space.t.cc    
    met.t.cc
    met_e1.t.cc    
    met_e2.t.cc    
    met_e3.t.cc    
    met_ed.t.cc
    st2.t.cc
    st2_e2.t.cc    
    st2_e3.t.cc    
    st3.t.cc
    st3_e3.t.cc    
    st4.t.cc
    st4_e2.t.cc    
    st4_e3.t.cc    
    stp.t.cc
    stp_space.t.cc    
    t2.t.cc
    t2_e2.t.cc    
    t2_e3.t.cc    
    t3.t.cc
    t3_e3.t.cc    
    t4.t.cc
    t4_e2.t.cc    
    t4_e3.t.cc    
    tp.t.cc
    tp_space.t.cc    
    tuple.t.cc
    tuple_space.t.cc    
    vd.t.cc   
    vd_space.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

)

collect_example_sources()
