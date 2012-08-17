#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.6 $ $Date: 2012/07/05 19:18:17 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER iterators)

#
# Library sources.
#
set(SRCS
    algebraic_system.cc
    banded_algebraic_system.cc
    banded_pde_solver.cc
    banded_solver.cc
    direct_banded_solver.cc
    linear_solver.cc
    pde_solver.cc
    poisson_eqn.cc
    poisson_term_evaluator.cc
    poisson_terms_bilinear_2d.cc
    poisson_terms_linear_1d.cc
    poisson_terms_linear_2d.cc
    poisson_terms_linear_3d.cc
    poisson_terms_trilinear_3d.cc
    poisson_terms_0d.cc
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
    one_material_with_source_2d.t.cc
    two_materials_with_source_2d.t.cc
    solver_1d.t.cc
    solver_2d.t.cc
    solver_3d.t.cc
)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()
