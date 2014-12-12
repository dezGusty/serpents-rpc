#-------------------------------------------------------------------
# This file is part of the CMake build system for the serpents-rpc library
#-------------------------------------------------------------------

# Configure Components build
cmake_minimum_required(VERSION 2.6)

# 
# Specify some user configurable options
# 
OPTION(SERPENTS_RPC_BUILD_CORE "Build the core lib" ON)
OPTION(SERPENTS_RPC_BUILD_UNIT_TESTS "Build a test, linking to the guslib library" ON)
OPTION(SERPENTS_RPC_USELOG4CPP "Use the log4cpp lib for logging" ON)
OPTION(SERPENTS_RPC_BUILD_SSL_SERVER_PLUGIN "build ssl server plugin" ON)
OPTION(SERPENTS_RPC_BUILD_XMLRPC_C_PLUGIN "build xmlrpc_c plugin" ON)
OPTION(SERPENTS_RPC_BUILD_XMLRPC_CPP_PLUGIN "build xmlrpcpp plugin" ON)
OPTION(SERPENTS_RPC_BUILD_LAUNCHER "build launcher" OFF)
OPTION(UNITTEST_SERVER "Build unit tests for ssl-plugin" ON)
OPTION(UNITTEST_XMLRPC_C_CLIENT "Build unit tests for xmlrpc_c plugin" ON)
OPTION(UNITTEST_SSL_CLIENT "Build unit tests for ssl plugin" ON)
OPTION(UNITTEST_LAUNCHER "Build test-launcher" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)


#
# Also load the CMakeLists file in sub-folders.
#
add_subdirectory(server-manager)
if (SERPENTS_RPC_BUILD_CORE)
  add_subdirectory(serpents-rpc)
endif ()

if (SERPENTS_RPC_BUILD_SSL_SERVER_PLUGIN )
  add_subdirectory(serpents-ssl)
endif ()

if (SERPENTS_RPC_BUILD_XMLRPC_C_PLUGIN)
  add_subdirectory(xmlrpc_c_plugin)
endif ()

if (SERPENTS_RPC_BUILD_UNIT_TESTS)
  add_subdirectory(tests)
endif ()

if(SERPENTS_RPC_BUILD_XMLRPC_CPP_PLUGIN)
  add_subdirectory(xmlrpc_cpp_plugin)
endif()
if(SERPENTS_RPC_BUILD_LAUNCHER)
add_subdirectory(serpents-launcher)
endif()

