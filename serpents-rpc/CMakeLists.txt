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

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
SET (SERPENTS_RPC_PROJECT_NAME serpents-rpc)

# Set the project to use: the rpc DLL.
# PROJECT (${SERPENTS_RPC_PROJECT_NAME})

# Set the include paths for the CMake scripts that will be used to find other libs.
# Add the project's CMake directories first, so they take precedence over the default CMake files.
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")
MESSAGE(STATUS "CMAKE_MODULE_PATH is ${CMAKE_MODULE_PATH}")
SET(SERPENTS_RPC_LIB_TYPE SHARED)


MESSAGE(STATUS "")
MESSAGE(STATUS "### Welcome to the serpents-rpc build system ###")
MESSAGE(STATUS "************************************************")
MESSAGE(STATUS "")

# 
# Specify some user configurable options
# 
OPTION(SERPENTS_RPC_BUILD_TESTS "Specify whether to build the tests (via the google test framework) or not." ON)

IF (${SERPENTS_RPC_BUILD_TESTS})

  # Search for the Google Test framework.
  ENABLE_TESTING()
  FIND_PACKAGE(GTestLocal REQUIRED)
  INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

ENDIF ()



include_directories("${CMAKE_SOURCE_DIR}/dependencies/")
include_directories("${CMAKE_SOURCE_DIR}/server-manager/")
link_directories("${CMAKE_SOURCE_DIR}/dependencies/bin/release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

SET ( SOURCE_FILES_SERVER
  "./serpents/rpc/server/server.h"
  "./serpents/rpc/server/server.cpp"
  "./serpents/rpc/server/method.hpp"
  "./serpents/rpc/server/method.cpp"
  "./serpents/rpc/server/repository.h"
  "./serpents/rpc/server/repository.cpp"
  "./serpents/rpc/server/rpcselector.h"
  "./serpents/rpc/server/rpcselector.cpp"
  "./serpents/rpc/server/serveroptions.h"
  "./serpents/rpc/server/serverstartup.h"
)

#SET (SOURCE_FILES_LAUNCHER
#  "./serpents/rpc/launcher/processrunner.h"
# "./serpents/rpc/launcher/processrunner.cpp"
#)
SET (SOURCE_FILES_LOG
  "./serpents/rpc/log/log.h"
  "./serpents/rpc/log/log.cpp"
  "./serpents/rpc/log/log_build_opts.h"
)
SET (SOURCE_FILES_PARAMETERS
 "./serpents/rpc/parameters/parametercontainer.hpp"
 "./serpents/rpc/parameters/parametercontainer.cpp"
  "./serpents/rpc/parameters/any.h"
  "./serpents/rpc/parameters/any.cpp"
 "./serpents/rpc/parameters/retvalue.h"
 "./serpents/rpc/parameters/retvalue.cpp"
 
 )

SET (SOURCE_FILES_BASE
 "./serpents/rpc/base.h"
)
SET (SOURCE_FILES
  ${SOURCE_FILES_BASE}
  ${SOURCE_FILES_PARAMETERS}
  ${SOURCE_FILES_SERVER}
  ${SOURCE_FILES_LAUNCHER}
  ${SOURCE_FILES_LOG}
 
)

#visual studio
SOURCE_GROUP("serpents\\rpc" FILES
  ${SOURCE_FILES_BASE}
)

SOURCE_GROUP("serpents\\rpc\\server\\" FILES
  ${SOURCE_FILES_SERVER}
)

SOURCE_GROUP("serpents\\rpc\\launcher\\" FILES
  ${SOURCE_FILES_LAUNCHER}
)

SOURCE_GROUP("serpents\\rpc\\log" FILES
  ${SOURCE_FILES_LOG}
)
SOURCE_GROUP("serpents\\rpc\\parameters" FILES
  ${SOURCE_FILES_PARAMETERS}
)

LINK_DIRECTORIES("${CMAKE_SOURCE_DIR}/build")
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
SOURCE_GROUP("" FILES ${SOURCE_FILES})


ADD_LIBRARY(${SERPENTS_RPC_PROJECT_NAME} SHARED ${SOURCE_FILES})

# Set the link dependencies.
# Note: This should be done for the test projects.

FIND_PACKAGE(XMLRPC_C_Locall)
FIND_PACKAGE(XMLRPCpp_Local)
FIND_PACKAGE(LOG4CPP_Local)
FIND_PACKAGE(GUSLIB_Local)

INCLUDE_DIRECTORIES("${GUSLIB_INCLUDE_DIR}")

# ---------------- Link Libraries section --------------------
# Set the link options: the libraries to link against. Store them in a temporary variable
# as these are the common, cross-system link libraries.
SET (LINK_LIBS_SERPENTS_RPC
  server_manager
  ${GUSLIB_LIBRARY}
)

# Append OS system specific libraries.
IF(WIN32)
  SET(LINK_LIBS_SERPENTS_RPC
#     ws2_32.lib
#     winmm.lib
#     odbc32.lib
#     odbccp32.lib
    ${LINK_LIBS_SERPENTS_RPC}
    )
ELSEIF(UNIX AND NOT APPLE)
  SET(LINK_LIBS_SERPENTS_RPC
    ${X11_X11_LIB}
    ${X11_Xrandr_LIB}
    ${LINK_LIBS_SERPENTS_RPC}
    )
ENDIF()

TARGET_LINK_LIBRARIES(${SERPENTS_RPC_PROJECT_NAME} ${LINK_LIBS_SERPENTS_RPC}) 

ADD_DEFINITIONS(-DSERPENTSRPC_EXPORTS -DSERVERMGR_EXP)
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

IF (SERPENTS_RPC_USELOG4CPP)
  LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/bin/release/log4cpp")
  TARGET_LINK_LIBRARIES(${SERPENTS_RPC_PROJECT_NAME} ${LOG4CPP_LIBRARY})
  ADD_DEFINITIONS(-DUSE_LOG4CPP)
ENDIF ()

INSTALL (TARGETS ${SERPENTS_RPC_PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library
    )
