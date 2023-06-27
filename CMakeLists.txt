cmake_minimum_required(VERSION 3.10)

project(Renderer)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
file(GLOB SOURCE_FILES "src/*.cc")

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})