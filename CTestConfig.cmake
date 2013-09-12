#
# Copyright (c) 2013 Limit Point Systems, Inc. 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#=============================================================================
# CMake - Cross Platform Makefile Generator
# Copyright 2000-2009 Kitware, Inc., Insight Software Consortium
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
set(CTEST_PROJECT_NAME "SheafSystem" CACHE STRING "")
set(CTEST_NIGHTLY_START_TIME "8:00:00 UTC" CACHE STRING "")
set(CTEST_DROP_METHOD "http" CACHE STRING "")
set(CTEST_DROP_SITE "www.limitpoint.com" CACHE STRING "")
set(CTEST_DROP_LOCATION "/CDash/submit.php?project=SheafSystem" CACHE STRING "")
set(CTEST_DROP_SITE_CDASH TRUE CACHE BOOL "")
set(CTEST_CDASH_VERSION "2.0.2" CACHE STRING "")
set(CTEST_CDASH_QUERY_VERSION TRUE CACHE BOOL "")

# Mark the least used as advanced so as not to clutter up the ccmake interface.
# The user will want to change start time and drop site, so we will
# leave them unchanged.
mark_as_advanced(CTEST_PROJECT_NAME)
mark_as_advanced(CTEST_DROP_METHOD)
mark_as_advanced(CTEST_DROP_LOCATION)
mark_as_advanced(CTEST_DROP_SITE_CDASH)
mark_as_advanced(CTEST_CDASH_VERSION)
mark_as_advanced(CTEST_CDASH_QUERY_VERSION)