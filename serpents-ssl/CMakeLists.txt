
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

find_package(Boost 1.36.0 COMPONENTS system date_time regex REQUIRED)
find_package(OpenSSL REQUIRED)


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
 "${CMAKE_CURRENT_SOURCE_DIR}/server/unyield.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/yield.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/mime_types.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/reply.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/request_parser.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/requesthandler.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/server.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/server/serverfunctionrepository.cpp"
 
)
SET(SOURCE_FILES_PARAMETER 
	"${CMAKE_CURRENT_SOURCE_DIR}/parametercontainer/parametercontainer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/parametercontainer/parametercontainer.cpp"
	)

SET (SOURCE_FILES_BASE "${CMAKE_CURRENT_SOURCE_DIR}/base.h")

SET(SOURCE_FILES_PUGIXML 
 "${PugiXML_BASE}/pugixml.cpp"
 "${PugiXML_BASE}/pugiconfig.hpp"
 "${PugiXML_BASE}/pugixml.hpp"
	)


SET (SOURCE_FILES
  ${SOURCE_FILES_BASE}
  ${SOURCE_FILES_SERVER}
  ${SOURCE_FILES_PARAMETER}
  ${SOURCE_FILES_PUGIXML}
  
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
  ${SOURCE_FILES_PARAMETER}
  ${SOURCE_FILES_PARAMETER}
)
SOURCE_GROUP("serpents\\ssl-server\\pugixml\\" FILES
  ${SOURCE_FILES_PUGIXML}
)




include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PugiXML_BASE})

source_group("" FILES ${SOURCE_FILES})

add_library(serpents_ssl SHARED ${SOURCE_FILES})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR} )

add_definitions(/D _WIN32_WINNT=0x0501 -D_SCL_SECURE_NO_WARNINGS )
target_link_libraries(serpents_ssl Ws2_32.lib odbc32.lib odbccp32.lib  ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})






