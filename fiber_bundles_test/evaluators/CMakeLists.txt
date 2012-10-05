#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.7 $ $Date: 2012/07/05 19:18:15 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER evaluators)

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
    bilinear_2d.t.cc
    constant_eval_family.t.cc
    constant_hex.t.cc 
    constant_quad.t.cc 
    constant_segment.t.cc 
    constant_tet.t.cc 
    constant_triangle.t.cc 
    dlinear_eval_family.t.cc
    linear_1d.t.cc 
    linear_2d.t.cc 
    linear_3d.t.cc
    quadratic_1d.t.cc
    quadratic_2d.t.cc
    quadratic_3d.t.cc
    trilinear_3d.t.cc
    uniform_1d.t.cc
    uniform_2d.t.cc
    uniform_3d.t.cc
    uniform_eval_family.t.cc
)

collect_unit_test_sources()

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()

