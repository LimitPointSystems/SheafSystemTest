//
// $RCSfile: tools_java_binding.i,v $ $Revision: 1.3 $ $Date: 2012/03/01 00:41:42 $
//
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//
//
// Swig module interface file for tools (java version)
//

//=============================================================================

// Set the module name according to the LPS formula.

%module tools_java_binding

//=============================================================================

%import "fields_java_binding.i"
%include "tools_common_binding.i"

//=============================================================================

//$$ISSUE: Swig complains about the methods because the base type has a
//         different return type.
//$$TODO: Find a better solution than "%ignore".

%ignore double_dof_tuple::values();
%ignore float_dof_tuple::values();
%ignore int_dof_tuple::values();

//=============================================================================


