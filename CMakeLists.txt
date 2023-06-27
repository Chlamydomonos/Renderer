cmake_minimum_required(VERSION 3.10)

project(Renderer)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/lib)
file(GLOB SOURCE_FILES "src/lib/*.cc")

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} src/exe/main.cc)
add_executable(${PROJECT_NAME}_test ${SOURCE_FILES} src/test/main.cc)