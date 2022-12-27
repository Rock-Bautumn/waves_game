project(waves_game)

cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_FLAGS "-D_XOPEN_SOURCE_EXTENDED")
set(CMAKE_CXX_STANDARD 20)
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# add executable
add_executable(waves_game src/main.cpp)
#libraries
add_library(window src/window/window.h src/window/window.cpp src/window/point.h)
add_library(wave src/wave.cpp src/waves.hpp)
add_library(cchar src/cchar/cchar.h src/cchar/cchar.cpp)

# Link all libraries to executable
target_link_libraries(waves_game ${CURSES_LIBRARIES} wave window cchar )
