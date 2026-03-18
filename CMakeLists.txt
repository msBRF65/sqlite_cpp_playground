cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

project(sqlite_cpp_playground)

# Get SQLite
find_package(SQLite3 REQUIRED)
if(NOT TARGET SQLite3::SQLite3) # CMake < 4.3
  add_library(SQLite3::SQLite3 ALIAS SQLite::SQLite3)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(app main.cpp)
set_property(TARGET app PROPERTY CXX_STANDARD 17)
target_compile_options(app PRIVATE -Wall -Wextra -Wno-deprecated)
target_link_libraries(app PRIVATE SQLite3::SQLite3)
