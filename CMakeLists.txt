cmake_minimum_required(VERSION 3.23)

project(cmakeauto VERSION 1.0.0)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/parserCode/src/*.c)
file(GLOB_RECURSE UTILITIES_SRC CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/utilities/src/*.c)
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/test/*.c)

# --------------------------------------------------
# Project executable
# --------------------------------------------------

add_executable(cmakeAutoExe)
target_sources(cmakeAutoExe PRIVATE ${SRC_FILES})
target_include_directories(cmakeAutoExe PRIVATE ${CMAKE_SOURCE_DIR}/parserCode/include)

# --------------------------------------------------
# Utilities library
# --------------------------------------------------

add_library(utilities ${UTILITIES_SRC})
target_include_directories(utilities PUBLIC ${CMAKE_SOURCE_DIR}/utilities/include)
target_link_libraries(cmakeAutoExe PRIVATE utilities)

# --------------------------------------------------
# Unity
# --------------------------------------------------

add_library(unity ${CMAKE_SOURCE_DIR}/external/Unity/src/unity.c)
target_include_directories(unity PUBLIC ${CMAKE_SOURCE_DIR}/external/Unity/src)

# --------------------------------------------------
# Test executable
# --------------------------------------------------

add_executable(testExec ${TEST_FILES})

# remove production main
set(SRC_NO_MAIN ${SRC_FILES})
list(REMOVE_ITEM SRC_NO_MAIN ${CMAKE_SOURCE_DIR}/parserCode/src/main.c)
target_sources(testExec PRIVATE ${SRC_NO_MAIN})
target_link_libraries(testExec PRIVATE unity utilities)
target_include_directories(testExec PRIVATE ${CMAKE_SOURCE_DIR}/parserCode/include)

# --------------------------------------------------
# Testing
# --------------------------------------------------

enable_testing()

add_test(NAME testExec COMMAND testExec)