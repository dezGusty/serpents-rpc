include_directories("${PROJECT_SOURCE_DIR}/include/")


link_directories("${PROJECT_SOURCE_DIR}/bin/release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

SET ( SOURCE_FILES_SERVER
  "./serpents/rpc/server/server.h"
  "./serpents/rpc/server/server.cpp"
  "./serpents/rpc/server/implservermethod.h"
  "./serpents/rpc/server/implservermethod.cpp"
  "./serpents/rpc/server/repository.h"
  "./serpents/rpc/server/repository.cpp"
  "./serpents/rpc/server/rpcselector.h"
  "./serpents/rpc/server/rpcselector.cpp"
  "./serpents/rpc/server/serveroptions.h"
  "./serpents/rpc/server/serveroptions.cpp"
  "./serpents/rpc/server/serverstartup.h"
  "./serpents/rpc/server/serverstartup.cpp"
)

SET (SOURCE_FILES_LAUNCHER
  "./serpents/rpc/launcher/processrunner.h"
  "./serpents/rpc/launcher/processrunner.cpp"
)
SET (SOURCE_FILES_LOG
  "./serpents/rpc/log/log.h"
  "./serpents/rpc/log/log.cpp"
)
SET (SOURCE_FILES_PARAMETERS
 "./serpents/rpc/parameters/parametercontainer.h"
 "./serpents/rpc/parameters/parametercontainer.cpp"
 "./serpents/rpc/parameters/retvalue.h"
 "./serpents/rpc/parameters/retvalue.cpp"
 )

SET (SOURCE_FILES_BASE
 "./serpents/rpc/base.h"
)
SET (SOURCE_FILES
  ${SOURCE_FILES_BASE}
  ${SOURCE_FILES_PARAMETERS}
  ${SOURCE_FILES_SERVER}
  ${SOURCE_FILES_LAUNCHER}
  ${SOURCE_FILES_LOG}
 
)

#visual studio
SOURCE_GROUP("serpents\\rpc" FILES
  ${SOURCE_FILES_BASE}
)

SOURCE_GROUP("serpents\\rpc\\server\\" FILES
  ${SOURCE_FILES_SERVER}
)

SOURCE_GROUP("serpents\\rpc\\launcher\\" FILES
  ${SOURCE_FILES_LAUNCHER}
)

SOURCE_GROUP("serpents\\rpc\\log" FILES
  ${SOURCE_FILES_LOG}
)
SOURCE_GROUP("serpents\\rpc\\parameters" FILES
  ${SOURCE_FILES_PARAMETERS}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
source_group("" FILES ${SOURCE_FILES})


add_library(serpents SHARED ${SOURCE_FILES})

target_link_libraries(serpents Ws2_32.lib odbc32.lib odbccp32.lib xmlrpc.lib libxmlrpc++.lib)

add_definitions(-DSERPENTSRPC_EXPORTS)

if (SERPENTS_RPC_USELOG4CPP)
	link_directories("${PROJECT_SOURCE_DIR}/bin/release/log4cpp")
  target_link_libraries(serpents log4cpp.lib)
  add_definitions(-DUSE_LOG4CPP)
endif ()
install (TARGETS serpents
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib
		COMPONENT library
		)