
INCLUDE(${CMAKE_SOURCE_DIR}/CMake/HandleLibraryTypes.cmake)

# Set the paths to search for as possible locations of the library.
SET (LOG4CPP_SEARCH_PATH 
    $ENV{LOG4CPP_ROOT}
    ${CMAKE_SOURCE_DIR}/dependencies
    ${PROJECT_SOURCE_DIR}/dependencies/log4cpp
    ${PROJECT_SOURCE_DIR}/../dependencies/xmlrpc-c
)

FIND_PATH(LOG4CPP_INCLUDE_DIR log4cpp/FileAppender.hh
    PATHS  ${LOG4CPP_SEARCH_PATH}
    PATH_SUFFIXES include 
                  log4cpp/include
                  /../
)

#
# Locate the link libraries (lib files)
#
FIND_LIBRARY(LOG4CPP_LIBRARY_OPTIMIZED
    NAMES log4cpp
    PATHS ${LOG4CPP_SEARCH_PATH}
    PATH_SUFFIXES bin/Release lib lib/Release 
                  libs bin build/lib 
                  build/Release bin/Release-DLL-Win32 
)

FIND_LIBRARY(LOG4CPP_LIBRARY_DEBUG
    NAMES log4cpp
    PATHS ${LOG4CPP_SEARCH_PATH}
    PATH_SUFFIXES bin/Debug lib lib/Debug 
                  libs bin build/lib 
                  build/Debug bin/Debug-DLL-Win32 
)

# Collect debug and optimized libraries.
HANDLE_LIBRARY_TYPES(LOG4CPP)
