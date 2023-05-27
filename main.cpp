#include <iostream>
#include "include/TicTacToe.h"

int main() {
    TicTacToe* game = new TicTacToe(3,3, 3);
    //game->play(false);
   game->displayBoard();
    delete game;
    return 0;
}
