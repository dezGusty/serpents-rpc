project(test-server)
include_directories("${CMAKE_SOURCE_DIR}/include/")
include_directories("${CMAKE_SOURCE_DIR}/serpents-src/")

link_directories("${CMAKE_SOURCE_DIR}/bin/release")
link_directories(${CMAKE_SOURCE_DIR}/build)
  
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
file (GLOB SERPENTS-TEST-SERVER
	"*.h"
	"*.cpp")

source_group("Test-Server" FILES ${SERPENTS-TEST-SERVER})



add_executable (testserver test-server.cpp)
target_link_libraries(testserver Ws2_32.lib odbc32.lib odbccp32.lib xmlrpc.lib libxmlrpc++.lib)
target_link_libraries(testserver serpents.lib)
#add_definitions(-DSERPENTSRPC_EXPORTS)
#install (TARGETS serpents
#		ARCHIVE DESTINATION lib
#		LIBRARY DESTINATION lib
#		COMPONENT library
#		)
		
