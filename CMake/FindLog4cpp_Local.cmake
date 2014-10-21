SET (LOG4CPP_SEARCH_PATH 
	$ENV{LOG4CPP_ROOT}
	${PROJECT_SOURCE_DIR}/dependencies/log4cpp
    ${PROJECT_SOURCE_DIR}/../dependencies/xmlrpc-c
	)        
find_path(LOG4CPP_INCLUDE_DIR log4cpp/FileAppender.hh
  PATHS  ${LOG4CPP_SEARCH_PATH}
  PATH_SUFFIXES include 
                log4cpp/include
                /../

)
 
FIND_LIBRARY(LOG4CPP_LIBRARY_OPTIMIZED
  NAMES log4cpp
  PATHS ${LOG4CPP_SEARCH_PATH}
  PATH_SUFFIXES bin/Release lib lib/Release libs bin build/lib build/Release bin/Release bin/Release-DLL-Win32 
)

FIND_LIBRARY(LOG4CPP_LIBRARY_DEBUG
  NAMES log4cpp
  PATHS ${LOG4CPP_SEARCH_PATH}
  PATH_SUFFIXES lib lib/Debug libs bin build/lib build/Debug bin/Debug bin/Debug-DLL-Win32 
)

HANDLE_LIBRARY_TYPES(LOG4CPP)