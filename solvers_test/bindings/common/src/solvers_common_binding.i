
//
// $RCSfile: solvers_common_binding.i,v $ $Revision: 1.5 $ $Date: 2012/03/01 00:41:38 $
//
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//
//
// Common SWIG interface to solvers cluster
//

//=============================================================================

//$$SCRIBBLE: This file contains only the part of the Swig interface which
//            is to be lists the classes, etc. to be wrapped.
//            We have to break the interface into two parts because
//            of the way Swig handles "%import" versus "%include".
//            If you change this file make sure you also change
//            "shell_common_binding_includes.i" as well.

//=============================================================================
// Ignore directives:
//=============================================================================

// Classes with a nested structs (which SWIG doesn't handle yet).


//=============================================================================

// Include the list of files to be inserted into the generated code.

%include "solvers_common_binding_includes.i"

//=============================================================================


//=============================================================================

// The list of classes, etc for which wrappers will be generated.

//$$SCRIBBLE: Note that order is important in the following list.  It must
//            follow the class hierarchies.

//=============================================================================



%include "algebraic_system.h"
%include       "banded_algebraic_system.h"
%include "linear_solver.h"
%include       "banded_solver.h"
%include             "direct_banded_solver.h"
%include "pde_solver.h"
%include       "banded_pde_solver.h"
%include "poisson_eqn.h"
%include "poisson_term_evaluator.h"
%include       "poisson_terms_0d.h"
%include       "poisson_terms_bilinear_2d.h"
%include       "poisson_terms_linear_1d.h"
%include       "poisson_terms_linear_2d.h"
%include       "poisson_terms_linear_3d.h"
%include       "poisson_terms_trilinear_3d.h"
