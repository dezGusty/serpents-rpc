SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

MESSAGE("")
MESSAGE("*")
MESSAGE("Building serpents-launcher")
MESSAGE("*")
MESSAGE("")

find_package(Guslib_Local)
include_directories(${GUSLIB_INCLUDE_DIR})
include_directories()

SET (SOURCE_FILES_LAUNCHER
 "${CMAKE_CURRENT_SOURCE_DIR}/launcher_build_opts.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/threadpool.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/threadpool.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/task.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/task.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/processutil.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/processutil.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/processfactory.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/processfactory.cpp")

SET (SOURCE_FILES
 ${SOURCE_FILES_LAUNCHER})

SOURCE_GROUP("launcher" FILES
  ${SOURCE_FILES}
)

add_definitions(-DLAUNCHER_EXP)
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

add_library(serpents_launcher SHARED ${SOURCE_FILES})

# ---------------- Link Libraries section --------------------
# Set the link options: the libraries to link against. Store them in a temporary variable
# as these are the common, cross-system link libraries.
SET (LINK_LIBS_LAUNCHER
  ${GUSLIB_LIBRARY}
)

MESSAGE (STATUS "LINK_LIBS_LAUNCHER: ${LINK_LIBS_LAUNCHER}")

# Append OS system specific libraries.
IF(WIN32)
  SET(LINK_LIBS_LAUNCHER
    ws2_32.lib
    winmm.lib
    ${LINK_LIBS_LAUNCHER}
    )
ELSEIF(UNIX AND NOT APPLE)
  SET(LINK_LIBS_LAUNCHER
    ${X11_X11_LIB}
    ${X11_Xrandr_LIB}
    ${LINK_LIBS_LAUNCHER}
    )
ENDIF()

target_link_libraries(serpents_launcher ${LINK_LIBS_LAUNCHER})