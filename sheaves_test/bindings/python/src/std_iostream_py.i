//
// $RCSfile: std_iostream_py.i,v $ $Revision: 1.8 $ $Date: 2012/03/01 00:41:16 $
//
//
// Copyright (c) 2012 Limit Point Systems, Inc.
//
//
// Swig interface for std::iostream (python version)
//

%{
#include "std_iostream.h"
%}

%inline %{
ostream* get_cout()
{
   return &cout;
}
%}
