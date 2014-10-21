INCLUDE(${CMAKE_SOURCE_DIR}/CMake/HandleLibraryTypes.cmake)


# Set the paths to search for as possible locations of the library.
SET (XMLLIB_XMLRPC_C_SEARCH_PATH 
	$ENV{XMLRPC_C_ROOT}
	${PROJECT_SOURCE_DIR}/dependencies/xmlrpc-c
    ${PROJECT_SOURCE_DIR}/../dependencies/xmlrpc-c
	)        
find_path(XMLLIB_XMLRPC_C_INCLUDE_DIR xmlrpc-c/server_abyss.h
  PATHS  ${XMLLIB_XMLRPC_C_SEARCH_PATH}
  PATH_SUFFIXES include 
                xmlrpc-advanced/include
                xmlrpc-c
				include/xmlrpc-c
				/../

)

FIND_LIBRARY(XMLLIB_XMLRPC_C_LIBRARY_OPTIMIZED
  NAMES libxmlrpc++
  PATHS ${XMLLIB_XMLRPC_C_SEARCH_PATH}
  PATH_SUFFIXES bin/Release lib libs bin build/lib build/Release bin/Release bin/Release-DLL-Win32
)

FIND_LIBRARY(XMLLIB_XMLRPC_C_LIBRARY_DEBUG
  NAMES libxmlrpc++
  PATHS ${XMLLIB_XMLRPC_C_SEARCH_PATH}
  PATH_SUFFIXES lib libs bin build/lib build/Debug bin/Debug bin/Debug-DLL-Win32
)
FIND_FILE (XMLLIB_XMLRPC_C_BINARY_REL 
      NAMES "libxmlrpc++.dll" 
      HINTS ${XMLLIB_XMLRPC_C_SEARCH_PATH}
      PATH_SUFFIXES "" lib libs bin build/lib build/Release Release bin/Release-DLL-Win32
  )
FIND_FILE (XMLLIB_XMLRPC_C_BINARY_DBG
      NAMES "libxmlrpc++.dll" 
      HINTS ${XMLLIB_XMLRPC_C_SEARCH_PATH}
      PATH_SUFFIXES "" lib libs bin build/lib build/Release Release bin/Debug-DLL-Win32
  )
 

HANDLE_LIBRARY_TYPES(XMLLIB_XMLRPC_C)