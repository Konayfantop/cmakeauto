cmake_minimum_required(VERSION 3.23)

project(cmakeauto VERSION 1.0.0)

add_executable(cmakeAutoExe)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/parserCode/src/*.c)

target_sources(cmakeAutoExe
  PRIVATE 
    ${SRC_FILES})

target_include_directories(cmakeAutoExe
  PRIVATE
    ${CMAKE_SOURCE_DIR}/parserCode/include)