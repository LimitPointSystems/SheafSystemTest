
//
// $RCSfile: geometry_java_binding.i,v $ $Revision: 1.3 $ $Date: 2012/03/01 00:41:13 $
//
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//
//
// SWIG interface to geometry cluster (java version)
//

//=============================================================================

%module geometry_java_binding

%include "arrays_java.i"

//$$ISSUE: We might want to build the geometry bindings but not components/tools.
//         So what do we do here?

%import "fiber_bundles_java_binding.i"
%include "geometry_common_binding.i"

//=============================================================================
//=============================================================================

%{
#include "std_iostream.h"
%}
                                                                                                    
%inline %{
ostream* get_cout()
{
   return &cout;
}
%}
                                                                                                    
