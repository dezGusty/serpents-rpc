SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMake/;${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_ROOT}/Modules;${CMAKE_MODULE_PATH}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

MESSAGE("")
MESSAGE("*")
MESSAGE("Building test-launcher")
MESSAGE("*")
MESSAGE("")

find_package(Guslib_Local)
include_directories(${GUSLIB_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/build)
include_directories(${PROJECT_SOURCE_DIR})

link_directories()
SET (SOURCE_FILES_TEST_LAUNCHER
 "${CMAKE_CURRENT_SOURCE_DIR}/test-launcher.cpp")

SET (SOURCE_FILES
 ${SOURCE_FILES_TEST_LAUNCHER})

SOURCE_GROUP("test-launcher" FILES
  ${SOURCE_FILES}
)

ADD_DEFINITIONS(-DXMLRPC_CPP_EXP)
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)


add_executable(test-launcher ${SOURCE_FILES})

SET (LINK_LIBS_TEST_LAUNCHER
  ${GUSLIB_LIBRARY}
  serpents_launcher
)
MESSAGE (STATUS "LINK_LIBS: ${LINK_LIBS_TEST_LAUNCHER}")

# Append OS system specific libraries.
IF(WIN32)
  SET(LINK_LIBS_TEST_LAUNCHER
	ws2_32.lib
    winmm.lib
    ${LINK_LIBS_TEST_LAUNCHER}
    )
ELSEIF(UNIX AND NOT APPLE)
  SET(LINK_LIBS_TEST_LAUNCHER
    ${X11_X11_LIB}
    ${X11_Xrandr_LIB}
    ${LINK_LIBS_TEST_LAUNCHER}
    )
ENDIF()

# Set the link libraries for the project.
TARGET_LINK_LIBRARIES(test-launcher ${LINK_LIBS_TEST_LAUNCHER})
