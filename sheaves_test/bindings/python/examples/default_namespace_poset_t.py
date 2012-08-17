#! /usr/bin/env python
##
## $RCSfile: default_namespace_poset_t.py,v $ $Revision: 1.5 $ $Date: 2012/03/01 00:41:16 $
##
##
## Copyright (c) 2012 Limit Point Systems, Inc.
##

from sheaves_python_binding import *

## Make the default namespace.

ns = namespace_poset("default_namespace_poset_t")

## Output a text version to stdout.

ns.to_stream();

##  Need read access to write namespace to a file.

ns.get_read_write_access()

##  Write it to a file.

sa = storage_agent("default_namespace_t.hdf")
sa.write_entire(ns)