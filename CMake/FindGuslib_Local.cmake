
INCLUDE(${CMAKE_SOURCE_DIR}/CMake/HandleLibraryTypes.cmake)

# Set the paths to search for as possible locations of the library.
SET (GUSLIB_SEARCH_PATH ${PROJECT_SOURCE_DIR}/../guslib
		${PROJECT_SOURCE_DIR}/../
		${PROJECT_SOURCE_DIR}/../../guslib
        $ENV{GUSLIB_ROOT})
		

FIND_PATH(GUSLIB_INCLUDE_DIR guslib/common/singleton.h
  PATHS  ${GUSLIB_SEARCH_PATH}
  PATH_SUFFIXES guslib
                guslib/guslib
                guslib/guslib
)


FIND_LIBRARY(GUSLIB_LIBRARY_OPTIMIZED
  NAMES guslib
  PATHS ${GUSLIB_SEARCH_PATH}
  PATH_SUFFIXES bin/Release lib libs bin build/lib build/Release bin/Release bin/Release-DLL-Win32 lib/Relase /lib/Release
)


FIND_LIBRARY(GUSLIB__LIBRARY_DEBUG
  NAMES guslib
  PATHS ${GUSLIB_SEARCH_PATH}
  PATH_SUFFIXES lib libs bin build/lib build/Debug bin/Debug bin/Debug-DLL-Win32 lib/Debug /lib/Debug
)

FIND_FILE (GUSLIB__BINARY_REL 
      NAMES "guslib.dll" 
      HINTS ${GUSLIB_SEARCH_PATH}
      PATH_SUFFIXES "" lib libs bin build/lib build/Release Release bin/Release-DLL-Win32 lib/Relase /lib/Release
  )
 
FIND_FILE (GUSLIB__BINARY_DBG
      NAMES "guslib.dll" 
      HINTS ${GUSLIB_SEARCH_PATH}
      PATH_SUFFIXES "" lib libs bin build/lib build/Release Release bin/Debug-DLL-Win32 lib/Debug /lib/Debug
  )
 
 HANDLE_LIBRARY_TYPES(GUSLIB)