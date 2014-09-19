include_directories("${PROJECT_SOURCE_DIR}/include/")


link_directories("${PROJECT_SOURCE_DIR}/bin/release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
file (GLOB SERPENTS-SRC
	"*.h"
	"*.cpp")

source_group("" FILES ${SERPENTS-SRC})


add_library(serpents SHARED ${SERPENTS-SRC})

target_link_libraries(serpents Ws2_32.lib odbc32.lib odbccp32.lib xmlrpc.lib libxmlrpc++.lib)

add_definitions(-DSERPENTSRPC_EXPORTS)
install (TARGETS serpents
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib
		COMPONENT library
		)
		
