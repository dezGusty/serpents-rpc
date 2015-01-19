SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")

SET(SERPENTS_RPC_LIB_TYPE SHARED)

project(test-server)
include_directories("${CMAKE_SOURCE_DIR}/dependencies/")
include_directories("${CMAKE_SOURCE_DIR}/serpents-rpc/")
link_directories("${CMAKE_SOURCE_DIR}/build")

link_directories("${CMAKE_SOURCE_DIR}/bin/release")
  
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
file (GLOB SERPENTS-TEST-SERVER
  "*.h"
  "*.cpp")

source_group("Test-Server" FILES ${SERPENTS-TEST-SERVER})

FIND_PACKAGE(XMLRPC_C_Locall)
FIND_PACKAGE(XMLRPCpp_Local)
FIND_PACKAGE(GTestLocal)

add_executable (testserver test-server.cpp)
target_link_libraries(testserver Ws2_32.lib odbc32.lib odbccp32.lib server_manager ${GTest_LIBRARY})
target_link_libraries(testserver serpents-rpc)

ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
#add_definitions(-DSERPENTSRPC_EXPORTS)
#install (TARGETS serpents
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#    COMPONENT library
#    )
    
