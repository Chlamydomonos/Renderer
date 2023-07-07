cmake_minimum_required(VERSION 3.10)

project(Renderer CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

flex_target(lexer src/parser/obj.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
bison_target(parser src/parser/obj.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/parser.h)
add_flex_bison_dependency(lexer parser)

include_directories(src/lib ${CMAKE_CURRENT_BINARY_DIR}/include ${FLEX_INCLUDE_DIRS} src/parser)

file(COPY src/parser/obj.l DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/parser)
file(COPY src/parser/obj.y DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/parser)

file(GLOB LIB_SOURCES "src/lib/*.cc")
file(GLOB PARSER_SOURCES "src/parser/*.cc")

add_executable(${PROJECT_NAME} WIN32 ${LIB_SOURCES} ${PARSER_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/lexer.c ${CMAKE_CURRENT_BINARY_DIR}/parser.c src/exe/main.cc)
add_executable(${PROJECT_NAME}_test ${LIB_SOURCES} ${PARSER_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/lexer.c ${CMAKE_CURRENT_BINARY_DIR}/parser.c src/test/main.cc)