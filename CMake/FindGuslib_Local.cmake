
INCLUDE(${CMAKE_SOURCE_DIR}/CMake/HandleLibraryTypes.cmake)

# Set the paths to search for as possible locations of the library.
SET (GUSLIB_SEARCH_PATH 
        $ENV{GUSLIB_ROOT}
        ${PROJECT_SOURCE_DIR}/../guslib
        ${PROJECT_SOURCE_DIR}/../
        ${PROJECT_SOURCE_DIR}/../../guslib
)

FIND_PATH(GUSLIB_INCLUDE_DIR guslib/guslib_version.hpp
    PATHS  ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES guslib
                guslib/guslib
)

#
# Locate the link libraries (lib files)
# A recommended setting is to use a "build" directory to build guslib with CMake.
#     E.g. Where is the source code: c:/code/guslib
#          Where to build the binaries: c:/code/guslib/build
#
FIND_LIBRARY(GUSLIB_LIBRARY_OPTIMIZED
    NAMES guslib
    PATHS ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES bin/Release lib libs bin
                  bin/Release-DLL-Win32 
                  build/lib build/Release
                  build/lib/Release  
                  lib/Relase /lib/Release
)

FIND_LIBRARY(GUSLIB_LIBRARY_DEBUG
    NAMES guslib
    PATHS ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES bin/Debug lib libs bin
                  bin/Debug-DLL-Win32 
                  build/lib build/Debug
                  build/lib/Debug 
                  lib/Debug /lib/Debug
)

#
# Locate the shared libraries (dll files)
#
FIND_FILE (GUSLIB_BINARY_REL 
    NAMES guslib.dll
    HINTS ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES "" lib libs bin Release 
                  build/bin/Release build/bin 
                  build/lib build/Release 
                  bin/Release-DLL-Win32 lib/Relase /lib/Release
)
 
FIND_FILE (GUSLIB_BINARY_DBG
    NAMES guslib.dll
    HINTS ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES "" lib libs bin Debug
                  build/bin/Debug build/bin
                  build/lib build/Debug
                  bin/Debug-DLL-Win32 lib/Debug /lib/Debug
)
 
# Collect debug and optimized libraries.
HANDLE_LIBRARY_TYPES(GUSLIB)

