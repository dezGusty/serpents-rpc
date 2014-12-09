INCLUDE(${CMAKE_SOURCE_DIR}/CMake/HandleLibraryTypes.cmake)


# Set the paths to search for as possible locations of the library.
SET (XMLLIB_XMLRPC_C_SEARCH_PATH 
    $ENV{XMLRPC_C_ROOT}
    ${CMAKE_SOURCE_DIR}/dependencies
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

MESSAGE(STATUS "XMLLIB_XMLRPC_C_SEARCH_PATH: ${XMLLIB_XMLRPC_C_SEARCH_PATH}")

#
# Locate the link libraries (lib files)
#
FIND_LIBRARY(XMLLIB_XMLRPC_C_LIBRARY_OPTIMIZED
    NAMES libxmlrpc++
    PATHS ${XMLLIB_XMLRPC_C_SEARCH_PATH}
    PATH_SUFFIXES bin/Release bin/Release-DLL-Win32 bin
                  lib libs build/lib build/Release
)

FIND_LIBRARY(XMLLIB_XMLRPC_C_LIBRARY_DEBUG
    NAMES libxmlrpc++
    PATHS ${XMLLIB_XMLRPC_C_SEARCH_PATH}
    PATH_SUFFIXES bin/Debug bin/Debug-DLL-Win32 bin 
                  lib libs build/lib build/Debug 
)

#
# Locate the shared libraries (dll files)
#
FIND_FILE (XMLLIB_XMLRPC_C_BINARY_REL 
    NAMES "libxmlrpc++.dll" 
    HINTS ${XMLLIB_XMLRPC_C_SEARCH_PATH}
    PATH_SUFFIXES "" bin bin/Release bin/Release-DLL-Win32
                  build/lib build/Release Release 
                  lib libs 
)
  
FIND_FILE (XMLLIB_XMLRPC_C_BINARY_DBG
    NAMES "libxmlrpc++.dll" 
    HINTS ${XMLLIB_XMLRPC_C_SEARCH_PATH}
    PATH_SUFFIXES "" bin bin/Debug bin/Debug-DLL-Win32
                  build/lib build/Debug Debug 
                  lib libs 
)
 

# Collect debug and optimized libraries.
HANDLE_LIBRARY_TYPES(XMLLIB_XMLRPC_C)
