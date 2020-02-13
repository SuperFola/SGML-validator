cmake_minimum_required(VERSION 3.8)

project(TP C)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})