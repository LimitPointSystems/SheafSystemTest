::
:: $RCSfile$ $Revision$ $Date$
::
::
:: Copyright (c) 2012 Limit Point Systems, Inc.
::
::

@echo off

:: Make vars local, and delay expansion until runtime.
Setlocal EnableDelayedExpansion
:: Var definitions.
set lib_dir=%RELEASE_DIR%\Components-Win64\lib\%1

:: Make the dir if it doesnt exist, else remove it's contents.
if not exist %lib_dir% (mkdir %lib_dir%) else (del /Q %lib_dir%)
