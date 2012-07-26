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
    any_lite.cc    
    at0.cc    
    at0_space.cc    
    at1.cc    
    at1_space.cc    
    at2.cc    
    at2_e2.cc    
    at2_e3.cc    
    at3.cc    
    at3_e3.cc    
    atp.cc    
    atp_space.cc    
    e1.cc    
    e2.cc    
    e3.cc    
    e4.cc    
    ed.cc    
    gl2.cc    
    gl3.cc    
    gln.cc    
    gln_space.cc    
    group.cc    
    jcb.cc    
    jcb_space.cc    
    jcb_e13.cc    
    jcb_e23.cc    
    jcb_e33.cc    
    jcb_ed.cc    
    met.cc    
    met_e1.cc    
    met_e2.cc    
    met_e3.cc    
    met_ed.cc    
    st2.cc    
    st2_e2.cc    
    st2_e3.cc    
    st3.cc    
    st3_e3.cc    
    st4.cc    
    st4_e2.cc    
    st4_e3.cc    
    stp.cc    
    stp_space.cc    
    t2.cc    
    t2_e2.cc    
    t2_e3.cc    
    t3.cc    
    t3_e3.cc    
    t4.cc    
    t4_e2.cc    
    t4_e3.cc    
    tensor_variance.cc    
    tp.cc    
    tp_space.cc    
    tuple.cc    
    tuple_space.cc    
    vd.cc    
    vd_space.cc    
    test_fibers.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    at0.impl.h 
    at1.impl.h 
    at2_e2.impl.h 
    at2_e3.impl.h 
    at2.impl.h 
    at3_e3.impl.h 
    at3.impl.h 
    atp.impl.h 
    e1.impl.h 
    e2.impl.h 
    e3.impl.h 
    e4.impl.h 
    ed.impl.h 
    gl2.impl.h 
    gl3.impl.h 
    gln_table_dofs_type.h 
    gln.impl.h 
    group.impl.h 
    jcb_e13.impl.h 
    jcb_e23.impl.h 
    jcb_e33.impl.h 
    jcb_ed.impl.h 
    jcb_table_dofs_type.h 
    jcb.impl.h 
    met_e1.impl.h 
    met_e2.impl.h 
    met_e3.impl.h 
    met_ed.impl.h 
    met.impl.h 
    st2_e2.impl.h 
    st2_e3.impl.h 
    st2.impl.h 
    st3_e3.impl.h 
    st3.impl.h 
    st4_e2.impl.h 
    st4_e3.impl.h 
    stp.impl.h 
    t2_e2.impl.h 
    t2_e3.impl.h 
    t3_e3.impl.h 
    t4_e2.impl.h 
    t4_e3.impl.h 
    test_fibers.impl.h 
    tp.impl.h 
    tp_table_dofs_type.h 
    tuple.impl.h 
    tuple_table_dofs_type.h 
    vd.impl.h 
    vd_table_dofs_type.h
  )

collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS    
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
    test.t.cc    
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