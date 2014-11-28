SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")
project(test-client)
include_directories("${CMAKE_SOURCE_DIR}/dependencies/" )
include(${CMAKE_SOURCE_DIR}/CMake/FindGTestLocal.cmake)

link_directories("${CMAKE_SOURCE_DIR}/dependencies/bin/release")
link_directories("${GTest_INCLUDE_DIR}/../build/")


include_directories("${GTest_INCLUDE_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

file (GLOB SERPENTS-TEST-CLIENT
  "*.h"
  "*.cpp")

source_group("Test-Client" FILES ${SERPENTS-TEST-CLIENT})

FIND_PACKAGE(XMLRPC_C_Locall)
FIND_PACKAGE(XMLRPCpp_Local)
FIND_PACKAGE(GTestLocal)

add_executable (testclient test-client.cpp)
target_link_libraries(testclient Ws2_32.lib odbc32.lib odbccp32.lib ${XMLLIB_XMLRPC_C_LIBRARY} ${XMLLIB_XMLRPCpp_LIBRARY} ${GTest_LIBRARY})

#add_definitions(-DSERPENTSRPC_EXPORTS)
#install (TARGETS serpents
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#    COMPONENT library
#    )
    


