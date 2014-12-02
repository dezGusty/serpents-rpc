SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

MESSAGE("")
MESSAGE("*")
MESSAGE("Building serpents-ssl")
MESSAGE("*")
MESSAGE("")

find_package(Boost 1.36.0 COMPONENTS system date_time regex REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Guslib_Local)

find_path(PugiXML_BASE pugixml.hpp
  PATHS ${PROJECT_SOURCE_DIR}
   PATH_SUFFIXES dependencies/pugixml
  )

include_directories(${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
SET (SOURCE_FILES_SERVER
 "${CMAKE_CURRENT_SOURCE_DIR}/server/coroutine.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/header.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/mime_types.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/reply.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/request.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/request_parser.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/requesthandler.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/server.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/serverfunctionrepository.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/session.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/session.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/unyield.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/yield.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/mime_types.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/reply.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/request_parser.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/requesthandler.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/server.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/serverfunctionrepository.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/serpents_ssl_startup.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/serpents_ssl_startup.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/ssl_server_build_opts.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/serpents_ssl_serveroptions.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/serpents_ssl_serveroptions.cpp"
 

)
SET(SOURCE_FILES_PARAMETER 
  "${CMAKE_CURRENT_SOURCE_DIR}/parametercontainer/parametercontainer.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/parametercontainer/parametercontainer.cpp"
  )

SET (SOURCE_FILES_BASE "${CMAKE_CURRENT_SOURCE_DIR}/base.h")

SET(SOURCE_FILES_PUGIXML 
 "${CMAKE_SOURCE_DIR}/dependencies/pugixml/pugiconfig.hpp"
 "${CMAKE_SOURCE_DIR}/dependencies/pugixml/pugixml.hpp"
 "${CMAKE_SOURCE_DIR}/dependencies/pugixml/pugixml.cpp"
  )

#SET (SOURCE_FILES_LOG 
#"${CMAKE_CURRENT_SOURCE_DIR}/log/log.h"
# "${CMAKE_CURRENT_SOURCE_DIR}/log/log.cpp"
# )
 
 SET(SOURCE_FILES_UTIL
  "${CMAKE_CURRENT_SOURCE_DIR}/util/xmlutil.hpp")
 

 SET(SOURCE_FILES_CLIENT
"${CMAKE_CURRENT_SOURCE_DIR}/client/client.hpp")


SET (SOURCE_FILES
  ${SOURCE_FILES_BASE}
  ${SOURCE_FILES_SERVER}
  ${SOURCE_FILES_PARAMETER}
  ${SOURCE_FILES_PUGIXML}
#  ${SOURCE_FILES_LOG}
  ${SOURCE_FILES_UTIL}
  ${SOURCE_FILES_CLIENT}
)


#visual studio 

SOURCE_GROUP("serpents\\ssl-server" FILES
  ${SOURCE_FILES_BASE}
)

SOURCE_GROUP("serpents\\ssl-server\\server\\" FILES
  ${SOURCE_FILES_SERVER}
)

SOURCE_GROUP("serpents\\ssl-server\\parameter\\" FILES
  ${SOURCE_FILES_PARAMETER}
)
SOURCE_GROUP("serpents\\ssl-server\\pugixml\\" FILES
  ${SOURCE_FILES_PUGIXML}
)
#SOURCE_GROUP("serpents\\ssl-server\\log" FILES
#  ${SOURCE_FILES_LOG}
#)
SOURCE_GROUP("serpents\\util" FILES
   ${SOURCE_FILES_UTIL}
)
SOURCE_GROUP("serpents\\client" FILES
   ${SOURCE_FILES_CLIENT}
)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/server-manager)
include_directories(${GUSLIB_INCLUDE_DIR}/guslib)
include_directories(${PROJECT_SOURCE_DIR}/serpents-rpc/)
include_directories(${PugiXML_BASE})
include_directories(${PROJECT_SOURCE_DIR}/dependencies/)
source_group("" FILES ${SOURCE_FILES})
link_directories("${PROJECT_SOURCE_DIR}/build/")
add_library(serpents_ssl SHARED ${SOURCE_FILES})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR} )

add_definitions(/D _WIN32_WINNT=0x0501 -D_SCL_SECURE_NO_WARNINGS -DSSL_SERVER_EXPORT -DSSLSERVER_EXP )
target_link_libraries(serpents_ssl Ws2_32.lib odbc32.lib odbccp32.lib server_manager.lib serpents-rpc.lib ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${GUSLIB_LIBRARY} )

if (SERPENTS_RPC_USELOG4CPP)
 FIND_PACKAGE(LOG4CPP_Local)
  target_link_libraries(serpents_ssl ${LOG4CPP_LIBRARY})
  add_definitions(-DUSE_LOG4CPP)
endif ()






