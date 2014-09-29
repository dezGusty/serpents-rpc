#------------------------------------------------------------------------------
# This file is part of the CMake build system for the serpents-rpc library.
# The serpents-rpc library is distributed under the terms of the MIT software
# license.
#------------------------------------------------------------------------------
# The MIT License (MIT)
#
# Copyright (c) 2014 - The serpents-rpc Team
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Configure Components build
cmake_minimum_required(VERSION 3.0)

# 
# Specify some user configurable options
# 
option(SERPENTS_RPC_BUILD_CORE "Build the core lib" ON)
option(SERPENTS_RPC_BUILD_UNIT_TESTS "Build a test, linking to the guslib library" ON)
option(SERPENTS_RPC_USELOG4CPP "Use the log4cpp lib for logging" ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#project(serpents-rpc)

#
# Also load the CMakeLists file in sub-folders.
#
if (SERPENTS_RPC_BUILD_CORE)
  add_subdirectory(serpents-rpc)
endif ()


if (SERPENTS_RPC_BUILD_UNIT_TESTS)
  add_subdirectory(tests)
endif ()
 

