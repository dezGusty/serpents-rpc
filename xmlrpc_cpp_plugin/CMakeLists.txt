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

SET (XMLRPCPP_SRC
	"./xmlrpc_cpp_start_up.h"
	"./xmlrpc_cpp_start_up.cpp"
	"./implservermethod.h"
	"./implservermethod.cpp"
	"./xmlrpcpp_retvalue.h"
	"./xmlrpcpp_retvalue.cpp"
	"./xmlrpc_cpp_buildopts"
)


SET ( XMLRPCPP_PLUGIN_V
  ${XMLRPCPP_SRC}
 )
#for visual studio 
source_group("xmlrpcpp_plugin" FILES ${XMLRPCPP_PLUGIN_V})


find_package(Guslib_Local)

include_directories(${CMAKE_SOURCE_DIR}/serpents-rpc/ ${CMAKE_SOURCE_DIR}/dependencies 
								${CMAKE_SOURCE_DIR}/server-manager ${GUSLIB_INCLUDE_DIR}/guslib 
)
link_directories( ${CMAKE_SOURCE_DIR}/build)

add_definitions(-DXMLRPC_CPP_EXP)

add_library( ${XMLRPC_CPP_PLUGIN_NAME} SHARED ${XMLRPCPP_PLUGIN_V} )

target_link_libraries(${XMLRPC_CPP_PLUGIN_NAME} xmlrpc.lib server_manager.lib serpents-rpc.lib ${GUSLIB_LIBRARY})
