
//
// $RCSfile: fields_java_binding.i,v $ $Revision: 1.4 $ $Date: 2012/03/01 00:41:02 $
//
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//
//
// SWIG interface to fields cluster (java version)
//

//=============================================================================

%module fields_java_binding

%include "arrays_java.i"

//$$ISSUE: We might want to build the fields bindings but not components/tools.
//         So what do we do here?

%import "geometry_java_binding.i"
%include "fields_common_binding.i"

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
                                                                                                    
