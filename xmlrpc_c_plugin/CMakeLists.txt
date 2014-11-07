MESSAGE("")
MESSAGE("*")
MESSAGE("Building the xmlrpc_c plugin")
MESSAGE("*")
MESSAGE("")

link_directories("${CMAKE_SOURCE_DIR}/dependencies/bin/release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

SET ( SRC_FLIES_XMLRPC_C
  "./implservermethod.h"
  "./implservermethod.cpp"
  "./parametercontainer.cpp"
  "./retvalue.h"
  "./retvalue.cpp"
  "./xmlrpc_c_buildopts.h"
  "./xmlrpc_c_plugin.h"
  "./xmlrpc_c_serveroptions.h"
  "./xmlrpc_c_serveroptions.cpp"
  "./xmlrpc_c_startup.h"
  "./xmlrpc_c_startup.cpp"
 )