include_directories("${PROJECT_SOURCE_DIR}/include/")

link_directories("${PROJECT_SOURCE_DIR}/bin/release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

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
		

