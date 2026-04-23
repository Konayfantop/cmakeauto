cmake_minimum_required(VERSION 3.23)

project(cmakeauto VERSION 1.0.0)

add_executable(cmakeAutoExe)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/parserCode/src/*.c)

# Project itself
target_sources(cmakeAutoExe PRIVATE ${SRC_FILES})
target_include_directories(cmakeAutoExe PRIVATE ${CMAKE_SOURCE_DIR}/parserCode/include)

# Unittest unity module
add_library(unity ${CMAKE_SOURCE_DIR}/external/Unity/src/unity.c)
target_include_directories(unity PUBLIC ${CMAKE_SOURCE_DIR}/external/Unity/src)

# Unittest exe
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/parserCode/test/*.c)
# remove main manually
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/parserCode/src/main.c)
add_executable(testExec ${TEST_FILES} ${SRC_FILES})
target_link_libraries(testExec unity)
target_include_directories(testExec PRIVATE ${CMAKE_SOURCE_DIR}/parserCode/include)

enable_testing()

add_test(NAME testExec COMMAND testExec)