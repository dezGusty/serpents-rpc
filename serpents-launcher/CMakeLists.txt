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
include_directories(${GUSLIB_INCLUDE_DIR}/guslib)
include_directories()

SET (SOURCE_FILES_LAUNCHER
 "${CMAKE_CURRENT_SOURCE_DIR}/launcher_build_opts.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/launcher_manager.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/launcher_manager.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/threadpool.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/task.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/task.cpp"
 "${CMAKE_CURRENT_SOURCE_DIR}/threadpool.cpp")
SET (SOURCE_FILES
 ${SOURCE_FILES_LAUNCHER})

SOURCE_GROUP("launcher" FILES
  ${SOURCE_FILES}
)

add_definitions(-DLAUNCHER_EXP)
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

add_library(serpents_launcher SHARED ${SOURCE_FILES})

target_link_libraries(serpents_launcher ${GUSLIB_LIBRARY} )