project(test-client)
include_directories("${CMAKE_SOURCE_DIR}/dependencies/")

link_directories("${CMAKE_SOURCE_DIR}/dependencies/bin/release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

file (GLOB SERPENTS-TEST-CLIENT
	"*.h"
	"*.cpp")

source_group("Test-Client" FILES ${SERPENTS-TEST-CLIENT})



add_executable (testclient test-client.cpp)
target_link_libraries(testclient Ws2_32.lib odbc32.lib odbccp32.lib xmlrpc.lib libxmlrpc++.lib gtest.lib)

#add_definitions(-DSERPENTSRPC_EXPORTS)
#install (TARGETS serpents
#		ARCHIVE DESTINATION lib
#		LIBRARY DESTINATION lib
#		COMPONENT library
#		)
		

