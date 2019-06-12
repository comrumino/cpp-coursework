cmake_minimum_required(VERSION 3.14.0)
project(CPROGRM)
# CXX Preferences
SET(CMAKE_CXX_COMPILER             "/usr/bin/clang++")
# SET(CMAKE_CXX_FLAGS                "-Wall -Wextra -Weverything -pedantic -Wno-sign-conversion")
SET(CMAKE_CXX_FLAGS_DEBUG          "-g")
SET(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
# Set shared object to be linked later
add_library(unitlite SHARED IMPORTED)
set_property(TARGET unitlite PROPERTY IMPORTED_LOCATION "$ENV{PWD}/lib/libUnitLite.so")
# Include some dirs
include_directories ("$ENV{RELPATH}")
include_directories ("${PROJECT_SOURCE_DIR}/include")
# include_directories ("/usr/include/openssl/")
# Glob the source and add exec and link
file(GLOB SRC_FILES $ENV{RELPATH}/*.cpp)
add_executable(CPROGRM  ${SRC_FILES})
TARGET_LINK_LIBRARIES(CPROGRM unitlite)
