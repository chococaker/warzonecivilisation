cmake_minimum_required(VERSION 3.16)
project(warzonecivilisation LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB_RECURSE SRC_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h")
file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp")

file(GLOB_RECURSE LIB_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lib/**/*.h")
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lib/**/*.cpp")

add_executable(warzonecivilisation ${SRC_SOURCES} ${SRC_HEADERS} ${LIB_SOURCES} ${LIB_HEADERS})

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/lib)

install(TARGETS warzonecivilisation)
