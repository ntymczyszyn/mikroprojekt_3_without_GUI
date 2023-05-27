cmake_minimum_required(VERSION 3.25)
project(mikroprojekt_3_without_GUI)

set(CMAKE_CXX_STANDARD 20)

set(TICTACTOE include/TicTacToe.h src/TicTacToe.cpp)

add_executable(mikroprojekt_3_without_GUI main.cpp ${TICTACTOE})

#find_package(fmt CONFIG REQUIRED)
#target_link_libraries(main PRIVATE fmt::fmt)