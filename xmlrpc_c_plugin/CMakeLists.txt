MESSAGE("")
MESSAGE("*")
MESSAGE("Building the xmlrpc_c plugin")
MESSAGE("*")
MESSAGE("")

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

#xmlrpc_c include and lib
find_package(XMLRPC_C_Locall REQUIRED)
include_directories(${XMLRPC_C_INCLUDE_DIRS})
link_directories(${XMLRPC_C_LIBRARY})

include_directories("${CMAKE_SOURCE_DIR}/server-manager/" 
          "${CMAKE_SOURCE_DIR}/serpents-rpc/"
          "${CMAKE_SOURCE_DIR}/dependencies"
          )

link_directories("${CMAKE_SOURCE_DIR}/build")


SET ( SRC_FLIES_ALL
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
 
 #vixual studio 
 SET (SRC_FLIES_XMLRPC_C
  ${SRC_FLIES_ALL}
 
)
 
 SOURCE_GROUP("xmlrpc_c_plugin" FILES
  ${SRC_FLIES_ALL}
)
FIND_PACKAGE(GUSLIB_Local)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${GUSLIB_INCLUDE_DIR}/guslib)
source_group("" FILES ${SRC_FLIES_XMLRPC_C})

add_library(xmlrpc_c_plugin SHARED ${SRC_FLIES_XMLRPC_C})

target_link_libraries(xmlrpc_c_plugin serpents-rpc.lib server_manager.lib ${XMLLIB_XMLRPC_C_LIBRARY} ${GUSLIB_LIBRARY})
#add guslib 
add_definitions(-DXMLRPC_C_PLUGIN_EXPORTS -DPLUGINXMLRPC_C_EXP -DGUSLIB_IMP )

#LOG4CPP logging lib
if (SERPENTS_RPC_USELOG4CPP)
 FIND_PACKAGE(LOG4CPP_Local)
  target_link_libraries(xmlrpc_c_plugin ${LOG4CPP_LIBRARY})
  add_definitions(-DUSE_LOG4CPP)
endif ()

