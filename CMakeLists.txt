cmake_minimum_required(VERSION 3.0)

project(tests)
add_definitions(-Wall -ansi -pthread -std=c++11 -lncurses -Wall)
# set( CMAKE_CXX_FLAGS "-O0 -Wall -pedantic -ansi -std=c++11 --coverage" )
set(CMAKE_EXE_LINKER_FLAGS "-pthread -lncurses")

# set(CURSES_LIBRARY_NAME "curses")
# set(NCURSES_LIBRARY_NAME "ncurses")

# include_directories(./include)

SET(Boost_USE_STATIC_LIBS ON)
# SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ./include)
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

set(MAIN_SOURCE src/main.cpp)
set(GAME_SOURCE src/game.cpp)
set(SNAKE_SOURCE src/snake.cpp)
set(OBJECT_SOURCE src/object.cpp)
set(POINT_SOURCE src/Point.cpp)

add_executable(main ${MAIN_SOURCE} ${GAME_SOURCE} ${SNAKE_SOURCE} ${OBJECT_SOURCE} ${POINT_SOURCE})
target_link_libraries(main ncurses ${USED_LIBS})
