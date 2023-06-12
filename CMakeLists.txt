cmake_minimum_required(VERSION 3.22)
project(mikroprojekt_3_without_GUI)

set(CMAKE_CXX_STANDARD 20)

set(TICTACTOE include/TicTacToe.h src/TicTacToe.cpp)
set(PLAYER include/Player.h src/Player.cpp)

add_executable(mikroprojekt_3_without_GUI main.cpp ${TICTACTOE} ${PLAYER})
