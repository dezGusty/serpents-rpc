include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_SOURCE_DIR}/serpents-src/")

link_directories("${PROJECT_SOURCE_DIR}/bin/release")

  
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
file (GLOB SERPENTS-TEST-SERVER
	"*.h"
	"*.cpp")

source_group("Test-Server" FILES ${SERPENTS-TEST-SERVER})



add_executable (testserver test-server.cpp)
target_link_libraries(testserver Ws2_32.lib odbc32.lib odbccp32.lib xmlrpc.lib libxmlrpc++.lib serpents.lib)

#add_definitions(-DSERPENTSRPC_EXPORTS)
#install (TARGETS serpents
#		ARCHIVE DESTINATION lib
#		LIBRARY DESTINATION lib
#		COMPONENT library
#		)
		
