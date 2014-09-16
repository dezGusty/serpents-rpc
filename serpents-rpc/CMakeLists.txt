include_directories("${PROJECT_SOURCE_DIR}/include/")

link_directories("${PROJECT_SOURCE_DIR}/libs/")


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
		
