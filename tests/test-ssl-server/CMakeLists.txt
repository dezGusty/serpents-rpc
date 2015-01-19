SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")

project(test-ssl-server)

  
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
file (GLOB TEST-SSL-SERVER
  "*.h"
  "*.cpp")

source_group("Test-SSL-Server" FILES ${TEST-SSL-SERVER})


find_package(Boost 1.36.0 COMPONENTS system date_time regex REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(GTestLocal)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR} )
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/dependencies)
include_directories(${GTEST_INCLUDE_DIR}) 
link_directories(${CMAKE_SOURCE_DIR}/build)
add_executable (test-ssl-server test-ssl-server.cpp)
add_definitions(/D _WIN32_WINNT=0x0501 -D_SCL_SECURE_NO_WARNINGS -DSSL_SERVER_EXPORT)
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
target_link_libraries(test-ssl-server Ws2_32.lib odbc32.lib odbccp32.lib ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} 
            ${GTEST_LIBRARIES} serpents_ssl)

if (SERPENTS_RPC_USELOG4CPP)
 FIND_PACKAGE(LOG4CPP_Local)
  target_link_libraries(test-ssl-server ${LOG4CPP_LIBRARY})
  add_definitions(-DUSE_LOG4CPP)
endif ()

#add_definitions(-DSERPENTSRPC_EXPORTS)
#install (TARGETS serpents
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#    COMPONENT library
#    )
    
