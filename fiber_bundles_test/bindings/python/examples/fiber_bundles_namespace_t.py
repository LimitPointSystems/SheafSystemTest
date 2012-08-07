#! /usr/bin/env python

##
## $RCSfile: fiber_bundles_namespace_t.py,v $ $Revision: 1.8 $ $Date: 2012/03/01 00:40:36 $
##
##
## Copyright (c) 2012 Limit Point Systems, Inc.
##

##$$TODO: Figure out how to combine these.

from sheaves_python_binding import *
from fiber_bundles_python_binding import *

## Make the sheaves namespace.

ns = fiber_bundles_namespace("fiber_bundles_namespace_t")

## Output a text version to stdout.

ns.to_stream()

##  Need read access to write namespace to a file.

ns.get_read_write_access()

##  Write it to a file.

sa = storage_agent("fiber_bundles_namespace_t.hdf")
sa.write_entire(ns)

