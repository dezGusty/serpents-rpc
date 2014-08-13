#-------------------------------------------------------------------
# This file is part of the CMake build system for the serpents-rpc library
#-------------------------------------------------------------------

# Configure Components build
cmake_minimum_required(VERSION 2.6)

# 
# Specify some user configurable options
# 
option(SERPENTS_RPC_BUILD_CORE "Build the core lib" ON)
option(SERPENTS_RPC_BUILD_UNIT_TESTS "Build a test, linking to the guslib library" ON)


project(serpents-rpc)

#
# Also load the CMakeLists file in sub-folders.
#
if (SERPENTS_RPC_BUILD_CORE)
  add_subdirectory(serpents-rpc)
endif ()


if (SERPENTS_RPC_BUILD_UNIT_TESTS)
  add_subdirectory(tests)
endif ()
 

