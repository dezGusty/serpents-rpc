MESSAGE("")
MESSAGE("*")
MESSAGE("Building the server-manager")
MESSAGE("*")
MESSAGE("")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

SET(XMLRPCPP_SRC 
	"./xmlrpc_cpp_start_up.h"
	"./xmlrpc_cpp_start_up.cpp"
)

SET ( XMLRPCPP_SRC
  ${XMLRPCPP_PLUGIN}
 )

source_group("xmlrpcpp_plugin" FILES ${XMLRPCPP_PLUGIN})