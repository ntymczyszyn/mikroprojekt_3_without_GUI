#include <iostream>
#include <memory>
#include "include/TicTacToe.h"

int main() {
    constexpr int size{3};
    constexpr int winning{3};
    std::unique_ptr<TicTacToe> game = std::make_unique<TicTacToe>(size,size, winning);
    game->play(false);
    //game->displayBoard();
    return 0;
}
