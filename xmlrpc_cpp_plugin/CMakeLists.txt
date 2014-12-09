MESSAGE("")
MESSAGE("*")
MESSAGE("Building the xmlrpcpp plugin")
MESSAGE("*")
MESSAGE("")

SET (XMLRPC_CPP_PLUGIN_NAME xmlrpcpp_plugin)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY Cbuild)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

project ( ${XMLRPC_CPP_PLUGIN_NAME})

# Define the files that are part of the project. Set them in a variable, so that they can also be grouped.
SET (XMLRPCPP_SRC
  "./xmlrpc_cpp_start_up.h"
  "./xmlrpc_cpp_start_up.cpp"
  "./implservermethod.h"
  "./implservermethod.cpp"
  "./xmlrpcpp_retvalue.h"
  "./xmlrpcpp_retvalue.cpp"
  "./xmlrpc_cpp_buildopts"
  "./xmlrpcpp_serveroptions.h"
  "./xmlrpcpp_serveroptions.cpp"
)


SET ( XMLRPCPP_PLUGIN_V
  ${XMLRPCPP_SRC}
 )

# Group the files if the IDE supports it (very useful for visual studio) 
SOURCE_GROUP("xmlrpcpp_plugin" FILES ${XMLRPCPP_PLUGIN_V})

# Find other libraries (identify values for environment variables).
FIND_PACKAGE(Guslib_Local)
FIND_PACKAGE(XMLRPCpp_Local)

# Specify the include directories.
INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/serpents-rpc 
  ${CMAKE_SOURCE_DIR}/dependencies 
  ${CMAKE_SOURCE_DIR}/server-manager 
  ${GUSLIB_INCLUDE_DIR}/guslib 
)

# Specify additional link directories.
LINK_DIRECTORIES( ${CMAKE_SOURCE_DIR}/build)

ADD_DEFINITIONS(-DXMLRPC_CPP_EXP)
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

add_library( ${XMLRPC_CPP_PLUGIN_NAME} SHARED ${XMLRPCPP_PLUGIN_V} )

# ---------------- Link Libraries section --------------------
# Set the link options: the libraries to link against. Store them in a temporary variable
# as these are the common, cross-system link libraries.
SET (LINK_LIBS
  ${XMLLIB_XMLRPCpp_LIBRARY}
  ${GUSLIB_LIBRARY}
  server_manager
  serpents-rpc
)

# Append OS system specific libraries.
IF(WIN32)
  SET(LINK_LIBS
    ws2_32.lib
    winmm.lib
    ${LINK_LIBS}
    )
ELSEIF(UNIX AND NOT APPLE)
  SET(LINK_LIBS
    ${X11_X11_LIB}
    ${X11_Xrandr_LIB}
    ${LINK_LIBS}
    )
ENDIF()

# Set the link libraries for the project.
TARGET_LINK_LIBRARIES(${XMLRPC_CPP_PLUGIN_NAME} ${LINK_LIBS})
