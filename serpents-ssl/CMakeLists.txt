
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(Boost 1.36.0 COMPONENTS system date_time regex REQUIRED)
find_package(OpenSSL REQUIRED)
include_directories(${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
SET (SOURCE_FILES_INCLUDE
 "${CMAKE_CURRENT_SOURCE_DIR}/include/base.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/coroutine.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/header.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/mime_types.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/parametercontainer/parametercontainer.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/reply.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/request.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/request_parser.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/requesthandler.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/server.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/serverfunctionrepository.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/session.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/unyield.hpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/server/yield.hpp"
 "${PugiXML_BASE}/src/pugixml.hpp"
 
)
set(PugiXML_BASE)
SET (SOURCE_FILES_BASE
 "server/mime_types.cpp"
 "parametercontainer/parametercontainer.cpp"
 "server/reply.cpp"
 "server/request_parser.cpp"
 "server/requesthandler.cpp"
 "server/server.cpp"
 "server/serverfunctionrepository.cpp"
 "${PugiXML_BASE}/src/pugixml.cpp"
 "${PugiXML_BASE}/src/pugiconfig.hpp"
)


SET (SOURCE_FILES
  ${SOURCE_FILES_BASE}
  ${SOURCE_FILES_INCLUDE}
  
)



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PugiXML_BASE}/src/)
source_group("" FILES ${SOURCE_FILES})

add_library(serpents_ssl SHARED ${SOURCE_FILES})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR} )

add_definitions(/D _WIN32_WINNT=0x0501 -D_SCL_SECURE_NO_WARNINGS )
target_link_libraries(serpents_ssl Ws2_32.lib odbc32.lib odbccp32.lib  ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})






